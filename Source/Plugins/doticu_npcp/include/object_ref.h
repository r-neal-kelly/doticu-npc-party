/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"
#include "xcontainer.h"
#include "xentry.h"

namespace doticu_npcp { namespace Object_Ref {

    using namespace Papyrus;

    String_t Class_Name();
    Class_Info_t* Class_Info();

    BContainer_t *Get_BContainer(TESObjectREFR *obj);
    XContainer_t *Get_XContainer(TESObjectREFR *obj, bool do_create = false);
    void Validate_XContainer(Reference_t* ref);

    BEntry_t *Get_BEntry(TESObjectREFR *obj, TESForm *form);
    XEntry_t *Get_XEntry(TESObjectREFR *obj, TESForm *form, bool do_create = false);
    void Add_XEntry(Reference_t* ref, XEntry_t* to_add);
    void Remove_XEntry(Reference_t* ref, XEntry_t* to_remove);
    bool Has_XEntry(TESObjectREFR *obj, TESForm *form);
    Bool_t Has_Similar_XList(Reference_t* ref, Form_t* form, XList_t* xlist_to_compare);

    Int_t Get_BEntry_Count(Reference_t* ref, Form_t* form);
    Int_t Get_XEntry_Count(Reference_t* ref, Form_t* form);
    Int_t Get_Entry_Count(Reference_t* ref, Form_t* form);

    const char *Get_Base_Name(TESObjectREFR *ref_object);
    const char *Get_Ref_Name(TESObjectREFR *ref_object);
    const char *Get_Name(TESObjectREFR *ref_object);

    bool Is_Off_Limits(TESObjectREFR *ref_object);
    bool Is_Quest_Item(TESObjectREFR *ref_object);
    bool Is_Worn(TESObjectREFR *obj, TESForm *form);

    void Remove_If(Reference_t* from,
                   Reference_t* to = nullptr, // if nullptr, will delete items
                   Bool_t(*should_remove_xform)(Form_t*) = nullptr, // if nullptr, will remove all
                   Bool_t(*should_remove_xlist)(XList_t*, Form_t*) = nullptr, // if nullptr, will remove non-quest items
                   Bool_t(*should_remove_bform)(Form_t*) = nullptr); // if nullptr, is the same as should_remove_xform
    void Remove_Wearables(Reference_t* ref, Reference_t* destination = nullptr, Bool_t do_remove_quest_items = false);
    void Remove_Unwearables(Reference_t* obj, Reference_t* other = nullptr, Bool_t remove_quest_items = false);
    void Remove_Non_Outfit_Worn(Reference_t* obj, Reference_t* other = nullptr, Bool_t remove_quest_items = false);
    void Remove_All_Items(Reference_t* from, Reference_t* to = nullptr, Bool_t remove_quest_items = false, Bool_t remove_unplayable_items = true);
    
    Bool_t Contains_Form(Reference_t* ref, Form_t* form);

    void Categorize(Reference_t* ref, Bool_t only_custom_categories = false);
    void Log_XContainer(TESObjectREFR *obj);
    void Log_XList(TESObjectREFR *ref_object);

    Worldspace_t* Worldspace(Reference_t* ref);
    Location_t* Location(Reference_t* ref);
    Cell_t* Cell(Reference_t* ref);

    void Move_To_Orbit(TESObjectREFR *obj, TESObjectREFR *target, float radius, float angle_degree);

    float Get_Distance(TESObjectREFR *obj, TESObjectREFR *target);
    bool Is_Near_Player(TESObjectREFR *obj, float max_radius = 4096);

    bool Has_Token(Reference_t* ref, Form_t* token, Int_t count = 1);
    void Token(Reference_t* ref, Form_t* token, Int_t count = 1);
    void Untoken(Reference_t* ref, Form_t* token);

    void Block_Activation(Reference_t* ref);
    void Unblock_Activation(Reference_t* ref);
    void Block_Player_Activation(Reference_t* ref);
    void Unblock_Player_Activation(Reference_t* ref);
    void Block_All_Activation(Reference_t* ref);
    void Unblock_All_Activation(Reference_t* ref);

    void Block_Activation(Reference_t* ref, Bool_t do_block, Virtual_Callback_i* vcallback = nullptr);

    void Play_Animation(Reference_t* ref, void* nicontroller, void* nisequence_from, void* nisequence_to);

    void Rename(Reference_t* ref, String_t new_name);

    void Init_Container_If_Needed(Reference_t* ref);
    void Open_Container(Reference_t* ref, Papyrus::Virtual_Callback_i** callback = nullptr);

    void Activate(Reference_t* ref,
                  Reference_t* activator,
                  Bool_t do_default_processing_only = false,
                  Papyrus::Virtual_Callback_i** callback = nullptr);

    Reference_t* Place_At_Me(Reference_t* me,
                             Form_t* to_place,
                             Int_t count = 1,
                             Bool_t force_persist = true,
                             Bool_t initially_disabled = false);

