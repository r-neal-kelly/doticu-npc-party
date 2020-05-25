/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "xdata.h"

// see GameBSExtraData.h
const char *arr_str_xdata_types[180]{
    "kExtraData_None",
    "kExtraData_Havok",
    "kExtraData_Cell3D",
    "kExtraData_CellWaterType",
    "kExtraData_RegionList",
    "kExtraData_SeenData",
    "kExtraData_EditorID",
    "kExtraData_CellMusicType",
    "kExtraData_CellSkyRegion",
    "kExtraData_ProcessMiddleLow",
    "kExtraData_DetachTime",
    "kExtraData_PersistentCell",
    NULL,
    "kExtraData_Action",
    "kExtraData_StartingPosition",
    NULL,
    "kExtraData_AnimGraphManager",
    NULL,
    "kExtraData_UsedMarkers",
    "kExtraData_DistantData",
    "kExtraData_RagDollData",
    "kExtraData_ContainerChanges",
    "kExtraData_Worn",
    "kExtraData_WornLeft",
    "kExtraData_PackageStartLocation",
    "kExtraData_Package",
    "kExtraData_TresPassPackage",
    "kExtraData_RunOncePacks",
    "kExtraData_ReferenceHandle",
    "kExtraData_Follower",
    "kExtraData_LevCreaModifier",
    "kExtraData_Ghost",
    "kExtraData_OriginalReference",
    "kExtraData_Ownership",
    "kExtraData_Global",
    "kExtraData_Rank",
    "kExtraData_Count",
    "kExtraData_Health",
    NULL,
    "kExtraData_TimeLeft",
    "kExtraData_Charge",
    "kExtraData_Light",
    "kExtraData_Lock",
    "kExtraData_Teleport",
    "kExtraData_MapMarker",
    "kExtraData_LeveledCreature",
    "kExtraData_LeveledItem",
    "kExtraData_Scale",
    "kExtraData_Seed",
    "kExtraData_MagicCaster",
    NULL,
    NULL,
    "kExtraData_PlayerCrimeList",
    NULL,
    "kExtraData_EnableStateParent",
    "kExtraData_EnableStateChildren",
    "kExtraData_ItemDropper",
    "kExtraData_DroppedItemList",
    "kExtraData_RandomTeleportMarker",
    NULL,
    "kExtraData_SavedHavokData",
    "kExtraData_CannotWear",
    "kExtraData_Poison",
    NULL,
    "kExtraData_LastFinishedSequence",
    "kExtraData_SavedAnimation",
    "kExtraData_NorthRotation",
    "kExtraData_SpawnContainer",
    "kExtraData_FriendHits",
    "kExtraData_HeadingTarget",
    NULL,
    "kExtraData_RefractionProperty",
    "kExtraData_StartingWorldOrCell",
    "kExtraData_Hotkey",
    NULL,
    "kExtraData_EditiorRefMoveData",
    "kExtraData_InfoGeneralTopic",
    "kExtraData_HasNoRumors",
    "kExtraData_Sound",
    "kExtraData_TerminalState",
    "kExtraData_LinkedRef",
    "kExtraData_LinkedRefChildren",
    "kExtraData_ActivateRef",
    "kExtraData_ActivateRefChildren",
    "kExtraData_CanTalkToPlayer",
    "kExtraData_ObjectHealth",
    "kExtraData_CellImageSpace",
    "kExtraData_NavMeshPortal",
    "kExtraData_ModelSwap",
    "kExtraData_Radius",
    NULL,
    "kExtraData_FactionChanges",
    "kExtraData_DismemberedLimbs",
    "kExtraData_ActorCause",
    "kExtraData_MultiBound",
    "kExtraData_MultiBoundData",
    "kExtraData_MultiBoundRef",
    "kExtraData_ReflectedRefs",
    "kExtraData_ReflectorRefs",
    "kExtraData_EmittanceSource",
    "kExtraData_RadioData",
    "kExtraData_CombatStyle",
    NULL,
    "kExtraData_Primitive",
    "kExtraData_OpenCloseActivateRef",
    "kExtraData_AnimNoteReceiver",
    "kExtraData_Ammo",
    "kExtraData_PatrolRefData",
    "kExtraData_PackageData",
    "kExtraData_OcclusionShape",
    "kExtraData_CollisionData",
    "kExtraData_SayTopicInfoOnceADay",
    "kExtraData_EncounterZone",
    "kExtraData_SayTopicInfo",
    "kExtraData_OcclusionPlaneRefData",
    "kExtraData_PortalRefData",
    "kExtraData_Portal",
    "kExtraData_Room",
    "kExtraData_HealthPerc",
    "kExtraData_RoomRefData",
    "kExtraData_GuardedRefData",
    "kExtraData_CreatureAwakeSound",
    NULL,
    "kExtraData_Horse",
    "kExtraData_IgnoredBySandbox",
    "kExtraData_CellAcousticSpace",
    "kExtraData_ReservedMarkers",
    "kExtraData_WeaponIdleSound",
    "kExtraData_WaterLightRefs",
    "kExtraData_LitWaterRefs",
    "kExtraData_WeaponAttackSound",
    "kExtraData_ActivateLoopSound",
    "kExtraData_PatrolRefInUseData",
    "kExtraData_AshPileRef",
    NULL,
    "kExtraData_FollowerSwimBreadcrumbs",
    "kExtraData_AliasInstanceArray",
    "kExtraData_Location",
    NULL,
    "kExtraData_LocationRefType",
    "kExtraData_PromotedRef",
    NULL,
    "kExtraData_OutfitItem",
    NULL,
    "kExtraData_LeveledItemBase",
    "kExtraData_LightData",
    "kExtraData_SceneData",
    "kExtraData_BadPosition",
    "kExtraData_HeadTrackingWeight",
    "kExtraData_FromAlias",
    "kExtraData_ShouldWear",
    "kExtraData_FavorCost",
    "kExtraData_AttachedArrows3D",
    "kExtraData_TextDisplayData",
    "kExtraData_AlphaCutoff",
    "kExtraData_Enchantment",
    "kExtraData_Soul",
    "kExtraData_ForcedTarget",
    NULL,
    "kExtraData_UniqueID",
    "kExtraData_Flags",
    "kExtraData_RefrPath",
    "kExtraData_DecalGroup",
    "kExtraData_LockList",
    "kExtraData_ForcedLandingMarker",
    "kExtraData_LargeRefOwnerCells",
    "kExtraData_CellWaterEnvMap",
    "kExtraData_CellGrassData",
    "kExtraData_TeleportName",
    "kExtraData_Interaction",
    "kExtraData_WaterData",
    "kExtraData_WaterCurrentZoneData",
    "kExtraData_AttachRef",
    "kExtraData_AttachRefChildren",
    "kExtraData_GroupConstraint",
    "kExtraData_ScriptedAnimDependence",
    "kExtraData_CachedScale",
    "kExtraData_RaceData",
    "kExtraData_GIDBuffer",
    "kExtraData_MissingRefIDs"
};

