/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Filter_t : public Quest_t {
    public:
        enum Flags_1 : UInt64 {
            IS_LOADED, IS_UNLOADED,
            IS_UNIQUE, IS_GENERIC,
            IS_ORIGINAL, IS_CLONE,
            IS_ALIVE, IS_DEAD,
            IS_MOBILE, IS_IMMOBILE,
            IS_SETTLER, ISNT_SETTLER,
            IS_THRALL, ISNT_THRALL,
            IS_PARALYZED, ISNT_PARALYZED,
            IS_MANNEQUIN, ISNT_MANNEQUIN,
            IS_REANIMATED, ISNT_REANIMATED,
            IS_FOLLOWER, ISNT_FOLLOWER,
            IS_SNEAK, ISNT_SNEAK,
            IS_SADDLER, ISNT_SADDLER,
            IS_RETREATER, ISNT_RETREATER,
        };

        enum Flags_2 : UInt64 {
            // if we hit 32 indices in the first one
        };

    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Filter_t* Self();
        static Object_t* Object();

        static Main_t* Main();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_View_Variable();

        Variable_t* Run_Filter_Option_Variable();

        Variable_t* Sex_Option_Variable();
        Variable_t* Sex_Argument_Variable();
        Variable_t* Sex_Display_Variable();

        Variable_t* Race_Option_Variable();
        Variable_t* Race_Argument_Variable();
        Variable_t* Race_Display_Variable();

        Variable_t* Search_Option_Variable();
        Variable_t* Search_Argument_Variable();

        Variable_t* Style_Option_Variable();
        Variable_t* Style_Argument_Variable();
        Variable_t* Style_Display_Variable();

        Variable_t* Vitality_Option_Variable();
        Variable_t* Vitality_Argument_Variable();
        Variable_t* Vitality_Display_Variable();

        Variable_t* Outfit2_Option_Variable();
        Variable_t* Outfit2_Argument_Variable();
        Variable_t* Outfit2_Display_Variable();

        Variable_t* Rating_Option_Variable();
        Variable_t* Rating_Argument_Variable();
        Variable_t* Rating_Display_Variable();

        Variable_t* Relationship_Rank_Option_Variable();
        Variable_t* Relationship_Rank_Argument_Variable();
        Variable_t* Relationship_Rank_Display_Variable();

        Variable_t* Is_Alive_Option_Variable();
        Variable_t* Is_Dead_Option_Variable();
        Variable_t* Alive_Dead_Ternary_Variable();

        Variable_t* Is_Original_Option_Variable();
        Variable_t* Is_Clone_Option_Variable();
        Variable_t* Original_Clone_Ternary_Variable();

        Variable_t* Is_Unique_Option_Variable();
        Variable_t* Is_Generic_Option_Variable();
        Variable_t* Unique_Generic_Ternary_Variable();

        Variable_t* Is_Mobile_Option_Variable();
        Variable_t* Is_Immobile_Option_Variable();
        Variable_t* Mobile_Immobile_Ternary_Variable();

        Variable_t* Is_Settler_Option_Variable();
        Variable_t* Is_Non_Settler_Option_Variable();
        Variable_t* Settler_Ternary_Variable();

        Variable_t* Is_Thrall_Option_Variable();
        Variable_t* Is_Non_Thrall_Option_Variable();
        Variable_t* Thrall_Ternary_Variable();

        Variable_t* Is_Paralyzed_Option_Variable();
        Variable_t* Is_Non_Paralyzed_Option_Variable();
        Variable_t* Paralyzed_Ternary_Variable();

        Variable_t* Is_Mannequin_Option_Variable();
        Variable_t* Is_Non_Mannequin_Option_Variable();
        Variable_t* Mannequin_Ternary_Variable();

        Variable_t* Is_Reanimated_Option_Variable();
        Variable_t* Is_Non_Reanimated_Option_Variable();
        Variable_t* Reanimated_Ternary_Variable();

        Variable_t* Is_Follower_Option_Variable();
        Variable_t* Is_Non_Follower_Option_Variable();
        Variable_t* Follower_Ternary_Variable();

        Variable_t* Is_Sneak_Option_Variable();
        Variable_t* Is_Non_Sneak_Option_Variable();
        Variable_t* Sneak_Ternary_Variable();

        Variable_t* Is_Saddler_Option_Variable();
        Variable_t* Is_Non_Saddler_Option_Variable();
        Variable_t* Saddler_Ternary_Variable();

        Int_t Current_View();
        void Current_View(Int_t view_code);

        void Review_Filter();

        Vector_t<String_t> Strings();
        Vector_t<Int_t> Ints();
        Int_t Flags_1();
        Int_t Flags_2();

        String_t Filter_String();

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
