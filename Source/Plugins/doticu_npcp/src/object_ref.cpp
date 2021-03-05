/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

namespace doticu_npcp { namespace Object_Ref {

    Bool_t Has_Similar_XList(Reference_t* ref, Form_t* form, XList_t* xlist_to_compare)
    {
        if (ref) {
            XContainer_t* xcontainer = Get_XContainer(ref, false);
            if (xcontainer) {
                XEntry_t* xentry = xcontainer->XEntry(form, false);
                if (xentry) {
                    return xentry->Has_Similar_XList(xlist_to_compare);
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void Remove_If(Reference_t* from,
                   Reference_t* to,
                   Bool_t(*should_remove_xform)(Form_t*),
                   Bool_t(*should_remove_xlist)(XList_t*, Form_t*),
                   Bool_t(*should_remove_bform)(Form_t*))
    {
        NPCP_ASSERT(from);

        Bool_t do_delete_to;
        if (to) {
            Init_Container_If_Needed(to);
            do_delete_to = false;
        } else {
            to = Create_Container();
            do_delete_to = true;
        }

        if (!should_remove_xform) {
            should_remove_xform = [](Form_t*) -> Bool_t
            {
                return true;
            };
        }

        if (!should_remove_xlist) {
            should_remove_xlist = [](XList_t* xlist, Form_t*) -> Bool_t
            {
                return !XList::Is_Quest_Item(xlist);
            };
        }

        if (!should_remove_bform) {
            should_remove_bform = should_remove_xform;
        }

        XContainer_t* xcontainer = Object_Ref::Get_XContainer(from, false);
        if (xcontainer && xcontainer->changes && xcontainer->changes->xentries) {
            std::vector<XEntry_t*> xentries_to_destroy;
            xentries_to_destroy.reserve(4);

            for (XEntries_t::Iterator xentries = xcontainer->changes->xentries->Begin(); !xentries.End(); ++xentries) {
                XEntry_t* xentry = xentries.Get();
                if (xentry) {
                    Form_t* form = xentry->form;
                    if (form) {
                        //xentry->Validate(Get_BEntry_Count(from, form));
                        if (should_remove_xform(form) && xentry->xlists) {
                            std::vector<XList_t*> xlists_to_remove;
                            xlists_to_remove.reserve(2);

                            for (XLists_t::Iterator xlists = xentry->xlists->Begin(); !xlists.End(); ++xlists) {
                                XList_t* xlist = xlists.Get();
                                if (xlist) {
                                    XList::Validate(xlist, xentry->delta_count, Get_BEntry_Count(from, xentry->form));
                                    if (should_remove_xlist(xlist, form)) {
                                        xlists_to_remove.push_back(xlist);
                                    }
                                }
                            }

                            if (xlists_to_remove.size() > 0) {
                                XEntry_t* to_xentry = Object_Ref::Get_XEntry(to, form, true);
                                for (size_t idx = 0, count = xlists_to_remove.size(); idx < count; idx += 1) {
                                    XList_t* xlist = xlists_to_remove[idx];
                                    xentry->Move_XList(to_xentry, to, xlist);
                                }
                            }
                        }

                        if (xentry->Delta_Count() == 0) {
                            xentries_to_destroy.push_back(xentry);
                        }
                    } else {
                        xentries_to_destroy.push_back(xentry);
                    }
                }
            }

            for (size_t idx = 0, count = xentries_to_destroy.size(); idx < count; idx += 1) {
                XEntry_t* xentry = xentries_to_destroy[idx];
                Object_Ref::Remove_XEntry(from, xentry);
                XEntry_t::Destroy(xentry);
            }
        }

        BContainer_t* bcontainer = Object_Ref::Get_BContainer(from);
        if (bcontainer) {
            std::vector<BEntry_t*> bentries_to_move;
            bentries_to_move.reserve(4);

            for (size_t idx = 0, count = bcontainer->numEntries; idx < count; idx += 1) {
                BEntry_t* bentry = bcontainer->entries[idx];
                if (bentry && bentry->form && bentry->count > 0) {
                    Form_t* form = bentry->form;
                    if (form->formType != kFormType_LeveledItem && should_remove_bform(form)) {
                        bentries_to_move.push_back(bentry);
                    }
                }
            }

            if (bentries_to_move.size() > 0) {
                for (size_t idx = 0, count = bentries_to_move.size(); idx < count; idx += 1) {
                    BEntry_t* bentry = bentries_to_move[idx];
                    XEntry_t* xentry = Get_XEntry(from, bentry->form, true);
                    Int_t entry_count = bentry->count + xentry->Delta_Count();
                    if (entry_count > 0) {
                        XEntry_t* to_xentry = Get_XEntry(to, bentry->form, true);

                        to_xentry->Increment(entry_count);
                        xentry->Delta_Count(0 - bentry->count);
                    }
                }
            }
        }

        if (do_delete_to) {
            Delete_Safe(to);
        }
    }

    void Remove_Wearables(Reference_t* ref, Reference_t* destination, Bool_t do_remove_quest_items)
    {
        Bool_t do_delete_destination;
        if (destination) {
            Init_Container_If_Needed(destination);
            do_delete_destination = false;
        } else {
            destination = Create_Container();
            do_delete_destination = true;
        }
        Object_Ref::Inventory_t destination_inventory(destination);

        Object_Ref::Inventory_t ref_inventory(ref);
        for (size_t idx = 0, end = ref_inventory.entries.size(); idx < end; idx += 1) {
            Object_Ref::Entry_t& ref_entry = ref_inventory.entries[idx];
            Form_t* form = ref_entry.form;
            if (form && form->formType != kFormType_LeveledItem) {
                if (form->IsArmor() || form->IsWeapon() || form->IsAmmo() || form->IsLight()) {
                    Object_Ref::Entry_t* destination_entry = destination_inventory.Entry(form);
                    Vector_t<XList_t*> xlists = ref_entry.XLists();
                    for (size_t idx = 0, end = xlists.size(); idx < end; idx += 1) {
                        XList_t* xlist = xlists[idx];
                        if (xlist && (do_remove_quest_items || !XList::Is_Quest_Item(xlist))) {
                            if (xlist && XList::Is_Outfit2_Item(xlist, ref->baseForm)) {
                                XList::Owner(xlist, nullptr);
                            }
                            if (!destination_entry) {
                                destination_entry = destination_inventory.Add_Entry(form);
                            }
                            ref_inventory.Remove_XList(&ref_entry, xlist);
                            destination_inventory.Add_XList(destination_entry, xlist);
                        }
                    }
                    Int_t loose_count = ref_inventory.Count_Loose(&ref_entry);
                    if (loose_count > 0) {
                        if (!destination_entry) {
                            destination_entry = destination_inventory.Add_Entry(form);
                        }
                        ref_inventory.Remove_Loose(&ref_entry, loose_count);
                        destination_inventory.Add_Loose(destination_entry, loose_count);
                    }
                }
            }
        }

        if (do_delete_destination) {
            Delete_Safe(destination);
        }
    }

    void Remove_Unwearables(Reference_t* obj, Reference_t* other, Bool_t remove_quest_items)
    {
        auto should_remove_xform = [](Form_t* form) -> Bool_t
        {
            return !form->IsArmor() && !form->IsWeapon() && !form->IsAmmo();
        };

        Bool_t(*should_remove_xlist)(XList_t*, Form_t*);
        if (remove_quest_items) {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return true;
            };
        } else {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return !XList::Is_Quest_Item(xlist);
            };
        }

        Remove_If(obj, other, should_remove_xform, should_remove_xlist);
    }

    void Remove_Non_Outfit_Worn(Reference_t* obj, Reference_t* other, Bool_t remove_quest_items)
    {
        auto should_remove_xform = [](Form_t* form) -> Bool_t
        {
            return true;
        };

        Bool_t(*should_remove_xlist)(XList_t*, Form_t*);
        if (remove_quest_items) {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return true;
            };
        } else {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return !XList::Is_Quest_Item(xlist);
            };
        }

        auto should_remove_bform = [](Form_t* form) -> Bool_t
        {
            return false;
        };

        Remove_If(obj, other, should_remove_xform, should_remove_xlist, should_remove_bform);
    }

