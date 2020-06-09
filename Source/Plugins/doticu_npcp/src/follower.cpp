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

    bool Is_Paralyzed(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Paralyzed(member);
    }

    bool Isnt_Paralyzed(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Isnt_Paralyzed(member);
    }

    bool Is_Mannequin(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Mannequin(member);
    }

    bool Isnt_Mannequin(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Isnt_Mannequin(member);
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

    bool Exists(Follower_t *follower) {
        if (!follower) {
            return false;
        }

        return Is_Created(follower) && Get_Actor(follower);
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

    void Summon_Behind(Follower_t *follower, float distance) {
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

        Actor2::Move_To_Orbit(follower_actor, player_actor, distance, 180);
    }

    void Catch_Up(Follower_t *follower) {
        if (!Exists(follower)) {
            return;
        }

        if (Is_Immobile(follower) || Is_Paralyzed(follower) || Is_Mannequin(follower)) {
            return;
        }

        if (Object_Ref::Is_Near_Player(Get_Actor(follower))) {
            return;
        }

        Summon_Behind(follower);
    }

}}

namespace doticu_npcp { namespace Follower { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        _MESSAGE("Added Follower functions.");

        return true;
    }

}}}
