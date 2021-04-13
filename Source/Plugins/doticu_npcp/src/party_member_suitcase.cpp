/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/armor.h"
#include "doticu_skylib/container.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/extra_owner.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/reference_container_entry.h"

#include "chests.h"
#include "consts.h"
#include "party_member_suitcase.h"

namespace doticu_npcp { namespace Party {

    Member_Suitcase_t::Suit_Entry_t::Suit_Entry_t(some<Bound_Object_t*> bound_object) :
        bound_object(bound_object), copies()
    {
        copies.reserve(2);
    }

    Member_Suitcase_t::Suit_Entry_t::Suit_Entry_t(some<Bound_Object_t*> bound_object,
                                                  Vector_t<some<Extra_List_t*>> copies) :
        bound_object(bound_object), copies(std::move(copies))
    {
    }

    Member_Suitcase_t::Suit_Entry_t::Suit_Entry_t(Suit_Entry_t&& other) noexcept :
        bound_object(std::move(other.bound_object)), copies(std::move(other.copies))
    {
    }

    Member_Suitcase_t::Suit_Entry_t::~Suit_Entry_t()
    {
    }

    Bool_t Member_Suitcase_t::Suit_Entry_t::Has_Copies()
    {
        return this->copies.size() > 0;
    }

    Bool_t Member_Suitcase_t::Suit_Entry_t::Destroy_Copy_If_Equals(some<Extra_List_t*> extra_list)
    {
        class Has_Equal_Extra_Datas_Filter_t :
            public Filter_i<Extra_Type_e>
        {
        public:
            virtual Bool_t operator ()(Extra_Type_e extra_type) override
            {
                return
                    extra_type != Extra_Type_e::OUTFIT &&
                    extra_type != Extra_Type_e::WORN &&
                    extra_type != Extra_Type_e::WORN_LEFT;
            }
        };
        static Has_Equal_Extra_Datas_Filter_t filter;

        for (size_t idx = 0, end = this->copies.size(); idx < end; idx += 1) {
            some<Extra_List_t*> copy = this->copies[idx];
            if (copy->Has_Equal_Extra_Datas(extra_list, filter)) {
                this->copies.Unstable_Remove(copy);
                Extra_List_t::Destroy(copy);
                return true;
            }
        }
        return false;
    }

    Member_Suitcase_t::Suit_Entries_t::Suit_Entries_t() :
        entries()
    {
        entries.reserve(4);
    }

    Member_Suitcase_t::Suit_Entries_t::Suit_Entries_t(Vector_t<Suit_Entry_t> entries) :
        entries(std::move(entries))
    {
    }

    Member_Suitcase_t::Suit_Entries_t::Suit_Entries_t(Suit_Entries_t&& other) noexcept :
        entries(std::move(other.entries))
    {
    }

    Member_Suitcase_t::Suit_Entries_t::~Suit_Entries_t()
    {
    }

    Bool_t Member_Suitcase_t::Suit_Entries_t::Has_Copies()
    {
        for (size_t idx = 0, end = this->entries.size(); idx < end; idx += 1) {
            if (this->entries[idx].Has_Copies()) {
                return true;
            }
        }
        return false;
    }

    size_t Member_Suitcase_t::Suit_Entries_t::Count()
    {
        return this->entries.size();
    }

    maybe<Member_Suitcase_t::Suit_Entry_t*> Member_Suitcase_t::Suit_Entries_t::Maybe_Entry(some<Bound_Object_t*> bound_object)
    {
        for (size_t idx = 0, end = this->entries.size(); idx < end; idx += 1) {
            if (this->entries[idx].bound_object == bound_object) {
                return &this->entries[idx];
            }
        }
        return none<Suit_Entry_t*>();
    }

