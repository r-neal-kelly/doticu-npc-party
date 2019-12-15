Scriptname doticu_npc_party_script_follower extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      p_CONSTS        = none
doticu_npc_party_script_codes       p_CODES         = none
doticu_npc_party_script_vars        p_VARS          = none
doticu_npc_party_script_actor       p_ACTOR2        = none
doticu_npc_party_script_members     p_MEMBERS       = none
doticu_npc_party_script_followers   p_FOLLOWERS     = none
Actor                               p_REF_PLAYER    = none
int                                 p_ID_ALIAS      =   -1

; Private Variables
bool                            p_is_created                = false
Actor                           p_ref_actor                 =  none
doticu_npc_party_script_member  p_ref_member                =  none
int                             p_style_follower            =    -1
int                             p_level_follower            =    -1
bool                            p_is_sneak                  = false

int                             p_prev_relationship_rank    =    -1
float                           p_prev_waiting_for_player   =  -1.0
float                           p_prev_aggression           =  -1.0
float                           p_prev_confidence           =  -1.0
float                           p_prev_assistance           =  -1.0; this may need to go on Member
float                           p_prev_morality             =  -1.0
float                           p_prev_speed_mult           =  -1.0

float                           p_prev_health               =  -1.0
float                           p_prev_magicka              =  -1.0
float                           p_prev_stamina              =  -1.0
float                           p_prev_one_handed           =  -1.0
float                           p_prev_two_handed           =  -1.0
float                           p_prev_block                =  -1.0
float                           p_prev_heavy_armor          =  -1.0
float                           p_prev_light_armor          =  -1.0
float                           p_prev_smithing             =  -1.0
float                           p_prev_destruction          =  -1.0
float                           p_prev_restoration          =  -1.0
float                           p_prev_conjuration          =  -1.0
float                           p_prev_alteration           =  -1.0
float                           p_prev_illusion             =  -1.0
float                           p_prev_enchanting           =  -1.0
float                           p_prev_marksman             =  -1.0
float                           p_prev_sneak                =  -1.0
float                           p_prev_alchemy              =  -1.0
float                           p_prev_lockpicking          =  -1.0
float                           p_prev_pickpocket           =  -1.0
float                           p_prev_speechcraft          =  -1.0

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int ID_ALIAS)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    p_MEMBERS = DATA.MODS.MEMBERS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
    p_REF_PLAYER = DATA.CONSTS.ACTOR_PLAYER
    p_ID_ALIAS = ID_ALIAS
endFunction

int function f_Create()
    int code_return

    if Exists()
        return p_CODES.IS_FOLLOWER
    endIf
    p_ref_actor = GetActorReference()
    if !p_ref_actor
        return p_CODES.ISNT_ACTOR
    endIf
    p_ref_member = p_MEMBERS.Get_Member(p_ref_actor)
    if !p_ref_member
        return p_CODES.ISNT_MEMBER
    endIf
    p_is_created = true
    p_style_follower = p_ref_member.Get_Style()

    p_Backup()
    p_Token()
    ; f_Enforce() will handle the rest

    return p_CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return p_CODES.ISNT_FOLLOWER
    endIf

    if p_is_sneak
        p_Unsneak()
    endIf
    p_Unlevel()
    p_Unfollow()
    p_Untoken()
    p_Restore()

    p_is_sneak = false
    p_level_follower = -1
    p_style_follower = -1
    p_ref_member = none
    p_ref_actor = none
    p_is_created = false

    return p_CODES.SUCCESS
endFunction

int function f_Enforce()
    int code_return

    if !Exists()
        return p_CODES.ISNT_FOLLOWER
    endIf

    p_Token()
    p_Follow()
    p_Level(); this needs to be put in an OnUpdate, so it doesn't disrupt user experience
    if p_is_sneak
        p_Sneak()
    endIf

    return p_CODES.SUCCESS
endFunction

