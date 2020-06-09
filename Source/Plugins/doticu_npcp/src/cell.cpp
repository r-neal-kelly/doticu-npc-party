/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "cell.h"

namespace doticu_npcp { namespace Cell {

    enum {
        f_CELL_IS_INTERIOR = 0x0001
    };

    bool Is_Interior(TESObjectCELL *cell) {
        if (!cell) {
            return false;
        }

        return (cell->unk040 & f_CELL_IS_INTERIOR) == f_CELL_IS_INTERIOR;
    }

}}

namespace doticu_npcp { namespace Cell { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        _MESSAGE("Added Cell functions.");

        return true;
    }

}}}
