/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/container.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/reference_container_entry.h"

#include "consts.h"
#include "party_member_suitcase.h"

namespace doticu_npcp { namespace Party {

    some<Member_Suitcase_t*> Member_Suitcase_t::Create()
    {
        return static_cast<some<Member_Suitcase_t*>>(Container_t::Create_Reference(
            Consts_t::NPCP::Container::Empty(),
            Consts_t::NPCP::Reference::Storage_Marker()
        ));
    }

    void Member_Suitcase_t::Destroy(some<Member_Suitcase_t*> suitcase)
    {
        SKYLIB_ASSERT_SOME(suitcase);
        suitcase->Remove_All_Items(none<Reference_t*>(), false);
        suitcase->Mark_For_Delete();
    }

    void Member_Suitcase_t::Copy_Items(some<Reference_t*> from, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables)
    {
        SKYLIB_ASSERT_SOME(from);
        SKYLIB_ASSERT_SOME(suit_type);

        some<Faction_t*> suit_faction = suit_type().As_Faction()();
        SKYLIB_ASSERT_SOME(suit_faction);

        Reference_Container_t this_container(this);
        if (this_container.Is_Valid()) {
            Reference_Container_t from_container(from);
            if (from_container.Is_Valid()) {
                for (size_t idx = 0, end = from_container.Count(); idx < end; idx += 1) {
                    Reference_Container_Entry_t& from_entry = from_container[idx];
                    if (!from_entry.Is_Leveled_Item() && (allow_unplayables || from_entry.Is_Playable_Item())) {
                        some<Bound_Object_t*> bound_object = from_entry.Some_Object();
                        Container_Entry_Count_t non_x_list_count = from_entry.Non_Extra_Lists_Count();
                        Vector_t<some<Extra_List_t*>> x_lists = from_entry.Some_Extra_Lists();
                        size_t x_list_count = x_lists.size();
                        if (non_x_list_count > 0 || x_list_count > 0) {
                            some<Reference_Container_Entry_t*> this_entry = this_container.Some_Entry(bound_object);
                            if (non_x_list_count > 0) {
                                some<Extra_List_t*> x_list = Reference_Container_Entry_t::Some_Extra_List(non_x_list_count);
                                x_list->Owner(suit_faction);
                                this_entry->Add(this_container, x_list);
                            }
                            for (size_t idx = 0, end = x_list_count; idx < end; idx += 1) {
                                some<Extra_List_t*> x_list = x_lists[idx];
                                if (!x_list->Should_Be_Destroyed()) {
                                    some<Extra_List_t*> x_list_copy = Reference_Container_Entry_t::Some_Extra_List_Copy(x_list);
                                    x_list_copy->Owner(suit_faction);
                                    this_entry->Add(this_container, x_list_copy);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void Member_Suitcase_t::Move_Items(some<Reference_t*> from, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables)
    {
        // this will apply the owner faction flag, and make everything an xlist of course
    }

    void Member_Suitcase_t::Apply_Items(some<Reference_t*> unto, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables)
    {
        // this fulfills the outfitting procedure. pass in whatever else is needed.
    }

    void Member_Suitcase_t::Remove_Items(maybe<Reference_t*> to, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables)
    {
        // removes the flag, maybe keeps xlist. can move to a pack or community chests otherwise
    }

    void Member_Suitcase_t::Remove_All_Items(maybe<Reference_t*> to, Bool_t allow_unplayables)
    {
        // move everything to reference or community chests.
    }

}}
