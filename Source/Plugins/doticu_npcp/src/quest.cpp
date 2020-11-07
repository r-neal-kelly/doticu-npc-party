/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"
#include "skse64/GameRTTI.h"

#include "consts.h"
#include "object_ref.h"
#include "papyrus.h"
#include "papyrus.inl"
#include "quest.h"
#include "types.h"
#include "utils.h"

namespace doticu_npcp { namespace Quest {

    const char *Get_Name(TESQuest *quest) {
        if (!quest) {
            return "";
        }

        TESFullName *full_name = DYNAMIC_CAST(quest, TESQuest, TESFullName);
        if (!full_name || !full_name->name || !full_name->name.data) {
            return "";
        }

        return full_name->name.data;
    }

    bool Is_Alias_Filled(Quest_t* quest, UInt16 alias_id)
    {
        if (quest) {
            Quest_t2::Hash_Map_t* hash_map = (Quest_t2::Hash_Map_t*)((u8*)quest + 0x070);
            if (hash_map) {
                return hash_map->Has_Key(alias_id);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Actor_t* Alias_Actor(Quest_t* quest, UInt16 alias_id)
    {
        if (quest) {
            tArray<Reference_Handle_t>* promoted = (tArray<Reference_Handle_t>*)((u8*)quest + 0x250);
            if (promoted) {
                for (size_t idx = 0, count = promoted->count; idx < count; idx += 1) {
                    Reference_Handle_t handle = promoted->entries[idx];
                    Reference_t* reference = Object_Ref::From_Handle(handle);
                    if (reference) {
                        XAliases_t* xaliases = static_cast<XAliases_t*>
                            (reference->extraData.GetByType(kExtraData_AliasInstanceArray));
                        if (xaliases) {
                            for (size_t idx = 0, count = xaliases->aliases.count; idx < count; idx += 1) {
                                XAliases_t::AliasInfo* info = xaliases->aliases.entries[idx];
                                if (info && info->quest == quest && info->alias && info->alias->aliasId == alias_id) {
                                    return static_cast<Actor_t*>(reference);
                                }
                            }
                        }
                    }
                }
            }
        }

        return nullptr;
    }

    void Clear_Alias(Quest_t* quest, UInt16 alias_id)
    {
        using namespace Papyrus;

        NPCP_ASSERT(quest);
        NPCP_ASSERT(alias_id < quest->aliases.count);

        Alias_Reference_t* alias = reinterpret_cast<Alias_Reference_t*>
            (quest->aliases.entries[alias_id]);
        Virtual_Machine_t::Self()->Send_Event(alias, "Clear");

        // to do this manually would at minimum require that we clear the relevant data
        // on quest, which is from a hashmap and an array (at least) and we clear data
        // on the actor, like promoted ref and xaliases. but I'm not sure what else
        // there might be I don't know about. I still haven't found the actual function
        // in the executable. maybe it's nearby Alias_Reference_t instead of Quest_t,
        // like ForceToRef is.
    }

    void Log_Aliases(Quest_t* quest)
    {
        _MESSAGE("Start Log Aliases: %s {", Get_Name(quest));

        _MESSAGE("Hashmap");
        Quest_t2::Hash_Map_t* hash_map = (Quest_t2::Hash_Map_t*)((u8*)quest + 0x070);
        for (size_t idx = 0, count = hash_map->capacity; idx < count; idx += 1) {
            Quest_t2::Hash_Map_t::Entry_t* entry = hash_map->entries + idx;
            if (entry->chain != nullptr) {
                _MESSAGE("    idx: %zu, key: %u, value: %u", idx, entry->tuple.key, entry->tuple.value);
            }
        }

        _MESSAGE("Promoted");
        tArray<Reference_Handle_t>* arr = (tArray<Reference_Handle_t>*)((u8*)quest + 0x250);
        for (size_t idx = 0, count = arr->count; idx < count; idx += 1) {
            Reference_Handle_t handle = arr->entries[idx];
            if (handle) {
                Reference_t* reference = Object_Ref::From_Handle(handle);
                if (reference) {
                    XAliases_t* xaliases = static_cast<XAliases_t*>
                        (reference->extraData.GetByType(kExtraData_AliasInstanceArray));
                    if (xaliases) {
                        for (size_t idx1 = 0, count = xaliases->aliases.count; idx1 < count; idx1 += 1) {
                            if (xaliases->aliases.entries[idx1]->quest == quest) {
                                UInt16 alias_id = xaliases->aliases.entries[idx1]->alias->aliasId;
                                _MESSAGE("    idx: %zu, handle: %u, ref: %p, id: %u",
                                         idx, handle, reference, alias_id);
                            }
                        }
                    }
                }
            }
        }

        _MESSAGE("}");
    }

    Bool_t Start(Quest_t* quest)
    {
        static auto start = reinterpret_cast
            <Bool_t(*)(Quest_t*, Bool_t&, Bool_t)>
            (RelocationManager::s_baseAddr + Offsets::Quest::START);
        Bool_t b; // what is this for? a latent indicator?
        return start(quest, b, true);
    }

    void Start_All(const Vector_t<Quest_t*> quests, Callback_t<>* user_callback)
    {
        using UCallback_t = Callback_t<>;
        NPCP_ASSERT(user_callback);

        struct VCallback : public Virtual_Callback_t {
            const Vector_t<Quest_t*> quests;
            size_t index;
            UCallback_t* user_callback;
            VCallback(const Vector_t<Quest_t*> quests, size_t index, UCallback_t* user_callback) :
                quests(quests), index(index), user_callback(user_callback)
            {
            }
            void operator()(Variable_t* result)
            {
                if (index < quests.size()) {
                    Virtual_Callback_i* vcallback = new VCallback(quests, index + 1, user_callback);
                    Papyrus::Virtual_Machine_t::Self()->Call_Method(quests[index], "Quest", "Start", nullptr, &vcallback);
                } else {
                    user_callback->operator()();
                    delete user_callback;
                }
            }
        };

        size_t index = 0;
        Virtual_Callback_i* vcallback = new VCallback(quests, index + 1, user_callback);
        Papyrus::Virtual_Machine_t::Self()->Call_Method(quests[index], "Quest", "Start", nullptr, &vcallback);
    }

    /*void Start(Quest_t* quest)
    {
        Papyrus::Virtual_Machine_t::Self()->Call_Method(quest, "Quest", "Start", nullptr, nullptr);
    }*/

    Vector_t<Custom_Branch_t> Custom_Branches(Quest_t* quest)
    {
        NPCP_ASSERT(quest);

        Vector_t<Custom_Branch_t> branches;

        for (size_t idx = 0, count = 2; idx < count; idx += 1) {
            using Branch_Map_t = Hash_Map_t<Branch_t*, tArray<Topic_t*>*>;
            Branch_Map_t& branch_tab = reinterpret_cast<Branch_Map_t&>(quest->unk118[idx]);
            for (size_t idx = 0, count = branch_tab.capacity; idx < count; idx += 1) {
                Branch_Map_t::Entry_t* entry = branch_tab.entries + idx;
                if (entry && entry->chain != nullptr) {
                    Branch_t* branch = entry->tuple.key;
                    tArray<Topic_t*>* topics = entry->tuple.value;
                    if (branch && topics) {
                        branches.push_back(
                            Custom_Branch_t(branch, reinterpret_cast<tArray<Topic_t*>&>(*topics))
                        );
                    }
                }
            }
        }

        return branches;
    }

    enum {
        QUEST_BRANCH_SCENE = 0,
        QUEST_BRANCH_COMBAT,
        QUEST_BRANCH_FAVORS,
        QUEST_BRANCH_DETECTION,
        QUEST_BRANCH_SERVICE,
        QUEST_BRANCH_MISC,
    };

    tArray<Topic_t*>& Scene_Branch(Quest_t* quest)
    {
        NPCP_ASSERT(quest);
        return reinterpret_cast<tArray<Topic_t*>&>(quest->unk178[QUEST_BRANCH_SCENE]);
    }

    tArray<Topic_t*>& Combat_Branch(Quest_t* quest)
    {
        NPCP_ASSERT(quest);
        return reinterpret_cast<tArray<Topic_t*>&>(quest->unk178[QUEST_BRANCH_COMBAT]);
    }

    tArray<Topic_t*>& Favors_Branch(Quest_t* quest)
    {
        NPCP_ASSERT(quest);
        return reinterpret_cast<tArray<Topic_t*>&>(quest->unk178[QUEST_BRANCH_FAVORS]);
    }

    tArray<Topic_t*>& Detection_Branch(Quest_t* quest)
    {
        NPCP_ASSERT(quest);
        return reinterpret_cast<tArray<Topic_t*>&>(quest->unk178[QUEST_BRANCH_DETECTION]);
    }

    tArray<Topic_t*>& Service_Branch(Quest_t* quest)
    {
        NPCP_ASSERT(quest);
        return reinterpret_cast<tArray<Topic_t*>&>(quest->unk178[QUEST_BRANCH_SERVICE]);
    }

    tArray<Topic_t*>& Misc_Branch(Quest_t* quest)
    {
        NPCP_ASSERT(quest);
        return reinterpret_cast<tArray<Topic_t*>&>(quest->unk178[QUEST_BRANCH_MISC]);
    }

    Bool_t Has_Single(tArray<Topic_t*>& topics)
    {
        if (topics.count > 0) {
            for (size_t idx = 0, end = topics.count; idx < end; idx += 1) {
                if (Has_Single(topics[idx])) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

    Bool_t Has_Single(Topic_t* topic)
    {
        if (topic) {
            NPCP_ASSERT(topic->quest);
            if (topic->topic_info_count > 0) {
                for (size_t idx = 0, end = topic->topic_info_count; idx < end; idx += 1) {
                    Topic_Info_t* topic_info = topic->topic_infos[idx];
                    if (topic_info) {
                        Dialogue_Info_t dialogue_info(topic->quest, topic, topic_info, nullptr);
                        if (dialogue_info.responses.Count() == 1) {
                            return true;
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

    void Log_Dialogue(Quest_t* quest, Bool_t do_empty, Bool_t only_singles)
    {
        if (quest) {
            _MESSAGE("quest: %8.8X %s", quest->formID, quest->Editor_ID());

            Vector_t<Custom_Branch_t> player_branches = Custom_Branches(quest);
            for (size_t idx = 0, end = player_branches.size(); idx < end; idx += 1) {
                Custom_Branch_t player_branch = player_branches[idx];
                Log_Branch(player_branch.branch, player_branch.topics, "    ", do_empty, only_singles);
            }

            Log_Branch("SCENE", Scene_Branch(quest), "    ", do_empty, only_singles);
            Log_Branch("COMBAT", Combat_Branch(quest), "    ", do_empty, only_singles);
            Log_Branch("FAVORS", Favors_Branch(quest), "    ", do_empty, only_singles);
            Log_Branch("DETECTION", Detection_Branch(quest), "    ", do_empty, only_singles);
            Log_Branch("SERVICE", Service_Branch(quest), "    ", do_empty, only_singles);
            Log_Branch("MISC", Misc_Branch(quest), "    ", do_empty, only_singles);
        }
    }

    void Log_Branch(Branch_t* branch, tArray<Topic_t*>& topics, std::string indent, Bool_t do_empty, Bool_t only_singles)
    {
        if (branch) {
            if (do_empty || topics.count > 0) {
                if (!only_singles || Has_Single(topics)) {
                    _MESSAGE((indent + "branch: %8.8X %s").c_str(), branch->formID, branch->Editor_ID());
                    for (size_t idx = 0, end = topics.count; idx < end; idx += 1) {
                        Log_Topic(topics[idx], indent + "    ", do_empty, only_singles);
                    }
                }
            }
        }
    }

    void Log_Branch(const char* name, tArray<Topic_t*>& topics, std::string indent, Bool_t do_empty, Bool_t only_singles)
    {
        if (do_empty || topics.count > 0) {
            if (!only_singles || Has_Single(topics)) {
                _MESSAGE((indent + "branch: %s").c_str(), name);
                for (size_t idx = 0, end = topics.count; idx < end; idx += 1) {
                    Log_Topic(topics[idx], indent + "    ", do_empty, only_singles);
                }
            }
        }
    }

    void Log_Topic(Topic_t* topic, std::string indent, Bool_t do_empty, Bool_t only_singles)
    {
        if (topic) {
            if (do_empty || topic->topic_info_count > 0) {
                if (!only_singles || Has_Single(topic)) {
                    _MESSAGE((indent + "topic: %8.8X %s").c_str(), topic->formID, topic->Editor_ID());
                    for (size_t idx = 0, end = topic->topic_info_count; idx < end; idx += 1) {
                        Log_Topic_Info(topic->topic_infos[idx], indent + "    ", do_empty, only_singles);
                    }
                }
            }
        }
    }

    void Log_Topic_Info(Topic_Info_t* topic_info, std::string indent, Bool_t do_empty, Bool_t only_singles)
    {
        if (topic_info) {
            NPCP_ASSERT(topic_info->topic);
            NPCP_ASSERT(topic_info->topic->quest);
            Dialogue_Info_t dialogue_info(topic_info->topic->quest, topic_info->topic, topic_info, nullptr);
            Int_t response_count = dialogue_info.responses.Count();
            if (do_empty || response_count > 0) {
                if (!only_singles || response_count == 1) {
                    _MESSAGE((indent + "topic_info: %8.8X %s").c_str(), topic_info->formID, topic_info->Editor_ID());
                    for (auto it = dialogue_info.responses.Begin(); !it.End(); ++it) {
                        Dialogue_Response_t* response = it.Get();
                        if (response) {
                            _MESSAGE((indent + "    %s").c_str(), response->text.Get());
                        }
                    }
                }
            }
        }
    }

    void Log_Start_Enabled_Dialogue()
    {
        DataHandler* data_handler = DataHandler::GetSingleton();
        if (data_handler) {
            for (size_t idx = 0, count = data_handler->quests.count; idx < count; idx += 1) {
                Quest_t* quest = *(data_handler->quests.entries + idx);
                if (quest && (quest->unk0D8.flags & (1 << 4))) {
                    Log_Dialogue(quest, false, true);
                }
            }
        }
    }

}}
