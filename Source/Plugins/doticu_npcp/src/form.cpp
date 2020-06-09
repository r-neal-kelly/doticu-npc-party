/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameRTTI.h"

#include "form.h"

const char *arr_str_form_types[143] = {
    "kFormType_None",
    "kFormType_TES4",
    "kFormType_Group",
    "kFormType_GMST",
    "kFormType_Keyword",
    "kFormType_LocationRef",
    "kFormType_Action",
    "kFormType_TextureSet",
    "kFormType_MenuIcon",
    "kFormType_Global",
    "kFormType_Class",
    "kFormType_Faction",
    "kFormType_HeadPart",
    "kFormType_Eyes",
    "kFormType_Race",
    "kFormType_Sound",
    "kFormType_AcousticSpace",
    "kFormType_Skill",
    "kFormType_EffectSetting",
    "kFormType_Script",
    "kFormType_LandTexture",
    "kFormType_Enchantment",
    "kFormType_Spell",
    "kFormType_ScrollItem",
    "kFormType_Activator",
    "kFormType_TalkingActivator",
    "kFormType_Armor",
    "kFormType_Book",
    "kFormType_Container",
    "kFormType_Door",
    "kFormType_Ingredient",
    "kFormType_Light",
    "kFormType_Misc",
    "kFormType_Apparatus",
    "kFormType_Static",
    "kFormType_StaticCollection",
    "kFormType_MovableStatic",
    "kFormType_Grass",
    "kFormType_Tree",
    "kFormType_Flora",
    "kFormType_Furniture",
    "kFormType_Weapon",
    "kFormType_Ammo",
    "kFormType_NPC",
    "kFormType_LeveledCharacter",
    "kFormType_Key",
    "kFormType_Potion",
    "kFormType_IdleMarker",
    "kFormType_Note",
    "kFormType_ConstructibleObject",
    "kFormType_Projectile",
    "kFormType_Hazard",
    "kFormType_SoulGem",
    "kFormType_LeveledItem",
    "kFormType_Weather",
    "kFormType_Climate",
    "kFormType_SPGD",
    "kFormType_ReferenceEffect",
    "kFormType_Region",
    "kFormType_NAVI",
    "kFormType_Cell",
    "kFormType_Reference",
    "kFormType_Character",
    "kFormType_Missile",
    "kFormType_Arrow",
    "kFormType_Grenade",
    "kFormType_BeamProj",
    "kFormType_FlameProj",
    "kFormType_ConeProj",
    "kFormType_BarrierProj",
    "kFormType_PHZD",
    "kFormType_WorldSpace",
    "kFormType_Land",
    "kFormType_NAVM",
    "kFormType_TLOD",
    "kFormType_Topic",
    "kFormType_TopicInfo",
    "kFormType_Quest",
    "kFormType_Idle",
    "kFormType_Package",
    "kFormType_CombatStyle",
    "kFormType_LoadScreen",
    "kFormType_LeveledSpell",
    "kFormType_ANIO",
    "kFormType_Water",
    "kFormType_EffectShader",
    "kFormType_TOFT",
    "kFormType_Explosion",
    "kFormType_Debris",
    "kFormType_ImageSpace",
    "kFormType_ImageSpaceMod",
    "kFormType_List",
    "kFormType_Perk",
    "kFormType_BodyPartData",
    "kFormType_AddonNode",
    "kFormType_ActorValueInfo",
    "kFormType_CameraShot",
    "kFormType_CameraPath",
    "kFormType_VoiceType",
    "kFormType_MaterialType",
    "kFormType_ImpactData",
    "kFormType_ImpactDataSet",
    "kFormType_ARMA",
    "kFormType_EncounterZone",
    "kFormType_Location",
    "kFormType_Message",
    "kFormType_Ragdoll",
    "kFormType_DOBJ",
    "kFormType_LightingTemplate",
    "kFormType_MusicType",
    "kFormType_Footstep",
    "kFormType_FootstepSet",
    "kFormType_StoryBranchNode",
    "kFormType_StoryQuestNode",
    "kFormType_StoryEventNode",
    "kFormType_DialogueBranch",
    "kFormType_MusicTrack",
    "kFormType_DLVW",
    "kFormType_WordOfPower",
    "kFormType_Shout",
    "kFormType_EquipSlot",
    "kFormType_Relationship",
    "kFormType_Scene",
    "kFormType_AssociationType",
    "kFormType_Outfit",
    "kFormType_Art",
    "kFormType_Material",
    "kFormType_MovementType",
    "kFormType_SoundDescriptor",
    "kFormType_DualCastData",
    "kFormType_SoundCategory",
    "kFormType_SoundOutput",
    "kFormType_CollisionLayer",
    "kFormType_ColorForm",
    "kFormType_ReverbParam",
    "kFormType_LensFlare",
    "kFormType_Unk88",
    "kFormType_VolumetricLighting",
    "kFormType_Unk8A",
    "kFormType_Alias",
    "kFormType_ReferenceAlias",
    "kFormType_LocationAlias",
    "kFormType_ActiveMagicEffect"
};

namespace doticu_npcp { namespace Form {

    const char *Get_Name(TESForm *ref_form) {
        TESFullName *full_name = DYNAMIC_CAST(ref_form, TESForm, TESFullName);
        if (!full_name || !full_name->name || !full_name->name.data) {
            return "";
        }

        return full_name->name.data;
    }

    const char *Get_Type_String(TESForm *ref_form) {
        if (ref_form) {
            return arr_str_form_types[ref_form->formType];
        } else {
            return "INVALID_FORM";
        }
    }

    bool Has_Keyword(TESForm *form, BGSKeyword *keyword) {
        if (!form || !keyword) {
            return false;
        }

        BGSKeywordForm *keywords = DYNAMIC_CAST(form, TESForm, BGSKeywordForm);
        if (!keywords) {
            return false;
        }

        return keywords->HasKeyword(keyword);
    }

}}

namespace doticu_npcp { namespace Form { namespace Exports {

    bool Register(VMClassRegistry *registry) {
        _MESSAGE("Added Form functions.");

        return true;
    }

}}}
