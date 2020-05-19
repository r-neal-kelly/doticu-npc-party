/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameRTTI.h"
#include "skse64/PapyrusActor.h"
#include "skse64/PapyrusNativeFunctions.h"

#include "utils.h"
#include "vector.h"
#include "papyrus.h"
#include "form.h"
#include "xentry.h"
#include "xlist.h"
#include "xdata.h"

namespace doticu_npcp { namespace Object_Ref {

    BContainer_t *Get_BContainer(TESObjectREFR *obj);
    XContainer_t *Get_XContainer(TESObjectREFR *obj);

    BEntry_t *Get_BEntry(TESObjectREFR *obj, TESForm *form);
    XEntry_t *Get_XEntry(TESObjectREFR *obj, TESForm *form, bool do_create = false);
    void Add_XEntry(TESObjectREFR *obj, XEntry_t *xentry_add);
    void Remove_XEntry(TESObjectREFR *obj, XEntry_t *xentry);
    bool Has_XEntry(TESObjectREFR *obj, TESForm *form);

    void Move_Entry(TESObjectREFR *from, TESObjectREFR *to, TESForm *form);
    void Move_XList(TESObjectREFR *from, TESObjectREFR *to, TESForm *form, XList_t *xlist);

    SInt32 Get_BEntry_Count(TESObjectREFR *obj, TESForm *form);
    SInt32 Get_XEntry_Count(TESObjectREFR *obj, TESForm *form);
    SInt32 Get_Entry_Count(TESObjectREFR *obj, TESForm *form);

    const char *Get_Base_Name(TESObjectREFR *ref_object);
    const char *Get_Ref_Name(TESObjectREFR *ref_object);
    const char *Get_Name(TESObjectREFR *ref_object);

    bool Is_Off_Limits(TESObjectREFR *ref_object);
    bool Is_Quest_Item(TESObjectREFR *ref_object);
    bool Is_Worn(TESObjectREFR *obj, TESForm *form);

    void Remove_Unwearable(TESObjectREFR *obj, TESObjectREFR *other);

    void Log_XContainer(TESObjectREFR *ref_object);

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    void Remove_Unwearable(StaticFunctionTag *, TESObjectREFR *obj, TESObjectREFR *other);

    void Log_XContainer(StaticFunctionTag *, TESObjectREFR *ref_object);

    bool Register(VMClassRegistry *registry);

}}}
