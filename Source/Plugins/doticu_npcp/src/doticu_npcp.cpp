/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_npcp.h"

namespace doticu_npcp {

    bool Register_Functions(VMClassRegistry *registry) {
        // actor.cpp
        registry->RegisterFunction(
            new NativeFunction2 <Actor, void, BGSOutfit *, bool>(
                "SetOutfit",
                "Actor",
                doticu_npcp::Actor_Set_Outfit,
                registry)
        );

        // alias.cpp

        // aliases.cpp
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>, UInt32, UInt32>(
                "Aliases_Slice",
                "doticu_npcp",
                doticu_npcp::Aliases_Slice,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>, BSFixedString>(
                "Aliases_Sort",
                "doticu_npcp",
                doticu_npcp::Aliases_Sort,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, VMArray<BGSBaseAlias *>, VMArray<BSFixedString>, VMArray<SInt32>>(
                "Aliases_Filter",
                "doticu_npcp",
                doticu_npcp::Aliases_Filter,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, UInt32, UInt32, BSFixedString, BSFixedString>(
                "Aliases_Filter_Flag",
                "doticu_npcp",
                doticu_npcp::Aliases_Filter_Flag,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<BSFixedString>, VMArray<BGSBaseAlias *>>(
                "Aliases_Get_Race_Names",
                "doticu_npcp",
                doticu_npcp::Aliases_Get_Race_Names,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<BSFixedString>, VMArray<BGSBaseAlias *>>(
                "Aliases_Get_Initial_Letters",
                "doticu_npcp",
                doticu_npcp::Aliases_Get_Initial_Letters,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<BGSBaseAlias *>, TESQuest *>(
                "Aliases_Get_Used",
                "doticu_npcp",
                doticu_npcp::Aliases_Get_Used,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, VMResultArray<SInt32>, TESQuest *>(
                "Aliases_Get_Free_IDs",
                "doticu_npcp",
                doticu_npcp::Aliases_Get_Free_IDs,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, UInt32, TESQuest *>(
                "Aliases_Get_Used_Count",
                "doticu_npcp",
                doticu_npcp::Aliases_Get_Used_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, UInt32, TESQuest *>(
                "Aliases_Get_Free_Count",
                "doticu_npcp",
                doticu_npcp::Aliases_Get_Free_Count,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, UInt32, TESQuest *>(
                "Aliases_Count_Mannequins",
                "doticu_npcp",
                doticu_npcp::Aliases_Count_Mannequins,
                registry)
        );

        // forms.cpp
        registry->RegisterFunction(
            new NativeFunction3 <StaticFunctionTag, VMResultArray<TESForm *>, VMArray<TESForm *>, UInt32, UInt32>(
                "Forms_Slice",
                "doticu_npcp",
                doticu_npcp::Forms_Slice,
                registry)
        );

        // outfit.cpp
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>(
                "Outfit_Add_Item",
                "doticu_npcp",
                doticu_npcp::Outfit_Add_Item,
                registry)
        );
        registry->RegisterFunction(
            new NativeFunction2 <StaticFunctionTag, void, BGSOutfit *, TESForm *>(
                "Outfit_Remove_Item",
                "doticu_npcp",
                doticu_npcp::Outfit_Remove_Item,
                registry)
        );

        // utils.cpp
        registry->RegisterFunction(
            new NativeFunction1 <StaticFunctionTag, void, BSFixedString>(
                "Print",
                "doticu_npcp",
                doticu_npcp::Print,
                registry)
        );

        return true;
    }

}
