/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "followers.h"
#include "player.h"

namespace doticu_npcp { namespace Player {

    bool Is_Party_In_Combat(Player_t *player) {
        return (*g_thePlayer)->IsInCombat() || Followers::Are_In_Combat(Followers::Get_Self());
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

        _MESSAGE("Added Player functions.");

        return true;
    }

}}}
