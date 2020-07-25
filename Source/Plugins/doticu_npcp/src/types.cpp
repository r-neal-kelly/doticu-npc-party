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

}
