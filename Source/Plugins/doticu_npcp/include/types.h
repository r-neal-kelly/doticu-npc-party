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
    typedef TESObjectSTAT   Static_t;
    typedef TESObjectWEAP   Weapon_t;
    typedef TESObjectARMO   Armor_t;
    typedef TESObjectCONT   Container_t;
    typedef BGSPerk         Perk_t;
    typedef TESEffectShader Effect_Shader_t;
    typedef TESLevCharacter Leveled_Actor_t;
    typedef BGSLocation     Location_t;
    typedef TESFaction      Faction_t;
    typedef BGSOutfit       Outfit_t;
    typedef BGSKeyword      Keyword_t;
    typedef EffectSetting   Magic_Effect_t;
    typedef SpellItem       Spell_t;

    typedef Actor           Actor_t;
    typedef TESNPC          Actor_Base_t;
    typedef Character       Character_t;
    typedef PlayerCharacter Player_Character_t;

    typedef Projectile      Projectile_t;
    typedef BGSProjectile   Projectile_Base_t;

    typedef BGSListForm     Formlist_t;

    typedef TESTopicInfo    Topic_Info_t;

    typedef TESContainer            BContainer_t;
    typedef TESContainer::Entry**   BEntries_t;
    typedef TESContainer::Entry     BEntry_t;

    //typedef ExtraContainerChanges   XContainer_t;
    //typedef EntryDataList           XEntries_t;
    //typedef InventoryEntryData      XEntry_t;
    typedef ExtendDataList          XLists_t;
    typedef BaseExtraList           XList_t;
    typedef BSExtraData             XData_t;
    typedef ExtraAliasInstanceArray XAliases_t;

    template <typename ...Arguments>
    struct Callback_t {
        virtual ~Callback_t() = default;
        virtual void operator()(Arguments...) = 0;
    };

    using Int_Callback_t = Callback_t<Int_t>;

    class Reference_t2 {
    public:
    };

    // a lot of credit for deciphering these classes goes to Ryan-rsm-McKenzie of CommonLibSSE as well as the SKSE team
    class Actor_Base_Data_t : public BaseFormComponent {
    public:
        enum Flags : UInt32 {
            IS_FEMALE = 0,
            IS_ESSENTIAL = 1,
            FACE_PRESET = 2,
            RESPAWNS = 3,
            AUTO_STATS = 4,
            IS_UNIQUE = 5,
            // ...
            IS_PROTECTED = 11,
            // ...
            IS_GHOST = 29,
            // ...
        };

        UInt32 flags; // 08

        Bool_t Is_Unique();
        Bool_t Is_Ghost();
        Bool_t Is_Protected();
        Bool_t Is_Essential();

        void Protect();
        void Unprotect();
        void Essentialize();
        void Unessentialize();
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

    class Actor_State_t : public IMovementState {
    public:
        virtual ~Actor_State_t();

        class State_t {
        public:
            Bool_t moving_back : 1;
            Bool_t moving_forward : 1;
            Bool_t moving_right : 1;
            Bool_t moving_left : 1;
            Bool_t unk_0_4 : 1;
            Bool_t unk_0_5 : 1;
            Bool_t walking : 1;
            Bool_t running : 1;

            Bool_t sprinting : 1;
            Bool_t sneaking : 1;
            Bool_t swimming : 1;

            Bool_t wip_2;
            Bool_t wip_3;
            Bool_t wip_4;
            Bool_t wip_5;
            Bool_t wip_6;
            Bool_t wip_7;
        };

        void Stop_Movement();

        State_t state;
    };
    STATIC_ASSERT(sizeof(Actor_State_t) == 0x10);

    class Actor_Equipper_t {
    public:
        static Actor_Equipper_t* Self();
    public:
        void Equip_Item(Actor_t* actor,
                        Form_t* form,
                        XList_t* xlist,
                        UInt32 count,
                        BGSEquipSlot* slot,
                        Bool_t do_queue,
                        Bool_t do_force,
                        Bool_t do_sounds,
                        Bool_t do_apply);
        Bool_t Unequip_Item(Actor_t* actor,
                            Form_t* form,
                            XList_t* xlist,
                            UInt32 count,
                            BGSEquipSlot* slot,
                            Bool_t do_queue,
                            Bool_t do_force,
                            Bool_t do_sounds,
                            Bool_t do_apply,
                            BGSEquipSlot* slot_to_replace);
    };

    class Actor_t2 {
    public:
        enum Form_Flags : UInt32 {
            HASNT_HAVOK_COLLISION = 4, // checkout 29 on Character type
            IGNORES_FRIENDLY_HITS = 20,
            IS_INITIALLY_DISABLED = 27,
        };

        enum Flags_1 : UInt32 {
            PROCESS_AI              = 1,
            IS_DEAD                 = 11,
            RESET_AI                = 17,
            IS_PLAYER_TEAMMATE      = 26,
            IS_PARALYZED            = 31,
        };

        enum Flags_2 : UInt32 {
            IS_A_MOUNT              = 1,
            IS_MOUNT_OBSTRUCTED     = 2,
            IS_MOUNTING_ON_OFF      = 3,
            DOES_FAVORS             = 7,
            UPDATE_ANIMATION_GRAPH  = 8,
            CAN_SPEAK               = 13,
            FORCE_ANIMATION_UPDATE  = 17,
            IS_ESSENTIAL            = 18,
            IS_PROTECTED            = 19,
            HIDDEN_FROM_STEALTH_EYE = 26,
            IS_IMMOBILE             = 27,
            FORCE_ANIMATION_UPDATES = 29,
            IS_UNDERWATER           = 31,
        };

        enum Update_3D_Flags : UInt8 {
            MODEL_3D                = 0,
            SKIN_3D                 = 1,
            HEAD_3D                 = 2,
            FACE_3D                 = 3,
            SCALE_3D                = 4,
            SKELETON_3D             = 5,
            UNKNOWN_6               = 6,
            UNKNOWN_7               = 7,
        };
    };

    class Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_Alias
        };

        enum Flags : UInt32 {
            // ...
            IS_ESSENTIAL = 1 << 6,
            // ...
            IS_PROTECTED = 1 << 10,
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

        void Log();
    };
    STATIC_ASSERT(sizeof(Alias_Base_t) == 0x28);

    class Alias_Reference_t : public Alias_Base_t {
    public:
        enum {
            kTypeID = kFormType_ReferenceAlias,
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

        void Log();
    };
    STATIC_ASSERT(sizeof(Alias_Reference_t) == 0x48);

    class Faction_Rank_t {
    public:
        Faction_t* faction;
        SInt8 rank;
        UInt8 pad[7];
    };
    STATIC_ASSERT(sizeof(Faction_Rank_t) == 0x10);

    class Quest_t2 : public BGSStoryManagerTreeForm {
    public:
        class Hash_Map_t {
        public:
            class Tuple_t {
            public:
                UInt16 key;
                UInt16 value; // unused in this hashmap!
            };

            class Entry_t {
            public:
                Tuple_t tuple;
                Entry_t* chain; // if nullptr, key is not in the table
            };

            UInt64 pad_00; // 00
            UInt32 pad_08; // 08
            UInt32 capacity; // 0C
            UInt32 free_count; // 10
            UInt32 free_idx; // 14
            Entry_t* end_of_chain; // 18
            UInt64 pad_20; // 20
            Entry_t* entries; // 28

            Bool_t Has_Key(UInt16 key);
        };
    };

    class Process_Lists_t {
    public:
        static Process_Lists_t* Self();
    public:
        void Stop_Combat_Alarm(Actor_t* actor, Bool_t dont_end_alarm = false);
    };

    class Global_t : public Form_t {
    public:
        enum {
            kTypeID = kFormType_Global,
        };

        enum Type : char {
            FLOAT = 'f',
            SHORT = 's',
            LONG = 'l',
        };
    public:
        virtual ~Global_t();

        BSString editor_id; // 20
        char type; // 30
        UInt8 pad_31; // 31
        UInt16 pad_32; // 32
        Float_t value; // 34 (static cast to other types)
    };
    STATIC_ASSERT(sizeof(Global_t) == 0x38);

    class Relationship_t : public Form_t {
    public:

        // interesting. maybe we can just enforce the relationship rank
        // and not save it. that way we don't have to back it up so seriously
        enum class Change_e : UInt32 {
            RELATIONSHIP = 1 << 1,
        };

        // are these accurate? Papyrus returns different values for GetRelationshipRank
        enum class Rank_e : UInt8 {
            LOVER = 0,
            ALLY = 1,
            CONFIDANT = 2,
            FRIEND = 3,
            ACQUAINTANCE = 4,
            RIVAL = 5,
            FOE = 6,
            ENEMY = 7,
            ARCHNEMESIS = 8,
        };

        virtual ~Relationship_t(); // 00

        Actor_Base_t* base_actor_1; // 20
        Actor_Base_t* base_actor_2; // 28
        BGSAssociationType* association; // 30
        Rank_e rank; // 38
        UInt8 unk_39; // 39
        UInt8 unk_3A; // 3A
        UInt8 flag_3B; // 3B
        UInt32 pad_3C; // 3C
    };
    STATIC_ASSERT(sizeof(Relationship_t) == 0x40);

    typedef tArray<Relationship_t*> Relationships_t;

    class Magic_Target_t {
    public:
        virtual ~Magic_Target_t(); // 00

        Bool_t Has_Magic_Effect(Magic_Effect_t* magic_effect);

        // bool HasMagicEffect(EffectSetting* a_effect);
    };

    class Menu_Manager_t {
    public:
        UInt8 unk[0x110];
        UnkArray menu_stack; // 0x110
    };
    STATIC_ASSERT(sizeof(Menu_Manager_t) == 0x110 + 0x18);

}

