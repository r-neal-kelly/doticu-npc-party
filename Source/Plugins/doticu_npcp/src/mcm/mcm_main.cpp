/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/PapyrusUI.h"

#include "consts.h"
#include "utils.h"

#include "mcm/mcm_main.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Papyrus { namespace UI {

    template <typename Type>
    Type Get_Value(GFxValue* gfx_value)
    {
        NPCP_ASSERT(false);
    }

    template <>
    Bool_t Get_Value<Bool_t>(GFxValue* gfx_value)
    {
        return gfx_value->GetType() == GFxValue::kType_Bool ? gfx_value->GetBool() : false;
    }

    template <>
    Int_t Get_Value<Int_t>(GFxValue* gfx_value)
    {
        return gfx_value->GetType() == GFxValue::kType_Number ? gfx_value->GetNumber() : 0;
    }

    template <>
    Float_t Get_Value<Float_t>(GFxValue* gfx_value)
    {
        return gfx_value->GetType() == GFxValue::kType_Number ? gfx_value->GetNumber() : 0.0f;
    }

    template <>
    String_t Get_Value<String_t>(GFxValue* gfx_value)
    {
        return gfx_value->GetType() == GFxValue::kType_String ? gfx_value->GetString() : "";
    }

    template <typename Type>
    Type Get_Value(String_t menu, String_t target)
    {
        if (menu.data && target.data) {
            MenuManager* menu_manager = MenuManager::GetSingleton();
            if (menu_manager) {
                GFxMovieView* view = menu_manager->GetMovieView(&menu);
                if (view) {
                    GFxValue value;
                    if (view->GetVariable(&value, target.data)) {
                        return Get_Value<Type>(&value);
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    template <typename Type>
    void Set_Value(GFxValue* gfx_value, Type value)
    {
        NPCP_ASSERT(false);
    }

    template <>
    void Set_Value<Bool_t>(GFxValue* gfx_value, Bool_t value)
    {
        gfx_value->SetBool(value);
    }

    template <>
    void Set_Value<Int_t>(GFxValue* gfx_value, Int_t value)
    {
        gfx_value->SetNumber(value);
    }

    template <>
    void Set_Value<Float_t>(GFxValue* gfx_value, Float_t value)
    {
        gfx_value->SetNumber(value);
    }

    template <>
    void Set_Value<String_t>(GFxValue* gfx_value, String_t value)
    {
        if (value.data) {
            gfx_value->SetString(value.data);
        } else {
            gfx_value->SetString("");
        }
    }

    template <typename Type>
    void Set_Value(String_t menu, String_t target, Type value)
    {
        if (menu.data && target.data) {
            MenuManager* menu_manager = MenuManager::GetSingleton();
            if (menu_manager) {
                GFxMovieView* view = menu_manager->GetMovieView(&menu);
                if (view) {
                    GFxValue gfx_value;
                    Set_Value<Type>(&gfx_value, value);
                    view->SetVariable(target.data, &gfx_value, 1);
                }
            }
        }
    }

    template <typename Type>
    void Run(String_t menu, String_t target, Type argument)
    {
        if (menu.data && target.data) {
            UIManager* ui_manager = UIManager::GetSingleton();
            if (ui_manager) {
                UIInvokeDelegate delegate(menu.data, target.data);
                delegate.args.resize(1);
                Set_Value<Type>(&delegate.args[0], argument);
                delegate.Run();
            }
        }
    }

    void Run(String_t menu, String_t target)
    {
        return Run<Bool_t>(menu, target, false);
    }

}}}

namespace doticu_npcp { namespace MCM {

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

    String_t SKI_Config_Base_t::Current_Page_Name()
    {
        return Current_Page_Name_Variable()->String();
    }

    Int_t SKI_Config_Base_t::Current_Page_Number()
    {
        return Current_Page_Number_Variable()->Int();
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

    void SKI_Config_Base_t::Reset()
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

    void SKI_Config_Base_t::Title_Text(String_t title)
    {
        UI::Run<String_t>("Journal Menu", "_root.ConfigPanelFader.configPanel" ".setTitleText", title);
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

    void SKI_Config_Base_t::Option_Number_Value(Int_t index, Float_t value, Bool_t do_render)
    {
        NPCP_ASSERT(Current_State() != State_e::RESET);

        UI::Set_Value<Int_t>("Journal Menu", "_root.ConfigPanelFader.configPanel" ".optionCursorIndex", index);
        UI::Set_Value<Float_t>("Journal Menu", "_root.ConfigPanelFader.configPanel" ".optionCursor.numValue", value);
        if (do_render) {
            UI::Run("Journal Menu", "_root.ConfigPanelFader.configPanel" ".invalidateOptionData");
        }
    }

    void SKI_Config_Base_t::Option_String_Value(Int_t index, String_t value, Bool_t do_render)
    {
        NPCP_ASSERT(Current_State() != State_e::RESET);

        UI::Set_Value<Int_t>("Journal Menu", "_root.ConfigPanelFader.configPanel" ".optionCursorIndex", index);
        UI::Set_Value<String_t>("Journal Menu", "_root.ConfigPanelFader.configPanel" ".optionCursor.strValue", value);
        if (do_render) {
            UI::Run("Journal Menu", "_root.ConfigPanelFader.configPanel" ".invalidateOptionData");
        }
    }

    void SKI_Config_Base_t::Text_Option_Value(Int_t option, String_t text, Bool_t do_render)
    {
        Int_t index = option % 0x100;
        Option_Type_e type = static_cast<Option_Type_e>
            (Flags()->Point(index)->Int() % 0x100);
        NPCP_ASSERT(type == Option_Type_e::TEXT);

        Option_String_Value(index, text, do_render);
    }

    void SKI_Config_Base_t::Keymap_Option_Value(Int_t option, Int_t key_code, Bool_t do_render)
    {
        Int_t index = option % 0x100;
        Option_Type_e type = static_cast<Option_Type_e>
            (Flags()->Point(index)->Int() % 0x100);
        NPCP_ASSERT(type == Option_Type_e::KEYMAP);

        Option_Number_Value(index, static_cast<Float_t>(key_code), do_render);
    }

    void SKI_Config_Base_t::Show_Message(String_t message,
                                         Bool_t allow_cancel,
                                         String_t accept,
                                         String_t cancel,
                                         Virtual_Callback_i** callback)
    {
        class Arguments : public Virtual_Arguments_t {
        public:
            String_t message;
            Bool_t allow_cancel;
            String_t accept;
            String_t cancel;
            Arguments(String_t message, Bool_t allow_cancel, String_t accept, String_t cancel) :
                message(message), allow_cancel(allow_cancel), accept(accept), cancel(cancel)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(4);
                arguments->At(0)->String(message);
                arguments->At(1)->Bool(allow_cancel);
                arguments->At(2)->String(accept);
                arguments->At(3)->String(cancel);
                return true;
            }
        } arguments(message, allow_cancel, accept, cancel);

        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "ShowMessage", &arguments, callback);
    }

    void SKI_Config_Base_t::Reset_Page()
    {
        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "ForcePageReset");
    }

    void SKI_Config_Base_t::Register_Me(Registry_t* registry)
    {
        auto Reset = [](SKI_Config_Base_t* self)->void FORWARD_VOID(SKI_Config_Base_t::Reset());

        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD(Class_Name(), MCM::SKI_Config_Base_t,      \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, METHOD_, __VA_ARGS__);            \
        W

        ADD_METHOD("ClearOptionBuffers", 0, void, Reset);

        #undef ADD_METHOD
    }

}}

namespace doticu_npcp { namespace MCM {

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

    void Main_t::Set_Option_Flags(Variable_t* option_in, Int_t flags, Bool_t do_render)
    {
        NPCP_ASSERT(option_in);

        struct Arguments : public Virtual_Arguments_t {
        public:
            Int_t option;
            Int_t flags;
            Bool_t dont_render;
            Arguments(Int_t option, Int_t flags, Bool_t dont_render) :
                option(option), flags(flags), dont_render(dont_render)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(3);
                arguments->At(0)->Int(option);
                arguments->At(1)->Int(flags);
                arguments->At(2)->Bool(dont_render);

                return true;
            }
        } arguments(option_in->Int(), flags, !do_render);

        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "SetOptionFlags", &arguments);
    }

    void Main_t::Enable_Option(Variable_t* option_in, Bool_t do_render)
    {
        NPCP_ASSERT(option_in);
        Set_Option_Flags(option_in, MCM::NONE, do_render);
    }

    void Main_t::Disable_Option(Variable_t* option_in, Bool_t do_render)
    {
        NPCP_ASSERT(option_in);
        Set_Option_Flags(option_in, MCM::DISABLE, do_render);
    }

    void Main_t::Register_Me(Registry_t* registry)
    {
        return;
    }

}}
