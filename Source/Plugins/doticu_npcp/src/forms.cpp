/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_npcp.h"

namespace doticu_npcp {

    VMResultArray<TESForm *> Forms_Slice(StaticFunctionTag *, VMArray<TESForm *> arr, UInt32 idx_from, UInt32 idx_to_ex) {
        VMResultArray<TESForm *> vec_slice;
        UInt32 len_forms = arr.Length();

        if (idx_from < 0) {
            idx_from = 0;
        }
        if (idx_from > len_forms) {
            idx_from = len_forms;
        }
        if (idx_to_ex > len_forms || idx_to_ex < 0) {
            idx_to_ex = len_forms;
        }

        s64 num_elems = idx_to_ex - idx_from;
        if (num_elems < 1) {
            vec_slice.push_back(NULL); // may want to send back empty vec
        } else {
            TESForm *ptr_elem;
            vec_slice.reserve(num_elems);
            for (u64 idx = idx_from, idx_end = idx_to_ex; idx < idx_end; idx += 1) {
                arr.Get(&ptr_elem, idx);
                vec_slice.push_back(ptr_elem);
            }
        }

        return vec_slice;
    }

}
