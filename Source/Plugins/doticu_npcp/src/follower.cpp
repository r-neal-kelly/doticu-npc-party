/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <cmath>

#include "actor2.h"
#include "follower.h"
#include "member.h"
#include "papyrus.h"
#include "utils.h"

namespace doticu_npcp { namespace Follower {

    Actor *Get_Actor(Follower_t *follower) {
        if (!follower) {
            return NULL;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_ref_actor").As_Actor();
    }

    BGSBaseAlias *Get_Member(Follower_t *follower) {
        if (!follower) {
            return NULL;
        }

        Papyrus::Handle hnd(kFormType_Alias, follower);
        return Papyrus::Value(&hnd, "p_ref_member").As_Alias();
    }

    bool Is_Created(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_is_created").As_Bool();
    }

    bool Is_Alive(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        return Actor2::Is_Alive(Get_Actor(follower));
    }

    bool Is_Dead(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        return Actor2::Is_Dead(Get_Actor(follower));
    }

    bool Is_Mobile(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Mobile(member);
    }

    bool Is_Immobile(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Immobile(member);
    }

    bool Is_Settler(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Settler(member);
    }

    bool Isnt_Settler(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Isnt_Settler(member);
    }

    bool Is_Sneak(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_is_sneak").As_Bool();
    }

    bool Isnt_Sneak(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return !Papyrus::Value(&hnd_alias, "p_is_sneak").As_Bool();
    }

    bool Is_Saddler(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_is_saddler").As_Bool();
    }

    bool Isnt_Saddler(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return !Papyrus::Value(&hnd_alias, "p_is_saddler").As_Bool();
    }

    bool Is_Retreater(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return Papyrus::Value(&hnd_alias, "p_is_retreater").As_Bool();
    }

    bool Isnt_Retreater(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, follower);
        return !Papyrus::Value(&hnd_alias, "p_is_retreater").As_Bool();
    }

    void Summon(Follower_t *follower, float distance, float angle_degree) {
        if (!follower) {
            return;
        }

        Actor *follower_actor = Get_Actor(follower);
        if (!follower_actor) {
            return;
        }

        Actor *player_actor = *g_thePlayer;
        if (!player_actor) {
            return;
        }

        Actor2::Move_To_Orbit(follower_actor, player_actor, distance, angle_degree);
    }

}}

namespace doticu_npcp { namespace Follower { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        return true;
    }

}}}
