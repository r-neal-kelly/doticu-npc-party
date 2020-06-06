/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "member.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Member {

    Actor *Get_Actor(Member_t *member) {
        if (!member) {
            return NULL;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_ref_actor").As_Actor();
    }

    TESObjectREFR *Get_Pack(Member_t *member) {
        if (!member) {
            return NULL;
        }

        Papyrus::Handle hnd(kFormType_Alias, member);
        return Papyrus::Value(&hnd, "p_container_pack").As_Object();
    }

    SInt32 Get_Style(Member_t *member) {
        if (!member) {
            return NULL;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_code_style").As_Int();
    }

    SInt32 Get_Vitality(Member_t *member) {
        if (!member) {
            return NULL;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_code_vitality").As_Int();
    }

    SInt32 Get_Outfit2(Member_t *member) {
        if (!member) {
            return NULL;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_code_outfit2").As_Int();
    }

    SInt32 Get_Rating(Member_t *member) {
        if (!member) {
            return NULL;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_int_rating").As_Int();
    }

    bool Is_Created(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_is_created").As_Bool();
    }

    bool Is_Original(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return !Papyrus::Value(&hnd_alias, "p_is_clone").As_Bool();
    }

    bool Is_Clone(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_is_clone").As_Bool();
    }

    bool Is_Follower(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_is_follower").As_Bool();
    }

    bool Is_Mobile(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return !Papyrus::Value(&hnd_alias, "p_is_immobile").As_Bool();
    }

    bool Is_Immobile(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_is_immobile").As_Bool();
    }

    bool Is_Settler(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_is_settler").As_Bool();
    }

    bool Isnt_Settler(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return !Papyrus::Value(&hnd_alias, "p_is_settler").As_Bool();
    }

    bool Is_Thrall(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_is_thrall").As_Bool();
    }

    bool Is_Paralyzed(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_is_paralyzed").As_Bool();
    }

    bool Is_Mannequin(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_is_mannequin").As_Bool();
    }

    bool Is_Reanimated(Member_t *member) {
        if (!member) {
            return false;
        }

        Papyrus::Handle hnd_alias(kFormType_Alias, member);
        return Papyrus::Value(&hnd_alias, "p_is_reanimated").As_Bool();
    }

}}

namespace doticu_npcp { namespace Member { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        return true;
    }

}}}
