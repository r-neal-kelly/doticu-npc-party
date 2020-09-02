/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"
#include "party/party_members.h"

namespace doticu_npcp { namespace Papyrus {

    class Outfit2_t;

}}

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Follower_t;

    class Member_t : public Alias_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Actor_Variable();
        Variable_t* Pack_Variable();
        Variable_t* Mannequin_Marker_Variable();
        Variable_t* Display_Marker_Variable();
        Variable_t* Undisplay_Marker_Variable();
        Variable_t* Vanilla_Outfit_Variable();
        Variable_t* Default_Outfit_Variable();

        Variable_t* Member_Outfit2_Variable();
        Variable_t* Immobile_Outfit2_Variable();
        Variable_t* Settler_Outfit2_Variable();
        Variable_t* Thrall_Outfit2_Variable();
        Variable_t* Follower_Outfit2_Variable();
        Variable_t* Vanilla_Outfit2_Variable();
        Variable_t* Default_Outfit2_Variable();
        Variable_t* Current_Outfit2_Variable();
        Variable_t* Backup_Outfit2_Variable();

        Variable_t* Is_Clone_Variable();
        Variable_t* Is_Immobile_Variable();
        Variable_t* Is_Settler_Variable();
        Variable_t* Is_Thrall_Variable();
        Variable_t* Is_Paralyzed_Variable();
        Variable_t* Is_Mannequin_Variable();
        Variable_t* Is_Display_Variable();
        Variable_t* Is_Reanimated_Variable();
        Variable_t* Do_Skip_On_Load_Variable();

        Variable_t* Style_Variable();
        Variable_t* Vitality_Variable();
        Variable_t* Outfit2_Variable();
        Variable_t* Rating_Variable();

        Variable_t* Name_Variable();

        Variable_t* Previous_Factions_Variable();
        Variable_t* Previous_Crime_Faction_Variable();
        Variable_t* Previous_Potential_Follower_Faction_Variable();
        Variable_t* Previous_No_Body_Cleanup_Faction_Variable();
        Variable_t* Previous_Aggression_Variable();
        Variable_t* Previous_Confidence_Variable();
        Variable_t* Previous_Assistance_Variable();
        Variable_t* Previous_Morality_Variable();

        Actor_t* Actor();
        Follower_t* Follower();
        Reference_t* Pack();
        Reference_t* Settler_Marker();
        Reference_t* Mannequin_Marker();
        Reference_t* Display_Marker();
        Reference_t* Undisplay_Marker();
        Cell_t* Cell();
        Int_t Style();
        Int_t Vitality();
        Int_t Outfit2();
        Int_t Rating();
        Int_t Relationship_Rank();
        String_t Sex();
        String_t Race();
        String_t Base_Name();
        String_t Reference_Name();
        String_t Name();
        String_t Rating_Stars();
        String_t Relationship_Rank_String();

        Outfit_t* Vanilla_Outfit();
        Outfit_t* Default_Outfit();
        Outfit2_t* Member_Outfit2();
        Outfit2_t* Immobile_Outfit2();
        Outfit2_t* Settler_Outfit2();
        Outfit2_t* Thrall_Outfit2();
        Outfit2_t* Follower_Outfit2();
        Outfit2_t* Vanilla_Outfit2();
        Outfit2_t* Default_Outfit2();
        Outfit2_t* Current_Outfit2();
        Outfit2_t* Backup_Outfit2();

        Bool_t Is_Ready();
        Bool_t Is_Unready();
        Bool_t Is_Loaded();
        Bool_t Is_Unloaded();
        Bool_t Is_Unique();
        Bool_t Is_Generic();
        Bool_t Is_Original();
        Bool_t Is_Clone();
        Bool_t Is_Alive();
        Bool_t Is_Dead();
        Bool_t Is_Mobile();
        Bool_t Is_Immobile();
        Bool_t Is_Settler();
        Bool_t Isnt_Settler();
        Bool_t Is_Thrall();
        Bool_t Isnt_Thrall();
        Bool_t Is_Paralyzed();
        Bool_t Isnt_Paralyzed();
        Bool_t Is_Mannequin();
        Bool_t Isnt_Mannequin();
        Bool_t Is_Display();
        Bool_t Isnt_Display();
        Bool_t Is_Reanimated();
        Bool_t Isnt_Reanimated();
        Bool_t Is_Follower();
        Bool_t Isnt_Follower();
        Bool_t Is_Sneak();
        Bool_t Isnt_Sneak();
        Bool_t Is_Saddler();
        Bool_t Isnt_Saddler();
        Bool_t Is_Retreater();
        Bool_t Isnt_Retreater();

        Bool_t Is_Loaded_Unsafe();
        Bool_t Is_Unloaded_Unsafe();
        Bool_t Is_Unique_Unsafe();
        Bool_t Is_Generic_Unsafe();
        Bool_t Is_Original_Unsafe();
        Bool_t Is_Clone_Unsafe();
        Bool_t Is_Alive_Unsafe();
        Bool_t Is_Dead_Unsafe();
        Bool_t Is_Mobile_Unsafe();
        Bool_t Is_Immobile_Unsafe();
        Bool_t Is_Settler_Unsafe();
        Bool_t Isnt_Settler_Unsafe();
        Bool_t Is_Thrall_Unsafe();
        Bool_t Isnt_Thrall_Unsafe();
        Bool_t Is_Paralyzed_Unsafe();
        Bool_t Isnt_Paralyzed_Unsafe();
        Bool_t Is_Mannequin_Unsafe();
        Bool_t Isnt_Mannequin_Unsafe();
        Bool_t Is_Display_Unsafe();
        Bool_t Isnt_Display_Unsafe();
        Bool_t Is_Reanimated_Unsafe();
        Bool_t Isnt_Reanimated_Unsafe();
        Bool_t Is_Follower_Unsafe();
        Bool_t Isnt_Follower_Unsafe();
        Bool_t Is_Sneak_Unsafe();
        Bool_t Isnt_Sneak_Unsafe();
        Bool_t Is_Saddler_Unsafe();
        Bool_t Isnt_Saddler_Unsafe();
        Bool_t Is_Retreater_Unsafe();
        Bool_t Isnt_Retreater_Unsafe();

        Bool_t Has_Same_Base(Actor_t* other_actor);
        Bool_t Has_Same_Head(Actor_t* other_actor);

        Bool_t Has_Same_Base_Unsafe(Actor_t* other_actor);
        Bool_t Has_Same_Head_Unsafe(Actor_t* other_actor);

        Bool_t Should_Unclone();

        Bool_t Is_In_Location(Location_t* location);

        void On_Load();
        void On_Death(Actor_t* killer);
        void On_Activate(Reference_t* activator);
        void On_Combat_State_Changed(Actor_t* target, Int_t combat_code);
        void On_Hit(Reference_t* attacker,
                    Form_t* tool,
                    Projectile_Base_t* projectile,
                    Bool_t is_power,
                    Bool_t is_sneak,
                    Bool_t is_bash,
                    Bool_t is_blocked);

        void Fill(Actor_t* actor, Bool_t is_clone, Members_t::Add_Callback_i** add_callback);
        void Unfill();
        void Create(Actor_t* actor, Bool_t is_clone);
        void Destroy();
        void Destroy_Containers();
        void Destroy_Outfit2s();
        void Backup_State(Actor_t* actor);
        void Restore_State(Actor_t* actor);

        void Enforce_Member(Actor_t* actor);
        void Destroy_Member(Actor_t* actor);
        void Enforce_Non_Member(Actor_t* actor);

        Int_t Mobilize();
        void Destroy_Immobile(Actor_t* actor);
        void Enforce_Mobile(Actor_t* actor);
        Int_t Immobilize();
        void Enforce_Immobile(Actor_t* actor);

        Int_t Settle();
        void Enforce_Settler(Actor_t* actor);
        Int_t Resettle();
        Int_t Unsettle();
        void Destroy_Settler(Actor_t* actor);
        void Enforce_Non_Settler(Actor_t* actor);

        Int_t Enthrall();
        void Enforce_Thrall(Actor_t* actor);
        Int_t Unthrall();
        void Destroy_Thrall(Actor_t* actor);
        void Enforce_Non_Thrall(Actor_t* actor);

        Int_t Paralyze();
        void Enforce_Paralyzed(Actor_t* actor);
        Int_t Unparalyze();
        void Destroy_Paralyzed(Actor_t* actor);
        void Enforce_Non_Paralyzed(Actor_t* actor);

        Int_t Mannequinize(Reference_t* marker = nullptr);
        void Enforce_Mannequin(Actor_t* actor, Reference_t* marker);
        Int_t Unmannequinize();
        void Destroy_Mannequin(Actor_t* actor);
        void Enforce_Non_Mannequin(Actor_t* actor);

        Int_t Display(Reference_t* origin, Float_t radius = 140.0f, Float_t degree = 0.0f);
        void Create_Display(Actor_t* actor, Reference_t* origin, Float_t radius, Float_t degree);
        void Enforce_Display(Actor_t* actor, Reference_t* display_marker);
        Int_t Undisplay();
        void Destroy_Display(Actor_t* actor);
        void Enforce_Non_Display(Actor_t* actor);

        Int_t Reanimate();
        void Enforce_Reanimated(Actor_t* actor);
        Int_t Deanimate();
        void Destroy_Reanimated(Actor_t* actor);
        void Enforce_Non_Reanimated(Actor_t* actor);

        Int_t Unmember();
        Int_t Unclone();

        Int_t Stylize(Int_t style);
        Int_t Stylize_Default();
        Int_t Stylize_Warrior();
        Int_t Stylize_Mage();
        Int_t Stylize_Archer();
        Int_t Stylize_Coward();
        void Enforce_Style(Actor_t* actor);
        void Enforce_Default_Style(Actor_t* actor);
        void Enforce_Warrior_Style(Actor_t* actor);
        void Enforce_Mage_Style(Actor_t* actor);
        void Enforce_Archer_Style(Actor_t* actor);
        void Enforce_Coward_Style(Actor_t* actor);
        Int_t Unstylize();

        Int_t Vitalize(Int_t vitality);
        Int_t Vitalize_Mortal();
        Int_t Vitalize_Protected();
        Int_t Vitalize_Essential();
        Int_t Vitalize_Invulnerable();
        void Enforce_Vitality(Actor_t* actor);
        void Enforce_Mortal_Vitality(Actor_t* actor);
        void Enforce_Protected_Vitality(Actor_t* actor);
        void Enforce_Essential_Vitality(Actor_t* actor);
        void Enforce_Invulnerable_Vitality(Actor_t* actor);
        Int_t Unvitalize();

        void Change_Outfit1(Outfit_t* outfit);
        Int_t Change_Outfit2(Int_t outfit2_code);
        Int_t Change_Member_Outfit2();
        Int_t Change_Immobile_Outfit2();
        Int_t Change_Settler_Outfit2();
        Int_t Change_Thrall_Outfit2();
        Int_t Change_Follower_Outfit2();
        Int_t Change_Vanilla_Outfit2();
        Int_t Change_Default_Outfit2();
        Int_t Change_Current_Outfit2();
        void Update_Outfit2(Int_t outfit2_code, Bool_t do_cache_outfit1 = false);
        void Open_Outfit2();
        void Enforce_Outfit2(Actor_t* actor);

        Int_t Rate(Int_t rating);

        Int_t Rename(String_t new_name);
        void Enforce_Name(Actor_t* actor, String_t name);

        void Enforce();

        void Summon(Reference_t* origin, Float_t radius = 140.0f, Float_t degree = 0.0f);
        Int_t Summon(Float_t radius = 140.0f, Float_t degree = 0.0f);
        Int_t Summon_Ahead(Float_t radius = 140.0f);
        Int_t Summon_Behind(Float_t radius = 140.0f);
        Int_t Goto(Int_t radius = 140.0f, Int_t degree = 0.0f);

        Int_t Open_Pack();
        Int_t Stash();
        Int_t Resurrect();
        Int_t Kill();
        void Enforce_Kill(Actor_t* actor);

        Int_t Unfollow();

        void Level();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
