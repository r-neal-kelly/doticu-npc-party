/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace XData {

    class Interaction : public BSHandleRefObject
    {
    public:
        Interaction();
        virtual ~Interaction(); // 00

        UInt32 interactee_handle; // 10
        UInt32 interactor_handle; // 14
        bool is_synced; // 18
        UInt8 pad_19; // 19
        UInt16 pad_1A; // 1A
        UInt32 pad_1C; // 1C
    };
    STATIC_ASSERT(sizeof(Interaction) == 0x20);

    class XInteraction : public BSExtraData
    {
    public:
        XInteraction();
        virtual ~XInteraction(); // 00

        Interaction* interaction;
    };
    STATIC_ASSERT(sizeof(XInteraction) == 0x18);

    void Create_Interaction(TESObjectREFR* interactee, TESObjectREFR* interactor, bool is_synced);
    void Destroy_Interaction(TESObjectREFR* obj);

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
