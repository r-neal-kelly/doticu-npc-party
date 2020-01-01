Scriptname doticu_npcp_follower extends ReferenceAlias

; Private Constants
doticu_npcp_data        p_DATA                      =  none
doticu_npcp_consts      p_CONSTS                    =  none
doticu_npcp_codes       p_CODES                     =  none
doticu_npcp_vars        p_VARS                      =  none
doticu_npcp_funcs       p_FUNCS                     =  none
doticu_npcp_actors      p_ACTORS                    =  none
doticu_npcp_queues      p_QUEUES                    =  none
doticu_npcp_members     p_MEMBERS                   =  none
doticu_npcp_followers   p_FOLLOWERS                 =  none
doticu_npcp_control     p_CONTROL                   =  none

Actor                   p_REF_PLAYER                =  none
int                     p_ID_ALIAS                  =    -1

; Private Variables
bool                    p_is_created                = false
Actor                   p_ref_actor                 =  none
doticu_npcp_member      p_ref_member                =  none
int                     p_style_follower            =    -1
int                     p_level_follower            =    -1
bool                    p_is_sneak                  = false
doticu_npcp_queue       p_queue_follower            =  none

int                     p_prev_relationship_rank    =    -1
float                   p_prev_waiting_for_player   =  -1.0
float                   p_prev_aggression           =  -1.0
float                   p_prev_confidence           =  -1.0
float                   p_prev_assistance           =  -1.0; this may need to go on Member
float                   p_prev_morality             =  -1.0
float                   p_prev_speed_mult           =  -1.0

float                   p_prev_health               =  -1.0
float                   p_prev_magicka              =  -1.0
float                   p_prev_stamina              =  -1.0
float                   p_prev_one_handed           =  -1.0
float                   p_prev_two_handed           =  -1.0
float                   p_prev_block                =  -1.0
float                   p_prev_heavy_armor          =  -1.0
float                   p_prev_light_armor          =  -1.0
float                   p_prev_smithing             =  -1.0
float                   p_prev_destruction          =  -1.0
float                   p_prev_restoration          =  -1.0
float                   p_prev_conjuration          =  -1.0
float                   p_prev_alteration           =  -1.0
float                   p_prev_illusion             =  -1.0
float                   p_prev_enchanting           =  -1.0
float                   p_prev_marksman             =  -1.0
float                   p_prev_sneak                =  -1.0
float                   p_prev_alchemy              =  -1.0
float                   p_prev_lockpicking          =  -1.0
float                   p_prev_pickpocket           =  -1.0
float                   p_prev_speechcraft          =  -1.0

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_FUNCS = DATA.MODS.FUNCS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_QUEUES = DATA.MODS.FUNCS.QUEUES
    p_MEMBERS = DATA.MODS.MEMBERS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
    p_CONTROL = DATA.MODS.CONTROL
endFunction

function f_Initialize(int ID_ALIAS)
    p_REF_PLAYER = p_CONSTS.ACTOR_PLAYER
    p_ID_ALIAS = ID_ALIAS
endFunction

function f_Register()
    ; registering mod events is global for each script on an object, and
    ; further, works for handlers labeled as function as well as event.
    RegisterForModEvent("doticu_npcp_followers_enforce", "On_Followers_Enforce")
    RegisterForModEvent("doticu_npcp_followers_settle", "On_Followers_Settle")
    RegisterForModEvent("doticu_npcp_followers_unsettle", "On_Followers_Unsettle")
    RegisterForModEvent("doticu_npcp_followers_immobilize", "On_Followers_Immobilize")
    RegisterForModEvent("doticu_npcp_followers_mobilize", "On_Followers_Mobilize")
    RegisterForModEvent("doticu_npcp_followers_sneak", "On_Followers_Sneak")
    RegisterForModEvent("doticu_npcp_followers_unsneak", "On_Followers_Unsneak")
    RegisterForModEvent("doticu_npcp_followers_unfollow", "On_Followers_Unfollow")
    RegisterForModEvent("doticu_npcp_followers_unmember", "On_Followers_Unmember")
    RegisterForModEvent("doticu_npcp_followers_resurrect", "On_Followers_Resurrect")
    RegisterForModEvent("doticu_npcp_members_u_0_1_1", "On_u_0_1_1")
    RegisterForModEvent("doticu_npcp_members_u_0_1_4", "On_u_0_1_4")
    RegisterForModEvent("doticu_npcp_queue_" + "follower_" + p_ID_ALIAS, "On_Queue_Follower")
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

    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER, p_ID_ALIAS + 1)
    p_ref_actor.EvaluatePackage()

    p_Create_Queues()
    p_Backup()

    return p_CODES.SUCCESS
