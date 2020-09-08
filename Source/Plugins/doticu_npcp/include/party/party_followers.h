/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "papyrus.h"

#include "party/party_aliases.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Member_t;
    class Follower_t;

    class Followers_t : public Aliases_t {
    public:
        static constexpr size_t MAX = Consts::MAX_FOLLOWERS;
        static constexpr size_t HALF = MAX / 2;
        static constexpr size_t BEGIN = 0;
        static constexpr size_t END = BEGIN + MAX;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Followers_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Range_t<UInt64> Indices();
        Range_t<Follower_t**> Aliases();

        Follower_t* From_ID(Int_t unique_id);
        Follower_t* From_Actor(Actor_t* actor);
        Follower_t* From_Unfilled();
        Follower_t* From_Horse_Actor(Actor_t* actor);

        Bool_t Has_Space();
        Bool_t Hasnt_Space();
        Bool_t Has_Actor(Actor_t* actor);
        Bool_t Hasnt_Actor(Actor_t* actor);
        Bool_t Are_In_Combat();

        Int_t Max();
        Int_t Count_Filled();
        Int_t Count_Unfilled();
        Int_t Count_Loaded();
        Int_t Count_Unloaded();
        Int_t Count_Unique();
        Int_t Count_Generic();
        Int_t Count_Alive();
        Int_t Count_Dead();
        Int_t Count_Originals();
        Int_t Count_Clones();
        Int_t Count_Mobile();
        Int_t Count_Immobile();
        Int_t Count_Settlers();
        Int_t Count_Non_Settlers();
        Int_t Count_Thralls();
        Int_t Count_Non_Thralls();
        Int_t Count_Paralyzed();
        Int_t Count_Non_Paralyzed();
        Int_t Count_Mannequins();
        Int_t Count_Non_Mannequins();
        Int_t Count_Reanimated();
        Int_t Count_Non_Reanimated();
        Int_t Count_Followers();
        Int_t Count_Non_Followers();
        Int_t Count_Sneaks();
        Int_t Count_Non_Sneaks();
        Int_t Count_Saddlers();
        Int_t Count_Non_Saddlers();
        Int_t Count_Retreaters();
        Int_t Count_Non_Retreaters();

        Vector_t<Follower_t*> All();
        Vector_t<Follower_t*> Filled();
        Vector_t<Follower_t*> Unfilled();
        Vector_t<Follower_t*> Loaded();
        Vector_t<Follower_t*> Unloaded();
        Vector_t<Follower_t*> Unique();
        Vector_t<Follower_t*> Generic();
        Vector_t<Follower_t*> Alive();
        Vector_t<Follower_t*> Dead();
        Vector_t<Follower_t*> Originals();
        Vector_t<Follower_t*> Clones();
        Vector_t<Follower_t*> Mobile();
        Vector_t<Follower_t*> Immobile();
        Vector_t<Follower_t*> Settlers();
        Vector_t<Follower_t*> Non_Settlers();
        Vector_t<Follower_t*> Thralls();
        Vector_t<Follower_t*> Non_Thralls();
        Vector_t<Follower_t*> Paralyzed();
        Vector_t<Follower_t*> Non_Paralyzed();
        Vector_t<Follower_t*> Mannequins();
        Vector_t<Follower_t*> Non_Mannequins();
        Vector_t<Follower_t*> Reanimated();
        Vector_t<Follower_t*> Non_Reanimated();
        Vector_t<Follower_t*> Followers();
        Vector_t<Follower_t*> Non_Followers();
        Vector_t<Follower_t*> Sneaks();
        Vector_t<Follower_t*> Non_Sneaks();
        Vector_t<Follower_t*> Saddlers();
        Vector_t<Follower_t*> Non_Saddlers();
        Vector_t<Follower_t*> Retreaters();
        Vector_t<Follower_t*> Non_Retreaters();

        Vector_t<Follower_t*> Sort(Vector_t<Follower_t*> members);
        Vector_t<Follower_t*> Sort_Filled(Int_t begin = 0, Int_t end = -1);

        Bool_t Can_Actor_Follow(Actor_t* actor);
        struct Add_Callback_i {
            virtual ~Add_Callback_i() = default;
            virtual void operator()(Int_t code, Follower_t* follower) = 0;
        };
        void Add_Follower(Member_t* member, Add_Callback_i** add_callback);
        void Remove_Follower(Member_t* member, Callback_t<Int_t, Member_t*>** callback);
        void Relinquish_Follower(Member_t* member, Callback_t<Int_t, Member_t*>* user_callback);

        Int_t Enforce();
        Int_t Resurrect();
        Int_t Mobilize();
        Int_t Immobilize();
        Int_t Settle();
        Int_t Resettle();
        Int_t Unsettle();
        Int_t Enthrall();
        Int_t Unthrall();
        Int_t Paralyze();
        Int_t Unparalyze();
        Int_t Sneak();
        Int_t Unsneak();
        Int_t Saddle();
        Int_t Unsaddle();
        Int_t Retreat();
        Int_t Unretreat();
        Int_t Unfollow();
        Int_t Unmember();
        Int_t Level();
        Int_t Unlevel();

        void Summon(Vector_t<Follower_t*> followers, float radius = 140.0, float degree = 0.0, float interval = 19.0);
        Int_t Summon_Filled(float radius = 140.0, float degree = 0.0, float interval = 19.0);
        Int_t Summon_Mobile(float radius = 140.0, float degree = 0.0, float interval = 19.0);
        Int_t Summon_Immobile(float radius = 140.0, float degree = 0.0, float interval = 19.0);

        Int_t Catch_Up();
        Int_t Stash();

        Vector_t<Follower_t*> Filter(Vector_t<String_t>* strings = nullptr,
                                     Vector_t<Int_t>* ints = nullptr,
                                     Int_t flags_1 = 0,
                                     Int_t flags_2 = 0);

        public:
            static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
