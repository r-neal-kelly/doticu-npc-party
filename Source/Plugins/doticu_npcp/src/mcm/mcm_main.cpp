/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "form.h"
#include "funcs.h"
#include "papyrus.inl"
#include "ui.h"
#include "utils.h"

#include "mcm/mcm_main.h"
#include "mcm/mcm_followers.h"
#include "mcm/mcm_members.h"
#include "mcm/mcm_mannequins.h"
#include "mcm/mcm_filter.h"
#include "mcm/mcm_chests.h"
#include "mcm/mcm_settings.h"
#include "mcm/mcm_hotkeys.h"
#include "mcm/mcm_logs.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t SKI_Config_Base_t::Class_Name()
    {
        static const String_t class_name = String_t("SKI_ConfigBase");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* SKI_Config_Base_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Object_t* SKI_Config_Base_t::Object()
    {
        Object_t* object = Object_t::Fetch(this, Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* SKI_Config_Base_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* SKI_Config_Base_t::Property(String_t property_name)
    {
        return Object()->Property(property_name);
    }

    Variable_t* SKI_Config_Base_t::Current_Page_Name_Variable() { DEFINE_VARIABLE("_currentPage"); }
    Variable_t* SKI_Config_Base_t::Current_Page_Number_Variable() { DEFINE_VARIABLE("_currentPageNum"); }
    Variable_t* SKI_Config_Base_t::Current_State_Variable() { DEFINE_VARIABLE("_state"); }
    Variable_t* SKI_Config_Base_t::Cursor_Position_Variable() { DEFINE_VARIABLE("_cursorPosition"); }
    Variable_t* SKI_Config_Base_t::Cursor_Fill_Mode_Variable() { DEFINE_VARIABLE("_cursorFillMode"); }
    Variable_t* SKI_Config_Base_t::Flags_Variable() { DEFINE_VARIABLE("_optionFlagsBuf"); }
    Variable_t* SKI_Config_Base_t::Labels_Variable() { DEFINE_VARIABLE("_textBuf"); }
    Variable_t* SKI_Config_Base_t::String_Values_Variable() { DEFINE_VARIABLE("_strValueBuf"); }
    Variable_t* SKI_Config_Base_t::Number_Values_Variable() { DEFINE_VARIABLE("_numValueBuf"); }
    Variable_t* SKI_Config_Base_t::States_Variable() { DEFINE_VARIABLE("_stateOptionMap"); }
    Variable_t* SKI_Config_Base_t::Info_Text_Variable() { DEFINE_VARIABLE("_infoText"); }
    Variable_t* SKI_Config_Base_t::Slider_Parameters_Variable() { DEFINE_VARIABLE("_sliderParams"); }
    Variable_t* SKI_Config_Base_t::Menu_Parameters_Variable() { DEFINE_VARIABLE("_menuParams"); }
    Variable_t* SKI_Config_Base_t::Is_Waiting_For_Message_Variable() { DEFINE_VARIABLE("_waitForMessage"); }
    Variable_t* SKI_Config_Base_t::Message_Result_Variable() { DEFINE_VARIABLE("_messageResult"); }

    Variable_t* SKI_Config_Base_t::Mod_Name_Property() { DEFINE_PROPERTY("ModName"); }
    Variable_t* SKI_Config_Base_t::Pages_Property() { DEFINE_PROPERTY("Pages"); }

    String_t SKI_Config_Base_t::Current_Page_Name()
    {
        return Current_Page_Name_Variable()->String();
    }

    Int_t SKI_Config_Base_t::Current_Page_Number()
    {
        return Current_Page_Number_Variable()->Int();
    }

    void SKI_Config_Base_t::Current_Page(String_t name)
    {
        Array_t* pages = Pages_Property()->Array();
        if (pages) {
            for (size_t idx = 0, count = pages->count; idx < count; idx += 1) {
                String_t page = pages->Point(idx)->String();
                if (String2::Is_Same_Caseless(page, name)) {
                    Current_Page_Name_Variable()->String(name);
                    Current_Page_Number_Variable()->Int(idx + 1);
                    return;
                }
            }
            Current_Page_Name_Variable()->String("");
            Current_Page_Number_Variable()->Int(-1);
        } else {
            Current_Page_Name_Variable()->String("");
            Current_Page_Number_Variable()->Int(-1);
        }
    }

    State_e SKI_Config_Base_t::Current_State()
    {
        return static_cast<State_e>(Current_State_Variable()->Int());
    }

    Int_t SKI_Config_Base_t::Cursor_Position()
    {
        return Cursor_Position_Variable()->Int();
    }

    Cursor_Fill_Mode_e SKI_Config_Base_t::Cursor_Fill_Mode()
    {
        return static_cast<Cursor_Fill_Mode_e>(Cursor_Fill_Mode_Variable()->Int());
    }

    Array_t* SKI_Config_Base_t::Flags()
    {
        return Flags_Variable()->Array();
    }

    Array_t* SKI_Config_Base_t::Labels()
    {
        return Labels_Variable()->Array();
    }

    Array_t* SKI_Config_Base_t::String_Values()
    {
        return String_Values_Variable()->Array();
    }

    Array_t* SKI_Config_Base_t::Number_Values()
    {
        return Number_Values_Variable()->Array();
    }

    Array_t* SKI_Config_Base_t::States()
    {
        return States_Variable()->Array();
    }

    void SKI_Config_Base_t::Cursor_Position(Int_t cursor_position)
    {
        NPCP_ASSERT(cursor_position < 128 && cursor_position >= -1);

        Cursor_Position_Variable()->Int(cursor_position);
    }

    void SKI_Config_Base_t::Cursor_Fill_Mode(Cursor_Fill_Mode_e cursor_fill_mode)
    {
        NPCP_ASSERT(cursor_fill_mode == Cursor_Fill_Mode_e::LEFT_TO_RIGHT ||
                    cursor_fill_mode == Cursor_Fill_Mode_e::TOP_TO_BOTTOM);

        Cursor_Fill_Mode_Variable()->Int(static_cast<Int_t>(cursor_fill_mode));
    }

    Int_t SKI_Config_Base_t::Pack_Flags(Int_t flags, Option_Type_e option_type)
    {
        return (flags * 0x100) + static_cast<Int_t>(option_type);
    }

    Int_t SKI_Config_Base_t::Pack_Option_ID(Int_t page_number, Int_t cursor_position)
    {
        return (page_number * 0x100) + cursor_position;
    }

    void SKI_Config_Base_t::Clear_Buffers()
    {
        Array_t* flags = Flags();
        Array_t* labels = Labels();
        Array_t* strings = String_Values();
        Array_t* numbers = Number_Values();
        Array_t* states = States();

        for (size_t idx = 0, count = 128; idx < count; idx += 1) {
            flags->Point(idx)->Int(0);
            labels->Point(idx)->String("");
            strings->Point(idx)->String("");
            numbers->Point(idx)->Float(0.0f);
            states->Point(idx)->String("");
        }

        Cursor_Position(0);
        Cursor_Fill_Mode(Cursor_Fill_Mode_e::LEFT_TO_RIGHT);
    }

    void SKI_Config_Base_t::Write_Buffers()
    {
        Array_t* flags = Flags();
        Int_t option_count = 0;
        for (size_t idx = 0, count = 128; idx < count; idx += 1) {
            Int_t flag = flags->Point(idx)->Int();
            if (flag != static_cast<Int_t>(Option_Type_e::EMPTY)) {
                option_count += 1;
            }
        }

        UI::Run<Int_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".setOptionFlagsBuffer", flags);
        UI::Run<String_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".setOptionTextBuffer", Labels());
        UI::Run<String_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".setOptionStrValueBuffer", String_Values());
        UI::Run<Float_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".setOptionNumValueBuffer", Number_Values());
        UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".flushOptionBuffers", option_count);
    }

    void SKI_Config_Base_t::Title_Text(String_t title)
    {
        UI::Run<String_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".setTitleText", title);
    }

    String_t SKI_Config_Base_t::Info_Text()
    {
        return Info_Text_Variable()->String();
    }

    void SKI_Config_Base_t::Info_Text(String_t info)
    {
        Info_Text_Variable()->String(info);
    }

    Int_t SKI_Config_Base_t::Add_Option(Option_Type_e option_type, String_t label, String_t string, Float_t number, Int_t flags)
    {
        NPCP_ASSERT(label);
        NPCP_ASSERT(string);
        NPCP_ASSERT(Current_State() == State_e::RESET);

        Int_t position = Cursor_Position();
        if (position != -1) {
            Flags()->Point(position)->Int(Pack_Flags(flags, option_type));
            Labels()->Point(position)->String(label);
            String_Values()->Point(position)->String(string);
            Number_Values()->Point(position)->Float(number);

            Int_t new_position = position + static_cast<Int_t>(Cursor_Fill_Mode());
            if (new_position >= 128) {
                Cursor_Position(-1);
            } else {
                Cursor_Position(new_position);
            }

            return Pack_Option_ID(Current_Page_Number(), position);
        } else {
            return -1;
        }
    }

    Int_t SKI_Config_Base_t::Add_Empty_Option()
    {
        return Add_Option(Option_Type_e::EMPTY, "", "", 0.0f, 0);
    }

    Int_t SKI_Config_Base_t::Add_Header_Option(String_t label, Int_t flags)
    {
        return Add_Option(Option_Type_e::HEADER, label, "", 0.0f, flags);
    }

    Int_t SKI_Config_Base_t::Add_Text_Option(String_t label, String_t value, Int_t flags)
    {
        return Add_Option(Option_Type_e::TEXT, label, value, 0.0f, flags);
    }

    Int_t SKI_Config_Base_t::Add_Toggle_Option(String_t label, Bool_t is_toggled, Int_t flags)
    {
        return Add_Option(Option_Type_e::TOGGLE, label, "", static_cast<Float_t>(is_toggled), flags);
    }

    Int_t SKI_Config_Base_t::Add_Slider_Option(String_t label, Float_t value, String_t format, Int_t flags)
    {
        return Add_Option(Option_Type_e::SLIDER, label, format, value, flags);
    }

    Int_t SKI_Config_Base_t::Add_Menu_Option(String_t label, String_t value, Int_t flags)
    {
        return Add_Option(Option_Type_e::MENU, label, value, 0.0f, flags);
    }

    Int_t SKI_Config_Base_t::Add_Color_Option(String_t label, Int_t color, Int_t flags)
    {
        return Add_Option(Option_Type_e::COLOR, label, "", static_cast<Float_t>(color), flags);
    }

    Int_t SKI_Config_Base_t::Add_Keymap_Option(String_t label, Int_t key_code, Int_t flags)
    {
        return Add_Option(Option_Type_e::KEYMAP, label, "", static_cast<Float_t>(key_code), flags);
    }

    Int_t SKI_Config_Base_t::Add_Input_Option(String_t label, String_t value, Int_t flags)
    {
        return Add_Option(Option_Type_e::INPUT, label, value, 0.0f, flags);
    }

    void SKI_Config_Base_t::Number_Option_Value(Int_t index, Float_t value, Bool_t do_render)
    {
        NPCP_ASSERT(Current_State() != State_e::RESET);

        UI::Set_Value<Int_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".optionCursorIndex", index);
        UI::Set_Value<Float_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".optionCursor.numValue", value);
        if (do_render) {
            UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".invalidateOptionData");
        }
    }

    void SKI_Config_Base_t::String_Option_Value(Int_t index, String_t value, Bool_t do_render)
    {
        NPCP_ASSERT(Current_State() != State_e::RESET);

        UI::Set_Value<Int_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".optionCursorIndex", index);
        UI::Set_Value<String_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".optionCursor.strValue", value);
        if (do_render) {
            UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".invalidateOptionData");
        }
    }

    void SKI_Config_Base_t::Both_Option_Values(Int_t index, String_t string_value, Float_t number_value, Bool_t do_render)
    {
        NPCP_ASSERT(Current_State() != State_e::RESET);

        UI::Set_Value<Int_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".optionCursorIndex", index);
        UI::Set_Value<String_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".optionCursor.strValue", string_value);
        UI::Set_Value<Float_t>(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".optionCursor.numValue", number_value);
        if (do_render) {
            UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".invalidateOptionData");
        }
    }

    void SKI_Config_Base_t::Slider_Dialog_Current_Value(Float_t value)
    {
        NPCP_ASSERT(Current_State() == State_e::SLIDER);

        Slider_Parameters_Variable()->Array()->Point(0)->Float(value);
    }

    void SKI_Config_Base_t::Slider_Dialog_Default_Value(Float_t value)
    {
        NPCP_ASSERT(Current_State() == State_e::SLIDER);

        Slider_Parameters_Variable()->Array()->Point(1)->Float(value);
    }

    void SKI_Config_Base_t::Slider_Dialog_Range_Values(Float_t min, Float_t max)
    {
        NPCP_ASSERT(Current_State() == State_e::SLIDER);

        Array_t* slider_parameters = Slider_Parameters_Variable()->Array();
        slider_parameters->Point(2)->Float(min);
        slider_parameters->Point(3)->Float(max);
    }

    void SKI_Config_Base_t::Slider_Dialog_Interval_Value(Float_t value)
    {
        NPCP_ASSERT(Current_State() == State_e::SLIDER);

        Slider_Parameters_Variable()->Array()->Point(4)->Float(value);
    }

    void SKI_Config_Base_t::Menu_Dialog_Values(Vector_t<String_t> values)
    {
        NPCP_ASSERT(Current_State() == State_e::MENU);

        UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".setMenuDialogOptions", values);
    }

    void SKI_Config_Base_t::Menu_Dialog_Default(Int_t index)
    {
        NPCP_ASSERT(Current_State() == State_e::MENU);

        Menu_Parameters_Variable()->Array()->Point(1)->Int(index);
    }

    void SKI_Config_Base_t::Text_Option_Value(Int_t option, String_t text, Bool_t do_render)
    {
        Int_t index = option % 0x100;
        Option_Type_e type = static_cast<Option_Type_e>
            (Flags()->Point(index)->Int() % 0x100);
        NPCP_ASSERT(type == Option_Type_e::TEXT);

        String_Option_Value(index, text, do_render);
    }

    void SKI_Config_Base_t::Toggle_Option_Value(Int_t option, Bool_t value, Bool_t do_render)
    {
        Int_t index = option % 0x100;
        Option_Type_e type = static_cast<Option_Type_e>
            (Flags()->Point(index)->Int() % 0x100);
        NPCP_ASSERT(type == Option_Type_e::TOGGLE);

        Number_Option_Value(index, static_cast<Float_t>(value), do_render);
    }

    void SKI_Config_Base_t::Slider_Option_Value(Int_t option, Float_t value, String_t format, Bool_t do_render)
    {
        Int_t index = option % 0x100;
        Option_Type_e type = static_cast<Option_Type_e>
            (Flags()->Point(index)->Int() % 0x100);
        NPCP_ASSERT(type == Option_Type_e::SLIDER);

        Both_Option_Values(index, format, value, do_render);
    }

    void SKI_Config_Base_t::Menu_Option_Value(Int_t option, String_t value, Bool_t do_render)
    {
        Int_t index = option % 0x100;
        Option_Type_e type = static_cast<Option_Type_e>
            (Flags()->Point(index)->Int() % 0x100);
        NPCP_ASSERT(type == Option_Type_e::MENU);

        String_Option_Value(index, value, do_render);
    }

    void SKI_Config_Base_t::Input_Option_Value(Int_t option, String_t value, Bool_t do_render)
    {
        Int_t index = option % 0x100;
        Option_Type_e type = static_cast<Option_Type_e>
            (Flags()->Point(index)->Int() % 0x100);
        NPCP_ASSERT(type == Option_Type_e::INPUT);

        String_Option_Value(index, value, do_render);
    }

    void SKI_Config_Base_t::Keymap_Option_Value(Int_t option, Int_t key_code, Bool_t do_render)
    {
        Int_t index = option % 0x100;
        Option_Type_e type = static_cast<Option_Type_e>
            (Flags()->Point(index)->Int() % 0x100);
        NPCP_ASSERT(type == Option_Type_e::KEYMAP);

        Number_Option_Value(index, static_cast<Float_t>(key_code), do_render);
    }

    void SKI_Config_Base_t::Option_Flags(Int_t option, Int_t flags, Bool_t do_render)
    {
        NPCP_ASSERT(Current_State() != State_e::RESET);

        Int_t index = option % 0x100;

        Int_t old_flags = Flags()->Point(index)->Int();
        old_flags %= 0x100;
        old_flags += flags * 0x100;

        Vector_t<Int_t> arguments;
        arguments.reserve(2);
        arguments.push_back(index);
        arguments.push_back(flags);

        UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".setOptionFlags", arguments);
        if (do_render) {
            UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".invalidateOptionData");
        }
    }

    void SKI_Config_Base_t::Show_Message(String_t message,
                                         Bool_t allow_cancel,
                                         String_t accept_label,
                                         String_t cancel_label,
                                         Callback_t<Bool_t>* user_callback)
    {
        using UCallback_t = Callback_t<Bool_t>;

        if (!Is_Waiting_For_Message_Variable()->Bool()) {
            Is_Waiting_For_Message_Variable()->Bool(true);
            Message_Result_Variable()->Bool(false);

            Vector_t<String_t> args;
            args.reserve(3);
            args.push_back(message);
            args.push_back(accept_label);
            if (allow_cancel) {
                args.push_back(cancel_label);
            } else {
                args.push_back("");
            }

            Form::Register_Mod_Event(this, "SKICP_messageDialogClosed", "OnMessageDialogClose");
            UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".showMessageDialog", args);

            struct Waiter : Virtual_Callback_t {
                SKI_Config_Base_t* self;
                UCallback_t* user_callback;
                Waiter(SKI_Config_Base_t* self, UCallback_t* user_callback) :
                    self(self), user_callback(user_callback)
                {
                }
                void operator()(Variable_t* result)
                {
                    if (self->Is_Waiting_For_Message_Variable()->Bool()) {
                        Virtual_Callback_i* vcallback = new Waiter(self, user_callback);
                        Modules::Funcs_t::Self()->Wait(0.1f, &vcallback);
                    } else {
                        Form::Unregister_Mod_Event(self, "SKICP_messageDialogClosed");
                        if (user_callback) {
                            user_callback->operator()(self->Message_Result_Variable()->Bool());
                            delete user_callback;
                        }
                    }
                }
            };
            Virtual_Callback_i* vcallback = new Waiter(this, user_callback);
            Modules::Funcs_t::Self()->Wait(0.1f, &vcallback);
        } else {
            if (user_callback) {
                user_callback->operator()(false);
                delete user_callback;
            }
        }
    }

    void SKI_Config_Base_t::Reset_Page()
    {
        UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".forcePageReset");
    }

    void SKI_Config_Base_t::Unlock()
    {
        UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".unlock", true);
    }

    void SKI_Config_Base_t::Open_Page(String_t page_name)
    {
        if (Current_State() == State_e::RESET) {
            struct VCallback : public Virtual_Callback_t {
                SKI_Config_Base_t* self;
                String_t page_name;
                VCallback(SKI_Config_Base_t* self, String_t page_name) :
                    self(self), page_name(page_name)
                {
                }
                void operator()(Variable_t* result)
                {
                    self->Open_Page(page_name);
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(this, page_name);
            Modules::Funcs_t::Self()->Wait(0.1f, &vcallback);
        } else {
            Current_Page(page_name);
            if (page_name && page_name.data && page_name.data[0]) {
                Title_Text(page_name);
            } else {
                Title_Text(Mod_Name_Property()->String());
            }

            Current_State_Variable()->Int(static_cast<Int_t>(State_e::RESET));
            Clear_Buffers();

            struct VArguments : public Virtual_Arguments_t {
                String_t page_name;
                VArguments(String_t page_name) :
                    page_name(page_name)
                {
                }
                Bool_t operator()(Arguments_t* arguments)
                {
                    arguments->Resize(1);
                    arguments->At(0)->String(page_name);
                    return true;
                }
            } varguments(page_name);
            struct VCallback : public Virtual_Callback_t {
                SKI_Config_Base_t* self;
                VCallback(SKI_Config_Base_t* self) :
                    self(self)
                {
                }
                void operator()(Variable_t* result)
                {
                    self->Write_Buffers();
                    self->Current_State_Variable()->Int(static_cast<Int_t>(State_e::DEFAULT));
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(this);
            Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "OnPageReset", &varguments, &vcallback);
        }
    }

    void SKI_Config_Base_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), SKI_Config_Base_t,     \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        METHOD("ClearOptionBuffers", 0, void, Clear_Buffers);

        #undef METHOD
    }

}}}

