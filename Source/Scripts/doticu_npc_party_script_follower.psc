Scriptname doticu_npc_party_script_follower extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      CONSTS      = none
doticu_npc_party_script_codes       CODES       = none
doticu_npc_party_script_vars        VARS        = none
doticu_npc_party_script_mods        MODS        = none
doticu_npc_party_script_actor       ACTOR2      = none
int                                 ID_ALIAS    =   -1

; Private Variables
bool                            is_created              = false
Actor                           ref_actor               =  none
doticu_npc_party_script_member  ref_member              =  none
bool                            is_sneak                = false
int                             prev_relationship_rank  =    -1

; Private Methods
function p_Backup()
    prev_relationship_rank = ref_actor.GetRelationshipRank(CONSTS.ACTOR_PLAYER)
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
endFunction

function p_Unfollow()
    ref_actor.IgnoreFriendlyHits(false)
    ref_actor.SetPlayerTeammate(false, false)
    ref_actor.SetRelationshipRank(CONSTS.ACTOR_PLAYER, prev_relationship_rank)
endFunction

function p_Sneak()
endFunction

function p_Unsneak()
endFunction

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int IDX_ALIAS)
    CONSTS = DATA.CONSTS
    CODES = DATA.CODES
    VARS = DATA.VARS
    MODS = DATA.MODS
    ACTOR2 = DATA.MODS.FUNCS.ACTOR2
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

doticu_npc_party_script_member function Get_Member()
    if !Exists() || !ref_member.Exists()
        return none
    else
        return ref_member
    endIf
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

bool function Is_Sneak()
    return is_sneak
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