endFunction

int function f_Destroy()
    if !Exists()
        return p_CODES.ISNT_FOLLOWER
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER)
    p_ref_actor.EvaluatePackage()

    p_queue_follower.Flush(); I think this is the right spot

    if p_is_sneak
        p_Unsneak()
    endIf
    p_Unlevel()
    p_Unfollow()
    p_Untoken()
    
    p_Restore()
    p_Destroy_Queues()

    p_queue_follower = none
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

    p_queue_follower.Enqueue("p_Token")
    p_queue_follower.Enqueue("p_Follow")
    p_queue_follower.Enqueue("p_Level")
    if p_is_sneak
        p_queue_follower.Enqueue("p_Sneak")
    endIf

    return p_CODES.SUCCESS
endFunction

; Private Methods
function p_Create_Queues()
    p_queue_follower = p_QUEUES.Create("follower_" + p_ID_ALIAS, 32, 0.5)
endFunction

function p_Destroy_Queues()
    p_QUEUES.Destroy(p_queue_follower)
endFunction

function p_Backup(); this may need to be async
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
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER, p_ID_ALIAS + 1)
    if p_is_sneak
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER_SNEAK)
    else
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER_SNEAK)
    endIf

    p_ref_actor.EvaluatePackage()
endFunction

function p_Untoken()
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER_SNEAK)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER)

    p_ref_actor.EvaluatePackage()
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

    ; we still need to disable the vanilla follower dialogue. Probably just add an never true condition to the quest data tab.

    ; we also need to figure out how to deal with traps
endFunction

function p_Unfollow()
    p_ref_actor.SetNotShowOnStealthMeter(false)
    p_ref_actor.IgnoreFriendlyHits(false)
    p_ref_actor.SetPlayerTeammate(false, false)
    p_ref_actor.SetRelationshipRank(p_CONSTS.ACTOR_PLAYER, p_prev_relationship_rank)
endFunction

function p_Sneak()
    ; if possible, I want this function to make the followers completely undetectable.
    ; maybe an invisibility spell without the visual effect, if possible? not sure
    p_ref_actor.SetActorValue("SpeedMult", 160.0)
endFunction

function p_Unsneak()
    p_ref_actor.SetActorValue("SpeedMult", 120.0)
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

    float level_player_modded = level_player * modifier

    if Is_Styled_Warrior()
        health      += level_player * 4; find a better equation

        one_handed  += level_player_modded
        two_handed  += level_player_modded
        block       += level_player_modded
        heavy_armor += level_player_modded
        light_armor += level_player_modded
        smithing    += level_player_modded

        destruction -= level_player_modded
        restoration -= level_player_modded
        conjuration -= level_player_modded
        alteration  -= level_player_modded
        illusion    -= level_player_modded
        enchanting  -= level_player_modded

        marksman    -= level_player_modded
        sneak       -= level_player_modded
        alchemy     -= level_player_modded
        lockpicking -= level_player_modded
        pickpocket  -= level_player_modded
        speechcraft -= level_player_modded
    elseIf Is_Styled_Mage()
        magicka      += level_player * 4; find a better equation

        one_handed  -= level_player_modded
        two_handed  -= level_player_modded
        block       -= level_player_modded
        heavy_armor -= level_player_modded
        light_armor -= level_player_modded
        smithing    -= level_player_modded

        destruction += level_player_modded
        restoration += level_player_modded
        conjuration += level_player_modded
        alteration  += level_player_modded
        illusion    += level_player_modded
        enchanting  += level_player_modded

        marksman    -= level_player_modded
        sneak       -= level_player_modded
        alchemy     -= level_player_modded
        lockpicking -= level_player_modded
        pickpocket  -= level_player_modded
        speechcraft -= level_player_modded
    elseIf Is_Styled_Archer()
        stamina      += level_player * 4; find a better equation

        one_handed  -= level_player_modded
        two_handed  -= level_player_modded
        block       -= level_player_modded
        heavy_armor -= level_player_modded
        light_armor -= level_player_modded
        smithing    -= level_player_modded

        destruction -= level_player_modded
        restoration -= level_player_modded
        conjuration -= level_player_modded
        alteration  -= level_player_modded
        illusion    -= level_player_modded
        enchanting  -= level_player_modded

        marksman    += level_player_modded
        sneak       += level_player_modded
        alchemy     += level_player_modded
        lockpicking += level_player_modded
        pickpocket  += level_player_modded
        speechcraft += level_player_modded
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

