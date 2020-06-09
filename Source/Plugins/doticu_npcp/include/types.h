/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameExtraData.h"
#include "skse64/GameForms.h"
#include "skse64/GameFormComponents.h"
#include "skse64/PapyrusNativeFunctions.h"

namespace doticu_npcp {

    typedef uint8_t                 u8;
    typedef uint16_t                u16;
    typedef uint32_t                u32;
    typedef uint64_t                u64;
    typedef int8_t                  s8;
    typedef int16_t                 s16;
    typedef int32_t                 s32;
    typedef int64_t                 s64;

    typedef BGSBaseAlias            Player_t;
    typedef BGSBaseAlias            Member_t;
    typedef BGSBaseAlias            Follower_t;
    typedef TESQuest                Members_t;
    typedef TESQuest                Followers_t;

    typedef TESContainer            BContainer_t;
    typedef TESContainer::Entry **  BEntries_t;
    typedef TESContainer::Entry     BEntry_t;

    typedef ExtraContainerChanges   XContainer_t;
    typedef EntryDataList           XEntries_t;
    typedef InventoryEntryData      XEntry_t;
    typedef ExtendDataList          XLists_t;
    typedef BaseExtraList           XList_t;
    typedef BSExtraData             XData_t;

    typedef StaticFunctionTag       Selfless_t;

}
