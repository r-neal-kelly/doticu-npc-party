/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <cmath>

#include "skse64/GameRTTI.h"

#include "actor_base2.h"
#include "actor2.h"
#include "cell.h"
#include "follower.h"
#include "member.h"
#include "object_ref.h"
#include "papyrus.h"
#include "player.h"
#include "utils.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Follower {

    String_t Class()
    {
        static const String_t class_name = String_t("doticu_npcp_follower");
        return class_name;
    }

    Actor *Get_Actor(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_ref_actor");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return variable->Actor();
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Member_t *Get_Member(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_ref_member");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return variable->Alias();
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Horse_t *Get_Horse(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_ref_horse");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return variable->Alias();
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Actor *Horse_Actor(Follower_t *follower) // this needs to grab info from Horse type instead of direct
    {
        static const String_t variable_name = String_t("p_ref_actor");

        if (follower) {
            Horse_t* horse = Get_Horse(follower);
            if (horse) {
                Variable_t* variable = Variable_t::Fetch(horse, "doticu_npcp_horse", variable_name);
                if (variable) {
                    return variable->Actor();
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    bool Is_Created(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_is_created");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Alive(Follower_t *follower)
    {
        if (follower) {
            return Actor2::Is_Alive(Get_Actor(follower));
        } else {
            return false;
        }
    }

    bool Is_Dead(Follower_t *follower)
    {
        if (!follower) {
            return false;
        }

        return Actor2::Is_Dead(Get_Actor(follower));
    }

    bool Is_Mobile(Follower_t *follower)
    {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Mobile(member);
    }

    bool Is_Immobile(Follower_t *follower)
    {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Immobile(member);
    }

    bool Is_Settler(Follower_t *follower)
    {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Settler(member);
    }

    bool Isnt_Settler(Follower_t *follower)
    {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Isnt_Settler(member);
    }

    bool Is_Paralyzed(Follower_t *follower)
    {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Paralyzed(member);
    }

    bool Isnt_Paralyzed(Follower_t *follower)
    {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Isnt_Paralyzed(member);
    }

    bool Is_Mannequin(Follower_t *follower)
    {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Is_Mannequin(member);
    }

    bool Isnt_Mannequin(Follower_t *follower)
    {
        if (!follower) {
            return false;
        }

        Member_t *member = Get_Member(follower);
        return Member::Isnt_Mannequin(member);
    }

    bool Is_Sneak(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_is_sneak");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Isnt_Sneak(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_is_sneak");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Saddler(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_is_saddler");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Isnt_Saddler(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_is_saddler");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Retreater(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_is_retreater");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Isnt_Retreater(Follower_t *follower)
    {
        static const String_t variable_name = String_t("p_is_retreater");

        if (follower) {
            Variable_t* variable = Variable_t::Fetch(follower, Class(), variable_name);
            if (variable) {
                return !variable->Bool();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Exists(Follower_t *follower)
    {
        return follower && Is_Created(follower) && Get_Actor(follower);
    }

    bool Is_Near_Player(Follower_t *follower, float distance) {
        if (follower)
        {
            Actor *follower_actor = Get_Actor(follower);
            if (follower_actor)
            {
                return Object_Ref::Is_Near_Player(follower_actor, distance);
            }
        }

        return false;
    }

    bool Isnt_Near_Player(Follower_t *follower, float distance) {
        if (follower)
        {
            Actor *follower_actor = Get_Actor(follower);
            if (follower_actor)
            {
                return !Object_Ref::Is_Near_Player(follower_actor, distance);
            }
        }

        return false;
    }

    bool Is_In_Interior_Cell(Follower_t *follower)
    {
        Actor *follower_actor = Get_Actor(follower);
        if (follower_actor)
        {
            TESObjectCELL *follower_cell = follower_actor->parentCell;
            return follower_cell && Cell::Is_Interior(follower_cell);
        }
        else
        {
            return false;
        }
    }

    bool Is_In_Exterior_Cell(Follower_t *follower)
    {
        Actor *follower_actor = Get_Actor(follower);
        if (follower_actor)
        {
            TESObjectCELL *follower_cell = follower_actor->parentCell;
            return follower_cell && Cell::Is_Exterior(follower_cell);
        }
        else
        {
            return false;
        }
    }

    void Summon(Follower_t *follower, float distance, float angle_degree)
    {
        Actor *follower_actor = Get_Actor(follower);
        if (Is_Created(follower) && follower_actor)
        {
            Actor *player_actor = *g_thePlayer;
            if (player_actor)
            {
                Actor *follower_horse = Horse_Actor(follower);
                if (follower_horse && Is_Saddler(follower) && Cell::Is_Exterior(player_actor->parentCell))
                {
                    Actor2::Move_To_Orbit(follower_horse, player_actor, distance * 4, angle_degree + 12);
                    Actor2::Move_To_Orbit(follower_actor, player_actor, distance * 3.5, angle_degree);
                    Saddle(follower);
                }
                else
                {
                    Actor2::Move_To_Orbit(follower_actor, player_actor, distance, angle_degree);
                }
            }
        }
    }

    void Summon_Ahead(Follower_t* follower, float distance)
    {
        if (follower) {
            Actor* follower_actor = Get_Actor(follower);
            Actor* player_actor = *g_thePlayer;
            if (follower_actor && player_actor) {
                Actor2::Move_To_Orbit(follower_actor, player_actor, distance, 0);
            }
        }
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

    void Catch_Up(Follower_t* follower)
    {
        if (Exists(follower) && Is_Mobile(follower) && Isnt_Paralyzed(follower) && Isnt_Mannequin(follower)) {
            if (Player::Is_In_Interior_Cell() || Isnt_Saddler(follower)) {
                if (Isnt_Near_Player(follower)) {
                    Summon_Behind(follower);
                }
            } else {
                Actor* follower_horse = Horse_Actor(follower);
                if (follower_horse && !Object_Ref::Is_Near_Player(follower_horse, 10240.0f)) {
                    if (Player::Is_On_Mount()) {
                        Summon_Behind(follower, 1024.0f);
                    } else {
                        Summon_Behind(follower);
                    }
                    Saddle(follower);
                }
            }
        }
    }

    void Level(Follower_t *follower) {
        enum {
            IS_WARRIOR = -381,
            IS_MAGE = -382,
            IS_ARCHER = -383
        };

        if (!follower) {
            return;
        }

        if (!Is_Created(follower)) {
            return;
        }

        Actor *follower_actor = Get_Actor(follower);
        if (!follower_actor) {
            return;
        }

        TESNPC *follower_base = DYNAMIC_CAST(follower_actor->baseForm, TESForm, TESNPC);
        if (!follower_base) {
            return;
        }

        Actor *player_actor = *g_thePlayer;
        if (!player_actor) {
            return;
        }

        const UInt16 player_level = CALL_MEMBER_FN(player_actor, GetLevel)();
        const SInt32 follower_style = Member::Get_Style(Get_Member(follower));
        const float player_modifier = 0.67f - (log((float)player_level) * 0.067f);
        const float player_level_modded = player_level * player_modifier;
        const float max_attribute = 1000.0f;
        const float min_attribute = 100.0f;
        const float max_skill = 100.0f;
        const float min_skill = 0.0f;

        #define GET_BASE_VALUE(NAME)                                            \
        (                                                                       \
            Actor_Base2::Get_Base_Actor_Value(follower_base, NAME) +            \
            Actor2::Get_Base_Actor_Value(player_actor, NAME) * player_modifier  \
        )

        float health = GET_BASE_VALUE("Health");
        float magicka = GET_BASE_VALUE("Magicka");
        float stamina = GET_BASE_VALUE("Stamina");

        float one_handed = GET_BASE_VALUE("OneHanded");
        float two_handed = GET_BASE_VALUE("TwoHanded");
        float block = GET_BASE_VALUE("Block");
        float heavy_armor = GET_BASE_VALUE("HeavyArmor");
        float light_armor = GET_BASE_VALUE("LightArmor");
        float smithing = GET_BASE_VALUE("Smithing");

        float destruction = GET_BASE_VALUE("Destruction");
        float restoration = GET_BASE_VALUE("Restoration");
        float conjuration = GET_BASE_VALUE("Conjuration");
        float alteration = GET_BASE_VALUE("Alteration");
        float illusion = GET_BASE_VALUE("Illusion");
        float enchanting = GET_BASE_VALUE("Enchanting");

        float marksman = GET_BASE_VALUE("Marksman");
        float sneak = GET_BASE_VALUE("Sneak");
        float alchemy = GET_BASE_VALUE("Alchemy");
        float lockpicking = GET_BASE_VALUE("Lockpicking");
        float pickpocket = GET_BASE_VALUE("Pickpocket");
        float speechcraft = GET_BASE_VALUE("Speechcraft");

        #undef GET_BASE_VALUE

        #define MOD_STRENGTH(OP, OPERAND)   \
        M                                   \
            one_handed  OP= (OPERAND);      \
            two_handed  OP= (OPERAND);      \
            block       OP= (OPERAND);      \
            heavy_armor OP= (OPERAND);      \
            light_armor OP= (OPERAND);      \
            smithing    OP= (OPERAND);      \
        W

        #define MOD_INTELLIGENCE(OP, OPERAND)   \
        M                                       \
            destruction OP= (OPERAND);          \
            restoration OP= (OPERAND);          \
            conjuration OP= (OPERAND);          \
            alteration  OP= (OPERAND);          \
            illusion    OP= (OPERAND);          \
            enchanting  OP= (OPERAND);          \
        W

        #define MOD_DEXTERITY(OP, OPERAND)  \
        M                                   \
            marksman    OP= (OPERAND);      \
            sneak       OP= (OPERAND);      \
            alchemy     OP= (OPERAND);      \
            lockpicking OP= (OPERAND);      \
            pickpocket  OP= (OPERAND);      \
            speechcraft OP= (OPERAND);      \
        W

        if (follower_style == IS_WARRIOR) {
            health += player_level * 4; // find a better equation
            MOD_STRENGTH(+, player_level_modded);
            MOD_INTELLIGENCE(-, player_level_modded);
            MOD_DEXTERITY(-, player_level_modded);
        } else if (follower_style == IS_MAGE) {
            magicka += player_level * 4; // find a better equation
            MOD_STRENGTH(-, player_level_modded);
            MOD_INTELLIGENCE(+, player_level_modded);
            MOD_DEXTERITY(-, player_level_modded);
        } else if (follower_style == IS_ARCHER) {
            stamina += player_level * 4; // find a better equation
            MOD_STRENGTH(-, player_level_modded);
            MOD_INTELLIGENCE(-, player_level_modded);
            MOD_DEXTERITY(+, player_level_modded);
        }

        #undef MOD_STRENGTH
        #undef MOD_INTELLIGENCE
        #undef MOD_DEXTERITY

        #define SET_ATTRIBUTE(NAME, VALUE)                  \
        (                                                   \
            Actor2::Set_Actor_Value(follower_actor, NAME,   \
                (VALUE) > max_attribute ? max_attribute :   \
                (VALUE) < min_attribute ? min_attribute :   \
                (VALUE)                                     \
            )                                               \
        )

        #define SET_SKILL(NAME, VALUE)                      \
        (                                                   \
            Actor2::Set_Actor_Value(follower_actor, NAME,   \
                (VALUE) > max_skill ? max_skill :           \
                (VALUE) < min_skill ? min_skill :           \
                (VALUE)                                     \
            )                                               \
        )

        SET_ATTRIBUTE("Health", health);
        SET_ATTRIBUTE("Magicka", magicka);
        SET_ATTRIBUTE("Stamina", stamina);

        SET_SKILL("OneHanded", one_handed);
        SET_SKILL("TwoHanded", two_handed);
        SET_SKILL("Block", block);
        SET_SKILL("HeavyArmor", heavy_armor);
        SET_SKILL("LightArmor", light_armor);
        SET_SKILL("Smithing", smithing);

        SET_SKILL("Destruction", destruction);
        SET_SKILL("Restoration", restoration);
        SET_SKILL("Conjuration", conjuration);
        SET_SKILL("Alteration", alteration);
        SET_SKILL("Illusion", illusion);
        SET_SKILL("Enchanting", enchanting);

        SET_SKILL("Marksman", marksman);
        SET_SKILL("Sneak", sneak);
        SET_SKILL("Alchemy", alchemy);
        SET_SKILL("Lockpicking", lockpicking);
        SET_SKILL("Pickpocket", pickpocket);
        SET_SKILL("Speechcraft", speechcraft);

        #undef SET_ATTRIBUTE
        #undef SET_SKILL
    }

    void Unlevel(Follower_t *follower) {
        if (!follower) {
            return;
        }

        if (!Is_Created(follower)) {
            return;
        }

        Actor *follower_actor = Get_Actor(follower);
        if (!follower_actor) {
            return;
        }

        TESNPC *follower_base = DYNAMIC_CAST(follower_actor->baseForm, TESForm, TESNPC);
        if (!follower_base) {
            return;
        }

        #define RESET_VALUE(NAME)                                       \
        (                                                               \
            Actor2::Set_Actor_Value(follower_actor, NAME,               \
                Actor_Base2::Get_Base_Actor_Value(follower_base, NAME)  \
            )                                                           \
        )

        RESET_VALUE("Health");
        RESET_VALUE("Magicka");
        RESET_VALUE("Stamina");

        RESET_VALUE("OneHanded");
        RESET_VALUE("TwoHanded");
        RESET_VALUE("Block");
        RESET_VALUE("HeavyArmor");
        RESET_VALUE("LightArmor");
        RESET_VALUE("Smithing");

        RESET_VALUE("Destruction");
        RESET_VALUE("Restoration");
        RESET_VALUE("Conjuration");
        RESET_VALUE("Alteration");
        RESET_VALUE("Illusion");
        RESET_VALUE("Enchanting");

        RESET_VALUE("Marksman");
        RESET_VALUE("Sneak");
        RESET_VALUE("Alchemy");
        RESET_VALUE("Lockpicking");
        RESET_VALUE("Pickpocket");
        RESET_VALUE("Speechcraft");

        #undef RESET_VALUE
    }

    void Saddle(Follower_t *follower)
    {
        BSFixedString name("p_Saddle");

        struct Args : public IFunctionArguments
        {
            bool Copy(Output *output)
            {
                return true;
            }
        }
        args;

        Papyrus::Handle_t follower_handle(follower);
        follower_handle.Registry()->QueueEvent(follower_handle, &name, &args);
    }

}}

namespace doticu_npcp { namespace Follower { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_follower", Follower_t,        \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Follower::METHOD_, __VA_ARGS__);  \
        W

        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp", Selfless_t,                 \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("p_Level", 0, void, Level);
        ADD_METHOD("p_Unlevel", 0, void, Unlevel);

        #undef ADD_METHOD
        #undef ADD_GLOBAL

        return true;
    }

}}}
