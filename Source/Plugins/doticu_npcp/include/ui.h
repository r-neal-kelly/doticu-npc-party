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

    inline void Run(String_t menu, String_t target)
    {
        return Run<Bool_t>(menu, target, false);
    }

    inline Bool_t Is_In_Menu_Mode()
    {
        MenuManager* menu_manager = MenuManager::GetSingleton();
        if (menu_manager) {
            return menu_manager->IsShowingMenus();
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

}}}
