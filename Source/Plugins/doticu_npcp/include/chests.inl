/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/extra_list.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/reference_container_entry.h"

#include "chests.h"

namespace doticu_npcp {

    template <typename T,
        std::enable_if_t<
            std::is_same<T, Functor_i<maybe<Reference_t*>, some<Bound_Object_t*>>&>::value ||
            std::is_same<T, maybe<Reference_t*>(*)(some<Bound_Object_t*>)>::value ||
            std::is_same<T, some<Reference_t*>(*)(some<Bound_Object_t*>)>::value,
            Bool_t
        >
    > inline void Chests_t::Categorize_Into_Chests(some<Reference_t*> reference, T Chest)
    {
        SKYLIB_ASSERT_SOME(reference);

        Reference_Container_t container(reference);
        if (container.Is_Valid()) {
            for (size_t idx = 0, end = container.Count(); idx < end; idx += 1) {
                Reference_Container_Entry_t& entry = container[idx];
                some<Bound_Object_t*> object = entry.Some_Object();
                if (!object->Is_Leveled_Item() && object->Is_Playable()) {
                    maybe<Reference_t*> chest = Chest(object)();
                    if (chest && chest != reference) {
                        entry.Remove_Count_To(container, entry.Non_Extra_Lists_Count(), chest());
                        Vector_t<some<Extra_List_t*>> x_lists = entry.Some_Extra_Lists();
                        for (size_t idx = 0, end = x_lists.size(); idx < end; idx += 1) {
                            some<Extra_List_t*> x_list = x_lists[idx];
                            if (!x_list->Is_Quest_Item()) { // maybe we should allow this here and filter above this func?
                                entry.Remove_To(container, x_list, chest());
                            }
                        }
                    }
                }
            }
        }
    }

}
