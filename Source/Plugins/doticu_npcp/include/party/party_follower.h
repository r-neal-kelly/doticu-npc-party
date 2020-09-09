/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"
#include "party/party_followers.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Member_t;
    class Horse_t;

    class Follower_t : public Alias_t {
    public:
        static constexpr Float_t MAX_SNEAK_SPEED = 160.0f;
        static constexpr Float_t MAX_UNSNEAK_SPEED = 130.0f;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Actor_Variable(); // Actor_t
        Variable_t* Member_Variable(); // Member_t
        Variable_t* Horse_Variable(); // Horse_t

        Variable_t* Is_Locked_Variable(); // Bool_t
        Variable_t* Is_Sneak_Variable(); // Bool_t
        Variable_t* Is_Saddler_Variable(); // Bool_t
        Variable_t* Is_Retreater_Variable(); // Bool_t

        Variable_t* Previous_Player_Relationship_Variable(); // Int_t
        Variable_t* Previous_Waiting_For_Player_Variable(); // Float_t
        Variable_t* Previous_Speed_Multiplier_Variable(); // Float_t
        Variable_t* Previous_No_Auto_Bard_Faction_Variable(); // Bool_t

        Actor_t* Actor();
        Member_t* Member();
        Horse_t* Horse();
        Reference_t* Pack();
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

        Bool_t Is_Locked();
        Bool_t Is_Unlocked();
        Bool_t Is_Ready();
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
        Bool_t Is_Near_Player(float radius = 4096.0f);
        Bool_t Isnt_Near_Player(float radius = 4096.0f);
        Bool_t Is_In_Interior_Cell();
        Bool_t Is_In_Exterior_Cell();
        Bool_t Is_In_Combat();
        Bool_t Isnt_In_Combat();

        bool Has_Token(Misc_t* token, Int_t count = 1);
        void Token(Misc_t* token, Int_t count = 1);
        void Untoken(Misc_t* token);

        void Lock(Callback_t<>* on_lock, Float_t interval = 0.2f, Float_t limit = 10.0f);
        void Unlock();
        void Fill(Member_t* member, Followers_t::Add_Callback_i** add_callback);
        void Unfill(Callback_t<Int_t, Member_t*>** callback);
        void Relinquish(Callback_t<Int_t, Member_t*>* user_callback);
        void Create(Member_t* member);
        void Destroy(Callback_t<>** callback);
        void Backup_State(Actor_t* actor);
        void Restore_State(Actor_t* actor);

        void Enforce_Follower(Actor_t* actor);
        void Enforce_Non_Follower(Actor_t* actor);
        void Level();
        void Unlevel();

        Int_t Sneak();
        void Enforce_Sneak(Actor_t* actor);
        Int_t Unsneak();
        void Enforce_Non_Sneak(Actor_t* actor);

        void Saddle(Callback_t<Int_t, Follower_t*>** callback);
        void Enforce_Saddler(Actor_t* actor);
        void Unsaddle(Callback_t<Int_t, Follower_t*>** callback);
        void Enforce_Non_Saddler(Actor_t* actor);

        Int_t Retreat();
        void Enforce_Retreater(Actor_t* actor);
        Int_t Unretreat();
        void Enforce_Non_Retreater(Actor_t* actor);

        void Enforce();

        void Summon(Reference_t* origin, Float_t radius = 140.0f, Float_t degree = 0.0f);
        Int_t Summon(Float_t radius = 140.0f, Float_t degree = 0.0f);
        Int_t Summon_Ahead(Float_t radius = 140.0f);
        Int_t Summon_Behind(Float_t radius = 140.0f);

        Int_t Mobilize();
        Int_t Immobilize();
        Int_t Settle();
        Int_t Resettle();
        Int_t Unsettle();
        Int_t Enthrall();
        Int_t Unthrall();
        Int_t Paralyze();
        Int_t Unparalyze();
        Int_t Stash();
        Int_t Resurrect();
        Int_t Kill();

        void Catch_Up();
        void Rename(String_t new_name);

    private:
        void Relinquish_Impl(Callback_t<Int_t, Member_t*>* user_callback);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
