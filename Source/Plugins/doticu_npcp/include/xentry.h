/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameExtraData.h"

#include "utils.h"
#include "types.h"
#include "xlist.h"
#include "xdata.h"

namespace doticu_npcp { namespace XEntry {

    XEntry_t *Create(TESForm *form, SInt32 count);
    void Destroy(XEntry_t *xentry);

    s32 Get_Count(XEntry_t *xentry);
    void Set_Count(XEntry_t *xentry, s32 count);
    void Inc_Count(XEntry_t *xentry, s32 inc);
    void Dec_Count(XEntry_t *xentry, s32 dec);

    void Add_XList(XEntry_t *xentry, XList_t *xlist);
    void Remove_XList(XEntry_t *xentry, XList_t *xlist);
    XList_t *Get_XList(XEntry_t *xentry, XList_t *xlist_similar, bool with_outfit2_flag);
    bool Has_XList(XEntry_t *xentry, XList_t *xlist_similar, bool with_outfit2_flag);
    void Move_XList(XEntry_t *from, XEntry_t *to, XList_t *xlist, TESObjectREFR *ref_to);
    void Clean_XLists(XEntry_t *xentry, TESObjectREFR *ref_container);
    bool Has_An_XList(XEntry_t *xentry);

    bool Is_Worn(XEntry_t *xentry);

    void Log(XEntry_t *xentry, const std::string str_indent);

}}
