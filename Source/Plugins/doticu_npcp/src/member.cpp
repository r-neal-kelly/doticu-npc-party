/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "actor_base2.h"
#include "alias.h"
#include "member.h"
#include "utils.h"

namespace doticu_npcp { namespace Party { namespace Member {

    String_t Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_member");
        return class_name;
    }

    Class_Info_t* Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Variable_t* Variable(Member_t* self, String_t variable_name)
    {
        return Variable_t::Fetch(self, Class_Name(), variable_name);
    }

    Actor_t* Actor(Member_t* self)
    {
        static const String_t variable_name = String_t("p_ref_actor");

        Variable_t* const variable = Variable(self, variable_name);
        if (self && variable) {
            Actor_t* actor = variable->Actor();
            return variable->Actor();
        } else {
            return nullptr;
        }
    }

    Int_t Rating(Member_t* self)
    {
        static const String_t variable_name = String_t("p_int_rating");

        Variable_t* const variable = Variable(self, variable_name);
        if (self && variable) {
            return variable->Int();
        } else {
            return 0;
        }
    }

    String_t Race_Name(Member_t* self)
    {
        Actor_t* actor = Actor(self);
        if (actor) {
            return actor->race->fullName.name;
        } else {
            return "";
        }
    }

    Bool_t Is_Filled(Member_t* self)
    {
        if (self) {
            return Is_Created(self) && Actor(self) != nullptr;
        } else {
            return false;
        }
    }

    Bool_t Is_Unfilled(Member_t* self)
    {
        if (self) {
            return Is_Destroyed(self) || Actor(self) == nullptr;
        } else {
            return false;
        }
    }

    Bool_t Is_Loaded(Member_t* self)
    {
        return self && Actor2::Is_Loaded(Actor(self));
    }

    Bool_t Is_Unloaded(Member_t* self)
    {
        return self && Actor2::Is_Unloaded(Actor(self));
    }

    Bool_t Is_Created(Member_t* self)
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(self, variable_name);
        if (self && variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Is_Destroyed(Member_t* self)
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(self, variable_name);
        if (self && variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Has_Same_Head(Member_t* self, Actor_t* actor)
    {
        if (self && actor) {
            Actor_t* alias_actor = Actor(self);
            if (alias_actor && Is_Created(self)) {
                Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(actor->baseForm);
                Actor_Base_t* alias_actor_base = static_cast<Actor_Base_t*>(alias_actor->baseForm);
                if (actor_base && alias_actor_base && Actor_Base2::Has_Same_Head(actor_base, alias_actor_base)) {
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void Log_Variable_Infos(Member_t* self)
    {
        Object_t* script = Object_t::Fetch(self, "doticu_npcp_member");
        if (script) {
            Class_Info_t* info = script->info;
            while (info) {
                info->Log_Variable_Infos();
                info = info->parent != info ? info->parent : nullptr;
            }
        }
    }

}}}

#include "utils.h"

namespace doticu_npcp { namespace Party { namespace Member { namespace Exports {

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_member", Member_t,            \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Member::METHOD_, __VA_ARGS__);    \
        W

        ADD_METHOD("Actor", 0, Actor_t*, Actor);



        ADD_METHOD("Log_Variable_Infos", 0, void, Log_Variable_Infos);

        #undef ADD_METHOD

        return true;
    }

}}}}













































#include "skse64/GameData.h"

#include "actor2.h"
#include "member.h"
#include "papyrus.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Member {

    String_t Class()
    {
        static const String_t class_name = String_t("doticu_npcp_member");
        return class_name;
    }

    Actor *Get_Actor(Member_t *member)
    {
        static const String_t variable_name = String_t("p_ref_actor");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Actor();
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    TESObjectREFR *Get_Pack(Member_t *member)
    {
        static const String_t variable_name = String_t("p_container_pack");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Reference();
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    SInt32 Get_Style(Member_t *member)
    {
        static const String_t variable_name = String_t("p_code_style");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Int();
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    SInt32 Get_Vitality(Member_t *member)
    {
        static const String_t variable_name = String_t("p_code_vitality");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Int();
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    SInt32 Get_Outfit2(Member_t *member)
    {
        static const String_t variable_name = String_t("p_code_outfit2");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Int();
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    SInt32 Get_Rating(Member_t *member)
    {
        static const String_t variable_name = String_t("p_int_rating");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Int();
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    bool Is_Created(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_created");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Original(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_clone");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Clone(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_clone");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Follower(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_follower");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Mobile(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_immobile");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Immobile(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_immobile");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Settler(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_settler");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Isnt_Settler(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_settler");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Thrall(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_thrall");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Isnt_Thrall(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_thrall");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Paralyzed(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_paralyzed");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Isnt_Paralyzed(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_paralyzed");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Mannequin(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_mannequin");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Isnt_Mannequin(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_mannequin");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Reanimated(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_reanimated");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Isnt_Reanimated(Member_t *member)
    {
        static const String_t variable_name = String_t("p_is_reanimated");

        if (member) {
            Variable_t* variable = Variable_t::Fetch(member, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
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
                Papyrus::Handle_t member_handle(member);
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
