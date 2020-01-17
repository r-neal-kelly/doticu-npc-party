Scriptname doticu_npcp_follower extends ReferenceAlias

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_codes property CODES hidden
    doticu_npcp_codes function Get()
        return p_DATA.CODES
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_queues property QUEUES hidden
    doticu_npcp_queues function Get()
        return p_DATA.MODS.FUNCS.QUEUES
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return p_DATA.MODS.MEMBERS
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return p_DATA.MODS.FOLLOWERS
    endFunction
endProperty

; Friend Constants
doticu_npcp_queue property f_QUEUE hidden
    doticu_npcp_queue function Get()
        return p_ref_member.f_QUEUE
    endFunction
endProperty

; Public Constants
Actor property ACTOR_PLAYER hidden
    Actor function Get()
        return p_DATA.CONSTS.ACTOR_PLAYER
    endFunction
endProperty
float property MAX_SPEED_SNEAK hidden
    float function Get()
        return 160.0
    endFunction
endProperty
float property MAX_SPEED_UNSNEAK hidden
    float function Get()
        return 130.0
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA                      =  none

; Private Variables
bool                    p_is_created                = false
int                     p_id_alias                  =    -1
Actor                   p_ref_actor                 =  none
doticu_npcp_member      p_ref_member                =  none
string                  p_str_namespace             =    ""
int                     p_style_follower            =    -1
int                     p_level_follower            =    -1
bool                    p_is_sneak                  = false

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
function f_Create(doticu_npcp_data DATA, int id_alias)
    p_DATA = DATA

    p_is_created = true
    p_id_alias = id_alias
    p_ref_actor = GetActorReference()
    p_ref_member = MEMBERS.Get_Member(p_ref_actor)
    p_str_namespace = "follower_" + p_id_alias
    p_style_follower = p_ref_member.Get_Style()
    p_level_follower = -1
    p_is_sneak = false

    ; these are here just so the user sees some changes as soon as possible
    ; the rest of the work is delayed in the queue, primarily through f_Enforce
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_FOLLOWER, p_id_alias + 1)
    p_ref_actor.SetPlayerTeammate(true, true)
    p_ref_actor.EvaluatePackage()

    p_Register_Queues()

    p_Enqueue("Follower.Backup")
endFunction

function f_Destroy()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_FOLLOWER)
    p_ref_actor.EvaluatePackage()

    if p_is_sneak
        p_Unsneak()
    endIf
    p_Unlevel()
    p_Unfollow()
    
    p_Restore()

    p_is_sneak = false
    p_level_follower = -1
    p_style_follower = -1
    p_str_namespace = ""
    p_ref_member = none
    p_ref_actor = none
    p_id_alias = -1
    p_is_created = false
endFunction

function f_Register()
    ; registering mod events is global for each script on an object, and
    ; further, works for handlers labeled as function as well as event.
    
    RegisterForModEvent("doticu_npcp_load_mod", "On_Load_Mod")
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
    RegisterForModEvent("doticu_npcp_followers_catch_up", "On_Followers_Catch_Up")

    p_Register_Queues()
endFunction

function f_Unregister()
    UnregisterForAllModEvents()
endFunction

function f_Lock_Resources()
    p_ref_member.f_Lock_Resources()
endFunction

function f_Unlock_Resources()
    p_ref_member.f_Unlock_Resources()
endFunction

function f_Enforce()
    p_Enqueue("Follower.Token")
    p_Enqueue("Follower.Follow")
    p_Enqueue("Follower.Level")
    if Is_Sneak()
        p_Enqueue("Follower.Sneak")
    else
        p_Enqueue("Follower.Unsneak")
    endIf
endFunction

; Private Methods
function p_Register_Queues()
    f_QUEUE.Register_Alias(self, "On_Queue_Follower", p_str_namespace)
endFunction

function p_Enqueue(string str_message, float float_interval = -1.0, bool allow_repeat = false)
    f_QUEUE.Enqueue(str_message, float_interval, p_str_namespace, allow_repeat)
endFunction

function p_Rush(string str_message)
    f_QUEUE.Rush(str_message, p_str_namespace)
endFunction

