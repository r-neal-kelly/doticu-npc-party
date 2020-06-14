/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "cell.h"

namespace doticu_npcp { namespace Cell {

    enum
    {
        f_CELL_IS_INTERIOR = 0x0001
    };

    bool Is_Interior(TESObjectCELL *cell)
    {
        if (cell)
        {
            return (cell->unk040 & f_CELL_IS_INTERIOR) == f_CELL_IS_INTERIOR;
        }
        else
        {
            return false;
        }
    }

    bool Is_Exterior(TESObjectCELL *cell)
    {
        if (cell)
        {
            return (cell->unk040 & f_CELL_IS_INTERIOR) != f_CELL_IS_INTERIOR;
        }
        else
        {
            return false;
        }
    }

}}

namespace doticu_npcp { namespace Cell { namespace Exports {

    bool Is_Interior(Selfless_t *, TESObjectCELL *cell)
    {
        return Cell::Is_Interior(cell);
    }

    bool Register(VMClassRegistry *registry)
    {
        registry->RegisterFunction(
            new NativeFunction1 <Selfless_t, bool, TESObjectCELL *>(
                "Cell_Is_Interior",
                "doticu_npcp",
                Exports::Is_Interior,
                registry)
        );

        return true;
    }

}}}