doticu_npcp_member function Get_Member()
    if !Exists() || !p_ref_member.Exists()
        return none
    else
        return p_ref_member
    endIf
endFunction

doticu_npcp_settler function Get_Settler()
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

    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER_SNEAK)
    p_ref_actor.EvaluatePackage()

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

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_FOLLOWER_SNEAK)
    p_ref_actor.EvaluatePackage()

    p_Unsneak()

    p_is_sneak = false

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unfollow()
    return p_ref_member.Unfollow()
endFunction

int function Pack()
    return p_ref_member.Pack()
endFunction

int function Settle()
    if Is_Settler()
        return p_ref_member.Resettle()
    else
        return p_ref_member.Settle()
    endIf
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
    return Exists() && p_is_sneak
endFunction

bool function Is_Unsneak()
    return Exists() && !p_is_sneak
endFunction

bool function Is_Settler()
    return Exists() && p_ref_member.Is_Settler()
endFunction

bool function Is_Immobile()
    return Exists() && p_ref_member.Is_Immobile()
endFunction

bool function Is_Mobile()
    return Exists() && p_ref_member.Is_Mobile()
endFunction

bool function Is_Styled_Default()
    return Exists() && p_ref_member.Is_Styled_Default()
endFunction

bool function Is_Styled_Warrior()
    return Exists() && p_ref_member.Is_Styled_Warrior()
endFunction

bool function Is_Styled_Mage()
    return Exists() && p_ref_member.Is_Styled_Mage()
endFunction

bool function Is_Styled_Archer()
    return Exists() && p_ref_member.Is_Styled_Archer()
endFunction

bool function Is_Alive()
    return Exists() && p_ACTORS.Is_Alive(p_ref_actor)
endFunction

bool function Is_Dead()
    return Exists() && p_ACTORS.Is_Dead(p_ref_actor)
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

function Resurrect()
    p_ref_member.Resurrect()
endFunction

; Update Methods
event On_u_0_1_1()
endEvent

event On_u_0_1_4(Form form_data)
    p_DATA = form_data as doticu_npcp_data
    if Exists()
        p_queue_follower.u_0_1_4(p_DATA)
    endIf
endEvent

; Events
event On_Queue_Follower(string str_message)
    if str_message == "p_Token"
        p_Token()
    elseIf str_message == "p_Follow"
        p_Follow()
    elseIf str_message == "p_Level"
        p_Level()
    elseIf str_message == "p_Sneak"
        p_Sneak()
    endIf

    p_queue_follower.Dequeue()
endEvent

event OnCombatStateChanged(Actor ref_target, int code_combat)
    if code_combat == p_CODES.COMBAT_NO
        if !Is_Dead()
            p_FUNCS.PLAYER.f_End_Combat()
        endIf
    elseIf code_combat == p_CODES.COMBAT_YES
        p_FUNCS.PLAYER.f_Begin_Combat()
    elseIf code_combat == p_CODES.COMBAT_SEARCHING
    endIf
endEvent

; need to add the catch up function, when player pulls out their weapon. but make it parallel this time.

event On_Followers_Enforce(Form form_tasklist)
    if Exists()
        Enforce()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Settle(Form form_tasklist)
    if Exists()
        Settle()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Unsettle(Form form_tasklist)
    if Exists() && Is_Settler()
        Unsettle()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Immobilize(Form form_tasklist)
    if Exists() && Is_Mobile()
        Immobilize()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Mobilize(Form form_tasklist)
    if Exists() && Is_Immobile()
        Mobilize()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Sneak(Form form_tasklist)
    if Exists() && Is_Unsneak()
        Sneak()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Unsneak(Form form_tasklist)
    if Exists() && Is_Sneak()
        Unsneak()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Resurrect(Form form_tasklist)
    if Exists() && Is_Dead()
        Resurrect()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Unfollow(Form form_tasklist)
    if Exists()
        Unfollow()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Unmember(Form form_tasklist)
    if Exists()
        Unmember()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent
