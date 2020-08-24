/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "utils.h"

#include "mcm/mcm_members.h"
#include "mcm/mcm_member.h"
#include "mcm/mcm_filter.h"

#include "papyrus.inl"
#include "party.inl"

namespace doticu_npcp { namespace MCM {

    String_t Members_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_members");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Members_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Members_t* Members_t::Self()
    {
        return static_cast<Members_t*>(Consts::Control_Quest());
    }

    Object_t* Members_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Members_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Members_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Members_t::Current_View_Variable() { DEFINE_VARIABLE("p_code_view"); }
    Variable_t* Members_t::Members_Variable() { DEFINE_VARIABLE("p_arr_aliases"); }
    Variable_t* Members_t::Members_Slice_Variable() { DEFINE_VARIABLE("p_arr_aliases_slice"); }
    Variable_t* Members_t::Current_Member_Variable() { DEFINE_VARIABLE("p_ref_member"); }
    Variable_t* Members_t::Members_Member_Variable() { DEFINE_VARIABLE("p_ref_member_members"); }
    Variable_t* Members_t::Filter_Members_Member_Variable() { DEFINE_VARIABLE("p_ref_member_filter_members"); }
    Variable_t* Members_t::Do_Previous_Member_Variable() { DEFINE_VARIABLE("p_do_prev_member"); }
    Variable_t* Members_t::Do_Next_Member_Variable() { DEFINE_VARIABLE("p_do_next_member"); }
    Variable_t* Members_t::Page_Index_Variable() { DEFINE_VARIABLE("p_idx_page"); }
    Variable_t* Members_t::Page_Count_Variable() { DEFINE_VARIABLE("p_num_pages"); }
    Variable_t* Members_t::Options_Offset_Variable() { DEFINE_VARIABLE("p_options_offset"); }
    Variable_t* Members_t::Title_Option_Variable() { DEFINE_VARIABLE("p_option_title"); }
    Variable_t* Members_t::Back_Option_Variable() { DEFINE_VARIABLE("p_option_back"); }
    Variable_t* Members_t::Previous_Option_Variable() { DEFINE_VARIABLE("p_option_prev"); }
    Variable_t* Members_t::Next_Option_Variable() { DEFINE_VARIABLE("p_option_next"); }

    Int_t Members_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    Array_t* Members_t::Members()
    {
        return Members_Variable()->Array();
    }

    Array_t* Members_t::Members_Slice()
    {
        return Members_Slice_Variable()->Array();
    }

    Party::Member_t* Members_t::Current_Member()
    {
        return static_cast<Party::Member_t*>(Current_Member_Variable()->Alias());
    }

    Bool_t Members_t::Do_Previous_Member()
    {
        return Do_Previous_Member_Variable()->Bool();
    }

    Bool_t Members_t::Do_Next_Member()
    {
        return Do_Next_Member_Variable()->Bool();
    }

    Int_t Members_t::Page_Index()
    {
        return Page_Index_Variable()->Int();
    }

    Int_t Members_t::Page_Count()
    {
        return Page_Count_Variable()->Int();
    }
    
