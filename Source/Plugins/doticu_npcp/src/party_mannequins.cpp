/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_player.h"
#include "party/party_members.h"
#include "party/party_member.h"
#include "party/party_mannequins.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    String_t Mannequins_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mannequins");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Mannequins_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Mannequins_t* Mannequins_t::Self()
    {
        return static_cast<Mannequins_t*>(Consts::Funcs_Quest());
    }

    Object_t* Mannequins_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Mannequins_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Mannequins_t::Slots_Array_Variable() { DEFINE_VARIABLE("p_arr_mannequins"); }
    Variable_t* Mannequins_t::Cell_Names_Array_Variable() { DEFINE_VARIABLE("p_arr_cell_names"); }
    Variable_t* Mannequins_t::Go_Back_Marker_Variable() { DEFINE_VARIABLE("p_marker_teleport"); }

    Array_t* Mannequins_t::Slots_Array()
    {
        Array_t* slots_array = Slots_Array_Variable()->Array();
        if (!slots_array) {
            Initialize();
            slots_array = Slots_Array_Variable()->Array();
        }
        NPCP_ASSERT(slots_array);
        return slots_array;
    }

    Array_t* Mannequins_t::Cell_Names_Array()
    {
        Array_t* cell_names_array = Cell_Names_Array_Variable()->Array();
        if (!cell_names_array) {
            Initialize();
            cell_names_array = Cell_Names_Array_Variable()->Array();
        }
        NPCP_ASSERT(cell_names_array);
        return cell_names_array;
    }

    Reference_t* Mannequins_t::Go_Back_Marker()
    {
        return Go_Back_Marker_Variable()->Reference();
    }

    void Mannequins_t::Go_Back_Marker(Reference_t* marker)
    {
        Go_Back_Marker_Variable()->Pack(marker);
    }

    void Mannequins_t::Initialize()
    {
        Vector_t<Member_t*> slots;
        slots.reserve(SLOTS);
        for (size_t idx = 0, count = SLOTS; idx < count; idx += 1) {
            slots.push_back(nullptr);
        }
        Slots_Array_Variable()->Pack(slots);

        Vector_t<String_t> cell_names;
        cell_names.reserve(CELLS);
        for (size_t idx = 0, count = CELLS; idx < count; idx += 1) {
            cell_names.push_back("");
        }
        Cell_Names_Array_Variable()->Pack(cell_names);

        Go_Back_Marker_Variable()->None(Object_Ref::Class_Info());
    }

    void Mannequins_t::Uninitialize()
    {
        Go_Back_Marker_Variable()->None(Object_Ref::Class_Info());

        Vector_t<String_t> cell_names;
        Cell_Names_Array_Variable()->Pack(cell_names);

        Vector_t<Member_t*> slots;
        Slots_Array_Variable()->Pack(slots);
    }

    void Mannequins_t::Reinitialize()
    {
        Uninitialize();
        Initialize();
    }

    Bool_t Mannequins_t::Has_Expoee(Int_t expoee_id)
    {
        Array_t* slots_array = Slots_Array();
        NPCP_ASSERT(expoee_id > -1 && expoee_id < slots_array->count);
        return slots_array->Point(expoee_id)->Has_Object();
    }

    Bool_t Mannequins_t::Hasnt_Expoee(Int_t expoee_id)
    {
        Array_t* slots_array = Slots_Array();
        NPCP_ASSERT(expoee_id > -1 && expoee_id < slots_array->count);
        return !slots_array->Point(expoee_id)->Has_Object();
    }

    Bool_t Mannequins_t::Is_Member_In_Expo(Member_t* member)
    {
        return member && member->Is_Filled() && member->Is_In_Location(Consts::Expo_Location());
    }

    Bool_t Mannequins_t::Is_Player_In_Expo()
    {
        return Player_t::Self()->Location() == Consts::Expo_Location();
    }

    Int_t Mannequins_t::Max_Expoees()
    {
        return SLOTS;
    }

    Int_t Mannequins_t::Count_Expoees()
    {
        Int_t expoee_count = 0;
        Array_t* slots_array = Slots_Array();
        for (size_t idx = 0, count = slots_array->count; idx < count; idx += 1) {
            if (slots_array->Point(idx)->Has_Object()) {
                expoee_count += 1;
            }
        }
        return expoee_count;
    }

    void Mannequins_t::Expo(Int_t expoee_id, Reference_t* marker, void (*callback)(Int_t code, const char* name))
    {
        using User_Callback = void (*)(Int_t code, const char* name);

        Array_t* slots_array = Slots_Array();
        if (expoee_id > -1 && expoee_id < slots_array->count) {
            if (marker) {
                Member_t* expoee = static_cast<Member_t*>(slots_array->Point(expoee_id)->Alias());
                if (!expoee) {
                    class Find_Callback : public Virtual_Callback_t {
                    public:
                        Mannequins_t* mannequins;
                        Int_t expoee_id;
                        Reference_t* marker;
                        User_Callback callback;
                        Find_Callback(Mannequins_t* mannequins,
                                      Int_t expoee_id,
                                      Reference_t* marker,
                                      User_Callback callback) :
                            mannequins(mannequins),
                            expoee_id(expoee_id),
                            marker(marker),
                            callback(callback)
                        {
                        }
                        void operator()(Variable_t* result)
                        {
                            Actor_t* actor = result ? result->Actor() : nullptr;
                            if (actor && actor != Player_t::Self()->Actor()) {
                                Member_t* member = Members_t::Self()->From_Actor(actor);
                                if (member) {
                                    mannequins->Slots_Array()->Point(expoee_id)->Pack(member);
                                    member->Mannequinize(marker);
                                    return callback(CODES::SUCCESS, member->Name());
                                } else {
                                    return callback(CODES::MEMBER, Actor2::Get_Name(actor));
                                }
                            } else {
                                return callback(CODES::ACTOR, "");
                            }
                        }
                    };
                    Virtual_Callback_i* find_callback = new Find_Callback(this, expoee_id, marker, callback);
                    Object_Ref::Find_Closest_Actor_From(marker, 48.0f, &find_callback);
                } else {
                    return callback(CODES::HAS, "");
                }
            } else {
                return callback(CODES::MARKER, "");
            }
        } else {
            return callback(CODES::HASNT, "");
        }
    }

    void Mannequins_t::Unexpo(Int_t expoee_id, void (*callback)(Int_t code, const char* name))
    {
        using User_Callback = void (*)(Int_t code, const char* name);

        Array_t* slots_array = Slots_Array();
        if (expoee_id > -1 && expoee_id < slots_array->count) {
            Variable_t* slot = slots_array->Point(expoee_id);
            Member_t* expoee = static_cast<Member_t*>(slot->Alias());
            if (expoee) {
                slot->None(Member_t::Class_Info());
                expoee->Unmannequinize();
                return callback(CODES::SUCCESS, expoee->Name());
            } else {
                return callback(CODES::MEMBER, "");
            }
        } else {
            return callback(CODES::HASNT, "");
        }
    }

    Bool_t Mannequins_t::Try_To_Remove(Member_t* member)
    {
        Array_t* slots_array = Slots_Array();

        Int_t expoee_id = -1;
        if (member) {
            for (size_t idx = 0, count = slots_array->count; idx < count; idx += 1) {
                Member_t* expoee = static_cast<Member_t*>(slots_array->Point(idx)->Alias());
                if (expoee == member) {
                    expoee_id = idx;
                    break;
                }
            }
        }

        if (expoee_id > -1 && expoee_id < slots_array->count) {
            slots_array->Point(expoee_id)->None(Member_t::Class_Info());
            return true;
        } else {
            return false;
        }
    }

    void Mannequins_t::Enforce_Expoee(Int_t expoee_id, Reference_t* marker)
    {
        Array_t* slots_array = Slots_Array();
        NPCP_ASSERT(expoee_id > -1 && expoee_id < slots_array->count);
        NPCP_ASSERT(marker);

        Member_t* member = static_cast<Member_t*>(slots_array->Point(expoee_id)->Alias());
        if (member) {
            Object_Ref::Move_To_Orbit(member->Actor(), marker, 0.0f, 180.0f);
        }
    }

    void Mannequins_t::Normalize_Coords(Int_t& column, Int_t& row)
    {
        if (column < 1) {
            column = 1;
        } else if (column > COLUMNS) {
            column = COLUMNS;
        }
        column -= 1;

        if (row < 1) {
            row = 1;
        } else if (row > ROWS) {
            row = ROWS;
        }
        row -= 1;
    }

    Vector_t<Member_t*> Mannequins_t::Expoees(Int_t column, Int_t row)
    {
        Normalize_Coords(column, row);

        Array_t* slots_array = Slots_Array();
        size_t begin = (column * SLOTS_PER_COLUMN) + (row * SLOTS_PER_CELL);
        size_t end = begin + SLOTS_PER_CELL;
        if (end > slots_array->count) {
            end = slots_array->count;
        }

        Vector_t<Member_t*> expoees;
        expoees.reserve(SLOTS_PER_CELL);
        for (; begin < end; begin += 1) {
            expoees.push_back(static_cast<Member_t*>(slots_array->Point(begin)->Alias()));
        }

        return expoees;
    }

    String_t Mannequins_t::Cell_Name(Int_t column, Int_t row)
    {
        Normalize_Coords(column, row);
        NPCP_ASSERT(column * ROWS + row < SLOTS);
        return Cell_Names_Array()->Point(column * ROWS + row)->String();
    }

    void Mannequins_t::Cell_Name(Int_t column, Int_t row, String_t name)
    {
        Normalize_Coords(column, row);
        NPCP_ASSERT(column * ROWS + row < SLOTS);
        Cell_Names_Array()->Point(column * ROWS + row)->String(name);
    }

    void Mannequins_t::Move_Player_To_Cell(Int_t column, Int_t row)
    {
        Normalize_Coords(column, row);
        Try_To_Set_Go_Back_Marker();

        Reference_t* cell_marker = static_cast<Reference_t*>
            (Consts::Expo_Cell_Markers_Formlist()->forms.entries[column * ROWS + row]);
        Object_Ref::Move_To_Orbit(Player_t::Self()->Actor(), cell_marker, 0.0f, 180.0f);
    }

    void Mannequins_t::Move_Player_To_Antechamber()
    {
        Try_To_Set_Go_Back_Marker();
        Object_Ref::Move_To_Orbit(Player_t::Self()->Actor(), Consts::Expo_Antechamber_Marker(), 0.0f, 180.0f);
    }

    void Mannequins_t::Remove_Player()
    {
        if (Is_Player_In_Expo()) {
            Reference_t* go_back_marker = Go_Back_Marker();
            if (go_back_marker) {
                Object_Ref::Move_To_Orbit(Player_t::Self()->Actor(), go_back_marker, 0.0f, 180.0f);
                Try_To_Unset_Go_Back_Marker();
            } else {
                Object_Ref::Move_To_Orbit(Player_t::Self()->Actor(), Consts::Safe_Go_Back_Marker(), 0.0f, 180.0f);
            }
        }
    }

    void Mannequins_t::Update_Go_Back_Marker(Member_t* member)
    {
        if (Is_Member_In_Expo(member)) {
            Try_To_Set_Go_Back_Marker();
        }
    }

    void Mannequins_t::Try_To_Set_Go_Back_Marker()
    {
        if (!Is_Player_In_Expo()) {
            Try_To_Unset_Go_Back_Marker();
            Go_Back_Marker_Variable()->Pack(
                Object_Ref::Place_At_Me(Player_t::Self()->Actor(), Consts::X_Marker_Static(), 1, true, false)
            );
        }
    }

    void Mannequins_t::Try_To_Unset_Go_Back_Marker()
    {
        Variable_t* go_back_marker_variable = Go_Back_Marker_Variable();
        Reference_t* go_back_marker = go_back_marker_variable->Reference();
        if (go_back_marker) {
            Object_Ref::Delete_Safe(go_back_marker);
            go_back_marker_variable->None(Object_Ref::Class_Info());
        }
    }

    void Mannequins_t::On_Load_Mod()
    {
        Array_t* slots_array = Slots_Array();
        for (size_t idx = 0, count = slots_array->count; idx < count; idx += 1) {
            Variable_t* slot = slots_array->Point(idx);
            Member_t* expoee = static_cast<Member_t*>(slot->Alias());
            if (expoee) {
                if (expoee->Is_Unfilled() || expoee->Isnt_Mannequin()) { // eventually Isnt_Expoee, once we add loose mannequins
                    slot->None(Member_t::Class_Info());
                }
            }
        }

        Object_Ref::Rename(Consts::Expo_Exit_Door(), "Exit Expo");
    }

    void Mannequins_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Mannequins_t,          \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
