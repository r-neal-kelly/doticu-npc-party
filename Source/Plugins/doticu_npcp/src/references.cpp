/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "object_ref.h"
#include "papyrus.inl"
#include "references.h"
#include "utils.h"

#include "party/party_mannequins.h"

namespace doticu_npcp { namespace Papyrus { namespace References {

    void On_Open(Reference_t* ref, Reference_t* activator)
    {
        if (ref == Consts::Expo_Exit_Door()) {
            if (activator == Consts::Player_Actor()) {
                Party::Mannequins_t::Self()->Remove_Player();
                Object_Ref::Set_Open(ref, false);
            }
        }
    }

}}}

namespace doticu_npcp { namespace Papyrus { namespace References { namespace Exports {

    void On_Open(Selfless_t*, Reference_t* ref, Reference_t* activator)
    {
        return References::On_Open(ref, activator);
    }

    Bool_t Register(VMClassRegistry* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_reference", Selfless_t,       \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("On_Open", 2, void, On_Open, Reference_t*, Reference_t*);

        #undef ADD_GLOBAL

        return true;
    }

}}}}
