/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace Papyrus {

    struct XEntry_t {
    public:
        static XEntry_t* Create(Form_t* form, Int_t delta_count = 0);
        static void Destroy(XEntry_t* xentry);

    public:
        Form_t* form;
        XLists_t* xlists;
        Int_t delta_count;

    public:
        Int_t Delta_Count();
        void Delta_Count(Int_t new_delta_count);
        void Increment(Int_t by);
        void Decrement(Int_t by);

        void Add_XList(XList_t* xlist);
        void Add_Clean_XList(XList_t* xlist, Reference_t* owner);
        void Remove_XList(XList_t* xlist);
        void Move_XList(XEntry_t* to_xentry, Reference_t* to_reference, XList_t* xlist);
        void Clean_XLists(Int_t from_bentry_count, Reference_t* to_reference);

        XList_t* Similar_XList(XList_t* similiar);
        Bool_t Has_Similar_XList(XList_t* similiar);
        Bool_t Has_Worn_XList();

        Int_t Validate(Int_t bentry_count);

        void Log(const std::string indent);
    };
    STATIC_ASSERT(sizeof(XEntry_t) == 0x18);

    typedef tList<XEntry_t> XEntries_t;

}}
