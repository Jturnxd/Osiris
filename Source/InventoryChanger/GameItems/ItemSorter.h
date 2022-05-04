#pragma once

#include "Item.h"
#include "Storage.h"

namespace game_items
{

struct ItemSorter {
    explicit ItemSorter(const Storage& storage) : storage{ storage } {}

    [[nodiscard]] bool operator()(const Item& a, const Item& b) const
    {
        if (a.isGraffiti() != b.isGraffiti())
            return a.isGraffiti();

        if (a.isGraffiti() && b.isGraffiti())
            return storage.getGraffitiKit(a).id < storage.getGraffitiKit(b).id;

        if (a.isPatch() != b.isPatch())
            return a.isPatch();

        if (a.isPatch() && b.isPatch())
            return storage.getPatch(a).id < storage.getPatch(b).id;

        const auto aHasPaintKit = storage.hasPaintKit(a);
        const auto bHasPaintKit = storage.hasPaintKit(b);
  
        if (aHasPaintKit != bHasPaintKit)
            return aHasPaintKit;
      
        if (aHasPaintKit && bHasPaintKit)
            return compareItemsWithPaintKit(a, b);

        return a.getWeaponID() < b.getWeaponID();
    }

private:
    [[nodiscard]] bool compareItemsWithPaintKit(const Item& a, const Item& b) const
    {
        assert(storage.hasPaintKit(a) && storage.hasPaintKit(b));

        if (a.getWeaponID() != b.getWeaponID())
            return a.getWeaponID() < b.getWeaponID();
        return storage.getPaintKit(a).id < storage.getPaintKit(b).id;
    }

    const Storage& storage;
};

}
