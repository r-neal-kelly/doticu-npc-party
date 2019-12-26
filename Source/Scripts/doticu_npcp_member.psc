Scriptname doticu_npcp_member extends ReferenceAlias

; Private Constants
doticu_npcp_data        p_DATA                  =  none
doticu_npcp_consts      p_CONSTS                =  none
doticu_npcp_codes       p_CODES                 =  none
doticu_npcp_vars        p_VARS                  =  none
doticu_npcp_actors      p_ACTORS                =  none
doticu_npcp_containers  p_CONTAINERS            =  none
doticu_npcp_queues      p_QUEUES                =  none
doticu_npcp_outfits     p_OUTFITS               =  none
doticu_npcp_members     p_MEMBERS               =  none
doticu_npcp_followers   p_FOLLOWERS             =  none
doticu_npcp_player      p_PLAYER                =  none
doticu_npcp_settler     p_SETTLER               =  none
doticu_npcp_immobile    p_IMMOBILE              =  none

int                     p_ID_ALIAS              =    -1
Outfit                  p_OUTFIT                =  none

; Private Variables
bool                    p_is_created            = false
Actor                   p_ref_actor             =  none
bool                    p_is_clone              = false
bool                    p_is_generic            = false
bool                    p_is_thrall             = false
int                     p_code_style            =    -1
int                     p_code_vitality         =    -1
doticu_npcp_outfit      p_outfit2_member        =  none
doticu_npcp_queue       p_queue_member          =  none
doticu_npcp_container   p_container_pack        =  none

int                     p_prev_vitality         =    -1
doticu_npcp_outfit      p_prev_outfit2_member   =  none
; maybe should backup factions and restore them also. removing from all factions may make things cleaner.

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_DATA = DATA
    p_CONSTS = DATA.CONSTS
    p_CODES = DATA.CODES
    p_VARS = DATA.VARS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_CONTAINERS = DATA.MODS.FUNCS.CONTAINERS
    p_QUEUES = DATA.MODS.FUNCS.QUEUES
    p_OUTFITS = DATA.MODS.FUNCS.OUTFITS
    p_MEMBERS = DATA.MODS.MEMBERS
    p_FOLLOWERS = DATA.MODS.FOLLOWERS
    p_PLAYER = DATA.MODS.FUNCS.PLAYER
    p_SETTLER = (self as ReferenceAlias) as doticu_npcp_settler
    p_IMMOBILE = (self as ReferenceAlias) as doticu_npcp_immobile

    p_SETTLER.f_Link(DATA)
    p_IMMOBILE.f_Link(DATA)

    p_Link_Queues(DATA)
    p_Link_Outfits(DATA)
    p_Link_Containers(DATA)
endFunction

function f_Initialize(int ID_ALIAS)
    p_ID_ALIAS = ID_ALIAS
    p_OUTFIT = p_CONSTS.FORMLIST_OUTFITS.GetAt(ID_ALIAS) as Outfit

    p_SETTLER.f_Initialize(ID_ALIAS)
    p_IMMOBILE.f_Initialize(ID_ALIAS)
endFunction

function f_Register()
    RegisterForModEvent("doticu_npcp_members_unmember", "On_Members_Unmember")
    RegisterForModEvent("doticu_npcp_members_u_0_1_0", "u_0_1_0")
    RegisterForModEvent("doticu_npcp_members_u_0_1_1", "u_0_1_1")
    RegisterForModEvent("doticu_npcp_queue_" + "member_" + p_ID_ALIAS, "On_Queue_Member")

    p_SETTLER.f_Register()
    p_IMMOBILE.f_Register()

    p_Register_Queues()
    p_Register_Outfits()
    p_Register_Containers()
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
    if p_ACTORS.Is_Dead(p_ref_actor)
        p_ACTORS.Resurrect(p_ref_actor)
        if p_ACTORS.Is_Dead(p_ref_actor)
            return p_CODES.CANT_RESURRECT
        endIf
    endIf

    p_is_created = true
    if is_a_clone
        p_is_clone = is_a_clone
    else
        p_is_clone = false
    endIf
    if p_ACTORS.Is_Generic(p_ref_actor)
        p_is_generic = true
    else
        p_is_generic = false
    endIf
    p_code_style = p_VARS.auto_style
    p_code_vitality = p_VARS.auto_vitality

    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_MEMBER, p_ID_ALIAS + 1)
    p_ref_actor.EvaluatePackage()

    p_Create_Queues()
    p_Create_Outfits()
    p_Create_Containers()
    p_Backup()
    
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

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_MEMBER)
    p_ref_actor.EvaluatePackage()

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

    ;p_Unoutfit() Restore sets the original
    p_Unvitalize()
    p_Unstyle()
    if p_is_thrall
        p_Unthrall()
    endIf
    p_Unmember()
    p_Untoken()

    p_Restore()
    p_Destroy_Containers()
    p_Destroy_Outfits()
    p_Destroy_Queues()

    p_prev_outfit2_member = none
    p_prev_vitality = -1

    p_container_pack = none
    p_queue_member = none
    p_outfit2_member = none
    p_code_vitality = -1
    p_code_style = -1
    p_is_thrall = false
    p_is_generic = false
    p_is_clone = false
    p_ref_actor = none
    p_is_created = false

    return p_CODES.SUCCESS
