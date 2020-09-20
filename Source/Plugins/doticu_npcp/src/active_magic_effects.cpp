/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "active_magic_effects.h"
#include "actor2.h"
#include "consts.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_player.h"
#include "party/party_followers.h"
#include "party/party_follower.h"

namespace doticu_npcp { namespace Papyrus { namespace Active_Magic_Effects {

    Magic_Effect_t* Magic_Effect(Active_Magic_Effect_t* active_magic_effect)
    {
        if (active_magic_effect) {
            if (active_magic_effect->effect) {
                return active_magic_effect->effect->mgef;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    void On_Effect_Start(Active_Magic_Effect_t* active_magic_effect, Actor_t* target, Actor_t* caster)
    {
        Magic_Effect_t* magic_effect = Magic_Effect(active_magic_effect);
        if (magic_effect == Consts::Retreat_Magic_Effect()) {
            Actor2::Pacify(target);
        }
    }

}}}

namespace doticu_npcp { namespace Papyrus { namespace Active_Magic_Effects { namespace Exports {

    void On_Effect_Start(Selfless_t*, Active_Magic_Effect_t* active_magic_effect, Actor_t* target, Actor_t* caster)
    {
        return Active_Magic_Effects::On_Effect_Start(active_magic_effect, target, caster);
    }

    Bool_t Register(VMClassRegistry* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)      \
        M                                                                   \
            ADD_CLASS_METHOD("doticu_npcp_active_magic_effect", Selfless_t, \
                             STR_FUNC_, ARG_NUM_,                           \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);       \
        W

        ADD_GLOBAL("On_Effect_Start", 3, void, On_Effect_Start, Active_Magic_Effect_t*, Actor_t*, Actor_t*);

        #undef ADD_GLOBAL

        return true;
    }

}}}}
