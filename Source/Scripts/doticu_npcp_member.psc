Scriptname doticu_npcp_member extends ReferenceAlias

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
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return p_DATA.MODS.FUNCS.ACTORS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
    endFunction
endProperty
doticu_npcp_queues property QUEUES hidden
    doticu_npcp_queues function Get()
        return p_DATA.MODS.FUNCS.QUEUES
    endFunction
endProperty
doticu_npcp_outfits property OUTFITS hidden
    doticu_npcp_outfits function Get()
        return p_DATA.MODS.FUNCS.OUTFITS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
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
        return p_queue_member
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA                  =  none

; Private Variables
bool                    p_is_created            = false
int                     p_id_alias              =    -1
Actor                   p_ref_actor             =  none
doticu_npcp_settler     p_ref_settler           =  none
doticu_npcp_immobile    p_ref_immobile          =  none
string                  p_str_namespace         =    ""
bool                    p_is_clone              = false
bool                    p_is_generic            = false
bool                    p_is_thrall             = false
int                     p_code_style            =    -1
int                     p_code_vitality         =    -1
int                     p_queue_code_return     =     0
Outfit                  p_outfit_member         =  none
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
Faction[]               p_prev_factions         =  none
int[]                   p_prev_faction_ranks    =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA, int id_alias, bool is_clone)
    GotoState("p_STATE_BUSY")
    p_Create(DATA, id_alias, is_clone)
    GotoState("")
endFunction

function p_Create(doticu_npcp_data DATA, int id_alias, bool is_clone)
    p_DATA = DATA

    p_is_created = true
    p_id_alias = id_alias
    p_ref_actor = GetActorReference()
    p_ref_settler = (self as ReferenceAlias) as doticu_npcp_settler
    p_ref_immobile = (self as ReferenceAlias) as doticu_npcp_immobile
    p_str_namespace = "member_" + p_id_alias
    p_is_clone = is_clone
    p_is_generic = ACTORS.Is_Generic(p_ref_actor)
    p_is_thrall = false
    p_code_style = VARS.auto_style
    p_code_vitality = VARS.auto_vitality
    p_queue_code_return = 0
    p_outfit_member = CONSTS.FORMLIST_OUTFITS.GetAt(p_id_alias) as Outfit

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_MEMBER, p_id_alias + 1)
    p_ref_actor.EvaluatePackage()

    p_Create_Queues()
    p_Register_Queues()

    if p_is_clone
        p_Enqueue("Member.Greet")
    endIf
    p_Enqueue("Member.Create_Containers")
    p_Enqueue("Member.Create_Outfits")
    p_Enqueue("Member.Backup")

    Enforce()
endFunction

function f_Destroy()
    GotoState("p_STATE_BUSY")
    p_Destroy()
    GotoState("")
endFunction

function p_Destroy()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_MEMBER)
    p_ref_actor.EvaluatePackage()

    f_QUEUE.Flush(true)
    f_QUEUE.Pause()

    if Is_Follower()
        FOLLOWERS.f_Destroy_Follower(p_ref_actor)
    endIf
    if Is_Immobile()
        p_ref_immobile.f_Destroy()
    endIf
    if Is_Settler()
        p_ref_settler.f_Destroy()
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

    p_prev_faction_ranks = none
    p_prev_factions = none
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
    p_outfit_member = none
    p_queue_code_return = 0
    p_code_vitality = -1
    p_code_style = -1
    p_is_thrall = false
    p_is_generic = false
    p_is_clone = false
    p_str_namespace = ""
    p_ref_immobile = none
    p_ref_settler = none
    p_ref_actor = none
    p_id_alias = -1
    p_is_created = false
endFunction

function f_Register()
    ; registering mod events is global for each script on an object, and
    ; further, works for handlers labeled as function as well as event.
    RegisterForModEvent("doticu_npcp_load_mod", "On_Load_Mod")
    RegisterForModEvent("doticu_npcp_members_unmember", "On_Members_Unmember")
    RegisterForModEvent("doticu_npcp_members_u_0_1_4", "On_u_0_1_4")
    RegisterForModEvent("doticu_npcp_members_u_0_1_5", "On_u_0_1_5")

    p_Register_Queues()

    if Is_Settler()
        p_ref_settler.f_Register()
    endIf
    if Is_Immobile()
        p_ref_immobile.f_Register()
    endIf
