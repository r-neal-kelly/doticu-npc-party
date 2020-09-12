/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "consts.h"
#include "papyrus.h"

#include "party/party_aliases.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Member_t;

    class Members_t : public Aliases_t {
    public:
        static constexpr size_t MAX = Consts::MAX_MEMBERS;
        static constexpr size_t HALF = MAX / 2;
        static constexpr size_t BEGIN = 0;
        static constexpr size_t END = BEGIN + MAX;

        static constexpr float DEFAULT_DISPLAY_RADIUS = 140.0f;
        static constexpr float DEFAULT_DISPLAY_DEGREE = 0.0f;
        static constexpr float DEFAULT_DISPLAY_INTERVAL = 24.0f;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Members_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);
        Variable_t* Has_Display_Variable();
        Variable_t* Display_Idx_Variable();
        Variable_t* Display_Marker_Variable();

        Range_t<UInt64> Indices();
        Range_t<Member_t**> Aliases();
        Reference_t* Display_Marker();

        Member_t* From_ID(Int_t unique_id);
        Member_t* From_Actor(Actor_t* actor);
        Member_t* From_Unfilled();

        Bool_t Has_Space();
        Bool_t Hasnt_Space();
        Bool_t Has_Actor(Actor_t* actor);
        Bool_t Hasnt_Actor(Actor_t* actor);
        Bool_t Has_Base(Actor_t* actor_with_base);
        Bool_t Hasnt_Base(Actor_t* actor_with_base);
        Bool_t Has_Head(Actor_t* actor);
        Bool_t Hasnt_Head(Actor_t* actor);
        Bool_t Has_Display();
        Bool_t Hasnt_Display();

        Bool_t Is_Clone(Actor_t* actor);

        Bool_t Should_Clone(Actor_t* actor);
        Bool_t Should_Unclone(Actor_t* actor);

        Int_t Max();
        Int_t Limit();
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
        Int_t Count_Base(Actor_t* actor_with_base);
        Int_t Count_Heads(Actor_t* actor);

        Vector_t<Member_t*> All();
        Vector_t<Member_t*> Filled();
        Vector_t<Member_t*> Unfilled();
        Vector_t<Member_t*> Loaded();
        Vector_t<Member_t*> Unloaded();
        Vector_t<Member_t*> Displayed();
        Vector_t<Member_t*> Undisplayed();

        Vector_t<Member_t*> Sort(Vector_t<Member_t*> members);
        Vector_t<Member_t*> Sort_Filled(Int_t begin = 0, Int_t end = -1);

        Vector_t<String_t> Race_Names();

        void Enforce_Loaded(Bool_t do_resurrect = false);

        Vector_t<Member_t*> Filter(Vector_t<String_t>* strings = nullptr,
                                   Vector_t<Int_t>* ints = nullptr,
                                   Int_t flags_1 = 0,
                                   Int_t flags_2 = 0);

        Vector_t<Member_t*> Current_Filter();

        Int_t Display_Start();
        Int_t Display_Stop();
        Int_t Display_Next();
        Int_t Display_Previous();
        void Display(Vector_t<Member_t*> filter,
                     Int_t begin,
                     Int_t count,
                     Reference_t* origin,
                     float radius = DEFAULT_DISPLAY_RADIUS,
                     float degree = DEFAULT_DISPLAY_DEGREE,
                     float interval = DEFAULT_DISPLAY_INTERVAL);
        void Undisplay();

        void Add_Original(Actor_t* original, Callback_t<Int_t, Member_t*>** user_callback);
        void Remove_Original(Actor_t* original, Callback_t<Int_t, Actor_t*>** user_callback);
        void Add_Clone(Actor_t* original, Callback_t<Int_t, Member_t*>** user_callback);
        void Remove_Clone(Actor_t* clone, Bool_t do_delete_clone, Callback_t<Int_t, Actor_t*>** user_callback);

        void u_0_9_3();
        void u_0_9_6();
        void u_0_9_8();
        void u_0_9_9();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
