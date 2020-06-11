/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "actor2.h"
#include "member.h"
#include "members.h"
#include "papyrus.h"

namespace doticu_npcp { namespace Members {

    void Enforce_Loaded(Members_t *members) {
        if (!members) {
            return;
        }

        BSFixedString func_name("Enforce");
        struct Args : public IFunctionArguments {
            bool Copy(Output *output) { return true; }
        } func_args;

        std::vector<Member_t *> vec_members = Get_Loaded(members);
        for (u64 idx = 0, size = vec_members.size(); idx < size; idx += 1) {
            Member_t *member = vec_members[idx];
            Papyrus::Handle member_handle(kFormType_Alias, member);
            member_handle.Registry()->QueueEvent(member_handle, &func_name, &func_args);
        }
    }

    VMResultArray<Member_t *> Get_Loaded(Members_t *members) {
        VMResultArray<Member_t *> vec_members;

        if (!members) {
            return vec_members;
        }

        Member_t *member;
        for (u64 idx = 0, size = members->aliases.count; idx < size; idx += 1) {
            members->aliases.GetNthItem(idx, member);
            if (!member) {
                continue;
            }

            if (!Member::Is_Created(member)) {
                continue;
            }

            Actor *actor = Member::Get_Actor(member);
            if (!actor || !Actor2::Is_Loaded(actor)) {
                continue;
            }

            vec_members.push_back(member);
        }

        return vec_members;
    }

}}

namespace doticu_npcp { namespace Members { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction0 <Members_t, void>(
                "p_Enforce_Loaded",
                "doticu_npcp_members",
                Members::Enforce_Loaded,
                registry)
        );

        return true;
    }

}}}
