/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"
#include "skse64/GameRTTI.h"
#include "skse64/PapyrusActor.h"

#include "actor_base2.h"
#include "actor2.h"
#include "codes.h"
#include "consts.h"
#include "form.h"
#include "funcs.h"
#include "object_ref.h"
#include "outfit.h"
#include "papyrus.h"
#include "papyrus.inl"
#include "utils.h"
#include "vector.h"
#include "xcontainer.h"
#include "xdata.h"
#include "xentry.h"
#include "xlist.h"

#include "party/party_player.h"
#include "party/party_npcs.h"
#include "party/party_members.h"
#include "party/party_member.h"

namespace doticu_npcp { namespace Actor2 {

    const char *Get_Base_Name(Actor *actor) {
        return Object_Ref::Get_Base_Name(actor);
    }

    const char *Get_Ref_Name(Actor *actor) {
        return Object_Ref::Get_Ref_Name(actor);
    }

    const char *Get_Name(Actor *actor) {
        return Object_Ref::Get_Name(actor);
    }

    Outfit_t* Base_Outfit(Actor_t* actor)
    {
        if (actor) {
            Actor_Base_t* base_actor = Dynamic_Base(actor);
            return base_actor->defaultOutfit;
        } else {
            return nullptr;
        }
    }

    void Base_Outfit(Actor_t* actor, Outfit_t* outfit)
    {
        if (actor) {
            Actor_Base_t* base_actor = Dynamic_Base(actor);
            base_actor->defaultOutfit = outfit;
            base_actor->MarkChanged(0x1000); // Thank you to Ian Patterson of SKSE for how to save the outfit!
        }
    }