endFunction

function f_Unregister()
    UnregisterForAllModEvents()

    if Is_Settler()
        p_ref_settler.f_Unregister()
    endIf
    if Is_Immobile()
        p_ref_immobile.f_Unregister()
    endIf
endFunction

; Private Methods
function p_Create_Queues()
    p_queue_member = QUEUES.Create("alias", 64, 0.1)
endFunction

function p_Destroy_Queues()
    QUEUES.Destroy(p_queue_member)
endFunction

function p_Register_Queues()
    f_QUEUE.Register_Alias(self, "On_Queue_Member", p_str_namespace)
endFunction

function p_Enqueue(string str_message, float float_interval = -1.0, bool allow_repeat = false)
    f_QUEUE.Enqueue(str_message, float_interval, p_str_namespace, allow_repeat)
endFunction

function p_Rush(string str_message)
    f_QUEUE.Rush(str_message, p_str_namespace)
endFunction

function p_Greet()
    ACTORS.Move_To(p_ref_actor, CONSTS.ACTOR_PLAYER, 60, 180)
    ACTORS.Greet_Player(p_ref_actor)
endFunction

function p_Create_Containers()
    p_container2_pack = CONTAINERS.Create()
    p_Rename_Containers(Get_Name())
endFunction

function p_Destroy_Containers()
    p_container2_pack.RemoveAllItems(CONSTS.ACTOR_PLAYER, false, true)
    CONTAINERS.Destroy(p_container2_pack)
endFunction

function p_Rename_Containers(string str_name_member)
    p_container2_pack.Set_Name(str_name_member + "'s Pack")
endFunction

function p_Create_Outfits()
    ; for settler, thrall, immobile, and follower, we can actually add some basic gear, so they are not naked.
    ; could be an option
    p_outfit2_member = OUTFITS.Create(p_outfit_member)
    p_outfit2_settler = OUTFITS.Create(p_outfit_member)
    p_outfit2_thrall = OUTFITS.Create(p_outfit_member)
    p_outfit2_immobile = OUTFITS.Create(p_outfit_member)
    p_outfit2_follower = OUTFITS.Create(p_outfit_member)
    p_outfit2_current = p_outfit2_member
    
    p_Rename_Outfits(Get_Name())

    p_outfit2_member.Get(p_ref_actor)
    p_outfit2_member.Remove_Inventory(p_ref_actor, p_container2_pack)

    p_prev_outfit2_member = OUTFITS.Create(p_outfit_member)
    p_prev_outfit2_member.Copy(p_outfit2_member)
endFunction

function p_Destroy_Outfits()
    OUTFITS.Destroy(p_prev_outfit2_member)

    OUTFITS.Destroy(p_outfit2_follower)
    OUTFITS.Destroy(p_outfit2_immobile)
    OUTFITS.Destroy(p_outfit2_thrall)
    OUTFITS.Destroy(p_outfit2_settler)
    OUTFITS.Destroy(p_outfit2_member)
endFunction

function p_Rename_Outfits(string str_name_member)
    p_outfit2_member.Set_Name(str_name_member + "'s Member Outfit")
    p_outfit2_settler.Set_Name(str_name_member + "'s Settler Outfit")
    p_outfit2_thrall.Set_Name(str_name_member + "'s Thrall Outfit")
    p_outfit2_immobile.Set_Name(str_name_member + "'s Immobile Outfit")
    p_outfit2_follower.Set_Name(str_name_member + "'s Follower Outfit")
endFunction

function p_Backup()
    ; backup if was in current follower faction
    ; to stop infighting, use a member package that just ignores combat.
    p_prev_vitality = ACTORS.Get_Vitality(p_ref_actor)
    p_prev_factions = ACTORS.Get_Factions(p_ref_actor)
    p_prev_faction_ranks = ACTORS.Get_Faction_Ranks(p_ref_actor, p_prev_factions)
