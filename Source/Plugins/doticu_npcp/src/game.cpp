/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameData.h"

#include "utils.h"
#include "game.h"
#include "string2.h"

namespace doticu_npcp { namespace Game {

    VMResultArray<BSFixedString> Get_Male_Vanilla_Voice_Names() {
        VMResultArray<BSFixedString> results;

        DataHandler *data_handler = DataHandler::GetSingleton();
        if (!data_handler) {
            return results;
        }

        TESForm *form_voice = NULL;
        BGSVoiceType *voice = NULL;
        for (u64 idx = 0, size = data_handler->arrVTYP.count; idx < size; idx += 1) {
            data_handler->arrVTYP.GetNthItem(idx, form_voice);
            voice = (BGSVoiceType *)form_voice;

            if (voice->formID >= 0x05000000) {
                break;
            }

            const char *str_voice = voice->editorId.Get();
            if (String2::Contains(str_voice, "Male")) {
                results.push_back(BSFixedString(str_voice));
            }
        }

        return results;
    }

    VMResultArray<BSFixedString> Get_Female_Vanilla_Voice_Names() {
        VMResultArray<BSFixedString> results;

        DataHandler *data_handler = DataHandler::GetSingleton();
        if (!data_handler) {
            return results;
        }

        TESForm *form_voice = NULL;
        BGSVoiceType *voice = NULL;
        for (u64 idx = 0, size = data_handler->arrVTYP.count; idx < size; idx += 1) {
            data_handler->arrVTYP.GetNthItem(idx, form_voice);
            voice = (BGSVoiceType *)form_voice;

            if (voice->formID >= 0x05000000) {
                break;
            }

            const char *str_voice = voice->editorId.Get();
            if (String2::Contains(str_voice, "Female")) {
                results.push_back(BSFixedString(str_voice));
            }
        }

        return results;
    }

    BGSVoiceType *Get_Voice_By_Name(BSFixedString str_name) {
        DataHandler *data_handler = DataHandler::GetSingleton();
        if (!data_handler) {
            return NULL;
        }

        TESForm *form_voice = NULL;
        BGSVoiceType *voice = NULL;
        for (u64 idx = 0, size = data_handler->arrVTYP.count; idx < size; idx += 1) {
            data_handler->arrVTYP.GetNthItem(idx, form_voice);
            voice = (BGSVoiceType *)form_voice;

            if (String2::Is_Same(voice->editorId.Get(), str_name.data)) {
                return voice;
            }
        }

        return NULL;
    }

}}

namespace doticu_npcp { namespace Game { namespace Exports {

    VMResultArray<BSFixedString> Get_Male_Vanilla_Voice_Names(StaticFunctionTag *) {
        return Game::Get_Male_Vanilla_Voice_Names();
    }

    VMResultArray<BSFixedString> Get_Female_Vanilla_Voice_Names(StaticFunctionTag *) {
        return Game::Get_Female_Vanilla_Voice_Names();
    }

    BGSVoiceType *Get_Voice_By_Name(StaticFunctionTag *, BSFixedString str_name) {
        return Game::Get_Voice_By_Name(str_name);
    }

    bool Register(VMClassRegistry *registry) {
        registry->RegisterFunction(
            new NativeFunction0 <StaticFunctionTag, VMResultArray<BSFixedString>>(
                "Game_Get_Male_Vanilla_Voice_Names",
                "doticu_npcp",
                Exports::Get_Male_Vanilla_Voice_Names,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction0 <StaticFunctionTag, VMResultArray<BSFixedString>>(
                "Game_Get_Female_Vanilla_Voice_Names",
                "doticu_npcp",
                Exports::Get_Female_Vanilla_Voice_Names,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, BGSVoiceType *, BSFixedString>(
                "Game_Get_Voice_By_Name",
                "doticu_npcp",
                Exports::Get_Voice_By_Name,
                registry)
        );

        return true;
    }

}}}