namespace doticu_npcp { namespace XData {

    ExtraCount *Create_Count(UInt32 count) {
        ExtraCount *xdata = ExtraCount::Create();
        ASSERT(xdata);

        xdata->count = count;

        return xdata;
    }

    ExtraOwnership *Create_Ownership(TESForm *owner) {
        ExtraOwnership *xdata = (ExtraOwnership *)XData_t::Create(sizeof(ExtraOwnership), s_ExtraOwnershipVtbl.GetUIntPtr());
        ASSERT(xdata);

        xdata->owner = owner;

        return xdata;
    }

    ExtraReferenceHandle *Create_Reference_Handle(TESObjectREFR *obj) {
        ExtraReferenceHandle *xdata = ExtraReferenceHandle::Create();
        ASSERT(xdata);

        xdata->handle = obj->CreateRefHandle();

        return xdata;
    }

    void Destroy(XData_t *xdata) {
        if (!xdata) {
            return;
        }

        // this apparently does delete the xdata the correct way.
        xdata->~BSExtraData();
    }

    ExtraCount *Copy_Count(ExtraCount *xdata, BSReadWriteLock *xlist_lock) {
        /*if (!xdata || !xlist_lock) {
            return NULL;
        }*/

        ExtraCount *xdata_new = ExtraCount::Create();
        ASSERT(xdata_new);

        //BSReadLocker locker(xlist_lock);
        xdata_new->count = xdata->count;

        return xdata_new;
    }

