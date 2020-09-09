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
    };

}}}
