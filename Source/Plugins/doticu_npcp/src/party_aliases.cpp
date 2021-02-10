/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "papyrus.inl"
#include "utils.h"

#include "party/party_aliases.h"
#include "party/party_aliases.inl"

#include "mcm/mcm_filter.h"

namespace doticu_npcp { namespace Papyrus { namespace Party {

    Vector_t<String_t> Aliases_t::Filter_Strings(String_t sex, String_t race, String_t search)
    {
        Vector_t<String_t> strings;
        strings.reserve(3);
        strings.push_back(sex);
        strings.push_back(race);
        strings.push_back(search);
        return strings;
    }

    Vector_t<Int_t> Aliases_t::Filter_Ints(Int_t style, Int_t vitality, Int_t outfit2, Int_t rating)
    {
        Vector_t<Int_t> ints;
        ints.reserve(4);
        ints.push_back(style);
        ints.push_back(vitality);
        ints.push_back(outfit2);
        ints.push_back(rating);
        return ints;
    }

    Int_t Aliases_t::Add_Filter_Flag_1(Int_t flags_1, String_t flag_1)
    {
        static const String_t IS_LOADED = String_t("IS_LOADED");
        static const String_t IS_UNLOADED = String_t("IS_UNLOADED");
        static const String_t IS_UNIQUE = String_t("IS_UNIQUE");
        static const String_t IS_GENERIC = String_t("IS_GENERIC");
        static const String_t IS_ORIGINAL = String_t("IS_ORIGINAL");
        static const String_t IS_CLONE = String_t("IS_CLONE");
        static const String_t IS_ALIVE = String_t("IS_ALIVE");
        static const String_t IS_DEAD = String_t("IS_DEAD");
        static const String_t IS_MOBILE = String_t("IS_MOBILE");
        static const String_t IS_IMMOBILE = String_t("IS_IMMOBILE");
        static const String_t IS_SETTLER = String_t("IS_SETTLER");
        static const String_t ISNT_SETTLER = String_t("ISNT_SETTLER");
        static const String_t IS_THRALL = String_t("IS_THRALL");
        static const String_t ISNT_THRALL = String_t("ISNT_THRALL");
        static const String_t IS_PARALYZED = String_t("IS_PARALYZED");
        static const String_t ISNT_PARALYZED = String_t("ISNT_PARALYZED");
        static const String_t IS_MANNEQUIN = String_t("IS_MANNEQUIN");
        static const String_t ISNT_MANNEQUIN = String_t("ISNT_MANNEQUIN");
        static const String_t IS_REANIMATED = String_t("IS_REANIMATED");
        static const String_t ISNT_REANIMATED = String_t("ISNT_REANIMATED");
        static const String_t IS_FOLLOWER = String_t("IS_FOLLOWER");
        static const String_t ISNT_FOLLOWER = String_t("ISNT_FOLLOWER");
        static const String_t IS_SNEAK = String_t("IS_SNEAK");
        static const String_t ISNT_SNEAK = String_t("ISNT_SNEAK");
        static const String_t IS_SADDLER = String_t("IS_SADDLER");
        static const String_t ISNT_SADDLER = String_t("ISNT_SADDLER");
        static const String_t IS_RETREATER = String_t("IS_RETREATER");
        static const String_t ISNT_RETREATER = String_t("ISNT_RETREATER");

        if (String2::Is_Same_Caseless(flag_1, IS_UNIQUE)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_UNIQUE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_GENERIC)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_GENERIC);
        } else if (String2::Is_Same_Caseless(flag_1, IS_LOADED)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_LOADED);
        } else if (String2::Is_Same_Caseless(flag_1, IS_UNLOADED)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_UNLOADED);
        } else if (String2::Is_Same_Caseless(flag_1, IS_ALIVE)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_ALIVE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_DEAD)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_DEAD);
        } else if (String2::Is_Same_Caseless(flag_1, IS_ORIGINAL)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_ORIGINAL);
        } else if (String2::Is_Same_Caseless(flag_1, IS_CLONE)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_CLONE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_MOBILE)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_MOBILE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_IMMOBILE)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_IMMOBILE);
        } else if (String2::Is_Same_Caseless(flag_1, IS_SETTLER)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_SETTLER);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_SETTLER)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::ISNT_SETTLER);
        } else if (String2::Is_Same_Caseless(flag_1, IS_THRALL)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_THRALL);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_THRALL)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::ISNT_THRALL);
        } else if (String2::Is_Same_Caseless(flag_1, IS_PARALYZED)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_PARALYZED);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_PARALYZED)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::ISNT_PARALYZED);
        } else if (String2::Is_Same_Caseless(flag_1, IS_MANNEQUIN)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_MANNEQUIN);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_MANNEQUIN)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::ISNT_MANNEQUIN);
        } else if (String2::Is_Same_Caseless(flag_1, IS_REANIMATED)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_REANIMATED);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_REANIMATED)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::ISNT_REANIMATED);
        } else if (String2::Is_Same_Caseless(flag_1, IS_FOLLOWER)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_FOLLOWER);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_FOLLOWER)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::ISNT_FOLLOWER);
        } else if (String2::Is_Same_Caseless(flag_1, IS_SNEAK)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_SNEAK);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_SNEAK)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::ISNT_SNEAK);
        } else if (String2::Is_Same_Caseless(flag_1, IS_SADDLER)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_SADDLER);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_SADDLER)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::ISNT_SADDLER);
        } else if (String2::Is_Same_Caseless(flag_1, IS_RETREATER)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::IS_RETREATER);
        } else if (String2::Is_Same_Caseless(flag_1, ISNT_RETREATER)) {
            return Utils::Bit_On(flags_1, MCM::Filter_t::Flags_1::ISNT_RETREATER);
        } else {
            return flags_1;
        }
    }

    Int_t Aliases_t::Add_Filter_Flag_2(Int_t flags_2, String_t flag_2)
    {
        return flags_2;
    }

}}}
