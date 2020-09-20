/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Logs_t : public Quest_t {
    public:
        static constexpr size_t HEADERS_PER_PAGE = 4;
        static constexpr size_t STRINGS_PER_COLUMN = 8;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Logs_t* Self();
        static Object_t* Object();

        static Main_t* Main();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Notes_Variable(); // Array_t* of String_t
        Variable_t* Errors_Variable(); // Array_t* of String_t

        Variable_t* Page_Count_Variable(); // Int_t
        Variable_t* Page_Index_Variable(); // Int_t

        Variable_t* Options_Offset_Variable(); // Int_t
        Variable_t* Previous_Option_Variable();
        Variable_t* Next_Option_Variable();
        Variable_t* Clear_Notes_Option_Variable();
        Variable_t* Clear_Errors_Option_Variable();

        Array_t* Notes();
        void Notes(Vector_t<String_t> notes);
        Array_t* Errors();
        void Errors(Vector_t<String_t> errors);

        Int_t Page_Count();
        void Page_Count(Int_t page_count);
        Int_t Page_Index();
        void Page_Index(Int_t page_index);

        void On_Build_Page();
        void On_Option_Select(Int_t option);
        void On_Option_Menu_Open(Int_t option);
        void On_Option_Menu_Accept(Int_t option, Int_t idx);
        void On_Option_Slider_Open(Int_t option);
        void On_Option_Slider_Accept(Int_t option, Float_t value);
        void On_Option_Input_Accept(Int_t option, String_t value);
        void On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod);
        void On_Option_Default(Int_t option);
        void On_Option_Highlight(Int_t option);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