function p_Backup()
    f_Lock_Resources()

    p_prev_relationship_rank = p_ref_actor.GetRelationshipRank(CONSTS.ACTOR_PLAYER)
    p_prev_waiting_for_player = p_ref_actor.GetBaseActorValue("WaitingForPlayer")
    p_prev_aggression = p_ref_actor.GetBaseActorValue("Aggression")
    p_prev_confidence = p_ref_actor.GetBaseActorValue("Confidence")
    p_prev_assistance = p_ref_actor.GetBaseActorValue("Assistance"); this may need to go on Member
    p_prev_morality = p_ref_actor.GetBaseActorValue("Morality")
    p_prev_speed_mult = p_ref_actor.GetBaseActorValue("SpeedMult")

    p_prev_health = p_ref_actor.GetBaseActorValue(CONSTS.STR_HEALTH)
    p_prev_magicka = p_ref_actor.GetBaseActorValue(CONSTS.STR_MAGICKA)
    p_prev_stamina = p_ref_actor.GetBaseActorValue(CONSTS.STR_STAMINA)
    p_prev_one_handed = p_ref_actor.GetBaseActorValue(CONSTS.STR_ONE_HANDED)
    p_prev_two_handed = p_ref_actor.GetBaseActorValue(CONSTS.STR_TWO_HANDED)
    p_prev_block = p_ref_actor.GetBaseActorValue(CONSTS.STR_BLOCK)
    p_prev_heavy_armor = p_ref_actor.GetBaseActorValue(CONSTS.STR_HEAVY_ARMOR)
    p_prev_light_armor = p_ref_actor.GetBaseActorValue(CONSTS.STR_LIGHT_ARMOR)
    p_prev_smithing = p_ref_actor.GetBaseActorValue(CONSTS.STR_SMITHING)
    p_prev_destruction = p_ref_actor.GetBaseActorValue(CONSTS.STR_DESTRUCTION)
    p_prev_restoration = p_ref_actor.GetBaseActorValue(CONSTS.STR_RESTORATION)
    p_prev_conjuration = p_ref_actor.GetBaseActorValue(CONSTS.STR_CONJURATION)
    p_prev_alteration = p_ref_actor.GetBaseActorValue(CONSTS.STR_ALTERATION)
    p_prev_illusion = p_ref_actor.GetBaseActorValue(CONSTS.STR_ILLUSION)
    p_prev_enchanting = p_ref_actor.GetBaseActorValue(CONSTS.STR_ENCHANTING)
    p_prev_marksman = p_ref_actor.GetBaseActorValue(CONSTS.STR_MARKSMAN)
    p_prev_sneak = p_ref_actor.GetBaseActorValue(CONSTS.STR_SNEAK)
    p_prev_alchemy = p_ref_actor.GetBaseActorValue(CONSTS.STR_ALCHEMY)
    p_prev_lockpicking = p_ref_actor.GetBaseActorValue(CONSTS.STR_LOCKPICKING)
    p_prev_pickpocket = p_ref_actor.GetBaseActorValue(CONSTS.STR_PICKPOCKET)
    p_prev_speechcraft = p_ref_actor.GetBaseActorValue(CONSTS.STR_SPEECHCRAFT)

    f_Unlock_Resources()
endFunction

function p_Restore()
    f_Lock_Resources()

    p_ref_actor.SetActorValue(CONSTS.STR_SPEECHCRAFT, p_prev_speechcraft)
    p_ref_actor.SetActorValue(CONSTS.STR_PICKPOCKET, p_prev_pickpocket)
    p_ref_actor.SetActorValue(CONSTS.STR_LOCKPICKING, p_prev_lockpicking)
    p_ref_actor.SetActorValue(CONSTS.STR_ALCHEMY, p_prev_alchemy)
    p_ref_actor.SetActorValue(CONSTS.STR_SNEAK, p_prev_sneak)
    p_ref_actor.SetActorValue(CONSTS.STR_MARKSMAN, p_prev_marksman)
    p_ref_actor.SetActorValue(CONSTS.STR_ENCHANTING, p_prev_enchanting)
    p_ref_actor.SetActorValue(CONSTS.STR_ILLUSION, p_prev_illusion)
    p_ref_actor.SetActorValue(CONSTS.STR_ALTERATION, p_prev_alteration)
    p_ref_actor.SetActorValue(CONSTS.STR_CONJURATION, p_prev_conjuration)
    p_ref_actor.SetActorValue(CONSTS.STR_RESTORATION, p_prev_restoration)
    p_ref_actor.SetActorValue(CONSTS.STR_DESTRUCTION, p_prev_destruction)
    p_ref_actor.SetActorValue(CONSTS.STR_SMITHING, p_prev_smithing)
    p_ref_actor.SetActorValue(CONSTS.STR_LIGHT_ARMOR, p_prev_light_armor)
    p_ref_actor.SetActorValue(CONSTS.STR_HEAVY_ARMOR, p_prev_heavy_armor)
    p_ref_actor.SetActorValue(CONSTS.STR_BLOCK, p_prev_block)
    p_ref_actor.SetActorValue(CONSTS.STR_TWO_HANDED, p_prev_two_handed)
    p_ref_actor.SetActorValue(CONSTS.STR_ONE_HANDED, p_prev_one_handed)
    p_ref_actor.SetActorValue(CONSTS.STR_STAMINA, p_prev_stamina)
    p_ref_actor.SetActorValue(CONSTS.STR_MAGICKA, p_prev_magicka)
    p_ref_actor.SetActorValue(CONSTS.STR_HEALTH, p_prev_health)

    p_ref_actor.SetActorValue("SpeedMult", p_prev_speed_mult)
    p_ref_actor.SetActorValue("Morality", p_prev_morality)
    p_ref_actor.SetActorValue("Assistance", p_prev_assistance); this may need to go on Member
    p_ref_actor.SetActorValue("Confidence", p_prev_confidence)
    p_ref_actor.SetActorValue("Aggression", 0.0)
    p_ref_actor.SetActorValue("WaitingForPlayer", p_prev_waiting_for_player)

    f_Unlock_Resources()
