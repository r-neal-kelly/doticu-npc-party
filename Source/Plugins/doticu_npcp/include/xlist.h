/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "types.h"

namespace doticu_npcp { namespace XList {

    XList_t *Create();
    void Destroy(XList_t *xlist);

    XList_t *Copy(XList_t *xlist);

    u64 Clean_For_Move(XList_t *xlist, TESObjectREFR *ref_to);

    UInt32 Get_Count(XList_t *xlist);
    void Set_Count(XList_t *xlist, UInt32 count);
    void Inc_Count(XList_t *xlist, UInt32 inc);

    bool Is_Similar(XList_t *xlist_a, XList_t *xlist_b);
    bool Can_Copy(XList_t *xlist);
    bool Is_Worn(XList_t *xlist);
    bool Is_Outfit_Item(XList_t *xlist);
    bool Is_Leveled_Item(XList_t *xlist);
    bool Is_Quest_Item(XList_t *xlist);

    void Add_Outfit2_Flag(XList_t *xlist);
    bool Has_Outfit2_Flag(XList_t *xlist);

    void Log(XList_t *xlist, const std::string str_indent);

}}
