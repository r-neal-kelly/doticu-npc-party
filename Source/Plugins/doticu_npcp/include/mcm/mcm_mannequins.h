/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_mannequins.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Member_t;

}}}

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Mannequins_t : public Quest_t {
    public:
        static constexpr size_t MANNEQUINS_HEADERS = 6; // must be even
        static constexpr size_t MANNEQUINS_CELL_HEADERS = 6;
        static constexpr size_t COLUMNS_PER_PAGE = 2;
        static constexpr size_t OPTIONS_PER_COLUMN = Party::Mannequins_t::ROWS + 1; // includes header

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Mannequins_t* Self();
        static Object_t* Object();

        static Main_t* Main();
    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_View_Variable(); // Int_t

        Variable_t* Page_Index_Variable(); // Int_t
        Variable_t* Page_Count_Variable(); // Int_t

        Variable_t* Current_Column_Variable(); // Int_t
        Variable_t* Current_Row_Variable(); // Int_t

        Variable_t* Members_Variable(); // Array_t* of Party::Member_t*
        Variable_t* Member_Variable(); // Party::Member_t*

        Variable_t* Options_Offset_Variable();
        Variable_t* Enter_Option_Variable();
        Variable_t* Exit_Option_Variable();
        Variable_t* Previous_Option_Variable();
        Variable_t* Next_Option_Variable();
        Variable_t* Name_Option_Variable();
        Variable_t* Back_Option_Variable();
        Variable_t* North_1_Option_Variable();
        Variable_t* North_2_Option_Variable();
        Variable_t* West_Option_Variable();
        Variable_t* East_Option_Variable();
        Variable_t* South_1_Option_Variable();
        Variable_t* South_2_Option_Variable();

        Int_t Current_View();
        void Current_View(Int_t view_code);

        Int_t Page_Index();
        void Page_Index(Int_t page_idx);
        Int_t Page_Count();
        void Page_Count(Int_t page_count);

        Int_t Current_Column();
        void Current_Column(Int_t column);
        Int_t Current_Row();
        void Current_Row(Int_t row);

        Array_t* Members();
        void Members(Vector_t<Party::Member_t*> members);
        Party::Member_t* Member();
        void Member(Party::Member_t* member);

        std::string Cell_Name(Int_t column, Int_t row);

        void View_Mannequins();
        void Review_Mannequins();

        Int_t Option_To_Column(Int_t option);
        Int_t Option_To_Row(Int_t option);
        Party::Member_t* Option_To_Member(Int_t option);

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