; Private Methods
function p_Backup()
    p_prev_relationship_rank = p_ref_actor.GetRelationshipRank(p_CONSTS.ACTOR_PLAYER)
    p_prev_waiting_for_player = p_ref_actor.GetBaseActorValue("WaitingForPlayer")
    p_prev_aggression = p_ref_actor.GetBaseActorValue("Aggression")
    p_prev_confidence = p_ref_actor.GetBaseActorValue("Confidence")
    p_prev_assistance = p_ref_actor.GetBaseActorValue("Assistance"); this may need to go on Member
    p_prev_morality = p_ref_actor.GetBaseActorValue("Morality")
    p_prev_speed_mult = p_ref_actor.GetBaseActorValue("SpeedMult")

    p_prev_health = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_HEALTH)
    p_prev_magicka = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_MAGICKA)
    p_prev_stamina = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_STAMINA)
    p_prev_one_handed = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_ONE_HANDED)
    p_prev_two_handed = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_TWO_HANDED)
    p_prev_block = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_BLOCK)
    p_prev_heavy_armor = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_HEAVY_ARMOR)
    p_prev_light_armor = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_LIGHT_ARMOR)
    p_prev_smithing = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_SMITHING)
    p_prev_destruction = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_DESTRUCTION)
    p_prev_restoration = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_RESTORATION)
    p_prev_conjuration = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_CONJURATION)
    p_prev_alteration = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_ALTERATION)
    p_prev_illusion = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_ILLUSION)
    p_prev_enchanting = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_ENCHANTING)
    p_prev_marksman = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_MARKSMAN)
    p_prev_sneak = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_SNEAK)
    p_prev_alchemy = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_ALCHEMY)
    p_prev_lockpicking = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_LOCKPICKING)
    p_prev_pickpocket = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_PICKPOCKET)
    p_prev_speechcraft = p_ref_actor.GetBaseActorValue(p_CONSTS.STR_SPEECHCRAFT)
endFunction

function p_Restore()
    p_ref_actor.SetActorValue(p_CONSTS.STR_SPEECHCRAFT, p_prev_speechcraft)
    p_ref_actor.SetActorValue(p_CONSTS.STR_PICKPOCKET, p_prev_pickpocket)
    p_ref_actor.SetActorValue(p_CONSTS.STR_LOCKPICKING, p_prev_lockpicking)
    p_ref_actor.SetActorValue(p_CONSTS.STR_ALCHEMY, p_prev_alchemy)
    p_ref_actor.SetActorValue(p_CONSTS.STR_SNEAK, p_prev_sneak)
    p_ref_actor.SetActorValue(p_CONSTS.STR_MARKSMAN, p_prev_marksman)
    p_ref_actor.SetActorValue(p_CONSTS.STR_ENCHANTING, p_prev_enchanting)
    p_ref_actor.SetActorValue(p_CONSTS.STR_ILLUSION, p_prev_illusion)
    p_ref_actor.SetActorValue(p_CONSTS.STR_ALTERATION, p_prev_alteration)
    p_ref_actor.SetActorValue(p_CONSTS.STR_CONJURATION, p_prev_conjuration)
    p_ref_actor.SetActorValue(p_CONSTS.STR_RESTORATION, p_prev_restoration)
    p_ref_actor.SetActorValue(p_CONSTS.STR_DESTRUCTION, p_prev_destruction)
    p_ref_actor.SetActorValue(p_CONSTS.STR_SMITHING, p_prev_smithing)
    p_ref_actor.SetActorValue(p_CONSTS.STR_LIGHT_ARMOR, p_prev_light_armor)
    p_ref_actor.SetActorValue(p_CONSTS.STR_HEAVY_ARMOR, p_prev_heavy_armor)
    p_ref_actor.SetActorValue(p_CONSTS.STR_BLOCK, p_prev_block)
    p_ref_actor.SetActorValue(p_CONSTS.STR_TWO_HANDED, p_prev_two_handed)
    p_ref_actor.SetActorValue(p_CONSTS.STR_ONE_HANDED, p_prev_one_handed)
    p_ref_actor.SetActorValue(p_CONSTS.STR_STAMINA, p_prev_stamina)
    p_ref_actor.SetActorValue(p_CONSTS.STR_MAGICKA, p_prev_magicka)
    p_ref_actor.SetActorValue(p_CONSTS.STR_HEALTH, p_prev_health)

    p_ref_actor.SetActorValue("SpeedMult", p_prev_speed_mult)
    p_ref_actor.SetActorValue("Morality", p_prev_morality)
    p_ref_actor.SetActorValue("Assistance", p_prev_assistance); this may need to go on Member
    p_ref_actor.SetActorValue("Confidence", p_prev_confidence)
    p_ref_actor.SetActorValue("Aggression", 0.0)
    p_ref_actor.SetActorValue("WaitingForPlayer", p_prev_waiting_for_player)
