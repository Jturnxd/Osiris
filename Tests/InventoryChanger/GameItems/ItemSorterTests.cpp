#include <gtest/gtest.h>

#include <InventoryChanger/GameItems/ItemSorter.h>
#include <InventoryChanger/GameItems/Storage.h>
#include <InventoryChanger/GameItems/Lookup.h>

namespace game_items
{
namespace
{

enum class ItemType {
    Gloves,
    Skin,
    Patch,
    Sticker,
    Music,
    Graffiti,
    Collectible,
    NameTag,
    Agent,
    Case,
    CaseKey,
    OperationPass,
    StatTrakSwapTool,
    ViewerPass,
    ServiceMedal,
    SouvenirToken,
    TournamentCoin,
    VanillaKnife,
    VanillaSkin
};

Item& addToStorage(Storage& storage, ItemType type, EconRarity rarity, WeaponId weaponID, std::size_t dataIndex, std::string_view iconPath)
{
    switch (type) {
    case ItemType::Gloves:
        storage.addPaintKit(0, {}, 0.0f, 0.0f);
        storage.addGlovesWithLastPaintKit(rarity, weaponID, iconPath);
        break;
    case ItemType::Skin:
        storage.addPaintKit(0, {}, 0.0f, 0.0f);
        storage.addSkinWithLastPaintKit(rarity, weaponID, iconPath);
        break;
    case ItemType::Patch:
        storage.addPatch(0, {}, rarity, iconPath);
        break;
    case ItemType::Sticker:
        storage.addSticker(0, {}, rarity, iconPath, 0, {}, 0, false);
        break;
    case ItemType::Music:
        storage.addMusic(0, {}, iconPath);
        break;
    case ItemType::Graffiti:
        storage.addGraffiti(0, {}, rarity, iconPath);
        break;
    case ItemType::Collectible:
        storage.addCollectible(rarity, weaponID, false, iconPath);
        break;
    case ItemType::NameTag:
        storage.addNameTag(rarity, weaponID, iconPath);
        break;
    case ItemType::Agent:
        storage.addAgent(rarity, weaponID, iconPath);
        break;
    case ItemType::Case:
        storage.addCase(rarity, weaponID, 0, iconPath);
        break;
    case ItemType::CaseKey:
        storage.addCaseKey(rarity, weaponID, iconPath);
        break;
    case ItemType::OperationPass:
        storage.addOperationPass(rarity, weaponID, iconPath);
        break;
    case ItemType::StatTrakSwapTool:
        storage.addStatTrakSwapTool(rarity, weaponID, iconPath);
        break;
    case ItemType::ViewerPass:
        storage.addViewerPass(rarity, weaponID, 0, iconPath);
        break;
    case ItemType::ServiceMedal:
        storage.addServiceMedal(rarity, 0, weaponID, iconPath);
        break;
    case ItemType::SouvenirToken:
        storage.addSouvenirToken(rarity, weaponID, 0, iconPath);
        break;
    case ItemType::TournamentCoin:
        storage.addTournamentCoin(rarity, weaponID, 0, iconPath);
        break;
    case ItemType::VanillaKnife:
        storage.addVanillaKnife(weaponID, iconPath);
        break;
    case ItemType::VanillaSkin:
        storage.addVanillaSkin(weaponID, iconPath);
        break;
    default:
        throw "Unhandled item type!";
    }
    return storage.getItems().back();
}

class InventoryChanger_GameItems_ItemSorter_GraffitiPartitionTest : public testing::TestWithParam<ItemType> {
protected:
    InventoryChanger_GameItems_ItemSorter_GraffitiPartitionTest()
    {
        storage.addGraffiti(222, {}, EconRarity::Blue, {});
        addToStorage(storage, GetParam(), EconRarity::Red, WeaponId::CS20Case, 0, {});
    }

    [[nodiscard]] const Item& graffiti() const noexcept { return storage.getItems()[0]; }
    [[nodiscard]] const Item& otherItem() const noexcept { return storage.getItems()[1]; }

    Storage storage;
};

TEST_P(InventoryChanger_GameItems_ItemSorter_GraffitiPartitionTest, GraffitiComesBeforeOtherItems) {
    ASSERT_TRUE(ItemSorter{ storage }(graffiti(), otherItem()));
}

TEST_P(InventoryChanger_GameItems_ItemSorter_GraffitiPartitionTest, OtherItemsDoNotComeBeforeGraffiti) {
    ASSERT_FALSE(ItemSorter{ storage }(otherItem(), graffiti()));
}

INSTANTIATE_TEST_SUITE_P(, InventoryChanger_GameItems_ItemSorter_GraffitiPartitionTest,
    testing::Values(
        ItemType::Gloves,
        ItemType::Skin,
        ItemType::Patch,
        ItemType::Sticker,
        ItemType::Music,
        ItemType::Collectible,
        ItemType::NameTag,
        ItemType::Agent,
        ItemType::Case,
        ItemType::CaseKey,
        ItemType::OperationPass,
        ItemType::StatTrakSwapTool,
        ItemType::ViewerPass,
        ItemType::ServiceMedal,
        ItemType::SouvenirToken,
        ItemType::TournamentCoin,
        ItemType::VanillaKnife,
        ItemType::VanillaSkin
    )
);

class InventoryChanger_GameItems_ItemSorter_PatchPartitionTest : public testing::TestWithParam<ItemType> {
protected:
    InventoryChanger_GameItems_ItemSorter_PatchPartitionTest()
    {
        storage.addPatch(111, {}, EconRarity::Blue, {});
        addToStorage(storage, GetParam(), EconRarity::Red, WeaponId::CS20Case, 0, {});
    }

