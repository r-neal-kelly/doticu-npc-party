/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "cell.h"
#include "object_ref.h"
#include "player.h"
#include "party.h"
#include "utils.h"

namespace doticu_npcp { namespace Player {

    Actor_t* Actor()
    {
        static Actor_t* actor = static_cast<Actor_t*>(*g_thePlayer);
        NPCP_ASSERT(actor);
        return actor;
    }

    bool Is_Party_In_Combat(Player_t *player) {
        Party::Followers_t* followers = Party::Followers_t::Self();
        return (Actor()->IsInCombat()) || (followers->Are_In_Combat());
    }

    bool Is_In_Interior_Cell()
    {
        return Object_Ref::Is_In_Interior_Cell(Actor());
    }

    bool Is_In_Exterior_Cell()
    {
        return Object_Ref::Is_In_Exterior_Cell(Actor());
    }

    bool Is_On_Mount()
    {
        return Actor2::Is_On_Mount(Actor());
    }

}}

namespace doticu_npcp { namespace Player { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction0 <Player_t, bool>(
                "Is_Party_In_Combat",
                "doticu_npcp_player",
                Player::Is_Party_In_Combat,
                registry)
        );

        return true;
    }

}}}
