/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Alias_t;
    class Member_t;

}}}

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    class Main_t;

    class Members_t : public Quest_t {
    public:
        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Members_t* Self();
        static Object_t* Object();

        static Main_t* Main();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Current_View_Variable();

        Variable_t* Members_Variable();
        Variable_t* Page_Index_Variable();
        Variable_t* Page_Count_Variable();
        Variable_t* Members_Slice_Variable();
        Variable_t* Member_Variable();

        Variable_t* Members_Page_Index_Variable();
        Variable_t* Members_Member_Variable();

        Variable_t* Filter_Members_Page_Index_Variable();
        Variable_t* Filter_Members_Member_Variable();

        Variable_t* Do_Previous_Member_Variable();
        Variable_t* Do_Next_Member_Variable();
        
        Variable_t* Options_Offset_Variable();
        Variable_t* Title_Option_Variable();
        Variable_t* Back_Option_Variable();
        Variable_t* Previous_Option_Variable();
        Variable_t* Next_Option_Variable();

        Int_t Current_View();
        void Current_View(Int_t view_code);

        Array_t* Members();
        void Members(Vector_t<Party::Member_t*> members);
        Int_t Page_Index();
        void Page_Index(Int_t page_idx);
        Int_t Page_Count();
        void Page_Count(Int_t page_count);
        Array_t* Members_Slice();
        Party::Member_t* Member();
        void Member(Party::Member_t* member);
        Party::Member_t* Previous_Member();
        Party::Member_t* Next_Member();

        Int_t Members_Page_Index();
        void Members_Page_Index(Int_t page_idx);
        Party::Member_t* Members_Member();
        void Members_Member(Party::Member_t* member);

        Int_t Filter_Members_Page_Index();
        void Filter_Members_Page_Index(Int_t page_idx);
        Party::Member_t* Filter_Members_Member();
        void Filter_Members_Member(Party::Member_t* member);

        Bool_t Do_Previous_Member();
        Bool_t Do_Next_Member();
        Bool_t Is_Valid_Member(Party::Member_t* member);

        Int_t Members_Per_Page();

        void View_Members();
        void View_Filter_Members(Vector_t<Party::Member_t*> members);
        void View_Slice(Vector_t<Party::Member_t*> members, Int_t page_idx);
        void Review_Members();
        void Review_Filter_Members();

        String_t Format_Title(Int_t member_count, Int_t page_idx, Int_t page_count);

        void Build_Page();

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
