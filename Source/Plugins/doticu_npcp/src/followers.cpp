/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "follower.h"
#include "followers.h"
#include "member.h"
#include "object_ref.h"

namespace doticu_npcp { namespace Followers {

    void Stash(TESQuest *quest) {
        if (!quest) {
            return;
        }

        BGSBaseAlias *follower;
        for (u64 idx = 0, size = quest->aliases.count; idx < size; idx += 1) {
            quest->aliases.GetNthItem(idx, follower);
            if (!follower) {
                continue;
            }

            BGSBaseAlias *member = Follower::Get_Member(follower);
            if (!member) {
                continue;
            }

            TESObjectREFR *pack = Member::Get_Pack(member);
            if (!pack) {
                continue;
            }

            Object_Ref::Categorize(pack);
        }
    }

}}

namespace doticu_npcp { namespace Followers { namespace Exports {

    void Stash(StaticFunctionTag *, TESQuest *quest) {
        return Followers::Stash(quest);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, TESQuest *>(
                "Followers_Stash",
                "doticu_npcp",
                Exports::Stash,
                registry)
        );

        return true;
    }

}}}
