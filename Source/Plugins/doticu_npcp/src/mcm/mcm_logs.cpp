/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "logs.h"
#include "papyrus.inl"
#include "utils.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_logs.h"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Logs_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm_logs");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Logs_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Logs_t* Logs_t::Self()
    {
        return static_cast<Logs_t*>(Consts::Control_Quest());
    }

    Object_t* Logs_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Main_t* Logs_t::Main()
    {
        return Main_t::Self();
    }

    Variable_t* Logs_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Logs_t::Notes_Variable() { DEFINE_VARIABLE("p_notes"); }
    Variable_t* Logs_t::Errors_Variable() { DEFINE_VARIABLE("p_errors"); }

    Variable_t* Logs_t::Page_Count_Variable() { DEFINE_VARIABLE("p_page_count"); }
    Variable_t* Logs_t::Page_Index_Variable() { DEFINE_VARIABLE("p_page_index"); }

    Variable_t* Logs_t::Options_Offset_Variable() { DEFINE_VARIABLE("p_options_offset"); }
    Variable_t* Logs_t::Previous_Option_Variable() { DEFINE_VARIABLE("p_option_previous"); }
    Variable_t* Logs_t::Next_Option_Variable() { DEFINE_VARIABLE("p_option_next"); }
    Variable_t* Logs_t::Clear_Notes_Option_Variable() { DEFINE_VARIABLE("p_option_clear_notes"); }
    Variable_t* Logs_t::Clear_Errors_Option_Variable() { DEFINE_VARIABLE("p_option_clear_errors"); }

    Array_t* Logs_t::Notes()
    {
        return Notes_Variable()->Array();
    }

    void Logs_t::Notes(Vector_t<String_t> notes)
    {
        Notes_Variable()->Pack(notes);
    }

    Array_t* Logs_t::Errors()
    {
        return Errors_Variable()->Array();
    }

    void Logs_t::Errors(Vector_t<String_t> errors)
    {
        Errors_Variable()->Pack(errors);
    }

    Int_t Logs_t::Page_Count()
    {
        return Page_Count_Variable()->Int();
    }

    void Logs_t::Page_Count(Int_t page_count)
    {
        Page_Count_Variable()->Int(page_count);
    }

    Int_t Logs_t::Page_Index()
    {
        return Page_Index_Variable()->Int();
    }

    void Logs_t::Page_Index(Int_t page_index)
    {
        Page_Index_Variable()->Int(page_index);
    }

    void Logs_t::On_Build_Page()
    {
        Modules::Logs_t* logs = Modules::Logs_t::Self();
        MCM::Main_t* mcm = Main();

        Int_t notes_count = logs->Notes_Count();
        Int_t errors_count = logs->Errors_Count();

        Int_t page_count;
        if (notes_count == 0 && errors_count == 0) {
            page_count = 1;
        } else {
            if (notes_count > errors_count) {
                page_count = ceilf(static_cast<Float_t>(notes_count) / STRINGS_PER_COLUMN);
            } else {
                page_count = ceilf(static_cast<Float_t>(errors_count) / STRINGS_PER_COLUMN);
            }
        }
        Page_Count(page_count);

        Int_t page_index = Page_Index();
        if (page_index >= page_count) {
            page_index = 0;
            Page_Index(page_index);
        }

        std::string notes_title = "Notes: " + std::to_string(notes_count) + "/" + std::to_string(Modules::Logs_t::MAX);
        std::string errors_title = "Errors: " + std::to_string(errors_count) + "/" + std::to_string(Modules::Logs_t::MAX);
        std::string pages_title = "Pages: " + std::to_string(page_index + 1) + "/" + std::to_string(page_count);
        mcm->Title_Text((notes_title + "         " + pages_title + "         " + errors_title).c_str());

        mcm->Cursor_Position(0);
        mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);

        if (notes_count > STRINGS_PER_COLUMN || errors_count > STRINGS_PER_COLUMN) {
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

        {
            Int_t notes_begin = STRINGS_PER_COLUMN * page_index;
            Int_t notes_end = notes_begin + STRINGS_PER_COLUMN;
            Vector_t<String_t> notes = logs->Notes(notes_begin, notes_end);
            Notes(notes);

            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
            mcm->Cursor_Position(2);
            mcm->Add_Header_Option("Notes ");

            for (size_t idx = 0, count = notes.size(); idx < count; idx += 1) {
                mcm->Add_Text_Option(notes[idx], "");
            }

            mcm->Cursor_Position(4 + STRINGS_PER_COLUMN * 2);
            mcm->Add_Header_Option("");
            if (notes_count > 0) {
                Clear_Notes_Option_Variable()->Int(
                    mcm->Add_Text_Option("                        Clear Notes", "")
                );
            } else {
                Clear_Notes_Option_Variable()->Int(
                    mcm->Add_Text_Option("                        Clear Notes", "", MCM::DISABLE)
                );
            }
        }

        {
            Int_t errors_begin = STRINGS_PER_COLUMN * page_index;
            Int_t errors_end = errors_begin + STRINGS_PER_COLUMN;
            Vector_t<String_t> errors = logs->Errors(errors_begin, errors_end);
            Errors(errors);

            mcm->Cursor_Fill_Mode(Cursor_Fill_Mode_e::TOP_TO_BOTTOM);
            mcm->Cursor_Position(3);
            mcm->Add_Header_Option("Errors ");

            for (size_t idx = 0, count = errors.size(); idx < count; idx += 1) {
                mcm->Add_Text_Option(errors[idx], "");
            }

            mcm->Cursor_Position(5 + STRINGS_PER_COLUMN * 2);
            mcm->Add_Header_Option("");
            if (errors_count > 0) {
                Clear_Errors_Option_Variable()->Int(
                    mcm->Add_Text_Option("                         Clear Errors", "")
                );
            } else {
                Clear_Errors_Option_Variable()->Int(
                    mcm->Add_Text_Option("                         Clear Errors", "", MCM::DISABLE)
                );
            }
        }
    }

    void Logs_t::On_Option_Select(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t* mcm = Main();

        if (option == Previous_Option_Variable()->Int()) {
            Int_t page_index = Page_Index();
            if (page_index == 0) {
                page_index = Page_Count() - 1;
            } else {
                page_index -= 1;
            }
            Page_Index(page_index);
            mcm->Reset_Page();
            mcm->Return_Latent(user_callback);
        } else if (option == Next_Option_Variable()->Int()) {
            Int_t page_index = Page_Index();
            if (page_index == Page_Count() - 1) {
                page_index = 0;
            } else {
                page_index += 1;
            }
            Page_Index(page_index);
            mcm->Reset_Page();
            mcm->Return_Latent(user_callback);
        } else if (option == Clear_Notes_Option_Variable()->Int()) {
            Modules::Logs_t::Self()->Clear_Notes();
            mcm->Reset_Page();
            mcm->Return_Latent(user_callback);
        } else if (option == Clear_Errors_Option_Variable()->Int()) {
            Modules::Logs_t::Self()->Clear_Errors();
            mcm->Reset_Page();
            mcm->Return_Latent(user_callback);
        } else {
            mcm->Return_Latent(user_callback);
        }
    }

    void Logs_t::On_Option_Menu_Open(Int_t option)
    {

    }

    void Logs_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {

    }

    void Logs_t::On_Option_Slider_Open(Int_t option)
    {

    }

    void Logs_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {

    }

    void Logs_t::On_Option_Input_Accept(Int_t option, String_t value)
    {

    }

    void Logs_t::On_Option_Keymap_Change(Int_t option,
                                         Int_t key_code,
                                         String_t conflict,
                                         String_t conflicting_mod,
                                         Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t::Self()->Return_Latent(user_callback);
    }

    void Logs_t::On_Option_Default(Int_t option, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        MCM::Main_t::Self()->Return_Latent(user_callback);
    }

    void Logs_t::On_Option_Highlight(Int_t option)
    {
        MCM::Main_t* mcm = Main();

        if (option == Previous_Option_Variable()->Int()) {
            mcm->Info_Text("Go to the Previous Page");
        } else if (option == Next_Option_Variable()->Int()) {
            mcm->Info_Text("Go to the Next Page");
        } else if (option == Clear_Notes_Option_Variable()->Int()) {
            mcm->Info_Text("Clear All Notes");
        } else if (option == Clear_Errors_Option_Variable()->Int()) {
            mcm->Info_Text("Clear All Errors");
        } else {
            Int_t idx = floorf((option - Options_Offset_Variable()->Int() - HEADERS_PER_PAGE) / 2.0f);
            if (idx % 2 == 0) {
                Array_t* notes = Notes();
                if (notes && idx < notes->count) {
                    mcm->Info_Text(notes->Point(idx)->String());
                }
            } else {
                Array_t* errors = Errors();
                if (errors && idx < errors->count) {
                    mcm->Info_Text(errors->Point(idx)->String());
                }
            }
        }
    }

    void Logs_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Logs_t,                \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}}
