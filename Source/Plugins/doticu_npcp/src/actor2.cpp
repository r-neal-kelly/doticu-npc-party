/*
    Copyright � 2020 r-neal-kelly, aka doticu
*/

namespace doticu_npcp { namespace Actor2 {

    void Set_Outfit_Basic(Actor_t* actor, Outfit_t* outfit, Bool_t is_sleep_outfit, Bool_t allow_bcontainer)
    {
        NPCP_ASSERT(actor);

        if (is_sleep_outfit) {
            Base_Sleep_Outfit(actor, outfit);
        } else {
            Base_Outfit(actor, outfit);
        }

        if (outfit) {
            Outfit::Add_Item(outfit, Consts::Blank_Armor());
        }

        Object_Ref::Remove_Wearables(actor, nullptr, false);

        Bool_t is_player_teammate = Utils::Is_Bit_On(actor->flags1, Actor_t2::IS_PLAYER_TEAMMATE);
        if (is_player_teammate) {
            actor->flags1 = Utils::Bit_Off(actor->flags1, Actor_t2::IS_PLAYER_TEAMMATE);
        }

        if (allow_bcontainer) {
            actor->ResetInventory(true);
        } else {
            BContainer_t* bcontainer = Object_Ref::Get_BContainer(actor);
            if (bcontainer) {
                UInt32 count = bcontainer->numEntries;
                bcontainer->numEntries = 0;
                actor->ResetInventory(true);
                bcontainer->numEntries = count;
            } else {
                actor->ResetInventory(true);
            }
        }

        XEntry_t* xentry = Object_Ref::Get_XEntry(actor, Consts::Belted_Tunic_Armor());
        if (xentry) {
            for (XLists_t::Iterator xlists = xentry->xlists->Begin(); !xlists.End(); ++xlists) {
                XList_t* xlist = xlists.Get();
                if (xlist) {
                    XList::Validate(xlist, xentry->delta_count, Object_Ref::Get_BEntry_Count(actor, xentry->form));
                    if (xlist->HasType(kExtraData_OutfitItem) && !xlist->HasType(kExtraData_Worn)) {
                        xentry->Remove_XList(xlist);
                        XList::Destroy(xlist);
                        if (xentry->Delta_Count() == 0) {
                            Object_Ref::Remove_XEntry(actor, xentry);
                            XEntry_t::Destroy(xentry);
                            break;
                        }
                    }
                }
            }
        }

        if (is_player_teammate) {
            actor->flags1 = Utils::Bit_On(actor->flags1, Actor_t2::IS_PLAYER_TEAMMATE);
        }
    }

    void Set_Outfit(Actor_t* actor, Outfit_t* outfit, Bool_t is_sleep_outfit)
    {
        if (actor && actor != Party::Player_t::Self()->Actor()) {
            Party::Member_t* member = Party::Members_t::Self()->From_Actor(actor);
            if (member) {
                struct VCallback : public Virtual_Callback_t {
                    Actor_t* actor;
                    Party::Member_t* member;
                    Outfit_t* outfit;
                    VCallback(Actor_t* actor, Party::Member_t* member, Outfit_t* outfit) :
                        actor(actor), member(member), outfit(outfit)
                    {
                    }
                    void operator()(Variable_t* result)
                    {
                        if (result && result->Bool()) {
                            member->Change_Outfit1(outfit);
                        } else {
                            Party::NPCS_t::Self()->Change_Default_Outfit(actor, outfit);
                        }
                    }
                };
                Virtual_Callback_i* vcallback = new VCallback(actor, member, outfit);
                Is_Talking_To_Player(actor, &vcallback);
            } else {
                Set_Outfit_Basic(actor, outfit, is_sleep_outfit, true); // could make this a setting
                Party::NPCS_t::Self()->Change_Default_Outfit(actor, outfit);
            }
        }
    }

    Bool_t Outfit_Inventory_t::Can_Evaluate_Form(Form_t* form)
    {
        static Form_t* linchpin = Consts::Blank_Armor();

        NPCP_ASSERT(form);

        return
            form != linchpin &&
            form->formType != kFormType_LeveledItem &&
            (form->IsPlayable() ||
             form->formType == kFormType_Armor ||
             form->formType == kFormType_Weapon ||
             form->formType == kFormType_Ammo ||
             form->formType == kFormType_Light);
    }

    Outfit_Inventory_t::Outfit_Inventory_t(Reference_t* outfit1_ref, Reference_t* outfit2_ref) :
        outfit1(outfit1_ref), outfit2(outfit2_ref)
    {
        entries.reserve(16);

        for (size_t idx = 0, count = outfit1.entries.size(); idx < count; idx += 1) {
            Entry_t* outfit1_entry = &outfit1.entries[idx];
            Entry_t* outfit2_entry = outfit2.Entry(outfit1_entry->form);
            Int_t loose_count = outfit1.Count_Loose(outfit1_entry);
            if (outfit2_entry) {
                loose_count += outfit2.Count_Loose(outfit2_entry);
            }
            if (loose_count < 0) {
                loose_count = std::numeric_limits<Int_t>::max();
            }
            Outfit_Entry_t entry(outfit1_entry, outfit2_entry, loose_count);
            entries.push_back(entry);
        }

        for (size_t idx = 0, count = outfit2.entries.size(); idx < count; idx += 1) {
            Entry_t* outfit2_entry = &outfit2.entries[idx];
            if (!Entry(outfit2_entry->form)) {
                Outfit_Entry_t entry(nullptr, outfit2_entry, outfit2.Count_Loose(outfit2_entry));
                entries.push_back(entry);
            }
        }
    }

