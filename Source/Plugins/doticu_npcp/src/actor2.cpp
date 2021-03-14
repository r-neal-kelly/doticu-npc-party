/*
    Copyright © 2020 r-neal-kelly, aka doticu
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

    bool Has_Same_Head(Actor *actor_a, Actor *actor_b) {
        if (!actor_a || !actor_b) {
            return false;
        }

        TESNPC *actor_base_a = DYNAMIC_CAST(actor_a->baseForm, TESForm, TESNPC);
        TESNPC *actor_base_b = DYNAMIC_CAST(actor_b->baseForm, TESForm, TESNPC);
        
        return Actor_Base2::Has_Same_Head(actor_base_a, actor_base_b);
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
