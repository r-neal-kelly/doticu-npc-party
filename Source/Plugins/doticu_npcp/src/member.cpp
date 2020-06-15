/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"

#include "actor2.h"
#include "member.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Member {

    Actor *Get_Actor(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_ref_actor").Actor();
        } else {
            return nullptr;
        }
    }

    TESObjectREFR *Get_Pack(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_container_pack").Object();
        } else {
            return nullptr;
        }
    }

    SInt32 Get_Style(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_code_style").Int();
        } else {
            return 0;
        }
    }

    SInt32 Get_Vitality(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_code_vitality").Int();
        } else {
            return 0;
        }
    }

    SInt32 Get_Outfit2(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_code_outfit2").Int();
        } else {
            return 0;
        }
    }

    SInt32 Get_Rating(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_int_rating").Int();
        } else {
            return 0;
        }
    }

    bool Is_Created(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_is_created").Bool();
        } else {
            return false;
        }
    }

    bool Is_Original(Member_t *member)
    {
        if (member) {
            return !Papyrus::Variable(member, "p_is_clone").Bool();
        } else {
            return false;
        }
    }

    bool Is_Clone(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_is_clone").Bool();
        } else {
            return false;
        }
    }

    bool Is_Follower(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_is_follower").Bool();
        } else {
            return false;
        }
    }

    bool Is_Mobile(Member_t *member)
    {
        if (member) {
            return !Papyrus::Variable(member, "p_is_immobile").Bool();
        } else {
            return false;
        }
    }

    bool Is_Immobile(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_is_immobile").Bool();
        } else {
            return false;
        }
    }

    bool Is_Settler(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_is_settler").Bool();
        } else {
            return false;
        }
    }

    bool Isnt_Settler(Member_t *member)
    {
        if (member) {
            return !Papyrus::Variable(member, "p_is_settler").Bool();
        } else {
            return false;
        }
    }

    bool Is_Thrall(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_is_thrall").Bool();
        } else {
            return false;
        }
    }

    bool Isnt_Thrall(Member_t *member)
    {
        if (member) {
            return !Papyrus::Variable(member, "p_is_thrall").Bool();
        } else {
            return false;
        }
    }

    bool Is_Paralyzed(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_is_paralyzed").Bool();
        } else {
            return false;
        }
    }

    bool Isnt_Paralyzed(Member_t *member)
    {
        if (member) {
            return !Papyrus::Variable(member, "p_is_paralyzed").Bool();
        } else {
            return false;
        }
    }

    bool Is_Mannequin(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_is_mannequin").Bool();
        } else {
            return false;
        }
    }

    bool Isnt_Mannequin(Member_t *member)
    {
        if (member) {
            return !Papyrus::Variable(member, "p_is_mannequin").Bool();
        } else {
            return false;
        }
    }

    bool Is_Reanimated(Member_t *member)
    {
        if (member) {
            return Papyrus::Variable(member, "p_is_reanimated").Bool();
        } else {
            return false;
        }
    }

    bool Isnt_Reanimated(Member_t *member)
    {
        if (member) {
            return !Papyrus::Variable(member, "p_is_reanimated").Bool();
        } else {
            return false;
        }
    }

    void On_Hit(Member_t *member,
                TESObjectREFR *attacker,
                TESForm *tool,
                BGSProjectile *projectile,
                bool is_power,
                bool is_sneak,
                bool is_bash,
                bool is_blocked) {
        enum {
            IS_MORTAL = -303,
            IS_PROTECTED = -304,
            IS_ESSENTIAL = -305,
            IS_INVULNERABLE = -306
        };

        Actor *member_actor = Member::Get_Actor(member);
        if (!member_actor || Actor2::Is_Dead(member_actor)) {
            return;
        }

        SInt32 member_vitality = Member::Get_Vitality(member);
        UInt32 id_health = LookupActorValueByName("Health");

        // we have the branching like this in concern for speed
        if (member_actor->actorValueOwner.GetCurrent(id_health) <= 0.0) {
            if (member_vitality == IS_MORTAL || member_vitality == IS_PROTECTED && attacker == *g_thePlayer) {
                BSFixedString func_name("p_Kill");
                struct Args : public IFunctionArguments {
                    bool Copy(Output *output) { return true; }
                } func_args;
                Papyrus::Handle member_handle(kFormType_Alias, member);
                member_handle.Registry()->QueueEvent(member_handle, &func_name, &func_args);
            }
        } else if (member_vitality == IS_INVULNERABLE) {
            // We need RestoreCurrent, but don't have it, so we do this instead.
            // Unfortuneately, not sure how to get the previous health back, so we just keep increasing until next enforce.
            float max_health = member_actor->actorValueOwner.GetMaximum(id_health);
            if (max_health < 1000000000) {
                member_actor->actorValueOwner.SetCurrent(id_health, member_actor->actorValueOwner.GetMaximum(id_health) + 1000.f);
            }
        }
    }

}}

namespace doticu_npcp { namespace Member { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction7 <Member_t, void, TESObjectREFR *, TESForm *, BGSProjectile *, bool, bool, bool, bool>(
                "OnHit",
                "doticu_npcp_member",
                Member::On_Hit,
                registry)
        );

        return true;
    }

}}}
