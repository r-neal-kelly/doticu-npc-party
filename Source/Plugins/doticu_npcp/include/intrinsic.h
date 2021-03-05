/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/skylib.h"
#include "doticu_skylib/virtual.h"

#include "doticu_skylib/reference_handle.h"

#include "doticu_mcmlib/mcmlib.h"

namespace doticu_skylib {}
namespace skylib = doticu_skylib;

namespace doticu_npcp {

    using u8                        = skylib::u8;
    using u16                       = skylib::u16;
    using u32                       = skylib::u32;
    using u64                       = skylib::u64;
    using s8                        = skylib::s8;
    using s16                       = skylib::s16;
    using s32                       = skylib::s32;
    using s64                       = skylib::s64;

    using Bool_t                    = skylib::Bool_t;
    using Int_t                     = skylib::Int_t;
    using Float_t                   = skylib::Float_t;
    using Double_t                  = skylib::Double_t;
    using String_t                  = skylib::String_t;
    using CString_t                 = skylib::CString_t;

    using Word_t                    = skylib::Word_t;

    template <typename T>
    using none                      = skylib::none<T>;
    template <typename T>
    using maybe                     = skylib::maybe<T>;
    template <typename T>
    using some                      = skylib::some<T>;

    template <typename T>
    using unique                    = skylib::unique<T>;

    template <typename T>
    using Range_t                   = skylib::Range_t<T>;
    template <typename T>
    using Vector_t                  = skylib::Vector_t<T>;

    template <typename ...Ts>
    using Callback_i                = skylib::Callback_i<Ts...>;

    template <typename T>
    using Version_t                 = skylib::Version_t<T>;

    using Form_Type_e               = skylib::Form_Type_e;
    using Script_Type_e             = skylib::Script_Type_e;

    using Active_Magic_Effect_t     = skylib::Active_Magic_Effect_t;
    using Actor_t                   = skylib::Actor_t;
    using Actor_Base_t              = skylib::Actor_Base_t;
    using Armor_t                   = skylib::Armor_t;
    using Cell_t                    = skylib::Cell_t;
    using Character_t               = skylib::Character_t;
    using Container_t               = skylib::Container_t;
    using Dialogue_Branch_t         = skylib::Dialogue_Branch_t;
    using Dialogue_Topic_t          = skylib::Dialogue_Topic_t;
    using Effect_Shader_t           = skylib::Effect_Shader_t;
    using Faction_t                 = skylib::Faction_t;
    using Faction_And_Rank_t        = skylib::Faction_And_Rank_t;
    using Form_t                    = skylib::Form_t;
    using Form_ID_t                 = skylib::Form_ID_t;
    using Form_List_t               = skylib::Form_List_t;
    using Furniture_t               = skylib::Furniture_t;
    using Game_t                    = skylib::Game_t;
    using Global_t                  = skylib::Global_t;
    using Keyword_t                 = skylib::Keyword_t;
    using Leveled_Actor_Base_t      = skylib::Leveled_Actor_Base_t;
    using Leveled_Item_t            = skylib::Leveled_Item_t;
    using Location_t                = skylib::Location_t;
    using Magic_Effect_t            = skylib::Magic_Effect_t;
    using Magic_Target_t            = skylib::Magic_Target_t;
    using Misc_t                    = skylib::Misc_t;
    using Mod_t                     = skylib::Mod_t;
    using Outfit_t                  = skylib::Outfit_t;
    using Package_t                 = skylib::Package_t;
    using Package_Bool_Value_t      = skylib::Package_Bool_Value_t;
    using Package_Data_t            = skylib::Package_Data_t;
    using Package_Float_Value_t     = skylib::Package_Float_Value_t;
    using Package_Int_Value_t       = skylib::Package_Int_Value_t;
    using Package_Location_t        = skylib::Package_Location_t;
    using Package_Location_Value_t  = skylib::Package_Location_Value_t;
    using Package_Reference_Value_t = skylib::Package_Reference_Value_t;
    using Package_Schedule_t        = skylib::Package_Schedule_t;
    using Package_Target_t          = skylib::Package_Target_t;
    using Package_Topic_Value_t     = skylib::Package_Topic_Value_t;
    using Package_Value_t           = skylib::Package_Value_t;
    using Perk_t                    = skylib::Perk_t;
    using Player_t                  = skylib::Player_t;
    using Quest_t                   = skylib::Quest_t;
    using Raw_Form_ID_t             = skylib::Raw_Form_ID_t;
    using Reference_t               = skylib::Reference_t;
    using Reference_Handle_t        = skylib::Reference_Handle_t;
    using Spell_t                   = skylib::Spell_t;
    using Static_t                  = skylib::Static_t;
    using UI_t                      = skylib::UI_t;
    using Weapon_t                  = skylib::Weapon_t;
    using Worldspace_t              = skylib::Worldspace_t;

    namespace V {

        using Type_e                = skylib::Virtual::Type_e;

        using Arguments_i           = skylib::Virtual::Arguments_i;
        using Arguments_t           = skylib::Virtual::Arguments_t;
        using Array_t               = skylib::Virtual::Array_t;
        using Callback_i            = skylib::Virtual::Callback_i;
        using Callback_t            = skylib::Virtual::Callback_t;
        using Class_t               = skylib::Virtual::Class_t;
        using Handle_Policy_t       = skylib::Virtual::Handle_Policy_t;
        using Machine_t             = skylib::Virtual::Machine_t;
        using Object_t              = skylib::Virtual::Object_t;
        using Object_Policy_t       = skylib::Virtual::Object_Policy_t;
        using Stack_ID_t            = skylib::Virtual::Stack_ID_t;
        using Utility_t             = skylib::Virtual::Utility_t;
        using Variable_t            = skylib::Virtual::Variable_t;

        template <typename T>
        using Variable_tt           = skylib::Virtual::Variable_tt<T>;

    }

}

namespace doticu_mcmlib {}
namespace mcmlib = doticu_mcmlib;