    ExtraHealth *Copy_Health(ExtraHealth *xdata, BSReadWriteLock *xlist_lock) {
        ExtraHealth *xdata_new = ExtraHealth::Create();
        ASSERT(xdata_new);

        //BSReadLocker locker(xlist_lock);
        xdata_new->health = xdata->health;

        return xdata_new;
    }

    ExtraEnchantment *Copy_Enchantment(ExtraEnchantment *xdata, BSReadWriteLock *xlist_lock) {
        ExtraEnchantment *xdata_new = ExtraEnchantment::Create();
        ASSERT(xdata_new);

        //BSReadLocker locker(xlist_lock);
        xdata_new->enchant = xdata->enchant; // do we need to copy this? probably not.
        xdata_new->maxCharge = xdata->maxCharge;
        xdata_new->unk0E = xdata->unk0E;

        return xdata_new;
    }

    ExtraCharge *Copy_Charge(ExtraCharge *xdata, BSReadWriteLock *xlist_lock) {
        ExtraCharge *xdata_new = ExtraCharge::Create();
        ASSERT(xdata_new);

        //BSReadLocker locker(xlist_lock);
        xdata_new->charge = xdata->charge;

        return xdata_new;
    }

    ExtraTextDisplayData *Copy_Text_Display(ExtraTextDisplayData *xdata, BSReadWriteLock *xlist_lock) {
        ExtraTextDisplayData *xdata_new = ExtraTextDisplayData::Create();
        ASSERT(xdata_new);

        //BSReadLocker locker(xlist_lock);
        xdata_new->name = xdata->name;
        xdata_new->message = xdata->message;
        xdata_new->owner = xdata->owner;
        xdata_new->unk14 = xdata->unk14;
        xdata_new->extraHealthValue = xdata->extraHealthValue;
        xdata_new->unk30 = xdata->unk30;

        return xdata_new;
    }

    bool Is_Same_Health(ExtraHealth *xdata_a, ExtraHealth *xdata_b, BSReadWriteLock *xlist_lock_a, BSReadWriteLock *xlist_lock_b) {
        if (!xdata_a && !xdata_b) {
            return true;
        } else if (!xdata_a || !xdata_b) {
            return false;
        }

        //BSReadLocker locker_a(xlist_lock_a);
        //BSReadLocker locker_b(xlist_lock_b);
        return xdata_a->health == xdata_b->health;
    }

    bool Is_Same_Enchantment(ExtraEnchantment *xdata_a, ExtraEnchantment *xdata_b, BSReadWriteLock *xlist_lock_a, BSReadWriteLock *xlist_lock_b) {
        if (!xdata_a && !xdata_b) {
            return true;
        } else if (!xdata_a || !xdata_b) {
            return false;
        }

        //BSReadLocker locker_a(xlist_lock_a);
        //BSReadLocker locker_b(xlist_lock_b);
        return xdata_a->enchant == xdata_b->enchant &&
            xdata_a->maxCharge == xdata_b->maxCharge &&
            xdata_a->unk0E == xdata_b->unk0E; // is this one necessary?
    }

    bool Is_Same_Charge(ExtraCharge *xdata_a, ExtraCharge *xdata_b, BSReadWriteLock *xlist_lock_a, BSReadWriteLock *xlist_lock_b) {
        if (!xdata_a && !xdata_b) {
            return true;
        } else if (!xdata_a || !xdata_b) {
            return false;
        }

        //BSReadLocker locker_a(xlist_lock_a);
        //BSReadLocker locker_b(xlist_lock_b);
        return xdata_a->charge == xdata_b->charge;
    }

    const char *Get_Type_String(XData_t *xdata) {
        if (xdata) {
            const char *str = arr_str_xdata_types[xdata->GetType()];
            return str ? str : "UNKNOWN_TYPE";
        } else {
            return "INVALID_EXTRA_DATA";
        }
    }

}}
