/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameRTTI.h"

#include "consts.h"
#include "form.h"
#include "game.h"
#include "object_ref.h"
#include "string2.h"
#include "types.h"
#include "utils.h"

namespace doticu_npcp { namespace Game {

    Bool_t Is_Outsourced_Follower(Actor_t* actor)
    {
        if (actor) {
            ExtraAliasInstanceArray* xaliases = static_cast<ExtraAliasInstanceArray*>
                (actor->extraData.GetByType(kExtraData_AliasInstanceArray));
            using Alias_Info_t = ExtraAliasInstanceArray::AliasInfo;
            if (xaliases) {
                BSReadLocker locker(&xaliases->lock);
                Quest_t* vanilla_followers_quest = Consts::Follower_Dialogue_Quest();
                Quest_t* npcp_followers_quest = Consts::Followers_Quest();
                Package_t* follower_template_package = Consts::Follower_Template_Package();
                Package_t* follow_player_template_package = Consts::Follow_Player_Template_Package();
                Package_t* follow_template_package = Consts::Follow_Template_Package();
                Actor_t* player_actor = Consts::Player_Actor();
                Reference_Handle_t player_reference_handle = player_actor->CreateRefHandle();
                for (size_t idx = 0, end = xaliases->aliases.count; idx < end; idx += 1) {
                    Alias_Info_t* alias_info = xaliases->aliases.entries[idx];
                    if (alias_info && alias_info->quest) {
                        if (alias_info->quest == vanilla_followers_quest) {
                            return true;
                        } else if (alias_info->quest != npcp_followers_quest && alias_info->packages) {
                            for (size_t idx = 0, end = alias_info->packages->count; idx < end; idx += 1) {
                                Package_t* package = reinterpret_cast<Package_t*>(alias_info->packages->entries[idx]);
                                if (package) {
                                    if (package->data) {
                                        Package_t* package_template = package->data->package_template;
                                        if (package_template == follower_template_package ||
                                            package_template == follow_player_template_package ||
                                            package_template == follow_template_package) {
                                            for (size_t idx = 0, end = package->data->value_count; idx < end; idx += 1) {
                                                Package_Value_t* value = package->data->values[idx];
                                                if (value && value->Type() == Package_Value_t::Type_e::SINGLE_REFERENCE) {
                                                    Package_Target_t* target =
                                                        static_cast<Package_Single_Reference_Value_t*>(value)->target;
                                                    if (target) {
                                                        if (target->type == Package_Target_t::Type_e::SPECIFIC) {
                                                            if (target->target.specific == player_reference_handle) {
                                                                return true;
                                                            }
                                                        } else if (target->type == Package_Target_t::Type_e::LINKED) {
                                                            if (target->target.linked == player_actor ||
                                                                target->target.linked == player_actor->baseForm) {
                                                                return true;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                return false;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

}}
