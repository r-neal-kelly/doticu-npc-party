/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

#include "party/party_alias.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    class Greeter_t : public Alias_t {
    public:
        static constexpr Float_t MAX_WAIT_TIME = 10.0f;
        static constexpr Float_t UPDATE_INTERVAL = 0.5f;

        static String_t Class_Name();
        static Class_Info_t* Class_Info();
        static Greeter_t* Self();
        static Object_t* Object();

    public:
        Variable_t* Variable(String_t variable_name);

        Variable_t* Is_Locked_Variable(); // Bool_t
        Variable_t* Actor_Variable(); // Actor_t
        Variable_t* Time_Waited_Variable(); // Float_t

        Topic_t* Actor_To_Topic(Actor_t* actor);

        void Lock(Callback_t<Greeter_t*>* on_lock, Float_t interval = 0.2f, Float_t limit = 10.0f);
        void Unlock();

        void Start(Actor_t* actor, Callback_t<Int_t, Greeter_t*>* user_callback = nullptr);
        void Start_Impl(Actor_t* actor, Callback_t<Int_t, Greeter_t*>* user_callback);
        void Stop(Callback_t<Int_t, Actor_t*>* user_callback = nullptr);
        void Stop_Impl(Callback_t<Int_t, Actor_t*>* user_callback);

        void Update();
        void Update_Impl(Callback_t<Greeter_t*>* user_callback);

    public:
        static void Register_Me(Virtual_Machine_t* vm);
    };

}}}