endFunction

function p_Token()
    p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER, p_ID_ALIAS + 1)
    if p_is_sneak
        p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER_SNEAK)
    else
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER_SNEAK)
    endIf
endFunction

function p_Untoken()
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER_SNEAK)
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER)
endFunction

function p_Follow()
    p_CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)
    p_ref_actor.SetRelationshipRank(p_CONSTS.ACTOR_PLAYER, 3)
    p_ref_actor.SetPlayerTeammate(true, true)
    p_ref_actor.IgnoreFriendlyHits(true)
    p_ref_actor.SetNotShowOnStealthMeter(true)
    ;p_ref_actor.AllowPCDialogue(true)
    p_ref_actor.SetActorValue("WaitingForPlayer", 0.0)
    p_ref_actor.SetActorValue("Aggression", 0.0)
    p_ref_actor.SetActorValue("Confidence", 4.0)
    p_ref_actor.SetActorValue("Assistance", 2.0); this may need to go on Member
    p_ref_actor.SetActorValue("Morality", 0.0)
    p_ref_actor.SetActorValue("SpeedMult", 120.0)
    ; use p_VARS to auto set as essential, protected, or mortal (immortal instead of essential?)

    ; will want to add to CurrentFollowerFaction?
    ; or completely remove it from the npc?
    ; or disable the vanilla follower dialogue?
    ; should we make our own with hard links?
endFunction

function p_Unfollow()
    p_ref_actor.SetNotShowOnStealthMeter(false)
    p_ref_actor.IgnoreFriendlyHits(false)
    p_ref_actor.SetPlayerTeammate(false, false)
    p_ref_actor.SetRelationshipRank(p_CONSTS.ACTOR_PLAYER, p_prev_relationship_rank)
endFunction

function p_Sneak()
endFunction

function p_Unsneak()
endFunction

