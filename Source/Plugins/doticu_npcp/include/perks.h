/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Papyrus { namespace Perks {

    void Execute_Perk(Perk_t* perk, Reference_t* ref, Actor_t* unknown_actor);

    void Execute_Kiss_Thrall(Reference_t* ref, Actor_t* unknown_actor);
    void Execute_Resurrect(Reference_t* ref, Actor_t* unknown_actor);
    void Execute_Reanimate(Reference_t* ref, Actor_t* unknown_actor);
    void Execute_Unparalyze(Reference_t* ref, Actor_t* unknown_actor);

}}}

namespace doticu_npcp { namespace Papyrus { namespace Perks { namespace Exports {

    Bool_t Register(VMClassRegistry *registry);

}}}}
