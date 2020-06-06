/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameExtraData.h"
#include "skse64/GameFormComponents.h"

namespace doticu_npcp {

    typedef TESContainer            BContainer_t;
    typedef TESContainer::Entry **  BEntries_t;
    typedef TESContainer::Entry     BEntry_t;

    // XContainer -> XEntries -> XEntry -> XLists -> XList -> various XData_t's
    typedef ExtraContainerChanges   XContainer_t;
    typedef EntryDataList           XEntries_t;
    typedef InventoryEntryData      XEntry_t;
    typedef ExtendDataList          XLists_t;
    typedef BaseExtraList           XList_t;
    typedef BSExtraData             XData_t;

    typedef BGSBaseAlias            Member_t;
    typedef TESQuest                Followers_t;
    typedef BGSBaseAlias            Follower_t;

}