namespace doticu_npcp { namespace Papyrus { namespace MCM {

    String_t Main_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_mcm");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Main_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Main_t* Main_t::Self()
    {
        return static_cast<Main_t*>(Consts::Control_Quest());
    }

    Object_t* Main_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Main_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    Variable_t* Main_t::Property(String_t property_name)
    {
        return Object()->Property(property_name);
    }

    Variable_t* Main_t::Last_Page_Variable() { DEFINE_VARIABLE("p_last_page"); }

    void Main_t::Close_Menus(Virtual_Callback_i** callback)
    {
        Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(), "doticu_npcp_funcs", "Close_Menus", nullptr, callback);
    }

    void Main_t::Enable(Int_t option, Bool_t do_render, Bool_t with_unmap)
    {
        Option_Flags(option, with_unmap ? MCM::UNMAP : MCM::NONE, do_render);
    }

    void Main_t::Disable(Int_t option, Bool_t do_render)
    {
        Option_Flags(option, MCM::DISABLE, do_render);
    }

    void Main_t::Show(Int_t option, Bool_t do_render, Bool_t with_unmap)
    {
        Enable(option, do_render, with_unmap);
    }

    void Main_t::Hide(Int_t option, Bool_t do_render)
    {
        Option_Flags(option, MCM::HIDE, do_render);
    }