    void Add_Item(Reference_t* ref, Form_t* form, Int_t count, Bool_t do_silently = true);

    Reference_t* From_Handle(Reference_Handle_t handle);

    Reference_t* Create_Marker_At(Reference_t* ref);
    Reference_t* Create_Container();

    void Delete_Safe(Reference_t* ref);

    void Enable(Reference_t* ref, Bool_t do_fade_in = false, Virtual_Callback_i** callback = nullptr);
    void Disable(Reference_t* ref, Bool_t do_fade_out = false, Virtual_Callback_i** callback = nullptr);

    bool Is_In_Interior_Cell(Reference_t* ref);
    bool Is_In_Exterior_Cell(Reference_t* ref);

    UInt32 Ref_Count(Reference_t* ref);

    void Add_Item_And_Callback(Reference_t* ref,
                               Form_t* form,
                               Int_t count = 1,
                               Bool_t do_sounds = false,
                               Papyrus::Virtual_Callback_i** callback = nullptr);
    void Remove_Item_And_Callback(Reference_t* ref,
                                  Form_t* form,
                                  Int_t count = 1,
                                  Bool_t do_sounds = false,
                                  Reference_t* destination = nullptr,
                                  Papyrus::Virtual_Callback_i** callback = nullptr);

    void Find_Closest_Actor_From(Reference_t* ref, Float_t radius, Virtual_Callback_i** callback);

    void Translate_To(Reference_t* ref,
                      Float_t pos_degree_x,
                      Float_t pos_degree_y,
                      Float_t pos_degree_z,
                      Float_t rot_degree_x,
                      Float_t rot_degree_y,
                      Float_t rot_degree_z,
                      Float_t pos_speed,
                      Float_t rot_speed,
                      Virtual_Callback_i** callback = nullptr);
    void Stop_Translation(Reference_t* ref, Virtual_Callback_i** callback = nullptr);
    void Push_Actor_Away(Reference_t* ref, Actor_t* actor, Float_t knockback_force, Virtual_Callback_i** vcallback = nullptr);
    void Apply_Havok_Impulse(Reference_t* ref, Float_t x, Float_t y, Float_t z, Float_t magnitude, Virtual_Callback_i** vcallback = nullptr);

    void Set_Open(Reference_t* ref, Bool_t is_open, Virtual_Callback_i* vcallback = nullptr);

    class Merged_XList_t : public Vector_t<XList_t*> {
    public:
        Int_t Count();
        Bool_t Is_Worn();
    };

    class Entry_t;
    class Merged_XLists_t : public Vector_t<Merged_XList_t> {
    public:
        Merged_XLists_t();
        Merged_XLists_t(Entry_t* entry, Bool_t(*do_exclude)(XList_t*));

        Merged_XList_t* Merged_XList(Merged_XList_t* similar_mxlist);
        Merged_XList_t* Merged_XList(XList_t* similar_xlist);

        Int_t Count();
        Bool_t Is_Worn();
    };

    class Entry_t {
    public:
        Form_t* form;
        Int_t bentry_count = 0;
        XEntry_t* xentry = nullptr;
        Int_t xlist_count = 0;

        Vector_t<XList_t*> XLists();
        Merged_XLists_t Merged_XLists(Bool_t allow_quest_items);
    };

    class Inventory_t {
    public:
        Reference_t* reference = nullptr;
        BContainer_t* bcontainer = nullptr;
        XContainer_t* xcontainer = nullptr;
        Vector_t<Entry_t> entries;

        Inventory_t(Reference_t* reference = nullptr);

        Entry_t* Entry(Form_t* form);
        Entry_t* Add_Entry(Form_t* form);

        Int_t Find(Entry_t* entry);

        void Validate(Entry_t* entry);

        Int_t Count(Entry_t* entry);
        Int_t Count_Base(Entry_t* entry);
        Int_t Count_Extra(Entry_t* entry);
        Int_t Count_Loose(Entry_t* entry);
        Int_t Count_XLists(Entry_t* entry);

        void Add_Loose(Entry_t* entry, Int_t count);
        void Remove_Loose(Entry_t* entry, Int_t count);
        void Add_XList(Entry_t* entry, XList_t* xlist);
        void Remove_XList(Entry_t* entry, XList_t* xlist);
        void Increment_XList(Entry_t* entry, XList_t* xlist, Int_t increment);
        void Decrement_XList(Entry_t* entry, XList_t* xlist, Int_t decrement);
        
        void Try_To_Destroy_Entry(Entry_t* entry);

        void Log(std::string indent = "");
    };

    // these don't belong here.
    void Current_Crosshair_Reference(Virtual_Callback_i** callback);
    void Can_Use_Keys(Virtual_Callback_i** callback);
    void Mapped_Control(Int_t key_code, Virtual_Callback_i* vcallback);

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    bool Register(VMClassRegistry *registry);

}}}
