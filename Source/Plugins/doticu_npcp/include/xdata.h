/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "xentry.h"

namespace doticu_npcp { namespace Papyrus {

    class XCount_t : public BSExtraData {
    public:
        static XCount_t* Create(Int_t count);
        static void Destroy(XCount_t* xcount);
    public:
        virtual ~XCount_t();

        UInt32 count; // 10
        UInt32 pad_14; // 14
    };
    STATIC_ASSERT(sizeof(XCount_t) == 0x18);

}}

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
    ExtraFactionChanges* Create_Faction_Changes(Actor_t* actor);
    ExtraCanTalkToPlayer* Create_Can_Talk_To_Player(Bool_t can_talk);
    ExtraFlags* Create_Flags();
    ExtraGhost* Create_Ghost(Bool_t is_ghost);
    ExtraTextDisplay* Create_Text_Display(String_t name);
    ExtraOutfitItem* Create_Outfit_Item(Outfit_t* outfit);
    void Destroy(XData_t *xdata);

    ExtraCount *Copy_Count(ExtraCount *xdata);
    ExtraHealth *Copy_Health(ExtraHealth *xdata);
    ExtraEnchantment *Copy_Enchantment(ExtraEnchantment *xdata);
    ExtraCharge *Copy_Charge(ExtraCharge *xdata);
    ExtraOwnership* Copy_Ownership(ExtraOwnership* xownership);
    ExtraTextDisplayData *Copy_Text_Display(ExtraTextDisplayData *xdata);

    Bool_t Has_Same_Health(ExtraHealth* xhealth_a, ExtraHealth* xhealth_b);
    Bool_t Has_Same_Enchantment(ExtraEnchantment* xenchantment_a, ExtraEnchantment* xenchantment_b);
    Bool_t Has_Same_Charge(ExtraCharge* xcharge_a, ExtraCharge* xcharge_b);
    Bool_t Has_Same_Owner(ExtraOwnership* xownership_a, ExtraOwnership* xownership_b);

    const char *Get_Type_String(BSExtraData *xdata);

    void Log(XData_t *xdata);
}}