    Outfit_Entry_t::Outfit_Entry_t(Entry_t* outfit1, Entry_t* outfit2, Int_t loose_count)
    {
        auto Combine_Merged_XLists = [&](Entry_t* entry)->void
        {
            if (entry) {
                Merged_XLists_t entry_mxlists = entry->Merged_XLists(true);
                for (size_t idx = 0, count = entry_mxlists.size(); idx < count; idx += 1) {
                    Merged_XList_t& entry_mxlist = entry_mxlists[idx];
                    Merged_XList_t* outfit_mxlist = merged_xlists.Merged_XList(entry_mxlist.at(0));
                    if (outfit_mxlist) {
                        for (size_t idx = 0, count = entry_mxlist.size(); idx < count; idx += 1) {
                            outfit_mxlist->push_back(entry_mxlist[idx]);
                        }
                    } else {
                        merged_xlists.push_back(entry_mxlist);
                    }
                }
            }
        };

        if (outfit1) {
            form = outfit1->form;
            merged_xlists = outfit1->Merged_XLists(true);
            Combine_Merged_XLists(outfit2);
        } else if (outfit2) {
            form = outfit2->form;
            merged_xlists = outfit2->Merged_XLists(true);
            Combine_Merged_XLists(outfit1);
        }

        if (loose_count > 0) {
            loose_xlist = XList::Create();
            XList::Count(loose_xlist, loose_count);
            Merged_XList_t* merged_xlist = merged_xlists.Merged_XList(loose_xlist);
            if (merged_xlist) {
                merged_xlist->push_back(loose_xlist);
            } else {
                Merged_XList_t merged_xlist;
                merged_xlist.push_back(loose_xlist);
                merged_xlists.push_back(merged_xlist);
            }
        } else {
            loose_xlist = nullptr;
        }
    }

    XList_t* Outfit_Entry_t::Copy(Merged_XList_t* outfit_xlist, Actor_Base_t* owner)
    {
        NPCP_ASSERT(outfit_xlist);
        NPCP_ASSERT(owner);

        XList_t* new_xlist = XList::Copy(outfit_xlist->at(0));
        if (!new_xlist) {
            new_xlist = XList::Create();
        }
        XList::Count(new_xlist, outfit_xlist->Count());
        XList::Owner(new_xlist, owner);
        return new_xlist;
    }

    Int_t Outfit_Entry_t::Count()
    {
        return merged_xlists.Count();
    }

    Bool_t Outfit_Entry_t::Is_Worn()
    {
        return merged_xlists.Is_Worn();
    }

    void Outfit_Entry_t::Cleanup()
    {
        if (loose_xlist) {
            XList::Destroy(loose_xlist);
        }
    }

    Outfit_Entry_t* Outfit_Inventory_t::Entry(Form_t* form)
    {
        for (size_t idx = 0, count = entries.size(); idx < count; idx += 1) {
            Outfit_Entry_t& entry = entries[idx];
            if (entry.form == form) {
                return &entry;
            }
        }
        return nullptr;
    }

    Bool_t Outfit_Inventory_t::Evaluate_Linchpin(Object_Ref::Inventory_t* actor)
    {
        NPCP_ASSERT(actor);

        Bool_t do_update = false;

        Form_t* linchpin = Consts::Blank_Armor();

        Entry_t* linchpin_entry = actor->Entry(linchpin);
        if (linchpin_entry) {
            Int_t linchpin_count = actor->Count(linchpin_entry);
            if (linchpin_count < 1) {
                do_update = true;
                actor->Add_Loose(linchpin_entry, 1);
            } else if (linchpin_count > 1) {
                do_update = true;
                Vector_t<XList_t*> xlists = linchpin_entry->XLists();
                for (size_t idx = 0, end = xlists.size(); idx < end; idx += 1) {
                    XList_t* xlist = xlists[idx];
                    if (xlist->HasType(kExtraData_Worn) || xlist->HasType(kExtraData_WornLeft)) {
                        do_update = false;
                    } else {
                        actor->Remove_XList(linchpin_entry, xlist);
                        XList::Destroy(xlist);
                    }
                }
                Int_t linchpin_loose_count = actor->Count_Loose(linchpin_entry);
                if (linchpin_loose_count > 0) {
                    actor->Remove_Loose(linchpin_entry, linchpin_loose_count);
                }
            }
        } else {
            do_update = true;
            linchpin_entry = actor->Add_Entry(linchpin);
            actor->Add_Loose(linchpin_entry, 1);
        }

        return do_update;
    }

    Int_t Outfit_Inventory_t::Evaluate_Existing(Inventory_t* actor, Inventory_t* transfer)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(transfer);

        enum {
            NO_UPDATE = 0,
            LESS_THAN_OUTFIT2_MXLIST_COUNT,
            GREATER_THAN_OUTFIT2_MXLIST_COUNT,
            NON_OUTFIT2_XLIST,
            NON_OUTFIT2_MXLIST,
            MISSING_OUTFIT2_MXLIST,
        };

        class Return_Code {
        private:
            Int_t code = NO_UPDATE;
        public:
            Int_t Code()
            {
                return code;
            }
            void Code(Int_t code)
            {
                this->code = code;
            }
        } return_code;

        Actor_Base_t* actor_base = Actor2::Dynamic_Base(static_cast<Actor_t*>(actor->reference));