endFunction

function p_Follow()
    f_Lock_Resources()

        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_FOLLOWER, p_id_alias + 1)

        CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)
        p_ref_actor.SetRelationshipRank(CONSTS.ACTOR_PLAYER, 3)
        p_ref_actor.SetPlayerTeammate(true, true)
        p_ref_actor.IgnoreFriendlyHits(true)
        p_ref_actor.SetNotShowOnStealthMeter(true)
        ;p_ref_actor.AllowPCDialogue(true)
        p_ref_actor.SetActorValue("WaitingForPlayer", 0.0)
        p_ref_actor.SetActorValue("Aggression", 0.0)
        p_ref_actor.SetActorValue("Confidence", 4.0)
        p_ref_actor.SetActorValue("Assistance", 2.0); this may need to go on Member
        p_ref_actor.SetActorValue("Morality", 0.0)
        p_ref_actor.SetActorValue("SpeedMult", MAX_SPEED_UNSNEAK)

        ; we also need to figure out how to deal with traps

        p_ref_actor.EvaluatePackage()

    f_Unlock_Resources()
endFunction

function p_Unfollow()
    f_Lock_Resources()

        p_ref_actor.SetNotShowOnStealthMeter(false)
        p_ref_actor.IgnoreFriendlyHits(false)
        p_ref_actor.SetPlayerTeammate(false, false)
        p_ref_actor.SetRelationshipRank(CONSTS.ACTOR_PLAYER, p_prev_relationship_rank)

        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_FOLLOWER)

        p_ref_actor.EvaluatePackage()

    f_Unlock_Resources()
endFunction

function p_Sneak()
    f_Lock_Resources()

        ; if possible, I want this function to make the followers completely undetectable.
        ; maybe an invisibility spell without the visual effect, if possible? not sure

        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_FOLLOWER_SNEAK)

        p_ref_actor.SetActorValue("SpeedMult", MAX_SPEED_SNEAK)

    f_Unlock_Resources()
endFunction

function p_Unsneak()
    f_Lock_Resources()

        p_ref_actor.SetActorValue("SpeedMult", MAX_SPEED_UNSNEAK)

        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_FOLLOWER_SNEAK)

    f_Unlock_Resources()
endFunction

