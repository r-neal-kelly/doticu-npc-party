/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/GameExtraData.h"
#include "skse64/GameForms.h"
#include "skse64/GameFormComponents.h"
#include "skse64/PapyrusNativeFunctions.h"
#include "skse64/PluginAPI.h"

namespace doticu_npcp {

    typedef uint8_t         u8;
    typedef uint16_t        u16;
    typedef uint32_t        u32;
    typedef uint64_t        u64;
    typedef int8_t          s8;
    typedef int16_t         s16;
    typedef int32_t         s32;
    typedef int64_t         s64;
    typedef int64_t         idx_t;

}

namespace doticu_npcp {

    typedef SInt32          Int_t;
    typedef BSFixedString   String_t;
    typedef float           Float_t;
    typedef bool            Bool_t;

    typedef UInt32          Form_Type_t;
    typedef UInt32          Reference_Handle_t;

    typedef TESForm         Form_t;
    typedef TESQuest        Quest_t;
    typedef TESObjectCELL   Cell_t;
    typedef TESObjectREFR   Reference_t;
    typedef TESObjectMISC   Misc_t;
    typedef TESFaction      Faction_t;

    typedef Actor           Actor_t;
    typedef TESNPC          Actor_Base_t;

    typedef Projectile      Projectile_t;
    typedef BGSProjectile   Projectile_Base_t;

    // a lot of credit for deciphering these classes goes to Ryan-rsm-McKenzie of CommonLibSSE as well as the SKSE team
    class Actor_Base_Data_t : public BaseFormComponent {
    public:
        enum Flags : UInt32 {
            FLAG_FEMALE = 1 << 0,
            FLAG_ESSENTIAL = 1 << 1,
            FLAG_FACE_PRESET = 1 << 2,
            FLAG_RESPAWNS = 1 << 3,
            FLAG_AUTO_STATS = 1 << 4,
            FLAG_UNIQUE = 1 << 5
            // ...
        };

        UInt32 flags; // 08

        bool Is_Unique()
        {
            return (flags & FLAG_UNIQUE) != 0;
        }
    };

    enum class Actor_Value_t : UInt32 {
        AGGRESSION = 0,
        CONFIDENCE,
        ENERGY,
        MORALITY,
        MOOD,
        ASSISTANCE,
        ONE_HANDED,
        TWO_HANDED,
        MARKSMAN,
        BLOCK,
        SMITHING,
        HEAVY_ARMOR,
        LIGHT_ARMOR,
        PICKPOCKET,
        LOCKPICKING,
        SNEAK,
        ALCHEMY,
        SPEECHCRAFT,
        ALTERATION,
        CONJURATION,
        DESTRUCTION,
        ILLUSION,
        RESTORATION,
        ENCHANTING,
        HEALTH,
        MAGICKA,
        STAMINA,
        HEAL_RATE,
        MAGICKA_RATE,
        STAMINA_RATE,
        SPEED_MULT,
        INVENTORY_WEIGHT,
        CARRY_WEIGHT,
        CRITICAL_CHANCE,
        MELEE_DAMAGE,
        UNARMED_DAMAGE,
        MASS,
        VOICE_POINTS,
        VOICE_RATE,
        DAMAGE_RESIST,
        POISON_RESIST,
        RESIST_FIRE,
        RESIST_SHOCK,
        RESIST_FROST,
        RESIST_MAGIC,
        RESIST_DISEASE,
        UNKNOWN_46,
        UNKNOWN_47,
        UNKNOWN_48,
        UNKNOWN_49,
        UNKNOWN_50,
        UNKNOWN_51,
        UNKNOWN_52,
        PARALYSIS,
        INVISIBILITY,
        NIGHT_EYE,
        DETECT_LIFE_RANGE,
        WATER_BREATHING,
        WATER_WALKING,
        UNKNOWN_59,
        FAME,
        INFAMY,
        JUMPING_BONUS,
        WARD_POWER,
        RIGHT_ITEM_CHARGE,
        ARMOR_PERKS,
        SHIELD_PERKS,
        WARD_DEFLECTION,
        // ...
        WAITING_FOR_PLAYER = 95,
        // ...
        INVALID = 164
    };

    enum class Actor_Modifier_t : UInt32 {
        PERMANENT = 0,
        TEMPORARY = 1,
        DAMAGE = 2,
        INVALID = 3
    };

