/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusUI.h"

#include "papyrus.h"
#include "papyrus.inl"

namespace doticu_npcp { namespace Papyrus { namespace UI {

    template <typename Type>
    inline Type Get_Value(GFxValue* gfx_value)
    {
        NPCP_ASSERT(false);
    }

    template <>
    inline Bool_t Get_Value<Bool_t>(GFxValue* gfx_value)
    {
        return gfx_value->GetType() == GFxValue::kType_Bool ? gfx_value->GetBool() : false;
    }

    template <>
    inline Int_t Get_Value<Int_t>(GFxValue* gfx_value)
    {
        return gfx_value->GetType() == GFxValue::kType_Number ? gfx_value->GetNumber() : 0;
    }

    template <>
    inline Float_t Get_Value<Float_t>(GFxValue* gfx_value)
    {
        return gfx_value->GetType() == GFxValue::kType_Number ? gfx_value->GetNumber() : 0.0f;
    }

    template <>
    inline String_t Get_Value<String_t>(GFxValue* gfx_value)
    {
        return gfx_value->GetType() == GFxValue::kType_String ? gfx_value->GetString() : "";
    }

    template <typename Type>
    inline Type Get_Value(String_t menu, String_t target)
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
    inline void Set_Value(GFxValue* gfx_value, Type value)
    {
        NPCP_ASSERT(false);
    }

    template <>
    inline void Set_Value<Bool_t>(GFxValue* gfx_value, Bool_t value)
    {
        gfx_value->SetBool(value);
    }

    template <>
    inline void Set_Value<Int_t>(GFxValue* gfx_value, Int_t value)
    {
        gfx_value->SetNumber(value);
    }

    template <>
    inline void Set_Value<Float_t>(GFxValue* gfx_value, Float_t value)
    {
        gfx_value->SetNumber(value);
    }

    template <>
    inline void Set_Value<String_t>(GFxValue* gfx_value, String_t value)
    {
        if (value.data) {
            gfx_value->SetString(value.data);
        } else {
            gfx_value->SetString("");
        }
    }

    template <typename Type>
    inline void Set_Value(String_t menu, String_t target, Type value)
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
    inline void Run(String_t menu, String_t target, Type argument)
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

    template <typename Type>
    inline void Run(String_t menu, String_t target, Vector_t<Type> arguments)
    {
        if (menu.data && target.data) {
            UIManager* ui_manager = UIManager::GetSingleton();
            if (ui_manager) {
                size_t argument_count = arguments.size();
                UIInvokeDelegate delegate(menu.data, target.data);
                delegate.args.resize(argument_count);
                for (size_t idx = 0; idx < argument_count; idx += 1) {
                    Set_Value<Type>(&delegate.args[idx], arguments[idx]);
                }
                delegate.Run();
            }
        }
    }

    template <typename Type>
    inline void Run(String_t menu, String_t target, Array_t* arguments)
    {
        if (menu.data && target.data) {
            UIManager* ui_manager = UIManager::GetSingleton();
            if (ui_manager) {
                size_t argument_count = arguments->count;
                UIInvokeDelegate delegate(menu.data, target.data);
                delegate.args.resize(argument_count);
                for (size_t idx = 0; idx < argument_count; idx += 1) {
                    Set_Value<Type>(&delegate.args[idx], *reinterpret_cast<Type*>(&arguments->Point(idx)->data));
                }
                delegate.Run();
            }
        }
    }

    inline void Run(String_t menu, String_t target)
    {
        return Run<Bool_t>(menu, target, false);
    }

    inline Bool_t Is_In_Menu_Mode()
    {
        MenuManager* menu_manager = MenuManager::GetSingleton();
        if (menu_manager) {
            return reinterpret_cast<Menu_Manager_t*>(menu_manager)->menu_stack.count > 1;
        } else {
            return false;
        }
    }

    inline Bool_t Is_Menu_Open(String_t menu)
    {
        MenuManager* menu_manager = MenuManager::GetSingleton();
        if (menu_manager) {
            return menu_manager->IsMenuOpen(&menu);
        } else {
            return false;
        }
    }

    inline void Message_Box(String_t message, Virtual_Callback_i* vcallback = nullptr)
    {
        struct VArguments : public Virtual_Arguments_t {
            String_t message;
            VArguments(String_t message) :
                message(message)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->String(message);
                return true;
            }
        } arguments(message);

        Virtual_Machine_t::Self()->Call_Global(
            "Debug",
            "MessageBox",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

    inline void Notification(String_t note, Virtual_Callback_i* vcallback = nullptr)
    {
        struct VArguments : public Virtual_Arguments_t {
            String_t note;
            VArguments(String_t note) :
                note(note)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->String(note);
                return true;
            }
        } arguments(note);

        Virtual_Machine_t::Self()->Call_Global(
            "Debug",
            "Notification",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

}}}
