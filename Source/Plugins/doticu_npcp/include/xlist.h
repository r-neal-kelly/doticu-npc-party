/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"
#include "xentry.h"

namespace doticu_npcp { namespace Papyrus {

    class XList_t2 : public BaseExtraList {
    public:
        static XList_t* Create();
        static void Destroy(XList_t* xlist);
    public:
        void Destroy();

        void Validate(Int_t xentry_count, Int_t bentry_count);
        void Validate_Without_Count();

        Int_t Count();
        void Count(Int_t count);

        Int_t operator++();
        Int_t operator++(int);
    };

}}

namespace doticu_npcp { namespace XList {

    using namespace Papyrus;

    XList_t* Create();
    void Destroy(XList_t* xlist);

    void Validate(XList_t* xlist, Int_t xentry_count, Int_t bentry_count);
    void Validate_No_Count(XList_t* xlist);

    Int_t Count(XList_t* xlist);
    void Count(XList_t* xlist, Int_t count);
    void Increment(XList_t* xlist, Int_t increment);
    Int_t Decrement(XList_t* xlist, Int_t decrement);

    XList_t* Copy(XList_t* xlist); // xlist should be validated first.
    void Owner(XList_t* xlist, Actor_Base_t* actor_base);

    u64 Clean_For_Move(XList_t* xlist, TESObjectREFR* ref_to);

    bool Is_Similar(XList_t* xlist_a, XList_t* xlist_b);
    bool Can_Copy(XList_t* xlist);
    Bool_t Has_Health(XList_t* xlist);
    Bool_t Has_Enchantement(XList_t* xlist);
    Bool_t Has_Charge(XList_t* xlist);
    bool Is_Worn(XList_t* xlist);
    bool Is_Outfit_Item(XList_t* xlist);
    Bool_t Is_Outfit2_Item(XList_t* xlist, Actor_Base_t* owner);
    bool Is_Leveled_Item(XList_t* xlist);
    bool Is_Quest_Item(XList_t* xlist);

    void Log(XList_t* xlist, const std::string str_indent);

}}
