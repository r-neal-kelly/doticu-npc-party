/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "alias.h"

namespace doticu_npcp { namespace Alias {

    Actor *Get_Actor(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_ref_actor").As_Actor();
    }
    SInt32 Get_Style(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_code_style").As_Int();
    }
    SInt32 Get_Vitality(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_code_vitality").As_Int();
    }
    SInt32 Get_Outfit2(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_code_outfit2").As_Int();
    }
    SInt32 Get_Rating(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_int_rating").As_Int();
    }

    bool Is_Created(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_is_created").As_Bool();
    }
    bool Is_Original(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return !Papyrus::Value(&hnd_alias, "p_is_clone").As_Bool();
    }
    bool Is_Clone(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_is_clone").As_Bool();
    }
    bool Is_Follower(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_is_follower").As_Bool();
    }
    bool Is_Settler(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_is_settler").As_Bool();
    }
    bool Is_Immobile(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_is_immobile").As_Bool();
    }
    bool Is_Thrall(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_is_thrall").As_Bool();
    }
    bool Is_Paralyzed(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_is_paralyzed").As_Bool();
    }
    bool Is_Mannequin(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_is_mannequin").As_Bool();
    }
    bool Is_Reanimated(BGSBaseAlias *ptr_alias) {
        Papyrus::Handle hnd_alias(kFormType_Alias, ptr_alias);
        return Papyrus::Value(&hnd_alias, "p_is_reanimated").As_Bool();
    }

}}