function p_Level()
    f_Lock_Resources()

    int style_member = p_ref_member.Get_Style()
    int level_player = CONSTS.ACTOR_PLAYER.GetLevel()
    if style_member == p_style_follower && level_player == p_level_follower
        f_Unlock_Resources()
        return
    endIf
    p_style_follower = style_member
    p_level_follower = level_player

    float modifier = 0.67 - (Math.Log(level_player) * 0.067)
    float max_attribute = 1000
    float min_attribute = 100
    float max_skill = 100
    float min_skill = 0

    float health        = p_prev_health         + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_HEALTH)       * modifier
    float magicka       = p_prev_magicka        + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_MAGICKA)      * modifier
    float stamina       = p_prev_stamina        + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_STAMINA)      * modifier

    float one_handed    = p_prev_one_handed     + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_ONE_HANDED)   * modifier
    float two_handed    = p_prev_two_handed     + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_TWO_HANDED)   * modifier
    float block         = p_prev_block          + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_BLOCK)        * modifier
    float heavy_armor   = p_prev_heavy_armor    + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_HEAVY_ARMOR)  * modifier
    float light_armor   = p_prev_light_armor    + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_LIGHT_ARMOR)  * modifier
    float smithing      = p_prev_smithing       + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_SMITHING)     * modifier

    float destruction   = p_prev_destruction    + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_DESTRUCTION)  * modifier
    float restoration   = p_prev_restoration    + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_RESTORATION)  * modifier
    float conjuration   = p_prev_conjuration    + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_CONJURATION)  * modifier
    float alteration    = p_prev_alteration     + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_ALTERATION)   * modifier
    float illusion      = p_prev_illusion       + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_ILLUSION)     * modifier
    float enchanting    = p_prev_enchanting     + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_ENCHANTING)   * modifier

    float marksman      = p_prev_marksman       + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_MARKSMAN)     * modifier
    float sneak         = p_prev_sneak          + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_SNEAK)        * modifier
    float alchemy       = p_prev_alchemy        + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_ALCHEMY)      * modifier
    float lockpicking   = p_prev_lockpicking    + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_LOCKPICKING)  * modifier
    float pickpocket    = p_prev_pickpocket     + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_PICKPOCKET)   * modifier
    float speechcraft   = p_prev_speechcraft    + ACTOR_PLAYER.GetBaseActorValue(CONSTS.STR_SPEECHCRAFT)  * modifier

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

    p_ref_actor.SetActorValue(CONSTS.STR_HEALTH, health)
    p_ref_actor.SetActorValue(CONSTS.STR_MAGICKA, magicka)
    p_ref_actor.SetActorValue(CONSTS.STR_STAMINA, stamina)

    p_ref_actor.SetActorValue(CONSTS.STR_ONE_HANDED, one_handed)
    p_ref_actor.SetActorValue(CONSTS.STR_TWO_HANDED, two_handed)
    p_ref_actor.SetActorValue(CONSTS.STR_BLOCK, block)
    p_ref_actor.SetActorValue(CONSTS.STR_HEAVY_ARMOR, heavy_armor)
    p_ref_actor.SetActorValue(CONSTS.STR_LIGHT_ARMOR, light_armor)
    p_ref_actor.SetActorValue(CONSTS.STR_SMITHING, smithing)

    p_ref_actor.SetActorValue(CONSTS.STR_DESTRUCTION, destruction)
    p_ref_actor.SetActorValue(CONSTS.STR_RESTORATION, restoration)
    p_ref_actor.SetActorValue(CONSTS.STR_CONJURATION, conjuration)
    p_ref_actor.SetActorValue(CONSTS.STR_ALTERATION, alteration)
    p_ref_actor.SetActorValue(CONSTS.STR_ILLUSION, illusion)
    p_ref_actor.SetActorValue(CONSTS.STR_ENCHANTING, enchanting)

    p_ref_actor.SetActorValue(CONSTS.STR_MARKSMAN, marksman)
    p_ref_actor.SetActorValue(CONSTS.STR_SNEAK, sneak)
    p_ref_actor.SetActorValue(CONSTS.STR_ALCHEMY, alchemy)
    p_ref_actor.SetActorValue(CONSTS.STR_LOCKPICKING, lockpicking)
    p_ref_actor.SetActorValue(CONSTS.STR_PICKPOCKET, pickpocket)
    p_ref_actor.SetActorValue(CONSTS.STR_SPEECHCRAFT, speechcraft)

    f_Unlock_Resources()
endFunction

function p_Unlevel()
    f_Lock_Resources()

        p_level_follower = -1

    f_Unlock_Resources()
endFunction

function p_Relevel()
    p_Unlevel()
    p_Level()
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

int function Set_Name(string str_name)
    int code_return

    code_return = p_ref_member.Set_Name(str_name)
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Sneak(int code_exec)
    int code_return

    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if Is_Sneak()
        return CODES.IS_SNEAK
    endIf

    p_is_sneak = true

    if code_exec == CODES.DO_ASYNC
        p_Enqueue("Follower.Sneak")
    else
        p_Sneak()
    endIf

    return CODES.SUCCESS
endFunction

