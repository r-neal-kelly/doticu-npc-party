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
doticu_npcp_logs        p_LOGS                  =  none
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
doticu_npcp_queue       p_queue_member          =  none
doticu_npcp_container   p_container2_pack       =  none
doticu_npcp_outfit      p_outfit2_member        =  none
doticu_npcp_outfit      p_outfit2_settler       =  none
doticu_npcp_outfit      p_outfit2_thrall        =  none
doticu_npcp_outfit      p_outfit2_immobile      =  none
doticu_npcp_outfit      p_outfit2_follower      =  none
doticu_npcp_outfit      p_outfit2_current       =  none

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
    p_LOGS = DATA.MODS.FUNCS.LOGS
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
    ; registering mod events is global for each script on an object, and
    ; further, works for handlers labeled as function as well as event.
    RegisterForModEvent("doticu_npcp_load_mod", "On_Load_Mod")
    RegisterForModEvent("doticu_npcp_members_unmember", "On_Members_Unmember")
    RegisterForModEvent("doticu_npcp_members_u_0_1_0", "On_u_0_1_0")
    RegisterForModEvent("doticu_npcp_members_u_0_1_1", "On_u_0_1_1")
    RegisterForModEvent("doticu_npcp_members_u_0_1_2", "On_u_0_1_2")
    RegisterForModEvent("doticu_npcp_members_u_0_1_3", "On_u_0_1_3")
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
    p_Create_Containers()
    p_Create_Outfits()
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

    p_queue_member.Flush(); I think this is the right spot

    if p_FOLLOWERS.Has_Follower(p_ref_actor)
        code_return = p_FOLLOWERS.f_Destroy_Follower(p_ref_actor)
        if code_return < 0
            return code_return
        endIf
    endIf
    if p_IMMOBILE.Exists()
        code_return = p_IMMOBILE.f_Destroy()
        if code_return < 0
            return code_return
        endIf
    endIf
    if p_SETTLER.Exists()
        code_return = p_SETTLER.f_Destroy()
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
    p_Destroy_Outfits()
    p_Destroy_Containers()
    p_Destroy_Queues()

    p_prev_outfit2_member = none
    p_prev_vitality = -1

    p_outfit2_current = none
    p_outfit2_follower = none
    p_outfit2_immobile = none
    p_outfit2_thrall = none
    p_outfit2_settler = none
    p_outfit2_member = none
    p_container2_pack = none
    p_queue_member = none
    p_code_vitality = -1
    p_code_style = -1
    p_is_thrall = false
    p_is_generic = false
    p_is_clone = false
    p_ref_actor = none
    p_is_created = false

    return p_CODES.SUCCESS
endFunction

function f_Enqueue(string str_message, float float_interval = -1.0, bool allow_repeat = false)
    p_queue_member.Enqueue(str_message, float_interval, allow_repeat)
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
    p_queue_member = p_QUEUES.Create("member_" + p_ID_ALIAS, 32, 0.15)
endFunction

function p_Destroy_Queues()
    p_QUEUES.Destroy(p_queue_member)
endFunction

function p_Link_Containers(doticu_npcp_data DATA)
    if p_container2_pack
        p_container2_pack.f_Link(DATA)
    endIf
endFunction

function p_Register_Containers()
    if p_container2_pack
        p_container2_pack.f_Register()
    endIf
endFunction

function p_Create_Containers()
    p_container2_pack = p_CONTAINERS.Create()
    p_Rename_Containers(Get_Name())
endFunction

function p_Destroy_Containers()
    p_container2_pack.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)
    p_CONTAINERS.Destroy(p_container2_pack)
endFunction

function p_Rename_Containers(string str_name_member)
    p_container2_pack.Set_Name(str_name_member + "'s Pack")
endFunction

function p_Link_Outfits(doticu_npcp_data DATA)
    if p_outfit2_member
        p_outfit2_member.f_Link(DATA)
    endIf
    if p_outfit2_settler
        p_outfit2_settler.f_Link(DATA)
    endIf
    if p_outfit2_thrall
        p_outfit2_thrall.f_Link(DATA)
    endIf
    if p_outfit2_immobile
        p_outfit2_immobile.f_Link(DATA)
    endIf
    if p_outfit2_follower
        p_outfit2_follower.f_Link(DATA)
    endIf
    if p_prev_outfit2_member
        p_prev_outfit2_member.f_Link(DATA)
    endIf
endFunction

