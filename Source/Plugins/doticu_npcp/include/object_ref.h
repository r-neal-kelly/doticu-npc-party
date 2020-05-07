/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameExtraData.h"
#include "skse64/GameRTTI.h"
#include "skse64/PapyrusActor.h"
#include "skse64/PapyrusNativeFunctions.h"

#include "utils.h"
#include "vector.h"
#include "papyrus.h"
#include "form.h"

namespace doticu_npcp { namespace Object_Ref {

    class Items {
    public:
        std::vector<TESForm *> forms;
        std::vector<s64> counts;

        s64 Count(TESForm *ref_form) {
            s64 idx = Vector::Index_Of(forms, ref_form);
            if (idx > -1) {
                return counts[idx];
            } else {
                return 0;
            }
        }

        bool Has(TESForm *ref_form) {
            return Vector::Index_Of(forms, ref_form) > -1;
        }
    };

    TESContainer *Get_Base_Container(TESObjectREFR *ref_object);
    ExtraContainerChanges *Get_Ref_Container(TESObjectREFR *ref_object);
    Items Get_Items(TESObjectREFR *ref_object, bool get_leveled = false);

    SInt32 Count_Item(TESObjectREFR *ref_object, TESForm *ref_form);
    SInt32 Count_Base_Item(TESObjectREFR *ref_object, TESForm *ref_form);
    SInt32 Count_Ref_Item(TESObjectREFR *ref_object, TESForm *ref_form);

    void Add_Item(TESObjectREFR *ref_object, TESForm *ref_form, SInt32 count);
    void Remove_Item(TESObjectREFR *ref_object, TESForm *ref_form, SInt32 count);
    void Remove_All_Items(TESObjectREFR *ref_object);

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    void Log_Items(StaticFunctionTag *, TESObjectREFR *ref_object);

    bool Register(VMClassRegistry *registry);

}}}
