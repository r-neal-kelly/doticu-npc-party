;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

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
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return p_DATA.VARS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_player property PLAYER hidden
    doticu_npcp_player function Get()
        return p_DATA.MODS.FUNCS.ACTORS.PLAYER
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

; Public Constants
Actor property ACTOR_PLAYER hidden
    Actor function Get()
        return p_DATA.CONSTS.ACTOR_PLAYER
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
bool                    p_is_locked                 = false
bool                    p_is_created                = false
Actor                   p_ref_actor                 =  none
doticu_npcp_member      p_ref_member                =  none
doticu_npcp_horse       p_ref_horse                 =  none
bool                    p_is_sneak                  = false
bool                    p_is_saddler                = false
bool                    p_is_retreater              = false

int                     p_prev_relationship_rank    =    -1
float                   p_prev_waiting_for_player   =  -1.0
float                   p_prev_speed_mult           =  -1.0
bool                    p_prev_faction_bard_no_auto = false

; Native Methods
Actor function Actor() native
int function ID() native

string function Name() native

function p_Level() native
function p_Unlevel() native
function p_Sneak() native
function p_Unsneak() native

function p_Rename(string new_name) native

; Friend Methods
function f_Create(doticu_npcp_data DATA, Actor ref_actor)
    p_DATA = DATA

p_Lock()
    ForceRefTo(ref_actor)

    p_is_created = true
    p_ref_actor = ref_actor
    p_ref_member = MEMBERS.Get_Member(p_ref_actor)
    p_ref_horse = none
    p_is_sneak = false
    p_is_retreater = false
p_Unlock()

    p_Backup()
    ACTORS.Stop_If_Playing_Music(p_ref_actor)

    p_Follow()
p_Lock()
    p_Level()
p_Unlock()
endFunction

function f_Destroy()
    if p_is_saddler
        p_Unsaddle()
    endIf
    if p_is_retreater
        p_Unretreat()
    endIf
    if p_is_sneak
        p_Unsneak()
    endIf
p_Lock()
    p_Unlevel()
p_Unlock()
    p_Unfollow()
    
    p_Restore()

p_Lock()
    if p_ref_horse
        p_Destroy_Horse()
    endIf

    p_prev_faction_bard_no_auto = false
    p_prev_speed_mult = -1.0
    p_prev_waiting_for_player = -1.0
    p_prev_relationship_rank = -1

    p_is_retreater = false
    p_is_sneak = false
    p_ref_horse = none
    p_ref_member = none
    p_ref_actor = none
    p_is_created = false

    Clear()
p_Unlock()
endFunction

function f_Register()
    ; is this necessary? prob. not
    RegisterForModEvent("doticu_npcp_cell_change", "On_Cell_Change")
endFunction

function f_Unregister()
    UnregisterForAllModEvents()
endFunction

function f_Enforce()
    if !Exists()
        return
    endIf

    p_Follow()

p_Lock()
    p_Level()
p_Unlock()

    if !Exists()
        return
    endIf

    if Is_Retreater()
        p_Retreat()
    else
        p_Unretreat()
    endIf

    if !Exists()
        return
    endIf

    if Is_Sneak()
        p_Sneak()
    else
        p_Unsneak()
    endIf

    if Is_Saddler()
        p_Saddle()
    else
        p_Unsaddle()
    endIf
endFunction

; Private Methods
function p_Lock(float interval = 0.2, float timeout = 6.0)
    float time_waited = 0.0

    while p_is_locked && time_waited < timeout
        FUNCS.Wait(interval)
        time_waited += interval
    endWhile

    p_is_locked = true
endFunction

function p_Unlock()
    p_is_locked = false
endFunction

function p_Backup()
p_Lock()

    p_prev_relationship_rank = p_ref_actor.GetRelationshipRank(CONSTS.ACTOR_PLAYER)
    p_prev_waiting_for_player = p_ref_actor.GetBaseActorValue("WaitingForPlayer")
    p_prev_speed_mult = p_ref_actor.GetBaseActorValue("SpeedMult")
    p_prev_faction_bard_no_auto = p_ref_actor.IsInFaction(CONSTS.FACTION_BARD_SINGER_NO_AUTOSTART)

p_Unlock()
endFunction

function p_Restore()
p_Lock()

    if p_prev_faction_bard_no_auto
        p_ref_actor.AddToFaction(CONSTS.FACTION_BARD_SINGER_NO_AUTOSTART)
    endIf
    p_ref_actor.SetActorValue("SpeedMult", p_prev_speed_mult)
    p_ref_actor.SetActorValue("WaitingForPlayer", p_prev_waiting_for_player)

p_Unlock()
endFunction

function p_Create_Horse()
    if !p_ref_horse
        int id_horse = FOLLOWERS.Max() + ID()
        p_ref_horse = (FOLLOWERS.GetNthAlias(id_horse) as doticu_npcp_horse)
        p_ref_horse.f_Create(p_DATA, id_horse, self)
    endIf
endFunction

function p_Destroy_Horse()
    if p_ref_horse
        p_ref_horse.f_Destroy()
        p_ref_horse = none
    endIf
