Scriptname doticu_npc_party_script_member extends ReferenceAlias

; Private Constants
doticu_npc_party_script_consts      p_CONSTS    = none
doticu_npc_party_script_codes       p_CODES     = none
doticu_npc_party_script_vars        p_VARS      = none
doticu_npc_party_script_actor       p_ACTOR2    = none
doticu_npc_party_script_members     p_MEMBERS   = none
doticu_npc_party_script_followers   p_FOLLOWERS = none
doticu_npc_party_script_player      p_PLAYER    = none
doticu_npc_party_script_settler     p_SETTLER   = none
doticu_npc_party_script_immobile    p_IMMOBILE  = none
int                                 p_ID_ALIAS  =   -1

; Private Variables
bool    p_is_created    = false
Actor   p_ref_actor     =  none
bool    p_is_clone      = false
bool    p_is_generic    = false
bool    p_is_thrall     = false
int     p_code_combat   =    -1

; Friend Methods
function f_Initialize(doticu_npc_party_script_data DATA, int IDX_ALIAS)
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_ACTOR2 = DATA.MODS.FUNCS.ACTOR2
    p_MEMBERS = DATA.MODS.MEMBERS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
    p_PLAYER = DATA.MODS.CONTROL.PLAYER
    p_SETTLER = (self as ReferenceAlias) as doticu_npc_party_script_settler
    p_IMMOBILE = (self as ReferenceAlias) as doticu_npc_party_script_immobile
    p_ID_ALIAS = IDX_ALIAS
endFunction

int function f_Create(bool is_a_clone)
    int code_return

    if Exists()
        return p_CODES.IS_MEMBER
    endIf
    p_ref_actor = GetActorReference()
    if !p_ref_actor
        return p_CODES.ISNT_ACTOR
    endIf
    if p_ACTOR2.Is_Dead(p_ref_actor)
        p_ACTOR2.Resurrect(p_ref_actor)
        if p_ACTOR2.Is_Dead(p_ref_actor)
            return p_CODES.CANT_RESURRECT
        endIf
    endIf

    p_is_created = true
    if is_a_clone
        p_is_clone = is_a_clone
    else
        p_is_clone = false
    endIf
    if p_ACTOR2.Is_Generic(p_ref_actor)
        p_is_generic = true
    else
        p_is_generic = false
    endIf
    p_code_combat = p_VARS.auto_style
    
    code_return = Enforce()
    if code_return < 0
        f_Destroy()
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function f_Destroy()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_FOLLOWERS.Has_Follower(p_ref_actor)
        code_return = Unfollow()
        if code_return < 0
            return code_return
        endIf
    endIf
    if p_IMMOBILE.Exists()
        code_return = Mobilize()
        if code_return < 0
            return code_return
        endIf
    endIf
    if p_SETTLER.Exists()
        code_return = Unsettle()
        if code_return < 0
            return code_return
        endIf
    endIf

    if p_is_thrall
        p_Unthrall()
    endIf
    p_Unmember()
    p_Untoken()

    p_code_combat = -1
    p_is_thrall = false
    p_is_generic = false
    p_is_clone = false
    p_ref_actor = none
    p_is_created = false

    return p_CODES.SUCCESS
endFunction

; Private Methods
function p_Token()
    p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_MEMBER, p_ID_ALIAS + 1)

    if p_is_clone
        p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_CLONE)
    else
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_CLONE)
    endIf

    if p_is_generic
        p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_GENERIC)
    else
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_GENERIC)
    endIf

    if p_is_thrall
        p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_THRALL)
    else
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_THRALL)
    endIf

    if p_code_combat == p_CODES.IS_WARRIOR
        p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_COMBAT_WARRIOR)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_DEFAULT)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_MAGE)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_ARCHER)
    elseIf p_code_combat == p_CODES.IS_MAGE
        p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_COMBAT_MAGE)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_DEFAULT)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_WARRIOR)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_ARCHER)
    elseIf p_code_combat == p_CODES.IS_ARCHER
        p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_COMBAT_ARCHER)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_DEFAULT)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_WARRIOR)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_MAGE)
    else
        p_ACTOR2.Token(p_ref_actor, p_CONSTS.TOKEN_COMBAT_DEFAULT)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_WARRIOR)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_MAGE)
        p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_ARCHER)
    endIf