function p_Level()
    int style_member = p_ref_member.Get_Style()
    int level_player = p_CONSTS.ACTOR_PLAYER.GetLevel()
    if style_member == p_style_follower && level_player == p_level_follower
        return
    endIf
    p_style_follower = style_member
    p_level_follower = level_player

    float modifier = 0.67 - (level_player * 0.003); maybe use Math.Log to get a more fair equation for higher levels
    float max_attribute = 1000
    float min_attribute = 100
    float max_skill = 100
    float min_skill = 0

    float health        = p_prev_health         + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_HEALTH)       * modifier
    float magicka       = p_prev_magicka        + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_MAGICKA)      * modifier
    float stamina       = p_prev_stamina        + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_STAMINA)      * modifier

    float one_handed    = p_prev_one_handed     + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_ONE_HANDED)   * modifier
    float two_handed    = p_prev_two_handed     + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_TWO_HANDED)   * modifier
    float block         = p_prev_block          + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_BLOCK)        * modifier
    float heavy_armor   = p_prev_heavy_armor    + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_HEAVY_ARMOR)  * modifier
    float light_armor   = p_prev_light_armor    + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_LIGHT_ARMOR)  * modifier
    float smithing      = p_prev_smithing       + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_SMITHING)     * modifier

    float destruction   = p_prev_destruction    + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_DESTRUCTION)  * modifier
    float restoration   = p_prev_restoration    + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_RESTORATION)  * modifier
    float conjuration   = p_prev_conjuration    + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_CONJURATION)  * modifier
    float alteration    = p_prev_alteration     + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_ALTERATION)   * modifier
    float illusion      = p_prev_illusion       + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_ILLUSION)     * modifier
    float enchanting    = p_prev_enchanting     + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_ENCHANTING)   * modifier

    float marksman      = p_prev_marksman       + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_MARKSMAN)     * modifier
    float sneak         = p_prev_sneak          + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_SNEAK)        * modifier
    float alchemy       = p_prev_alchemy        + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_ALCHEMY)      * modifier
    float lockpicking   = p_prev_lockpicking    + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_LOCKPICKING)  * modifier
    float pickpocket    = p_prev_pickpocket     + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_PICKPOCKET)   * modifier
    float speechcraft   = p_prev_speechcraft    + p_REF_PLAYER.GetBaseActorValue(p_CONSTS.STR_SPEECHCRAFT)  * modifier

    if Is_Styled_Warrior()
        one_handed  += level_player * modifier
        two_handed  += level_player * modifier
        block       += level_player * modifier
        heavy_armor += level_player * modifier
        light_armor += level_player * modifier
        smithing    += level_player * modifier

        destruction -= level_player * modifier
        restoration -= level_player * modifier
        conjuration -= level_player * modifier
        alteration  -= level_player * modifier
        illusion    -= level_player * modifier
        enchanting  -= level_player * modifier

        marksman    -= level_player * modifier
        sneak       -= level_player * modifier
        alchemy     -= level_player * modifier
        lockpicking -= level_player * modifier
        pickpocket  -= level_player * modifier
        speechcraft -= level_player * modifier
    elseIf Is_Styled_Mage()
        one_handed  -= level_player * modifier
        two_handed  -= level_player * modifier
        block       -= level_player * modifier
        heavy_armor -= level_player * modifier
        light_armor -= level_player * modifier
        smithing    -= level_player * modifier

        destruction += level_player * modifier
        restoration += level_player * modifier
        conjuration += level_player * modifier
        alteration  += level_player * modifier
        illusion    += level_player * modifier
        enchanting  += level_player * modifier

        marksman    -= level_player * modifier
        sneak       -= level_player * modifier
        alchemy     -= level_player * modifier
        lockpicking -= level_player * modifier
        pickpocket  -= level_player * modifier
        speechcraft -= level_player * modifier
    elseIf Is_Styled_Archer()
        one_handed  -= level_player * modifier
        two_handed  -= level_player * modifier
        block       -= level_player * modifier
        heavy_armor -= level_player * modifier
        light_armor -= level_player * modifier
        smithing    -= level_player * modifier

        destruction -= level_player * modifier
        restoration -= level_player * modifier
        conjuration -= level_player * modifier
        alteration  -= level_player * modifier
        illusion    -= level_player * modifier
        enchanting  -= level_player * modifier

        marksman    += level_player * modifier
        sneak       += level_player * modifier
        alchemy     += level_player * modifier
        lockpicking += level_player * modifier
        pickpocket  += level_player * modifier
        speechcraft += level_player * modifier
    endIf

    if health > max_attribute
        health = max_attribute
    elseIf health < min_attribute
        health = min_attribute
    endIf
    if magicka > max_attribute
        magicka = max_attribute
    elseIf magicka < min_attribute
        magicka = min_attribute
    endIf
    if stamina > max_attribute
        stamina = max_attribute
    elseIf stamina < min_attribute
        stamina = min_attribute
    endIf

    if one_handed > max_skill
        one_handed = max_skill
    elseIf one_handed < min_skill
        one_handed = min_skill
    endIf
    if two_handed > max_skill
        two_handed = max_skill
    elseIf two_handed < min_skill
        two_handed = min_skill
    endIf
    if block > max_skill
        block = max_skill
    elseIf block < min_skill
        block = min_skill
    endIf
    if heavy_armor > max_skill
        heavy_armor = max_skill
    elseIf heavy_armor < min_skill
        heavy_armor = min_skill
    endIf
    if light_armor > max_skill
        light_armor = max_skill
    elseIf light_armor < min_skill
        light_armor = min_skill
    endIf
    if smithing > max_skill
        smithing = max_skill
    elseIf smithing < min_skill
        smithing = min_skill
    endIf

    if destruction > max_skill
        destruction = max_skill
    elseIf destruction < min_skill
        destruction = min_skill
    endIf
    if restoration > max_skill
        restoration = max_skill
    elseIf restoration < min_skill
        restoration = min_skill
    endIf
    if conjuration > max_skill
        conjuration = max_skill
    elseIf conjuration < min_skill
        conjuration = min_skill
    endIf
    if alteration > max_skill
        alteration = max_skill
    elseIf alteration < min_skill
        alteration = min_skill
    endIf
    if illusion > max_skill
        illusion = max_skill
    elseIf illusion < min_skill
        illusion = min_skill
    endIf
    if enchanting > max_skill
        enchanting = max_skill
    elseIf enchanting < min_skill
        enchanting = min_skill
    endIf

    if marksman > max_skill
        marksman = max_skill
    elseIf marksman < min_skill
        marksman = min_skill
    endIf
    if sneak > max_skill
        sneak = max_skill
    elseIf sneak < min_skill
        sneak = min_skill
    endIf
    if alchemy > max_skill
        alchemy = max_skill
    elseIf alchemy < min_skill
        alchemy = min_skill
    endIf
    if lockpicking > max_skill
        lockpicking = max_skill
    elseIf lockpicking < min_skill
        lockpicking = min_skill
    endIf
    if pickpocket > max_skill
        pickpocket = max_skill
    elseIf pickpocket < min_skill
        pickpocket = min_skill
    endIf
    if speechcraft > max_skill
        speechcraft = max_skill
    elseIf speechcraft < min_skill
        speechcraft = min_skill
    endIf

    p_ref_actor.SetActorValue(p_CONSTS.STR_HEALTH, health)
    p_ref_actor.SetActorValue(p_CONSTS.STR_MAGICKA, magicka)
    p_ref_actor.SetActorValue(p_CONSTS.STR_STAMINA, stamina)

    p_ref_actor.SetActorValue(p_CONSTS.STR_ONE_HANDED, one_handed)
    p_ref_actor.SetActorValue(p_CONSTS.STR_TWO_HANDED, two_handed)
    p_ref_actor.SetActorValue(p_CONSTS.STR_BLOCK, block)
    p_ref_actor.SetActorValue(p_CONSTS.STR_HEAVY_ARMOR, heavy_armor)
    p_ref_actor.SetActorValue(p_CONSTS.STR_LIGHT_ARMOR, light_armor)
    p_ref_actor.SetActorValue(p_CONSTS.STR_SMITHING, smithing)

    p_ref_actor.SetActorValue(p_CONSTS.STR_DESTRUCTION, destruction)
    p_ref_actor.SetActorValue(p_CONSTS.STR_RESTORATION, restoration)
    p_ref_actor.SetActorValue(p_CONSTS.STR_CONJURATION, conjuration)
    p_ref_actor.SetActorValue(p_CONSTS.STR_ALTERATION, alteration)
    p_ref_actor.SetActorValue(p_CONSTS.STR_ILLUSION, illusion)
    p_ref_actor.SetActorValue(p_CONSTS.STR_ENCHANTING, enchanting)

    p_ref_actor.SetActorValue(p_CONSTS.STR_MARKSMAN, marksman)
    p_ref_actor.SetActorValue(p_CONSTS.STR_SNEAK, sneak)
    p_ref_actor.SetActorValue(p_CONSTS.STR_ALCHEMY, alchemy)
    p_ref_actor.SetActorValue(p_CONSTS.STR_LOCKPICKING, lockpicking)
    p_ref_actor.SetActorValue(p_CONSTS.STR_PICKPOCKET, pickpocket)
    p_ref_actor.SetActorValue(p_CONSTS.STR_SPEECHCRAFT, speechcraft)

    ; Print
    ;/MiscUtil.PrintConsole("health: " + p_ref_actor.GetActorValue(p_CONSTS.STR_HEALTH))
    MiscUtil.PrintConsole("magicka: " + p_ref_actor.GetActorValue(p_CONSTS.STR_MAGICKA))
    MiscUtil.PrintConsole("stamina: " + p_ref_actor.GetActorValue(p_CONSTS.STR_STAMINA))

    MiscUtil.PrintConsole("one_handed: " + p_ref_actor.GetActorValue(p_CONSTS.STR_ONE_HANDED))
    MiscUtil.PrintConsole("two_handed: " + p_ref_actor.GetActorValue(p_CONSTS.STR_TWO_HANDED))
    MiscUtil.PrintConsole("block: " + p_ref_actor.GetActorValue(p_CONSTS.STR_BLOCK))
    MiscUtil.PrintConsole("heavy_armor: " + p_ref_actor.GetActorValue(p_CONSTS.STR_HEAVY_ARMOR))
    MiscUtil.PrintConsole("light_armor: " + p_ref_actor.GetActorValue(p_CONSTS.STR_LIGHT_ARMOR))
    MiscUtil.PrintConsole("smithing: " + p_ref_actor.GetActorValue(p_CONSTS.STR_SMITHING))

    MiscUtil.PrintConsole("destruction: " + p_ref_actor.GetActorValue(p_CONSTS.STR_DESTRUCTION))
    MiscUtil.PrintConsole("restoration: " + p_ref_actor.GetActorValue(p_CONSTS.STR_RESTORATION))
    MiscUtil.PrintConsole("conjuration: " + p_ref_actor.GetActorValue(p_CONSTS.STR_CONJURATION))
    MiscUtil.PrintConsole("alteration: " + p_ref_actor.GetActorValue(p_CONSTS.STR_ALTERATION))
    MiscUtil.PrintConsole("illusion: " + p_ref_actor.GetActorValue(p_CONSTS.STR_ILLUSION))
    MiscUtil.PrintConsole("enchanting: " + p_ref_actor.GetActorValue(p_CONSTS.STR_ENCHANTING))

    MiscUtil.PrintConsole("marksman: " + p_ref_actor.GetActorValue(p_CONSTS.STR_MARKSMAN))
    MiscUtil.PrintConsole("sneak: " + p_ref_actor.GetActorValue(p_CONSTS.STR_SNEAK))
    MiscUtil.PrintConsole("alchemy: " + p_ref_actor.GetActorValue(p_CONSTS.STR_ALCHEMY))
    MiscUtil.PrintConsole("lockpicking: " + p_ref_actor.GetActorValue(p_CONSTS.STR_LOCKPICKING))
    MiscUtil.PrintConsole("pickpocket: " + p_ref_actor.GetActorValue(p_CONSTS.STR_PICKPOCKET))
    MiscUtil.PrintConsole("speechcraft: " + p_ref_actor.GetActorValue(p_CONSTS.STR_SPEECHCRAFT))/;