endFunction

function p_Follow()
p_Lock()

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_FOLLOWER, ID() + 1)

    CONSTS.GLOBAL_PLAYER_FOLLOWER_COUNT.SetValue(1)

    ; we can't do away with this, because it controls dialogue api in mods.
    ; however, maybe we could set it dynamically somehow?
    p_ref_actor.SetRelationshipRank(CONSTS.ACTOR_PLAYER, 3)

    p_ref_actor.IgnoreFriendlyHits(true)
    p_ref_actor.SetNotShowOnStealthMeter(true)

    p_ref_actor.AddToFaction(CONSTS.FACTION_BARD_SINGER_NO_AUTOSTART)

    p_ref_actor.SetActorValue("WaitingForPlayer", 0.0); we don't use the vanilla wait, but immobilize
    p_ref_actor.SetActorValue("SpeedMult", MAX_SPEED_UNSNEAK)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Unfollow()
p_Lock()

    p_ref_actor.RemoveFromFaction(CONSTS.FACTION_BARD_SINGER_NO_AUTOSTART)

    p_ref_actor.SetNotShowOnStealthMeter(false)
    p_ref_actor.IgnoreFriendlyHits(false)
    p_ref_actor.SetRelationshipRank(CONSTS.ACTOR_PLAYER, p_prev_relationship_rank)

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_FOLLOWER)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Saddle()
p_Lock()

    if !p_ref_horse
        p_Create_Horse()
    endIf

    if CONSTS.ACTOR_PLAYER.GetParentCell().IsInterior()
p_Unlock()
        return p_Unsaddle()
    endIf

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_SADDLER)

    Actor ref_horse = p_ref_horse.Actor()

    ref_horse.Enable()
    ref_horse.IgnoreFriendlyHits(true)
    ref_horse.SetNotShowOnStealthMeter(true)
    ref_horse.AllowPCDialogue(false)
    ref_horse.SetActorValue("SpeedMult", MAX_SPEED_UNSNEAK)

    ; we need to support leveled bases (members) as opposed to real bases (clones) only
    ; because this takes an actor base, we can't specify a reference clone in this manner.
    ; so anything we can do to avoid the follower not being on the right horse is advisable
    ref_horse.SetActorOwner(ACTORS.Get_Leveled_Base(p_ref_actor))

    if ref_horse.IsDead()
        ref_horse.Resurrect()
    endIf

    if ref_horse.GetParentCell() != p_ref_actor.GetParentCell()
        ACTORS.Move_To(ref_horse, p_ref_actor, 140, -90)
    endIf

    Actor mounted_actor = doticu_npcp.Actor_Get_Mounted_Actor(ref_horse)
    if !mounted_actor || mounted_actor != p_ref_actor
        (CONSTS.FORMLIST_GLOBALS_SADDLER_IS_SITTING.GetAt(ID()) as GlobalVariable).SetValue(0)
    endIf

    p_ref_actor.EvaluatePackage()
    ref_horse.EvaluatePackage()

p_Unlock()
endFunction

function p_Unsaddle()
p_Lock()

    if p_ref_actor.IsOnMount()
        p_ref_actor.Dismount()
    endIf

    if p_ref_horse
        Actor ref_horse = p_ref_horse.Actor()
        ref_horse.Disable()
        ref_horse.MoveTo(CONSTS.MARKER_STORAGE)
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_SADDLER)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Retreat()
    ; this is kinda a hack to make sure that they don't get stuck as a retreater.
    ; it becomes very obvious when they won't get on their horses for example
    if !CONSTS.ACTOR_PLAYER.IsSneaking()
        p_is_retreater = false
        return p_Unretreat()
    endIf

p_Lock()

    ; this will cause a package change, where ref ignores combat
    ACTORS.TOKEN(p_ref_actor, CONSTS.TOKEN_RETREATER)

    ; add a spell that immediately causes invisibility.
    ; sometimes it won't work correctly, so check that it does
    while !p_ref_actor.HasMagicEffect(CONSTS.EFFECT_RETREAT)
        ACTORS.Apply_Ability(p_ref_actor, CONSTS.ABILITY_RETREAT)
    endWhile

    ; make sure there is no fighting
    ACTORS.Pacify(p_ref_actor)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Unretreat()
p_Lock()

    ACTORS.Unapply_Ability(p_ref_actor, CONSTS.ABILITY_RETREAT)

    ACTORS.UNTOKEN(p_ref_actor, CONSTS.TOKEN_RETREATER)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Async(string str_func)
    string str_event = "doticu_npcp_follower_async_" + ID()

p_Lock()
    RegisterForModEvent(str_event, str_func)
    FUNCS.Send_Event(str_event, 0.25, 5.0)
    UnregisterForModEvent(str_event)
p_Unlock()
endFunction

; Public Methods
function Enforce()
    p_ref_member.Enforce()
endFunction

bool function Exists()
    return p_is_created
endFunction

doticu_npcp_member function Get_Member()
    if !Exists() || !p_ref_member.Exists()
        return none
    else
        return p_ref_member
    endIf
