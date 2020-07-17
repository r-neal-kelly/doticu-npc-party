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

    TESNPC::Color* Get_Skin_Color(TESNPC* actor_base)
    {
        if (actor_base) {
            return &actor_base->color;
        } else {
            return nullptr;
        }
    }

    bool Has_Same_Skin_Color(TESNPC* actor_base_a, TESNPC* actor_base_b)
    {
        return
            actor_base_a && actor_base_b &&
            actor_base_a->color.red == actor_base_b->color.red &&
            actor_base_a->color.green == actor_base_b->color.green &&
            actor_base_a->color.blue == actor_base_b->color.blue;
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

        if (!Has_Same_Skin_Color(actor_base_a, actor_base_b)) {
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

    Actor_Value_Owner_t* Actor_Value_Owner(Actor_Base_t* actor_base)
    {
        return actor_base ?
            reinterpret_cast<Actor_Value_Owner_t*>(&actor_base->actorValueOwner) :
            nullptr;
    }

    float Get_Actor_Value(TESNPC *actor_base, const char *name) {
        if (!actor_base || !name || !name[0]) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor_base->actorValueOwner.GetCurrent(id_value);
    }

    float Get_Base_Actor_Value(TESNPC *actor_base, const char *name) {
        if (!actor_base || !name || !name[0]) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor_base->actorValueOwner.GetBase(id_value);
    }

    float Get_Max_Actor_Value(TESNPC *actor_base, const char *name) {
        if (!actor_base) {
            return 0.0;
        }

        UInt32 id_value = LookupActorValueByName(name);
        if (id_value >= ActorValueList::kNumActorValues) {
            return 0.0;
        }

        return actor_base->actorValueOwner.GetMaximum(id_value);
    }

    Bool_t Is_Ghost(Actor_Base_t* actor_base)
    {
        if (actor_base) {
            return reinterpret_cast<Actor_Base_Data_t*>(&actor_base->actorData)->Is_Ghost();
        } else {
            return false;
        }
    }

}}

namespace doticu_npcp { namespace Actor_Base2 { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        return true;
    }

}}}
