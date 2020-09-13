/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "funcs.h"
#include "papyrus.inl"
#include "utils.h"

namespace doticu_npcp { namespace Modules {

    String_t Funcs_t::Class_Name()
    {
        static const String_t class_name = String_t("doticu_npcp_funcs");
        NPCP_ASSERT(class_name);
        return class_name;
    }

    Class_Info_t* Funcs_t::Class_Info()
    {
        static Class_Info_t* class_info = Class_Info_t::Fetch(Class_Name());
        NPCP_ASSERT(class_info);
        return class_info;
    }

    Funcs_t* Funcs_t::Self()
    {
        return static_cast<Funcs_t*>(Consts::Funcs_Quest());
    }

    Object_t* Funcs_t::Object()
    {
        Object_t* object = Object_t::Fetch(Self(), Class_Name());
        NPCP_ASSERT(object);
        object->Decrement_Lock();
        return object;
    }

    Variable_t* Funcs_t::Variable(String_t variable_name)
    {
        return Object()->Variable(variable_name);
    }

    void Funcs_t::Wait(Float_t seconds, Virtual_Callback_i** callback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Float_t seconds;
            Arguments(Float_t seconds) :
                seconds(seconds)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Float(seconds);
                return true;
            }
        } arguments(seconds);

        Virtual_Machine_t::Self()->Call_Method(
            Consts::Funcs_Quest(),
            Class_Name(),
            "Wait",
            &arguments,
            callback
        );
    }

    void Funcs_t::Wait_Out_Of_Menu(Float_t seconds, Virtual_Callback_i** callback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Float_t seconds;
            Arguments(Float_t seconds) :
                seconds(seconds)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Float(seconds);
                return true;
            }
        } arguments(seconds);

        Virtual_Machine_t::Self()->Call_Method(
            Consts::Funcs_Quest(),
            Class_Name(),
            "Wait_Out_Of_Menu",
            &arguments,
            callback
        );
    }

    void Funcs_t::Open_Container(Reference_t* container, Virtual_Callback_i* vcallback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Reference_t* container;
            Arguments(Reference_t* container) :
                container(container)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Pack(container);
                return true;
            }
        } arguments(container);

        Virtual_Machine_t::Self()->Call_Method(
            Consts::Funcs_Quest(),
            Class_Name(),
            "Open_Container",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

    void Funcs_t::Close_Menus(Virtual_Callback_i* vcallback)
    {
        Virtual_Machine_t::Self()->Call_Method(
            Consts::Funcs_Quest(),
            Class_Name(),
            "Close_Menus",
            nullptr,
            vcallback ? &vcallback : nullptr
        );
    }

    void Funcs_t::Register_Me(Virtual_Machine_t* vm)
    {
        #define METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                           \
            FORWARD_METHOD(vm, Class_Name(), Funcs_t,               \
                           STR_FUNC_, ARG_NUM_,                     \
                           RETURN_, METHOD_, __VA_ARGS__);          \
        W

        #undef METHOD
    }

}}