endFunction

int function Rename(string str_name)

    int code_return = p_ref_member.Rename(str_name)
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Sneak(int code_exec)
    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if Is_Sneak()
        return CODES.IS_SNEAK
    endIf

    p_is_sneak = true

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Sneak")
    else
        p_Sneak()
    endIf

    return CODES.SUCCESS
endFunction
event On_Sneak()
    if Is_Sneak()
        p_Sneak()
    endIf
endEvent

int function Unsneak(int code_exec)
    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if Is_Unsneak()
        return CODES.ISNT_SNEAK
    endIf

    p_is_sneak = false

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Unsneak")
    else
        p_Unsneak()
    endIf

    return CODES.SUCCESS
endFunction
event On_Unsneak()
    if Is_Unsneak()
        p_Unsneak()
    endIf
endEvent

int function Saddle(int code_exec)
    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if Is_Saddler()
        return CODES.IS_SADDLER
    endIf

    if p_ref_actor.GetParentCell().IsInterior()
        return CODES.IS_INTERIOR
    endIf

    p_is_saddler = true

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Saddle")
    else
        p_Saddle()
    endIf

    return CODES.SUCCESS
endFunction
event On_Saddle()
    if Is_Saddler()
        p_Saddle()
    endIf
endEvent

int function Unsaddle(int code_exec)
    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    if Isnt_Saddler()
        return CODES.ISNT_SADDLER
    endIf

    p_is_saddler = false

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Unsaddle")
    else
        p_Unsaddle()
    endIf

    return CODES.SUCCESS
endFunction
event On_Unsaddle()
    if Isnt_Saddler()
        p_Unsaddle()
    endIf
endEvent

int function Retreat()
    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    p_is_retreater = true

    p_Retreat()

    return CODES.SUCCESS
endFunction

int function Unretreat()
    if !Exists()
        return CODES.ISNT_FOLLOWER
    endIf

    p_is_retreater = false

    p_Unretreat()

    return CODES.SUCCESS
endFunction

int function Unfollow()
    return p_ref_member.Unfollow()
endFunction

int function Pack(int code_exec)
    return p_ref_member.Pack(code_exec)
endFunction

int function Stash()
    return p_ref_member.Stash()
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

bool function Is_Saddler()
    return Exists() && p_is_saddler
endFunction

bool function Isnt_Saddler()
    return Exists() && !p_is_saddler
endFunction

bool function Is_Retreater()
    return Exists() && p_is_retreater
endFunction

bool function Isnt_Retreater()
    return Exists() && !p_is_retreater
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

bool function Is_Paralyzed()
    return Exists() && p_ref_member.Is_Paralyzed()
endFunction

bool function Is_Mannequin()
    return Exists() && p_ref_member.Is_Mannequin()
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

bool function Is_Styled_Coward()
    return Exists() && p_ref_member.Is_Styled_Coward()
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

function Summon_Ahead(int distance = 120)
    p_ref_member.Summon_Ahead(distance)
endFunction

function Summon_Behind(int distance = 120)
    p_ref_member.Summon_Behind(distance)
endFunction

function Resurrect(int code_exec)
    p_ref_member.Resurrect(code_exec)
endFunction

; Events
event OnCombatStateChanged(Actor ref_target, int code_combat)
    if VARS.is_updating
        return
    endIf

    if code_combat == CODES.COMBAT_NO
        
    elseIf code_combat == CODES.COMBAT_YES
        ACTORS.PLAYER.f_Begin_Combat()
    elseIf code_combat == CODES.COMBAT_SEARCHING

    endIf
endEvent

event On_Cell_Change(Form cell_new, Form cell_old)
    if Exists()
        p_Follow()
        if Is_Sneak()
            p_Sneak()
        endIf
    endIf
endEvent

event On_Followers_Enforce(Form form_tasklist)
    if Exists()
        Enforce()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Resurrect(Form form_tasklist)
    if Exists() && Is_Dead()
        Resurrect(CODES.DO_SYNC)
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Sneak(Form form_tasklist)
    if Exists() && Is_Unsneak()
        Sneak(CODES.DO_SYNC)
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unsneak(Form form_tasklist)
    if Exists() && Is_Sneak()
        Unsneak(CODES.DO_SYNC)
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Saddle(Form form_tasklist)
    if Exists() && Isnt_Saddler()
        Saddle(CODES.DO_SYNC)
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unsaddle(Form form_tasklist)
    if Exists() && Is_Saddler()
        Unsaddle(CODES.DO_SYNC)
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Retreat(Form form_tasklist)
    if Exists() && Isnt_Retreater()
        Retreat()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unretreat(Form form_tasklist)
    if Exists() && Is_Retreater()
        Unretreat()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unfollow(Form form_tasklist)
    if Exists()
        Unfollow()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent

event On_Followers_Unmember(Form form_tasklist)
    if Exists()
        Unmember()
        if form_tasklist
            (form_tasklist as doticu_npcp_tasklist).Detask()
        endIf
    endIf
endEvent
