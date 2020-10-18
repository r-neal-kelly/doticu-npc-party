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
#include "party/party_settler.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_settlers.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Settlers_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_settlers");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Settlers_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Settlers_t* Settlers_t::Self()
    {
        return static_cast<Settlers_t*>(Consts::Control_Quest());
    }

    Object_t* Settlers_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Settlers_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Settlers_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Settlers_t::Current_View_Variable() { DEFINE_VARIABLE("p_current_view"); }

    Variable_t* Settlers_t::Settlers_Variable() { DEFINE_VARIABLE("p_settlers"); }
    Variable_t* Settlers_t::Page_Count_Variable() { DEFINE_VARIABLE("p_page_count"); }
    Variable_t* Settlers_t::Page_Index_Variable() { DEFINE_VARIABLE("p_page_index"); }

    Variable_t* Settlers_t::Settler_Variable() { DEFINE_VARIABLE("p_settler"); }
    Variable_t* Settlers_t::Do_Previous_Settler_Variable() { DEFINE_VARIABLE("p_do_previous_settler"); }
    Variable_t* Settlers_t::Do_Next_Settler_Variable() { DEFINE_VARIABLE("p_do_next_settler"); }
    
    Variable_t* Settlers_t::Options_Offset_Variable() { DEFINE_VARIABLE("p_options_offset"); }
    Variable_t* Settlers_t::Title_Option_Variable() { DEFINE_VARIABLE("p_option_title"); }
    Variable_t* Settlers_t::Back_Option_Variable() { DEFINE_VARIABLE("p_option_back"); }
    Variable_t* Settlers_t::Previous_Option_Variable() { DEFINE_VARIABLE("p_option_previous"); }
    Variable_t* Settlers_t::Next_Option_Variable() { DEFINE_VARIABLE("p_option_next"); }

    Int_t Settlers_t::Current_View()
    {
        return Current_View_Variable()->Int();
    }

    void Settlers_t::Current_View(Int_t view_code)
    {
        Current_View_Variable()->Int(view_code);
    }

    Array_t* Settlers_t::Settlers()
    {
        return Settlers_Variable()->Array();
    }

    void Settlers_t::Settlers(Vector_t<Party::Member_t*> settlers)
    {
        Settlers_Variable()->Pack(settlers);
    }

    Int_t Settlers_t::Page_Count()
    {
        return Page_Count_Variable()->Int();
    }

    void Settlers_t::Page_Count(Int_t page_count)
    {
        Page_Count_Variable()->Int(page_count);
    }

    Int_t Settlers_t::Page_Index()
    {
        return Page_Index_Variable()->Int();
    }

    void Settlers_t::Page_Index(Int_t page_index)
    {
        Page_Index_Variable()->Int(page_index);
    }

    Party::Settler_t* Settlers_t::Settler()
    {
        return static_cast<Party::Settler_t*>(Settler_Variable()->Alias());
    }

    void Settlers_t::Settler(Party::Settler_t* settler)
    {
        Settler_Variable()->Pack(settler, Class_Info_t::Fetch(Party::Settler_t::kTypeID, true));
    }

    Party::Settler_t* Settlers_t::Previous_Settler()
    {
        Array_t* settlers = Settlers();
        if (settlers && settlers->count > 0) {
            Party::Settler_t* settler = Settler();
            Int_t idx = settlers->Find(Party::Settler_t::kTypeID, settler);
            if (idx > -1) {
                if (idx == 0) {
                    return static_cast<Party::Settler_t*>(settlers->Point(settlers->count - 1)->Alias());
                } else {
                    return static_cast<Party::Settler_t*>(settlers->Point(idx - 1)->Alias());
                }
            } else {
                return static_cast<Party::Settler_t*>(settlers->Point(0)->Alias());
            }
        } else {
            return nullptr;
        }
    }

    Party::Settler_t* Settlers_t::Next_Settler()
    {
        Array_t* settlers = Settlers();
        if (settlers && settlers->count > 0) {
            Party::Settler_t* settler = Settler();
            Int_t idx = settlers->Find(Party::Settler_t::kTypeID, settler);
            if (idx > -1) {
                if (idx == settlers->count - 1) {
                    return static_cast<Party::Settler_t*>(settlers->Point(0)->Alias());
                } else {
                    return static_cast<Party::Settler_t*>(settlers->Point(idx + 1)->Alias());
                }
            } else {
                return static_cast<Party::Settler_t*>(settlers->Point(settlers->count - 1)->Alias());
            }
        } else {
            return nullptr;
        }
    }

    Bool_t Settlers_t::Do_Previous_Settler()
    {
        return Do_Previous_Settler_Variable()->Bool();
    }

    void Settlers_t::Do_Previous_Settler(Bool_t value)
    {
        Do_Previous_Settler_Variable()->Bool(value);
    }

    Bool_t Settlers_t::Do_Next_Settler()
    {
        return Do_Next_Settler_Variable()->Bool();
    }

    void Settlers_t::Do_Next_Settler(Bool_t value)
    {
        Do_Next_Settler_Variable()->Bool(value);
    }

    Bool_t Settlers_t::Is_Valid_Settler(Party::Settler_t* settler)
    {
        Array_t* settlers = Settlers();
        if (settlers) {
            return settler && settler->Is_Filled() && settler->Is_Settler() && settlers->Has(Party::Settler_t::kTypeID, settler);
        } else {
            return false;
        }
    }

    Int_t Settlers_t::Headers_Per_Page()
    {
        if (Current_View() == CODES::VIEW::SETTLERS) {
            return 4;
        } else if (Current_View() == CODES::VIEW::SETTLERS_SETTLER) {
            return 6;
        } else {
            NPCP_ASSERT(false);
            return 0;
        }
    }

    Int_t Settlers_t::Settlers_Per_Page()
    {
        if (Current_View() == CODES::VIEW::SETTLERS) {
            return 20;
        } else if (Current_View() == CODES::VIEW::SETTLERS_SETTLER) {
            return 1;
        } else {
            NPCP_ASSERT(false);
            return 0;
        }
    }

    Party::Settler_t* Settlers_t::Option_To_Settler(Int_t option)
    {
        if (Current_View() == CODES::VIEW::SETTLERS) {
            Int_t settlers_per_page = Settlers_Per_Page();
            Int_t relative_idx = option - Options_Offset_Variable()->Int() - Headers_Per_Page();
            if (relative_idx > -1 && relative_idx < settlers_per_page) {
                Array_t* settlers = Settlers();
                Int_t absolute_idx = Page_Index() * settlers_per_page + relative_idx;
                if (absolute_idx > -1 && absolute_idx < settlers->count) {
                    return static_cast<Party::Settler_t*>(settlers->Point(absolute_idx)->Alias());
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else if (Current_View() == CODES::VIEW::SETTLERS_SETTLER) {
            return Settler();
        } else {
            NPCP_ASSERT(false);
            return nullptr;
        }
    }

    String_t Settlers_t::Settler_Info_String(Party::Settler_t* settler)
    {
        // we could add location cell, etc.

        if (settler) {
            std::string info =
                std::string("Sex: ") + settler->Sex().data + ", " +
                std::string("Race: ") + settler->Race().data + "\n";
            if (settler->Rating() > 0) {
                info += std::string("Rating: ") + settler->Rating_Stars().data;
            }
            return info.c_str();
        } else {
            return "";
        }
    }

    void Settlers_t::Review_Settlers()
    {
        Current_View_Variable()->Int(CODES::VIEW::SETTLERS);
        Settler_Variable()->Pack(static_cast<Party::Settler_t*>(nullptr));
        Do_Previous_Settler(false);
        Do_Next_Settler(false);
    }

    String_t Settlers_t::Format_Title(Int_t settler_count, Int_t page_index, Int_t page_count)
    {
        std::string settlers =
            std::string("Settlers: ") +
            std::to_string(settler_count) + "/" +
            std::to_string(Party::Members_t::Self()->Limit());

        std::string pages =
            std::string("Page: ") +
            std::to_string(page_index + 1) + "/" +
            std::to_string(page_count);

        return (settlers + "               " + pages).c_str();
    }

    void Settlers_t::On_Build_Page()
    {
        auto Update_Settlers_Data = [&]()
        {
            Vector_t<Party::Member_t*> settlers = Party::Members_t::Self()->Sort_Settlers();
            Int_t settler_count = settlers.size();
            Int_t settlers_per_page = Settlers_Per_Page();
            Settlers(settlers);

            Int_t page_count;
            if (settler_count > 0) {
                page_count = static_cast<Int_t>(ceilf(
                    static_cast<Float_t>(settler_count) / static_cast<Float_t>(settlers_per_page)
                ));
            } else {
                page_count = 0;
            }
            Page_Count(page_count);

            Int_t page_index = Page_Index();
            if (page_count > 0) {
                if (page_index < 0) {
                    page_index = 0;
                } else if (page_index >= page_count) {
                    page_index = page_count - 1;
                }
            } else {
                page_index = -1;
            }
            Page_Index(page_index);
        };

        auto Update_Settler_Data = [&]()
        {
            if (Do_Previous_Settler()) {
                Do_Previous_Settler(false);
                Settler(Previous_Settler());
            } else if (Do_Next_Settler()) {
                Do_Next_Settler(false);
                Settler(Next_Settler());
            }
        };

        auto Build_Settlers = [&]()
        {
            Update_Settlers_Data();

            Main_t* mcm = Main_t::Self();
            mcm->Cursor_Position(0);
            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

            Array_t* settlers = Settlers();
            if (settlers && settlers->count > 0) {
                Int_t settlers_per_page = Settlers_Per_Page();

                mcm->Title_Text(Format_Title(settlers->count, Page_Index(), Page_Count()));

                if (settlers->count > settlers_per_page) {
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
                Options_Offset_Variable()->Int(Previous_Option_Variable()->Int());

                mcm->Add_Header_Option("");
                mcm->Add_Header_Option("");

                Int_t begin = settlers_per_page * Page_Index();
                Int_t end = begin + settlers_per_page;
                if (end > settlers->count) {
                    end = settlers->count;
                }
                for (; begin < end; begin += 1) {
                    Party::Settler_t* settler = static_cast<Party::Settler_t*>
                        (settlers->Point(begin)->Alias());
                    mcm->Add_Text_Option(settler->Name(), "...");
                }
            } else {
                mcm->Title_Text(Format_Title(0, 0, 1));
                mcm->Add_Header_Option(" No Settlers ");
            }
        };

        auto Build_Settler = [&]()
        {
            Update_Settler_Data();

            Party::Settler_t* settler = Settler();
            if (settler && Is_Valid_Settler(settler)) {
                Update_Settlers_Data();

                // ...
            } else {
                Review_Settlers();
                Build_Settlers();
            }
        };

        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            Build_Settlers();
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            Build_Settler();
        } else {
            Review_Settlers();
            Build_Settlers();
        }
    }

    void Settlers_t::On_Option_Select(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>*;
        NPCP_ASSERT(user_callback);

        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            if (option == Previous_Option_Variable()->Int()) {
                mcm->Option_Flags(option, MCM::DISABLE, true);

                Int_t page_idx = Page_Index();
                if (page_idx == 0) {
                    page_idx = Page_Count() - 1;
                } else {
                    page_idx -= 1;
                }
                Page_Index(page_idx);

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

                mcm->Reset_Page();
            } else {
                Party::Settler_t* settler = Option_To_Settler(option);
                if (settler) {
                    mcm->Option_Flags(option, MCM::DISABLE, true);

                    Current_View(CODES::VIEW::SETTLERS_SETTLER);
                    Settler(settler);

                    mcm->Reset_Page();
                }
            }
            mcm->Return_Latent(user_callback);
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            mcm->Return_Latent(user_callback);
        } else {
            mcm->Return_Latent(user_callback);
        }
    }

    void Settlers_t::On_Option_Menu_Open(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {

        } else {

        }
    }

    void Settlers_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {

        } else {

        }
    }

    void Settlers_t::On_Option_Slider_Open(Int_t option)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {

        } else {

        }
    }

    void Settlers_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {

        } else {

        }
    }

    void Settlers_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {

        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {

        } else {

        }
    }

    void Settlers_t::On_Option_Keymap_Change(Int_t option,
                                             Int_t key_code,
                                             String_t conflict,
                                             String_t conflicting_mod,
                                             Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            mcm->Return_Latent(user_callback);
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            mcm->Return_Latent(user_callback);
        } else {
            mcm->Return_Latent(user_callback);
        }
    }

    void Settlers_t::On_Option_Default(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            mcm->Return_Latent(user_callback);
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {
            mcm->Return_Latent(user_callback);
        } else {
            mcm->Return_Latent(user_callback);
        }
    }

    void Settlers_t::On_Option_Highlight(Int_t option)
    {
        Main_t* mcm = Main();
        Int_t current_view = Current_View();
        if (current_view == CODES::VIEW::SETTLERS) {
            if (option == Previous_Option_Variable()->Int()) {
                mcm->Info_Text("Go to the Previous Page");
            } else if (option == Next_Option_Variable()->Int()) {
                mcm->Info_Text("Go to the Next Page");
            } else {
                Party::Settler_t* settler = Option_To_Settler(option);
                if (settler) {
                    mcm->Info_Text(
                        (std::string("Opens the settler menu for ") +
                         settler->Name().data + ".\n" +
                         Settler_Info_String(settler).data).c_str()
                    );
                }
            }
        } else if (current_view == CODES::VIEW::SETTLERS_SETTLER) {

        } else {

        }
    }

    void Settlers_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Members_t,             \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