int function Unsneak(int code_exec)
    int code_return

    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if Is_Unsneak()
        return CODES.ISNT_SNEAK
    endIf

    p_is_sneak = false

    if code_exec == CODES.DO_ASYNC
        p_Enqueue("Follower.Unsneak")
    else
        p_Unsneak()
    endIf

    return CODES.SUCCESS
endFunction

int function Relevel(int code_exec)
    int code_return

    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if code_exec == CODES.DO_ASYNC
        p_Enqueue("Follower.Relevel")
    else
        p_Relevel()
    endIf

    return CODES.SUCCESS
endFunction

int function Catch_Up()
    int code_return

    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if !ACTORS.Is_Near_Player(p_ref_actor, 2048)
        Summon_Behind()
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unfollow(int code_exec)
    return p_ref_member.Unfollow(code_exec)
endFunction

int function Pack(int code_exec)
    return p_ref_member.Pack(code_exec)
endFunction

int function Settle(int code_exec)
    if Is_Settler()
        return p_ref_member.Resettle(code_exec)
    else
        return p_ref_member.Settle(code_exec)
    endIf
endFunction

int function Unsettle(int code_exec)
    return p_ref_member.Unsettle(code_exec)
endFunction

int function Immobilize(int code_exec)
    return p_ref_member.Immobilize(code_exec)
endFunction

int function Mobilize(int code_exec)
    return p_ref_member.Mobilize(code_exec)
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

bool function Is_In_Combat()
    return Exists() && p_ref_member.Is_In_Combat()
endFunction

bool function Is_Alive()
    return Exists() && ACTORS.Is_Alive(p_ref_actor)
endFunction

bool function Is_Dead()
    return Exists() && ACTORS.Is_Dead(p_ref_actor)
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

function Resurrect(int code_exec)
    p_ref_member.Resurrect(code_exec)
endFunction

; Events
event On_Queue_Follower(string str_message)
    if false

    elseIf str_message == "Follower.Backup"
        p_Backup()
    elseIf str_message == "Follower.Follow"
        p_Follow()
    elseIf str_message == "Follower.Level"
        p_Level()
    elseIf str_message == "Follower.Relevel"
        p_Relevel()
    elseIf str_message == "Follower.Sneak"
        if Is_Sneak()
            p_Sneak()
        endIf
    elseIf str_message == "Follower.Unsneak"
        if Is_Unsneak()
            p_Unsneak()
        endIf

    endIf

    f_QUEUE.Dequeue()
endEvent

event OnCombatStateChanged(Actor ref_target, int code_combat)
    if code_combat == CODES.COMBAT_NO
        
    elseIf code_combat == CODES.COMBAT_YES
        ACTORS.PLAYER.f_Begin_Combat()
    elseIf code_combat == CODES.COMBAT_SEARCHING

    endIf
endEvent

event OnDeath(Actor ref_killer)
    p_Unlevel()
endEvent

; need to add the catch up function, when player pulls out their weapon. but make it parallel this time.
; it's RegisterForActorAction

event On_Load_Mod()
    if Exists()
        p_Follow()
    endIf
endEvent

event On_Followers_Enforce(Form form_tasklist)
    if Exists()
        Enforce()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Settle(Form form_tasklist)
    if Exists()
        Settle(CODES.DO_SYNC)
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Unsettle(Form form_tasklist)
    if Exists() && Is_Settler()
        Unsettle(CODES.DO_SYNC)
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Immobilize(Form form_tasklist)
    if Exists() && Is_Mobile()
        Immobilize(CODES.DO_SYNC)
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Mobilize(Form form_tasklist)
    if Exists() && Is_Immobile()
        Mobilize(CODES.DO_SYNC)
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Sneak(Form form_tasklist)
    if Exists() && Is_Unsneak()
        Sneak(CODES.DO_SYNC)
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Unsneak(Form form_tasklist)
    if Exists() && Is_Sneak()
        Unsneak(CODES.DO_SYNC)
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Resurrect(Form form_tasklist)
    if Exists() && Is_Dead()
        Resurrect(CODES.DO_SYNC)
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Unfollow(Form form_tasklist)
    if Exists()
        Unfollow(CODES.DO_SYNC)
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Unmember(Form form_tasklist)
    if Exists()
        Unmember()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent

event On_Followers_Catch_Up(Form form_tasklist)
    if Exists()
        Catch_Up()
        (form_tasklist as doticu_npcp_tasklist).Detask()
    endIf
endEvent