endFunction

; Private Methods
function p_Link_Queues(doticu_npcp_data DATA)
    if p_queue_member
        p_queue_member.f_Link(DATA)
    endIf
endFunction

function p_Register_Queues()
    if p_queue_member
        p_queue_member.f_Register()
    endIf
endFunction

function p_Create_Queues()
    p_queue_member = p_QUEUES.Create("member_" + p_ID_ALIAS, 32, 0.5)
endFunction

function p_Destroy_Queues()
    p_QUEUES.Destroy(p_queue_member)
endFunction

function p_Link_Outfits(doticu_npcp_data DATA)
    if p_outfit2_member
        p_outfit2_member.f_Link(DATA)
    endIf
    if p_prev_outfit2_member
        p_prev_outfit2_member.f_Link(DATA)
    endIf
endFunction

function p_Register_Outfits()
    if p_outfit2_member
        p_outfit2_member.f_Register()
    endIf
    if p_prev_outfit2_member
        p_prev_outfit2_member.f_Register()
    endIf
endFunction

function p_Create_Outfits()
    p_outfit2_member = p_OUTFITS.Create(p_OUTFIT, p_ACTORS.Get_Name(p_ref_actor) + "'s Outfit")
    p_prev_outfit2_member = p_OUTFITS.Create(p_OUTFIT)

    p_outfit2_member.Get(p_ref_actor)
    p_prev_outfit2_member.Get(p_ref_actor)
endFunction

function p_Destroy_Outfits()
    p_OUTFITS.Destroy(p_prev_outfit2_member)
    p_OUTFITS.Destroy(p_outfit2_member)
endFunction

function p_Link_Containers(doticu_npcp_data DATA)
    if p_container_pack
        p_container_pack.f_Link(DATA)
    endIf
endFunction

function p_Register_Containers()
    if p_container_pack
        p_container_pack.f_Register()
    endIf
endFunction

function p_Create_Containers()
    p_container_pack = p_CONTAINERS.Create(p_ACTORS.Get_Name(p_ref_actor) + "'s Pack")
endFunction

function p_Destroy_Containers()
    p_container_pack.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)
    p_CONTAINERS.Destroy(p_container_pack)
endFunction

function p_Backup()
    p_prev_vitality = p_ACTORS.Get_Vitality(p_ref_actor)
endFunction

function p_Restore()
    p_prev_outfit2_member.Set(p_ref_actor); instead of this, we might set the outfit to GetOutfit on base actor
    p_ACTORS.Vitalize(p_ref_actor, p_prev_vitality)
endFunction

function p_Token()
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_MEMBER, p_ID_ALIAS + 1)

    if p_is_clone
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_CLONE)
    else
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_CLONE)
    endIf

    if p_is_generic
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_GENERIC)
    else
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_GENERIC)
    endIf

    if p_is_thrall
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_THRALL)
    else
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_THRALL)
    endIf

    if p_code_style == p_CODES.IS_WARRIOR
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_STYLE_WARRIOR)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_DEFAULT)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_MAGE)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_ARCHER)
    elseIf p_code_style == p_CODES.IS_MAGE
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_STYLE_MAGE)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_DEFAULT)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_WARRIOR)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_ARCHER)
    elseIf p_code_style == p_CODES.IS_ARCHER
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_STYLE_ARCHER)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_DEFAULT)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_WARRIOR)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_MAGE)
    else
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_STYLE_DEFAULT)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_WARRIOR)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_MAGE)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_ARCHER)
    endIf

    if p_code_vitality == p_CODES.IS_MORTAL
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_VITALITY_MORTAL)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_PROTECTED)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_ESSENTIAL)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_INVULNERABLE)
    elseIf p_code_vitality == p_CODES.IS_PROTECTED
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_MORTAL)
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_VITALITY_PROTECTED)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_ESSENTIAL)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_INVULNERABLE)
    elseIf p_code_vitality == p_CODES.IS_ESSENTIAL
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_MORTAL)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_PROTECTED)
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_VITALITY_ESSENTIAL)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_INVULNERABLE)
    elseIf p_code_vitality == p_CODES.IS_INVULNERABLE
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_MORTAL)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_PROTECTED)
        p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_ESSENTIAL)
        p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_VITALITY_INVULNERABLE)
    endIf

    p_ref_actor.EvaluatePackage()
