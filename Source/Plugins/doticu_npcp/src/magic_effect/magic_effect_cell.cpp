/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"

#include "magic_effect/magic_effect_cell.h"
#include "party/party_player.h"
#include "party/party_movee.h"

namespace doticu_npcp { namespace Papyrus { namespace Magic_Effect {

    String_t Cell_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_effect_cell");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Cell_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }
    
    void Cell_t::On_Effect_Start(Actor_t* target, Actor_t* caster)
    {
        Actor_t* player_actor = Consts::Player_Actor();
        Reference_t* cell_marker = Consts::Cell_Marker();
        doticu_npcp::Cell_t* new_cell = player_actor->parentCell;
        doticu_npcp::Cell_t* old_cell = cell_marker->parentCell;

        Object_Ref::Move_To_Orbit(cell_marker, player_actor, 0.0f, 180.0f);

        Party::Player_t::Self()->On_Cell_Change(new_cell, old_cell);
        Party::Movee_t::Self()->On_Cell_Change(new_cell, old_cell);
    }

    void Cell_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Cell_t,                \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("OnEffectStart", 2, void, On_Effect_Start, Actor_t*, Actor_t*);
        
        #undef METHOD
    }

}}}
