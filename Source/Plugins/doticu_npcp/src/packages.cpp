/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "consts.h"
#include "packages.h"
#include "papyrus.inl"
#include "utils.h"

#include "party/party_player.h"

namespace doticu_npcp { namespace Papyrus { namespace Packages {

    void Execute_Package(Package_t* package, Actor_t* actor)
    {
        if (package == Consts::Menu_Exit_Package()) {
            return Execute_Menu_Exit();
        }
    }

    void Execute_Menu_Exit()
    {
        Party::Player_t::Self()->Close_Global_Dialogue_Menu();
    }

}}}

namespace doticu_npcp { namespace Papyrus { namespace Packages { namespace Exports {

    void Execute_Package(Selfless_t*, Package_t* package, Actor_t* actor)
    {
        return Packages::Execute_Package(package, actor);
    }

    Bool_t Register(VMClassRegistry* registry)
    {
        #define ADD_GLOBAL(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("doticu_npcp_main", Selfless_t,            \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Exports::METHOD_, __VA_ARGS__);   \
        W

        ADD_GLOBAL("Execute_Package", 2, void, Execute_Package, Package_t*, Actor_t*);

        #undef ADD_GLOBAL

        return true;
    }

}}}}