endFunction

function p_Untoken()
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_INVULNERABLE)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_ESSENTIAL)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_PROTECTED)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_MORTAL)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_ARCHER)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_MAGE)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_WARRIOR)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_DEFAULT)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_THRALL)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_GENERIC)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_CLONE)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_MEMBER)

    p_ref_actor.EvaluatePackage()
endFunction

function p_Member()
    p_ref_actor.AddToFaction(p_CONSTS.FACTION_MEMBER)
    p_ref_actor.SetActorValue("Aggression", 0)
endFunction

function p_Unmember()
    p_ref_actor.SetActorValue("Aggression", 0)
    p_ref_actor.RemoveFromFaction(p_CONSTS.FACTION_MEMBER)
endFunction

function p_Enthrall()
    p_ref_actor.AddToFaction(p_CONSTS.FACTION_DLC1_VAMPIRE_FEED_NO_CRIME)
endFunction

function p_Unthrall()
    p_ref_actor.RemoveFromFaction(p_CONSTS.FACTION_DLC1_VAMPIRE_FEED_NO_CRIME)
endFunction

function p_Style()
endFunction

function p_Unstyle()
endFunction

function p_Vitalize()
    p_ACTORS.Vitalize(p_ref_actor, p_code_vitality)
endFunction

function p_Unvitalize()
endFunction

function p_Outfit()
    p_outfit2_member.Set(p_ref_actor)
endFunction

function p_Unoutfit()
    p_outfit2_member.Unset(p_ref_actor)
endFunction

; Public Methods
int function Enforce()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_FOLLOWERS.Has_Follower(p_ref_actor)
        code_return = p_Followers.Get_Follower(p_ref_actor).f_Enforce()
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

    if p_SETTLER.Exists()
        code_return = p_SETTLER.f_Enforce()
        if code_return < 0
            return code_return
        endIf
    endIf

    p_queue_member.Enqueue("p_Token")
    p_queue_member.Enqueue("p_Member")
    if p_is_thrall
        p_queue_member.Enqueue("p_Enthrall")
    endIf
    p_queue_member.Enqueue("p_Style")
    p_queue_member.Enqueue("p_Vitalize")
    ;p_Outfit() currently not enforced

    p_ACTORS.Update_Equipment(p_ref_actor); not sure if this should go here

    return p_CODES.SUCCESS
endFunction

bool function Exists()
    return p_is_created
endFunction

string function Get_Name()
    if !Exists()
        return ""
    else
        return p_ACTORS.Get_Name(p_ref_actor)
    endIf
endFunction

Actor function Get_Actor()
    if !Exists()
        return none
    else
        return p_ref_actor
    endIf
endFunction

doticu_npcp_settler function Get_Settler()
    if !Exists() || !p_SETTLER.Exists()
        return none
    else
        return p_SETTLER
    endIf
endFunction

doticu_npcp_immobile function Get_Immobile()
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
        return p_code_style
    endIf
endFunction

int function Get_Vitality()
    if !Exists()
        return -1
    else
        return p_code_vitality
    endIf
endFunction

int function Set_Name(string str_name)
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    p_ACTORS.Set_Name(p_ref_actor, str_name)

    if Get_Name() != str_name
        return p_CODES.CANT_RENAME
    endIf

    p_container_pack.Set_Name(str_name + "'s Pack")
    p_outfit2_member.Set_Name(str_name + "'s Outfit")

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

