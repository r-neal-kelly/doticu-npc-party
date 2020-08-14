/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "utils.h"

#include "mcm/mcm_main.h"

#include "papyrus.inl"

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

    void Main_t::Add_Option(String_t method, Variable_t* option_out, String_t text, String_t value, Int_t flags)
    {
        NPCP_ASSERT(method);
        NPCP_ASSERT(option_out);
        NPCP_ASSERT(text);
        NPCP_ASSERT(value);

        struct Arguments : public Virtual_Arguments_t {
        public:
            String_t text;
            String_t value;
            Int_t flags;
            Arguments(String_t text, String_t value, Int_t flags) :
                text(text), value(value), flags(flags)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(3);
                arguments->At(0)->String(text);
                arguments->At(1)->String(value);
                arguments->At(2)->Int(flags);

                return true;
            }
        } arguments(text, value, flags);

        struct Callback : public Virtual_Callback_t {
        public:
            Variable_t* option_out;
            Callback(Variable_t* option_out) :
                option_out(option_out)
            {
            }
            void operator()(Variable_t* result)
            {
                NPCP_ASSERT(result);
                option_out->Int(result->Int());
            }
        };
        Virtual_Callback_i* callback = new Callback(option_out);

        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), method, &arguments, &callback);
    }

    void Main_t::Add_Text_Option(Variable_t* option_out, String_t text, String_t value, Int_t flags)
    {
        NPCP_ASSERT(option_out);
        NPCP_ASSERT(text);
        NPCP_ASSERT(value);

        Add_Option("AddTextOption", option_out, text, value, flags);
    }

    void Main_t::Add_Menu_Option(Variable_t* option_out, String_t text, String_t value, Int_t flags)
    {
        NPCP_ASSERT(option_out);
        NPCP_ASSERT(text);
        NPCP_ASSERT(value);

        Add_Option("AddMenuOption", option_out, text, value, flags);
    }

    void Main_t::Set_Text_Option(Variable_t* option_in, String_t value, Bool_t do_render)
    {
        NPCP_ASSERT(option_in);
        NPCP_ASSERT(value);

        struct Arguments : public Virtual_Arguments_t {
        public:
            Int_t option;
            String_t value;
            Bool_t dont_render;
            Arguments(Int_t option, String_t value, Bool_t dont_render) :
                option(option), value(value), dont_render(dont_render)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(3);
                arguments->At(0)->Int(option);
                arguments->At(1)->String(value);
                arguments->At(2)->Bool(dont_render);

                return true;
            }
        } arguments(option_in->Int(), value, !do_render);

        Virtual_Machine_t::Self()->Call_Method(this, Class_Name(), "SetTextOptionValue", &arguments);
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