    void Main_t::Flicker(Int_t option)
    {
        Option_Flags(option, MCM::DISABLE, true);

        struct VCallback : public Virtual_Callback_t {
            Main_t* self;
            Int_t option;
            VCallback(Main_t* self, Int_t option) :
                self(self), option(option)
            {
            }
            void operator()(Variable_t* result)
            {
                if (self->Current_State() != State_e::RESET) {
                    self->Option_Flags(option, MCM::NONE, true);
                }
            }
        };
        Virtual_Callback_i* vcallback = new VCallback(this, option);
        Modules::Funcs_t::Self()->Wait(0.2f, &vcallback);
    }

    String_t Main_t::Concat(const char* a, const char* b)
    {
        return (std::string(a) + b).c_str();
    }

    String_t Main_t::Concat(const char* a, const char* b, const char* c)
    {
        return (std::string(a) + b + c).c_str();
    }

    void Main_t::On_Config_Init()
    {
        Mod_Name_Property()->String(" NPC Party");
    }

    Bool_t Main_t::On_Config_Open(Virtual_Machine_t* vm, Stack_ID_t stack_id)
    {
        Vector_t<String_t> pages;
        pages.reserve(8);

        pages.push_back(FOLLOWERS_PAGE);
        pages.push_back(MEMBERS_PAGE);
        pages.push_back(MANNEQUINS_PAGE);
        pages.push_back(FILTER_PAGE);
        pages.push_back(CHESTS_PAGE);
        pages.push_back(SETTINGS_PAGE);
        pages.push_back(HOTKEYS_PAGE);
        pages.push_back(LOGS_PAGE);

        Pages_Property()->Pack(pages);
        UI::Run(JOURNAL_MENU, "_root.ConfigPanelFader.configPanel" ".setPageNames", pages);

        Variable_t none;
        vm->Return_Latent_Function(stack_id, &none);

        return true;
    }

