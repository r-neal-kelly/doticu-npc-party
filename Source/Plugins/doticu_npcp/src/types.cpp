/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "types.h"
#include "utils.h"
#include "string2.h"
#include "offsets.h"

namespace doticu_npcp {

    /* String_t */

    /*String_t::String_t()
    {
        String_t("");
    }

    String_t::String_t(const char* str)
    {
        static auto create = reinterpret_cast
            <void(*)(String_t*, const char* str)>
            (RelocationManager::s_baseAddr + Offsets::String::CREATE);
        create(this, str);
    }

    String_t::String_t(std::string str)
    {
        String_t(str.c_str());
    }

    void String_t::Destroy()
    {
        static auto destroy = reinterpret_cast
            <void(*)(String_t*)>
            (RelocationManager::s_baseAddr + Offsets::String::DESTROY);
        destroy(this);
    }

    Bool_t String_t::operator==(const String_t& lhs) const
    {
        return data == lhs.data;
    }

    Bool_t String_t::operator<(const String_t& lhs) const
    {
        return data < lhs.data;
    }

    String_t::operator const char* () const
    {
        return data ? data : "";
    }

    String_t::operator BSFixedString ()
    {
        return *reinterpret_cast<BSFixedString*>(this);
    }

    String_t::operator BSFixedString () const
    {
        return *reinterpret_cast<const BSFixedString*>(this);
    }*/

    /* Actor_Base_Data_t */

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

    Bool_t Actor_State_t::Is_Moving()
    {
        return
            state.moving_forward ||
            state.moving_left ||
            state.moving_right ||
            state.moving_back;
    }

    void Actor_State_t::Stop_Movement()
    {
        state.moving_back = false;
        state.moving_forward = false;
        state.moving_right = false;
        state.moving_left = false;
    }