function p_Register_Outfits()
    if p_outfit2_member
        p_outfit2_member.f_Register()
    endIf
    if p_outfit2_settler
        p_outfit2_settler.f_Register()
    endIf
    if p_outfit2_thrall
        p_outfit2_thrall.f_Register()
    endIf
    if p_outfit2_immobile
        p_outfit2_immobile.f_Register()
    endIf
    if p_outfit2_follower
        p_outfit2_follower.f_Register()
    endIf
    if p_prev_outfit2_member
        p_prev_outfit2_member.f_Register()
    endIf
endFunction

function p_Create_Outfits()
    ; for settler, thrall, immobile, and follower, we can actually add some basic gear, so they are not naked.
    ; could be an option
    p_outfit2_member = p_OUTFITS.Create(p_OUTFIT)
    p_outfit2_settler = p_OUTFITS.Create(p_OUTFIT)
    p_outfit2_thrall = p_OUTFITS.Create(p_OUTFIT)
    p_outfit2_immobile = p_OUTFITS.Create(p_OUTFIT)
    p_outfit2_follower = p_OUTFITS.Create(p_OUTFIT)
    p_prev_outfit2_member = p_OUTFITS.Create(p_OUTFIT)

    p_Rename_Outfits(Get_Name())

    p_outfit2_member.Get(p_ref_actor)
    p_prev_outfit2_member.Get(p_ref_actor)

    p_outfit2_member.Remove_Inventory(p_ref_actor, p_container2_pack)

    p_outfit2_current = p_outfit2_member
endFunction

function p_Destroy_Outfits()
    p_OUTFITS.Destroy(p_prev_outfit2_member)
    p_OUTFITS.Destroy(p_outfit2_follower)
    p_OUTFITS.Destroy(p_outfit2_immobile)
    p_OUTFITS.Destroy(p_outfit2_thrall)
    p_OUTFITS.Destroy(p_outfit2_settler)
    p_OUTFITS.Destroy(p_outfit2_member)
endFunction

function p_Rename_Outfits(string str_name_member)
    p_outfit2_member.Set_Name(str_name_member + "'s Member Outfit")
    p_outfit2_settler.Set_Name(str_name_member + "'s Settler Outfit")
    p_outfit2_thrall.Set_Name(str_name_member + "'s Thrall Outfit")
    p_outfit2_immobile.Set_Name(str_name_member + "'s Immobile Outfit")
    p_outfit2_follower.Set_Name(str_name_member + "'s Follower Outfit")
endFunction

function p_Backup()
    p_prev_vitality = p_ACTORS.Get_Vitality(p_ref_actor)
endFunction

function p_Restore()
    p_prev_outfit2_member.Set(p_ref_actor); instead of this, we might set the outfit to GetOutfit on base actor.

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
    if p_VARS.auto_outfit
        if Is_Immobile()
            p_outfit2_current = p_outfit2_immobile
        elseIf Is_Follower()
            p_outfit2_current = p_outfit2_follower
        elseIf Is_Thrall()
            p_outfit2_current = p_outfit2_thrall
        elseIf Is_Settler()
            p_outfit2_current = p_outfit2_settler
        else
            p_outfit2_current = p_outfit2_member
        endIf
    endIf

    if !p_outfit2_current
        p_outfit2_current = p_outfit2_member
    endIf

    p_outfit2_current.Set(p_ref_actor)
endFunction

function p_Unoutfit()
    ; this is not really helpful atm
    p_outfit2_member.Unset(p_ref_actor)
    p_outfit2_current = none
endFunction

; Public Methods
int function Enforce()
    int code_return

    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    if Is_Paralyzed()
        p_queue_member.Enqueue("f_Paralyze", 0.3)
    endIf
    p_queue_member.Enqueue("p_Outfit", 0.12)
    p_queue_member.Enqueue("p_Token", 0.12)
    p_queue_member.Enqueue("p_Member", 0.12)
    if p_is_thrall
        p_queue_member.Enqueue("p_Enthrall", 0.12)
    endIf
    p_queue_member.Enqueue("p_Style", 0.12)
    p_queue_member.Enqueue("p_Vitalize", 0.12)
    if Is_Follower()
        p_queue_member.Enqueue("Follower.F_Enforce", 0.12)
    endIf

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

doticu_npcp_follower function Get_Follower()
    if !Exists() || !Is_Follower()
        return none
    else
        return p_FOLLOWERS.Get_Follower(p_ref_actor)
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

    p_Rename_Containers(str_name)
    p_Rename_Outfits(str_name)

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

    p_Unthrall()

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

int function Pack()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf
    
    p_container2_pack.Open()
    Utility.Wait(0.1)

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Outfit(int code_outfit)
    if code_outfit == p_CODES.IS_MEMBER
        return Outfit_Member()
    elseIf code_outfit == p_CODES.IS_SETTLER
        return Outfit_Settler()
    elseIf code_outfit == p_CODES.IS_THRALL
        return Outfit_Thrall()
    elseIf code_outfit == p_CODES.IS_IMMOBILE
        return Outfit_Immobile()
    elseIf code_outfit == p_CODES.IS_FOLLOWER
        return Outfit_Follower()
    endIf
