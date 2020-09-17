/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_alias.h"
#include "party/party_members.h"
#include "party/party_member.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_members.h"
#include "mcm/mcm_member.h"
#include "mcm/mcm_filter.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

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
    Variable_t* Members_t::Page_Index_Variable() { DEFINE_VARIABLE("p_idx_page"); }
    Variable_t* Members_t::Page_Count_Variable() { DEFINE_VARIABLE("p_num_pages"); }
    Variable_t* Members_t::Member_Variable() { DEFINE_VARIABLE("p_ref_member"); }

    Variable_t* Members_t::Members_Page_Index_Variable() { DEFINE_VARIABLE("p_idx_page_members"); }
    Variable_t* Members_t::Members_Member_Variable() { DEFINE_VARIABLE("p_ref_member_members"); }

    Variable_t* Members_t::Filter_Members_Page_Index_Variable() { DEFINE_VARIABLE("p_idx_page_filter_members"); }
    Variable_t* Members_t::Filter_Members_Member_Variable() { DEFINE_VARIABLE("p_ref_member_filter_members"); }

    Variable_t* Members_t::Do_Previous_Member_Variable() { DEFINE_VARIABLE("p_do_prev_member"); }
    Variable_t* Members_t::Do_Next_Member_Variable() { DEFINE_VARIABLE("p_do_next_member"); }
    
    Variable_t* Members_t::Options_Offset_Variable() { DEFINE_VARIABLE("p_options_offset"); }
    Variable_t* Members_t::Title_Option_Variable() { DEFINE_VARIABLE("p_option_title"); }
    Variable_t* Members_t::Back_Option_Variable() { DEFINE_VARIABLE("p_option_back"); }
    Variable_t* Members_t::Previous_Option_Variable() { DEFINE_VARIABLE("p_option_prev"); }
    Variable_t* Members_t::Next_Option_Variable() { DEFINE_VARIABLE("p_option_next"); }

    Int_t Members_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    void Members_t::Current_View(Int_t view_code)
    {
        Current_View_Variable()->Int(view_code);
    }

    Array_t* Members_t::Members()
    {
        return Members_Variable()->Array();
    }

    void Members_t::Members(Vector_t<Party::Member_t*> members)
    {
        Members_Variable()->Pack(members);
    }

    Int_t Members_t::Page_Index()
    {
        return Page_Index_Variable()->Int();
    }

    void Members_t::Page_Index(Int_t page_idx)
    {
        Page_Index_Variable()->Int(page_idx);
    }

    Int_t Members_t::Page_Count()
    {
        return Page_Count_Variable()->Int();
    }

    void Members_t::Page_Count(Int_t page_count)
    {
        Page_Count_Variable()->Int(page_count);
    }

    Party::Member_t* Members_t::Member()
    {
        return static_cast<Party::Member_t*>(Member_Variable()->Alias());
    }

    void Members_t::Member(Party::Member_t* member)
    {
        Member_Variable()->Pack(member, Party::Member_t::Class_Info());
    }

    Party::Member_t* Members_t::Previous_Member()
    {
        Array_t* members = Members();
        if (members && members->count > 0) {
            Party::Member_t* member = Member();
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
            Party::Member_t* member = Member();
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

    Int_t Members_t::Members_Page_Index()
    {
        return Members_Page_Index_Variable()->Int();
    }

    void Members_t::Members_Page_Index(Int_t page_idx)
    {
        Members_Page_Index_Variable()->Int(page_idx);
    }

    Party::Member_t* Members_t::Members_Member()
    {
        return static_cast<Party::Member_t*>(Members_Member_Variable()->Alias());
    }

    void Members_t::Members_Member(Party::Member_t* member)
    {
        Members_Member_Variable()->Pack(member, Party::Member_t::Class_Info());
    }

    Int_t Members_t::Filter_Members_Page_Index()
    {
        return Filter_Members_Page_Index_Variable()->Int();
    }

    void Members_t::Filter_Members_Page_Index(Int_t page_idx)
    {
        Filter_Members_Page_Index_Variable()->Int(page_idx);
    }

    Party::Member_t* Members_t::Filter_Members_Member()
    {
        return static_cast<Party::Member_t*>(Filter_Members_Member_Variable()->Alias());
    }

    void Members_t::Filter_Members_Member(Party::Member_t* member)
    {
        Filter_Members_Member_Variable()->Pack(member, Party::Member_t::Class_Info());
    }

    Bool_t Members_t::Do_Previous_Member()
    {
        return Do_Previous_Member_Variable()->Bool();
    }

    void Members_t::Do_Previous_Member(Bool_t do_previous_member)
    {
        Do_Previous_Member_Variable()->Bool(do_previous_member);
    }

    Bool_t Members_t::Do_Next_Member()
    {
        return Do_Next_Member_Variable()->Bool();
    }

    void Members_t::Do_Next_Member(Bool_t do_next_member)
    {
        Do_Next_Member_Variable()->Bool(do_next_member);
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

    Int_t Members_t::Headers_Per_Page()
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            return 6;
        } else {
            return 4;
        }
    }

    Int_t Members_t::Members_Per_Page()
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            return 18;
        } else {
            return 20;
        }
    }

    Party::Member_t* Members_t::Option_To_Member(Int_t option)
    {
        Int_t members_per_page = Members_Per_Page();
        Int_t relative_idx = option - Options_Offset_Variable()->Int() - Headers_Per_Page();
        if (relative_idx > -1 && relative_idx < members_per_page) {
            Array_t* members = Members();
            Int_t absolute_idx = Page_Index() * members_per_page + relative_idx;
            if (absolute_idx > -1 && absolute_idx < members->count) {
                return static_cast<Party::Member_t*>(members->Point(absolute_idx)->Alias());
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    String_t Members_t::Member_Info_String(Party::Member_t* member)
    {
        if (member) {
            std::string info =
                std::string("Sex: ") + member->Sex().data + ", " +
                std::string("Race: ") + member->Race().data + "\n";
            if (member->Rating() > 0) {
                info += std::string("Rating: ") + member->Rating_Stars().data;
            }
            return info.c_str();
        } else {
            return "";
        }
    }

    void Members_t::View_Members()
    {
        Vector_t<Party::Member_t*> members =
            Party::Members_t::Self()->Sort_Filled();

        Party::Member_t* members_member = Members_Member();
        if (members_member) {
            Current_View(CODES::VIEW::MEMBERS_MEMBER);
        } else {
            Current_View(CODES::VIEW::MEMBERS);
        }
        Member(members_member);

        Members(members);
        View_Slice(members, Members_Page_Index());
        Members_Page_Index(Page_Index());
    }

    void Members_t::View_Filter_Members(Vector_t<Party::Member_t*> members)
    {
        Party::Member_t* filter_members_member = Filter_Members_Member();
        if (filter_members_member) {
            Current_View(CODES::VIEW::FILTER_MEMBERS_MEMBER);
        } else {
            Current_View(CODES::VIEW::FILTER_MEMBERS);
        }
        Member(filter_members_member);

        Members(members);
        View_Slice(members, Filter_Members_Page_Index());
        Filter_Members_Page_Index(Page_Index());
    }

    void Members_t::View_Slice(Vector_t<Party::Member_t*> members, Int_t page_idx)
    {
        Int_t members_count = members.size();
        Int_t members_per_page = Members_Per_Page();

        Int_t page_count;
        if (members_count > 0) {
            page_count = static_cast<Int_t>(ceilf(
                static_cast<Float_t>(members_count) / static_cast<Float_t>(members_per_page)
            ));
        } else {
            page_count = 0;
        }
        Page_Count(page_count);

        if (page_idx < 0) {
            page_idx = 0;
        } else if (page_idx >= page_count) {
            page_idx = page_count - 1;
        }
        Page_Index(page_idx);

        Int_t begin = members_per_page * page_idx;
        Int_t end = begin + members_per_page;
        if (end > members_count) {
            end = members_count;
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

    void Members_t::Go_Back()
    {
        if (Current_View() == CODES::VIEW::FILTER_MEMBERS) {
            Filter_t::Self()->Review_Filter();
            Main_t::Self()->Reset_Page();
        }
    }

    void Members_t::Request_Previous_Member()
    {
        Do_Previous_Member(true);
    }

    void Members_t::Request_Next_Member()
    {
        Do_Next_Member(true);
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

    void Members_t::On_Build_Page()
    {
        if (Do_Previous_Member()) {
            Member_Variable()->Pack(Previous_Member(), Party::Member_t::Class_Info());
            Do_Previous_Member_Variable()->Bool(false);
        } else if (Do_Next_Member()) {
            Member_Variable()->Pack(Next_Member(), Party::Member_t::Class_Info());
            Do_Next_Member_Variable()->Bool(false);
        }

        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER) {
            Party::Member_t* current_member = Member();
            if (Is_Valid_Member(current_member)) {
                Member_t* mcm_member = Member_t::Self();
                Members_Member_Variable()->Pack(current_member, Party::Member_t::Class_Info());
                mcm_member->View_Members_Member(current_member);
                return mcm_member->On_Build_Page();
            } else {
                Review_Members();
            }
        } else if (current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            Party::Member_t* current_member = Member();
            if (Is_Valid_Member(current_member)) {
                Member_t* mcm_member = Member_t::Self();
                Filter_Members_Member_Variable()->Pack(current_member, Party::Member_t::Class_Info());
                mcm_member->View_Filter_Members_Member(current_member);
                return mcm_member->On_Build_Page();
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

            Int_t members_count = members->count;
            Int_t members_per_page = Members_Per_Page();
            Int_t begin = members_per_page * Page_Index();
            Int_t end = begin + members_per_page;
            if (end > members_count) {
                end = members_count;
            }
            for (; begin < end; begin += 1) {
                Party::Member_t* member = static_cast<Party::Member_t*>
                    (members->Point(begin)->Alias());
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

    void Members_t::On_Option_Select(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Select(option);
        } else {
            Main_t* mcm = Main();
            if (option == Back_Option_Variable()->Int() && current_view == CODES::VIEW::FILTER_MEMBERS) {
                mcm->Option_Flags(option, MCM::DISABLE, true);
                Go_Back();
            } else if (option == Previous_Option_Variable()->Int()) {
                mcm->Option_Flags(option, MCM::DISABLE, true);

                Int_t page_idx = Page_Index();
                if (page_idx == 0) {
                    page_idx = Page_Count() - 1;
                } else {
                    page_idx -= 1;
                }
                Page_Index(page_idx);

                Int_t current_view = Current_View();
                if (current_view == CODES::VIEW::MEMBERS) {
                    Members_Page_Index(page_idx);
                } else if (current_view == CODES::VIEW::FILTER_MEMBERS) {
                    Filter_Members_Page_Index(page_idx);
                }

                mcm->Reset_Page();
            } else if (option == Next_Option_Variable()->Int()) {
                mcm->Option_Flags(option, MCM::DISABLE, true);

                Int_t page_idx = Page_Index();
                if (page_idx == Page_Count() - 1) {
                    page_idx = 0;
                } else {
                    page_idx += 1;
                }
                Page_Index(page_idx);

                Int_t current_view = Current_View();
                if (current_view == CODES::VIEW::MEMBERS) {
                    Members_Page_Index(page_idx);
                } else if (current_view == CODES::VIEW::FILTER_MEMBERS) {
                    Filter_Members_Page_Index(page_idx);
                }

                mcm->Reset_Page();
            } else {
                Party::Member_t* member = Option_To_Member(option);
                if (member) {
                    mcm->Option_Flags(option, MCM::DISABLE, true);

                    Int_t current_view = Current_View();
                    if (current_view == CODES::VIEW::MEMBERS) {
                        Current_View(CODES::VIEW::MEMBERS_MEMBER);
                        Members_Member(member);
                    } else if (current_view == CODES::VIEW::FILTER_MEMBERS) {
                        Current_View(CODES::VIEW::FILTER_MEMBERS_MEMBER);
                        Filter_Members_Member(member);
                    }

                    mcm->Reset_Page();
                }
            }
        }
    }

    void Members_t::On_Option_Menu_Open(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Menu_Open(option);
        }
    }

    void Members_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Menu_Accept(option, idx);
        }
    }

    void Members_t::On_Option_Slider_Open(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Slider_Open(option);
        }
    }

    void Members_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Slider_Accept(option, value);
        }
    }

    void Members_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Input_Accept(option, value);
        }
    }

    void Members_t::On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        }
    }

    void Members_t::On_Option_Default(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Default(option);
        }
    }

    void Members_t::On_Option_Highlight(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::MEMBERS_MEMBER || current_view == CODES::VIEW::FILTER_MEMBERS_MEMBER) {
            MCM::Member_t::Self()->On_Option_Highlight(option);
        } else {
            Main_t* mcm = Main();
            if (option == Back_Option_Variable()->Int() && current_view == CODES::VIEW::FILTER_MEMBERS) {
                mcm->Info_Text("Go back to the filter menu.");
            } else if (option == Previous_Option_Variable()->Int()) {
                mcm->Info_Text("Go to the Previous Page");
            } else if (option == Next_Option_Variable()->Int()) {
                mcm->Info_Text("Go to the Next Page");
            } else {
                Party::Member_t* member = Option_To_Member(option);
                if (member) {
                    mcm->Info_Text(
                        (std::string("Opens the member menu for ") +
                         member->Name().data + ".\n" +
                         Member_Info_String(member).data).c_str()
                    );
                }
            }
        }
    }

    void Members_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Members_t,             \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("View_Members", 0, void, View_Members);
        METHOD("Member_Info_String", 1, String_t, Member_Info_String, Party::Member_t*);

        METHOD("On_Build_Page", 0, void, On_Build_Page);
        METHOD("On_Option_Select", 1, void, On_Option_Select, Int_t);
        METHOD("On_Option_Menu_Open", 1, void, On_Option_Menu_Open, Int_t);
        METHOD("On_Option_Menu_Accept", 2, void, On_Option_Menu_Accept, Int_t, Int_t);
        METHOD("On_Option_Slider_Open", 1, void, On_Option_Slider_Open, Int_t);
        METHOD("On_Option_Slider_Accept", 2, void, On_Option_Slider_Accept, Int_t, Float_t);
        METHOD("On_Option_Input_Accept", 2, void, On_Option_Input_Accept, Int_t, String_t);
        METHOD("On_Option_Keymap_Change", 4, void, On_Option_Keymap_Change, Int_t, Int_t, String_t, String_t);
        METHOD("On_Option_Default", 1, void, On_Option_Default, Int_t);
        METHOD("On_Option_Highlight", 1, void, On_Option_Highlight, Int_t);

        #undef METHOD
    }

}}}
