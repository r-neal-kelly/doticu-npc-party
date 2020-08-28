/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Papyrus {

    struct XEntry_t {
    public:
        static XEntry_t* Create(Form_t* form, Int_t delta_count);
        static void Destroy(XEntry_t* xentry);

    public:
        Form_t* form;
        XLists_t* xlists;
    private:
        Int_t delta_count;

    public:
        Int_t Delta_Count();
        void Delta_Count(Int_t new_delta_count);
        void Increment(Int_t by);
        void Decrement(Int_t by);

        void Add_XList(XList_t* xlist);
        void Remove_XList(XList_t* xlist);
        void Move_XList(XEntry_t* to_xentry, Reference_t* to_reference, XList_t* xlist);
        void Clean_XLists(Reference_t* to_reference);

        XList_t* Similar_XList(XList_t* similiar, Bool_t with_outfit2_flag);
        Bool_t Has_Similar_XList(XList_t* similiar, Bool_t with_outfit2_flag);
        Bool_t Has_Worn_XList();

        void Validate(Reference_t* owner);

        void Log(const std::string indent);
    };
    STATIC_ASSERT(sizeof(XEntry_t) == 0x18);

    typedef tList<XEntry_t> XEntries_t;

}}
