/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Alias_t : public Alias_Base_t {
    public:
        Int_t ID();
        Actor_t* Actor();

        Bool_t Is_Filled();
        Bool_t Is_Unfilled();

        void Fill(Actor_t* actor, Virtual_Callback_i** callback);
        void Unfill(Virtual_Callback_i** callback);

        void Queue(Callback_t<>* user_callback);

        void Register_Key(Int_t key_code, Virtual_Callback_i* vcallback = nullptr);
        void Unregister_Key(Int_t key_code, Virtual_Callback_i* vcallback = nullptr);
        void Unregister_Keys(Virtual_Callback_i* vcallback = nullptr);
        void Register_Control(String_t control, Virtual_Callback_i* vcallback = nullptr);
        void Unregister_Control(String_t control, Virtual_Callback_i* vcallback = nullptr);
        void Unregister_Controls(Virtual_Callback_i* vcallback = nullptr);
        void Register_For_Crosshair_Change(Virtual_Callback_i* vcallback = nullptr);
        void Unregister_For_Crosshair_Change(Virtual_Callback_i* vcallback = nullptr);
        void Register_Menu(String_t menu_name, Virtual_Callback_i* vcallback = nullptr);
        void Unregister_Menus(Virtual_Callback_i* vcallback = nullptr);

        template <typename Alias_tm>
        void Lock(Alias_tm* self, Callback_t<Alias_tm*>* on_lock, Float_t interval = 0.2f, Float_t limit = 10.0f);
        template <typename Alias_tm>
        void Unlock(Alias_tm* self);
    };

}}}
