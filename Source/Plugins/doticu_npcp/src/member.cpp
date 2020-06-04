/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "member.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Member {

    TESObjectREFR *Get_Pack(BGSBaseAlias *member) {
        if (!member) {
            return NULL;
        }

        Papyrus::Handle hnd(kFormType_Alias, member);
        return Papyrus::Value(&hnd, "p_container_pack").As_Object();
    }

}}

namespace doticu_npcp { namespace Member { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        return true;
    }

}}}
