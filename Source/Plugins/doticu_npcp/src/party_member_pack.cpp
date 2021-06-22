/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/container.h"
#include "doticu_skylib/reference.h"

#include "chests.h"
#include "consts.h"
#include "party_member_pack.h"
#include "party_member_suitcase.h"

namespace doticu_skylib { namespace doticu_npcp {

    some<Member_Pack_t*> Member_Pack_t::Create()
    {
        return static_cast<some<Member_Pack_t*>>(Container_t::Create_Reference(
            Consts_t::NPCP::Container::Empty(),
            Consts_t::NPCP::Reference::Storage_Marker()
        ));
    }

    void Member_Pack_t::Destroy(some<Member_Pack_t*> pack)
    {
        SKYLIB_ASSERT_SOME(pack);

        pack->Clear();
        pack->Mark_For_Delete();
    }

    void Member_Pack_t::Clear()
    {
        Reference_Container_t this_container(this);
        SKYLIB_ASSERT(this_container.Is_Valid());

        for (size_t idx = 0, end = this_container.Count(); idx < end; idx += 1) {
            Reference_Container_Entry_t& this_entry = this_container[idx];
            some<Bound_Object_t*> bound_object = this_entry.Some_Object();
            if (!this_entry.Is_Leveled_Item()) {
                if (Member_Suitcase_t::filter_out_blank_or_token_or_unplayable_objects(bound_object)) {
                    some<Reference_t*> to_reference = Chests_t::Chest(bound_object);
                    sp32 non_x_list_count = this_entry.Non_Extra_Lists_Count();
                    if (non_x_list_count > 0) {
                        this_entry.Remove_Count_To(this_container, non_x_list_count, to_reference);
                    }
                    Vector_t<some<Extra_List_t*>> x_lists = this_entry.Some_Extra_Lists();
                    for (size_t idx = 0, end = x_lists.size(); idx < end; idx += 1) {
                        some<Extra_List_t*> x_list = x_lists[idx];
                        if (!x_list->Should_Be_Destroyed()) {
                            x_list->Remove_And_Destroy<Extra_Owner_t>();
                            this_entry.Remove_To(this_container, x_list, to_reference);
                        }
                    }
                } else {
                    sp32 non_x_list_count = this_entry.Non_Extra_Lists_Count();
                    if (non_x_list_count > 0) {
                        this_entry.Decrement_Count(this_container, non_x_list_count);
                    }
                    Vector_t<some<Extra_List_t*>> x_lists = this_entry.Some_Extra_Lists();
                    for (size_t idx = 0, end = x_lists.size(); idx < end; idx += 1) {
                        some<Extra_List_t*> x_list = x_lists[idx];
                        this_entry.Remove_And_Destroy(this_container, x_list);
                    }
                }
            }
        }
    }

}}
