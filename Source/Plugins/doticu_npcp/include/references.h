/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace References {

    void On_Open(Reference_t* ref, Reference_t* activator);
    void Expoee_Button_On_Activate(Reference_t* ref, Reference_t* activator);

}}}

namespace doticu_npcp { namespace Papyrus { namespace References { namespace Exports {

    Bool_t Register(VMClassRegistry *registry);

}}}}
