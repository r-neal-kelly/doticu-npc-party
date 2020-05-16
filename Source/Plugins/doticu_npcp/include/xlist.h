/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <string>

#include "skse64/GameExtraData.h"

#include "utils.h"
#include "types.h"
#include "xdata.h"

namespace doticu_npcp { namespace XList {

    XList_t *Create();

    XList_t *Copy(XList_t *xlist);

    UInt32 Get_Count(XList_t *xlist);
    void Set_Count(XList_t *xlist, UInt32 count);
    void Inc_Count(XList_t *xlist, UInt32 inc);

    bool Is_Same(XList_t *xlist_a, XList_t *xlist_b);
    bool Can_Copy(XList_t *xlist);
    bool Is_Worn(XList_t *xlist);
    bool Is_Outfit_Item(XList_t *xlist);
    bool Is_Leveled_Item(XList_t *xlist);
    bool Is_Quest_Item(XList_t *xlist);

    void Add_Outfit2_Flag(XList_t *xlist);
    bool Has_Outfit2_Flag(XList_t *xlist);

    void Log(XList_t *xlist, const std::string str_indent);

}}
