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

    using u8                            = skylib::u8;
    using u16                           = skylib::u16;
    using u32                           = skylib::u32;
    using u64                           = skylib::u64;
    using s8                            = skylib::s8;
    using s16                           = skylib::s16;
    using s32                           = skylib::s32;
    using s64                           = skylib::s64;

    using Bool_t                        = skylib::Bool_t;
    using Int_t                         = skylib::Int_t;
    using Float_t                       = skylib::Float_t;
    using Double_t                      = skylib::Double_t;
    using String_t                      = skylib::String_t;
    using CString_t                     = skylib::CString_t;

    using Word_t                        = skylib::Word_t;

    template <typename T>
    using none                          = skylib::none<T>;
    template <typename T>
    using maybe                         = skylib::maybe<T>;
    template <typename T>
    using some                          = skylib::some<T>;
    template <typename T>
    using none_numeric                  = skylib::none_numeric<T>;
    template <typename T>
    using maybe_numeric                 = skylib::maybe_numeric<T>;
    template <typename T>
    using some_numeric                  = skylib::some_numeric<T>;
    template <typename T>
    using none_enum                     = skylib::none_enum<T>;
    template <typename T>
    using maybe_enum                    = skylib::maybe_enum<T>;
    template <typename T>
    using some_enum                     = skylib::some_enum<T>;
    template <typename T>
    using unique                        = skylib::unique<T>;

    template <typename T>
    using Range_t                       = skylib::Range_t<T>;
    template <typename T>
    using Vector_t                      = skylib::Vector_t<T>;

    template <typename ...Ts>
    using Callback_i                    = skylib::Callback_i<Ts...>;
    template <typename Return_t, typename ...Ts>
    using Functor_i                     = skylib::Functor_i<Return_t, Ts...>;

    template <typename T>
    using Enum_t                        = skylib::Enum_t<T>;
    template <typename T>
    using Enum_Type_t                   = skylib::Enum_Type_t<T>;
    template <typename T>
    using Enum_Type_Data_t              = skylib::Enum_Type_Data_t<T>;
    template <typename T>
    using Numeric_t                     = skylib::Numeric_t<T>;
    template <typename T>
    using Numeric_Data_t                = skylib::Numeric_Data_t<T>;
    template <typename T>
    using Version_t                     = skylib::Version_t<T>;

    using Form_Type_e                   = skylib::Form_Type_e;
    using Operator_e                    = skylib::Operator_e;
    using Package_Flags_e               = skylib::Package_Flags_e;
    using Package_Interrupt_Flags_e     = skylib::Package_Interrupt_Flags_e;
    using Relation_e                    = skylib::Relation_e;
    using Script_Type_e                 = skylib::Script_Type_e;
    using Vitality_e                    = skylib::Vitality_e;

    using Active_Magic_Effect_t         = skylib::Active_Magic_Effect_t;
    using Actor_t                       = skylib::Actor_t;
    using Actor_Base_t                  = skylib::Actor_Base_t;
    using Alias_Base_t                  = skylib::Alias_Base_t;
    using Alias_ID_t                    = skylib::Alias_ID_t;
    using Alias_Reference_t             = skylib::Alias_Reference_t;
    using Alpha_t                       = skylib::Alpha_t;
    using Ammo_t                        = skylib::Ammo_t;
    using Armor_t                       = skylib::Armor_t;
    using Book_t                        = skylib::Book_t;
    using Bound_Object_t                = skylib::Bound_Object_t;
    using Cell_t                        = skylib::Cell_t;
    using Character_t                   = skylib::Character_t;
    using Color_t                       = skylib::Color_t;
    using Combat_Style_t                = skylib::Combat_Style_t;
    using Container_t                   = skylib::Container_t;
    using Container_Entry_Count_t       = skylib::Container_Entry_Count_t;
    using Dialogue_Branch_t             = skylib::Dialogue_Branch_t;
    using Dialogue_Topic_t              = skylib::Dialogue_Topic_t;
    using Effect_Shader_t               = skylib::Effect_Shader_t;
    using Extra_List_t                  = skylib::Extra_List_t;
    using Faction_t                     = skylib::Faction_t;
    using Faction_And_Rank_t            = skylib::Faction_And_Rank_t;
    using Form_t                        = skylib::Form_t;
    using Form_ID_t                     = skylib::Form_ID_t;
    using Form_List_t                   = skylib::Form_List_t;
    using Furniture_t                   = skylib::Furniture_t;
    using Game_t                        = skylib::Game_t;
    using Global_t                      = skylib::Global_t;
    using Ingredient_t                  = skylib::Ingredient_t;
    using Keyword_t                     = skylib::Keyword_t;
    using Leveled_Actor_Base_t          = skylib::Leveled_Actor_Base_t;
    using Leveled_Item_t                = skylib::Leveled_Item_t;
    using Location_t                    = skylib::Location_t;
    using Magic_Effect_t                = skylib::Magic_Effect_t;
    using Magic_Target_t                = skylib::Magic_Target_t;
    using Misc_t                        = skylib::Misc_t;
    using Mod_t                         = skylib::Mod_t;
    using Outfit_t                      = skylib::Outfit_t;
    using Package_t                     = skylib::Package_t;
    using Package_Data_t                = skylib::Package_Data_t;
    using Package_Location_t            = skylib::Package_Location_t;
    using Package_Schedule_t            = skylib::Package_Schedule_t;
    using Package_Target_t              = skylib::Package_Target_t;
    using Package_Value_t               = skylib::Package_Value_t;
    using Package_Value_Bool_t          = skylib::Package_Value_Bool_t;
    using Package_Value_Float_t         = skylib::Package_Value_Float_t;
    using Package_Value_Int_t           = skylib::Package_Value_Int_t;
    using Package_Value_Location_t      = skylib::Package_Value_Location_t;
    using Package_Value_Reference_t     = skylib::Package_Value_Reference_t;
    using Package_Value_Target_t        = skylib::Package_Value_Target_t;
    using Package_Value_Topic_t         = skylib::Package_Value_Topic_t;
    using Perk_t                        = skylib::Perk_t;
    using Player_t                      = skylib::Player_t;
    using Potion_t                      = skylib::Potion_t;
    using Quest_t                       = skylib::Quest_t;
    using Raw_Form_ID_t                 = skylib::Raw_Form_ID_t;
    using Reference_t                   = skylib::Reference_t;
    using Reference_Container_t         = skylib::Reference_Container_t;
    using Reference_Container_Entry_t   = skylib::Reference_Container_Entry_t;
    using Reference_Handle_t            = skylib::Reference_Handle_t;
    using Script_t                      = skylib::Script_t;
    using Scroll_t                      = skylib::Scroll_t;
    using SKSE_Message_t                = skylib::SKSE_Message_t;
    using SKSE_Plugin_t                 = skylib::SKSE_Plugin_t;
    using Spell_t                       = skylib::Spell_t;
    using Static_t                      = skylib::Static_t;
    using UI_t                          = skylib::UI_t;
    using Voice_Type_t                  = skylib::Voice_Type_t;
    using Weapon_t                      = skylib::Weapon_t;
    using Worldspace_t                  = skylib::Worldspace_t;

    namespace V {

        using Type_e                    = skylib::Virtual::Type_e;

        using Arguments_i               = skylib::Virtual::Arguments_i;
        using Arguments_t               = skylib::Virtual::Arguments_t;
        using Array_t                   = skylib::Virtual::Array_t;
        using Callback_i                = skylib::Virtual::Callback_i;
        using Callback_t                = skylib::Virtual::Callback_t;
        using Class_t                   = skylib::Virtual::Class_t;
        using Debug_t                   = skylib::Virtual::Debug_t;
        using Handle_Policy_t           = skylib::Virtual::Handle_Policy_t;
        using Latent_ID_t               = skylib::Virtual::Latent_ID_t;
        using Machine_t                 = skylib::Virtual::Machine_t;
        using Object_t                  = skylib::Virtual::Object_t;
        using Object_Policy_t           = skylib::Virtual::Object_Policy_t;
        using Stack_ID_t                = skylib::Virtual::Stack_ID_t;
        using Utility_t                 = skylib::Virtual::Utility_t;
        using Variable_t                = skylib::Virtual::Variable_t;

        template <typename T>
        using Variable_tt               = skylib::Virtual::Variable_tt<T>;

    }

}

namespace doticu_mcmlib {}
namespace mcmlib = doticu_mcmlib;

#define NPCP_PRINT_HEAD         \
(                               \
    std::string("NPC Party: ")  \
)
