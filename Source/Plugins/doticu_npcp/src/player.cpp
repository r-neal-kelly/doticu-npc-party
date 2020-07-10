/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "cell.h"
#include "player.h"
#include "party.h"

namespace doticu_npcp { namespace Player {

    bool Is_Party_In_Combat(Player_t *player) {
        Actor_t* player_actor = *g_thePlayer;
        Party::Followers_t* followers = Party::Followers_t::Self();
        return (player_actor && player_actor->IsInCombat()) || (followers && followers->Are_In_Combat());
    }

    bool Is_In_Interior_Cell()
    {
        Actor_t* player_actor = *g_thePlayer;
        if (player_actor) {
            TESObjectCELL* player_cell = player_actor->parentCell;
            return player_cell && Cell::Is_Interior(player_cell);
        } else {
            return false;
        }
    }

    bool Is_In_Exterior_Cell()
    {
        Actor_t* player_actor = *g_thePlayer;
        if (player_actor) {
            TESObjectCELL* player_cell = player_actor->parentCell;
            return player_cell && Cell::Is_Exterior(player_cell);
        } else {
            return false;
        }
    }

    bool Is_On_Mount()
    {
        Actor_t* player_actor = *g_thePlayer;
        return player_actor && Actor2::Is_On_Mount(player_actor);
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