endFunction

function p_Unlevel()
endFunction

; Public Methods
int function Enforce()
    return p_ref_member.Enforce()
endFunction

bool function Exists()
    return p_is_created
endFunction

string function Get_Name()
    return p_ref_member.Get_Name()
endFunction

Actor function Get_Actor()
    return p_ref_member.Get_Actor()
endFunction

doticu_npc_party_script_member function Get_Member()
    if !Exists() || !p_ref_member.Exists()
        return none
    else
        return p_ref_member
    endIf
endFunction

doticu_npc_party_script_settler function Get_Settler()
    return p_ref_member.Get_Settler()
endFunction

int function Set_Name(string str_name)
    return p_ref_member.Set_Name(str_name)
endFunction

int function Sneak()
    int code_return

    if !Exists()
        return p_CODES.ISNT_FOLLOWER
    endIf

    if p_is_sneak
        return p_CODES.IS_SNEAK
    endIf

    p_is_sneak = true

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unsneak()
    int code_return

    if !Exists()
        return p_CODES.ISNT_FOLLOWER
    endIf

    if !p_is_sneak
        return p_CODES.ISNT_SNEAK
    endIf

    p_is_sneak = false

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Level()
    int code_return

    if !Exists()
        return p_CODES.ISNT_FOLLOWER
    endIf

    p_Level()

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unfollow()
    return p_ref_member.Unfollow()
