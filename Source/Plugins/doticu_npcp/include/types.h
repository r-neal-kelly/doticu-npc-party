/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_npcp {

    typedef SpellItem       Spell_t;

    typedef Projectile      Projectile_t;
    typedef BGSProjectile   Projectile_Base_t;


    typedef BGSVoiceType    Voice_Type_t;

    typedef BGSDialogueBranch   Branch_t;

    class Topic_Info_t;
    class Topic_t : public Form_t {
    public:
        enum {
            kTypeID = kFormType_Topic
        };

        virtual ~Topic_t();

        TESFullName full_name; // 20

        UInt8 flags; // 30
        UInt8 type; // 31
        UInt16 subtype; // 32
        UInt32 priority_and_journal_index; // 34
        Branch_t* branch; // 38
        Quest_t* quest; // 40
        Topic_Info_t** topic_infos; // 48
        UInt32 topic_info_count; // 50
        String_t editor_id; // 58
    };
    STATIC_ASSERT(sizeof(Topic_t) == 0x60);

    class Topic_Info_t : public Form_t {
    public:
        enum {
            kTypeID = kFormType_TopicInfo
        };

        virtual ~Topic_Info_t();

        Topic_t* topic; // 20
        Topic_Info_t* shared; // 28 (I think)
        Condition* conditions; // 30
        UInt16 index; // 38 (to array on topic)
        Bool_t said_once; // 3A
        UInt8 favor_level; // 3B
        UInt16 flags; // 3C
        UInt16 hours_to_reset; // 3E
        UInt32 mod_info_offset; // 40
        UInt32 pad_44; // 44

        Bool_t Is_In_Quest(Quest_t* quest)
        {
            if (topic) {
                if (topic->quest) {
                    return topic->quest == quest;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }

        Bool_t Is_In_Branch(Branch_t* branch)
        {
            if (topic) {
                if (topic->branch) {
                    return topic->branch == branch;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }

        Bool_t Is_In_Topic(Topic_t* topic)
        {
            if (this->topic) {
                return this->topic == topic;
            } else {
                return false;
            }
        }

        Branch_t* Branch()
        {
            if (topic) {
                return topic->branch;
            } else {
                return nullptr;
            }
        }
    };
    STATIC_ASSERT(sizeof(Topic_Info_t) == 0x48);

    class Process_Lists_t {
    public:
        static Process_Lists_t* Self();
    public:
        void Stop_Combat_Alarm(Actor_t* actor, Bool_t dont_end_alarm = false);
    };

    class Dialogue_Response_t {
    public:
        enum class Emotion_e : UInt32 {
            NEUTRAL = 0,
            ANGER = 1,
            DISGUST = 2,
            FEAR = 3,
            SAD = 4,
            HAPPY = 5,
            SURPRISE = 6,
            PUZZLED = 7,
        };

        BSString text; // 00
        Emotion_e emotion; // 10
        UInt32 emotion_value; // 14
        BSFixedString voice_text; // 18
        TESIdleForm* speaker_idle; // 20
        TESIdleForm* listener_idle; // 28
        BGSSoundDescriptorForm* voice_sound; // 30
        Bool_t allow_emotion; // 38
        Bool_t has_sound_lip; // 39
        UInt16 pad_3A; // 3A
        UInt32 pad_3C; // 3C
    };
    STATIC_ASSERT(sizeof(Dialogue_Response_t) == 0x40);

    class Dialogue_Info_t {
    public:
        Dialogue_Info_t(Quest_t* quest, Topic_t* topic, Topic_Info_t* topic_info, Actor_t* speaker);

        UInt32 ref_count; // 00
        UInt32 pad_04; // 04
        tList<Dialogue_Response_t> responses; // 08
        void* current_response; // 18 (node in tList?)
        Topic_Info_t* topic_info; // 20
        Topic_t* topic; // 28
        Quest_t* quest; // 30
        Actor_t* speaker; // 38
        void* extra_response; // 40 (ExtraSayToTopicInfo)
    };

}
