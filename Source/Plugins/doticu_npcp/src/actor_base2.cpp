/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"

#include "actor_base2.h"

namespace doticu_npcp { namespace Actor_Base2 {

    BGSColorForm *Get_Hair_Color(TESNPC *actor_base) {
        if (!actor_base || !actor_base->headData) {
            return NULL;
        }

        return actor_base->headData->hairColor;
    }

    TESObjectARMO *Get_Skin(TESNPC *actor_base) {
        if (!actor_base) {
            return NULL;
        }

        return actor_base->skinForm.skin;
    }

    bool Has_Same_Head(TESNPC *actor_base_a, TESNPC *actor_base_b) {
        if (!actor_base_a || !actor_base_b) {
            return false;
        }

        if (actor_base_a->nextTemplate) {
            actor_base_a = actor_base_a->GetRootTemplate();
        }
        if (actor_base_b->nextTemplate) {
            actor_base_b = actor_base_b->GetRootTemplate();
        }

        if (actor_base_a == actor_base_b) {
            return true;
        }

        if (actor_base_a->numHeadParts != actor_base_b->numHeadParts) {
            return false;
        }

        if (Get_Hair_Color(actor_base_a) != Get_Hair_Color(actor_base_b)) {
            return false;
        }

        if (Get_Skin(actor_base_a) != Get_Skin(actor_base_b)) {
            return false;
        }

        for (u64 idx = 0, size = actor_base_a->numHeadParts; idx < size; idx += 1) {
            if (actor_base_a->headparts[idx] != actor_base_b->headparts[idx]) {
                return false;
            }
        }

        TESNPC::FaceMorphs *face_a = actor_base_a->faceMorph;
        TESNPC::FaceMorphs *face_b = actor_base_b->faceMorph;
        if (face_a && !face_b || !face_a && face_b) {
            return false;
        }

        if (face_a && face_b) {
            for (u64 idx = 0, size = TESNPC::FaceMorphs::kNumOptions; idx < size; idx += 1) {
                if (face_a->option[idx] != face_b->option[idx]) {
                    return false;
                }
            }

            for (u64 idx = 0, size = TESNPC::FaceMorphs::kNumPresets; idx < size; idx += 1) {
                if (face_a->presets[idx] != face_b->presets[idx]) {
                    return false;
                }
            }
        }

        return true;
    }

    float Get_Max_Actor_Value(TESNPC *actor_base, BSFixedString name) {
        if (!actor_base) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name.data);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor_base->actorValueOwner.GetMaximum(id_value);
    }

}}

namespace doticu_npcp { namespace Actor_Base2 { namespace Exports {

    float Get_Max_Actor_Value(StaticFunctionTag *, TESNPC *actor_base, BSFixedString name) {
        return Actor_Base2::Get_Max_Actor_Value(actor_base, name);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, float, TESNPC *, BSFixedString>(
                "Actor_Base2_Get_Max_Actor_Value",
                "doticu_npcp",
                Exports::Get_Max_Actor_Value,
                registry)
        );

        _MESSAGE("Added Actor_Base2 functions.");

        return true;
    }

}}}