    Int_t Members_t::Members_Per_Page()
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            return 18;
        } else {
            return 20;
        }
    }

    Bool_t Members_t::Is_Valid_Member(Party::Member_t* member)
    {
        Array_t* members = Members();
        if (members) {
            return member && member->Is_Filled() && members->Has(Party::Member_t::kTypeID, member);
        } else {
            return false;
        }
    }

    void Members_t::Review_Members()
    {
        Current_View_Variable()->Int(CODES::VIEW::MEMBERS);
        Members_Member_Variable()->Pack(static_cast<Party::Member_t*>(nullptr),
                                        Party::Member_t::Class_Info());
    }

    void Members_t::Review_Filter_Members()
    {
        Current_View_Variable()->Int(CODES::VIEW::FILTER_MEMBERS);
        Filter_Members_Member_Variable()->Pack(static_cast<Party::Member_t*>(nullptr),
                                               Party::Member_t::Class_Info());
    }

    String_t Members_t::Format_Title(Int_t member_count, Int_t page_idx, Int_t page_count)
    {
        std::string members =
            std::string("Members: ") +
            std::to_string(member_count) + "/" +
            std::to_string(Party::Members_t::Self()->Limit());

        std::string pages =
            std::string("Page: ") +
            std::to_string(page_idx + 1) + "/" +
            std::to_string(page_count);

        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            members = std::string("Filtered ") + members;
        }

        return (members + "               " + pages).c_str();
    }

    void Members_t::Build_Page()
    {
        if (Do_Previous_Member()) {
            Current_Member_Variable()->Pack(Previous_Member(), Party::Member_t::Class_Info());
            Do_Previous_Member_Variable()->Bool(false);
        } else if (Do_Next_Member()) {
            Current_Member_Variable()->Pack(Next_Member(), Party::Member_t::Class_Info());
            Do_Next_Member_Variable()->Bool(false);
        }
        
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER) {
            Party::Member_t* current_member = Current_Member();
            if (Is_Valid_Member(current_member)) {
                Member_t* mcm_member = Member_t::Self();
                Members_Member_Variable()->Pack(current_member, Party::Member_t::Class_Info());
                mcm_member->View_Members_Member(current_member);
                return mcm_member->Build_Page();
            } else {
                Review_Members();
            }
        } else if (current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            Party::Member_t* current_member = Current_Member();
            if (Is_Valid_Member(current_member)) {
                Member_t* mcm_member = Member_t::Self();
                Filter_Members_Member_Variable()->Pack(current_member, Party::Member_t::Class_Info());
                mcm_member->View_Filter_Members_Member(current_member);
                return mcm_member->Build_Page();
            } else {
                Review_Filter_Members();
            }
        }
        current_view = Current_View();

        Main_t* mcm = Main_t::Self();

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

        Array_t* members = Members();
        if (members) {
            mcm->Title_Text(Format_Title(members->count, Page_Index(), Page_Count()));

            if (current_view == CODES::VIEW::FILTER_MEMBERS) {
                Title_Option_Variable()->Int(
                    mcm->Add_Text_Option(Filter_t::Self()->Filter_String(), "")
                ); 
                Back_Option_Variable()->Int(
                    mcm->Add_Text_Option("                            Go Back", "")
                );
            }

            if (members->count > Members_Per_Page()) {
                Previous_Option_Variable()->Int(
                    mcm->Add_Text_Option("                     Go to Previous Page", "")
                );
                Next_Option_Variable()->Int(
                    mcm->Add_Text_Option("                       Go to Next Page", "")
                );
            } else {
                Previous_Option_Variable()->Int(
                    mcm->Add_Text_Option("                     Go to Previous Page", "", MCM::DISABLE)
                );
                Next_Option_Variable()->Int(
                    mcm->Add_Text_Option("                       Go to Next Page", "", MCM::DISABLE)
                );
            }

            if (current_view == CODES::VIEW::FILTER_MEMBERS) {
                Options_Offset_Variable()->Int(Title_Option_Variable()->Int());
            } else {
                Options_Offset_Variable()->Int(Previous_Option_Variable()->Int());
            }

            mcm->Add_Header_Option("");
            mcm->Add_Header_Option("");

            Array_t* members_slice = Members_Slice();
            for (size_t idx = 0, count = members_slice->count; idx < count; idx += 1) {
                Party::Member_t* member = static_cast<Party::Member_t*>
                    (members_slice->Point(idx)->Alias());
                mcm->Add_Text_Option(member->Name(), "...");
            }
        } else {
            mcm->Title_Text(Format_Title(0, 0, 1));

            if (current_view == CODES::VIEW::FILTER_MEMBERS) {
                Title_Option_Variable()->Int(
                    mcm->Add_Text_Option(Filter_t::Self()->Filter_String(), "")
                );
                Back_Option_Variable()->Int(
                    mcm->Add_Text_Option("                            Go Back", "")
                );
            }

            mcm->Add_Header_Option(" No Members ");
        }
    }

    Party::Member_t* Members_t::Previous_Member()
    {
        Array_t* members = Members();
        if (members && members->count > 0) {
            Party::Member_t* member = Current_Member();
            Int_t idx = members->Find(Party::Member_t::kTypeID, member);
            if (idx > -1) {
                if (idx == 0) {
                    return static_cast<Party::Member_t*>(members->Point(members->count - 1)->Alias());
                } else {
                    return static_cast<Party::Member_t*>(members->Point(idx - 1)->Alias());
                }
            } else {
                return static_cast<Party::Member_t*>(members->Point(0)->Alias());
            }
        } else {
            return nullptr;
        }
    }

    Party::Member_t* Members_t::Next_Member()
    {
        Array_t* members = Members();
        if (members && members->count > 0) {
            Party::Member_t* member = Current_Member();
            Int_t idx = members->Find(Party::Member_t::kTypeID, member);
            if (idx > -1) {
                if (idx == members->count - 1) {
                    return static_cast<Party::Member_t*>(members->Point(0)->Alias());
                } else {
                    return static_cast<Party::Member_t*>(members->Point(idx + 1)->Alias());
                }
            } else {
                return static_cast<Party::Member_t*>(members->Point(members->count - 1)->Alias());
            }
        } else {
            return nullptr;
        }
    }

    void Members_t::Register_Me(Registry_t* registry)
    {
        using namespace Utils;

        auto Build_Page = Forward<void, Members_t, &Members_t::Build_Page>();

        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Class_Name(), MCM::Members_t,              \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, METHOD_, __VA_ARGS__);            \
        W

        ADD_METHOD("f_Build_Page", 0, void, Build_Page);

        #undef ADD_METHOD
    }

}}