        for (size_t idx = 0, end = actor->entries.size(); idx < end; idx += 1) {
            Entry_t* actor_entry = &actor->entries[idx];
            Form_t* form = actor_entry->form;
            if (Can_Evaluate_Form(form)) {
                Outfit_Entry_t* outfit_entry = Entry(form);
                Entry_t* transfer_entry = transfer->Entry(form);
                Merged_XLists_t actor_mxlists = actor_entry->Merged_XLists(false);
                Merged_XLists_t* outfit_mxlists = outfit_entry ? &outfit_entry->merged_xlists : nullptr;

                for (size_t idx = 0, end = actor_mxlists.size(); idx < end; idx += 1) {
                    Merged_XList_t& actor_mxlist = actor_mxlists[idx];
                    Merged_XList_t* outfit_mxlist = outfit_mxlists ? outfit_mxlists->Merged_XList(&actor_mxlist) : nullptr;
                    if (outfit_mxlist) {
                        XList_t* actor_unworn_xlist = nullptr;
                        Vector_t<XList_t*> actor_worn_xlists;
                        actor_worn_xlists.reserve(2);
                        for (size_t idx = 0, end = actor_mxlist.size(); idx < end; idx += 1) {
                            XList_t* xlist = actor_mxlist[idx];
                            if (XList::Is_Outfit2_Item(xlist, actor_base)) {
                                if (XList::Is_Worn(xlist)) {
                                    actor_worn_xlists.push_back(xlist);
                                } else if (actor_unworn_xlist) {
                                    actor->Remove_XList(actor_entry, xlist);
                                    XList::Destroy(xlist);
                                } else {
                                    actor_unworn_xlist = xlist;
                                }
                            } else {
                                if (XList::Is_Worn(xlist)) {
                                    return_code.Code(NON_OUTFIT2_XLIST);
                                }
                                if (!form->IsPlayable() || XList::Is_Outfit_Item(xlist)) {
                                    actor->Remove_XList(actor_entry, xlist);
                                    XList::Destroy(xlist);
                                } else {
                                    if (!transfer_entry) {
                                        transfer_entry = transfer->Add_Entry(form);
                                    }
                                    actor->Remove_XList(actor_entry, xlist);
                                    transfer->Add_XList(transfer_entry, xlist);
                                }
                            }
                        }

                        Int_t actor_mxlist_count = 0;
                        Int_t outfit_mxlist_count = outfit_mxlist->Count();
                        for (size_t idx = 0, end = actor_worn_xlists.size(); idx < end; idx += 1) {
                            XList_t* worn_xlist = actor_worn_xlists[idx];
                            if (actor_mxlist_count < outfit_mxlist_count) {
                                Int_t worn_xlist_count = XList::Count(worn_xlist);
                                if (actor_mxlist_count + worn_xlist_count > outfit_mxlist_count) {
                                    return_code.Code(GREATER_THAN_OUTFIT2_MXLIST_COUNT);
                                    Int_t difference = outfit_mxlist_count - actor_mxlist_count;
                                    actor->Decrement_XList(actor_entry, worn_xlist, worn_xlist_count - difference);
                                    actor_mxlist_count += difference;
                                } else {
                                    actor_mxlist_count += worn_xlist_count;
                                }
                            } else {
                                return_code.Code(GREATER_THAN_OUTFIT2_MXLIST_COUNT);
                                actor->Remove_XList(actor_entry, worn_xlist);
                                XList::Destroy(worn_xlist);
                            }
                        }
                        if (actor_unworn_xlist) {
                            if (actor_mxlist_count < outfit_mxlist_count) {
                                Int_t unworn_xlist_count = XList::Count(actor_unworn_xlist);
                                if (actor_mxlist_count + unworn_xlist_count > outfit_mxlist_count) {
                                    Int_t difference = outfit_mxlist_count - actor_mxlist_count;
                                    actor->Decrement_XList(actor_entry, actor_unworn_xlist, unworn_xlist_count - difference);
                                    actor_mxlist_count += difference;
                                } else if (actor_mxlist_count + unworn_xlist_count < outfit_mxlist_count) {
                                    Int_t difference = outfit_mxlist_count - (actor_mxlist_count + unworn_xlist_count);
                                    actor->Increment_XList(actor_entry, actor_unworn_xlist, difference);
                                    actor_mxlist_count += unworn_xlist_count + difference;
                                } else {
                                    actor_mxlist_count += unworn_xlist_count;
                                }
                            } else {
                                actor->Remove_XList(actor_entry, actor_unworn_xlist);
                                XList::Destroy(actor_unworn_xlist);
                            }
                        } else {
                            if (actor_mxlist_count < outfit_mxlist_count) {
                                return_code.Code(LESS_THAN_OUTFIT2_MXLIST_COUNT);
                                Int_t difference = outfit_mxlist_count - actor_mxlist_count;
                                XList_t* xlist = outfit_entry->Copy(outfit_mxlist, actor_base);
                                XList::Count(xlist, difference);
                                actor->Add_XList(actor_entry, xlist);
                                actor_mxlist_count += difference;
                            }
                        }
                        if (actor_mxlist_count != outfit_mxlist_count) {
                            _MESSAGE("Failed to correct actor_mxlist_count!\n");
                            actor->Log();
                            Log();
                        }
                    } else {
                        for (size_t idx = 0, end = actor_mxlist.size(); idx < end; idx += 1) {
                            XList_t* xlist = actor_mxlist[idx];
                            if (XList::Is_Worn(xlist)) {
                                return_code.Code(NON_OUTFIT2_MXLIST);
                            }
                            if (!form->IsPlayable() || XList::Is_Outfit_Item(xlist) || XList::Is_Outfit2_Item(xlist, actor_base)) {
                                actor->Remove_XList(actor_entry, xlist);
                                XList::Destroy(xlist);
                            } else {
                                if (!transfer_entry) {
                                    transfer_entry = transfer->Add_Entry(form);
                                }
                                actor->Remove_XList(actor_entry, xlist);
                                transfer->Add_XList(transfer_entry, xlist);
                            }
                        }
                    }
                }

                Int_t actor_loose_count = actor->Count_Loose(actor_entry);
                if (actor_loose_count > 0) {
                    if (!transfer_entry) {
                        transfer_entry = transfer->Add_Entry(form);
                    }
                    actor->Remove_Loose(actor_entry, actor_loose_count);
                    transfer->Add_Loose(transfer_entry, actor_loose_count);
                }

                if (outfit_mxlists) {
                    Merged_XLists_t actor_mxlists = actor_entry->Merged_XLists(false);
                    for (size_t idx = 0, end = outfit_mxlists->size(); idx < end; idx += 1) {
                        Merged_XList_t& outfit_mxlist = outfit_mxlists->at(idx);
                        Merged_XList_t* actor_mxlist = actor_mxlists.Merged_XList(outfit_mxlist.at(0));
                        if (!actor_mxlist) {
                            return_code.Code(MISSING_OUTFIT2_MXLIST);
                            actor->Add_XList(actor_entry, outfit_entry->Copy(&outfit_mxlist, actor_base));
                        }
                    }
                }
            }
        }

