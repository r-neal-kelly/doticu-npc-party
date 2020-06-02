/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace XContainer {

    XContainer_t *Create(TESObjectREFR *owner);
    XContainer_t::Data *Create_Data(TESObjectREFR *owner);
    XEntries_t *Create_Data_Entries();

}}
