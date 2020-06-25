/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "cell.h"
#include "followers.h"
#include "player.h"

namespace doticu_npcp { namespace Player {

    bool Is_Party_In_Combat(Player_t *player) {
        Actor_t* player_actor = *g_thePlayer;
        return (player_actor && player_actor->IsInCombat()) || Followers::Are_In_Combat(Followers::Self());
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