endFunction

function p_Untoken()
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_ARCHER)
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_MAGE)
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_WARRIOR)
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_COMBAT_DEFAULT)
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_THRALL)
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_GENERIC)
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_CLONE)
    p_ACTOR2.Untoken(p_ref_actor, p_CONSTS.TOKEN_MEMBER)
endFunction

function p_Member()
    p_ref_actor.SetActorValue("Aggression", 0)
endFunction

function p_Unmember()
    p_ref_actor.SetActorValue("Aggression", 0)
endFunction

function p_Enthrall()
    ; also, we want to limit this to whether or not the pc is a vamp.
    
    ;p_ref_actor.AddToFaction(p_CONSTS.FACTION_DLC1_THRALL)
    p_ref_actor.AddToFaction(p_CONSTS.FACTION_DLC1_VAMPIRE_FEED_NO_CRIME)

    ; we need to investigate further how to stop the quest that has these topics
    ; from disallowing any other dialogue with the enthralled npc.
endFunction

function p_Unthrall()
    p_ref_actor.RemoveFromFaction(p_CONSTS.FACTION_DLC1_VAMPIRE_FEED_NO_CRIME)
    p_ref_actor.RemoveFromFaction(p_CONSTS.FACTION_DLC1_THRALL)
endFunction

; Public Methods
int function Enforce()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    p_Token()
    p_Member()
    if p_is_thrall
        p_Enthrall()
    endIf

    if p_SETTLER.Exists()
        code_return = p_SETTLER.f_Enforce()
        if code_return < 0
            return code_return
        endIf
    endIf
    if p_IMMOBILE.Exists()
        code_return = p_IMMOBILE.f_Enforce()
        if code_return < 0
            return code_return
        endIf
    endIf
    if p_FOLLOWERS.Has_Follower(p_ref_actor)
        code_return = p_Followers.Get_Follower(p_ref_actor).f_Enforce()
        if code_return < 0
            return code_return
        endIf
    endIf

    p_ref_actor.EvaluatePackage()

    return p_CODES.SUCCESS
endFunction

bool function Exists()
    return p_is_created
endFunction

string function Get_Name()
    return p_ACTOR2.Get_Name(p_ref_actor)
endFunction

Actor function Get_Actor()
    return p_ref_actor
endFunction

doticu_npc_party_script_settler function Get_Settler()
    if !Exists() || !p_SETTLER.Exists()
        return none
    else
        return p_SETTLER
    endIf
endFunction

doticu_npc_party_script_immobile function Get_Immobile()
    if !Exists() || !p_IMMOBILE.Exists()
        return none
    else
        return p_IMMOBILE
    endIf
endFunction

int function Get_Style()
    if !Exists()
        return -1
    else
        return p_code_combat
    endIf
endFunction

int function Set_Name(string str_name)
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    p_ACTOR2.Set_Name(p_ref_actor, str_name)

    if Get_Name() != str_name
        return p_CODES.CANT_RENAME
    endIf

    return p_CODES.SUCCESS
endFunction

