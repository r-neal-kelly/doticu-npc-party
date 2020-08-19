/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "actor_base2.h"
#include "cell.h"
#include "codes.h"
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
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Follower_t::Class_Info()
    {
        static Class_Info_t* object_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(object_info);
        return object_info;
    }

    Variable_t* Follower_t::Variable(String_t variable_name)
    {
        return Variable_t::Fetch(this, Class_Name(), variable_name);
    }

    Variable_t* Follower_t::Actor_Variable() { DEFINE_VARIABLE("p_ref_actor"); }
    Variable_t* Follower_t::Member_Variable() { DEFINE_VARIABLE("p_ref_member"); }
    Variable_t* Follower_t::Horse_Variable() { DEFINE_VARIABLE("p_ref_horse"); }

    Variable_t* Follower_t::Is_Sneak_Variable() { DEFINE_VARIABLE("p_is_sneak"); }
    Variable_t* Follower_t::Is_Saddler_Variable() { DEFINE_VARIABLE("p_is_saddler"); }
    Variable_t* Follower_t::Is_Retreater_Variable() { DEFINE_VARIABLE("p_is_retreater"); }

    Variable_t* Follower_t::Previous_Player_Relationship_Variable() { DEFINE_VARIABLE("p_prev_relationship_rank"); }
    Variable_t* Follower_t::Previous_Waiting_For_Player_Variable() { DEFINE_VARIABLE("p_prev_waiting_for_player"); }
    Variable_t* Follower_t::Previous_Speed_Multiplier_Variable() { DEFINE_VARIABLE("p_prev_speed_mult"); }
    Variable_t* Follower_t::Previous_No_Auto_Bard_Faction_Variable() { DEFINE_VARIABLE("p_prev_faction_bard_no_auto"); }

    Actor_t* Follower_t::Actor()
    {
        NPCP_ASSERT(Is_Filled());
        Actor_t* actor = Actor_Variable()->Actor();
        if (actor == nullptr) {
            actor = Alias_t::Actor();
            NPCP_ASSERT(actor);
            Actor_Variable()->Pack(actor);
        }
        return actor;
    }

    Member_t* Follower_t::Member()
    {
        NPCP_ASSERT(Is_Filled());
        Member_t* member = static_cast<Member_t*>(Member_Variable()->Alias());
        NPCP_ASSERT(member);
        return member;
    }

    Horse_t* Follower_t::Horse()
    {
        NPCP_ASSERT(Is_Filled());
        return static_cast<Horse_t*>(Horse_Variable()->Alias());
    }

    Reference_t* Follower_t::Pack()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Pack();
    }

    Cell_t* Follower_t::Cell()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Cell();
    }

    Int_t Follower_t::Style()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Style();
    }

    Int_t Follower_t::Vitality()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Vitality();
    }

    Int_t Follower_t::Outfit2()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Outfit2();
    }

    Int_t Follower_t::Rating()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Rating();
    }

    String_t Follower_t::Sex()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Sex();
    }

    String_t Follower_t::Race()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Race();
    }

    String_t Follower_t::Base_Name()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Base_Name();
    }

    String_t Follower_t::Reference_Name()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Reference_Name();
    }

    String_t Follower_t::Name()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Name();
    }

    Bool_t Follower_t::Is_Loaded()
    {
        return Is_Filled() && Actor2::Is_Loaded(Actor());
    }

    Bool_t Follower_t::Is_Unloaded()
    {
        return Is_Filled() && Actor2::Is_Unloaded(Actor());
    }

    Bool_t Follower_t::Is_Unique()
    {
        return Is_Filled() && Actor2::Is_Unique(Actor());
    }

    Bool_t Follower_t::Is_Generic()
    {
        return Is_Filled() && Actor2::Is_Generic(Actor());
    }

    Bool_t Follower_t::Is_Original()
    {
        return Is_Filled() && Member()->Is_Original();
    }

    Bool_t Follower_t::Is_Clone()
    {
        return Is_Filled() && Member()->Is_Clone();
    }

    Bool_t Follower_t::Is_Alive()
    {
        return Is_Filled() && Actor2::Is_Alive(Actor());
    }

    Bool_t Follower_t::Is_Dead()
    {
        return Is_Filled() && Actor2::Is_Dead(Actor());
    }

    Bool_t Follower_t::Is_Mobile()
    {
        return Is_Filled() && Member()->Is_Mobile();
    }

    Bool_t Follower_t::Is_Immobile()
    {
        return Is_Filled() && Member()->Is_Immobile();
    }

    Bool_t Follower_t::Is_Settler()
    {
        return Is_Filled() && Member()->Is_Settler();
    }

    Bool_t Follower_t::Isnt_Settler()
    {
        return Is_Filled() && Member()->Isnt_Settler();
    }

    Bool_t Follower_t::Is_Thrall()
    {
        return Is_Filled() && Member()->Is_Thrall();
    }

    Bool_t Follower_t::Isnt_Thrall()
    {
        return Is_Filled() && Member()->Isnt_Thrall();
    }

    Bool_t Follower_t::Is_Paralyzed()
    {
        return Is_Filled() && Member()->Is_Paralyzed();
    }

    Bool_t Follower_t::Isnt_Paralyzed()
    {
        return Is_Filled() && Member()->Isnt_Paralyzed();
    }

    Bool_t Follower_t::Is_Mannequin()
    {
        return Is_Filled() && Member()->Is_Mannequin();
    }

    Bool_t Follower_t::Isnt_Mannequin()
    {
        return Is_Filled() && Member()->Isnt_Mannequin();
    }

    Bool_t Follower_t::Is_Display()
    {
        return Is_Filled() && Member()->Is_Display();
    }

    Bool_t Follower_t::Isnt_Display()
    {
        return Is_Filled() && Member()->Isnt_Display();
    }

    Bool_t Follower_t::Is_Reanimated()
    {
        return Is_Filled() && Member()->Is_Reanimated();
    }

    Bool_t Follower_t::Isnt_Reanimated()
    {
        return Is_Filled() && Member()->Isnt_Reanimated();
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
        return Is_Filled() && Is_Sneak_Variable()->Bool();
    }

    Bool_t Follower_t::Isnt_Sneak()
    {
        return Is_Filled() && !Is_Sneak_Variable()->Bool();
    }

    Bool_t Follower_t::Is_Saddler()
    {
        return Is_Filled() && Is_Saddler_Variable()->Bool();
    }

    Bool_t Follower_t::Isnt_Saddler()
    {
        return Is_Filled() && !Is_Saddler_Variable()->Bool();
    }

    Bool_t Follower_t::Is_Retreater()
    {
        return Is_Filled() && Is_Retreater_Variable()->Bool();
    }

    Bool_t Follower_t::Isnt_Retreater()
    {
        return Is_Filled() && !Is_Retreater_Variable()->Bool();
    }

    Bool_t Follower_t::Is_Near_Player(float radius)
    {
        return Is_Filled() && Object_Ref::Is_Near_Player(Actor(), radius);
    }

    Bool_t Follower_t::Isnt_Near_Player(float radius)
    {
        return Is_Filled() && !Object_Ref::Is_Near_Player(Actor(), radius);
    }

    Bool_t Follower_t::Is_In_Interior_Cell()
    {
        if (Is_Filled()) {
            Cell_t* cell = Cell();
            return cell && Cell::Is_Interior(cell);
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_In_Exterior_Cell()
    {
        if (Is_Filled()) {
            Cell_t* cell = Cell();
            return cell && Cell::Is_Exterior(cell);
        } else {
            return false;
        }
    }

    Bool_t Follower_t::Is_In_Combat()
    {
        return Is_Filled() && Actor()->IsInCombat();
    }

    Bool_t Follower_t::Isnt_In_Combat()
    {
        return Is_Filled() && !Actor()->IsInCombat();
    }

    bool Follower_t::Has_Token(Misc_t* token, Int_t count)
    {
        return Is_Filled() && Object_Ref::Has_Token(Actor(), token, count);
    }

    void Follower_t::Token(Misc_t* token, Int_t count)
    {
        NPCP_ASSERT(Is_Filled());
        Object_Ref::Token(Actor(), token, count);
    }

    void Follower_t::Untoken(Misc_t* token)
    {
        NPCP_ASSERT(Is_Filled());
        Object_Ref::Untoken(Actor(), token);
    }

    void Follower_t::Fill(Member_t* member)
    {
        NPCP_ASSERT(Is_Unfilled());

        struct Callback : public Virtual_Callback_t {
        public:
            Follower_t* self;
            Member_t* member;
            Callback(Follower_t* self, Member_t* member) :
                self(self), member(member)
            {
            }
            void operator()(Variable_t* result)
            {
                self->Create(member);
                Virtual_Machine_t::Self()->Call_Method(self, self->Class_Name(), "f_Register");
            }
        };
        Virtual_Callback_i* callback = new Callback(this, member);

        Alias_t::Fill(member->Actor(), &callback);
    }

    void Follower_t::Unfill()
    {
        NPCP_ASSERT(Is_Filled());

        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "f_Unregister");
        Destroy();
        Alias_t::Unfill(nullptr);
    }

    void Follower_t::Create(Member_t* member)
    {
        Actor_t* actor = member->Actor();

        Actor_Variable()->Pack(actor);
        Member_Variable()->Pack(member);
        Horse_Variable()->None();

        Is_Sneak_Variable()->Bool(false);
        Is_Saddler_Variable()->Bool(false);
        Is_Retreater_Variable()->Bool(false);

        Backup_State(actor);
        Actor2::Stop_If_Playing_Music(actor);

        Enforce_Follower(actor);
        Level();
    }

    void Follower_t::Destroy()
    {
        Actor_t* actor = Actor();

        if (Is_Retreater()) {
            Unretreat();
        }
        if (Is_Saddler()) {
            Unsaddle();
        }
        if (Is_Sneak()) {
            Unsneak();
        }
        Unlevel();
        Enforce_Non_Follower(actor);

        Restore_State(actor);
        Destroy_Horse();

        Previous_No_Auto_Bard_Faction_Variable()->Bool(false);
        Previous_Speed_Multiplier_Variable()->Float(-1.0f);
        Previous_Waiting_For_Player_Variable()->Float(-1.0f);
        Previous_Player_Relationship_Variable()->Int(-1);

        Is_Retreater_Variable()->Bool(false);
        Is_Saddler_Variable()->Bool(false);
        Is_Sneak_Variable()->Bool(false);

        Horse_Variable()->None();
        Member_Variable()->None();
        Actor_Variable()->None();
    }

    void Follower_t::Create_Horse()
    {
        NPCP_ASSERT(!Horse());
        Horses_t::Self()->Add_Horse(this);
        Horse_Variable()->Pack(Horses_t::Self()->From_ID(Followers_t::MAX + ID()));
    }

    void Follower_t::Destroy_Horse()
    {
        if (Horse()) {
            Horses_t::Self()->Remove_Horse(this);
            Horse_Variable()->None();
        }
    }

    void Follower_t::Backup_State(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
        Previous_Waiting_For_Player_Variable()->Float(value_owner->Get_Base_Actor_Value(Actor_Value_t::WAITING_FOR_PLAYER));
        Previous_Speed_Multiplier_Variable()->Float(value_owner->Get_Base_Actor_Value(Actor_Value_t::SPEED_MULT));

        Previous_No_Auto_Bard_Faction_Variable()->Bool(Actor2::Has_Faction(actor, Consts::No_Bard_Singer_Autostart_Faction()));

        class Callback : public Virtual_Callback_t {
        public:
            Variable_t* variable;
            Callback(Variable_t* variable) :
                variable(variable)
            {
            }
            void operator()(Variable_t* result)
            {
                variable->Int(result->Int());
            }
        };
        Virtual_Callback_i* callback = new Callback(Previous_Player_Relationship_Variable());
        Actor2::Relationship_Rank(actor, Player::Actor(), &callback);
    }

    void Follower_t::Restore_State(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Actor2::Relationship_Rank(actor, Player::Actor(), Previous_Player_Relationship_Variable()->Int());

        if (Previous_No_Auto_Bard_Faction_Variable()->Bool()) {
            Actor2::Add_Faction(actor, Consts::No_Bard_Singer_Autostart_Faction());
        }

        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
        value_owner->Set_Actor_Value(Actor_Value_t::SPEED_MULT, Previous_Speed_Multiplier_Variable()->Float());
        value_owner->Set_Actor_Value(Actor_Value_t::WAITING_FOR_PLAYER, Previous_Waiting_For_Player_Variable()->Float());
    }

    void Follower_t::Enforce_Follower(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());

        Object_Ref::Token(actor, Consts::Follower_Token(), ID() + 1);
        
        Actor2::Add_Faction(actor, Consts::No_Bard_Singer_Autostart_Faction());

        Actor_Value_Owner_t* value_owner = Actor2::Actor_Value_Owner(actor);
        value_owner->Set_Actor_Value(Actor_Value_t::WAITING_FOR_PLAYER, 0.0f);
        value_owner->Set_Actor_Value(Actor_Value_t::SPEED_MULT, MAX_UNSNEAK_SPEED);

        Actor2::Ignore_Friendly_Hits(actor);
        Actor2::Hide_From_Stealth_Eye(actor);

        class Callback : public Virtual_Callback_t {
        public:
            Actor_t* actor;
            Callback(Actor_t* actor) :
                actor(actor)
            {
            }
            void operator()(Variable_t* result)
            {
                Actor2::Evaluate_Package(actor);
            }
        };
        Virtual_Callback_i* callback = new Callback(actor);
        Actor2::Relationship_Rank(actor, Player::Actor(), 3, &callback);
    }

    void Follower_t::Enforce_Non_Follower(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());

        Actor2::Show_On_Stealth_Eye(actor);
        Actor2::Notice_Friendly_Hits(actor);

        Actor2::Remove_Faction(actor, Consts::No_Bard_Singer_Autostart_Faction());

        Object_Ref::Untoken(actor, Consts::Follower_Token());

        Actor2::Evaluate_Package(actor);
    }

    void Follower_t::Level()
    {
        NPCP_ASSERT(Is_Filled());

        Actor_t* player_actor = *g_thePlayer;
        Actor_t* follower_actor = Actor();
        if (player_actor && follower_actor && Is_Filled()) {
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
                    if (follower_style == CODES::STYLE::WARRIOR) {
                        health += player_level * 4; // find a better equation
                        Mod_Strength(+player_level_modded);
                        Mod_Intelligence(-player_level_modded);
                        Mod_Dexterity(-player_level_modded);
                    } else if (follower_style == CODES::STYLE::MAGE) {
                        magicka += player_level * 4; // find a better equation
                        Mod_Strength(-player_level_modded);
                        Mod_Intelligence(+player_level_modded);
                        Mod_Dexterity(-player_level_modded);
                    } else if (follower_style == CODES::STYLE::ARCHER) {
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
        NPCP_ASSERT(Is_Filled());

        Actor_t* follower_actor = Actor();
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

    Int_t Follower_t::Sneak()
    {
        if (Is_Filled()) {
            if (Isnt_Sneak()) {
                Is_Sneak_Variable()->Bool(true);

                Actor_t* actor = Actor();
                Enforce_Sneak(actor);
                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::FOLLOWER;
        }
    }

    void Follower_t::Enforce_Sneak(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(Is_Sneak());

        Object_Ref::Token(actor, Consts::Sneak_Follower_Token());

        Actor_Value_Owner_t* values = Actor2::Actor_Value_Owner(actor);
        values->Set_Actor_Value(Actor_Value_t::SPEED_MULT, MAX_SNEAK_SPEED);
    }

    Int_t Follower_t::Unsneak()
    {
        if (Is_Filled()) {
            if (Is_Sneak()) {
                Is_Sneak_Variable()->Bool(false);

                Actor_t* actor = Actor();
                Enforce_Non_Sneak(actor);
                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::FOLLOWER;
        }
    }

    void Follower_t::Enforce_Non_Sneak(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(Isnt_Sneak());

        Object_Ref::Untoken(actor, Consts::Sneak_Follower_Token());

        Actor_Value_Owner_t* values = Actor2::Actor_Value_Owner(actor);
        values->Set_Actor_Value(Actor_Value_t::SPEED_MULT, MAX_UNSNEAK_SPEED);
    }

    Int_t Follower_t::Saddle()
    {
        if (Is_Filled()) {
            if (Isnt_Saddler()) {
                if (Is_In_Exterior_Cell()) {
                    Is_Saddler_Variable()->Bool(true);

                    Actor_t* actor = Actor();
                    Enforce_Saddler(actor);
                    Actor2::Evaluate_Package(actor);

                    return CODES::SUCCESS;
                } else {
                    return CODES::INTERIOR;
                }
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::FOLLOWER;
        }
    }

    void Follower_t::Enforce_Saddler(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(Is_Saddler());

        if (Player::Is_In_Exterior_Cell()) {
            Object_Ref::Token(actor, Consts::Saddler_Token());

            Horse_t* horse = Horse();
            if (horse) {
                horse->Groom();
            } else {
                Create_Horse();
            }
        } else {
            Enforce_Non_Saddler(actor);
        }
    }

    Int_t Follower_t::Unsaddle()
    {
        if (Is_Filled()) {
            if (Is_Saddler()) {
                Is_Saddler_Variable()->Bool(false);

                Actor_t* actor = Actor();
                Enforce_Non_Saddler(actor);
                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::FOLLOWER;
        }
    }

    void Follower_t::Enforce_Non_Saddler(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());

        Object_Ref::Untoken(actor, Consts::Saddler_Token());

        if (Actor2::Is_On_Mount(actor)) {
            Actor2::Dismount(actor);
        }

        Horse_t* horse = Horse();
        if (horse) {
            horse->Ungroom();
        }
    }

    Int_t Follower_t::Retreat()
    {
        if (Is_Filled()) {
            if (Isnt_Retreater()) {
                Is_Retreater_Variable()->Bool(true);

                Actor_t* actor = Actor();
                Enforce_Retreater(actor);
                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::FOLLOWER;
        }
    }

    void Follower_t::Enforce_Retreater(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(Is_Retreater());

        if (Is_Alive()) {
            if (Actor2::Is_Sneaking(Player::Actor())) {
                Object_Ref::Token(actor, Consts::Retreater_Token());

                if (!Actor2::Has_Magic_Effect(actor, Consts::Retreat_Magic_Effect())) {
                    Actor2::Add_Spell(actor, Consts::Retreat_Ability_Spell());
                }

                Actor2::Pacify(actor);
            } else {
                Unretreat();
            }
        }
    }

    Int_t Follower_t::Unretreat()
    {
        if (Is_Filled()) {
            if (Is_Retreater()) {
                Is_Retreater_Variable()->Bool(false);

                Actor_t* actor = Actor();
                Enforce_Non_Retreater(actor);
                Actor2::Evaluate_Package(actor);

                return CODES::SUCCESS;
            } else {
                return CODES::IS;
            }
        } else {
            return CODES::FOLLOWER;
        }
    }

    void Follower_t::Enforce_Non_Retreater(Actor_t* actor)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(Isnt_Retreater());

        Object_Ref::Untoken(actor, Consts::Retreater_Token());
        Actor2::Remove_Spell(actor, Consts::Retreat_Ability_Spell());
    }

    void Follower_t::Enforce()
    {
        if (Is_Filled() && Is_Alive()) {
            Actor_t* actor = Actor();

            Enforce_Follower(actor); // Backup should be Follow and Restore Unfollow

            Level();

            if (Is_Sneak()) {
                Enforce_Sneak(actor);
            } else {
                Enforce_Non_Sneak(actor);
            }

            if (Is_Saddler()) {
                Enforce_Saddler(actor);
            } else {
                Enforce_Non_Saddler(actor);
            }

            if (Is_Retreater()) {
                Enforce_Retreater(actor);
            } else {
                Enforce_Non_Retreater(actor);
            }
        }
    }
    
    void Follower_t::Summon(Reference_t* origin, Float_t radius, Float_t degree)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(origin);

        Actor_t* follower_actor = Actor();
        if (Object_Ref::Is_In_Exterior_Cell(origin) && Is_Saddler()) {
            Horse_t* follower_horse = Horse();
            Actor_t* follower_horse_actor = follower_horse ? follower_horse->Actor() : nullptr;
            if (follower_horse_actor) {
                Actor2::Move_To_Orbit(follower_horse_actor, origin, radius * 4, degree + 12);
                Actor2::Move_To_Orbit(follower_actor, origin, radius * 3.5, degree);
                Enforce_Saddler(follower_actor);
            } else {
                Actor2::Move_To_Orbit(follower_actor, origin, radius, degree);
            }
        } else {
            Actor2::Move_To_Orbit(follower_actor, origin, radius, degree);
        }
    }

    Int_t Follower_t::Summon(Float_t radius, Float_t degree)
    {
        if (Is_Filled()) {
            NPCP_ASSERT(Isnt_Mannequin());
            Summon(Player::Actor(), radius, degree);
            Member()->Enforce();
            return CODES::SUCCESS;
        } else {
            return CODES::FOLLOWER;
        }
    }

    Int_t Follower_t::Summon_Ahead(Float_t radius)
    {
        return Summon(radius, 0.0f);
    }

    Int_t Follower_t::Summon_Behind(Float_t radius)
    {
        return Summon(radius, 180.0f);
    }

    Int_t Follower_t::Mobilize()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Mobilize();
    }

    Int_t Follower_t::Immobilize()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Immobilize();
    }

    Int_t Follower_t::Settle()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Settle();
    }

    Int_t Follower_t::Resettle()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Resettle();
    }

    Int_t Follower_t::Unsettle()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Unsettle();
    }

    Int_t Follower_t::Enthrall()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Enthrall();
    }

    Int_t Follower_t::Unthrall()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Unthrall();
    }

    Int_t Follower_t::Paralyze()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Paralyze();
    }

    Int_t Follower_t::Unparalyze()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Unparalyze();
    }

    Int_t Follower_t::Stash()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Stash();
    }

    Int_t Follower_t::Resurrect()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Resurrect();
    }

    Int_t Follower_t::Kill()
    {
        NPCP_ASSERT(Is_Filled());
        return Member()->Kill();
    }

    void Follower_t::Catch_Up()
    {
        // for the last three we are asking if they have ai essentially
        if (Is_Filled() && Is_Mobile() && Isnt_Paralyzed() && Isnt_Mannequin() && Isnt_Display()) {
            if (Player::Is_In_Interior_Cell() || Isnt_Saddler()) {
                if (Isnt_Near_Player()) {
                    Summon(Player::Actor(), 256.0f, 180.0f);
                }
            } else {
                Horse_t* horse = Horse();
                if (horse) {
                    Actor_t* horse_actor = horse->Actor();
                    if (horse_actor && !Object_Ref::Is_Near_Player(horse_actor, 10240.0f)) {
                        if (Player::Is_On_Mount()) {
                            Summon(Player::Actor(), 1024.0f, 180.0f);
                        } else {
                            Summon(Player::Actor(), 256.0f, 180.0f);
                        }
                        Enforce_Saddler(Actor());
                    }
                }
            }
        }
    }

    void Follower_t::Rename(String_t new_name)
    {
        NPCP_ASSERT(Is_Filled());
        NPCP_ASSERT(new_name);

        Member()->Rename(new_name);
    }

}}

