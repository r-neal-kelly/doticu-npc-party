/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "papyrus.h"

namespace doticu_npcp { namespace Quest {

    using namespace Papyrus;

    const char *Get_Name(TESQuest *quest);

    bool Is_Alias_Filled(Quest_t* quest, UInt16 alias_id);
    Actor_t* Alias_Actor(Quest_t* quest, UInt16 alias_id);
    void Clear_Alias(Quest_t* quest, UInt16 alias_id);

    void Log_Aliases(Quest_t* quest);

    Bool_t Start(Quest_t* quest);
    //void Start(Quest_t* quest);
    void Start_All(const Vector_t<Quest_t*> quests, Callback_t<>* user_callback);

    class Custom_Branch_t {
    public:
        Branch_t* branch;
        tArray<Topic_t*>& topics;

        Custom_Branch_t(Branch_t* branch, tArray<Topic_t*>& topics) :
            branch(branch), topics(topics)
        {
        }
    };

    Vector_t<Custom_Branch_t> Custom_Branches(Quest_t* quest);
    tArray<Topic_t*>& Scene_Branch(Quest_t* quest);
    tArray<Topic_t*>& Combat_Branch(Quest_t* quest);
    tArray<Topic_t*>& Favors_Branch(Quest_t* quest);
    tArray<Topic_t*>& Detection_Branch(Quest_t* quest);
    tArray<Topic_t*>& Service_Branch(Quest_t* quest);
    tArray<Topic_t*>& Misc_Branch(Quest_t* quest);

    Bool_t Has_Single(tArray<Topic_t*>& topics);
    Bool_t Has_Single(Topic_t* topic);

    void Log_Dialogue(Quest_t* quest, Bool_t do_empty = true, Bool_t only_singles = false);
    void Log_Branch(Branch_t* branch, tArray<Topic_t*>& topics, std::string indent, Bool_t do_empty = true, Bool_t only_singles = false);
    void Log_Branch(const char* name, tArray<Topic_t*>& topics, std::string indent, Bool_t do_empty = true, Bool_t only_singles = false);
    void Log_Topic(Topic_t* topic, std::string indent, Bool_t do_empty = true, Bool_t only_singles = false);
    void Log_Topic_Info(Topic_Info_t* topic_info, std::string indent, Bool_t do_empty = true, Bool_t only_singles = false);

    void Log_Start_Enabled_Dialogue();

}}