endFunction

int function Outfit_Member()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    p_outfit2_member.Put()
    Utility.Wait(0.1)
    p_outfit2_current = p_outfit2_member

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Outfit_Settler()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    p_outfit2_settler.Put()
    Utility.Wait(0.1)
    p_outfit2_current = p_outfit2_settler

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Outfit_Thrall()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    p_outfit2_thrall.Put()
    Utility.Wait(0.1)
    p_outfit2_current = p_outfit2_thrall

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Outfit_Immobile()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    p_outfit2_immobile.Put()
    Utility.Wait(0.1)
    p_outfit2_current = p_outfit2_immobile

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return p_CODES.SUCCESS
endFunction

int function Outfit_Follower()
    int code_return
    
    if !Exists()
        return p_CODES.ISNT_MEMBER
    endIf

    p_outfit2_follower.Put()
    Utility.Wait(0.1)
    p_outfit2_current = p_outfit2_follower

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
    
    p_Unoutfit(); this needs to be worked out better

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

bool function Is_Paralyzed()
    return Is_Immobile() && p_IMMOBILE.Is_Paralyzed()
endFunction

function Summon(int distance = 60, int angle = 0)
    bool has_enabled_ai = p_ref_actor.IsAIEnabled()

    if !has_enabled_ai
        p_ref_actor.EnableAI(true)
    endIf
    
    p_ACTORS.Move_To(p_ref_actor, p_CONSTS.ACTOR_PLAYER, distance, angle)

    if !has_enabled_ai
        p_ref_actor.EnableAI(false)
    endIf
endFunction

function Summon_Ahead()
    Summon(60, 0)
endFunction

function Summon_Behind()
    Summon(60, 180)
endFunction

; Update Methods
event On_u_0_1_0()
    p_OUTFIT = p_CONSTS.FORMLIST_OUTFITS.GetAt(p_ID_ALIAS) as Outfit
    if Exists()
        p_Destroy_Outfits()
        p_Create_Outfits()
    endIf
endEvent

event On_u_0_1_1()
    p_Create_Queues()
    p_outfit2_member.MoveTo(p_CONSTS.MARKER_STORAGE)
    p_prev_outfit2_member.MoveTo(p_CONSTS.MARKER_STORAGE)
endEvent

event On_u_0_1_2()
    if Exists()
        p_VARS.auto_outfit = true
        p_Destroy_Outfits()
        p_Create_Outfits()
    endIf
endEvent

event On_u_0_1_3()
    if Exists()
        if !p_queue_member
            p_Create_Queues()
        endIf
        if !p_container2_pack
            p_Create_Containers()
        endIf
        if !p_outfit2_member
            p_Create_Outfits()
        endIf
    endIf
endEvent

; Events
event On_Queue_Member(string str_message)
    if str_message == "f_Paralyze"
        p_IMMOBILE.f_Paralyze()
    elseIf str_message == "p_Outfit"
        p_Outfit()
    elseIf str_message == "p_Token"
        p_Token()
        if Is_Settler()
            p_SETTLER.f_Token()
        endIf
        if Is_Immobile()
            p_IMMOBILE.f_Token()
        endIf
    elseIf str_message == "p_Member"
        p_Member()
    elseIf str_message == "p_Enthrall"
        p_Enthrall()
    elseIf str_message == "p_Style"
        p_Style()
    elseIf str_message == "p_Vitalize"
        p_Vitalize()
    elseIf str_message == "Follower.F_Enforce"
        if p_FOLLOWERS.Has_Follower(p_ref_actor)
            Get_Follower().f_Enforce()
        endIf
    endIf

    p_queue_member.Dequeue()
endEvent

event On_Members_Unmember()
    if Exists()
        Unmember()
    endIf
endEvent

event On_Load_Mod()
    if Exists()
        p_Rename_Containers(Get_Name())
        p_Rename_Outfits(Get_Name())
        Enforce()
    endIf
endEvent

event OnActivate(ObjectReference ref_activator)
    Enforce()
    ; maybe we could also pop up some basic stats on screen?
endEvent

event OnLoad()
    Enforce()
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

event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if ref_container_source == p_CONSTS.ACTOR_PLAYER
        p_ref_actor.RemoveItem(form_item, count_item, true, ref_container_source)
        p_LOGS.Create_Error("You can only put items into a member's pack or one of their outfits.")
    endIf
endEvent