namespace doticu_npcp { namespace Party { namespace Follower { namespace Exports {

    Int_t ID(Follower_t* self)              FORWARD_INT(Follower_t::ID());
    Actor_t* Actor(Follower_t* self)        FORWARD_POINTER(Follower_t::Actor());
    Member_t* Member(Follower_t* self)      FORWARD_POINTER(Follower_t::Member());
    String_t Name(Follower_t* self)         FORWARD_STRING(Follower_t::Name());

    Bool_t Is_Filled(Follower_t* self)      FORWARD_BOOL(Follower_t::Is_Filled());
    Bool_t Is_Unfilled(Follower_t* self)    FORWARD_BOOL(Follower_t::Is_Unfilled());
    Bool_t Is_Mobile(Follower_t* self)      FORWARD_BOOL(Follower_t::Is_Mobile());
    Bool_t Is_Immobile(Follower_t* self)    FORWARD_BOOL(Follower_t::Is_Immobile());
    Bool_t Is_Sneak(Follower_t* self)       FORWARD_BOOL(Follower_t::Is_Sneak());
    Bool_t Isnt_Sneak(Follower_t* self)     FORWARD_BOOL(Follower_t::Isnt_Sneak());
    Bool_t Is_Saddler(Follower_t* self)     FORWARD_BOOL(Follower_t::Is_Saddler());
    Bool_t Isnt_Saddler(Follower_t* self)   FORWARD_BOOL(Follower_t::Isnt_Saddler());
    Bool_t Is_Retreater(Follower_t* self)   FORWARD_BOOL(Follower_t::Is_Retreater());
    Bool_t Isnt_Retreater(Follower_t* self) FORWARD_BOOL(Follower_t::Isnt_Retreater());