int function Settle()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    code_return = p_SETTLER.f_Create()
    if code_return < 0
        return code_return
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unsettle()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    code_return = p_SETTLER.f_Destroy()
    if code_return < 0
        return code_return
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Immobilize()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    code_return = p_IMMOBILE.f_Create()
    if code_return < 0
        return code_return
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Mobilize()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    code_return = p_IMMOBILE.f_Destroy()
    if code_return < 0
        return code_return
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Follow()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    code_return = p_FOLLOWERS.f_Create_Follower(p_ref_actor)
    if code_return < 0
        return code_return
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unfollow()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    ; should check to see if is a follower, even though it's redundant

    code_return = p_FOLLOWERS.f_Destroy_Follower(p_ref_actor)
    if code_return < 0
        return code_return
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Enthrall()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_is_thrall
        return p_CODES.IS_THRALL
    endIf

    p_is_thrall = true

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unthrall()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if !p_is_thrall
        return p_CODES.ISNT_THRALL
    endIf

    p_is_thrall = false

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Style_Default()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_code_combat == p_CODES.IS_DEFAULT
        return p_CODES.IS_DEFAULT
    endIf

    p_code_combat = p_CODES.IS_DEFAULT

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Style_Warrior()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_code_combat == p_CODES.IS_WARRIOR
        return p_CODES.IS_WARRIOR
    endIf

    p_code_combat = p_CODES.IS_WARRIOR

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Style_Mage()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_code_combat == p_CODES.IS_MAGE
        return p_CODES.IS_MAGE
    endIf

    p_code_combat = p_CODES.IS_MAGE

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Style_Archer()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_code_combat == p_CODES.IS_ARCHER
        return p_CODES.IS_ARCHER
    endIf

    p_code_combat = p_CODES.IS_ARCHER

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Access()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf
    
    p_ACTOR2.Open_Inventory(p_ref_actor)

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unmember()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_MEMBERS.Should_Unclone_Actor(p_ref_actor)
        return Unclone()
    else
        return p_MEMBERS.Destroy_Member(p_ref_actor, false)
    endIf
endFunction

int function Clone()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    return p_MEMBERS.Create_Member(p_ref_actor, true)
endFunction

int function Unclone()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if !p_is_clone
        return p_CODES.ISNT_CLONE
    endIf

    return p_MEMBERS.Destroy_Member(p_ref_actor, true)
endFunction

bool function Is_Unique()
    return !p_is_generic
endFunction

bool function Is_Generic()
    return p_is_generic
endFunction

bool function Is_Member()
    return Exists()
endFunction

bool function Is_Settler()
    return p_SETTLER.Exists()
endFunction

bool function Is_Immobile()
    return p_IMMOBILE.Exists()
endFunction

bool function Is_Follower()
    return p_FOLLOWERS.Has_Follower(p_ref_actor)
endFunction

bool function Is_Clone()
    return p_is_clone
endFunction

bool function Is_Thrall()
    return p_is_thrall
endFunction

bool function Is_Styled_Default()
    return p_code_combat == p_CODES.IS_DEFAULT
endFunction

bool function Is_Styled_Warrior()
    return p_code_combat == p_CODES.IS_WARRIOR
endFunction

bool function Is_Styled_Mage()
    return p_code_combat == p_CODES.IS_MAGE
endFunction

bool function Is_Styled_Archer()
    return p_code_combat == p_CODES.IS_ARCHER
endFunction

function Summon(int distance = 60, int angle = 0)
    p_ACTOR2.Move_To(p_ref_actor, p_CONSTS.ACTOR_PLAYER, distance, angle)
endFunction

function Summon_Ahead()
    Summon(60, 0)
endFunction

function Summon_Behind()
    Summon(60, 180)
endFunction

; Events
event OnActivate(ObjectReference ref_activator)
    Enforce()
    ; maybe we could pop up some basic stats on screen
endEvent

event OnCombatStateChanged(Actor ref_target, int code_combat)
    if ref_target == p_CONSTS.ACTOR_PLAYER || p_ACTOR2.Has_Token(ref_target, p_CONSTS.TOKEN_MEMBER)
        p_ACTOR2.Pacify(p_ref_actor)
    endIf

    if code_combat == 0; Not in Combat
        Enforce()
    elseIf code_combat == 1; In Combat

    elseIf code_combat == 2; Searching
        Enforce(); this may be too intensive here
    endIf
endEvent
