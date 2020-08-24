/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "papyrus.h"

#include "mcm/mcm_main.h"

namespace doticu_npcp { namespace MCM {

    class Filter_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Filter_t* Self();
        static Object_t* Object();

        static Main_t* Main();
    public:
        Variable_t* Variable(String_t variable_name);

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

        Variable_t* Flags_1_Variable();

        Vector_t<String_t> Strings();
        Vector_t<Int_t> Ints();
        Int_t Flags_1();
        Int_t Flags_2();

        String_t Filter_String();

    public:
        static void Register_Me(Registry_t* registry);
    };

}}