endFunction

function p_Restore()
    ACTORS.Set_Factions(p_ref_actor, p_prev_factions, p_prev_faction_ranks)

    p_prev_outfit2_member.Set(p_ref_actor); instead of this, we might set the outfit to GetOutfit on base actor.

    ACTORS.Vitalize(p_ref_actor, p_prev_vitality)
    ; put in current follower faction if they were in there
endFunction

function p_Token()
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_MEMBER, p_id_alias + 1)

    if p_is_clone
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_CLONE)
    else
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_CLONE)
    endIf

    if p_is_generic
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_GENERIC)
    else
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_GENERIC)
    endIf

    if p_is_thrall
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_THRALL)
    else
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_THRALL)
    endIf

    if p_code_style == CODES.IS_DEFAULT
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    elseIf p_code_style == CODES.IS_WARRIOR
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    elseIf p_code_style == CODES.IS_MAGE
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    elseIf p_code_style == CODES.IS_ARCHER
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    endIf

    if p_code_vitality == CODES.IS_MORTAL
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    elseIf p_code_vitality == CODES.IS_PROTECTED
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    elseIf p_code_vitality == CODES.IS_ESSENTIAL
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    elseIf p_code_vitality == CODES.IS_INVULNERABLE
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    endIf

    p_ref_actor.EvaluatePackage()
endFunction

function p_Untoken()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_THRALL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_GENERIC)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_CLONE)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_MEMBER)

    p_ref_actor.EvaluatePackage()
endFunction

function p_Member()
    p_ref_actor.RemoveFromFaction(CONSTS.FACTION_CURRENT_FOLLOWER)
    p_ref_actor.RemoveFromFaction(CONSTS.FACTION_WI_NO_BODY_CLEANUP)
    p_ref_actor.AddToFaction(CONSTS.FACTION_MEMBER)
    p_ref_actor.SetActorValue("Aggression", 0)
endFunction

function p_Unmember()
    p_ref_actor.SetActorValue("Aggression", 0)
    p_ref_actor.RemoveFromFaction(CONSTS.FACTION_MEMBER)
    ; Restore resets factions
endFunction

function p_Enthrall()
    p_ref_actor.AddToFaction(CONSTS.FACTION_DLC1_VAMPIRE_FEED_NO_CRIME)
endFunction

function p_Unthrall()
    p_ref_actor.RemoveFromFaction(CONSTS.FACTION_DLC1_VAMPIRE_FEED_NO_CRIME)
endFunction

function p_Style()
endFunction

function p_Unstyle()
endFunction

function p_Vitalize()
    ACTORS.Vitalize(p_ref_actor, p_code_vitality)
endFunction

function p_Unvitalize()
endFunction

function p_Outfit()
    if VARS.auto_outfit
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

function p_Resurrect()
    ACTORS.Resurrect(p_ref_actor)
endFunction

; Public Methods
int function Enforce()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Enqueue("Member.Member")
    p_Enqueue("Member.Outfit")
    p_Enqueue("Member.Token")
    if Is_Thrall()
        p_Enqueue("Member.Enthrall")
    endIf
    p_Enqueue("Member.Style")
    p_Enqueue("Member.Vitalize")

    if Is_Settler()
        p_ref_settler.f_Enforce()
    endIf

    if Is_Immobile()
        p_ref_immobile.f_Enforce()
    endIf

    if Is_Follower()
        Get_Follower().f_Enforce()
    endIf

    return CODES.SUCCESS
endFunction

bool function Exists()
    return p_is_created
endFunction

string function Get_Name()
    if !Exists()
        return ""
    else
        return ACTORS.Get_Name(p_ref_actor)
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
    if !Exists() || !p_ref_settler.Exists()
        return none
    else
        return p_ref_settler
    endIf
endFunction

doticu_npcp_immobile function Get_Immobile()
    if !Exists() || !p_ref_immobile.Exists()
        return none
    else
        return p_ref_immobile
    endIf
endFunction

