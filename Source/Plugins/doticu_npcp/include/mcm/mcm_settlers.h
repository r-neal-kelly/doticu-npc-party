/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Alias_t;
    class Member_t;
    class Settler_t;

}}}

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Settlers_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Settlers_t* Self();
        static Object_t* Object();

        static Main_t* Main();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_View_Variable(); // Int_t

        Variable_t* Settlers_Variable(); // Array_t* of Alias_t*
        Variable_t* Page_Count_Variable(); // Int_t
        Variable_t* Page_Index_Variable(); // Int_t

        Variable_t* Settler_Variable(); // Alias_t*
        Variable_t* Do_Previous_Settler_Variable(); // Bool_t
        Variable_t* Do_Next_Settler_Variable(); // Bool_t
        
        Variable_t* Options_Offset_Variable(); // Int_t
        Variable_t* Title_Option_Variable(); // Int_t
        Variable_t* Back_Option_Variable(); // Int_t
        Variable_t* Previous_Option_Variable(); // Int_t
        Variable_t* Next_Option_Variable(); // Int_t

        Int_t Current_View();
        void Current_View(Int_t view_code);

        Array_t* Settlers();
        void Settlers(Vector_t<Party::Member_t*> settlers);
        Int_t Page_Count();
        void Page_Count(Int_t page_count);
        Int_t Page_Index();
        void Page_Index(Int_t page_idx);

        Party::Settler_t* Settler();
        void Settler(Party::Settler_t* settler);
        Party::Settler_t* Previous_Settler();
        Party::Settler_t* Next_Settler();
        Bool_t Do_Previous_Settler();
        void Do_Previous_Settler(Bool_t value);
        Bool_t Do_Next_Settler();
        void Do_Next_Settler(Bool_t value);
        Bool_t Is_Valid_Settler(Party::Settler_t* settler);

        Int_t Headers_Per_Page();
        Int_t Settlers_Per_Page();
        Party::Settler_t* Option_To_Settler(Int_t option);
        String_t Settler_Info_String(Party::Settler_t* settler);

        void Review_Settlers();

        String_t Format_Title(Int_t settler_count, Int_t page_index, Int_t page_count);

        void On_Build_Page();
        void On_Option_Select(Int_t option, Callback_t<>* user_callback);
        void On_Option_Menu_Open(Int_t option);
        void On_Option_Menu_Accept(Int_t option, Int_t idx);
        void On_Option_Slider_Open(Int_t option);
        void On_Option_Slider_Accept(Int_t option, Float_t value);
        void On_Option_Input_Accept(Int_t option, String_t value);
        void On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod, Callback_t<>* user_callback);
        void On_Option_Default(Int_t option, Callback_t<>* user_callback);
        void On_Option_Highlight(Int_t option);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