    void Remove_All_Items(Reference_t* ref, Reference_t* transfer, Bool_t remove_quest_items, Bool_t remove_unplayable_items)
    {
        Bool_t(*should_remove_xform)(Form_t*);
        if (remove_unplayable_items) {
            should_remove_xform = [](Form_t* form) -> Bool_t
            {
                return true;
            };
        } else {
            should_remove_xform = [](Form_t* form) -> Bool_t
            {
                return form->IsPlayable();
            };
        }

        Bool_t(*should_remove_xlist)(XList_t*, Form_t*);
        if (remove_quest_items) {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return true;
            };
        } else {
            should_remove_xlist = [](XList_t* xlist, Form_t* form) -> Bool_t
            {
                return !XList::Is_Quest_Item(xlist);
            };
        }

        Remove_If(ref, transfer, should_remove_xform, should_remove_xlist);
    }

    Bool_t Contains_Form(Reference_t* ref, Form_t* form)
    {
        if (ref && form) {
            BContainer_t* bcontainer = Object_Ref::Get_BContainer(ref);
            if (bcontainer) {
                for (size_t idx = 0, count = bcontainer->numEntries; idx < count; idx += 1) {
                    BEntry_t* bentry = bcontainer->entries[idx];
                    if (bentry && bentry->form == form && bentry->count > 0) {
                        XEntry_t* xentry = Get_XEntry(ref, form, false);
                        if (!xentry || xentry->Delta_Count() > 0 - bentry->count) {
                            return true;
                        }
                    }
                }
            }
            XContainer_t* xcontainer = Object_Ref::Get_XContainer(ref, false);
            if (xcontainer) {
                for (XEntries_t::Iterator it = xcontainer->changes->xentries->Begin(); !it.End(); ++it) {
                    XEntry_t* xentry = it.Get();
                    if (xentry && xentry->form == form && xentry->Delta_Count() > 0) {
                        return true;
                    }
                }
            }
            return false;
        } else {
            return false;
        }
    }