doticu_npcp_follower function Get_Follower()
    if !Exists() || !Is_Follower()
        return none
    else
        return FOLLOWERS.Get_Follower(p_ref_actor)
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
        return CODES.ISNT_MEMBER
    endIf

    ACTORS.Set_Name(p_ref_actor, str_name)

    if Get_Name() != str_name
        return CODES.CANT_RENAME
    endIf

    p_Rename_Containers(str_name)
    p_Rename_Outfits(str_name)

    return CODES.SUCCESS
endFunction

int function Settle()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Is_Settler()
        return CODES.IS_SETTLER
    endIf

    p_Rush("Settler.Create")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Resettle()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Settler()
        return CODES.ISNT_SETTLER
    endIf

    ; Settler will handle queue.
    code_return = Get_Settler().Resettle()
    if code_return < 0
        return code_return
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unsettle()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Settler()
        return CODES.ISNT_SETTLER
    endIf

    p_Rush("Settler.Destroy")

    ; we need to get rid of any old messages
    ; else a deadlock may occur on next Rush
    f_QUEUE.Flush(false)

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Immobilize()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Is_Immobile()
        return CODES.IS_IMMOBILE
    endIf

    p_Rush("Immobile.Create")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Mobilize()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Immobile()
        return CODES.ISNT_IMMOBILE
    endIf

    p_Rush("Immobile.Destroy")

    ; we need to get rid of any old messages
    ; else a deadlock may occur on next Rush
    f_QUEUE.Flush(false)

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Follow()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Rush("Follower.Create")
    if p_queue_code_return < 0
        return p_queue_code_return
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unfollow()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Follower()
        return CODES.ISNT_FOLLOWER
    endIf

    p_Rush("Follower.Destroy")
    if p_queue_code_return < 0
        return p_queue_code_return
    endIf

    ; we need to get rid of any old messages
    ; else a deadlock may occur on next Rush
    f_QUEUE.Flush(false)

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Enthrall()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
        return CODES.ISNT_VAMPIRE
    endIf

    if p_is_thrall
        return CODES.IS_THRALL
    endIf

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_THRALL)
    p_ref_actor.EvaluatePackage()

    p_is_thrall = true
    p_Rush("Member.Enthrall")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unthrall()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
        return CODES.ISNT_VAMPIRE
    endIf

    if !p_is_thrall
        return CODES.ISNT_THRALL
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_THRALL)
    p_ref_actor.EvaluatePackage()

    p_is_thrall = false
    p_Rush("Member.Unthrall")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Resurrect()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if ACTORS.Is_Alive(p_ref_actor)
        return CODES.IS_ALIVE
    endIf

    p_Rush("Member.Resurrect")

    if ACTORS.Is_Dead(p_ref_actor)
        return CODES.CANT_RESURRECT
    endIf

    if Is_Follower()
        Get_Follower().Relevel()
    endIf

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Style(int code_style)
    if code_style == CODES.IS_DEFAULT
        return Style_Default()
    elseIf code_style == CODES.IS_WARRIOR
        return Style_Warrior()
    elseIf code_style == CODES.IS_MAGE
        return Style_Mage()
    elseIf code_style == CODES.IS_ARCHER
        return Style_Archer()
    endIf
endFunction

int function Style_Default()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if p_code_style == CODES.IS_DEFAULT
        return CODES.IS_DEFAULT
    endIf

    f_QUEUE.Pause()
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    p_ref_actor.EvaluatePackage()
    f_QUEUE.Unpause()

    p_code_style = CODES.IS_DEFAULT
    p_Rush("Member.Style")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Style_Warrior()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if p_code_style == CODES.IS_WARRIOR
        return CODES.IS_WARRIOR
    endIf

    f_QUEUE.Pause()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    p_ref_actor.EvaluatePackage()
    f_QUEUE.Unpause()

    p_code_style = CODES.IS_WARRIOR
    p_Rush("Member.Style")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Style_Mage()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if p_code_style == CODES.IS_MAGE
        return CODES.IS_MAGE
    endIf

    f_QUEUE.Pause()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    p_ref_actor.EvaluatePackage()
    f_QUEUE.Unpause()

    p_code_style = CODES.IS_MAGE
    p_Rush("Member.Style")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Style_Archer()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if p_code_style == CODES.IS_ARCHER
        return CODES.IS_ARCHER
    endIf

    f_QUEUE.Pause()
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    p_ref_actor.EvaluatePackage()
    f_QUEUE.Unpause()

    p_code_style = CODES.IS_ARCHER
    p_Rush("Member.Style")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Vitalize(int code_vitality)
    if code_vitality == CODES.IS_MORTAL
        return Vitalize_Mortal()
    elseIf code_vitality == CODES.IS_PROTECTED
        return Vitalize_Protected()
    elseIf code_vitality == CODES.IS_ESSENTIAL
        return Vitalize_Essential()
    elseIf code_vitality == CODES.IS_INVULNERABLE
        return Vitalize_Invulnerable()
    endIf