    void Main_t::On_Build_Page(String_t current_page)
    {
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t* mcm_followers = MCM::Followers_t::Self();
            mcm_followers->View_Followers();
            mcm_followers->On_Build_Page();
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t* mcm_members = MCM::Members_t::Self();
            mcm_members->View_Members();
            mcm_members->On_Build_Page();
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t* mcm_mannequins = MCM::Mannequins_t::Self();
            mcm_mannequins->View_Mannequins();
            mcm_mannequins->On_Build_Page();
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Build_Page();
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Build_Page();
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Build_Page();
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Build_Page();
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Build_Page();
        } /*else {
            String_t last_page = Last_Page_Variable()->String();
            if (last_page && last_page.data && last_page[0]) {
                Open_Page(last_page);
            } else {
                Open_Page(DEFAULT_PAGE);
            }
        }*/

        Last_Page_Variable()->String(current_page);
    }

    void Main_t::On_Option_Select(Int_t option)
    {
        String_t current_page = Current_Page_Name();
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t::Self()->On_Option_Select(option);
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t::Self()->On_Option_Select(option);
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t::Self()->On_Option_Select(option);
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Option_Select(option);
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Option_Select(option);
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Option_Select(option);
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Option_Select(option);
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Option_Select(option);
        }
    }

    void Main_t::On_Option_Menu_Open(Int_t option)
    {
        String_t current_page = Current_Page_Name();
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t::Self()->On_Option_Menu_Open(option);
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t::Self()->On_Option_Menu_Open(option);
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t::Self()->On_Option_Menu_Open(option);
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Option_Menu_Open(option);
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Option_Menu_Open(option);
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Option_Menu_Open(option);
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Option_Menu_Open(option);
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Option_Menu_Open(option);
        }
    }

    void Main_t::On_Option_Menu_Accept(Int_t option, Int_t idx)
    {
        String_t current_page = Current_Page_Name();
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t::Self()->On_Option_Menu_Accept(option, idx);
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t::Self()->On_Option_Menu_Accept(option, idx);
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t::Self()->On_Option_Menu_Accept(option, idx);
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Option_Menu_Accept(option, idx);
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Option_Menu_Accept(option, idx);
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Option_Menu_Accept(option, idx);
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Option_Menu_Accept(option, idx);
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Option_Menu_Accept(option, idx);
        }
    }

    void Main_t::On_Option_Slider_Open(Int_t option)
    {
        String_t current_page = Current_Page_Name();
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t::Self()->On_Option_Slider_Open(option);
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t::Self()->On_Option_Slider_Open(option);
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t::Self()->On_Option_Slider_Open(option);
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Option_Slider_Open(option);
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Option_Slider_Open(option);
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Option_Slider_Open(option);
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Option_Slider_Open(option);
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Option_Slider_Open(option);
        }
    }

    void Main_t::On_Option_Slider_Accept(Int_t option, Float_t value)
    {
        String_t current_page = Current_Page_Name();
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t::Self()->On_Option_Slider_Accept(option, value);
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t::Self()->On_Option_Slider_Accept(option, value);
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t::Self()->On_Option_Slider_Accept(option, value);
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Option_Slider_Accept(option, value);
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Option_Slider_Accept(option, value);
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Option_Slider_Accept(option, value);
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Option_Slider_Accept(option, value);
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Option_Slider_Accept(option, value);
        }
    }

    void Main_t::On_Option_Input_Accept(Int_t option, String_t value)
    {
        String_t current_page = Current_Page_Name();
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t::Self()->On_Option_Input_Accept(option, value);
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t::Self()->On_Option_Input_Accept(option, value);
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t::Self()->On_Option_Input_Accept(option, value);
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Option_Input_Accept(option, value);
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Option_Input_Accept(option, value);
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Option_Input_Accept(option, value);
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Option_Input_Accept(option, value);
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Option_Input_Accept(option, value);
        }
    }

    void Main_t::On_Option_Keymap_Change(Int_t option, Int_t key_code, String_t conflict, String_t conflicting_mod)
    {
        String_t current_page = Current_Page_Name();
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Option_Keymap_Change(option, key_code, conflict, conflicting_mod);
        }
    }

    void Main_t::On_Option_Default(Int_t option)
    {
        String_t current_page = Current_Page_Name();
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t::Self()->On_Option_Default(option);
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t::Self()->On_Option_Default(option);
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t::Self()->On_Option_Default(option);
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Option_Default(option);
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Option_Default(option);
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Option_Default(option);
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Option_Default(option);
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Option_Default(option);
        }
    }

    void Main_t::On_Option_Highlight(Int_t option)
    {
        String_t current_page = Current_Page_Name();
        auto Is_Page = [&current_page](const char* page)->Bool_t
        {
            return String2::Is_Same_Caseless(current_page, page);
        };

        if (Is_Page(FOLLOWERS_PAGE)) {
            MCM::Followers_t::Self()->On_Option_Highlight(option);
        } else if (Is_Page(MEMBERS_PAGE)) {
            MCM::Members_t::Self()->On_Option_Highlight(option);
        } else if (Is_Page(MANNEQUINS_PAGE)) {
            MCM::Mannequins_t::Self()->On_Option_Highlight(option);
        } else if (Is_Page(FILTER_PAGE)) {
            MCM::Filter_t::Self()->On_Option_Highlight(option);
        } else if (Is_Page(CHESTS_PAGE)) {
            MCM::Chests_t::Self()->On_Option_Highlight(option);
        } else if (Is_Page(SETTINGS_PAGE)) {
            MCM::Settings_t::Self()->On_Option_Highlight(option);
        } else if (Is_Page(HOTKEYS_PAGE)) {
            MCM::Hotkeys_t::Self()->On_Option_Highlight(option);
        } else if (Is_Page(LOGS_PAGE)) {
            MCM::Logs_t::Self()->On_Option_Highlight(option);
        }
    }

    void Main_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Main_t,                \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #define LMETHOD(STR_FUNC_, ARG_NUM_, METHOD_, ...)  \
        M                                                   \
            FORWARD_LATENT_METHOD(vm, Class_Name(), Main_t, \
                           STR_FUNC_, ARG_NUM_,             \
                           METHOD_, __VA_ARGS__);           \
        W

        // these should be latent. they will need to pass a callback through the tree. We need
        // LatentNativeFunctions for Hotkeys in specific, so we could just hack it. but,
        // properly speaking, they should all be latent to make sure that SkyUI doesn't change
        // state in the before callback execution (especially with Show_Message())

        METHOD("OnPageReset", 1, void, On_Build_Page, String_t);
        METHOD("OnOptionSelect", 1, void, On_Option_Select, Int_t);
        METHOD("OnOptionMenuOpen", 1, void, On_Option_Menu_Open, Int_t);
        METHOD("OnOptionMenuAccept", 2, void, On_Option_Menu_Accept, Int_t, Int_t);
        METHOD("OnOptionSliderOpen", 1, void, On_Option_Slider_Open, Int_t);
        METHOD("OnOptionSliderAccept", 2, void, On_Option_Slider_Accept, Int_t, Float_t);
        METHOD("OnOptionInputAccept", 2, void, On_Option_Input_Accept, Int_t, String_t);
        METHOD("OnOptionKeymapChange", 4, void, On_Option_Keymap_Change, Int_t, Int_t, String_t, String_t);
        METHOD("OnOptionDefault", 1, void, On_Option_Default, Int_t);
        METHOD("OnOptionHighlight", 1, void, On_Option_Highlight, Int_t);

        //LMETHOD("OnConfigOpen", 0, void, On_Config_Open);

        #undef METHOD
    }

}}}
