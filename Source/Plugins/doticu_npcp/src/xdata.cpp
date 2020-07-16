/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "offsets.h"
#include "utils.h"
#include "xdata.h"

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

    const RelocPtr<uintptr_t> xinteraction_vtbl(0x0152F540);
    const RelocPtr<uintptr_t> interaction_vtbl(0x0165EC98);

    ExtraCount *Create_Count(UInt32 count) {
        ExtraCount *xdata = ExtraCount::Create();
        NPCP_ASSERT(xdata);

        xdata->count = count;

        return xdata;
    }

    // not sure if all of this should belong in one place, but it may help with clarity?
    void Create_Interaction(TESObjectREFR* interactee, TESObjectREFR* interactor, bool is_synced)
    {
        if (interactee && interactor) {
            Interaction* interaction = (Interaction*)Heap_Allocate(sizeof(Interaction));
            memset(interaction, 0, sizeof(Interaction));
            ((uintptr_t*)interaction)[0] = interaction_vtbl.GetUIntPtr();
            NPCP_ASSERT(interaction);

            interaction->interactee_handle = interactee->CreateRefHandle();
            interaction->IncRef();

            interaction->interactor_handle = interactor->CreateRefHandle();
            interaction->IncRef();

            interaction->is_synced = is_synced;

            Destroy_Interaction(interactee);
            Destroy_Interaction(interactor);

            XInteraction* xinteraction_a = (XInteraction*)XData_t::Create(sizeof(XInteraction), xinteraction_vtbl.GetUIntPtr());
            XInteraction* xinteraction_b = (XInteraction*)XData_t::Create(sizeof(XInteraction), xinteraction_vtbl.GetUIntPtr());
            NPCP_ASSERT(xinteraction_a && xinteraction_b);

            xinteraction_a->interaction = interaction;
            xinteraction_b->interaction = interaction;

            interactee->extraData.Add(kExtraData_Interaction, xinteraction_a);
            interactor->extraData.Add(kExtraData_Interaction, xinteraction_b);
        }
    }

    void Destroy_Interaction(TESObjectREFR* obj_a)
    {
        if (obj_a) {
            XInteraction* xinteraction_a = (XInteraction*)obj_a->extraData.GetByType(kExtraData_Interaction);
            if (xinteraction_a) {
                Interaction* interaction = xinteraction_a->interaction;
                if (interaction) {
                    TESObjectREFR* obj_b = nullptr;
                    NiPointer<TESObjectREFR> interactee = nullptr;
                    NiPointer<TESObjectREFR> interactor = nullptr;
                    LookupREFRByHandle(interaction->interactee_handle, interactee);
                    LookupREFRByHandle(interaction->interactor_handle, interactor);
                    if (interactee && interactee != obj_a) {
                        obj_b = interactee;
                    } else if (interactor && interactor != obj_a) {
                        obj_b = interactor;
                    }
                    if (obj_b) {
                        XInteraction* xinteraction_b = (XInteraction*)obj_b->extraData.GetByType(kExtraData_Interaction);
                        if (xinteraction_b) {
                            obj_b->extraData.Remove(kExtraData_Interaction, xinteraction_b);
                            ((XData_t*)xinteraction_b)->~BSExtraData();
                        }
                        interaction->DecRef();
                    }
                    interaction->DecRef();
                }
                obj_a->extraData.Remove(kExtraData_Interaction, xinteraction_a);
                ((XData_t*)xinteraction_a)->~BSExtraData();
            }
        }
    }

    ExtraOwnership *Create_Ownership(TESForm *owner) {
        ExtraOwnership *xdata = (ExtraOwnership *)XData_t::Create(sizeof(ExtraOwnership), s_ExtraOwnershipVtbl.GetUIntPtr());
        NPCP_ASSERT(xdata);

        xdata->owner = owner;

        return xdata;
    }

    ExtraReferenceHandle *Create_Reference_Handle(TESObjectREFR *obj) {
        ExtraReferenceHandle *xdata = ExtraReferenceHandle::Create();
        NPCP_ASSERT(xdata);

        xdata->handle = obj->CreateRefHandle();

        return xdata;
    }

    ExtraFactionChanges* Create_Faction_Changes(Actor_t* actor)
    {
        if (actor) {
            ExtraFactionChanges* xfaction_changes = static_cast<ExtraFactionChanges*>(XData_t::Create(
                sizeof(ExtraFactionChanges),
                Offsets::Extra::FACTION_CHANGES_V_TABLE + RelocationManager::s_baseAddr
            ));
            if (xfaction_changes) {
                xfaction_changes->factions.Grow(1);
                xfaction_changes->unk28 = reinterpret_cast<UInt64>(static_cast<Actor_Base_t*>(actor->baseForm)->faction);
                xfaction_changes->unk30 = 0;
                return xfaction_changes;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    ExtraCanTalkToPlayer* Create_Can_Talk_To_Player(Bool_t can_talk)
    {
        ExtraCanTalkToPlayer* xcan_talk_to_player = static_cast<ExtraCanTalkToPlayer*>(XData_t::Create(
            sizeof(ExtraCanTalkToPlayer),
            Offsets::Extra::CAN_TALK_TO_PLAYER_V_TABLE + RelocationManager::s_baseAddr
        ));
        if (xcan_talk_to_player) {
            xcan_talk_to_player->can_talk = can_talk;
            return xcan_talk_to_player;
        } else {
            return nullptr;
        }
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
        NPCP_ASSERT(xdata_new);

        //BSReadLocker locker(xlist_lock);
        xdata_new->count = xdata->count;

        return xdata_new;
    }

    ExtraHealth *Copy_Health(ExtraHealth *xdata, BSReadWriteLock *xlist_lock) {
        ExtraHealth *xdata_new = ExtraHealth::Create();
        NPCP_ASSERT(xdata_new);

        //BSReadLocker locker(xlist_lock);
        xdata_new->health = xdata->health;

        return xdata_new;
    }

    ExtraEnchantment *Copy_Enchantment(ExtraEnchantment *xdata, BSReadWriteLock *xlist_lock) {
        ExtraEnchantment *xdata_new = ExtraEnchantment::Create();
        NPCP_ASSERT(xdata_new);

        //BSReadLocker locker(xlist_lock);
        xdata_new->enchant = xdata->enchant; // do we need to copy this? probably not.
        xdata_new->maxCharge = xdata->maxCharge;
        xdata_new->unk0E = xdata->unk0E;

        return xdata_new;
    }

    ExtraCharge *Copy_Charge(ExtraCharge *xdata, BSReadWriteLock *xlist_lock) {
        ExtraCharge *xdata_new = ExtraCharge::Create();
        NPCP_ASSERT(xdata_new);

        //BSReadLocker locker(xlist_lock);
        xdata_new->charge = xdata->charge;

        return xdata_new;
    }

    ExtraTextDisplayData *Copy_Text_Display(ExtraTextDisplayData *xdata, BSReadWriteLock *xlist_lock) {
        ExtraTextDisplayData *xdata_new = ExtraTextDisplayData::Create();
        NPCP_ASSERT(xdata_new);

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