endFunction

int function Vitalize_Mortal()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if p_code_vitality == CODES.IS_MORTAL
        return CODES.IS_MORTAL
    endIf

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    p_ref_actor.EvaluatePackage()

    p_code_vitality = CODES.IS_MORTAL
    p_Rush("Member.Vitalize")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Vitalize_Protected()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if p_code_vitality == CODES.IS_PROTECTED
        return CODES.IS_PROTECTED
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    p_ref_actor.EvaluatePackage()

    p_code_vitality = CODES.IS_PROTECTED
    p_Rush("Member.Vitalize")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Vitalize_Essential()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if p_code_vitality == CODES.IS_ESSENTIAL
        return CODES.IS_ESSENTIAL
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    p_ref_actor.EvaluatePackage()

    p_code_vitality = CODES.IS_ESSENTIAL
    p_Rush("Member.Vitalize")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Vitalize_Invulnerable()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if p_code_vitality == CODES.IS_INVULNERABLE
        return CODES.IS_INVULNERABLE
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    p_ref_actor.EvaluatePackage()

    p_code_vitality = CODES.IS_INVULNERABLE
    p_Rush("Member.Vitalize")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Pack()
    int code_return
    
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf
    
    p_container2_pack.Open()
    Utility.Wait(0.1)

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit(int code_outfit)
    if code_outfit == CODES.IS_MEMBER
        return Outfit_Member()
    elseIf code_outfit == CODES.IS_SETTLER
        return Outfit_Settler()
    elseIf code_outfit == CODES.IS_THRALL
        return Outfit_Thrall()
    elseIf code_outfit == CODES.IS_IMMOBILE
        return Outfit_Immobile()
    elseIf code_outfit == CODES.IS_FOLLOWER
        return Outfit_Follower()
    endIf
endFunction

int function Outfit_Member()
    int code_return
    
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_outfit2_member.Put()
    Utility.Wait(0.1)

    p_outfit2_current = p_outfit2_member
    p_Enqueue("Member.Outfit")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Settler()
    int code_return
    
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_outfit2_settler.Put()
    Utility.Wait(0.1)

    p_outfit2_current = p_outfit2_settler
    p_Enqueue("Member.Outfit")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Thrall()
    int code_return
    
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_outfit2_thrall.Put()
    Utility.Wait(0.1)

    p_outfit2_current = p_outfit2_thrall
    p_Enqueue("Member.Outfit")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Immobile()
    int code_return
    
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_outfit2_immobile.Put()
    Utility.Wait(0.1)

    p_outfit2_current = p_outfit2_immobile
    p_Enqueue("Member.Outfit")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Follower()
    int code_return
    
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_outfit2_follower.Put()
    Utility.Wait(0.1)

    p_outfit2_current = p_outfit2_follower
    p_Enqueue("Member.Outfit")

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unoutfit()
    int code_return
    
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf
    
    p_Rush("Member.Unoutfit"); this needs to be worked out better

    code_return = Enforce()
    if code_return < 0
        return code_return
    endIf

    return CODES.SUCCESS
endFunction

int function Unmember()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if MEMBERS.Should_Unclone_Actor(p_ref_actor)
        return Unclone()
    else
        return MEMBERS.Destroy_Member(p_ref_actor, false)
    endIf
endFunction

