/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "follower.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Follower {

    BGSBaseAlias *Get_Member(BGSBaseAlias *follower) {
        if (!follower) {
            return NULL;
        }

        Papyrus::Handle hnd(kFormType_Alias, follower);
        return Papyrus::Value(&hnd, "p_ref_member").As_Alias();
    }

}}

namespace doticu_npcp { namespace Follower { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        return true;
    }

}}}
