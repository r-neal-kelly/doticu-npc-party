/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameExtraData.h"

#include "utils.h"
#include "types.h"

namespace doticu_npcp { namespace XData {

    ExtraCount *Create_Count(UInt32 count);
    ExtraOwnership *Create_Ownership(TESForm *owner);
    ExtraReferenceHandle *Create_Reference_Handle(TESObjectREFR *obj);
    void Destroy(XData_t *xdata);

    ExtraCount *Copy_Count(ExtraCount *xdata, BSReadWriteLock *xlist_lock);
    ExtraHealth *Copy_Health(ExtraHealth *xdata, BSReadWriteLock *xlist_lock);
    ExtraEnchantment *Copy_Enchantment(ExtraEnchantment *xdata, BSReadWriteLock *xlist_lock);
    ExtraCharge *Copy_Charge(ExtraCharge *xdata, BSReadWriteLock *xlist_lock);
    ExtraTextDisplayData *Copy_Text_Display(ExtraTextDisplayData *xdata, BSReadWriteLock *xlist_lock);

    bool Is_Same_Health(ExtraHealth *xdata_a, ExtraHealth *xdata_b, BSReadWriteLock *xlist_lock_a, BSReadWriteLock *xlist_lock_b);
    bool Is_Same_Enchantment(ExtraEnchantment *xdata_a, ExtraEnchantment *xdata_b, BSReadWriteLock *xlist_lock_a, BSReadWriteLock *xlist_lock_b);
    bool Is_Same_Charge(ExtraCharge *xdata_a, ExtraCharge *xdata_b, BSReadWriteLock *xlist_lock_a, BSReadWriteLock *xlist_lock_b);

    const char *Get_Type_String(BSExtraData *xdata);

    void Log(XData_t *xdata);
}}