        for (size_t idx = 0, end = actor->entries.size(); idx < end; idx += 1) {
            Entry_t* actor_entry = &actor->entries[idx];
            actor->Try_To_Destroy_Entry(actor_entry);
        }

        return return_code.Code();
    }

    Bool_t Outfit_Inventory_t::Evaluate_Missing(Inventory_t* actor)
    {
        NPCP_ASSERT(actor);

        Bool_t do_update = false;

        Actor_Base_t* actor_base = Actor2::Dynamic_Base(static_cast<Actor_t*>(actor->reference));

        for (size_t idx = 0, count = entries.size(); idx < count; idx += 1) {
            Outfit_Entry_t& outfit_entry = entries[idx];
            Form_t* form = outfit_entry.form; NPCP_ASSERT(form);
            if (Can_Evaluate_Form(form)) {
                if (!actor->Entry(form)) {
                    Entry_t* actor_entry = actor->Add_Entry(form); NPCP_ASSERT(actor_entry);
                    Merged_XLists_t& outfit_xlists = outfit_entry.merged_xlists;
                    for (size_t idx = 0, count = outfit_xlists.size(); idx < count; idx += 1) {
                        actor->Add_XList(actor_entry, outfit_entry.Copy(&outfit_xlists[idx], actor_base));
                    }
                    do_update = true;
                }
            }
        }

        return do_update;
    }

    void Outfit_Inventory_t::Cleanup()
    {
        for (size_t idx = 0, end = entries.size(); idx < end; idx += 1) {
            Outfit_Entry_t& outfit_entry = entries[idx];
            outfit_entry.Cleanup();
        }
    }

    void Outfit_Inventory_t::Log(std::string indent)
    {
        _MESSAGE((indent + "Log_Outfit_Inventory: {").c_str());

        for (size_t idx = 0, end = entries.size(); idx < end; idx += 1) {
            Outfit_Entry_t& entry = entries[idx];
            const char* name = Form::Name(entry.form);
            if (!name || !name[0]) {
                name = "*";
            }
            _MESSAGE((indent + "    %-36s: total: %6i, form_type: %s").c_str(),
                     name,
                     entry.Count(),
                     Form::Get_Type_String(entry.form));
            for (size_t idx = 0, end = entry.merged_xlists.size(); idx < end; idx += 1) {
                Merged_XList_t& mxlist = entry.merged_xlists[idx];
                _MESSAGE((indent + "        mxlist: %zu").c_str(), idx);
                for (size_t idx = 0, end = mxlist.size(); idx < end; idx += 1) {
                    XList_t* xlist = mxlist[idx];
                    _MESSAGE((indent + "            xlist: %zu").c_str(), idx);
                    XList::Log(xlist, (indent + "                ").c_str());
                }
            }
        }

        _MESSAGE("}\n");
    }
    
    Bool_t Set_Outfit2(Actor_t* actor, Reference_t* outfit1, Reference_t* outfit2, Reference_t* transfer)
    {
        NPCP_ASSERT(actor);

        Bool_t do_delete_transfer;
        if (transfer) {
            Object_Ref::Init_Container_If_Needed(transfer);
            do_delete_transfer = false;
        } else {
            transfer = Object_Ref::Create_Container();
            do_delete_transfer = true;
        }

        Inventory_t actor_inventory(actor);
        Inventory_t transfer_inventory(transfer);
        Outfit_Inventory_t outfit_inventory(outfit1, outfit2);

        Bool_t should_update1 = outfit_inventory.Evaluate_Linchpin(&actor_inventory);
        Int_t existing_code = outfit_inventory.Evaluate_Existing(&actor_inventory, &transfer_inventory);
        Bool_t should_update3 = outfit_inventory.Evaluate_Missing(&actor_inventory);
        outfit_inventory.Cleanup();

        if (do_delete_transfer) {
            Object_Ref::Delete_Safe(transfer);
        }

        return should_update1 || existing_code > 0 || should_update3;
    }