endFunction

int function Access()
    return p_ref_member.Access()
endFunction

int function Settle()
    return p_ref_member.Settle()
endFunction

int function Unsettle()
    return p_ref_member.Unsettle()
endFunction

int function Immobilize()
    return p_ref_member.Immobilize()
endFunction

int function Mobilize()
    return p_ref_member.Mobilize()
endFunction

int function Unmember()
    return p_ref_member.Unmember()
endFunction

int function Unclone()
    return p_ref_member.Unclone()
endFunction

bool function Is_Sneak()
    return p_is_sneak
endFunction

bool function Is_Settler()
    return p_ref_member.Is_Settler()
endFunction

bool function Is_Immobile()
    return p_ref_member.Is_Immobile()
endFunction

bool function Is_Styled_Default()
    return p_ref_member.Is_Styled_Default()
endFunction

bool function Is_Styled_Warrior()
    return p_ref_member.Is_Styled_Warrior()
endFunction

bool function Is_Styled_Mage()
    return p_ref_member.Is_Styled_Mage()
endFunction

bool function Is_Styled_Archer()
    return p_ref_member.Is_Styled_Archer()
endFunction

function Summon(int distance = 60, int angle = 0)
    p_ref_member.Summon(distance, angle)
endFunction

function Summon_Ahead()
    p_ref_member.Summon_Ahead()
endFunction

function Summon_Behind()
    p_ref_member.Summon_Behind()
endFunction

; Events
; need to add the catch up function, when player pulls out their weapon. but make it faster this time.
