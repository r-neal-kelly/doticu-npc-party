/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameForms.h"
#include "skse64/PapyrusNativeFunctions.h"

namespace doticu_npcp { namespace Follower {

    BGSBaseAlias *Get_Member(BGSBaseAlias *follower);

}}

namespace doticu_npcp { namespace Follower { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