int function Resettle()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if !Is_Settler()
        return p_CODES.ISNT_SETTLER
    endIf

    code_return = Get_Settler().Resettle()
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

    if !p_ACTORS.Is_Vampire(p_CONSTS.ACTOR_PLAYER)
        return p_CODES.ISNT_VAMPIRE
    endIf

    if p_is_thrall
        return p_CODES.IS_THRALL
    endIf

    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_THRALL)
    p_ref_actor.EvaluatePackage()

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

    if !p_ACTORS.Is_Vampire(p_CONSTS.ACTOR_PLAYER)
        return p_CODES.ISNT_VAMPIRE
    endIf

    if !p_is_thrall
        return p_CODES.ISNT_THRALL
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_THRALL)
    p_ref_actor.EvaluatePackage()

    p_is_thrall = false

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Resurrect()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_ACTORS.Is_Alive(p_ref_actor)
        return p_CODES.IS_ALIVE
    endIf

    p_ACTORS.Resurrect(p_ref_actor)

    if p_ACTORS.Is_Dead(p_ref_actor)
        return p_CODES.CANT_RESURRECT
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Style(int code_style)
    if code_style == p_CODES.IS_DEFAULT
        return Style_Default()
    elseIf code_style == p_CODES.IS_WARRIOR
        return Style_Warrior()
    elseIf code_style == p_CODES.IS_MAGE
        return Style_Mage()
    elseIf code_style == p_CODES.IS_ARCHER
        return Style_Archer()
    endIf
endFunction

int function Style_Default()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_code_style == p_CODES.IS_DEFAULT
        return p_CODES.IS_DEFAULT
    endIf

    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_STYLE_DEFAULT)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_WARRIOR)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_MAGE)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_ARCHER)
    p_ref_actor.EvaluatePackage()

    p_code_style = p_CODES.IS_DEFAULT

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

    if p_code_style == p_CODES.IS_WARRIOR
        return p_CODES.IS_WARRIOR
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_DEFAULT)
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_STYLE_WARRIOR)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_MAGE)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_ARCHER)
    p_ref_actor.EvaluatePackage()

    p_code_style = p_CODES.IS_WARRIOR

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

    if p_code_style == p_CODES.IS_MAGE
        return p_CODES.IS_MAGE
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_DEFAULT)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_WARRIOR)
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_STYLE_MAGE)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_ARCHER)
    p_ref_actor.EvaluatePackage()

    p_code_style = p_CODES.IS_MAGE

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

    if p_code_style == p_CODES.IS_ARCHER
        return p_CODES.IS_ARCHER
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_DEFAULT)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_WARRIOR)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_STYLE_MAGE)
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_STYLE_ARCHER)
    p_ref_actor.EvaluatePackage()

    p_code_style = p_CODES.IS_ARCHER

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Vitalize(int code_vitality)
    if code_vitality == p_CODES.IS_MORTAL
        return Vitalize_Mortal()
    elseIf code_vitality == p_CODES.IS_PROTECTED
        return Vitalize_Protected()
    elseIf code_vitality == p_CODES.IS_ESSENTIAL
        return Vitalize_Essential()
    elseIf code_vitality == p_CODES.IS_INVULNERABLE
        return Vitalize_Invulnerable()
    endIf
endFunction

int function Vitalize_Mortal()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_code_vitality == p_CODES.IS_MORTAL
        return p_CODES.IS_MORTAL
    endIf

    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_VITALITY_MORTAL)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_PROTECTED)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_ESSENTIAL)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_INVULNERABLE)
    p_ref_actor.EvaluatePackage()

    p_code_vitality = p_CODES.IS_MORTAL

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Vitalize_Protected()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_code_vitality == p_CODES.IS_PROTECTED
        return p_CODES.IS_PROTECTED
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_MORTAL)
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_VITALITY_PROTECTED)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_ESSENTIAL)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_INVULNERABLE)
    p_ref_actor.EvaluatePackage()

    p_code_vitality = p_CODES.IS_PROTECTED

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Vitalize_Essential()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_code_vitality == p_CODES.IS_ESSENTIAL
        return p_CODES.IS_ESSENTIAL
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_MORTAL)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_PROTECTED)
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_VITALITY_ESSENTIAL)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_INVULNERABLE)
    p_ref_actor.EvaluatePackage()

    p_code_vitality = p_CODES.IS_ESSENTIAL

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Vitalize_Invulnerable()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if p_code_vitality == p_CODES.IS_INVULNERABLE
        return p_CODES.IS_INVULNERABLE
    endIf

    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_MORTAL)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_PROTECTED)
    p_ACTORS.Untoken(p_ref_actor, p_CONSTS.TOKEN_VITALITY_ESSENTIAL)
    p_ACTORS.Token(p_ref_actor, p_CONSTS.TOKEN_VITALITY_INVULNERABLE)
    p_ref_actor.EvaluatePackage()

    p_code_vitality = p_CODES.IS_INVULNERABLE

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
    
    p_ACTORS.Open_Inventory(p_ref_actor)
    Utility.Wait(0.1)
    p_ACTORS.Update_Equipment(p_ref_actor)

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Pack()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf
    
    p_container_pack.Open()

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Outfit()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf
    
    p_Outfit()

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Unoutfit()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf
    
    p_Unoutfit()

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