    void Split_Inventory(Actor_t* actor, Reference_t* worn, Reference_t* pack)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(worn);
        NPCP_ASSERT(pack);

        Form_t* linchpin = Consts::Blank_Armor();
        Actor_Base_t* actor_base = Dynamic_Base(actor);

        Inventory_t actor_inventory(actor);
        Inventory_t worn_inventory(worn);
        Inventory_t pack_inventory(pack);

        for (size_t idx = 0, end = actor_inventory.entries.size(); idx < end; idx += 1) {
            Entry_t& actor_entry = actor_inventory.entries[idx];
            Form_t* form = actor_entry.form;
            if (form && form != linchpin && form->formType != kFormType_LeveledItem && form->IsPlayable()) {
                Entry_t* worn_entry = worn_inventory.Entry(form);
                Entry_t* pack_entry = pack_inventory.Entry(form);

                Vector_t<XList_t*> xlists = actor_entry.XLists();
                for (size_t idx = 0, end = xlists.size(); idx < end; idx += 1) {
                    XList_t* xlist = xlists[idx];
                    if (XList::Is_Worn(xlist) || XList::Is_Outfit2_Item(xlist, actor_base)) {
                        if (!worn_entry) {
                            worn_entry = worn_inventory.Add_Entry(form);
                        }
                        actor_inventory.Remove_XList(&actor_entry, xlist);
                        worn_inventory.Add_XList(worn_entry, xlist);
                    } else {
                        if (!pack_entry) {
                            pack_entry = pack_inventory.Add_Entry(form);
                        }
                        actor_inventory.Remove_XList(&actor_entry, xlist);
                        pack_inventory.Add_XList(pack_entry, xlist);
                    }
                }

                Int_t actor_loose_count = actor_inventory.Count_Loose(&actor_entry);
                if (actor_loose_count > 0) {
                    if (!pack_entry) {
                        pack_entry = pack_inventory.Add_Entry(form);
                    }
                    actor_inventory.Remove_Loose(&actor_entry, actor_loose_count);
                    pack_inventory.Add_Loose(pack_entry, actor_loose_count);
                }

                actor_inventory.Try_To_Destroy_Entry(&actor_entry);
            }
        }
    }

    void Cache_Worn(Actor_t* actor, Reference_t* cache_out)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(cache_out);

        Form_t* linchpin = Consts::Blank_Armor();

        Inventory_t actor_inventory(actor);
        Inventory_t cache_inventory(cache_out);

        for (size_t idx = 0, end = actor_inventory.entries.size(); idx < end; idx += 1) {
            Entry_t& actor_entry = actor_inventory.entries[idx];
            Form_t* form = actor_entry.form;
            if (form && form != linchpin && form->formType != kFormType_LeveledItem) {
                Entry_t* cache_entry = cache_inventory.Entry(form);
                Vector_t<XList_t*> xlists = actor_entry.XLists();
                for (size_t idx = 0, end = xlists.size(); idx < end; idx += 1) {
                    XList_t* xlist = xlists[idx];
                    if (XList::Is_Worn(xlist)) {
                        if (!cache_entry) {
                            cache_entry = cache_inventory.Add_Entry(form);
                        }
                        XList_t* xlist_copy = XList::Copy(xlist);
                        if (xlist_copy) {
                            cache_inventory.Add_XList(cache_entry, xlist_copy);
                        } else {
                            cache_inventory.Add_Loose(cache_entry, XList::Count(xlist));
                        }
                    }
                }
            }
        }
    }

    void Cache_BContainer(Actor_t* actor, Reference_t* cache_out)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(cache_out);

        Form_t* linchpin = Consts::Blank_Armor();

        BContainer_t* bcontainer_actor = Object_Ref::Get_BContainer(actor);
        if (bcontainer_actor) {
            for (u64 idx = 0; idx < bcontainer_actor->numEntries; idx += 1) {
                BEntry_t* bentry_actor = bcontainer_actor->entries[idx];
                if (!bentry_actor || !bentry_actor->form || bentry_actor->count < 1) {
                    continue;
                }

                TESForm* form_actor = bentry_actor->form;
                if (form_actor == linchpin) {
                    continue;
                }

                Object_Ref::Add_Item(cache_out, form_actor, bentry_actor->count, true);
            }
        }
    }

    bool Has_Same_Head(Actor *actor_a, Actor *actor_b) {
        if (!actor_a || !actor_b) {
            return false;
        }

        TESNPC *actor_base_a = DYNAMIC_CAST(actor_a->baseForm, TESForm, TESNPC);
        TESNPC *actor_base_b = DYNAMIC_CAST(actor_b->baseForm, TESForm, TESNPC);
        
        return Actor_Base2::Has_Same_Head(actor_base_a, actor_base_b);
    }

    bool Is_Aliased_In_Quest(Actor* actor, TESQuest* quest)
    {
        if (actor && quest) {
            ExtraAliasInstanceArray* xaliases = (ExtraAliasInstanceArray*)actor->extraData.GetByType(kExtraData_AliasInstanceArray);
            if (xaliases) {
                for (u64 idx = 0, size = xaliases->aliases.count; idx < size; idx += 1) {
                    ExtraAliasInstanceArray::AliasInfo* info = xaliases->aliases[idx];
                    if (info && info->quest == quest) {
                        return true;
                    }
                }
                return false;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Actor_Value_Owner_t* Actor_Value_Owner(Actor_t* actor)
    {
        NPCP_ASSERT(actor);
        return reinterpret_cast<Actor_Value_Owner_t*>(&actor->actorValueOwner);
    }

    float Get_Actor_Value(Actor *actor, const char *name) {
        if (!actor || !name || !name[0]) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor->actorValueOwner.GetCurrent(id_value);
    }

    float Get_Base_Actor_Value(Actor *actor, const char *name) {
        if (!actor || !name || !name[0]) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor->actorValueOwner.GetBase(id_value);
    }

    float Get_Max_Actor_Value(Actor *actor, const char *name) {
        if (!actor || !name || !name[0]) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor->actorValueOwner.GetMaximum(id_value);
    }

    void Set_Actor_Value(Actor *actor, const char *name, float value) {
        if (!actor || !name || !name[0]) {
            return;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return;
        }

        actor->actorValueOwner.SetCurrent(id_value, value);
    }

    void Reset_Actor_Value(Actor *actor, const char *name) {
        if (!actor || !name || !name[0]) {
            return;
        }

        TESNPC *actor_base = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
        if (!actor_base) {
            return;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return;
        }

        Set_Actor_Value(actor, name, Actor_Base2::Get_Base_Actor_Value(actor_base, name));
    }

    void Log_Actor_Values(Actor *actor) {
        if (!actor) {
            return;
        }

        _MESSAGE("Logging Actor Values: %s", Get_Name(actor));

        #define LOG_ACTOR_VALUE(NAME)                                   \
        M                                                               \
            _MESSAGE("    " NAME ": curr %10f, base %10f, max %10f",    \
                     Get_Actor_Value(actor, NAME),                      \
                     Get_Base_Actor_Value(actor, NAME),                 \
                     Get_Max_Actor_Value(actor, NAME));                 \
        W

        LOG_ACTOR_VALUE("Health");
        LOG_ACTOR_VALUE("Magicka");
        LOG_ACTOR_VALUE("Stamina");

        LOG_ACTOR_VALUE("OneHanded");
        LOG_ACTOR_VALUE("TwoHanded");
        LOG_ACTOR_VALUE("Block");
        LOG_ACTOR_VALUE("HeavyArmor");
        LOG_ACTOR_VALUE("LightArmor");
        LOG_ACTOR_VALUE("Smithing");

        LOG_ACTOR_VALUE("Destruction");
        LOG_ACTOR_VALUE("Restoration");
        LOG_ACTOR_VALUE("Conjuration");
        LOG_ACTOR_VALUE("Alteration");
        LOG_ACTOR_VALUE("Illusion");
        LOG_ACTOR_VALUE("Enchanting");

        LOG_ACTOR_VALUE("Marksman");
        LOG_ACTOR_VALUE("Sneak");
        LOG_ACTOR_VALUE("Alchemy");
        LOG_ACTOR_VALUE("Lockpicking");
        LOG_ACTOR_VALUE("Pickpocket");
        LOG_ACTOR_VALUE("Speechcraft");

        #undef LOG_ACTOR_VALUE
    }

    void Update_3D_Model(Actor_t* actor)
    {
        using func_type = void(*)(ActorProcessManager*, Actor_t*);
        static func_type func = reinterpret_cast<func_type>
            (RelocationManager::s_baseAddr + Offsets::Actor::UPDATE_3D_MODEL);

        if (actor && Is_Loaded(actor)) {
            return func(actor->processManager, actor);
        }
    }

    void Fully_Update_3D_Model(Actor_t* actor)
    {
        if (actor && Is_Loaded(actor) && actor->processManager && actor->processManager->middleProcess) {
            u8* flags_3d = ((u8*)actor->processManager->middleProcess + 0x311);
            *flags_3d = 0 |
                1 << Actor_t2::Update_3D_Flags::MODEL_3D |
                1 << Actor_t2::Update_3D_Flags::SKIN_3D |
                1 << Actor_t2::Update_3D_Flags::HEAD_3D |
                1 << Actor_t2::Update_3D_Flags::FACE_3D |
                1 << Actor_t2::Update_3D_Flags::SCALE_3D |
                1 << Actor_t2::Update_3D_Flags::SKELETON_3D;
            Update_3D_Model(actor);
        }
    }

    void Enable_Havok_Collision(Actor_t* actor)
    {
        if (actor) {
            actor->flags = Utils::Bit_Off(actor->flags, Actor_t2::Form_Flags::HASNT_HAVOK_COLLISION); // 1 << 4
        }
    }

    void Disable_Havok_Collision(Actor_t* actor)
    {
        if (actor) {
            actor->flags = Utils::Bit_On(actor->flags, Actor_t2::Form_Flags::HASNT_HAVOK_COLLISION); // 1 << 4
        }
    }

    void Stop_Combat(Actor_t* actor)
    {
        if (actor) {
            actor->Stop_Combat();
            actor->Update_Combat(); // maybe not necessary?
        }
    }

    void Stop_Combat_Alarm(Actor_t* actor)
    {
        if (actor) {
            Process_Lists_t::Self()->Stop_Combat_Alarm(actor);
        }
    }

    void Pacify(Actor_t* actor)
    {
        if (actor) {
            Actor_Value_Owner(actor)->Set_Actor_Value(Actor_Value_t::AGGRESSION, 0.0f);
            Stop_Combat(actor);
            Stop_Combat_Alarm(actor);
            Evaluate_Package(actor);
        }
    }

    void Kill(Actor_t* actor, Actor_t* killer, Float_t damage, Bool_t do_send_event, Bool_t do_quick_ragdoll)
    {
        if (actor && Is_Alive(actor)) {
            Actor_Base_t* base_actor = Dynamic_Base(actor);
            Actor_Base_Data_t* base_data = reinterpret_cast<Actor_Base_Data_t*>(&base_actor->actorData);

            Bool_t is_essential = base_data->Is_Essential();
            if (is_essential) {
                base_data->Unessentialize();
            }

            Bool_t is_protected = base_data->Is_Protected();
            if (is_protected) {
                base_data->Unprotect();
            }

            actor->Kill(killer, damage, do_send_event, do_quick_ragdoll);

            if (is_essential) {
                Actor_Base2::Essentialize(static_cast<Actor_Base_t*>(actor->baseForm));
            } else if (is_protected) {
                Actor_Base2::Protect(static_cast<Actor_Base_t*>(actor->baseForm));
            }
        }
    }

    Actor_t* Clone(Actor_t* actor, Reference_t* marker)
    {
        if (actor) {
            if (!marker) {
                if (Is_AI_Enabled(actor) && Object_Ref::Is_Near_Player(actor, 1024.0f)) {
                    marker = actor;
                } else {
                    marker = Party::Player_t::Self()->Actor();
                }
            }

            Actor_Base_t* real_base = Real_Base(actor);
            NPCP_ASSERT(real_base);
            Outfit_t* base_outfit = real_base->defaultOutfit;
            real_base->defaultOutfit = nullptr;
            Actor_t* clone = static_cast<Actor_t*>(Object_Ref::Place_At_Me(marker, real_base, 1));
            NPCP_ASSERT(clone);
            clone->ResetInventory(false);
            real_base->defaultOutfit = base_outfit;

            Pacify(clone);

            return clone;
        } else {
            return nullptr;
        }
    }

    void Resurrect(Actor_t* actor, Bool_t do_reset_inventory)
    {
        if (actor) {
            // it may actually be okay to use this, perhaps after PushActorAway
            /*if (Actor2::Is_Loaded(actor) && actor->processManager && actor->processManager->middleProcess) {
                u8* flags_3d = ((u8*)actor->processManager->middleProcess + 0x311);
                *flags_3d = 0 |
                    1 << Actor_t2::Update_3D_Flags::MODEL_3D |
                    1 << Actor_t2::Update_3D_Flags::SKIN_3D |
                    1 << Actor_t2::Update_3D_Flags::HEAD_3D |
                    1 << Actor_t2::Update_3D_Flags::FACE_3D |
                    1 << Actor_t2::Update_3D_Flags::SCALE_3D |
                    1 << Actor_t2::Update_3D_Flags::SKELETON_3D;
            }*/
            actor->Resurrect(do_reset_inventory, true);
            Pacify(actor);
            Object_Ref::Push_Actor_Away(actor, actor, 0.01f);
        }
    }

    Bool_t Try_Resurrect(Actor_t* actor, Bool_t do_reset_inventory)
    {
        NPCP_ASSERT(Is_Dead(actor));

        Resurrect(actor, do_reset_inventory);
        return Is_Alive(actor);
    }

    Bool_t Is_Child(Actor_t* actor)
    {
        return actor->Is_Child();
    }

    Bool_t Isnt_Child(Actor_t* actor)
    {
        return !actor->Is_Child();
    }

    void Update_Equipment(Actor_t* actor, Callback_t<Actor_t*>* user_callback)
    {
        using namespace Papyrus;
        using UCallback_t = Callback_t<Actor_t*>;

        if (actor) {
            Bool_t is_player_teammate = Is_Player_Teammate(actor);
            if (!is_player_teammate) {
                Join_Player_Team(actor);
            }

            struct VCallback : public Virtual_Callback_t {
                Actor_t* actor;
                Bool_t is_player_teammate;
                UCallback_t* user_callback;
                VCallback(Actor_t* actor, Bool_t is_player_teammate, UCallback_t* user_callback) :
                    actor(actor), is_player_teammate(is_player_teammate), user_callback(user_callback)
                {
                }
                void operator()(Variable_t* result)
                {
                    XEntry_t* xentry = Object_Ref::Get_XEntry(actor, Consts::Blank_Weapon(), false);
                    if (xentry) {
                        Object_Ref::Remove_XEntry(actor, xentry);
                        XEntry_t::Destroy(xentry);
                    }

                    if (!is_player_teammate) {
                        Leave_Player_Team(actor);
                    }

                    if (user_callback) {
                        user_callback->operator()(actor);
                        delete user_callback;
                    }
                }
            };
            Virtual_Callback_i* vcallback = new VCallback(actor, is_player_teammate, user_callback);
            Object_Ref::Add_Item_And_Callback(actor, Consts::Blank_Weapon(), 1, false, &vcallback);
        } else {
            if (user_callback) {
                user_callback->operator()(nullptr);
                delete user_callback;
            }
        }
    }

    void Stop_If_Playing_Music(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        class Arguments : public Virtual_Arguments_t {
        public:
            Actor_t* actor;
            Arguments(Actor_t* actor) :
                actor(actor)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Pack(actor);

                return true;
            }
        } arguments(actor);
        Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(),
                                               "doticu_npcp_funcs",
                                               "Stop_If_Playing_Music",
                                               &arguments);
    }

    Bool_t Has_Magic_Effect(Actor_t* actor, Magic_Effect_t* magic_effect)
    {
        if (actor) {
            return reinterpret_cast<Magic_Target_t*>(&actor->magicTarget)->Has_Magic_Effect(magic_effect);
        } else {
            return false;
        }
    }

    Bool_t Add_Spell(Actor_t* actor, Spell_t* spell)
    {
        static auto add_spell = reinterpret_cast
            <Bool_t(*)(Actor_t*, Spell_t*)>
            (RelocationManager::s_baseAddr + Offsets::Actor::ADD_SPELL);
        if (actor && spell) {
            return add_spell(actor, spell);
        } else {
            return false;
        }
    }

    void Add_Spell(Actor_t* actor, Spell_t* spell, Bool_t be_verbose, Virtual_Callback_i** callback)
    {
        if (actor && spell) {
            class Arguments : public Virtual_Arguments_t {
            public:
                Spell_t* spell;
                Bool_t be_verbose;
                Arguments(Spell_t* spell, Bool_t be_verbose) :
                    spell(spell), be_verbose(be_verbose)
                {
                }
                Bool_t operator()(Arguments_t* arguments)
                {
                    arguments->Resize(2);
                    arguments->At(0)->Pack(spell);
                    arguments->At(1)->Bool(be_verbose);
                    return true;
                }
            } arguments(spell, be_verbose);
            Virtual_Machine_t::Self()->Call_Method(actor, "Actor", "AddSpell", &arguments, callback);
        }
    }

    void Remove_Spell(Actor_t* actor, Spell_t* spell, Virtual_Callback_i** callback)
    {
        if (actor && spell) {
            class Arguments : public Virtual_Arguments_t {
            public:
                Spell_t* spell;
                Arguments(Spell_t* spell) :
                    spell(spell)
                {
                }
                Bool_t operator()(Arguments_t* arguments)
                {
                    arguments->Resize(1);
                    arguments->At(0)->Pack(spell);
                    return true;
                }
            } arguments(spell);
            Virtual_Machine_t::Self()->Call_Method(actor, "Actor", "RemoveSpell", &arguments, callback);
        }
    }

    Bool_t Is_Sneaking(Actor_t* actor)
    {
        return reinterpret_cast<Actor_State_t*>(&actor->actorState)->state.sneaking;
    }

    void Is_Talking_To_Player(Actor_t* actor, Virtual_Callback_i** callback)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(callback);

        Virtual_Machine_t::Self()->Call_Method(actor, "ObjectReference", "IsInDialogueWithPlayer", nullptr, callback);
    }

    void Owner(Actor_t* actor, Actor_Base_t* owner)
    {
        Object_Ref::Owner(actor, owner);
    }

    void Send_Animation_Event(Actor_t* actor, String_t animation, Virtual_Callback_i** callback)
    {
        struct Arguments : public Virtual_Arguments_t {
            Actor_t* actor;
            String_t animation;
            Arguments(Actor_t* actor, String_t animation) :
                actor(actor), animation(animation)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(2);
                arguments->At(0)->Pack(static_cast<Reference_t*>(actor));
                arguments->At(1)->String(animation);
                return true;
            }
        } arguments(actor, animation);
        Virtual_Machine_t::Self()->Call_Global("Debug", "SendAnimationEvent", &arguments, callback);
    }

    void Set_Doing_Favor(Actor_t* actor, Bool_t is, Virtual_Callback_i* vcallback)
    {
        struct VArguments : public Virtual_Arguments_t {
            Bool_t is;
            VArguments(Bool_t is) :
                is(is)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Bool(is);
                return true;
            }
        } arguments(is);
        Virtual_Machine_t::Self()->Call_Method(
            actor,
            "Actor",
            "SetDoingFavor",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

    void Set_Alpha(Actor_t* actor, Float_t alpha_0_to_1, Bool_t do_fade_in, Virtual_Callback_i* vcallback)
    {
        struct VArguments : public Virtual_Arguments_t {
            Float_t alpha_0_to_1;
            Bool_t do_fade_in;
            VArguments(Float_t alpha_0_to_1, Bool_t do_fade_in) :
                alpha_0_to_1(alpha_0_to_1), do_fade_in(do_fade_in)
            {
            }
            Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(2);
                arguments->At(0)->Float(alpha_0_to_1);
                arguments->At(1)->Bool(do_fade_in);
                return true;
            }
        } arguments(alpha_0_to_1, do_fade_in);
        Virtual_Machine_t::Self()->Call_Method(
            actor,
            "Actor",
            "SetAlpha",
            &arguments,
            vcallback ? &vcallback : nullptr
        );
    }

    Voice_Type_t* Voice_Type(Actor_t* actor)
    {
        return Actor_Base2::Voice_Type(Dynamic_Base(actor));
    }

}}

namespace doticu_npcp { namespace Actor2 { namespace Exports {

    bool Register(VMClassRegistry* registry)
    {
        #define ADD_METHOD(STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)  \
        M                                                               \
            ADD_CLASS_METHOD("Actor", Actor,                            \
                             STR_FUNC_, ARG_NUM_,                       \
                             RETURN_, Actor2::METHOD_, __VA_ARGS__);    \
        W

        ADD_METHOD("SetOutfit", 2, void, Set_Outfit, Outfit_t*, Bool_t);

        #undef ADD_METHOD

        return true;
    }

}}}
