/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_npcp.h"

namespace doticu_npcp {

    Actor *Alias_Get_Actor(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_ref_actor").As_Actor();
    }

    SInt32 Alias_Get_Rating(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_int_rating").As_Int();
    }

    bool Alias_Is_Created(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_is_created").As_Bool();
    }

    bool Alias_Is_Original(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return !Object_Value(&hnd_alias, "p_is_clone").As_Bool();
    }

    bool Alias_Is_Clone(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_is_clone").As_Bool();
    }

    bool Alias_Is_Follower(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_is_follower").As_Bool();
    }

    bool Alias_Is_Settler(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_is_settler").As_Bool();
    }

    bool Alias_Is_Immobile(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_is_immobile").As_Bool();
    }

    bool Alias_Is_Thrall(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_is_thrall").As_Bool();
    }

    bool Alias_Is_Paralyzed(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_is_paralyzed").As_Bool();
    }

    bool Alias_Is_Mannequin(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_is_mannequin").As_Bool();
    }

    bool Alias_Is_Reanimated(BGSBaseAlias *ptr_alias) {
        Object_Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Object_Value(&hnd_alias, "p_is_reanimated").As_Bool();
    }

}