    [[nodiscard]] const Item& patch() const noexcept { return storage.getItems()[0]; }
    [[nodiscard]] const Item& otherItem() const noexcept { return storage.getItems()[1]; }

    Storage storage;
};

TEST_P(InventoryChanger_GameItems_ItemSorter_PatchPartitionTest, PatchComesBeforeOtherItems) {
    ASSERT_TRUE(ItemSorter{ storage }(patch(), otherItem()));
}

TEST_P(InventoryChanger_GameItems_ItemSorter_PatchPartitionTest, OtherItemsDoNotComeBeforePatch) {
    ASSERT_FALSE(ItemSorter{ storage }(otherItem(), patch()));
}

INSTANTIATE_TEST_SUITE_P(, InventoryChanger_GameItems_ItemSorter_PatchPartitionTest,
    testing::Values(
        ItemType::Gloves,
        ItemType::Skin,
        ItemType::Sticker,
        ItemType::Music,
        ItemType::Collectible,
        ItemType::NameTag,
        ItemType::Agent,
        ItemType::Case,
        ItemType::CaseKey,
        ItemType::OperationPass,
        ItemType::StatTrakSwapTool,
        ItemType::ViewerPass,
        ItemType::ServiceMedal,
        ItemType::SouvenirToken,
        ItemType::TournamentCoin,
        ItemType::VanillaKnife,
        ItemType::VanillaSkin
    )
);

class InventoryChanger_GameItems_ItemSorter_PartitionTest : public testing::TestWithParam<ItemType> {
protected:
    InventoryChanger_GameItems_ItemSorter_PartitionTest()
    {
        storage.addPaintKit(1234, {}, 0.0f, 1.0f);
        storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Famas, {});
        storage.addGlovesWithLastPaintKit(EconRarity::Red, WeaponId::GloveStuddedBloodhound, {});
        addToStorage(storage, GetParam(), EconRarity::Red, WeaponId::None, 0, {});
    }

    [[nodiscard]] const Item& skin() const noexcept { return storage.getItems()[0]; }
    [[nodiscard]] const Item& gloves() const noexcept { return storage.getItems()[1]; }
    [[nodiscard]] const Item& otherItem() const noexcept { return storage.getItems()[2]; }

    Storage storage;
};

TEST_P(InventoryChanger_GameItems_ItemSorter_PartitionTest, SkinComesBeforeItemsNotHavingPaintKit) {
    ASSERT_TRUE(ItemSorter{ storage }(skin(), otherItem()));
}

TEST_P(InventoryChanger_GameItems_ItemSorter_PartitionTest, GlovesComesBeforeItemsNotHavingPaintKit) {
    ASSERT_TRUE(ItemSorter{ storage }(gloves(), otherItem()));
}

TEST_P(InventoryChanger_GameItems_ItemSorter_PartitionTest, ItemsNotHavingPaintKitDoNotComeBeforeSkin) {
    ASSERT_FALSE(ItemSorter{ storage }(otherItem(), skin()));
}

TEST_P(InventoryChanger_GameItems_ItemSorter_PartitionTest, ItemsNotHavingPaintKitDoNotComeBeforeGloves) {
    ASSERT_FALSE(ItemSorter{ storage }(otherItem(), gloves()));
}

INSTANTIATE_TEST_SUITE_P(, InventoryChanger_GameItems_ItemSorter_PartitionTest,
    testing::Values(
        ItemType::Sticker,
        ItemType::Music,
        ItemType::Collectible,
        ItemType::NameTag,
        ItemType::Agent,
        ItemType::Case,
        ItemType::CaseKey,
        ItemType::OperationPass,
        ItemType::StatTrakSwapTool,
        ItemType::ViewerPass,
        ItemType::ServiceMedal,
        ItemType::SouvenirToken,
        ItemType::TournamentCoin
));

TEST(InventoryChanger_GameItems_ItemSorter_ItemsWithPaintKit_DifferentWeaponIdTest, SkinWithSmallerWeaponIdComesFirst) {
    Storage storage;
    storage.addPaintKit(1234, {}, 0.0f, 1.0f);
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Famas, {});
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Ak47, {});

    const auto& famas = storage.getItems()[0];
    const auto& ak47 = storage.getItems()[1];
    ASSERT_TRUE(ItemSorter{ storage }(ak47, famas));
}

