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

        TESForm *Form(s64 idx) {
            if (idx > -1 && idx < forms.size()) {
                return forms[idx];
            } else {
                return NULL;
            }
        }
        s64 Count(s64 idx) {
            if (idx > -1 && idx < counts.size()) {
                return counts[idx];
            } else {
                return 0;
            }
        }
        s64 Count(TESForm *ref_form) {
            s64 idx = Vector::Index_Of(forms, ref_form);
            if (idx > -1) {
                return counts[idx];
            } else {
                return 0;
            }
        }
        u64 Size() {
            return forms.size();
        }
        s64 Idx(TESForm *ref_form) {
            return Vector::Index_Of(forms, ref_form);
        }
        bool Has(TESForm *ref_form) {
            return Vector::Index_Of(forms, ref_form) > -1;
        }

        void Increment(TESForm *ref_form, s64 count) {
            if (count > 0) {
                s64 idx = Vector::Index_Of(forms, ref_form);
                if (idx > -1) {
                    counts[idx] += count;
                }
            }
        }
        void Decrement(TESForm *ref_form, s64 count) {
            if (count > 0) {
                s64 idx = Vector::Index_Of(forms, ref_form);
                if (idx > -1) {
                    counts[idx] -= count;
                    if (counts[idx] < 0) {
                        counts[idx] = 0;
                    }
                }
            }
        }
        void Increment(s64 idx, s64 count) {
            if (idx > -1 && idx < counts.size() && count > 0) {
                counts[idx] += count;
            }
        }
        void Decrement(s64 idx, s64 count) {
            if (idx > -1 && idx < counts.size() && count > 0) {
                counts[idx] -= count;
                if (counts[idx] < 0) {
                    counts[idx] = 0;
                }
            }
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
    void Remove_Item(TESObjectREFR *ref_object, TESForm *ref_form, SInt32 count, TESObjectREFR *ref_other);
    void Remove_All_Items(TESObjectREFR *ref_object);

    void Log_Items(TESObjectREFR *ref_object);

}}

namespace doticu_npcp { namespace Object_Ref { namespace Exports {

    void Log_Items(StaticFunctionTag *, TESObjectREFR *ref_object);

    bool Register(VMClassRegistry *registry);

}}}