namespace doticu_npcp {

    typedef tArray<Faction_Rank_t>  BFaction_Ranks_t;
    typedef Faction_Rank_t          BFaction_Rank_t;
    typedef ExtraFactionChanges     XFactions_t;
    typedef tArray<Faction_Rank_t>  XFaction_Ranks_t;
    typedef Faction_Rank_t          XFaction_Rank_t;

    class ExtraCanTalkToPlayer : public BSExtraData {
    public:
        virtual ~ExtraCanTalkToPlayer();

        Bool_t can_talk; // 10
        UInt8 pad_11; // 11
        UInt16 pad_12; // 12
        UInt32 pad_14; // 14
    };

    class ExtraFlags : public BSExtraData {
    public:
        enum : UInt32 {
            BLOCKS_ACTIVATION = 0,
            BLOCKS_PLAYER_ACTIVATION = 1,
            // ...
        };

        virtual ~ExtraFlags();

        UInt32 flags; // 10
        UInt32 pad; // 14
    };

    class ExtraGhost : public BSExtraData {
    public:
        virtual ~ExtraGhost();

        Bool_t is_ghost; // 10
        UInt8 pad_11; // 11
        UInt16 pad_12; // 12
        UInt32 pad_14; // 14
    };

    class ExtraTextDisplay : public BSExtraData {
    public:
        virtual ~ExtraTextDisplay();