TEST(InventoryChanger_GameItems_ItemSorter_ItemsWithPaintKit_DifferentWeaponIdTest, SkinWithGreaterWeaponIdComesSecond) {
    Storage storage;
    storage.addPaintKit(1234, {}, 0.0f, 1.0f);
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Famas, {});
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Ak47, {});

    const auto& famas = storage.getItems()[0];
    const auto& ak47 = storage.getItems()[1];
    ASSERT_FALSE(ItemSorter{ storage }(famas, ak47));
}

TEST(InventoryChanger_GameItems_ItemSorter_ItemsWithPaintKit_SameWeaponIdTest, SkinWithSmallerPaintKitComesFirst) {
    Storage storage;
    storage.addPaintKit(1234, {}, 0.0f, 1.0f);
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Famas, {});
    storage.addPaintKit(2234, {}, 0.0f, 1.0f);
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Famas, {});

    const auto& skin1 = storage.getItems()[0];
    const auto& skin2 = storage.getItems()[1];
    ASSERT_TRUE(ItemSorter{ storage }(skin1, skin2));
}

TEST(InventoryChanger_GameItems_ItemSorter_ItemsWithPaintKit_SameWeaponIdTest, SkinWithGreaterPaintKitComesSecond) {
    Storage storage;
    storage.addPaintKit(1234, {}, 0.0f, 1.0f);
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Famas, {});
    storage.addPaintKit(2234, {}, 0.0f, 1.0f);
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Famas, {});

    const auto& skin1 = storage.getItems()[0];
    const auto& skin2 = storage.getItems()[1];
    ASSERT_FALSE(ItemSorter{ storage }(skin2, skin1));
}

TEST(InventoryChanger_GameItems_ItemSorter_ItemsWithPaintKit_SameWeaponIdTest, ReturnsFalseForSkinsWithSamePaintKit) {
    Storage storage;
    storage.addPaintKit(1234, {}, 0.0f, 1.0f);
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Famas, {});
    storage.addSkinWithLastPaintKit(EconRarity::Red, WeaponId::Famas, {});

    const auto& skin1 = storage.getItems()[0];
    const auto& skin2 = storage.getItems()[1];
    ASSERT_FALSE(ItemSorter{ storage }(skin1, skin2));
}

TEST(InventoryChanger_GameItems_ItemSorter_PatchTest, PatchWithSmallerIdComesFirst) {
    Storage storage;
    storage.addPatch(570, {}, EconRarity::Blue, {});
    storage.addPatch(1024, {}, EconRarity::Blue, {});
    ASSERT_TRUE(ItemSorter{ storage }(storage.getItems()[0], storage.getItems()[1]));
}

TEST(InventoryChanger_GameItems_ItemSorter_PatchTest, PatchWithGreaterIdComesSecond) {
    Storage storage;
    storage.addPatch(570, {}, EconRarity::Blue, {});
    storage.addPatch(1024, {}, EconRarity::Blue, {});
    ASSERT_FALSE(ItemSorter{ storage }(storage.getItems()[1], storage.getItems()[0]));
}

TEST(InventoryChanger_GameItems_ItemSorter_PatchTest, ReturnsFalseForEqualPatchId) {
    Storage storage;
    storage.addPatch(1024, {}, EconRarity::Blue, {});
    storage.addPatch(1024, {}, EconRarity::Blue, {});
    ASSERT_FALSE(ItemSorter{ storage }(storage.getItems()[0], storage.getItems()[1]));
}

TEST(InventoryChanger_GameItems_ItemSorter_GraffitiTest, GraffitiWithSmallerIdComesFirst) {
    Storage storage;
    storage.addGraffiti(570, {}, EconRarity::Blue, {});
    storage.addGraffiti(1024, {}, EconRarity::Blue, {});
    ASSERT_TRUE(ItemSorter{ storage }(storage.getItems()[0], storage.getItems()[1]));
}

TEST(InventoryChanger_GameItems_ItemSorter_GraffitiTest, GraffitiWithGreaterIdComesSecond) {
    Storage storage;
    storage.addGraffiti(570, {}, EconRarity::Blue, {});
    storage.addGraffiti(1024, {}, EconRarity::Blue, {});
    ASSERT_FALSE(ItemSorter{ storage }(storage.getItems()[1], storage.getItems()[0]));
}

TEST(InventoryChanger_GameItems_ItemSorter_GraffitiTest, ReturnsFalseForEqualGraffitiId) {
    Storage storage;
    storage.addGraffiti(1024, {}, EconRarity::Blue, {});
    storage.addGraffiti(1024, {}, EconRarity::Blue, {});
    ASSERT_FALSE(ItemSorter{ storage }(storage.getItems()[0], storage.getItems()[1]));
}

}
}