int function Clone()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Rush("Member.Clone")
    return p_queue_code_return
endFunction

int function Unclone()
    int code_return

    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !p_is_clone
        return CODES.ISNT_CLONE
    endIf

    return MEMBERS.Destroy_Member(p_ref_actor, true)
endFunction

bool function Is_Unique()
    return Exists() && !p_is_generic
endFunction

bool function Is_Generic()
    return Exists() && p_is_generic
endFunction

bool function Is_Member()
    return Exists()
endFunction

bool function Is_Settler()
    return Exists() && p_ref_settler.Exists()
endFunction

bool function Is_Immobile()
    return Exists() && p_ref_immobile.Exists()
endFunction

bool function Is_Mobile()
    return Exists() && !p_ref_immobile.Exists()
endFunction

bool function Is_Follower()
    return Exists() && FOLLOWERS.Has_Follower(p_ref_actor)
endFunction

bool function Is_Clone()
    return Exists() && p_is_clone
endFunction

bool function Is_Thrall()
    return Exists() && p_is_thrall
endFunction

bool function Is_Styled_Default()
    return Exists() && p_code_style == CODES.IS_DEFAULT
endFunction

bool function Is_Styled_Warrior()
    return Exists() && p_code_style == CODES.IS_WARRIOR
endFunction

bool function Is_Styled_Mage()
    return Exists() && p_code_style == CODES.IS_MAGE
endFunction

bool function Is_Styled_Archer()
    return Exists() && p_code_style == CODES.IS_ARCHER
endFunction

bool function Is_Vitalized_Mortal()
    return Exists() && p_code_vitality == CODES.IS_MORTAL
endFunction

bool function Is_Vitalized_Protected()
    return Exists() && p_code_vitality == CODES.IS_PROTECTED
endFunction

bool function Is_Vitalized_Essential()
    return Exists() && p_code_vitality == CODES.IS_ESSENTIAL
endFunction

bool function Is_Vitalized_Invulnerable()
    return Exists() && p_code_vitality == CODES.IS_INVULNERABLE
endFunction

bool function Is_Paralyzed()
    return Exists() && Is_Immobile() && p_ref_immobile.Is_Paralyzed()
endFunction

function Summon(int distance = 120, int angle = 0)
    ACTORS.Move_To(p_ref_actor, CONSTS.ACTOR_PLAYER, distance, angle)
endFunction

function Summon_Ahead()
    Summon(120, 0)
endFunction

function Summon_Behind()
    Summon(120, 180)
endFunction

; Update Methods
event On_u_0_1_0()
    p_outfit_member = CONSTS.FORMLIST_OUTFITS.GetAt(p_id_alias) as Outfit
    if Exists()
        p_Destroy_Outfits()
        p_Create_Outfits()
    endIf
endEvent

event On_u_0_1_1()
    p_Create_Queues()
    p_outfit2_member.MoveTo(CONSTS.MARKER_STORAGE)
    p_prev_outfit2_member.MoveTo(CONSTS.MARKER_STORAGE)
endEvent

event On_u_0_1_2()
    if Exists()
        VARS.auto_outfit = true
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

event On_u_0_1_4(Form form_data)
    if Exists()
        p_queue_member.u_0_1_4(p_DATA)

        p_container2_pack.u_0_1_4(p_DATA)

        p_outfit2_member.u_0_1_4(p_DATA)
        p_outfit2_settler.u_0_1_4(p_DATA)
        p_outfit2_thrall.u_0_1_4(p_DATA)
        p_outfit2_immobile.u_0_1_4(p_DATA)
        p_outfit2_follower.u_0_1_4(p_DATA)
        p_prev_outfit2_member.u_0_1_4(p_DATA)
    endIf

    p_ref_settler.u_0_1_4(p_DATA)
    p_ref_immobile.u_0_1_4(p_DATA)
endEvent

