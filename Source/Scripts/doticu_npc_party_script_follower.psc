Scriptname doticu_npc_party_script_follower extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
doticu_npc_party_script_followers   FOLLOWERS   = none
int                                 ID_ALIAS    =   -1

; Private Variables
bool                            is_created              = false
Actor                           ref_actor               =  none
doticu_npc_party_script_member  ref_member              =  none
bool                            is_sneak                = false
int                             prev_relationship_rank  =    -1
float                           prev_aggression         =  -1.0
float                           prev_confidence         =  -1.0
float                           prev_assistance         =  -1.0; this may need to go on Member
float                           prev_morality           =  -1.0

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int IDX_ALIAS)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    FOLLOWERS = DATA.MODS.FOLLOWERS
    ID_ALIAS = IDX_ALIAS
endFunction

int function f_Enforce()
    int code_return

    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    code_return = ref_member.f_Enforce()
    if code_return < 0
        return code_return
    endIf

    p_Token()
    p_Follow()
    if is_sneak
        p_Sneak()
    endIf

    ref_actor.EvaluatePackage()

    return CODES.SUCCESS
endFunction

; Private Methods
function p_Backup()
    prev_relationship_rank = ref_actor.GetRelationshipRank(CONSTS.ACTOR_PLAYER)
    prev_aggression = ref_actor.GetBaseActorValue("Aggression")
    prev_confidence = ref_actor.GetBaseActorValue("Confidence")
    prev_assistance = ref_actor.GetBaseActorValue("Assistance"); this may need to go on Member
    prev_morality = ref_actor.GetBaseActorValue("Morality")
endFunction

; function p_Restore() ?

function p_Token()
    ACTOR2.Token(ref_actor, CONSTS.TOKEN_FOLLOWER, ID_ALIAS + 1)
    if is_sneak
        ACTOR2.Token(ref_actor, CONSTS.TOKEN_FOLLOWER_SNEAK)
    else
        ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_FOLLOWER_SNEAK)
    endIf
endFunction

function p_Untoken()
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_FOLLOWER_SNEAK)
    ACTOR2.Untoken(ref_actor, CONSTS.TOKEN_FOLLOWER)
endFunction

function p_Follow()
    CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)
    ref_actor.SetRelationshipRank(CONSTS.ACTOR_PLAYER, 3)
    ref_actor.SetPlayerTeammate(true, true)
    ref_actor.IgnoreFriendlyHits(true)
    ref_actor.SetNotShowOnStealthMeter(true)
    ref_actor.SetActorValue("Aggression", 0.0)
    ref_actor.SetActorValue("Confidence", 4.0)
    ref_actor.SetActorValue("Assistance", 2.0); this may need to go on Member
    ref_actor.SetActorValue("Morality", 0.0)

    ; need to calc values, at least when it seems they should be, like if the player leveled.

    ; will want to add to CurrentFollowerFaction?
    ; or completely remove it from the npc?
    ; or disable the vanilla follower dialogue?
    ; should we make our own with hard links?
endFunction

function p_Unfollow()
    ref_actor.SetActorValue("Morality", prev_morality)
    ref_actor.SetActorValue("Assistance", prev_assistance); this may need to go on Member
    ref_actor.SetActorValue("Confidence", prev_confidence)
    ref_actor.SetActorValue("Aggression", prev_aggression)
    ref_actor.SetNotShowOnStealthMeter(false)
    ref_actor.IgnoreFriendlyHits(false)
    ref_actor.SetPlayerTeammate(false, false)
    ref_actor.SetRelationshipRank(CONSTS.ACTOR_PLAYER, prev_relationship_rank)
endFunction

function p_Sneak()
endFunction

function p_Unsneak()
endFunction

; Public Methods
int function Create()
    int code_return

    if Exists()
        return CODES.IS_FOLLOWER
    endIf
    ref_actor = GetActorReference()
    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf
    ref_member = MODS.MEMBERS.Get_Member(ref_actor)
    if !ref_member
        return CODES.ISNT_MEMBER
    endIf
    is_created = true

    p_Backup()

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Destroy()
    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if is_sneak
        p_Unsneak()
    endIf
    p_Unfollow()
    p_Untoken()

    is_sneak = false
    ref_member = none
    ref_actor = none
    is_created = false

    return CODES.SUCCESS
endFunction

bool function Exists()
    return is_created
endFunction

string function Get_Name()
    return ref_member.Get_Name()
endFunction

Actor function Get_Actor()
    return ref_member.Get_Actor()
endFunction

doticu_npc_party_script_member function Get_Member()
    if !Exists() || !ref_member.Exists()
        return none
    else
        return ref_member
    endIf
endFunction

doticu_npc_party_script_settler function Get_Settler()
    return ref_member.Get_Settler()
endFunction

int function Set_Name(string str_name)
    return ref_member.Set_Name(str_name)
endFunction

int function Sneak()
    int code_return

    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if is_sneak
        return CODES.IS_SNEAK
    endIf

    is_sneak = true

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unsneak()
    int code_return

    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if !is_sneak
        return CODES.ISNT_SNEAK
    endIf

    is_sneak = false

    code_return = f_Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unfollow()
    int code_return

    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    return FOLLOWERS.Destroy_Follower(ref_actor)
endFunction

int function Access()
    return ref_member.Access(); doesn't currently f_Enforce follower
endFunction

int function Settle()
    return ref_member.Settle(); doesn't currently f_Enforce follower
endFunction

int function Unsettle()
    return ref_member.Unsettle(); doesn't currently f_Enforce follower
endFunction

int function Immobilize()
    return ref_member.Immobilize(); doesn't currently f_Enforce follower
endFunction

int function Mobilize()
    return ref_member.Mobilize(); doesn't currently f_Enforce follower
endFunction

int function Unmember()
    return ref_member.Unmember(); doesn't currently f_Enforce follower
endFunction

int function Unclone()
    return ref_member.Unclone(); doesn't currently f_Enforce follower
endFunction

bool function Is_Sneak()
    return is_sneak
endFunction

bool function Is_Settler()
    return ref_member.Is_Settler()
endFunction

bool function Is_Immobile()
    return ref_member.Is_Immobile()
endFunction

function Summon(int distance = 60, int angle = 0)
    ref_member.Summon(distance, angle)
endFunction

function Summon_Ahead()
    ref_member.Summon_Ahead()
endFunction

function Summon_Behind()
    ref_member.Summon_Behind()
endFunction

; Events
event OnActivate(ObjectReference ref_activator)
    f_Enforce()
endEvent

event OnCombatStateChanged(Actor ref_target, int code_combat)
    ; may want to put on member instead

    if ref_target == CONSTS.ACTOR_PLAYER
        ref_actor.StopCombat()
        ;ref_actor.StopCombatAlarm()
    endIf

    ; check for other members, if they have the member token, stop fighting them

    if code_combat == 0; Not in Combat
    elseIf code_combat == 1; In Combat
    elseIf code_combat == 2; Searching
    endIf
endEvent
