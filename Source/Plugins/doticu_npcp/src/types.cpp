/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "types.h"
#include "utils.h"
#include "string2.h"
#include "offsets.h"

namespace doticu_npcp {

    Bool_t Actor_Base_Data_t::Is_Unique()
    {
        return Utils::Is_Bit_On(flags, IS_UNIQUE);
    }

    Bool_t Actor_Base_Data_t::Is_Ghost()
    {
        return Utils::Is_Bit_On(flags, IS_GHOST);
    }

    Bool_t Actor_Base_Data_t::Is_Protected()
    {
        return Utils::Is_Bit_On(flags, IS_PROTECTED);
    }

    Bool_t Actor_Base_Data_t::Is_Essential()
    {
        return Utils::Is_Bit_On(flags, IS_ESSENTIAL);
    }

    void Actor_Base_Data_t::Protect()
    {
        flags = Utils::Bit_On(flags, IS_PROTECTED);
    }

    void Actor_Base_Data_t::Unprotect()
    {
        flags = Utils::Bit_Off(flags, IS_PROTECTED);
    }

    void Actor_Base_Data_t::Essentialize()
    {
        flags = Utils::Bit_On(flags, IS_ESSENTIAL);
    }

    void Actor_Base_Data_t::Unessentialize()
    {
        flags = Utils::Bit_Off(flags, IS_ESSENTIAL);
    }

    void ExtraTextDisplay::Force_Rename(String_t new_name)
    {
        name = new_name;
        message = nullptr;
        owner = nullptr;
        flag = ExtraTextDisplay::CUSTOM;
        extra_health = 1.0f;
        custom_length = String2::Length(new_name);
    }

    Container_Changes_t* Container_Changes_t::Create(Reference_t* owner)
    {
        static auto ctor = reinterpret_cast<Container_Changes_t* (*)(Container_Changes_t*, Reference_t*)>
            (RelocationManager::s_baseAddr + Offsets::Container_Changes::CTOR);

        Container_Changes_t self;
        Container_Changes_t* changes = ctor(&self, owner);
        NPCP_ASSERT(changes != nullptr);

        _MESSAGE("entries: %p", changes->entries);
        _MESSAGE("owner: %p", changes->owner);
        _MESSAGE("total_weight: %f", changes->total_weight);
        _MESSAGE("armor_weight: %f", changes->armor_weight);
        _MESSAGE("has_changed: %i", changes->has_changed);
        _MESSAGE("pad_19: %u", changes->pad_19);
        _MESSAGE("pad_1A: %u", changes->pad_1A);
        _MESSAGE("pad_1C: %u", changes->pad_1C);

        return changes;
    }

    void Container_Changes_t::Destroy(Container_Changes_t* changes)
    {
        static auto dtor = reinterpret_cast<void(*)(Container_Changes_t*)>
            (RelocationManager::s_baseAddr + Offsets::Container_Changes::DTOR);

        if (changes) {
            dtor(changes);
        }
    }

    Extra_Container_Changes_t* Extra_Container_Changes_t::Create(Reference_t* owner)
    {
        Extra_Container_Changes_t* xchanges = static_cast<Extra_Container_Changes_t*>(XData_t::Create(
            sizeof(Extra_Container_Changes_t),
            RelocationManager::s_baseAddr + Offsets::Extra::CONTAINER_CHANGES_V_TABLE
        ));
        NPCP_ASSERT(xchanges != nullptr);

        xchanges->changes = Container_Changes_t::Create(owner);

        return xchanges;
    }

    void Extra_Container_Changes_t::Destroy(Extra_Container_Changes_t* xchanges)
    {
        if (xchanges) {
            //Container_Changes_t::Destroy(xchanges->changes);
            static_cast<BSExtraData*>(xchanges)->~BSExtraData();
        }
    }