    void Base_Sleep_Outfit(Actor_t* actor, Outfit_t* outfit)
    {
        if (actor) {
            Actor_Base_t* base_actor = Dynamic_Base(actor);
            base_actor->sleepOutfit = outfit;
            base_actor->MarkChanged(0x2000);
        }
    }

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
                    XList::Validate(xlist);
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
                member->Change_Outfit1(outfit);
            } else {
                Set_Outfit_Basic(actor, outfit, is_sleep_outfit, true); // could make this a setting
                Party::NPCS_t::Self()->Change_Default_Outfit(actor, outfit);
            }
        }
    }

    template <typename Type, size_t count_>
    struct Static_Array_t {
        size_t count = count_;
        Type data[count_];

        Static_Array_t()
        {
        }
    };

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

        Form_t* linchpin = Consts::Blank_Armor();
        XEntry_t* linchpin_xentry = Object_Ref::Get_XEntry(actor, linchpin, true);
        NPCP_ASSERT(linchpin_xentry);
        linchpin_xentry->Delta_Count(1); // we need to fix xlists too...

        class Outfit_Entry_t {
        public:
            Reference_t* reference = nullptr;
            XContainer_t* xcontainer = nullptr;
            XEntry_t* xentry = nullptr;
            Vector_t<XList_t*> xlists;
            Vector_t<UInt32> xlist_counts;
            UInt32 xlist_count = 0;
            UInt32 non_xlist_count = 0;

            Outfit_Entry_t() :
                reference(nullptr)
            {
            }

            Outfit_Entry_t(Reference_t* reference) :
                reference(reference)
            {
                if (reference) {
                    xcontainer = Object_Ref::Get_XContainer(reference, true);
                    NPCP_ASSERT(xcontainer);
                }
                xlists.reserve(4);
                xlist_counts.reserve(4);
            }

            void Evaluate(Form_t* form)
            {
                xlists.clear();
                xlist_counts.clear();
                xlist_count = 0;
                non_xlist_count = 0;

                auto Combine = [&](XList_t* xlist)->void
                {
                    if (xlist) {
                        XList::Validate(xlist);

                        UInt32 xlist_count = XList::Get_Count(xlist);
                        xlist_count += xlist_count;

                        if (XList::Can_Copy(xlist)) {
                            for (size_t idx = 0, count = xlists.size(); idx < count; idx += 1) {
                                if (XList::Is_Similar(xlist, xlists[idx])) {
                                    xlist_counts[idx] += xlist_count;
                                    return;
                                }
                            }
                            xlists.push_back(xlist);
                            xlist_counts.push_back(xlist_count);
                        } else {
                            non_xlist_count += xlist_count;
                        }
                    }
                };

                if (xcontainer) {
                    xentry = xcontainer->XEntry(form, false);
                    if (xentry) {
                        if (xentry->xlists) {
                            for (XLists_t::Iterator xlists_it = xentry->xlists->Begin(); !xlists_it.End(); ++xlists_it) {
                                XList_t* xlist = xlists_it.Get();
                                Combine(xlist);
                            }
                        }
                        Int_t remainder = Object_Ref::Get_BEntry_Count(reference, form) + xentry->Delta_Count() - xlist_count;
                        if (remainder > 0) {
                            non_xlist_count += remainder;
                        }
                    } else {
                        Int_t remainder = Object_Ref::Get_BEntry_Count(reference, form);
                        if (remainder > 0) {
                            non_xlist_count += remainder;
                        }
                    }
                } else {
                    Int_t remainder = Object_Ref::Get_BEntry_Count(reference, form);
                    if (remainder > 0) {
                        non_xlist_count += remainder;
                    }
                }
            }

        };

        class Outfits_Entry_t : public Static_Array_t<Outfit_Entry_t, 2> {
        public:
            Vector_t<XList_t*> xlists;
            Vector_t<UInt32> xlist_counts;
            UInt32 non_xlist_count = 0;

            Outfits_Entry_t(Reference_t* outfit1, Reference_t* outfit2)
            {
                data[0] = Outfit_Entry_t(outfit1);
                data[1] = Outfit_Entry_t(outfit2);
                xlists.reserve(4);
                xlist_counts.reserve(4);
            }

            void Evaluate(Form_t* form)
            {
                xlists.clear();
                xlist_counts.clear();
                non_xlist_count = 0;

                auto Combine = [&](XList_t* xlist, UInt32 xlist_count)->void
                {
                    if (xlist && xlist_count > 0) {
                        for (size_t idx = 0, count = xlists.size(); idx < count; idx += 1) {
                            if (XList::Is_Similar(xlist, xlists[idx])) {
                                xlist_counts[idx] += xlist_count;
                                return;
                            }
                        }
                        xlists.push_back(xlist);
                        xlist_counts.push_back(xlist_count);
                    }
                };

                for (size_t idx = 0; idx < count; idx += 1) {
                    Outfit_Entry_t& outfit = data[idx];
                    outfit.Evaluate(form);
                    for (size_t idx = 0, count = outfit.xlists.size(); idx < count; idx += 1) {
                        Combine(outfit.xlists[idx], outfit.xlist_counts[idx]);
                    }
                    non_xlist_count += outfit.non_xlist_count;
                }
            }

            UInt32 Count_Similar_XList(XList_t* xlist_to_compare)
            {
                for (size_t idx = 0, count = xlists.size(); idx < count; idx += 1) {
                    if (XList::Is_Similar(xlist_to_compare, xlists[idx])) {
                        return xlist_counts[idx];
                    }
                }

                if (!XList::Can_Copy(xlist_to_compare)) {
                    return non_xlist_count;
                } else {
                    return 0;
                }
            }

            Bool_t Add_Missing_XLists(XEntry_t* xentry)
            {
                NPCP_ASSERT(xentry);

                Bool_t did_add_an_xlist = false;

                auto Has_Similar_XList = [](XEntry_t* xentry, XList_t* xlist_to_compare)->Bool_t
                {
                    if (xentry->xlists) {
                        for (XLists_t::Iterator xlists_it = xentry->xlists->Begin(); !xlists_it.End(); ++xlists_it) {
                            XList_t* xlist = xlists_it.Get();
                            if (XList::Is_Similar(xlist_to_compare, xlist)) {
                                return true;
                            } else if (!XList::Can_Copy(xlist_to_compare) && !XList::Can_Copy(xlist)) {
                                return true;
                            }
                        }
                        return false;
                    } else {
                        return false;
                    }
                };

                auto Has_Remainder_XList = [](XEntry_t* xentry)->Bool_t
                {
                    if (xentry->xlists) {
                        for (XLists_t::Iterator xlists_it = xentry->xlists->Begin(); !xlists_it.End(); ++xlists_it) {
                            XList_t* xlist = xlists_it.Get();
                            if (!XList::Can_Copy(xlist)) {
                                return true;
                            }
                        }
                        return false;
                    } else {
                        return false;
                    }
                };

                for (size_t idx = 0, count = xlists.size(); idx < count; idx += 1) {
                    XList_t* xlist = xlists[idx];
                    if (!Has_Similar_XList(xentry, xlist)) {
                        XList_t* new_xlist = XList::Copy(xlist);
                        if (new_xlist) {
                            XList::Set_Count(new_xlist, xlist_counts[idx]);
                            XList::Add_Outfit2_Flag(new_xlist);
                            xentry->Add_XList(new_xlist);
                            did_add_an_xlist = true;
                        }
                    }
                }

                if (non_xlist_count > 0) {
                    if (!Has_Remainder_XList(xentry)) {
                        XList_t* remainder_xlist = XList::Create();
                        XList::Set_Count(remainder_xlist, non_xlist_count);
                        XList::Add_Outfit2_Flag(remainder_xlist);
                        xentry->Add_XList(remainder_xlist);
                        did_add_an_xlist = true;
                    }
                }

                return did_add_an_xlist;
            }

            void Add_Each_XList(XEntry_t* xentry)
            {
                for (size_t idx = 0, count = xlists.size(); idx < count; idx += 1) {
                    XList_t* xlist = xlists[idx];
                    XList_t* new_xlist = XList::Copy(xlist);
                    if (new_xlist) {
                        XList::Set_Count(new_xlist, xlist_counts[idx]);
                        XList::Add_Outfit2_Flag(new_xlist);
                        xentry->Add_XList(new_xlist);
                    }
                }

                if (non_xlist_count > 0) {
                    XList_t* remainder_xlist = XList::Create();
                    XList::Set_Count(remainder_xlist, non_xlist_count);
                    XList::Add_Outfit2_Flag(remainder_xlist);
                    xentry->Add_XList(remainder_xlist);
                }
            }

        } outfits_entry(outfit1, outfit2);

        class Actor_Inventory_t {
        public:
            Actor_t* actor;
            XContainer_t* xcontainer;
            Reference_t* transfer;
            Form_t* linchpin;
            Bool_t do_refresh = false;

            Actor_Inventory_t(Actor_t* actor, Reference_t* transfer, Form_t* linchpin) :
                actor(actor),
                xcontainer(actor ? Object_Ref::Get_XContainer(actor, true) : nullptr),
                transfer(transfer),
                linchpin(linchpin)
            {
                NPCP_ASSERT(actor);
                NPCP_ASSERT(xcontainer);
                NPCP_ASSERT(transfer);
                NPCP_ASSERT(linchpin);
            }

            Bool_t Is_Form_Transferable(Form_t* form)
            {
                return form->IsPlayable();
            }

            Bool_t Is_XList_Transferable(XList_t* xlist)
            {
                return
                    !XList::Is_Outfit_Item(xlist) &&
                    !XList::Is_Leveled_Item(xlist) &&
                    !XList::Has_Outfit2_Flag(xlist);
            }

            Bool_t Remove_Invalid_Entries(Outfits_Entry_t& outfits_entry)
            {
                if (xcontainer->changes->xentries) {
                    Vector_t<XEntry_t*> xentries_to_destroy;
                    xentries_to_destroy.reserve(4);
                    for (XEntries_t::Iterator xentries_it = xcontainer->changes->xentries->Begin(); !xentries_it.End(); ++xentries_it) {
                        XEntry_t* xentry = xentries_it.Get();
                        if (xentry && xentry->form && xentry->form != linchpin) {
                            Form_t* form = xentry->form;
                            if (form->IsPlayable() || form->IsArmor() || form->IsWeapon() || form->IsAmmo() || form->IsLight()) {
                                Int_t bentry_count = Object_Ref::Get_BEntry_Count(actor, form);
                                outfits_entry.Evaluate(form);
                                Simplify_Outfit2_XLists(xentry);
                                size_t remaining_xlists = Remove_Invalid_XLists(xentry, outfits_entry);
                                Remove_Non_XLists(xentry, remaining_xlists, bentry_count);
                                if (outfits_entry.Add_Missing_XLists(xentry)) {
                                    do_refresh = true;
                                }
                                if (xentry->Delta_Count() == 0 && bentry_count == 0) {
                                    xentries_to_destroy.push_back(xentry);
                                }
                            }
                        }
                    }
                    for (size_t idx = 0, count = xentries_to_destroy.size(); idx < count; idx += 1) {
                        XEntry_t* xentry_to_destroy = xentries_to_destroy[idx];
                        Object_Ref::Remove_XEntry(actor, xentry_to_destroy);
                        XEntry_t::Destroy(xentry_to_destroy);
                    }
                }

                BContainer_t* bcontainer = Object_Ref::Get_BContainer(actor);
                if (bcontainer) {
                    for (size_t idx = 0, count = bcontainer->numEntries; idx < count; idx += 1) {
                        BEntry_t* bentry = bcontainer->entries[idx];
                        if (bentry && bentry->form && bentry->form->formType != kFormType_LeveledItem && bentry->count > 0) {
                            if (!Object_Ref::Has_XEntry(actor, bentry->form)) {
                                XEntry_t* xentry = Object_Ref::Get_XEntry(actor, bentry->form, true);
                                xentry->Decrement(bentry->count);
                                if (Is_Form_Transferable(bentry->form)) {
                                    XEntry_t* transfer_xentry = Object_Ref::Get_XEntry(transfer, bentry->form, true);
                                    transfer_xentry->Increment(bentry->count);
                                }
                            }
                        }
                    }
                }

                return do_refresh;
            }

            void Simplify_Outfit2_XLists(XEntry_t* xentry)
            {
                NPCP_ASSERT(xentry);

                if (xentry->xlists) {
                    Vector_t<XList_t*> xlists_to_keep;
                    xlists_to_keep.reserve(4);
                    Vector_t<XList_t*> xlists_to_destroy;
                    xlists_to_destroy.reserve(4);

                    auto Find_Similar_Kept_XList = [&](XList_t* xlist_to_compare)->s64
                    {
                        for (size_t idx = 0, count = xlists_to_keep.size(); idx < count; idx += 1) {
                            XList_t* kept_xlist = xlists_to_keep[idx];
                            if (XList::Is_Similar(xlist_to_compare, kept_xlist)) {
                                return idx;
                            } else if (!XList::Can_Copy(xlist_to_compare) && !XList::Can_Copy(kept_xlist)) {
                                return idx;
                            }
                        }
                        return -1;
                    };

                    for (XLists_t::Iterator xlists_it = xentry->xlists->Begin(); !xlists_it.End(); ++xlists_it) {
                        XList_t* xlist = xlists_it.Get();
                        if (xlist) {
                            XList::Validate(xlist);
                            if (!XList::Is_Quest_Item(xlist) && XList::Has_Outfit2_Flag(xlist)) {
                                s64 kept_xlist_idx = Find_Similar_Kept_XList(xlist);
                                if (kept_xlist_idx > -1) {
                                    XList_t* kept_xlist = xlists_to_keep[kept_xlist_idx];
                                    if (XList::Is_Worn(xlist)) {
                                        if (!XList::Is_Worn(kept_xlist)) {
                                            XList_t* swap = xlist;
                                            xlist = kept_xlist;
                                            xlists_to_keep[kept_xlist_idx] = swap;
                                        } else {
                                            do_refresh = true;
                                        }
                                    }
                                    size_t xlist_count = XList::Get_Count(xlist);
                                    xentry->Increment(xlist_count);
                                    XList::Inc_Count(kept_xlist, xlist_count);
                                    xlists_to_destroy.push_back(xlist);
                                } else {
                                    xlists_to_keep.push_back(xlist);
                                }
                            }
                        }
                    }

                    for (size_t idx = 0, count = xlists_to_destroy.size(); idx < count; idx += 1) {
                        XList_t* xlist_to_destroy = xlists_to_destroy[idx];
                        xentry->Remove_XList(xlist_to_destroy);
                        XList::Destroy(xlist_to_destroy);
                    }
                }
            }

            size_t Remove_Invalid_XLists(XEntry_t* xentry, Outfits_Entry_t& outfits_entry)
            {
                NPCP_ASSERT(xentry);

                size_t xlists_remaining = 0;

                if (xentry->xlists) {
                    Vector_t<XList_t*> xlists_to_transfer;
                    xlists_to_transfer.reserve(4);
                    Vector_t<XList_t*> xlists_to_destroy;
                    xlists_to_destroy.reserve(4);

                    for (XLists_t::Iterator xlists_it = xentry->xlists->Begin(); !xlists_it.End(); ++xlists_it) {
                        XList_t* xlist = xlists_it.Get();
                        if (xlist) {
                            XList::Validate(xlist);
                            if (XList::Is_Quest_Item(xlist)) {
                                xlists_remaining += XList::Get_Count(xlist);
                            } else if (XList::Has_Outfit2_Flag(xlist)) {
                                UInt32 outfits_count = outfits_entry.Count_Similar_XList(xlist);
                                if (outfits_count > 0) {
                                    UInt32 xlist_count = XList::Get_Count(xlist);
                                    if (xlist_count != outfits_count) {
                                        xentry->Increment(outfits_count - xlist_count);
                                        XList::Set_Count(xlist, outfits_count);
                                        do_refresh = true;
                                    }
                                    if (xlist->HasType(kExtraData_CannotWear)) {
                                        XData_t* xdata = xlist->GetByType(kExtraData_CannotWear);
                                        if (xdata) {
                                            xlist->Remove(kExtraData_CannotWear, xdata);
                                            XData::Destroy(xdata);
                                        }
                                        do_refresh = true;
                                    }
                                    xlists_remaining += outfits_count;
                                } else {
                                    xlists_to_destroy.push_back(xlist);
                                    do_refresh = true;
                                }
                            } else {
                                if (Is_Form_Transferable(xentry->form) && Is_XList_Transferable(xlist)) {
                                    xlists_to_transfer.push_back(xlist);
                                } else {
                                    xlists_to_destroy.push_back(xlist);
                                }
                                do_refresh = true;
                            }
                        }
                    }

                    for (size_t idx = 0, count = xlists_to_destroy.size(); idx < count; idx += 1) {
                        XList_t* xlist_to_destroy = xlists_to_destroy[idx];
                        xentry->Remove_XList(xlist_to_destroy);
                        XList::Destroy(xlist_to_destroy);
                    }

                    size_t transfer_xlist_count = xlists_to_transfer.size();
                    if (transfer_xlist_count > 0) {
                        XEntry_t* transfer_xentry = Object_Ref::Get_XEntry(transfer, xentry->form, true);
                        for (size_t idx = 0; idx < transfer_xlist_count; idx += 1) {
                            XList_t* xlist_to_transfer = xlists_to_transfer[idx];
                            xentry->Move_XList(transfer_xentry, transfer, xlist_to_transfer);
                        }
                    }
                }

                return xlists_remaining;
            }

            void Remove_Non_XLists(XEntry_t* xentry, Int_t xlist_count, Int_t bentry_count)
            {
                NPCP_ASSERT(xentry);
                NPCP_ASSERT(xentry->form);
                NPCP_ASSERT(xlist_count > -1);

                Int_t remaining_count = bentry_count + xentry->Delta_Count() - xlist_count;
                if (remaining_count > 0) {
                    if (Is_Form_Transferable(xentry->form)) {
                        XEntry_t* transfer_xentry = Object_Ref::Get_XEntry(transfer, xentry->form, true);
                        transfer_xentry->Increment(remaining_count);
                    }
                    xentry->Delta_Count(xlist_count - bentry_count);
                }
            }

            void Add_Missing_Entries(Outfits_Entry_t& outfits_entry)
            {
                for (size_t idx = 0; idx < outfits_entry.count; idx += 1) {
                    XContainer_t* xcontainer = outfits_entry.data[idx].xcontainer;
                    if (xcontainer) {
                        for (XEntries_t::Iterator xentries_it = xcontainer->changes->xentries->Begin(); !xentries_it.End(); ++xentries_it) {
                            XEntry_t* xentry = xentries_it.Get();
                            if (xentry && xentry->form && xentry->form != linchpin) {
                                Form_t* form = xentry->form;
                                if (form->IsPlayable() || form->IsArmor() || form->IsWeapon() || form->IsAmmo() || form->IsLight()) {
                                    if (Object_Ref::Get_Entry_Count(actor, xentry->form) == 0) {
                                        outfits_entry.Evaluate(form);
                                        outfits_entry.Add_Each_XList(Object_Ref::Get_XEntry(actor, xentry->form, true));
                                        do_refresh = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Bool_t Should_Update()
            {
                return do_refresh;
            }

        } actor_inventory(actor, transfer, linchpin);

        actor_inventory.Remove_Invalid_Entries(outfits_entry);
        actor_inventory.Add_Missing_Entries(outfits_entry);

        if (do_delete_transfer) {
            Object_Ref::Delete_Safe(transfer);
        }

        return actor_inventory.Should_Update();
    }

    void Split_Inventory(Actor_t* actor, Reference_t* worn_out, Reference_t* pack_out)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(worn_out);
        NPCP_ASSERT(pack_out);

        Form_t* linchpin = Consts::Blank_Armor();

        XContainer_t* xcontainer_worn = Object_Ref::Get_XContainer(worn_out, true);
        NPCP_ASSERT(xcontainer_worn);

        XContainer_t* xcontainer_pack = Object_Ref::Get_XContainer(pack_out, true);
        NPCP_ASSERT(xcontainer_pack);

        XContainer_t* xcontainer_actor = Object_Ref::Get_XContainer(actor, false);
        if (xcontainer_actor) {
            for (XEntries_t::Iterator it_xentry_actor = xcontainer_actor->changes->xentries->Begin(); !it_xentry_actor.End(); ++it_xentry_actor) {
                XEntry_t* xentry_actor = it_xentry_actor.Get();
                if (!xentry_actor || !xentry_actor->form || xentry_actor->form == linchpin) {
                    continue;
                }

                TESForm* form_actor = xentry_actor->form;
                if (!form_actor->IsPlayable()) {
                    continue;
                }

                u64 count_xlists_actor = 0;
                if (xentry_actor->xlists) {
                    std::vector<XList_t*> vec_xlists_worn;
                    std::vector<XList_t*> vec_xlists_pack;
                    vec_xlists_worn.reserve(2);
                    vec_xlists_pack.reserve(2);

                    for (XLists_t::Iterator it_xlist_actor = xentry_actor->xlists->Begin(); !it_xlist_actor.End(); ++it_xlist_actor) {
                        XList_t* xlist_actor = it_xlist_actor.Get();
                        if (xlist_actor) {
                            XList::Validate(xlist_actor);

                            count_xlists_actor += XList::Get_Count(xlist_actor);

                            if (XList::Is_Worn(xlist_actor) || XList::Has_Outfit2_Flag(xlist_actor)) {
                                vec_xlists_worn.push_back(xlist_actor);
                            } else {
                                vec_xlists_pack.push_back(xlist_actor);
                            }
                        }
                    }

                    if (vec_xlists_worn.size() > 0) {
                        XEntry_t* xentry_worn = Object_Ref::Get_XEntry(worn_out, form_actor, true);
                        if (!xentry_worn) {
                            continue;
                        }

                        for (u64 idx = 0, size = vec_xlists_worn.size(); idx < size; idx += 1) {
                            XList_t* xlist_worn = vec_xlists_worn[idx];
                            XList_t* xlist_copy = XList::Copy(xlist_worn);
                            if (xlist_copy) {
                                xentry_worn->Add_XList(xlist_copy);
                            } else {
                                xentry_worn->Increment(XList::Get_Count(xlist_worn));
                            }
                        }
                    }

                    if (vec_xlists_pack.size() > 0) {
                        XEntry_t* xentry_pack = Object_Ref::Get_XEntry(pack_out, form_actor, true);
                        if (!xentry_pack) {
                            continue;
                        }

                        for (u64 idx = 0, size = vec_xlists_pack.size(); idx < size; idx += 1) {
                            XList_t* xlist_pack = vec_xlists_pack[idx];
                            XList_t* xlist_copy = XList::Copy(xlist_pack);
                            if (xlist_copy) {
                                xentry_pack->Add_XList(xlist_copy);
                            } else {
                                xentry_pack->Increment(XList::Get_Count(xlist_pack));
                            }
                        }
                    }
                }

                u64 count_remaining = Object_Ref::Get_BEntry_Count(actor, form_actor) + xentry_actor->Delta_Count() - count_xlists_actor;
                if (count_remaining > 0) {
                    XEntry_t* xentry_pack = Object_Ref::Get_XEntry(pack_out, form_actor, true);
                    if (xentry_pack) {
                        xentry_pack->Increment(count_remaining);
                    }
                }
            }
        }

        BContainer_t* bcontainer_actor = Object_Ref::Get_BContainer(actor);
        if (bcontainer_actor) {
            for (u64 idx = 0; idx < bcontainer_actor->numEntries; idx += 1) {
                BEntry_t* bentry_actor = bcontainer_actor->entries[idx];
                if (!bentry_actor || !bentry_actor->form || bentry_actor->count < 1) {
                    continue;
                }

                TESForm* form_actor = bentry_actor->form;
                if (form_actor == linchpin || form_actor->formType == kFormType_LeveledItem || !form_actor->IsPlayable()) {
                    continue;
                }

                if (!Object_Ref::Has_XEntry(actor, form_actor)) {
                    XEntry_t* xentry_pack = Object_Ref::Get_XEntry(pack_out, form_actor, true);
                    xentry_pack->Increment(bentry_actor->count);
                }
            }
        }
    }

    void Cache_Worn(Actor_t* actor, Reference_t* cache_out)
    {
        NPCP_ASSERT(actor);
        NPCP_ASSERT(cache_out);

        Form_t* linchpin = Consts::Blank_Armor();

        XContainer_t* xcontainer_actor = Object_Ref::Get_XContainer(actor, false);
        if (!xcontainer_actor) {
            return;
        }

        for (XEntries_t::Iterator it_xentry_actor = xcontainer_actor->changes->xentries->Begin(); !it_xentry_actor.End(); ++it_xentry_actor) {
            XEntry_t* xentry_actor = it_xentry_actor.Get();
            if (!xentry_actor || !xentry_actor->form || xentry_actor->form == linchpin || !xentry_actor->xlists) {
                continue;
            }

            std::vector<XList_t*> vec_xlists_worn;
            vec_xlists_worn.reserve(2);

            for (XLists_t::Iterator it_xlist_actor = xentry_actor->xlists->Begin(); !it_xlist_actor.End(); ++it_xlist_actor) {
                XList_t* xlist_actor = it_xlist_actor.Get();
                if (!xlist_actor) {
                    continue;
                }
                XList::Validate(xlist_actor);

                if (XList::Is_Worn(xlist_actor)) {
                    vec_xlists_worn.push_back(xlist_actor);
                }
            }

            if (vec_xlists_worn.size() > 0) {
                XEntry_t* xentry_cache = Object_Ref::Get_XEntry(cache_out, xentry_actor->form, true);
                if (!xentry_cache) {
                    continue;
                }

                for (u64 idx = 0, size = vec_xlists_worn.size(); idx < size; idx += 1) {
                    XList_t* xlist_worn = vec_xlists_worn[idx];
                    XList_t* xlist_cache = XList::Copy(xlist_worn);
                    if (xlist_cache) {
                        xentry_cache->Add_XList(xlist_cache);
                    } else {
                        xentry_cache->Increment(XList::Get_Count(xlist_worn));
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

    void Flag_Outfit1_As_Outfit2(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        XContainer_t* xcontainer = Object_Ref::Get_XContainer(actor, false);
        if (xcontainer) {
            for (XEntries_t::Iterator xentries = xcontainer->changes->xentries->Begin(); !xentries.End(); ++xentries) {
                XEntry_t* xentry = xentries.Get();
                if (xentry) {
                    Form_t* form = xentry->form;
                    if (form) {
                        for (XLists_t::Iterator xlists = xentry->xlists->Begin(); !xlists.End(); ++xlists) {
                            XList_t* xlist = xlists.Get();
                            if (xlist) {
                                XList::Validate(xlist);
                                if (xlist->HasType(kExtraData_OutfitItem)) {
                                    XList::Add_Outfit2_Flag(xlist);
                                }
                            }
                        }
                    }
                }
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

    bool Is_Alive(Actor *actor) {
        if (!actor) {
            return false;
        }

        return !actor->IsDead(1);
    }

    bool Is_Dead(Actor *actor) {
        if (!actor) {
            return false;
        }

        return actor->IsDead(1);
    }

    bool Is_Loaded(Actor_t* actor)
    {
        return actor && actor->loadedState != nullptr;
    }

    bool Is_Unloaded(Actor_t* actor)
    {
        return actor && actor->loadedState == nullptr;
    }

    bool Is_Unique(Actor_t* actor)
    {
        if (actor) {
            TESNPC* base_npc = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
            if (base_npc) {
                Actor_Base_Data_t* base_data = reinterpret_cast<Actor_Base_Data_t*>(&base_npc->actorData);
                return base_data->Is_Unique();
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool Is_Generic(Actor_t* actor)
    {
        if (actor) {
            TESNPC* base_npc = DYNAMIC_CAST(actor->baseForm, TESForm, TESNPC);
            if (base_npc) {
                Actor_Base_Data_t* base_data = reinterpret_cast<Actor_Base_Data_t*>(&base_npc->actorData);
                return !base_data->Is_Unique();
            } else {
                return false;
            }
        } else {
            return false;
        }
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

    Bool_t Is_Vampire(Actor_t* actor)
    {
        if (actor) {
            return actor->Has_Keyword(Consts::Vampire_Keyword());
        } else {
            return false;
        }
    }

    void Move_To_Orbit(Actor* actor, Reference_t* origin, float radius, float degree)
    {
        if (actor && origin) {
            //Stop_Movement(actor); // doesnt work yet.
            Object_Ref::Move_To_Orbit(actor, origin, radius, degree);
            if (Is_Loaded(actor)) {
                Update_3D_Model(actor); // we may want to move this behavior up to member/follower, etc.
            }
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

    Actor_t* Get_Mount(Actor_t* mounter)
    {
        if (mounter) {
            XData::XInteraction* xinteraction = (XData::XInteraction*)mounter->extraData.GetByType(kExtraData_Interaction);
            if (xinteraction && xinteraction->interaction) {
                NiPointer<TESObjectREFR> interactee = nullptr;
                LookupREFRByHandle(xinteraction->interaction->interactee_handle, interactee);
                return (Actor_t*)(TESObjectREFR*)interactee;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Actor_t* Get_Mounted_Actor(Actor_t* horse)
    {
        if (horse) {
            XData::XInteraction* xinteraction = (XData::XInteraction*)horse->extraData.GetByType(kExtraData_Interaction);
            if (xinteraction && xinteraction->interaction) {
                NiPointer<TESObjectREFR> interactor = nullptr;
                LookupREFRByHandle(xinteraction->interaction->interactor_handle, interactor);
                return (Actor_t*)(TESObjectREFR*)interactor;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    bool Is_On_Mount(Actor_t* actor)
    {
        return actor && Get_Mount(actor) != nullptr;
    }

    Int_t Sex(Actor_t* actor)
    {
        if (actor && actor->baseForm) {
            return CALL_MEMBER_FN(static_cast<TESNPC*>(actor->baseForm), GetSex)();
        } else {
            return ~0;
        }
    }

    String_t Sex_String(Actor_t* actor)
    {
        static const String_t male = String_t("male");
        static const String_t female = String_t("female");
        static const String_t none = String_t("none");
        static const String_t invalid = String_t("");

        NPCP_ASSERT(male && female && none && invalid);

        Int_t sex = Sex(actor);
        if (sex == CODES::SEX::MALE) {
            return male;
        } else if (sex == CODES::SEX::FEMALE) {
            return female;
        } else if (sex == CODES::SEX::NONE) {
            return none;
        } else {
            return invalid;
        }
    }

    String_t Race(Actor_t* actor)
    {
        if (actor && actor->race) {
            return actor->race->fullName.name;
        } else {
            return "";
        }
    }

    void Evaluate_Package(Actor_t* actor, bool unk_01, bool unk_02)
    {
        using func_type = void(*)(Actor_t*, bool, bool);
        static func_type func = reinterpret_cast<func_type>
            (RelocationManager::s_baseAddr + Offsets::Actor::EVALUATE_PACKAGE);

        if (actor) {
            return func(actor, unk_01, unk_02);
        }
    }

    void Update_3D_Model(Actor_t* actor)
    {
        using func_type = void(*)(ActorProcessManager*, Actor_t*);
        static func_type func = reinterpret_cast<func_type>
            (RelocationManager::s_baseAddr + Offsets::Actor::UPDATE_3D_MODEL);

        if (actor) {
            return func(actor->processManager, actor);
        }
    }

    void Fully_Update_3D_Model(Actor_t* actor)
    {
        if (actor && Actor2::Is_Loaded(actor) && actor->processManager && actor->processManager->middleProcess) {
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

    void Queue_Fully_Update_3D_Model(Actor_t* actor)
    {
        struct Callback : public Virtual_Callback_t {
            Actor_t* actor;
            Callback(Actor_t* actor) :
                actor(actor)
            {
            }
            void operator()(Variable_t* result)
            {
                Fully_Update_3D_Model(actor);
            }
        };
        Virtual_Callback_i* callback = new Callback(actor);
        Object_Ref::Enable(actor, false, &callback);
    }

    void Queue_Ni_Node_Update(Actor_t* actor, bool do_update_weight)
    {
        static auto queue_ni_node_update = reinterpret_cast
            <void (*)(Actor_t*, bool)>
            (RelocationManager::s_baseAddr + Offsets::Actor::QUEUE_NI_NODE_UPDATE);
        if (actor) {
            queue_ni_node_update(actor, do_update_weight);
        }
    }

    XFactions_t* XFactions(Actor_t* actor, bool do_create)
    {
        if (actor) {
            XFactions_t* xfactions = static_cast<ExtraFactionChanges*>
                (actor->extraData.GetByType(kExtraData_FactionChanges));
            if (!xfactions && do_create) {
                xfactions = XData::Create_Faction_Changes(actor);
                if (xfactions) {
                    actor->extraData.Add(kExtraData_FactionChanges, xfactions);
                    return xfactions;
                } else {
                    return nullptr;
                }
            } else {
                return xfactions;
            }
        } else {
            return nullptr;
        }
    }

    BFaction_Ranks_t* BFaction_Ranks(Actor_t* actor)
    {
        if (actor && actor->baseForm) {
            Actor_Base_t* base = static_cast<Actor_Base_t*>(actor->baseForm);
            return reinterpret_cast<BFaction_Ranks_t*>(&base->actorData.factions);
        } else {
            return nullptr;
        }
    }

    XFaction_Ranks_t* XFaction_Ranks(Actor_t* actor, bool do_create)
    {
        if (actor) {
            XFactions_t* xfactions = XFactions(actor, do_create);
            if (xfactions) {
                return reinterpret_cast<XFaction_Ranks_t*>(&xfactions->factions);
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    Bool_t Has_Faction(Actor_t* actor, Faction_t* faction)
    {
        if (actor && faction) {
            XFaction_Ranks_t* xfaction_ranks = XFaction_Ranks(actor);
            if (xfaction_ranks) {
                for (size_t idx = xfaction_ranks->count; idx > 0;) {
                    XFaction_Rank_t& xfaction_rank = xfaction_ranks->entries[idx -= 1];
                    if (xfaction_rank.faction == faction && xfaction_rank.rank > -1) {
                        return true;
                    }
                }
            }

            BFaction_Ranks_t* bfaction_ranks = BFaction_Ranks(actor);
            if (bfaction_ranks) {
                for (size_t idx = bfaction_ranks->count; idx > 0;) {
                    BFaction_Rank_t& bfaction_rank = bfaction_ranks->entries[idx -= 1];
                    if (bfaction_rank.faction == faction && bfaction_rank.rank > -1) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    Bool_t Has_Faction_Rank(Actor_t* actor, Faction_t* faction, Int_t rank)
    {
        if (actor && faction) {
            XFaction_Ranks_t* xfaction_ranks = XFaction_Ranks(actor);
            if (xfaction_ranks) {
                for (size_t idx = xfaction_ranks->count; idx > 0;) {
                    XFaction_Rank_t& xfaction_rank = xfaction_ranks->entries[idx -= 1];
                    if (xfaction_rank.faction == faction && xfaction_rank.rank == rank) {
                        return true;
                    }
                }
            }

            BFaction_Ranks_t* bfaction_ranks = BFaction_Ranks(actor);
            if (bfaction_ranks) {
                for (size_t idx = bfaction_ranks->count; idx > 0;) {
                    BFaction_Rank_t& bfaction_rank = bfaction_ranks->entries[idx -= 1];
                    if (bfaction_rank.faction == faction && bfaction_rank.rank == rank) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    void Add_Faction(Actor_t* actor, Faction_t* faction, Int_t rank)
    {
        if (actor && faction && rank > -1) {
            bool base_has_rank = false;
            BFaction_Ranks_t* bfaction_ranks = BFaction_Ranks(actor);
            if (bfaction_ranks) {
                for (size_t idx = 0, count = bfaction_ranks->count; idx < count; idx += 1) {
                    BFaction_Rank_t& bfaction_rank = bfaction_ranks->entries[idx];
                    if (bfaction_rank.faction == faction && bfaction_rank.rank == rank) {
                        base_has_rank = true;
                        break;
                    }
                }
            }

            if (base_has_rank) {
                XFaction_Ranks_t* xfaction_ranks = XFaction_Ranks(actor);
                if (xfaction_ranks) {
                    std::vector<size_t> removes;
                    for (size_t idx = 0, count = xfaction_ranks->count; idx < count; idx += 1) {
                        XFaction_Rank_t& xfaction_rank = xfaction_ranks->entries[idx];
                        if (xfaction_rank.faction == faction) {
                            removes.push_back(idx);
                        }
                    }
                    for (size_t idx = 0, count = removes.size(); idx < count; idx += 1) {
                        size_t remove_idx = removes[idx];
                        xfaction_ranks->count -= 1;
                        if (remove_idx != xfaction_ranks->count) {
                            xfaction_ranks->entries[remove_idx] = xfaction_ranks->entries[xfaction_ranks->count];
                        }
                    }
                }
            } else {
                XFaction_Ranks_t* xfaction_ranks = XFaction_Ranks(actor, true);
                if (xfaction_ranks) {
                    bool extra_has_rank = false;
                    for (size_t idx = 0, count = xfaction_ranks->count; idx < count; idx += 1) {
                        XFaction_Rank_t& xfaction_rank = xfaction_ranks->entries[idx];
                        if (xfaction_rank.faction == faction) {
                            xfaction_rank.rank = rank;
                            extra_has_rank = true;
                        }
                    }
                    if (!extra_has_rank) {
                        xfaction_ranks->Push({ faction, static_cast<SInt8>(rank) });
                    }
                }
            }
        }
    }

    void Remove_Faction(Actor_t* actor, Faction_t* faction)
    {
        if (actor && faction) {
            bool base_in_faction = false;
            BFaction_Ranks_t* bfaction_ranks = BFaction_Ranks(actor);
            if (bfaction_ranks) {
                for (size_t idx = 0, count = bfaction_ranks->count; idx < count; idx += 1) {
                    BFaction_Rank_t& bfaction_rank = bfaction_ranks->entries[idx];
                    if (bfaction_rank.faction == faction && bfaction_rank.rank > -1) {
                        base_in_faction = true;
                        break;
                    }
                }
            }

            if (base_in_faction) {
                XFaction_Ranks_t* xfaction_ranks = XFaction_Ranks(actor, true);
                if (xfaction_ranks) {
                    bool extra_has_rank = false;
                    for (size_t idx = 0, count = xfaction_ranks->count; idx < count; idx += 1) {
                        XFaction_Rank_t& xfaction_rank = xfaction_ranks->entries[idx];
                        if (xfaction_rank.faction == faction) {
                            xfaction_rank.rank = -1;
                            extra_has_rank = true;
                        }
                    }
                    if (!extra_has_rank) {
                        xfaction_ranks->Push({ faction, -1 });
                    }
                }
            } else {
                XFaction_Ranks_t* xfaction_ranks = XFaction_Ranks(actor);
                if (xfaction_ranks) {
                    std::vector<size_t> removes;
                    for (size_t idx = 0, count = xfaction_ranks->count; idx < count; idx += 1) {
                        XFaction_Rank_t& xfaction_rank = xfaction_ranks->entries[idx];
                        if (xfaction_rank.faction == faction) {
                            removes.push_back(idx);
                        }
                    }
                    for (size_t idx = 0, count = removes.size(); idx < count; idx += 1) {
                        size_t remove_idx = removes[idx];
                        xfaction_ranks->count -= 1;
                        if (remove_idx != xfaction_ranks->count) {
                            xfaction_ranks->entries[remove_idx] = xfaction_ranks->entries[xfaction_ranks->count];
                        }
                    }
                }
            }
        }
    }

    void Add_Crime_Faction(Actor_t* actor, Faction_t* crime_faction)
    {
        if (actor && crime_faction) {
            Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(actor->baseForm);
            if (actor_base->faction == crime_faction) {
                XFactions_t* xfactions = XFactions(actor, false);
                if (xfactions) {
                    xfactions->unk28 = reinterpret_cast<UInt64>(crime_faction);
                }
            } else {
                XFactions_t* xfactions = XFactions(actor, true);
                if (xfactions) {
                    xfactions->unk28 = reinterpret_cast<UInt64>(crime_faction);
                }
            }
        }
    }

    void Remove_Crime_Faction(Actor_t* actor)
    {
        if (actor) {
            Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(actor->baseForm);
            if (actor_base->faction == nullptr) {
                XFactions_t* xfactions = XFactions(actor, false);
                if (xfactions) {
                    xfactions->unk28 = reinterpret_cast<UInt64>(nullptr);
                }
            } else {
                XFactions_t* xfactions = XFactions(actor, true);
                if (xfactions) {
                    xfactions->unk28 = reinterpret_cast<UInt64>(nullptr);
                }
            }
        }
    }

    void Log_Factions(Actor_t* actor)
    {
        if (actor) {
            _MESSAGE("Log_Factions: %s {", Get_Name(actor));

            _MESSAGE("    BFactions:");
            BFaction_Ranks_t* bfaction_ranks = BFaction_Ranks(actor);
            if (bfaction_ranks) {
                for (size_t idx = 0, count = bfaction_ranks->count; idx < count; idx += 1) {
                    BFaction_Rank_t& bfaction_rank = bfaction_ranks->entries[idx];
                    _MESSAGE("        form: %X, name: %s, rank: %i, is_in_faction: %i %i",
                             bfaction_rank.faction->formID,
                             bfaction_rank.faction->fullName.name,
                             bfaction_rank.rank,
                             actor->Is_In_Faction(bfaction_rank.faction),
                             Has_Faction(actor, bfaction_rank.faction));
                }
            }

            _MESSAGE("    XFactions:");
            XFaction_Ranks_t* xfaction_ranks = XFaction_Ranks(actor);
            if (xfaction_ranks) {
                for (size_t idx = 0, count = xfaction_ranks->count; idx < count; idx += 1) {
                    XFaction_Rank_t& xfaction_rank = xfaction_ranks->entries[idx];
                    _MESSAGE("        form: %X, name: %s, rank: %i, is_in_faction: %i %i",
                             xfaction_rank.faction->formID,
                             xfaction_rank.faction->fullName.name,
                             xfaction_rank.rank,
                             actor->Is_In_Faction(xfaction_rank.faction),
                             Has_Faction(actor, xfaction_rank.faction));
                }
            }

            _MESSAGE("}\n");
        }
    }

    void Factions_And_Ranks(Actor_t* actor, Factions_And_Ranks_t& results, Int_t min_rank, Int_t max_rank)
    {
        NPCP_ASSERT(actor);

        results.factions.clear();
        results.factions.reserve(4);
        results.ranks.clear();
        results.ranks.reserve(4);

        Vector_t<Faction_t*> xfactions;
        xfactions.reserve(4);

        auto try_update = [&](Faction_t* faction, Int_t rank) -> void
        {
            if (rank >= min_rank && rank <= max_rank) {
                s64 faction_idx = Vector::Index_Of(results.factions, faction);
                if (faction_idx > -1) {
                    results.ranks.at(faction_idx) = rank;
                } else {
                    results.factions.push_back(faction);
                    results.ranks.push_back(rank);
                }
            }
        };

        XFaction_Ranks_t* xfaction_ranks = XFaction_Ranks(actor);
        if (xfaction_ranks) {
            for (size_t idx = 0, count = xfaction_ranks->count; idx < count; idx += 1) {
                XFaction_Rank_t* xfaction_rank = xfaction_ranks->entries + idx;
                try_update(xfaction_rank->faction, xfaction_rank->rank);
                xfactions.push_back(xfaction_rank->faction);
            }
        }

        BFaction_Ranks_t* bfaction_ranks = BFaction_Ranks(actor);
        if (bfaction_ranks) {
            for (size_t idx = 0, count = bfaction_ranks->count; idx < count; idx += 1) {
                BFaction_Rank_t* bfaction_rank = bfaction_ranks->entries + idx;
                if (!Vector::Has(xfactions, bfaction_rank->faction)) {
                    try_update(bfaction_rank->faction, bfaction_rank->rank);
                }
            }
        }
    }

    Faction_t* Crime_Faction(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(actor->baseForm);
        NPCP_ASSERT(actor_base);

        Faction_t* crime_faction = nullptr;

        XFactions_t* xfactions = XFactions(actor, false);
        if (xfactions) {
            crime_faction = reinterpret_cast<Faction_t*>(xfactions->unk28);
        }

        if (!crime_faction) {
            crime_faction = actor_base->faction;
        }

        return crime_faction;
    }

    void Join_Player_Team(Actor_t* actor, Bool_t allow_favors)
    {
        if (actor) {
            if (Utils::Is_Bit_Off(actor->flags1, Actor_t2::IS_PLAYER_TEAMMATE)) {
                actor->flags1 = Utils::Bit_On(actor->flags1, Actor_t2::IS_PLAYER_TEAMMATE);

                Party::Player_t::Self()->Player_Character()->numTeammates += 1; // necessary to get quick commands to work
            }
            if (allow_favors && Utils::Is_Bit_Off(actor->flags2, Actor_t2::DOES_FAVORS)) {
                actor->flags2 = Utils::Bit_On(actor->flags2, Actor_t2::DOES_FAVORS);
            }
        }
    }

    void Leave_Player_Team(Actor_t* actor)
    {
        if (actor) {
            if (Utils::Is_Bit_On(actor->flags1, Actor_t2::IS_PLAYER_TEAMMATE)) {
                actor->flags1 = Utils::Bit_Off(actor->flags1, Actor_t2::IS_PLAYER_TEAMMATE);

                UInt32* teammate_count = &Party::Player_t::Self()->Player_Character()->numTeammates;
                if (*teammate_count > 0) {
                    *teammate_count -= 1;
                }
            }
            if (Utils::Is_Bit_On(actor->flags2, Actor_t2::DOES_FAVORS)) {
                actor->flags2 = Utils::Bit_Off(actor->flags2, Actor_t2::DOES_FAVORS);
            }
        }
    }

    Bool_t Is_Player_Teammate(Actor_t* actor)
    {
        if (actor) {
            return Utils::Is_Bit_On(actor->flags1, Actor_t2::IS_PLAYER_TEAMMATE);
        } else {
            return false;
        }
    }

    void Talks_To_Player(Actor_t* actor, Bool_t can_talk)
    {
        if (actor) {
            ExtraCanTalkToPlayer* xcan_talk = static_cast<ExtraCanTalkToPlayer*>
                (actor->extraData.GetByType(kExtraData_CanTalkToPlayer));
            if (xcan_talk) {
                xcan_talk->can_talk = can_talk;
            } else {
                xcan_talk = XData::Create_Can_Talk_To_Player(can_talk);
                if (xcan_talk) {
                    actor->extraData.Add(kExtraData_CanTalkToPlayer, xcan_talk);
                }
            }
        }
    }

    Bool_t Can_Talk_To_Player(Actor_t* actor)
    {
        if (actor) {
            ExtraCanTalkToPlayer* xcan_talk = static_cast<ExtraCanTalkToPlayer*>
                (actor->extraData.GetByType(kExtraData_CanTalkToPlayer));
            if (xcan_talk) {
                return xcan_talk->can_talk;
            } else {
                if (actor->race) {
                    return (actor->race->data.raceFlags & TESRace::kRace_AllowPCDialogue) != 0;
                } else {
                    return false;
                }
            }
        } else {
            return false;
        }
    }

    Bool_t Cant_Talk_To_Player(Actor_t* actor)
    {
        if (actor) {
            return !Can_Talk_To_Player(actor);
        } else {
            return false;
        }
    }

    Bool_t Race_Can_Talk_To_Player(Actor_t* actor)
    {
        if (actor && actor->race) {
            return (actor->race->data.raceFlags & TESRace::kRace_AllowPCDialogue) != 0;
        } else {
            return false;
        }
    }

    Bool_t Race_Cant_Talk_To_Player(Actor_t* actor)
    {
        if (actor && actor->race) {
            return (actor->race->data.raceFlags & TESRace::kRace_AllowPCDialogue) == 0;
        } else {
            return false;
        }
    }

    Bool_t Is_AI_Enabled(Actor_t* actor)
    {
        if (actor) {
            return Utils::Is_Bit_On(actor->flags1, Actor_t2::PROCESS_AI);
        } else {
            return false;
        }
    }

    void Enable_AI(Actor_t* actor)
    {
        if (actor) {
            actor->flags1 = Utils::Bit_On(actor->flags1, Actor_t2::PROCESS_AI);
        }
    }

    void Disable_AI(Actor_t* actor)
    {
        if (actor) {
            actor->flags1 = Utils::Bit_Off(actor->flags1, Actor_t2::PROCESS_AI);
        }
    }

    Bool_t Is_Ghost(Actor_t* actor)
    {
        if (actor) {
            ExtraGhost* xghost = static_cast<ExtraGhost*>(actor->extraData.GetByType(kExtraData_Ghost));
            if (xghost) {
                return xghost->is_ghost;
            } else {
                return Actor_Base2::Is_Ghost(static_cast<Actor_Base_t*>(actor->baseForm));
            }
        } else {
            return false;
        }
    }

    void Ghostify(Actor_t* actor)
    {
        if (actor) {
            ExtraGhost* xghost = static_cast<ExtraGhost*>(actor->extraData.GetByType(kExtraData_Ghost));
            if (xghost) {
                xghost->is_ghost = true;
            } else if (!Actor_Base2::Is_Ghost(static_cast<Actor_Base_t*>(actor->baseForm))) {
                ExtraGhost* xghost = XData::Create_Ghost(true);
                if (xghost) {
                    actor->extraData.Add(kExtraData_Ghost, xghost);
                }
            }
        }
    }

    void Unghostify(Actor_t* actor)
    {
        if (actor) {
            ExtraGhost* xghost = static_cast<ExtraGhost*>(actor->extraData.GetByType(kExtraData_Ghost));
            if (xghost) {
                xghost->is_ghost = false;
            } else if (Actor_Base2::Is_Ghost(static_cast<Actor_Base_t*>(actor->baseForm))) {
                ExtraGhost* xghost = XData::Create_Ghost(false);
                if (xghost) {
                    actor->extraData.Add(kExtraData_Ghost, xghost);
                }
            }
        }
    }

    void Enable_Havok_Collision(Actor_t* actor)
    {
        if (actor) {
            actor->flags = Utils::Bit_Off(actor->flags, Actor_t2::Form_Flags::HASNT_HAVOK_COLLISION);
        }
    }

    void Disable_Havok_Collision(Actor_t* actor)
    {
        if (actor) {
            actor->flags = Utils::Bit_On(actor->flags, Actor_t2::Form_Flags::HASNT_HAVOK_COLLISION);
        }
    }

    void Ignore_Friendly_Hits(Actor_t* actor)
    {
        if (actor) {
            actor->flags = Utils::Bit_On(actor->flags, Actor_t2::Form_Flags::IGNORES_FRIENDLY_HITS);
        }
    }

    void Notice_Friendly_Hits(Actor_t* actor)
    {
        if (actor) {
            actor->flags = Utils::Bit_Off(actor->flags, Actor_t2::Form_Flags::IGNORES_FRIENDLY_HITS);
        }
    }

    void Show_On_Stealth_Eye(Actor_t* actor)
    {
        if (actor) {
            actor->flags2 = Utils::Bit_Off(actor->flags2, Actor_t2::Flags_2::HIDDEN_FROM_STEALTH_EYE);
        }
    }

    void Hide_From_Stealth_Eye(Actor_t* actor)
    {
        if (actor) {
            actor->flags2 = Utils::Bit_On(actor->flags2, Actor_t2::Flags_2::HIDDEN_FROM_STEALTH_EYE);
        }
    }

    void Stop_Movement(Actor_t* actor)
    {
        if (actor) {
            Actor_State_t* actor_state = reinterpret_cast<Actor_State_t*>(&actor->actorState);
            actor_state->Stop_Movement();
        }
    }

    Actor_Base_t* Dynamic_Base(Actor_t* actor)
    {
        NPCP_ASSERT(actor);
        Actor_Base_t* dynamic_base = static_cast<Actor_Base_t*>(actor->baseForm);
        NPCP_ASSERT(dynamic_base);
        return dynamic_base;
    }

    Actor_Base_t* Real_Base(Actor_t* actor)
    {
        if (actor) {
            Actor_Base_t* real_base = Dynamic_Base(actor);
            while (real_base->nextTemplate) {
                real_base = real_base->nextTemplate;
            }
            return real_base;
        } else {
            return nullptr;
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

            Vector_t<XList_t*> weapons;
            XContainer_t* xcontainer = Object_Ref::Get_XContainer(actor, false);
            if (xcontainer && xcontainer->changes && xcontainer->changes->xentries) {
                for (XEntries_t::Iterator xentries_it = xcontainer->changes->xentries->Begin(); !xentries_it.End(); ++xentries_it) {
                    XEntry_t* xentry = xentries_it.Get();
                    if (xentry) {
                        Form_t* form = xentry->form;
                        if (form && form->formType == kFormType_Weapon) {
                            if (xentry->xlists) {
                                for (XLists_t::Iterator xlists_it = xentry->xlists->Begin(); !xlists_it.End(); ++xlists_it) {
                                    XList_t* xlist = xlists_it.Get();
                                    if (xlist && XList::Has_Outfit2_Flag(xlist)) {
                                        XList::Remove_Outfit2_Flag(xlist, actor->baseForm);
                                        weapons.push_back(xlist);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            struct VCallback : public Virtual_Callback_t {
                Actor_t* actor;
                Bool_t is_player_teammate;
                Vector_t<XList_t*> weapons;
                UCallback_t* user_callback;
                VCallback(Actor_t* actor, Bool_t is_player_teammate, Vector_t<XList_t*> weapons, UCallback_t* user_callback) :
                    actor(actor), is_player_teammate(is_player_teammate), weapons(weapons), user_callback(user_callback)
                {
                }
                void operator()(Variable_t* result)
                {
                    XEntry_t* xentry = Object_Ref::Get_XEntry(actor, Consts::Blank_Weapon(), false);
                    if (xentry) {
                        Object_Ref::Remove_XEntry(actor, xentry);
                        XEntry_t::Destroy(xentry);
                    }
                    
                    for (size_t idx = 0, count = weapons.size(); idx < count; idx += 1) {
                        XList::Add_Outfit2_Flag(weapons[idx]);
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
            Virtual_Callback_i* vcallback = new VCallback(actor, is_player_teammate, weapons, user_callback);
            Object_Ref::Add_Item_And_Callback(actor, Consts::Blank_Weapon(), 1, false, &vcallback);
        } else {
            if (user_callback) {
                user_callback->operator()(nullptr);
                delete user_callback;
            }
        }
    }

    void Greet_Player(Actor_t* actor)
    {
        NPCP_ASSERT(actor);

        class Arguments : public Virtual_Arguments_t {
        public:
            Actor_t* actor;
            Arguments(Actor_t* actor) :
                actor(actor)
            {
            }
            virtual Bool_t operator()(Arguments_t* arguments)
            {
                arguments->Resize(1);
                arguments->At(0)->Pack(actor);

                return true;
            }
        } arguments(actor);

        Virtual_Machine_t::Self()->Call_Method(Consts::Funcs_Quest(),
                                               "doticu_npcp_actors",
                                               "Greet_Player",
                                               &arguments);
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
                                               "doticu_npcp_actors",
                                               "Stop_If_Playing_Music",
                                               &arguments);
    }

    Relationship_t::Rank_e Relationship_Rank(Actor_t* actor, Actor_t* other)
    {
        if (actor && other) {
            return Relationships_t::Self()->Relationship_Rank(Dynamic_Base(actor), Dynamic_Base(other));
        }
    }

    void Relationship_Rank(Actor_t* actor, Actor_t* other, Relationship_t::Rank_e rank)
    {
        if (actor && other) {
            Relationships_t::Self()->Relationship_Rank(Dynamic_Base(actor), Dynamic_Base(other), rank);
        }
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
        if (actor) {
            ExtraOwnership* xowner = static_cast<ExtraOwnership*>
                (actor->extraData.GetByType(kExtraData_Ownership));
            if (xowner) {
                if (owner) {
                    xowner->owner = static_cast<Form_t*>(owner);
                } else {
                    actor->extraData.Remove(kExtraData_Ownership, xowner);
                    XData::Destroy(xowner);
                }
            } else {
                if (owner) {
                    xowner = XData::Create_Ownership(static_cast<Form_t*>(owner));
                    actor->extraData.Add(kExtraData_Ownership, xowner);
                }
            }
        }
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
