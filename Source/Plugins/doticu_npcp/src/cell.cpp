/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "cell.h"
#include "utils.h"

#include "papyrus.inl"

namespace doticu_npcp { namespace Cell {

    enum {
        f_CELL_IS_INTERIOR = 0x0001
    };

    bool Is_Interior(TESObjectCELL* cell)
    {
        if (cell) {
            return (cell->unk040 & f_CELL_IS_INTERIOR) == f_CELL_IS_INTERIOR;
        } else {
            return false;
        }
    }

    bool Is_Exterior(TESObjectCELL* cell)
    {
        if (cell) {
            return (cell->unk040 & f_CELL_IS_INTERIOR) != f_CELL_IS_INTERIOR;
        } else {
            return false;
        }
    }

    Vector_t<Reference_t*> References(Cell_t* cell, Form_t* of_base)
    {
        NPCP_ASSERT(cell);
        NPCP_ASSERT(of_base);

        Vector_t<Reference_t*> references;
        references.reserve(8);

        Cell_t::ReferenceData* ref_datas = &cell->refData;
        for (size_t idx = 0, count = ref_datas->maxSize; idx < count; idx += 1) {
            Cell_t::ReferenceData::Reference* ref_data = ref_datas->refArray + idx;
            Reference_t* reference = ref_data->unk08 ? ref_data->ref : nullptr;
            if (reference && reference->baseForm && reference->baseForm == of_base) {
                references.push_back(reference);
            }
        }

        return references;
    }

}}

namespace doticu_npcp { namespace Cell { namespace Exports {

    bool Register(VMClassRegistry *registry)
    {
        return true;
    }

}}}
