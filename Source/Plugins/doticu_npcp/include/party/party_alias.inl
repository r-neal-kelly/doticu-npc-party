/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "party/party_alias.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    template <typename Base_t>
    inline void Alias_t::Lock(Base_t* self, Callback_t<Base_t*>* on_lock, Float_t interval, Float_t limit)
    {
        if (self->Is_Locked_Variable()->Bool()) {
            struct VCallback : Virtual_Callback_t {
                Base_t* self;
                Callback_t<Base_t*>* on_lock;
                Float_t interval;
                Float_t time_left;
                VCallback(Base_t* self, Callback_t<Base_t*>* on_lock, Float_t interval, Float_t time_left) :
                    self(self), on_lock(on_lock), interval(interval), time_left(time_left)
                {
                }
                void operator()(Variable_t* result)
                {
                    if (self->Is_Locked_Variable()->Bool() && time_left > 0.0f) {
                        self->Alias_t::Lock(self, on_lock, interval, time_left - interval);
                    } else {
                        self->Is_Locked_Variable()->Bool(true);
                        on_lock->operator()(self);
                        delete on_lock;
                    }
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(self, on_lock, interval, limit);
            Modules::Funcs_t::Self()->Wait(interval, &vcallback);
        } else {
            self->Is_Locked_Variable()->Bool(true);
            on_lock->operator()(self);
            delete on_lock;
        }
    }

    template <typename Base_t>
    inline void Alias_t::Unlock(Base_t* self)
    {
        self->Is_Locked_Variable()->Bool(false);
    }

}}}