    Int_t Sneak(Follower_t* self)           FORWARD_INT(Follower_t::Sneak());
    Int_t Unsneak(Follower_t* self)         FORWARD_INT(Follower_t::Unsneak());
    Int_t Saddle(Follower_t* self)          FORWARD_INT(Follower_t::Saddle());
    Int_t Unsaddle(Follower_t* self)        FORWARD_INT(Follower_t::Unsaddle());
    Int_t Retreat(Follower_t* self)         FORWARD_INT(Follower_t::Retreat());
    Int_t Unretreat(Follower_t* self)       FORWARD_INT(Follower_t::Unretreat());

    Bool_t Register(Registry_t* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Follower_t::Class_Name(), Follower_t,      \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_METHOD("ID", 0, Int_t, ID);
        ADD_METHOD("Actor", 0, Actor_t*, Actor);
        ADD_METHOD("Member", 0, Member_t*, Member);
        ADD_METHOD("Name", 0, String_t, Name);

        ADD_METHOD("Is_Filled", 0, Bool_t, Is_Filled);
        ADD_METHOD("Is_Unfilled", 0, Bool_t, Is_Unfilled);
        ADD_METHOD("Is_Mobile", 0, Bool_t, Is_Mobile);
        ADD_METHOD("Is_Immobile", 0, Bool_t, Is_Immobile);
        ADD_METHOD("Is_Sneak", 0, Bool_t, Is_Sneak);
        ADD_METHOD("Isnt_Sneak", 0, Bool_t, Isnt_Sneak);
        ADD_METHOD("Is_Saddler", 0, Bool_t, Is_Saddler);
        ADD_METHOD("Isnt_Saddler", 0, Bool_t, Isnt_Saddler);
        ADD_METHOD("Is_Retreater", 0, Bool_t, Is_Retreater);
        ADD_METHOD("Isnt_Retreater", 0, Bool_t, Isnt_Retreater);

        ADD_METHOD("Sneak", 0, Int_t, Sneak);
        ADD_METHOD("Unsneak", 0, Int_t, Unsneak);
        ADD_METHOD("Saddle", 0, Int_t, Saddle);
        ADD_METHOD("Unsaddle", 0, Int_t, Unsaddle);
        ADD_METHOD("Retreat", 0, Int_t, Retreat);
        ADD_METHOD("Unretreat", 0, Int_t, Unretreat);

        #undef ADD_METHOD

        return true;
    }

}}}}
