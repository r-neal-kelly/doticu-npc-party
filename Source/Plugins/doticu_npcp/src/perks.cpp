/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "commands.h"
#include "consts.h"
#include "funcs.h"
#include "game.h"
#include "papyrus.inl"
#include "perks.h"
#include "utils.h"

#include "party/party_player.h"
#include "party/party_members.h"

namespace doticu_npcp { namespace Papyrus { namespace Perks {

    void Execute_Perk(Perk_t* perk, Reference_t* ref, Actor_t* unknown_actor)
    {
        if (perk == Consts::Kiss_Thrall_Perk()) {
            return Execute_Kiss_Thrall(ref, unknown_actor);
        } else if (perk == Consts::Resurrect_Perk()) {
            return Execute_Resurrect(ref, unknown_actor);
        } else if (perk == Consts::Reanimate_Perk()) {
            return Execute_Reanimate(ref, unknown_actor);
        } else if (perk == Consts::Unparalyze_Perk()) {
            return Execute_Unparalyze(ref, unknown_actor);
        }
    }

    void Execute_Kiss_Thrall(Reference_t* ref, Actor_t* unknown_actor)
    {
        Actor_t* thrall = ref && ref->formType == kFormType_Character ?
            static_cast<Actor_t*>(ref) : nullptr;
        if (thrall && Party::Player_t::Self()->Is_Vampire()) {
            struct VCallback : public Virtual_Callback_t {
                Actor_t* thrall;
                VCallback(Actor_t* thrall) :
                    thrall(thrall)
                {
                }
                void operator()(Variable_t* result)
                {
                    if (Game::Is_Better_Vampires_Installed()) {
                        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(thrall);
                        value_owner->Set_Actor_Value(Actor_Value_t::VARIABLE_08, 8); // cancels limit
                        Actor2::Add_Faction(thrall, Consts::DLC1_Thrall_Faction(), 0);

                        struct Callback : public Callback_t<Party::Player_t*, Actor_t*> {
                            void operator()(Party::Player_t* player, Actor_t* thrall)
                            {
                                Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(thrall);
                                value_owner->Set_Actor_Value(Actor_Value_t::VARIABLE_08, 8); // cancels limit
                                Actor2::Remove_Faction(thrall, Consts::DLC1_Thrall_Faction());
                            }
                        };
                        Party::Player_t::Self()->Drink_Blood_Of(thrall, new Callback());
                    } else if (Actor2::Is_Alive(thrall)) {
                        Actor2::Add_Faction(thrall, Consts::DLC1_Thrall_Faction(), 0);

                        struct Callback : public Callback_t<Party::Player_t*, Actor_t*> {
                            void operator()(Party::Player_t* player, Actor_t* thrall)
                            {
                                Actor2::Remove_Faction(thrall, Consts::DLC1_Thrall_Faction());
                            }
                        };
                        Party::Player_t::Self()->Drink_Blood_Of(thrall, new Callback());
                    } else {
                        // do cannibal?
                    }
                }
            };
            Modules::Funcs_t::Self()->Force_Third_Person(new VCallback(thrall));
        }
    }

    void Execute_Resurrect(Reference_t* ref, Actor_t* unknown_actor)
    {
        Actor_t* actor = ref && ref->formType == kFormType_Character ?
            static_cast<Actor_t*>(ref) : nullptr;
        if (actor) {
            Modules::Control::Commands_t::Self()->Resurrect(actor);
        }
    }

    void Execute_Reanimate(Reference_t* ref, Actor_t* unknown_actor)
    {
        Actor_t* actor = ref && ref->formType == kFormType_Character ?
            static_cast<Actor_t*>(ref) : nullptr;
        if (actor) {
            Modules::Control::Commands_t::Self()->Toggle_Reanimated(actor);
        }
    }

    void Execute_Unparalyze(Reference_t* ref, Actor_t* unknown_actor)
    {
        Actor_t* actor = ref && ref->formType == kFormType_Character ?
            static_cast<Actor_t*>(ref) : nullptr;
        if (actor) {
            Modules::Control::Commands_t::Self()->Unparalyze(actor, true);
        }
    }

}}}

namespace doticu_npcp { namespace Papyrus { namespace Perks { namespace Exports {

    void Execute_Perk(Selfless_t*, Perk_t* perk, Reference_t* ref, Actor_t* actor)
    {
        return Perks::Execute_Perk(perk, ref, actor);
    }

    Bool_t Register(VMClassRegistry* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_main", Selfless_t,            \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("Execute_Perk", 3, void, Execute_Perk, Perk_t*, Reference_t*, Actor_t*);

        #undef ADD_GLOBAL

        return true;
    }

}}}}