event On_u_0_1_5(Form form_data)
    if Exists()
        p_ref_settler = (self as ReferenceAlias) as doticu_npcp_settler
        p_ref_immobile = (self as ReferenceAlias) as doticu_npcp_immobile
        p_outfit_member = CONSTS.FORMLIST_OUTFITS.GetAt(p_id_alias) as Outfit

        p_outfit2_member.u_0_1_5(p_DATA)
        p_outfit2_settler.u_0_1_5(p_DATA)
        p_outfit2_thrall.u_0_1_5(p_DATA)
        p_outfit2_immobile.u_0_1_5(p_DATA)
        p_outfit2_follower.u_0_1_5(p_DATA)
        p_prev_outfit2_member.u_0_1_5(p_DATA)

        if Is_Settler()
            p_ref_settler.u_0_1_5(p_DATA)
        endIf

        if Is_Immobile()
            p_ref_immobile.u_0_1_5(p_DATA)
        endIf
    endIf
endEvent

; Private States
state p_STATE_BUSY
    function f_Create(doticu_npcp_data DATA, int id_alias, bool is_clone)
    endFunction
    function f_Destroy()
    endFunction

    ; really ought to add all public methods, but it's difficult because so many
    ; already have a private version. what really should be done is to make two
    ; scripts per script, one implementation, and one interface. but I'm not sure
    ; if that is too costly on the engine.
endState

; Events
event On_Queue_Member(string str_message)
    if false
    
    elseIf str_message == "Member.Greet"
        p_Greet()
    elseIf str_message == "Member.Create_Containers"
        p_Create_Containers()
    elseIf str_message == "Member.Create_Outfits"
        p_Create_Outfits()
    elseIf str_message == "Member.Backup"
        p_Backup()
    elseIf str_message == "Member.Token"
        p_Token()
    elseIf str_message == "Member.Member"
        p_Member()
    elseIf str_message == "Member.Outfit"
        p_Outfit()
    elseIf str_message == "Member.Unoutfit"
        p_Unoutfit()
    elseIf str_message == "Member.Enthrall"
        if Is_Thrall()
            p_Enthrall()
        endIf
    elseIf str_message == "Member.Unthrall"
        if !Is_Thrall()
            p_Unthrall()
        endIf
    elseIf str_message == "Member.Style"
        p_Style()
    elseIf str_message == "Member.Vitalize"
        p_Vitalize()
    elseIf str_message == "Member.Resurrect"
        p_Resurrect()
    elseIf str_message == "Member.Clone"
        p_queue_code_return = MEMBERS.Create_Member(p_ref_actor, true)
    elseIf str_message == "Settler.Create"
        if !Is_Settler()
            p_ref_settler.f_Create(p_DATA, p_id_alias)
        endIf
    elseIf str_message == "Settler.Destroy"
        if Is_Settler()
            p_ref_settler.f_Destroy()
        endIf
    elseIf str_message == "Immobile.Create"
        if !Is_Immobile()
            p_ref_immobile.f_Create(p_DATA, p_id_alias)
        endIf
    elseIf str_message == "Immobile.Destroy"
        if Is_Immobile()
            p_ref_immobile.f_Destroy()
        endIf
    elseIf str_message == "Follower.Create"
        if !Is_Follower()
            p_queue_code_return = FOLLOWERS.f_Create_Follower(p_ref_actor)
        endIf
    elseIf str_message == "Follower.Destroy"
        if Is_Follower()
            p_queue_code_return = FOLLOWERS.f_Destroy_Follower(p_ref_actor)
        endIf
    
    endIf

    f_QUEUE.Dequeue()
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
    if ref_target == CONSTS.ACTOR_PLAYER || ACTORS.Has_Token(ref_target, CONSTS.TOKEN_MEMBER)
        ACTORS.Pacify(p_ref_actor)
    endIf

    if code_combat == CODES.COMBAT_NO
        Enforce()
    elseIf code_combat == CODES.COMBAT_YES

    elseIf code_combat == CODES.COMBAT_SEARCHING
        Enforce(); this may be too intensive here
    endIf
endEvent

event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if ref_container_source == CONSTS.ACTOR_PLAYER
        p_ref_actor.RemoveItem(form_item, count_item, true, ref_container_source)
        LOGS.Create_Error("You can only put items into a member's pack or one of their outfits.")
    endIf
endEvent