        enum {
            DEFAULT = -1,
            CUSTOM = -2,
        };

        String_t name; // 10
        BGSMessage* message; // 18
        Quest_t* owner; // 20
        SInt32 flag; // 28
        Float_t extra_health; // 2C
        UInt16 custom_length; // 30
        UInt16 pad_32; // 32
        UInt32 pad_34; // 34

        void Force_Rename(String_t new_name);
    };
    STATIC_ASSERT(sizeof(ExtraTextDisplay) == 0x38);

    /*class Extra_Container_Changes_t : public BSExtraData {
    public:
        static Extra_Container_Changes_t* Create(Reference_t* owner);
        static void Destroy(Extra_Container_Changes_t* xchanges);
    public:
        virtual ~Extra_Container_Changes_t();

        Container_Changes_t* changes;
    };
    STATIC_ASSERT(sizeof(Extra_Container_Changes_t) == 0x18);*/

}

namespace doticu_npcp {

    typedef TESQuest                Consts_t;
    typedef TESQuest                Vars_t;

    typedef StaticFunctionTag       Selfless_t;

}

namespace doticu_npcp { namespace Papyrus {

    typedef VMClassRegistry         Registry_t;
    typedef IObjectHandlePolicy     Policy_t;
    typedef UInt32                  Stack_ID_t;
    typedef VMScriptInstance        Script_t;
    typedef UInt64                  Type_e;
    typedef UInt32                  Type_ID_t;

    template <typename T> using Vector_t = VMResultArray<T>;
    typedef Vector_t<Int_t> Int_Vector_t;

    template <typename Type>
    struct Range_t {
        Type begin;
        Type end;
    };

}}