    some<Member_Suitcase_t::Suit_Entry_t*> Member_Suitcase_t::Suit_Entries_t::Some_Entry(some<Bound_Object_t*> bound_object)
    {
        maybe<Suit_Entry_t*> entry = Maybe_Entry(bound_object);
        if (!entry) {
            this->entries.push_back(Suit_Entry_t(bound_object));
            entry = &this->entries[this->entries.size() - 1];
            SKYLIB_ASSERT_SOME(entry);
        }
        return entry();
    }

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
        suitcase->Move_All_To(none<Reference_t*>(), false);
        suitcase->Mark_For_Delete();
    }

    void Member_Suitcase_t::Copy_From(some<Reference_t*> from, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables)
    {
        SKYLIB_ASSERT_SOME(from);
        SKYLIB_ASSERT_SOME(suit_type);

        some<Faction_t*> suit_faction = suit_type().As_Faction()();
        SKYLIB_ASSERT_SOME(suit_faction);

        Reference_Container_t this_container(this);
        SKYLIB_ASSERT(this_container.Is_Valid());

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

    void Member_Suitcase_t::Move_From(some<Reference_t*> from, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables)
    {
        SKYLIB_ASSERT_SOME(from);
        SKYLIB_ASSERT_SOME(suit_type);

        some<Faction_t*> suit_faction = suit_type().As_Faction()();
        SKYLIB_ASSERT_SOME(suit_faction);

        Reference_Container_t this_container(this);
        SKYLIB_ASSERT(this_container.Is_Valid());

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
                            from_entry.Decrement_Count(from_container, non_x_list_count);
                            some<Extra_List_t*> x_list = Reference_Container_Entry_t::Some_Extra_List(non_x_list_count);
                            x_list->Owner(suit_faction);
                            this_entry->Add(this_container, x_list);
                        }
                        for (size_t idx = 0, end = x_list_count; idx < end; idx += 1) {
                            some<Extra_List_t*> x_list = x_lists[idx];
                            if (!x_list->Should_Be_Destroyed()) {
                                x_list->Owner(suit_faction);
                                from_entry.Remove_To(from_container, x_list, this_container);
                            }
                        }
                    }
                }
            }
        }
    }

    void Member_Suitcase_t::Move_To(maybe<Reference_t*> to, some<Member_Suit_Type_e> suit_type, Bool_t allow_unplayables)
    {
        SKYLIB_ASSERT_SOME(suit_type);

        some<Faction_t*> suit_faction = suit_type().As_Faction()();
        SKYLIB_ASSERT_SOME(suit_faction);

        Reference_Container_t this_container(this);
        SKYLIB_ASSERT(this_container.Is_Valid());

        for (size_t idx = 0, end = this_container.Count(); idx < end; idx += 1) {
            Reference_Container_Entry_t& this_entry = this_container[idx];
            if (!this_entry.Is_Leveled_Item() && (allow_unplayables || this_entry.Is_Playable_Item())) {
                some<Bound_Object_t*> bound_object = this_entry.Some_Object();
                some<Reference_t*> to_reference = to ? to() : Chests_t::Chest(bound_object);
                Container_Entry_Count_t non_x_list_count = this_entry.Non_Extra_Lists_Count();
                if (non_x_list_count > 0) {
                    this_entry.Remove_Count_To(this_container, non_x_list_count, to_reference);
                }
                Vector_t<some<Extra_List_t*>> x_lists = this_entry.Some_Extra_Lists();
                for (size_t idx = 0, end = x_lists.size(); idx < end; idx += 1) {
                    some<Extra_List_t*> x_list = x_lists[idx];
                    if (!x_list->Should_Be_Destroyed()) {
                        maybe<Form_Owner_t> owner = x_list->Owner();
                        if (!owner.Has_Value() || owner().As_Faction() == suit_faction) {
                            x_list->Destroy_Extra_Data<Extra_Owner_t>();
                            this_entry.Remove_To(this_container, x_list, to_reference);
                        }
                    }
                }
            }
        }
    }

    void Member_Suitcase_t::Move_All_To(maybe<Reference_t*> to, Bool_t allow_unplayables)
    {
        Reference_Container_t this_container(this);
        SKYLIB_ASSERT(this_container.Is_Valid());

        for (size_t idx = 0, end = this_container.Count(); idx < end; idx += 1) {
            Reference_Container_Entry_t& this_entry = this_container[idx];
            if (!this_entry.Is_Leveled_Item() && (allow_unplayables || this_entry.Is_Playable_Item())) {
                some<Bound_Object_t*> bound_object = this_entry.Some_Object();
                some<Reference_t*> to_reference = to ? to() : Chests_t::Chest(bound_object);
                Container_Entry_Count_t non_x_list_count = this_entry.Non_Extra_Lists_Count();
                if (non_x_list_count > 0) {
                    this_entry.Remove_Count_To(this_container, non_x_list_count, to_reference);
                }
                Vector_t<some<Extra_List_t*>> x_lists = this_entry.Some_Extra_Lists();
                for (size_t idx = 0, end = x_lists.size(); idx < end; idx += 1) {
                    some<Extra_List_t*> x_list = x_lists[idx];
                    if (!x_list->Should_Be_Destroyed()) {
                        x_list->Destroy_Extra_Data<Extra_Owner_t>();
                        this_entry.Remove_To(this_container, x_list, to_reference);
                    }
                }
            }
        }
    }

    Member_Suitcase_t::Suit_Entries_t Member_Suitcase_t::Active_Suit_Entries(some<Member_Suit_Type_e> suit_type,
                                                                             Bool_t allow_unplayables,
                                                                             maybe<Outfit_t*> outfit)
    {
        SKYLIB_ASSERT_SOME(suit_type);

        some<Faction_t*> target_suit_faction = suit_type().As_Faction()();
        SKYLIB_ASSERT_SOME(target_suit_faction);

        some<Faction_t*> active_suit_faction = Member_Suit_Type_e::To_Faction(Member_Suit_Type_e::ACTIVE)();
        SKYLIB_ASSERT_SOME(active_suit_faction);

        Suit_Entries_t entries;

        Reference_Container_t this_container(this);
        SKYLIB_ASSERT(this_container.Is_Valid());

        for (size_t idx = 0, end = this_container.Count(); idx < end; idx += 1) {
            Reference_Container_Entry_t& this_entry = this_container[idx];
            if (!this_entry.Is_Leveled_Item() && (allow_unplayables || this_entry.Is_Playable_Item())) {
                some<Bound_Object_t*> bound_object = this_entry.Some_Object();
                Bool_t is_outfit_item = bound_object->Is_Armor() || bound_object->Is_Weapon() || bound_object->Is_Light();
                some<Suit_Entry_t*> suit_entry = entries.Some_Entry(bound_object);
                Vector_t<some<Extra_List_t*>> x_lists = this_entry.Some_Extra_Lists();
                for (size_t idx = 0, end = x_lists.size(); idx < end; idx += 1) {
                    some<Extra_List_t*> x_list = x_lists[idx];
                    if (!x_list->Should_Be_Destroyed()) {
                        maybe<Form_Owner_t> owner = x_list->Owner();
                        if (owner.Has_Value() && owner().As_Faction() == target_suit_faction) {
                            some<Extra_List_t*> copy = Reference_Container_Entry_t::Some_Extra_List_Copy(x_list);
                            copy->Owner(active_suit_faction);
                            if (is_outfit_item) {
                                copy->Outfit(outfit);
                            } else {
                                copy->Outfit(none<Outfit_t*>());
                            }
                            suit_entry->copies.push_back(copy);
                        }
                    }
                }
            }
        }

        // instead we could always add the blank armor with outfit,
        // and when we have an outfit on actor we can use it to determine if an external outfit change occured.
        if (outfit && !entries.Has_Copies()) {
            some<Suit_Entry_t*> suit_entry = entries.Some_Entry(Consts_t::NPCP::Armor::Blank());
            some<Extra_List_t*> x_list = Extra_List_t::Create();
            x_list->Owner(active_suit_faction);
            x_list->Outfit(outfit);
            suit_entry->copies.push_back(x_list);
        }

        return std::move(entries);
    }

    void Member_Suitcase_t::Apply_Unto(some<Actor_t*> unto,
                                       some<Member_Suit_Type_e> suit_type,
                                       Bool_t allow_unplayables,
                                       Bool_t do_strict,
                                       maybe<Reference_t*> to)
    {
        SKYLIB_ASSERT_SOME(unto);
        SKYLIB_ASSERT_SOME(suit_type);

        some<Faction_t*> active_suit_faction = Member_Suit_Type_e::To_Faction(Member_Suit_Type_e::ACTIVE)();
        SKYLIB_ASSERT_SOME(active_suit_faction);

        Suit_Entries_t suit_entries = Active_Suit_Entries(suit_type, allow_unplayables, unto->Base_Default_Outfit());

        Reference_Container_t unto_container(unto);
        SKYLIB_ASSERT(unto_container.Is_Valid());
        Bool_t has_changed_container = false;

        for (size_t idx = 0, end = unto_container.Count(); idx < end; idx += 1) {
            Reference_Container_Entry_t& unto_entry = unto_container[idx];
            if (!unto_entry.Is_Leveled_Item()) {
                some<Bound_Object_t*> bound_object = unto_entry.Some_Object();
                some<Reference_t*> to_reference = to ? to() : Chests_t::Chest(bound_object);
                maybe<Suit_Entry_t*> suit_entry = suit_entries.Maybe_Entry(bound_object);

                if (do_strict && unto_entry.Is_Playable_Item()) {
                    Container_Entry_Count_t non_x_list_count = unto_entry.Non_Extra_Lists_Count();
                    if (non_x_list_count > 0) {
                        unto_entry.Remove_Count_To(unto_container, unto_entry.Non_Extra_Lists_Count(), to_reference);
                        has_changed_container = true;
                    }
                }

                Vector_t<some<Extra_List_t*>> unto_x_lists = unto_entry.Some_Extra_Lists();
                for (size_t idx = 0, end = unto_x_lists.size(); idx < end; idx += 1) {
                    some<Extra_List_t*> unto_x_list = unto_x_lists[idx];
                    if (!unto_x_list->Should_Be_Destroyed() && !unto_x_list->Is_Quest_Item()) {
                        maybe<Form_Owner_t> unto_owner = unto_x_list->Owner();
                        if (unto_owner.Has_Value() && unto_owner().As_Faction() == active_suit_faction) {
                            if (suit_entry && suit_entry->Has_Copies()) {
                                if (!suit_entry->Destroy_Copy_If_Equals(unto_x_list)) {
                                    unto_entry.Remove(unto_container, unto_x_list);
                                    Extra_List_t::Destroy(unto_x_list);
                                    has_changed_container = true;
                                }
                            } else {
                                unto_entry.Remove(unto_container, unto_x_list);
                                Extra_List_t::Destroy(unto_x_list);
                                has_changed_container = true;
                            }
                        } else if (do_strict && unto_entry.Is_Playable_Item()) {
                            unto_entry.Remove_To(unto_container, unto_x_list, to_reference);
                            has_changed_container = true;
                        } else if (unto_x_list->Is_Outfit_Item()) {
                            unto_entry.Remove(unto_container, unto_x_list);
                            Extra_List_t::Destroy(unto_x_list);
                            has_changed_container = true;
                        }
                    }
                }
            }
        }

        for (size_t idx = 0, end = suit_entries.Count(); idx < end; idx += 1) {
            Suit_Entry_t& suit_entry = suit_entries.entries[idx];
            if (suit_entry.Has_Copies()) {
                some<Reference_Container_Entry_t*> unto_entry = unto_container.Some_Entry(suit_entry.bound_object);
                for (size_t idx = 0, end = suit_entry.copies.size(); idx < end; idx += 1) {
                    unto_entry->Add(unto_container, suit_entry.copies[idx]);
                }
                has_changed_container = true;
            }
        }

        unto_container.Has_Changed(has_changed_container);
    }

}}
