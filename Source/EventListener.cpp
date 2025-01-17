#include <cassert>
#include <utility>

#include "EventListener.h"
#include "fnv.h"
#include "GameData.h"
#include "Hacks/Misc.h"
#include "InventoryChanger/InventoryChanger.h"
#include "Hacks/Visuals.h"
#include "Interfaces.h"
#include "Memory.h"
#include "SDK/GameEvent.h"
#include "SDK/UtlVector.h"

namespace
{
    class EventListenerImpl : public GameEventListener {
    public:
        void fireGameEvent(GameEvent* event) override
        {
            switch (fnv::hashRuntime(event->getName())) {
            case fnv::hash("round_start"):
                GameData::clearProjectileList();
                Misc::preserveKillfeed(true);
                [[fallthrough]];
            case fnv::hash("round_freeze_end"):
                Misc::purchaseList(event);
                break;
            case fnv::hash("player_death"): {
                auto& inventoryChanger = inventory_changer::InventoryChanger::instance();
                inventoryChanger.updateStatTrak(*event);
                inventoryChanger.overrideHudIcon(*event);
                Misc::killMessage(*event);
                Misc::killSound(*event);
                Misc::runLog(event);
                break;
            }
            case fnv::hash("player_hurt"):
                Misc::playHitSound(*event);
                Visuals::hitEffect(event);
                Visuals::hitMarker(event);
                Misc::runLog(event);
                break;
            case fnv::hash("bomb_planted"):
                Misc::runLog(event);
                break;
            case fnv::hash("bomb_defused"):
                Misc::runLog(event);
                break;
            case fnv::hash("bomb_beginplant"):
                Misc::runLog(event);
                break;
            case fnv::hash("bomb_begindefuse"):
                Misc::runLog(event);
                break;
            case fnv::hash("vote_cast"):
                Misc::voteRevealer(*event);
                break;
            case fnv::hash("round_mvp"):
                inventory_changer::InventoryChanger::instance().onRoundMVP(*event);
                break;
            }
        }

        static EventListenerImpl& instance() noexcept
        {
            static EventListenerImpl impl;
            return impl;
        }
    };
}

void EventListener::init() noexcept
{
    assert(interfaces);

    // If you add here listeners which aren't used by client.dll (e.g., item_purchase, bullet_impact), the cheat will be detected by AntiDLL (community anticheat).
    // Instead, register listeners dynamically and only when certain functions are enabled - see Misc::updateEventListeners(), Visuals::updateEventListeners()

    const auto gameEventManager = interfaces->gameEventManager;
    gameEventManager->addListener(&EventListenerImpl::instance(), "round_start");
    gameEventManager->addListener(&EventListenerImpl::instance(), "round_freeze_end");
    gameEventManager->addListener(&EventListenerImpl::instance(), "player_hurt");
    gameEventManager->addListener(&EventListenerImpl::instance(), "player_death");
    gameEventManager->addListener(&EventListenerImpl::instance(), "bomb_planted");
    gameEventManager->addListener(&EventListenerImpl::instance(), "bomb_defused");
    gameEventManager->addListener(&EventListenerImpl::instance(), "bomb_beginplant");
    gameEventManager->addListener(&EventListenerImpl::instance(), "bomb_begindefuse");
    gameEventManager->addListener(&EventListenerImpl::instance(), "vote_cast");
    gameEventManager->addListener(&EventListenerImpl::instance(), "round_mvp");

    // Move our player_death listener to the first position to override killfeed icons (InventoryChanger::overrideHudIcon()) before HUD gets them
    if (const auto desc = memory->getEventDescriptor(gameEventManager, "player_death", nullptr))
        std::swap(desc->listeners[0], desc->listeners[desc->listeners.size - 1]);
    else
        assert(false);

    // Move our round_mvp listener to the first position to override event data (InventoryChanger::onRoundMVP()) before HUD gets them
    if (const auto desc = memory->getEventDescriptor(gameEventManager, "round_mvp", nullptr))
        std::swap(desc->listeners[0], desc->listeners[desc->listeners.size - 1]);
    else
        assert(false);
}

void EventListener::remove() noexcept
{
    assert(interfaces);

    interfaces->gameEventManager->removeListener(&EventListenerImpl::instance());
}