    Actor_State_t::Weapon_e Actor_State_t::Weapon_State()
    {
        return static_cast<Weapon_e>(
            static_cast<UInt8>(state.weapon_0) << 0 |
            static_cast<UInt8>(state.weapon_1) << 1 |
            static_cast<UInt8>(state.weapon_2) << 2
        );
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

    BGSEquipSlot* Actor_Equipper_t::Right_Hand_Slot()
    {
        static auto self = reinterpret_cast
            <BGSEquipSlot**>
            (RelocationManager::s_baseAddr + Offsets::Actor_Equipper::RIGHT_HAND_SLOT);
        NPCP_ASSERT(self);
        return *self;
    }

    BGSEquipSlot* Actor_Equipper_t::Left_Hand_Slot()
    {
        static auto self = reinterpret_cast
            <BGSEquipSlot**>
            (RelocationManager::s_baseAddr + Offsets::Actor_Equipper::LEFT_HAND_SLOT);
        NPCP_ASSERT(self);
        return *self;
    }

    BGSEquipSlot* Actor_Equipper_t::Either_Hand_Slot()
    {
        static auto self = reinterpret_cast
            <BGSEquipSlot**>
            (RelocationManager::s_baseAddr + Offsets::Actor_Equipper::EITHER_HAND_SLOT);
        NPCP_ASSERT(self);
        return *self;
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

    const char* Relationship_t::Rank_To_String(Relationship_t::Rank_e rank)
    {
        switch (rank) {
            case (Rank_e::LOVER): return "Lover";
            case (Rank_e::ALLY): return "Ally";
            case (Rank_e::CONFIDANT): return "Confidant";
            case (Rank_e::FRIEND): return "Friend";
            case (Rank_e::ACQUAINTANCE): return "Acquaintance";
            case (Rank_e::RIVAL): return "Rival";
            case (Rank_e::FOE): return "Foe";
            case (Rank_e::ENEMY): return "Enemy";
            case (Rank_e::ARCHNEMESIS): return "Archnemesis";
            default: return "Acquaintance";
        };
    }

    Int_t Relationship_t::To_Papyrus_Rank(Rank_e rank)
    {
        switch (rank) {
            case (Rank_e::LOVER):           return  4;
            case (Rank_e::ALLY):            return  3;
            case (Rank_e::CONFIDANT):       return  2;
            case (Rank_e::FRIEND):          return  1;
            case (Rank_e::ACQUAINTANCE):    return  0;
            case (Rank_e::RIVAL):           return -1;
            case (Rank_e::FOE):             return -2;
            case (Rank_e::ENEMY):           return -3;
            case (Rank_e::ARCHNEMESIS):     return -4;
            default:                        return  0;
        };
    }

    Relationship_t::Rank_e Relationship_t::From_Papyrus_Rank(Int_t rank)
    {
        switch (rank) {
            case ( 4):  return Rank_e::LOVER;
            case ( 3):  return Rank_e::ALLY;
            case ( 2):  return Rank_e::CONFIDANT;
            case ( 1):  return Rank_e::FRIEND;
            case ( 0):  return Rank_e::ACQUAINTANCE;
            case (-1):  return Rank_e::RIVAL;
            case (-2):  return Rank_e::FOE;
            case (-3):  return Rank_e::ENEMY;
            case (-4):  return Rank_e::ARCHNEMESIS;
            default:    return Rank_e::ACQUAINTANCE;
        };
    }

    Relationships_t* Relationships_t::Self()
    {
        static auto self = reinterpret_cast
            <Relationships_t**>
            (RelocationManager::s_baseAddr + Offsets::Relationships::SELF);
        NPCP_ASSERT(self);
        return *self;
    }

    Relationship_t::Rank_e Relationships_t::Relationship_Rank(Form_t* form_1, Form_t* form_2)
    {
        static auto get_relationship_rank = reinterpret_cast
            <Relationship_t::Rank_e(*)(Form_t*, Form_t*)>
            (RelocationManager::s_baseAddr + Offsets::Relationships::GET_RELATIONSHIP_RANK);
        return get_relationship_rank(form_1, form_2);
    }

    void Relationships_t::Relationship_Rank(Form_t* form_1, Form_t* form_2, Relationship_t::Rank_e rank)
    {
        static auto set_relationship_rank = reinterpret_cast
            <void(*)(Form_t*, Form_t*, Relationship_t::Rank_e)>
            (RelocationManager::s_baseAddr + Offsets::Relationships::SET_RELATIONSHIP_RANK);
        set_relationship_rank(form_1, form_2, rank);
    }

    Dialogue_Info_t::Dialogue_Info_t(Quest_t* quest, Topic_t* topic, Topic_Info_t* topic_info, Actor_t* speaker)
    {
        static auto ctor = reinterpret_cast
            <Dialogue_Info_t * (*)(Dialogue_Info_t*, Quest_t*, Topic_t*, Topic_Info_t*, Actor_t*)>
            (RelocationManager::s_baseAddr + Offsets::Dialogue_Info::CTOR);
        ctor(this, quest, topic, topic_info, speaker);
    }

    Package_Value_t::Type_e Package_Value_t::Type()
    {
        uintptr_t vtbl = *(uintptr_t*)this - RelocationManager::s_baseAddr;
        if (vtbl == Offsets::Package::BOOL_VALUE) {
            return Type_e::BOOL;
        } else if (vtbl == Offsets::Package::INT_VALUE) {
            return Type_e::INT;
        } else if (vtbl == Offsets::Package::FLOAT_VALUE) {
            return Type_e::FLOAT;
        } else if (vtbl == Offsets::Package::LOCATION_VALUE) {
            return Type_e::LOCATION;
        } else if (vtbl == Offsets::Package::SINGLE_REFERENCE_VALUE) {
            return Type_e::SINGLE_REFERENCE;
        } else {
            return Type_e::NONE;
        }
    }

    Bool_t Package_t::Is_Flagged(General_Flag_e flag)
    {
        return (flags & static_cast<UInt32>(flag)) != 0;
    }

    Bool_t Package_t::Is_Flagged(Interrupt_Flag_e flag)
    {
        return (interrupt_flags & static_cast<UInt16>(flag)) != 0;
    }

    Bool_t Package_t::Flag(General_Flag_e flag, Bool_t value)
    {
        if (value) {
            if (!Is_Flagged(flag)) {
                flags |= static_cast<UInt32>(flag);
                return true;
            } else {
                return false;
            }
        } else {
            if (Is_Flagged(flag)) {
                flags &= ~static_cast<UInt32>(flag);
                return true;
            } else {
                return false;
            }
        }
    }

    Bool_t Package_t::Flag(Interrupt_Flag_e flag, Bool_t value)
    {
        if (value) {
            if (!Is_Flagged(flag)) {
                interrupt_flags |= static_cast<UInt16>(flag);
                return true;
            } else {
                return false;
            }
        } else {
            if (Is_Flagged(flag)) {
                interrupt_flags &= ~static_cast<UInt16>(flag);
                return true;
            } else {
                return false;
            }
        }
    }

    Form_Factory_i* Form_Factory_i::Form_Factory(Form_Type_t form_type)
    {
        struct Form_Factories_t {
            Form_Factory_i* factories[138];
        };
        static auto factories = reinterpret_cast
            <Form_Factories_t*>
            (RelocationManager::s_baseAddr + Offsets::Form_Factory::FACTORIES);
        static Bool_t is_created = *reinterpret_cast
            <Bool_t*>
            (RelocationManager::s_baseAddr + Offsets::Form_Factory::IS_CREATED);

        NPCP_ASSERT(is_created);
        return factories->factories[form_type];
    }

    void Script_t::Command(const char* command)
    {
        size_t length = String2::Length(command) + 1;
        if (length > 0) {
            if (text) {
                free(text);
            }
            text = static_cast<char*>(malloc(length));
            std::memcpy(text, command, length);
        }
    }

    void Script_t::Execute(Reference_t* reference, Script_t::Compiler_e compiler_enum)
    {
        class Compiler_t {
        public:
        };
        static auto execute = reinterpret_cast
            <void(*)(Script_t*, Compiler_t*, Compiler_e, Reference_t*)>
            (RelocationManager::s_baseAddr + Offsets::Script::EXECUTE);
        Compiler_t compiler;
        execute(this, &compiler, compiler_enum, reference);
    }

}