    void Categorize(Reference_t *ref, Bool_t only_custom_categories) {
        if (ref) {
            Vector_t<XEntry_t*> xentries_to_destroy;
            xentries_to_destroy.reserve(2);

            XContainer_t* xcontainer = Get_XContainer(ref, false);
            if (xcontainer) {
                for (XEntries_t::Iterator it = xcontainer->changes->xentries->Begin(); !it.End(); ++it) {
                    XEntry_t* xentry = it.Get();
                    if (xentry && xentry->form && xentry->form->IsPlayable()) {
                        Reference_t* category = only_custom_categories ?
                            Game::Get_NPCP_Custom_Category(xentry->form) :
                            Game::Get_NPCP_Category(xentry->form);
                        Init_Container_If_Needed(category);
                        if (category && category != ref) {
                            Int_t bentry_count = Get_BEntry_Count(ref, xentry->form);
                            xentry->Validate(bentry_count);

                            XEntry_t* category_xentry = nullptr;

                            Vector_t<XList_t*> xlists_to_move;
                            xlists_to_move.reserve(2);
                            for (XLists_t::Iterator it = xentry->xlists->Begin(); !it.End(); ++it) {
                                XList_t* xlist = it.Get();
                                if (xlist) {
                                    xlists_to_move.push_back(xlist);
                                }
                            }

                            size_t xlists_to_move_count = xlists_to_move.size();
                            if (xlists_to_move_count > 0) {
                                category_xentry = Get_XEntry(category, xentry->form, true);
                                NPCP_ASSERT(category_xentry);
                                for (size_t idx = 0; idx < xlists_to_move_count; idx += 1) {
                                    XList_t* xlist = xlists_to_move[idx];
                                    xentry->Move_XList(category_xentry, category, xlist);
                                }
                            }
                            
                            Int_t bentry_negation = 0 - bentry_count;
                            if (xentry->Delta_Count() < bentry_negation) {
                                xentry->Delta_Count(bentry_negation);
                            }

                            if (xentry->Delta_Count() > bentry_negation) {
                                if (!category_xentry) {
                                    category_xentry = Get_XEntry(category, xentry->form, true);
                                    NPCP_ASSERT(category_xentry);
                                }
                                category_xentry->Increment(xentry->Delta_Count() - bentry_negation);
                                xentry->Delta_Count(bentry_negation);
                            }

                            if (xentry->Delta_Count() == 0) {
                                xentries_to_destroy.push_back(xentry);
                            }
                        }
                    }
                }
            }

            for (size_t idx = 0, count = xentries_to_destroy.size(); idx < count; idx += 1) {
                XEntry_t* xentry = xentries_to_destroy[idx];
                Remove_XEntry(ref, xentry);
                XEntry_t::Destroy(xentry);
            }

            BContainer_t* bcontainer = Object_Ref::Get_BContainer(ref);
            if (bcontainer) {
                for (size_t idx = 0; idx < bcontainer->numEntries; idx += 1) {
                    BEntry_t* bentry = bcontainer->entries[idx];
                    if (bentry && bentry->form && bentry->count > 0) {
                        if (bentry->form->IsPlayable() && bentry->form->formType != kFormType_LeveledItem) {
                            if (Get_XEntry(ref, bentry->form, false) == nullptr) {
                                Reference_t* category = only_custom_categories ?
                                    Game::Get_NPCP_Custom_Category(bentry->form) :
                                    Game::Get_NPCP_Category(bentry->form);
                                Init_Container_If_Needed(category);
                                if (category && category != ref) {
                                    XEntry_t* category_xentry = Get_XEntry(category, bentry->form, true);
                                    NPCP_ASSERT(category_xentry);
                                    category_xentry->Increment(bentry->count);
                                    XEntry_t* xentry = Get_XEntry(ref, bentry->form, true);
                                    NPCP_ASSERT(xentry);
                                    xentry->Delta_Count(0 - bentry->count);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    bool Has_Token(Reference_t* ref, Form_t* token, Int_t count)
    {
        if (ref && token && count > 0) {
            return Get_Entry_Count(ref, token) == count;
        } else {
            return false;
        }
    }

    void Token(Reference_t* ref, Form_t* token, Int_t count)
    {
        if (ref && token && count > 0) {
            Int_t bentry_count = Object_Ref::Get_BEntry_Count(ref, token);
            if (bentry_count == count) {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, false);
                if (xentry) {
                    Object_Ref::Remove_XEntry(ref, xentry);
                    XEntry_t::Destroy(xentry);
                }
            } else {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, true);
                if (xentry) {
                    if (xentry->Delta_Count() + bentry_count != count) {
                        xentry->Delta_Count(count - bentry_count);
                    }
                } else {
                    _MESSAGE("unable to get xentry for adding token.");
                }
            }
        }
    }

    void Untoken(Reference_t* ref, Form_t* token)
    {
        if (ref && token) {
            Int_t bentry_count = Object_Ref::Get_BEntry_Count(ref, token);
            if (bentry_count == 0) {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, false);
                if (xentry) {
                    Object_Ref::Remove_XEntry(ref, xentry);
                    XEntry_t::Destroy(xentry);
                }
            } else {
                XEntry_t* xentry = Object_Ref::Get_XEntry(ref, token, true);
                if (xentry) {
                    if (xentry->Delta_Count() + bentry_count != 0) {
                        xentry->Delta_Count(0 - bentry_count);
                    }
                } else {
                    _MESSAGE("unable to get xentry for removing token.");
                }
            }
        }
    }

    void Rename(Reference_t* ref, String_t new_name)
    {
        if (ref && new_name.data) {
            XList::Validate_No_Count(&ref->extraData);
            referenceUtils::SetDisplayName(&ref->extraData, new_name, true);
        }

        /*if (ref) {
            XList::Validate(&ref->extraData);
            ExtraTextDisplay* xtext = static_cast<ExtraTextDisplay*>(ref->extraData.GetByType(kExtraData_TextDisplayData));
            if (xtext) {
                xtext->Force_Rename(new_name);
            } else {
                xtext = XData::Create_Text_Display(new_name);
                if (xtext) {
                    ref->extraData.Add(kExtraData_TextDisplayData, xtext);
                }
            }
        }*/
    }

    Reference_t* Create_Marker_At(Reference_t* ref, Static_t* static_marker)
    {
        if (ref) {
            Reference_t* marker = Place_At_Me(ref, static_marker, 1, true, false);
            if (marker) {
                marker->pos.x = ref->pos.x;
                marker->pos.y = ref->pos.y;
                marker->pos.z = ref->pos.z;
                marker->rot.x = ref->rot.x;
                marker->rot.y = ref->rot.y;
                marker->rot.z = ref->rot.z;
                marker->Update_3D_Position();
                return marker;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Reference_t* Create_Marker_At(Reference_t* ref)
    {
        return Create_Marker_At(ref, Consts::X_Marker_Static());
    }

    Reference_t* Create_Directed_Marker_At(Reference_t* ref)
    {
        return Create_Marker_At(ref, Consts::Directed_X_Marker_Static());
    }

    Reference_t* Create_Container()
    {
        Reference_t* container = Place_At_Me(Consts::Storage_Marker(), Consts::Empty_Container(), 1, true, false);
        NPCP_ASSERT(container);
        Init_Container_If_Needed(container);
        return container;
    }

    bool Is_In_Interior_Cell(Reference_t* ref)
    {
        if (ref) {
            return ref->parentCell && Cell::Is_Interior(ref->parentCell);
        } else {
            return false;
        }
    }

    bool Is_In_Exterior_Cell(Reference_t* ref)
    {
        if (ref) {
            return ref->parentCell && Cell::Is_Exterior(ref->parentCell);
        } else {
            return false;
        }
    }

}}