    Bool_t Quest_t2::Hash_Map_t::Has_Key(UInt16 key)
    {
        if (entries) {
            UInt32 idx = Utils::CRC32(key) & (capacity - 1);
            Entry_t* entry = entries + idx;
            if (entry && entry->chain != nullptr) {
                for (; entry != end_of_chain; entry = entry->chain) {
                    if (entry->tuple.key == key) {
                        return true;
                    }
                }
                return false;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void Actor_State_t::Stop_Movement()
    {
        state.moving_back = 0;
        state.moving_forward = 0;
        state.moving_right = 0;
        state.moving_left = 0;
    }

    Actor_Equipper_t* Actor_Equipper_t::Self()
    {
        static auto self = reinterpret_cast
            <Actor_Equipper_t**>
            (RelocationManager::s_baseAddr + Offsets::Actor_Equipper::SELF);
        NPCP_ASSERT(self);
        return *self;
    }

    void Actor_Equipper_t::Equip_Item(Actor_t* actor,
                                      Form_t* form,
                                      XList_t* xlist,
                                      UInt32 count,
                                      BGSEquipSlot* slot,
                                      Bool_t do_queue,
                                      Bool_t do_force,
                                      Bool_t do_sounds,
                                      Bool_t do_apply)
    {
        static auto equip_item = reinterpret_cast
            <void (*)(Actor_Equipper_t*, Actor_t*, Form_t*, XList_t*, UInt32, BGSEquipSlot*, Bool_t, Bool_t, Bool_t, Bool_t)>
            (RelocationManager::s_baseAddr + Offsets::Actor_Equipper::EQUIP_ITEM);
        NPCP_ASSERT(equip_item);
        return equip_item(this, actor, form, xlist, count, slot, do_queue, do_force, do_sounds, do_apply);
    }

    Bool_t Actor_Equipper_t::Unequip_Item(Actor_t* actor,
                                          Form_t* form,
                                          XList_t* xlist,
                                          UInt32 count,
                                          BGSEquipSlot* slot,
                                          Bool_t do_queue,
                                          Bool_t do_force,
                                          Bool_t do_sounds,
                                          Bool_t do_apply,
                                          BGSEquipSlot* slot_to_replace)
    {
        static auto unequip_item = reinterpret_cast
            <Bool_t (*)(Actor_Equipper_t*, Actor_t*, Form_t*, XList_t*, UInt32, BGSEquipSlot*, Bool_t, Bool_t, Bool_t, Bool_t, BGSEquipSlot*)>
            (RelocationManager::s_baseAddr + Offsets::Actor_Equipper::UNEQUIP_ITEM);
        NPCP_ASSERT(unequip_item);
        return unequip_item(this, actor, form, xlist, count, slot, do_queue, do_force, do_sounds, do_apply, slot_to_replace);
    }

    void Alias_Base_t::Log()
    {
        _MESSAGE("Log Alias Base: {");



        _MESSAGE("}");
    }

    void Alias_Reference_t::Log()
    {
        _MESSAGE("Log Alias Reference: {");



        _MESSAGE("}");
    }

    Process_Lists_t* Process_Lists_t::Self()
    {
        static auto self = reinterpret_cast
            <Process_Lists_t**>
            (RelocationManager::s_baseAddr + Offsets::Process_Lists::SELF);
        NPCP_ASSERT(self);
        return *self;
    }

    void Process_Lists_t::Stop_Combat_Alarm(Actor_t* actor, Bool_t dont_end_alarm)
    {
        static auto stop_combat_alarm = reinterpret_cast
            <void (*)(Process_Lists_t*, Actor_t*, Bool_t)>
            (RelocationManager::s_baseAddr + Offsets::Process_Lists::STOP_COMBAT_ALARM);
        if (actor) {
            stop_combat_alarm(this, actor, dont_end_alarm);
        }
    }

    Bool_t Magic_Target_t::Has_Magic_Effect(Magic_Effect_t* magic_effect)
    {
        static auto has_magic_effect = reinterpret_cast
            <Bool_t(*)(Magic_Target_t*, Magic_Effect_t*)>
            (RelocationManager::s_baseAddr + Offsets::Magic_Target::HAS_MAGIC_EFFECT);
        if (magic_effect) {
            return has_magic_effect(this, magic_effect);
        } else {
            return false;
        }
    }

}
