/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

namespace doticu_npcp { namespace Followers {

    void Stash(TESQuest *quest);

}}

namespace doticu_npcp { namespace Followers { namespace Exports {

    void Stash(StaticFunctionTag *, TESQuest *quest);

    bool Register(VMClassRegistry *registry);

}}}
