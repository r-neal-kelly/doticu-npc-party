/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "party.h"
#include "party.inl"
#include "quest.h"

namespace doticu_npcp { namespace Party {

    Int_t Alias_t::ID()
    {
        return id;
    }

    Actor_t* Alias_t::Actor()
    {
        return Quest::Alias_Actor(quest, id);
    }

    Bool_t Alias_t::Is_Filled()
    {
        return Quest::Is_Alias_Filled(quest, id);
    }

    Bool_t Alias_t::Is_Unfilled()
    {
        return !Quest::Is_Alias_Filled(quest, id);
    }

    void Alias_t::Fill(Actor_t* actor, Virtual_Callback_i** callback)
    {
        struct Arguments : public Virtual_Arguments_t {
        public:
            Reference_t* ref;
            Arguments(Reference_t* ref) :
                ref(ref)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Pack(ref);

                return true;
            }
        } arguments(actor);

        Virtual_Machine_t::Self()->Call_Method(this, "ReferenceAlias", "ForceRefTo", &arguments, callback);
    }

    void Alias_t::Unfill(Virtual_Callback_i** callback)
    {
        Virtual_Machine_t::Self()->Call_Method(this, "ReferenceAlias", "Clear", nullptr, callback);
    }

}}
