/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Follower_t;

}}}

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Followers_t : public Quest_t {
    public:
        static constexpr size_t HEADERS = 2;
        static constexpr size_t OPTIONS_PER_FOLLOWER = 5; // includes name option

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Followers_t* Self();
        static Object_t* Object();

        static Main_t* Main();
    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_View_Variable(); // Int_t

        Variable_t* Followers_Variable(); // Array_t* of Follower_t*
        Variable_t* Follower_Variable(); // Follower_t*

        Variable_t* Do_Previous_Follower_Variable(); // Bool_t
        Variable_t* Do_Next_Follower_Variable(); // Bool_t

        Variable_t* Options_Offset_Variable(); // Int_t
        Variable_t* Menu_Option_Variable(); // Int_t

        Int_t Current_View();
        void Current_View(Int_t view_code);

        Array_t* Followers();
        void Followers(Vector_t<Party::Follower_t*> followers);
        Party::Follower_t* Follower();
        void Follower(Party::Follower_t* follower);
        Party::Follower_t* Previous_Follower();
        Party::Follower_t* Next_Follower();

        struct Follower_Indices_t {
            Int_t follower;
            Int_t option;
        };
        Follower_Indices_t Follower_Indices(Int_t option);

        Bool_t Do_Previous_Follower();
        void Do_Previous_Follower(Bool_t do_previous_follower);
        Bool_t Do_Next_Follower();
        void Do_Next_Follower(Bool_t do_next_follower);

        void View_Followers();
        void Review_Followers();
        void Request_Previous_Follower();
        void Request_Next_Follower();

        void On_Build_Page();
        void On_Option_Select(Int_t option, Callback_t<>* user_callback);
        void On_Option_Menu_Open(Int_t option);
        void On_Option_Menu_Accept(Int_t option, Int_t idx);
        void On_Option_Slider_Open(Int_t option);
        void On_Option_Slider_Accept(Int_t option, Float_t value);
        void On_Option_Input_Accept(Int_t option, String_t value);
        void On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod, Callback_t<>* user_callback);
        void On_Option_Default(Int_t option);
        void On_Option_Highlight(Int_t option);
        
    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