bool function Is_Mobile()
    return !p_IMMOBILE.Exists()
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
    return p_code_style == p_CODES.IS_DEFAULT
endFunction

bool function Is_Styled_Warrior()
    return p_code_style == p_CODES.IS_WARRIOR
endFunction

bool function Is_Styled_Mage()
    return p_code_style == p_CODES.IS_MAGE
endFunction

bool function Is_Styled_Archer()
    return p_code_style == p_CODES.IS_ARCHER
endFunction

bool function Is_Vitalized_Mortal()
    return p_code_vitality == p_CODES.IS_MORTAL
endFunction

bool function Is_Vitalized_Protected()
    return p_code_vitality == p_CODES.IS_PROTECTED
endFunction

bool function Is_Vitalized_Essential()
    return p_code_vitality == p_CODES.IS_ESSENTIAL
endFunction

bool function Is_Vitalized_Invulnerable()
    return p_code_vitality == p_CODES.IS_INVULNERABLE
endFunction

function Summon(int distance = 60, int angle = 0)
    p_ACTORS.Move_To(p_ref_actor, p_CONSTS.ACTOR_PLAYER, distance, angle)
endFunction

function Summon_Ahead()
    Summon(60, 0)
endFunction

function Summon_Behind()
    Summon(60, 180)
endFunction

; Update Methods
event u_0_1_0()
    p_OUTFIT = p_CONSTS.FORMLIST_OUTFITS.GetAt(p_ID_ALIAS) as Outfit
    if Exists()
        p_Destroy_Outfits()
        p_Create_Outfits()
    endIf
endEvent

event u_0_1_1()
    p_Create_Queues()
    p_outfit2_member.MoveTo(p_CONSTS.MARKER_STORAGE)
    p_prev_outfit2_member.MoveTo(p_CONSTS.MARKER_STORAGE)

    p_SETTLER.u_0_1_1()
    p_IMMOBILE.u_0_1_1()
endEvent

; we need an update to create pack, but we might move to 0_2_0, with more aliases
; which will require a fresh restart, because it's not going to be supported, updating
; members quest. however, we may make it so that we can add new quests containing aliases.
; we'll need a quest manager that can do that.

; Events
event On_Queue_Member()
    string str_message = p_queue_member.Dequeue()

    if str_message == "p_Token"
        p_Token()
    elseIf str_message == "p_Member"
        p_Member()
    elseIf str_message == "p_Enthrall"
        p_Enthrall()
    elseIf str_message == "p_Style"
        p_Style()
    elseIf str_message == "p_Vitalize"
        p_Vitalize()
    endIf
endEvent

event On_Members_Unmember()
    if Exists()
        Unmember()
    endIf
endEvent

event OnActivate(ObjectReference ref_activator)
    Enforce()
    ; maybe we could also pop up some basic stats on screen?
endEvent

event OnLoad()
    p_ACTORS.Update_Equipment(p_ref_actor)
endEvent

event OnCombatStateChanged(Actor ref_target, int code_combat)
    if ref_target == p_CONSTS.ACTOR_PLAYER || p_ACTORS.Has_Token(ref_target, p_CONSTS.TOKEN_MEMBER)
        p_ACTORS.Pacify(p_ref_actor)
    endIf

    if code_combat == p_CODES.COMBAT_NO
        Enforce()
    elseIf code_combat == p_CODES.COMBAT_YES

    elseIf code_combat == p_CODES.COMBAT_SEARCHING
        Enforce(); this may be too intensive here
    endIf
endEvent

; we can use OnItemAdded to keep track of stuff that is added to the member's inventory.
