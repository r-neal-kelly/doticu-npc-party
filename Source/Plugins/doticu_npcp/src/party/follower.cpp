/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "actor_base2.h"
#include "cell.h"
#include "consts.h"
#include "object_ref.h"
#include "party.h"
#include "party.inl"
#include "player.h"
#include "utils.h"

namespace doticu_npcp { namespace Party {

    String_t Follower_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_follower");
        return class_name;
    }

    Class_Info_t* Follower_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        return object_info;
    }

    Variable_t* Follower_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Actor_t* Follower_t::Actor()
    {
        static const String_t variable_name = String_t("p_ref_actor");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Actor();
        } else {
            return nullptr;
        }
    }

    Member_t* Follower_t::Member()
    {
        Members_t* members = Members_t::Self();
        if (members) {
            return members->From_Actor(Actor());
        } else {
            return nullptr;
        }
    }

    Horse_t* Follower_t::Horse()
    {
        Horses_t* horses = Horses_t::Self();
        if (horses) {
            return horses->From_ID(ID() + Followers_t::MAX);
        } else {
            return nullptr;
        }
    }

    Reference_t* Follower_t::Pack()
    {
        Member_t* member = Member();
        return member ? member->Pack() : nullptr;
    }

    Cell_t* Follower_t::Cell()
    {
        Member_t* member = Member();
        return member ? member->Cell() : nullptr;
    }

    Int_t Follower_t::Style()
    {
        Member_t* member = Member();
        return member ? member->Style() : 0;
    }

    Int_t Follower_t::Vitality()
    {
        Member_t* member = Member();
        return member ? member->Vitality() : 0;
    }

    Int_t Follower_t::Outfit2()
    {
        Member_t* member = Member();
        return member ? member->Outfit2() : 0;
    }

    Int_t Follower_t::Rating()
    {
        Member_t* member = Member();
        return member ? member->Rating() : 0;
    }

    String_t Follower_t::Sex()
    {
        Member_t* member = Member();
        return member ? member->Sex() : "";
    }

    String_t Follower_t::Race()
    {
        Member_t* member = Member();
        return member ? member->Race() : "";
    }

    String_t Follower_t::Base_Name()
    {
        return Actor2::Get_Base_Name(Actor());
    }

    String_t Follower_t::Reference_Name()
    {
        return Actor2::Get_Ref_Name(Actor());
    }

    String_t Follower_t::Name()
    {
        return Actor2::Get_Name(Actor());
    }

    Bool_t Follower_t::Is_Filled()
    {
        return Is_Created() && Actor() != nullptr;
    }

    Bool_t Follower_t::Is_Unfilled()
    {
        return Is_Destroyed() || Actor() == nullptr;
    }

    Bool_t Follower_t::Is_Loaded()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Loaded(actor);
    }

    Bool_t Follower_t::Is_Unloaded()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Unloaded(actor);
    }

    Bool_t Follower_t::Is_Created()
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Destroyed()
    {
        static const String_t variable_name = String_t("p_is_created");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Unique()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Unique(actor);
    }

    Bool_t Follower_t::Is_Generic()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Generic(actor);
    }

    Bool_t Follower_t::Is_Original()
    {
        Member_t* member = Member();
        return member && member->Is_Original();
    }

    Bool_t Follower_t::Is_Clone()
    {
        Member_t* member = Member();
        return member && member->Is_Clone();
    }

    Bool_t Follower_t::Is_Alive()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Alive(actor);
    }

    Bool_t Follower_t::Is_Dead()
    {
        Actor_t* actor = Actor();
        return actor && Actor2::Is_Dead(actor);
    }

    Bool_t Follower_t::Is_Mobile()
    {
        Member_t* member = Member();
        return member && member->Is_Mobile();
    }

    Bool_t Follower_t::Is_Immobile()
    {
        Member_t* member = Member();
        return member && member->Is_Immobile();
    }

    Bool_t Follower_t::Is_Settler()
    {
        Member_t* member = Member();
        return member && member->Is_Settler();
    }

    Bool_t Follower_t::Isnt_Settler()
    {
        Member_t* member = Member();
        return member && member->Isnt_Settler();
    }

    Bool_t Follower_t::Is_Thrall()
    {
        Member_t* member = Member();
        return member && member->Is_Thrall();
    }

    Bool_t Follower_t::Isnt_Thrall()
    {
        Member_t* member = Member();
        return member && member->Isnt_Thrall();
    }

    Bool_t Follower_t::Is_Paralyzed()
    {
        Member_t* member = Member();
        return member && member->Is_Paralyzed();
    }

    Bool_t Follower_t::Isnt_Paralyzed()
    {
        Member_t* member = Member();
        return member && member->Isnt_Paralyzed();
    }

    Bool_t Follower_t::Is_Mannequin()
    {
        Member_t* member = Member();
        return member && member->Is_Mannequin();
    }

    Bool_t Follower_t::Isnt_Mannequin()
    {
        Member_t* member = Member();
        return member && member->Isnt_Mannequin();
    }

    Bool_t Follower_t::Is_Reanimated()
    {
        Member_t* member = Member();
        return member && member->Is_Reanimated();
    }

    Bool_t Follower_t::Isnt_Reanimated()
    {
        Member_t* member = Member();
        return member && member->Isnt_Reanimated();
    }

    Bool_t Follower_t::Is_Follower()
    {
        return Is_Filled();
    }

    Bool_t Follower_t::Isnt_Follower()
    {
        return Is_Unfilled();
    }

    Bool_t Follower_t::Is_Sneak()
    {
        static const String_t variable_name = String_t("p_is_sneak");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Isnt_Sneak()
    {
        static const String_t variable_name = String_t("p_is_sneak");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Saddler()
    {
        static const String_t variable_name = String_t("p_is_saddler");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Isnt_Saddler()
    {
        static const String_t variable_name = String_t("p_is_saddler");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Retreater()
    {
        static const String_t variable_name = String_t("p_is_retreater");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Isnt_Retreater()
    {
        static const String_t variable_name = String_t("p_is_retreater");

        Variable_t* const variable = Variable(variable_name);
        if (variable) {
            return !variable->Bool();
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_Near_Player(float radius)
    {
        Actor_t* actor = Actor();
        return actor && Object_Ref::Is_Near_Player(actor, radius);
    }

    Bool_t Follower_t::Isnt_Near_Player(float radius)
    {
        Actor_t* actor = Actor();
        return actor && !Object_Ref::Is_Near_Player(actor, radius);
    }

    Bool_t Follower_t::Is_In_Interior_Cell()
    {
        Cell_t* cell = Cell();
        return cell && Cell::Is_Interior(cell);
    }

    Bool_t Follower_t::Is_In_Exterior_Cell()
    {
        Cell_t* cell = Cell();
        return cell && Cell::Is_Exterior(cell);
    }

    bool Follower_t::Has_Token(Misc_t* token, Int_t count)
    {
        return Object_Ref::Has_Token(Actor(), token, count);
    }

    void Follower_t::Token(Misc_t* token, Int_t count)
    {
        Object_Ref::Token(Actor(), token, count);
    }

    void Follower_t::Untoken(Misc_t* token)
    {
        Object_Ref::Untoken(Actor(), token);
    }

    void Follower_t::Summon(float radius, float degree)
    {
        Actor_t* player_actor = *g_thePlayer;
        Actor_t* follower_actor = Actor();
        if (player_actor && follower_actor && Is_Created()) {
            if (Player::Is_In_Exterior_Cell() && Is_Saddler()) {
                Horse_t* follower_horse = Horse();
                Actor_t* follower_horse_actor = follower_horse ? follower_horse->Actor() : nullptr;
                if (follower_horse_actor) {
                    Actor2::Move_To_Orbit(follower_horse_actor, player_actor, radius * 4, degree + 12);
                    Actor2::Move_To_Orbit(follower_actor, player_actor, radius * 3.5, degree);
                    Saddle();
                } else {
                    Actor2::Move_To_Orbit(follower_actor, player_actor, radius, degree);
                }
            } else {
                Actor2::Move_To_Orbit(follower_actor, player_actor, radius, degree);
            }
        }
    }

    void Follower_t::Summon_Ahead(float radius)
    {
        Summon(radius, 0);
    }

    void Follower_t::Summon_Behind(float radius)
    {
        Summon(radius, 180);
    }

    void Follower_t::Mobilize()
    {
        Member_t* member = Member();
        if (member) {
            member->Mobilize();
        }
    }

    void Follower_t::Immobilize()
    {
        Member_t* member = Member();
        if (member) {
            member->Immobilize();
        }
    }

    void Follower_t::Settle()
    {
        Member_t* member = Member();
        if (member) {
            member->Settle();
        }
    }

    void Follower_t::Unsettle()
    {
        Member_t* member = Member();
        if (member) {
            member->Unsettle();
        }
    }

    void Follower_t::Enthrall()
    {
        Member_t* member = Member();
        if (member) {
            member->Enthrall();
        }
    }

    void Follower_t::Unthrall()
    {
        Member_t* member = Member();
        if (member) {
            member->Unthrall();
        }
    }

    void Follower_t::Paralyze()
    {
        Member_t* member = Member();
        if (member) {
            member->Paralyze();
        }
    }

    void Follower_t::Unparalyze()
    {
        Member_t* member = Member();
        if (member) {
            member->Unparalyze();
        }
    }

    void Follower_t::Catch_Up()
    {
        if (Is_Filled() && Is_Mobile() && Isnt_Paralyzed() && Isnt_Mannequin()) {
            if (Player::Is_In_Interior_Cell() || Isnt_Saddler()) {
                if (Isnt_Near_Player()) {
                    Summon_Behind();
                }
            } else {
                Horse_t* horse = Horse();
                if (horse) {
                    Actor_t* horse_actor = horse->Actor();
                    if (horse_actor && !Object_Ref::Is_Near_Player(horse_actor, 10240.0f)) {
                        if (Player::Is_On_Mount()) {
                            Summon_Behind(1024.0f);
                        } else {
                            Summon_Behind();
                        }
                        Saddle();
                    }
                }
            }
        }
    }

    void Follower_t::Saddle()
    {
        static const String_t func_name = String_t("p_Saddle");

        struct Args : public IFunctionArguments {
            bool Copy(Output* output)
            {
                return true;
            }
        } args;

        Handle_t handle(this);
        handle.Registry()->QueueEvent(handle, &func_name, &args);
    }

    void Follower_t::Level()
    {
        Actor_t* player_actor = *g_thePlayer;
        Actor_t* follower_actor = Actor();
        if (player_actor && follower_actor && Is_Created()) {
            Actor_Value_Owner_t* values =
                Actor2::Actor_Value_Owner(follower_actor);
            Actor_Value_Owner_t* base_values =
                Actor_Base2::Actor_Value_Owner(static_cast<Actor_Base_t*>(follower_actor->baseForm));
            if (values && base_values) {
                const UInt16 player_level = CALL_MEMBER_FN(player_actor, GetLevel)();
                const float player_modifier = 0.67f - (log((float)player_level) * 0.067f);

                float health;
                float magicka;
                float stamina;

                float one_handed;
                float two_handed;
                float block;
                float heavy_armor;
                float light_armor;
                float smithing;

                float destruction;
                float restoration;
                float conjuration;
                float alteration;
                float illusion;
                float enchanting;

                float marksman;
                float sneak;
                float alchemy;
                float lockpicking;
                float pickpocket;
                float speechcraft;

                auto Get_Values = [&]() -> void
                {
                    auto Get_Value = [&](Actor_Value_t value_type) -> float
                    {
                        return base_values->Get_Base_Actor_Value(value_type) * player_modifier;
                    };

                    health = Get_Value(Actor_Value_t::HEALTH);
                    magicka = Get_Value(Actor_Value_t::MAGICKA);
                    stamina = Get_Value(Actor_Value_t::STAMINA);

                    one_handed = Get_Value(Actor_Value_t::ONE_HANDED);
                    two_handed = Get_Value(Actor_Value_t::TWO_HANDED);
                    block = Get_Value(Actor_Value_t::BLOCK);
                    heavy_armor = Get_Value(Actor_Value_t::HEAVY_ARMOR);
                    light_armor = Get_Value(Actor_Value_t::LIGHT_ARMOR);
                    smithing = Get_Value(Actor_Value_t::SMITHING);

                    destruction = Get_Value(Actor_Value_t::DESTRUCTION);
                    restoration = Get_Value(Actor_Value_t::RESTORATION);
                    conjuration = Get_Value(Actor_Value_t::CONJURATION);
                    alteration = Get_Value(Actor_Value_t::ALTERATION);
                    illusion = Get_Value(Actor_Value_t::ILLUSION);
                    enchanting = Get_Value(Actor_Value_t::ENCHANTING);

                    marksman = Get_Value(Actor_Value_t::MARKSMAN);
                    sneak = Get_Value(Actor_Value_t::SNEAK);
                    alchemy = Get_Value(Actor_Value_t::ALCHEMY);
                    lockpicking = Get_Value(Actor_Value_t::LOCKPICKING);
                    pickpocket = Get_Value(Actor_Value_t::PICKPOCKET);
                    speechcraft = Get_Value(Actor_Value_t::SPEECHCRAFT);
                };

                auto Mod_Values = [&]() -> void
                {
                    auto Mod_Strength = [&](float modifier) -> void
                    {
                        one_handed += modifier;
                        two_handed += modifier;
                        block += modifier;
                        heavy_armor += modifier;
                        light_armor += modifier;
                        smithing += modifier;
                    };

                    auto Mod_Intelligence = [&](float modifier) -> void
                    {
                        destruction += modifier;
                        restoration += modifier;
                        conjuration += modifier;
                        alteration += modifier;
                        illusion += modifier;
                        enchanting += modifier;
                    };

                    auto Mod_Dexterity = [&](float modifier) -> void
                    {
                        marksman += modifier;
                        sneak += modifier;
                        alchemy += modifier;
                        lockpicking += modifier;
                        pickpocket += modifier;
                        speechcraft += modifier;
                    };

                    const SInt32 follower_style = Style();
                    const float player_level_modded = player_level * player_modifier;
                    if (follower_style == Style_e::WARRIOR) {
                        health += player_level * 4; // find a better equation
                        Mod_Strength(+player_level_modded);
                        Mod_Intelligence(-player_level_modded);
                        Mod_Dexterity(-player_level_modded);
                    } else if (follower_style == Style_e::MAGE) {
                        magicka += player_level * 4; // find a better equation
                        Mod_Strength(-player_level_modded);
                        Mod_Intelligence(+player_level_modded);
                        Mod_Dexterity(-player_level_modded);
                    } else if (follower_style == Style_e::ARCHER) {
                        stamina += player_level * 4; // find a better equation
                        Mod_Strength(-player_level_modded);
                        Mod_Intelligence(-player_level_modded);
                        Mod_Dexterity(+player_level_modded);
                    }
                };

                auto Set_Values = [&]() -> void
                {
                    constexpr float max_attribute = 1000.0f;
                    constexpr float min_attribute = 100.0f;
                    constexpr float max_skill = 100.0f;
                    constexpr float min_skill = 0.0f;

                    auto Set_Attribute = [&](Actor_Value_t value_type, float value) -> void
                    {
                        values->Set_Base_Actor_Value(
                            value_type,
                            value > max_attribute ? max_attribute :
                            value < min_attribute ? min_attribute :
                            value
                        );
                    };

                    auto Set_Skill = [&](Actor_Value_t value_type, float value) -> void
                    {
                        values->Set_Base_Actor_Value(
                            value_type,
                            value > max_skill ? max_skill :
                            value < min_skill ? min_skill :
                            value
                        );
                    };

                    Set_Attribute(Actor_Value_t::HEALTH, health);
                    Set_Attribute(Actor_Value_t::MAGICKA, magicka);
                    Set_Attribute(Actor_Value_t::STAMINA, stamina);

                    Set_Skill(Actor_Value_t::ONE_HANDED, one_handed);
                    Set_Skill(Actor_Value_t::TWO_HANDED, two_handed);
                    Set_Skill(Actor_Value_t::BLOCK, block);
                    Set_Skill(Actor_Value_t::HEAVY_ARMOR, heavy_armor);
                    Set_Skill(Actor_Value_t::LIGHT_ARMOR, light_armor);
                    Set_Skill(Actor_Value_t::SMITHING, smithing);

                    Set_Skill(Actor_Value_t::DESTRUCTION, destruction);
                    Set_Skill(Actor_Value_t::RESTORATION, restoration);
                    Set_Skill(Actor_Value_t::CONJURATION, conjuration);
                    Set_Skill(Actor_Value_t::ALTERATION, alteration);
                    Set_Skill(Actor_Value_t::ILLUSION, illusion);
                    Set_Skill(Actor_Value_t::ENCHANTING, enchanting);

                    Set_Skill(Actor_Value_t::MARKSMAN, marksman);
                    Set_Skill(Actor_Value_t::SNEAK, sneak);
                    Set_Skill(Actor_Value_t::ALCHEMY, alchemy);
                    Set_Skill(Actor_Value_t::LOCKPICKING, lockpicking);
                    Set_Skill(Actor_Value_t::PICKPOCKET, pickpocket);
                    Set_Skill(Actor_Value_t::SPEECHCRAFT, speechcraft);
                };

                auto Check_Values = [&]() -> void
                {
                    auto Check_Value = [&](Actor_Value_t value_type, float desired_value) -> void
                    {
                        float permanent_value = values->Get_Permanent_Actor_Value(value_type);
                        if (permanent_value < 0.0f) {
                            values->Restore_Actor_Value(Actor_Modifier_t::PERMANENT,
                                                        value_type,
                                                        -permanent_value + desired_value);
                            permanent_value = values->Get_Permanent_Actor_Value(value_type);
                            if (permanent_value < 0.0f) {
                                values->Mod_Actor_Value(value_type,
                                                        -permanent_value + desired_value);
                            }
                        }
                    };

                    Check_Value(Actor_Value_t::HEALTH, health);
                    Check_Value(Actor_Value_t::MAGICKA, magicka);
                    Check_Value(Actor_Value_t::STAMINA, stamina);

                    Check_Value(Actor_Value_t::ONE_HANDED, one_handed);
                    Check_Value(Actor_Value_t::TWO_HANDED, two_handed);
                    Check_Value(Actor_Value_t::BLOCK, block);
                    Check_Value(Actor_Value_t::HEAVY_ARMOR, heavy_armor);
                    Check_Value(Actor_Value_t::LIGHT_ARMOR, light_armor);
                    Check_Value(Actor_Value_t::SMITHING, smithing);

                    Check_Value(Actor_Value_t::DESTRUCTION, destruction);
                    Check_Value(Actor_Value_t::RESTORATION, restoration);
                    Check_Value(Actor_Value_t::CONJURATION, conjuration);
                    Check_Value(Actor_Value_t::ALTERATION, alteration);
                    Check_Value(Actor_Value_t::ILLUSION, illusion);
                    Check_Value(Actor_Value_t::ENCHANTING, enchanting);

                    Check_Value(Actor_Value_t::MARKSMAN, marksman);
                    Check_Value(Actor_Value_t::SNEAK, sneak);
                    Check_Value(Actor_Value_t::ALCHEMY, alchemy);
                    Check_Value(Actor_Value_t::LOCKPICKING, lockpicking);
                    Check_Value(Actor_Value_t::PICKPOCKET, pickpocket);
                    Check_Value(Actor_Value_t::SPEECHCRAFT, speechcraft);
                };

                Get_Values();
                Mod_Values();
                Set_Values();
                Check_Values();
            }
        }
    }

    void Follower_t::Unlevel()
    {
        if (!Is_Created()) {
            return;
        }

        Actor_t* follower_actor = Actor();
        if (!follower_actor) {
            return;
        }

        TESNPC* follower_base = static_cast<TESNPC*>(follower_actor->baseForm);
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

    void Follower_t::Sneak()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Actor_Value_Owner_t* values = Actor2::Actor_Value_Owner(actor);
            if (values) {
                values->Set_Actor_Value(Actor_Value_t::SPEED_MULT, MAX_SNEAK_SPEED);
            }

            Object_Ref::Token(actor, Consts::Sneak_Follower_Token());

            Actor2::Evaluate_Package(actor);
        }
    }

    void Follower_t::Unsneak()
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Actor_Value_Owner_t* values = Actor2::Actor_Value_Owner(actor);
            if (values) {
                values->Set_Actor_Value(Actor_Value_t::SPEED_MULT, MAX_UNSNEAK_SPEED);
            }

            Object_Ref::Untoken(actor, Consts::Sneak_Follower_Token());

            Actor2::Evaluate_Package(actor);
        }
    }

    void Follower_t::Rename(String_t new_name)
    {
        Actor_t* actor = Actor();
        if (actor && Is_Created()) {
            Object_Ref::Rename(actor, new_name);

            Actor2::Evaluate_Package(actor);
        }
    }

}}

namespace doticu_npcp { namespace Party { namespace Follower { namespace Exports {

    Actor_t* Actor(Follower_t* self) FORWARD_POINTER(Actor());
    Int_t ID(Follower_t* self) FORWARD_INT(ID());

    String_t Name(Follower_t* self) FORWARD_STRING(Follower_t::Name());

    void Level(Follower_t* self) FORWARD_VOID(Follower_t::Level());
    void Unlevel(Follower_t* self) FORWARD_VOID(Follower_t::Unlevel());
    void Sneak(Follower_t* self) FORWARD_VOID(Follower_t::Sneak());
    void Unsneak(Follower_t* self) FORWARD_VOID(Follower_t::Unsneak());

    void Rename(Follower_t* self, String_t new_name) FORWARD_VOID(Follower_t::Rename(new_name));

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Follower_t::Class_Name(), Follower_t,      \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("Actor", 0, Actor_t*, Actor);
        ADD_METHOD("ID", 0, Int_t, ID);

        ADD_METHOD("Name", 0, String_t, Name);

        ADD_METHOD("p_Level", 0, void, Level);
        ADD_METHOD("p_Unlevel", 0, void, Unlevel);
        ADD_METHOD("p_Sneak", 0, void, Sneak);
        ADD_METHOD("p_Unsneak", 0, void, Unsneak);

        ADD_METHOD("p_Rename", 1, void, Rename, String_t);

        #undef ADD_METHOD

        return true;
    }

}}}}