    class Actor_Value_Owner_t {
    public:
        virtual ~Actor_Value_Owner_t(); // 00
        virtual float Get_Actor_Value(Actor_Value_t value_type); // 01
        virtual float Get_Permanent_Actor_Value(Actor_Value_t value_type); // 02
        virtual float Get_Base_Actor_Value(Actor_Value_t value_type); // 03 (doesn't get the base actor, but its own base)
        virtual void Set_Base_Actor_Value(Actor_Value_t value_type, float value); // 04 (doesn't set the base actor, but its own base)
        virtual void Mod_Actor_Value(Actor_Value_t value_type, float value); // 05
        virtual void Restore_Actor_Value(Actor_Modifier_t modifier_type, Actor_Value_t value_type, float value); // 06
        virtual void Set_Actor_Value(Actor_Value_t value_type, float value); // 07
        virtual void Is_Player_Owner(); // 08
        //void* _vtbl; // 00
    };
    STATIC_ASSERT(sizeof(Actor_Value_Owner_t) == 0x08);

    class Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_Alias
        };

        enum Flags : UInt32 {
            // ...
        };

        enum Fill_Types : UInt16 {
            CONDITION_FILL = 0,
            FORCED_FILL = 1
            // ...
        };

        virtual ~Alias_Base_t(); // 00
        virtual bool Load(TESFile* file); // 01
        virtual void Item(TESForm* form); // 02
        virtual String_t Type(); // 03

        // void* _vtbl; // 00
        String_t name; // 08
        Quest_t* quest; // 10
        UInt32 id; // 18
        UInt32 flags; // 1C
        UInt16 fill_type; // 20
        UInt16 pad_22; // 22
        UInt32 pad_24; // 24
    };
    STATIC_ASSERT(sizeof(Alias_Base_t) == 0x28);

    class Alias_Reference_t : public Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_ReferenceAlias
        };

        struct Forced_Fill {
            Reference_Handle_t ref_handle; // this never seems to be there...
        };
        STATIC_ASSERT(sizeof(Forced_Fill) == 0x4);

        union Fill_u {
            UInt64 padding[3];
            Forced_Fill forced;
        };
        STATIC_ASSERT(sizeof(Fill_u) == 0x18);

        virtual ~Alias_Reference_t(); // 00
        virtual bool Load(TESFile* file) override; // 01
        virtual void Item(TESForm* form) override; // 02
        virtual String_t Type() override; // 03

        Fill_u fill; // 28
        void* conditions; // 40
    };
    STATIC_ASSERT(sizeof(Alias_Reference_t) == 0x48);

    class Faction_Rank_t {
    public:
        Faction_t* faction;
        SInt8 rank;
        UInt8 pad[7];
    };
    STATIC_ASSERT(sizeof(Faction_Rank_t) == 0x10);

    class ExtraCanTalkToPlayer : public BSExtraData {
    public:
        virtual ~ExtraCanTalkToPlayer();

        Bool_t can_talk; // 10
        UInt8 pad_11; // 11
        UInt16 pad_12; // 12
        UInt32 pad_14; // 14
    };

}

namespace doticu_npcp {

    typedef BGSBaseAlias            Player_t;
    typedef TESQuest                Keys_t;
    typedef TESQuest                Consts_t;
    typedef TESQuest                Vars_t;

    typedef TESContainer            BContainer_t;
    typedef TESContainer::Entry**   BEntries_t;
    typedef TESContainer::Entry     BEntry_t;

    typedef ExtraContainerChanges   XContainer_t;
    typedef EntryDataList           XEntries_t;
    typedef InventoryEntryData      XEntry_t;
    typedef ExtendDataList          XLists_t;
    typedef BaseExtraList           XList_t;
    typedef BSExtraData             XData_t;
    typedef ExtraAliasInstanceArray XAliases_t;

    typedef tArray<Faction_Rank_t>  BFaction_Ranks_t;
    typedef Faction_Rank_t          BFaction_Rank_t;
    typedef ExtraFactionChanges     XFactions_t;
    typedef tArray<Faction_Rank_t>  XFaction_Ranks_t;
    typedef Faction_Rank_t          XFaction_Rank_t;

    typedef StaticFunctionTag       Selfless_t;

}

namespace doticu_npcp { namespace Papyrus {

    typedef VMClassRegistry         Registry_t;
    typedef IObjectHandlePolicy     Policy_t;
    typedef VMScriptInstance        Script_t;
    typedef UInt64                  Type_e;

    template <typename T> using Vector_t = VMResultArray<T>;
    typedef Vector_t<Int_t> Int_Vector_t;

}}
