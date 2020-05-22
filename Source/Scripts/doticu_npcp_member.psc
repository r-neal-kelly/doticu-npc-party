;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_member extends ReferenceAlias

; Modules
doticu_npcp_main property MAIN hidden
    doticu_npcp_main function Get()
        return p_DATA.MODS.MAIN
    endFunction
endProperty
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
doticu_npcp_npcs property NPCS hidden
    doticu_npcp_npcs function Get()
        return p_DATA.MODS.FUNCS.NPCS
    endFunction
endProperty
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return p_DATA.MODS.FUNCS.MANNEQUINS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
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

; Private Constants
doticu_npcp_data        p_DATA                      =  none

; Private Variables
bool                    p_is_locked                 = false
bool                    p_is_created                = false
int                     p_id_alias                  =    -1
Actor                   p_ref_actor                 =  none
bool                    p_is_clone                  = false
bool                    p_is_follower               = false
bool                    p_is_settler                = false
bool                    p_is_thrall                 = false
bool                    p_is_immobile               = false
bool                    p_is_paralyzed              = false
bool                    p_is_mannequin              = false
bool                    p_is_reanimated             = false
bool                    p_do_outfit_vanilla         = false
int                     p_code_style                =    -1
int                     p_code_vitality             =    -1
int                     p_int_rating                =     0
ObjectReference         p_marker_settler            =  none
ObjectReference         p_marker_display            =  none
ObjectReference         p_marker_mannequin          =  none
Outfit                  p_outfit_vanilla            =  none
ObjectReference         p_container_pack            =  none
doticu_npcp_outfit      p_outfit2_member            =  none
doticu_npcp_outfit      p_outfit2_settler           =  none
doticu_npcp_outfit      p_outfit2_thrall            =  none
doticu_npcp_outfit      p_outfit2_immobile          =  none
doticu_npcp_outfit      p_outfit2_follower          =  none
doticu_npcp_outfit      p_outfit2_vanilla           =  none
doticu_npcp_outfit      p_outfit2_default           =  none
doticu_npcp_outfit      p_outfit2_current           =  none
doticu_npcp_outfit      p_outfit2_previous          =  none

Faction[]               p_prev_factions             =  none
int[]                   p_prev_faction_ranks        =  none
Faction                 p_prev_faction_crime        =  none
float                   p_prev_aggression           =   0.0
float                   p_prev_confidence           =   0.0
float                   p_prev_assistance           =   0.0
float                   p_prev_morality             =   0.0

; Friend Methods
function f_Create(doticu_npcp_data DATA, int id_alias, bool is_clone)
p_Lock()

    p_DATA = DATA

    p_is_created = true
    p_id_alias = id_alias
    p_ref_actor = GetActorReference()
    p_is_clone = is_clone
    p_is_follower = false
    p_is_settler = false
    p_is_thrall = false
    p_is_immobile = false
    p_is_paralyzed = false
    p_is_mannequin = false
    p_is_reanimated = false
    
    p_do_outfit_vanilla = false
    p_code_style = VARS.auto_style
    p_code_vitality = VARS.auto_vitality
    p_int_rating = 0
    p_marker_settler = CONSTS.FORMLIST_MARKERS_SETTLER.GetAt(p_id_alias) as ObjectReference
    p_marker_display = none
    p_marker_mannequin = none
    p_outfit_vanilla = NPCS.Get_Default_Outfit(p_ref_actor)

    p_Create_Container()
    p_Create_Outfit()
    p_Backup()

p_Unlock()
    
    p_Member()
    p_Style()
    p_Vitalize()
    p_Outfit()

    ; has to happen after p_Member() because it needs
    ; to have the token for the full dialogue
    if p_is_clone
        ACTORS.Greet_Player(p_ref_actor)
    endIf
endFunction

function f_Destroy()
    if Is_Follower()
        FOLLOWERS.f_Destroy_Follower(p_ref_actor)
    endIf

    p_Unvitalize()
    p_Unstyle()
    if Is_Mannequin()
        p_Unmannequinize()
    endIf
    if Is_Paralyzed()
        p_Unparalyze()
    endIf
    if Is_Immobile()
        p_Mobilize()
    endIf
    if Is_Thrall()
        p_Unthrall()
    endIf
    if Is_Settler()
        p_Unsettle()
    endIf
    p_Unmember()
    if Is_Reanimated()
        p_Deanimate()
        p_Kill()
    endIf

p_Lock()

    p_Restore()
    p_Destroy_Outfits()
    p_Destroy_Containers()

    p_prev_morality = 0.0
    p_prev_assistance = 0.0
    p_prev_confidence = 0.0
    p_prev_aggression = 0.0
    p_prev_faction_crime = none
    p_prev_faction_ranks = new int[1]
    p_prev_factions = new Faction[1]

    p_outfit2_previous = none
    p_outfit2_current = none
    p_outfit2_default = none
    p_outfit2_vanilla = none
    p_outfit2_follower = none
    p_outfit2_immobile = none
    p_outfit2_thrall = none
    p_outfit2_settler = none
    p_outfit2_member = none
    p_container_pack = none
    p_outfit_vanilla = none
    p_marker_mannequin = none
    p_marker_display = none
    p_marker_settler = none
    p_int_rating = 0
    p_code_vitality = -1
    p_code_style = -1
    p_do_outfit_vanilla = false
    p_is_reanimated = false
    p_is_mannequin = false
    p_is_paralyzed = false
    p_is_immobile = false
    p_is_thrall = false
    p_is_settler = false
    p_is_follower = false
    p_is_clone = false
    p_ref_actor = none
    p_id_alias = -1
    p_is_created = false

p_Unlock()
endFunction

function f_Register()
endFunction

function f_Unregister()
    ; this covers queue registration also I believe
    UnregisterForAllModEvents()
endFunction

int function f_Get_ID()
    return p_id_alias
endFunction

; Private Methods
function p_Lock(float interval = 0.2, float timeout = 6.0)
    float time_waited = 0.0

    while p_is_locked && time_waited < timeout
        Utility.Wait(interval)
        time_waited += interval
    endWhile

    p_is_locked = true
endFunction

function p_Unlock()
    p_is_locked = false
endFunction

function p_Create_Container()
    p_container_pack = CONTAINERS.Create_Perm()
endFunction

function p_Destroy_Containers()
    p_container_pack.RemoveAllItems(CONSTS.ACTOR_PLAYER, true, true)
    CONTAINERS.Destroy_Perm(p_container_pack)
endFunction

function p_Create_Outfit()
    p_outfit2_member = OUTFITS.Create()
    if VARS.fill_outfits
        p_outfit2_member.Get(p_ref_actor, p_container_pack)
    else
        p_ref_actor.RemoveAllItems(p_container_pack, true, false)
    endIf
    p_outfit2_current = p_outfit2_member
    p_outfit2_previous = p_outfit2_current
endFunction

function p_Destroy_Outfits()
    if p_outfit2_default
        OUTFITS.Destroy(p_outfit2_default)
    endIf
    if p_outfit2_vanilla
        OUTFITS.Destroy(p_outfit2_vanilla)
    endIf
    if p_outfit2_immobile
        OUTFITS.Destroy(p_outfit2_immobile)
    endIf
    if p_outfit2_follower
        OUTFITS.Destroy(p_outfit2_follower)
    endIf
    if p_outfit2_thrall
        OUTFITS.Destroy(p_outfit2_thrall)
    endIf
    if p_outfit2_settler
        OUTFITS.Destroy(p_outfit2_settler)
    endIf
    OUTFITS.Destroy(p_outfit2_member)
endFunction

function p_Backup()
    p_prev_factions = ACTORS.Get_Factions(p_ref_actor)
    p_prev_faction_ranks = ACTORS.Get_Faction_Ranks(p_ref_actor, p_prev_factions)
    p_prev_faction_crime = p_ref_actor.GetCrimeFaction()

    p_prev_aggression = p_ref_actor.GetBaseActorValue("Aggression")
    p_prev_confidence = p_ref_actor.GetBaseActorValue("Confidence")
    p_prev_assistance = p_ref_actor.GetBaseActorValue("Assistance")
    p_prev_morality = p_ref_actor.GetBaseActorValue("Morality")
endFunction

function p_Restore()
    p_ref_actor.SetActorValue("Morality", p_prev_morality)
    p_ref_actor.SetActorValue("Assistance", p_prev_assistance)
    p_ref_actor.SetActorValue("Confidence", p_prev_confidence)
    p_ref_actor.SetActorValue("Aggression", 0.0)

    ACTORS.Set_Factions(p_ref_actor, p_prev_factions, p_prev_faction_ranks)
    p_ref_actor.SetCrimeFaction(p_prev_faction_crime)
endFunction

function p_Member()
p_Lock()

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_MEMBER, p_id_alias + 1)
    if p_is_clone
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_CLONE)
    else
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_CLONE)
    endIf
    if ACTORS.Is_Generic(p_ref_actor)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_GENERIC)
    else
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_GENERIC)
    endIf
    if p_is_thrall
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_THRALL)
    else
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_THRALL)
    endIf

    p_ref_actor.RemoveFromFaction(CONSTS.FACTION_POTENTIAL_FOLLOWER)
    p_ref_actor.RemoveFromFaction(CONSTS.FACTION_CURRENT_FOLLOWER); we want to separate state for each reference
    p_ref_actor.AddToFaction(CONSTS.FACTION_WI_NO_BODY_CLEANUP)
    p_ref_actor.AddToFaction(CONSTS.FACTION_MEMBER)
    p_ref_actor.SetCrimeFaction(none)

    p_ref_actor.SetActorValue("Aggression", 0.0)
    p_ref_actor.SetActorValue("Confidence", 4.0)
    p_ref_actor.SetActorValue("Assistance", 2.0)
    p_ref_actor.SetActorValue("Morality", 0.0)

    ; we don't use the vanilla wait system, and have disabled it
    ; so this makes sure that a member doesn't get stuck
    p_ref_actor.SetActorValue("WaitingForPlayer", 0.0)

    p_ref_actor.SetPlayerTeammate(true, true)

    if !p_ref_actor.GetRace().AllowPCDialogue()
        p_ref_actor.AllowPCDialogue(true)
    endIf

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Unmember()
p_Lock()

    if !p_ref_actor.GetRace().AllowPCDialogue()
        p_ref_actor.AllowPCDialogue(false)
    endIf

    p_ref_actor.SetPlayerTeammate(false, false)

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_THRALL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_GENERIC)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_CLONE)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_MEMBER)

    ; Restore() handles the rest

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Settle()
p_Lock()

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_SETTLER)

    p_marker_settler.MoveTo(p_ref_actor)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Unsettle()
p_Lock()

    p_marker_settler.MoveToMyEditorLocation()

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_SETTLER)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Enthrall()
p_Lock()

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_THRALL)

    p_ref_actor.AddToFaction(CONSTS.FACTION_DLC1_VAMPIRE_FEED_NO_CRIME)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Unthrall()
p_Lock()

    p_ref_actor.RemoveFromFaction(CONSTS.FACTION_DLC1_VAMPIRE_FEED_NO_CRIME)

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_THRALL)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Immobilize()
p_Lock()

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_IMMOBILE)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Mobilize()
p_Lock()

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_IMMOBILE)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Paralyze()
p_Lock()

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_PARALYZED)

    ObjectReference ref_marker = p_ref_actor.PlaceAtMe(CONSTS.STATIC_MARKER_X)
    ref_marker.MoveTo(p_ref_actor)
    
    p_ref_actor.EnableAI(false)
    p_ref_actor.SetGhost(true)
    p_ref_actor.BlockActivation(true)

    p_ref_actor.EvaluatePackage()

    p_ref_actor.MoveTo(ref_marker)

p_Unlock()
endFunction

function p_Unparalyze()
p_Lock()
    
    if !Is_Mannequin()
        p_ref_actor.BlockActivation(false)
        p_ref_actor.SetGhost(false)
        p_ref_actor.EnableAI(true)
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_PARALYZED)

    ;p_ref_actor.EvaluatePackage(); resets animation

p_Unlock()
endFunction

function p_Reparalyze()
    if !Is_Paralyzed() || Is_Mannequin()
        return
    endIf

    p_Unparalyze()

p_Lock()

    Debug.SendAnimationEvent(p_ref_actor, "IdleForceDefaultState"); go to cached animation? FNIS?
    ;Debug.SendAnimationEvent(p_ref_actor, "IdleCiceroDance1")
    ;p_ref_actor.WaitForAnimationEvent("done")
    Utility.Wait(0.1)

p_Unlock()

    p_Paralyze()
endFunction

function p_Mannequinize()
    if !Is_Mannequin()
        return
    endIf

p_Lock()

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_MANNEQUIN)

    p_ref_actor.EnableAI(false)
    p_ref_actor.SetGhost(true)
    p_ref_actor.BlockActivation(true)

    p_ref_actor.MoveTo(p_marker_mannequin)
    p_ref_actor.Disable()
    p_ref_actor.Enable()

    p_ref_actor.EvaluatePackage()

p_Unlock()

    if Is_Follower()
        Unfollow()
    endIf
endFunction

function p_Unmannequinize()
p_Lock()
    
    if !Is_Paralyzed()
        p_ref_actor.BlockActivation(false)
        p_ref_actor.SetGhost(false)
        p_ref_actor.EnableAI(true)
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_MANNEQUIN)

p_Unlock()
endFunction

function p_Remannequinize()
    if !Is_Mannequin()
        return
    endIf
    
p_Lock()

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_MANNEQUIN)

    p_ref_actor.EnableAI(false)
    p_ref_actor.SetGhost(true)
    p_ref_actor.BlockActivation(true)

    ; this allows the mannequin to be called on display
    if !p_marker_display
        p_ref_actor.MoveTo(p_marker_mannequin)
    endIf

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Set_Style(int code_style)
p_Lock()

    p_code_style = code_style

p_Unlock()
endFunction

function p_Style()
p_Lock()

    if p_code_style == CODES.IS_DEFAULT
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_COWARD)
    elseIf p_code_style == CODES.IS_WARRIOR
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_COWARD)
    elseIf p_code_style == CODES.IS_MAGE
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_COWARD)
    elseIf p_code_style == CODES.IS_ARCHER
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_COWARD)
    elseIf p_code_style == CODES.IS_COWARD
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
        ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
        ACTORS.Token(p_ref_actor, CONSTS.TOKEN_STYLE_COWARD)
    endIf

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Unstyle()
p_Lock()

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_COWARD)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_ARCHER)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_MAGE)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_WARRIOR)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_STYLE_DEFAULT)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Set_Vitality(int code_vitality)
p_Lock()

    p_code_vitality = code_vitality

p_Unlock()
endFunction

function p_Vitalize()
p_Lock()

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

p_Unlock()
endFunction

function p_Unvitalize()
p_Lock()

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_INVULNERABLE)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_ESSENTIAL)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_PROTECTED)
    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_VITALITY_MORTAL)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Put_Outfit(int code_outfit)
p_Lock()

    if code_outfit == CODES.OUTFIT_MEMBER
        p_outfit2_member.Set_Name(Get_Name() + "'s Member Outfit")
        p_outfit2_current = p_outfit2_member
    elseIf code_outfit == CODES.OUTFIT_SETTLER
        if !p_outfit2_settler
            p_outfit2_settler = OUTFITS.Create_Settler()
        endIf
        p_outfit2_settler.Set_Name(Get_Name() + "'s Settler Outfit")
        p_outfit2_current = p_outfit2_settler
    elseIf code_outfit == CODES.OUTFIT_THRALL
        if !p_outfit2_thrall
            p_outfit2_thrall = OUTFITS.Create_Thrall()
        endIf
        p_outfit2_thrall.Set_Name(Get_Name() + "'s Thrall Outfit")
        p_outfit2_current = p_outfit2_thrall
    elseIf code_outfit == CODES.OUTFIT_FOLLOWER
        if !p_outfit2_follower
            p_outfit2_follower = OUTFITS.Create_Follower()
        endIf
        p_outfit2_follower.Set_Name(Get_Name() + "'s Follower Outfit")
        p_outfit2_current = p_outfit2_follower
    elseIf code_outfit == CODES.OUTFIT_IMMOBILE
        if !p_outfit2_immobile
            p_outfit2_immobile = OUTFITS.Create_Immobile()
        endIf
        p_outfit2_immobile.Set_Name(Get_Name() + "'s Immobile Outfit")
        p_outfit2_current = p_outfit2_immobile
    elseIf code_outfit == CODES.OUTFIT_VANILLA
        if !p_outfit2_vanilla
            p_outfit2_vanilla = OUTFITS.Create_Vanilla()
        endIf
        p_outfit2_vanilla.Set_Name(Get_Name() + "'s Vanilla Outfit")
        p_outfit2_current = p_outfit2_vanilla
    elseIf code_outfit == CODES.OUTFIT_DEFAULT
        if !p_outfit2_default
            p_outfit2_default = OUTFITS.Create_Default()
            p_outfit2_default.Get_Default(p_ref_actor)
        endIf
        p_outfit2_default.Set_Name(Get_Name() + "'s Default Outfit")
        p_outfit2_current = p_outfit2_default
    endIf

    p_outfit2_current.Put()

p_Unlock()
endFunction

function p_Outfit()
p_Lock()
    ; if we ever allow manual outfit switching without having to put, we need to make sure the oufit is created

    if VARS.auto_outfit
        if Is_Immobile() && VARS.auto_immobile_outfit
            if !p_outfit2_immobile
                p_outfit2_immobile = OUTFITS.Create_Immobile()
            endIf
            p_outfit2_current = p_outfit2_immobile
        elseIf Is_Follower()
            if !p_outfit2_follower
                p_outfit2_follower = OUTFITS.Create_Follower()
            endIf
            p_outfit2_current = p_outfit2_follower
        elseIf Is_Thrall()
            if !p_outfit2_thrall
                p_outfit2_thrall = OUTFITS.Create_Thrall()
            endIf
            p_outfit2_current = p_outfit2_thrall
        elseIf Is_Settler()
            if !p_outfit2_settler
                p_outfit2_settler = OUTFITS.Create_Settler()
            endIf
            p_outfit2_current = p_outfit2_settler
        else
            p_outfit2_current = p_outfit2_member
        endIf
    endIf

    ; just in case
    if !p_outfit2_current
        p_outfit2_current = p_outfit2_member
    endIf
    if !p_outfit_vanilla
        p_outfit_vanilla = NPCS.Get_Default_Outfit(p_ref_actor)
    endIf

    if p_do_outfit_vanilla
        p_do_outfit_vanilla = false
        if !p_outfit2_vanilla
            p_outfit2_vanilla = OUTFITS.Create_Vanilla()
        endIf
        p_outfit2_previous = p_outfit2_current
        p_outfit2_current = p_outfit2_vanilla
        p_outfit2_current.Cache_Vanilla_Dynamic(p_ref_actor)
        p_outfit2_current.Set(p_ref_actor, p_container_pack)
    elseIf p_outfit2_previous != p_outfit2_current
        if p_outfit2_current == p_outfit2_vanilla
            ; maybe we can make this a setting, because it makes it easy to relevel the same outfit
            ; it has to be static because the actor is not likely wearing the outfit or the items
            p_outfit2_current.Cache_Vanilla_Static(p_outfit_vanilla)
        elseIf p_outfit2_current == p_outfit2_default
            p_outfit2_current.Cache_Vanilla_Static(NPCS.Get_Default_Outfit(p_ref_actor))
        endIf
        p_outfit2_previous = p_outfit2_current
        p_outfit2_current.Set(p_ref_actor, p_container_pack)
    else
        ; this is just a way to do asyncronous updating for 0.9.0
        if p_outfit2_current == p_outfit2_vanilla
            p_outfit2_current.Try_Cache_Vanilla(p_outfit_vanilla)
        elseIf p_outfit2_current == p_outfit2_default
            p_outfit2_current.Try_Cache_Vanilla(NPCS.Get_Default_Outfit(p_ref_actor))
        endIf
        p_outfit2_current.Set(p_ref_actor, p_container_pack)
    endIf

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Resurrect()
p_Lock()

    ; no longer triggers an OnLoad()
    ACTORS.Resurrect(p_ref_actor)

p_Unlock()

    ; OnLoad checks a lot of state that can be removed on the death of the actor.
    OnLoad()
endFunction

function p_Kill()
p_Lock()

    ; we clear it just to make sure that their default essential
    ; status doesn't get in the way of their dying
    Clear()
    ACTORS.Kill(p_ref_actor)
    ForceRefTo(p_ref_actor)

p_Unlock()

    ; we call the event handler ourselves because the actor
    ; is not filled on death
    OnDeath(none)
endFunction

function p_Reanimate()
p_Lock()

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_REANIMATED)

    ; we could have an option for what shader is player, including none
    ; we go ahead and make sure that the shader is stopped so we don't stack them
    CONSTS.SHADER_REANIMATE_FX.Stop(p_ref_actor)
    CONSTS.SHADER_REANIMATE_FX.Play(p_ref_actor, -1.0)

    ; can't set unconscious, messes up their ai pretty badly
    ; it would be cool if we could change how they walk.
    ; we probably need to check that they have an appropiate voice type, so we gets moans even for modded npcs
    ; the voice may need to be reset on each game load. and each npc load, because i doubt it sticks
    ; look into the susanna the wicked shirt, could be reused in shader? also, there may be a shader in dlc1

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Deanimate()
p_Lock()

    CONSTS.SHADER_REANIMATE_FX.Stop(p_ref_actor)

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_REANIMATED)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Rename(string str_name)
p_Lock()

    ACTORS.Set_Name(p_ref_actor, str_name)

    p_ref_actor.EvaluatePackage()

p_Unlock()
endfunction

function p_Pack()
p_Lock()

    CONTAINERS.Set_Name(p_container_pack, Get_Name() + "'s Pack")
    CONTAINERS.Open(p_container_pack)

p_Unlock()
endFunction

int function p_Clone()
p_Lock()
    int code_return = MEMBERS.Create_Member(p_ref_actor, true)
p_Unlock()
    return code_return
endFunction

function p_Async(string str_func)
    string str_event = "doticu_npcp_member_async_" + p_id_alias

p_Lock()
    RegisterForModEvent(str_event, str_func)
    FUNCS.Send_Event(str_event, 0.25, 5.0)
    UnregisterForModEvent(str_event)
p_Unlock()
endFunction

; Public Methods
function Enforce()
    if !Exists() || Is_Dead()
        return
    endIf

    if Is_Immobile()
        p_Immobilize()
    else
        p_Mobilize()
    endIf

    if Is_Paralyzed()
        p_Reparalyze()
    else
        p_Unparalyze()
    endIf

    if Is_Mannequin()
        p_Remannequinize()
    else
        p_Unmannequinize()
    endIf

    if Is_Reanimated()
        p_Reanimate()
    else
        p_Deanimate()
    endIf

    Utility.Wait(0.1)
    if !Exists() || Is_Dead()
        return
    endIf

    p_Outfit()

    p_Member()

    p_Style()

    p_Vitalize()

    Utility.Wait(0.1)
    if !Exists() || Is_Dead()
        return
    endIf

    if Is_Settler()
        p_Settle()
    else
        p_Unsettle()
    endIf

    if Is_Thrall()
        p_Enthrall()
    else
        p_Unthrall()
    endIf

    if Is_Follower()
        Get_Follower().f_Enforce()
    endIf
endFunction

function Enforce_Async()
    p_Async("On_Enforce")
endFunction
event On_Enforce()
    Enforce()
endEvent

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

int function Get_Outfit()
    if !Exists() || p_outfit2_current == none
        return -1
    else
        if p_outfit2_current == p_outfit2_member
            return CODES.OUTFIT_MEMBER
        elseIf p_outfit2_current == p_outfit2_settler
            return CODES.OUTFIT_SETTLER
        elseIf p_outfit2_current == p_outfit2_thrall
            return CODES.OUTFIT_THRALL
        elseIf p_outfit2_current == p_outfit2_follower
            return CODES.OUTFIT_FOLLOWER
        elseIf p_outfit2_current == p_outfit2_immobile
            return CODES.OUTFIT_IMMOBILE
        elseIf p_outfit2_current == p_outfit2_vanilla
            return CODES.OUTFIT_VANILLA
        elseIf p_outfit2_current == p_outfit2_default
            return CODES.OUTFIT_DEFAULT
        endIf
    endIf
endFunction

doticu_npcp_outfit function Get_Current_Outfit2()
    return p_outfit2_current
endFunction

Outfit function Get_Vanilla_Outfit()
    return p_outfit_vanilla
endFunction

function Set_Vanilla_Outfit(Outfit outfit_vanilla)
    if outfit_vanilla
        p_outfit_vanilla = outfit_vanilla
    endIf
endFunction

int function Set_Name(string str_name)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Rename(str_name)

    if Get_Name() != str_name
        return CODES.CANT_RENAME
    endIf

    MEMBERS.Request_Sort()

    if Is_Follower()
        FOLLOWERS.Request_Sort()
    endIf
    
    return CODES.SUCCESS
endFunction

int function Settle(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Is_Settler()
        return CODES.IS_SETTLER
    endIf

    p_is_settler = true

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Settle")
    else
        p_Settle()
    endIf

    p_Outfit()

    return CODES.SUCCESS
endFunction
event On_Settle()
    if Is_Settler()
        p_Settle()
    endIf
endEvent

int function Resettle(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Settler()
        return CODES.ISNT_SETTLER
    endIf

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Settle")
    else
        p_Settle()
    endIf

    p_Outfit()

    return CODES.SUCCESS
endFunction

int function Unsettle(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Settler()
        return CODES.ISNT_SETTLER
    endIf

    p_is_settler = false

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Unsettle")
    else
        p_Unsettle()
    endIf

    p_Outfit()

    return CODES.SUCCESS
endFunction
event On_Unsettle()
    if Isnt_Settler()
        p_Unsettle()
    endIf
endEvent

int function Enthrall(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
        return CODES.ISNT_VAMPIRE
    endIf

    if Is_Thrall()
        return CODES.IS_THRALL
    endIf

    p_is_thrall = true

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Enthrall")
    else
        p_Enthrall()
    endIf

    p_Outfit()

    return CODES.SUCCESS
endFunction
event On_Enthrall()
    if Is_Thrall()
        p_Enthrall()
    endIf
endEvent

int function Unthrall(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
        return CODES.ISNT_VAMPIRE
    endIf

    if !Is_Thrall()
        return CODES.ISNT_THRALL
    endIf

    p_is_thrall = false

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Unthrall")
    else
        p_Unthrall()
    endIf

    p_Outfit()

    return CODES.SUCCESS
endFunction
event On_Unthrall()
    if Isnt_Thrall()
        p_Unthrall()
    endIf
endEvent

int function Immobilize(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Is_Immobile()
        return CODES.IS_IMMOBILE
    endIf

    p_is_immobile = true

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Immobilize")
    else
        p_Immobilize()
    endIf

    p_Outfit()

    return CODES.SUCCESS
endFunction
event On_Immobilize()
    if Is_Immobile()
        p_Immobilize()
    endIf
endEvent

int function Mobilize(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Immobile()
        return CODES.ISNT_IMMOBILE
    endIf

    p_is_immobile = false

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Mobilize")
    else
        p_Mobilize()
    endIf

    p_Outfit()

    return CODES.SUCCESS
endFunction
event On_Mobilize()
    if Is_Mobile()
        p_Mobilize()
    endIf
endEvent

int function Paralyze(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Is_Paralyzed()
        return CODES.IS_PARALYZED
    endIf

    p_is_paralyzed = true

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Paralyze")
    else
        p_Paralyze()
    endIf

    return CODES.SUCCESS
endFunction
event On_Paralyze()
    if Is_Paralyzed()
        p_Paralyze()
    endIf
endEvent

int function Unparalyze(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Paralyzed()
        return CODES.ISNT_PARALYZED
    endIf

    p_is_paralyzed = false

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Unparalyze")
    else
        p_Unparalyze()
    endIf

    return CODES.SUCCESS
endFunction
event On_Unparalyze()
    if Is_Unparalyzed()
        p_Unparalyze()
    endIf
endEvent

int function Mannequinize(int code_exec, ObjectReference ref_marker)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Is_Mannequin()
        return CODES.IS_MANNEQUIN
    endIf

    if !ref_marker
        return CODES.HASNT_MARKER
    endIf

    p_is_mannequin = true
    p_marker_mannequin = ref_marker

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Mannequinize")
    else
        p_Mannequinize()
    endIf

    return CODES.SUCCESS
endFunction
event On_Mannequinize()
    if Is_Mannequin()
        p_Mannequinize()
    endIf
endEvent

int function Unmannequinize(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Mannequin()
        return CODES.ISNT_MANNEQUIN
    endIf

    p_marker_mannequin = none
    p_is_mannequin = false

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Unmannequinize")
    else
        p_Unmannequinize()
    endIf

    return CODES.SUCCESS
endFunction
event On_Unmannequinize()
    if Isnt_Mannequin()
        p_Unmannequinize()
    endIf
endEvent

int function Follow()
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Is_Follower()
        return CODES.IS_FOLLOWER
    endIf

    if Is_Mannequin()
        return CODES.IS_MANNEQUIN
    endIf

    int code_return = FOLLOWERS.f_Create_Follower(p_ref_actor)
    if code_return < 0
        return code_return
    endIf

    p_is_follower = true

    p_Outfit()

    return CODES.SUCCESS
endFunction

int function Unfollow()
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !Is_Follower()
        return CODES.ISNT_FOLLOWER
    endIf

    int code_return = FOLLOWERS.f_Destroy_Follower(p_ref_actor)
    if code_return < 0
        return code_return
    endIf

    p_is_follower = false

    p_Outfit()

    return CODES.SUCCESS
endFunction

int function Resurrect(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if ACTORS.Is_Alive(p_ref_actor)
        return CODES.IS_ALIVE
    endIf

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Resurrect")
    else
        p_Resurrect()
    endIf

    return CODES.SUCCESS
endFunction
event On_Resurrect()
    if Is_Dead()
        p_Resurrect()
    endIf
endEvent

int function Reanimate(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    ; we set this here for the queue to check
    p_is_reanimated = true

    ; we accept an already alive member to make it easier on creation, but maybe not once we make a dedicated Create_Reanimated()
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Reanimate")
    else
        if Is_Dead()
            p_Resurrect()
        endIf
        p_Reanimate()
    endIf

    return CODES.SUCCESS
endFunction
event On_Reanimate()
    if Is_Reanimated()
        if Is_Dead()
            p_Resurrect()
        endIf
        p_Reanimate()
    endIf
endEvent

int function Deanimate(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    ; we set this here for the queue to check
    p_is_reanimated = false

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Deanimate")
    else
        if Is_Alive()
            p_Kill()
        endIf
        p_Deanimate()
    endIf

    return CODES.SUCCESS
endFunction
event On_Deanimate()
    if Isnt_Reanimated()
        if Is_Alive()
            p_Kill()
        endIf
        p_Deanimate()
    endIf
endEvent

int function Style(int code_exec, int code_style)
    if code_style == CODES.IS_DEFAULT
        return Style_Default(code_exec)
    elseIf code_style == CODES.IS_WARRIOR
        return Style_Warrior(code_exec)
    elseIf code_style == CODES.IS_MAGE
        return Style_Mage(code_exec)
    elseIf code_style == CODES.IS_ARCHER
        return Style_Archer(code_exec)
    elseIf code_style == CODES.IS_COWARD
        return Style_Coward(code_exec)
    endIf
endFunction
event On_Style()
    p_Style()
endEvent

int function Style_Default(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Get_Style() == CODES.IS_DEFAULT
        return CODES.IS_DEFAULT
    endIf

    p_Set_Style(CODES.IS_DEFAULT)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Style")
    else
        p_Style()
    endIf

    return CODES.SUCCESS
endFunction

int function Style_Warrior(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Get_Style() == CODES.IS_WARRIOR
        return CODES.IS_WARRIOR
    endIf

    p_Set_Style(CODES.IS_WARRIOR)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Style")
    else
        p_Style()
    endIf

    return CODES.SUCCESS
endFunction

int function Style_Mage(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Get_Style() == CODES.IS_MAGE
        return CODES.IS_MAGE
    endIf

    p_Set_Style(CODES.IS_MAGE)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Style")
    else
        p_Style()
    endIf

    return CODES.SUCCESS
endFunction

int function Style_Archer(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Get_Style() == CODES.IS_ARCHER
        return CODES.IS_ARCHER
    endIf

    p_Set_Style(CODES.IS_ARCHER)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Style")
    else
        p_Style()
    endIf

    return CODES.SUCCESS
endFunction

int function Style_Coward(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Get_Style() == CODES.IS_COWARD
        return CODES.IS_COWARD
    endIf

    p_Set_Style(CODES.IS_COWARD)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Style")
    else
        p_Style()
    endIf

    return CODES.SUCCESS
endFunction

int function Vitalize(int code_exec, int code_vitality)
    if code_vitality == CODES.IS_MORTAL
        return Vitalize_Mortal(code_exec)
    elseIf code_vitality == CODES.IS_PROTECTED
        return Vitalize_Protected(code_exec)
    elseIf code_vitality == CODES.IS_ESSENTIAL
        return Vitalize_Essential(code_exec)
    elseIf code_vitality == CODES.IS_INVULNERABLE
        return Vitalize_Invulnerable(code_exec)
    endIf
endFunction
event On_Vitalize()
    p_Vitalize()
endEvent

int function Vitalize_Mortal(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Get_Vitality() == CODES.IS_MORTAL
        return CODES.IS_MORTAL
    endIf

    p_Set_Vitality(CODES.IS_MORTAL)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Vitalize")
    else
        p_Vitalize()
    endIf

    return CODES.SUCCESS
endFunction

int function Vitalize_Protected(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Get_Vitality() == CODES.IS_PROTECTED
        return CODES.IS_PROTECTED
    endIf

    p_Set_Vitality(CODES.IS_PROTECTED)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Vitalize")
    else
        p_Vitalize()
    endIf

    return CODES.SUCCESS
endFunction

int function Vitalize_Essential(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Get_Vitality() == CODES.IS_ESSENTIAL
        return CODES.IS_ESSENTIAL
    endIf

    p_Set_Vitality(CODES.IS_ESSENTIAL)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Vitalize")
    else
        p_Vitalize()
    endIf

    return CODES.SUCCESS
endFunction

int function Vitalize_Invulnerable(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if Get_Vitality() == CODES.IS_INVULNERABLE
        return CODES.IS_INVULNERABLE
    endIf

    p_Set_Vitality(CODES.IS_INVULNERABLE)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Vitalize")
    else
        p_Vitalize()
    endIf

    return CODES.SUCCESS
endFunction

; can this one actually be async?
int function Pack(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if code_exec == CODES.DO_ASYNC
        p_Async("On_Pack")
    else
        p_Pack()
    endIf

    return CODES.SUCCESS
endFunction
event On_Pack()
    p_Pack()
endEvent

int function Outfit(int code_exec, int code_outfit)
    if code_outfit == CODES.OUTFIT_MEMBER
        return Outfit_Member(code_exec)
    elseIf code_outfit == CODES.OUTFIT_SETTLER
        return Outfit_Settler(code_exec)
    elseIf code_outfit == CODES.OUTFIT_THRALL
        return Outfit_Thrall(code_exec)
    elseIf code_outfit == CODES.OUTFIT_IMMOBILE
        return Outfit_Immobile(code_exec)
    elseIf code_outfit == CODES.OUTFIT_FOLLOWER
        return Outfit_Follower(code_exec)
    elseIf code_outfit == CODES.OUTFIT_CURRENT
        return Outfit_Current(code_exec)
    elseIf code_outfit == CODES.OUTFIT_VANILLA
        return Outfit_Vanilla(code_exec)
    elseIf code_outfit == CODES.OUTFIT_DEFAULT
        return Outfit_Default(code_exec)
    endIf
endFunction
event On_Outfit()
    p_Outfit()
endEvent

int function Outfit_Member(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Put_Outfit(CODES.OUTFIT_MEMBER)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Settler(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Put_Outfit(CODES.OUTFIT_SETTLER)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Thrall(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Put_Outfit(CODES.OUTFIT_THRALL)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Immobile(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Put_Outfit(CODES.OUTFIT_IMMOBILE)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Follower(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Put_Outfit(CODES.OUTFIT_FOLLOWER)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Current(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Put_Outfit(CODES.OUTFIT_CURRENT)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Vanilla(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Put_Outfit(CODES.OUTFIT_VANILLA)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return CODES.SUCCESS
endFunction

int function Outfit_Default(int code_exec)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    p_Put_Outfit(CODES.OUTFIT_DEFAULT)
    if code_exec == CODES.DO_ASYNC
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return CODES.SUCCESS
endFunction

int function Get_Rating()
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    return p_int_rating
endFunction

int function Set_Rating(int int_rating)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if int_rating < 0 || int_rating > 5
        return CODES.ISNT_RATING
    endIf

    p_int_rating = int_rating
    
    MEMBERS.Request_Sort()

    if Is_Follower()
        FOLLOWERS.Request_Sort()
    endIf

    return CODES.SUCCESS
endFunction

string function Get_Rating_Stars()
    if !Exists()
        return ""
    endIf

    if false

    elseIf p_int_rating == 0
        return "-"
    elseIf p_int_rating == 1
        return "*"
    elseIf p_int_rating == 2
        return "**"
    elseIf p_int_rating == 3
        return "***"
    elseIf p_int_rating == 4
        return "****"
    elseIf p_int_rating == 5
        return "*****"
    
    endIf
endFunction

int function Display(ObjectReference ref_marker, int distance, int angle)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if ACTORS.Has_Token(p_ref_actor, CONSTS.TOKEN_DISPLAY)
        return CODES.IS_DISPLAY
    endIf

    ACTORS.Token(p_ref_actor, CONSTS.TOKEN_DISPLAY)

    p_marker_display = p_ref_actor.PlaceAtMe(CONSTS.STATIC_MARKER_X)

    ACTORS.Move_To(p_ref_actor as ObjectReference, ref_marker, distance, angle)

    p_Remannequinize()
    p_Reparalyze()

    return CODES.SUCCESS
endFunction

int function Undisplay()
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !ACTORS.Has_Token(p_ref_actor, CONSTS.TOKEN_DISPLAY)
        return CODES.ISNT_DISPLAY
    endIf

    ACTORS.Untoken(p_ref_actor, CONSTS.TOKEN_DISPLAY)

    p_ref_actor.MoveTo(p_marker_display)

    p_marker_display.Disable()
    p_marker_display.Delete()
    p_marker_display = none

    return CODES.SUCCESS
endFunction

int function Unmember()
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
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    return p_Clone()
endFunction

int function Unclone()
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    if !p_is_clone
        return CODES.ISNT_CLONE
    endIf

    return MEMBERS.Destroy_Member(p_ref_actor, true)
endFunction

int function Summon(int distance = 120, int angle = 0)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    ; we don't allow mannequins to be removed, until they are unmannequinized
    if Is_Mannequin()
        return CODES.IS_MANNEQUIN
    endIf

    ACTORS.Move_To(p_ref_actor, CONSTS.ACTOR_PLAYER, distance, angle)

    p_Remannequinize()
    p_Reparalyze()

    return CODES.SUCCESS
endFunction

int function Summon_Ahead(int distance = 120)
    return Summon(distance, 0)
endFunction

int function Summon_Behind(int distance = 120)
    return Summon(distance, 180)
endFunction

int function Goto(int distance = 120, int angle = 0)
    if !Exists()
        return CODES.ISNT_MEMBER
    endIf

    ; this is done so that we can exit expo gracefully
    MANNEQUINS.f_Try_Set_Teleport(self)

    ACTORS.Move_To(CONSTS.ACTOR_PLAYER, p_ref_actor, distance, angle)

    p_Remannequinize()
    p_Reparalyze()

    return CODES.SUCCESS
endFunction

bool function Is_Member()
    return Exists()
endFunction

bool function Is_Unique()
    return Exists() && ACTORS.Is_Unique(p_ref_actor)
endFunction

bool function Is_Generic()
    return Exists() && ACTORS.Is_Generic(p_ref_actor)
endFunction

bool function Is_Original()
    return Exists() && !p_is_clone
endFunction

bool function Is_Clone()
    return Exists() && p_is_clone
endFunction

bool function Is_Settler()
    return Exists() && p_is_settler
endFunction

bool function Isnt_Settler()
    return Exists() && !p_is_settler
endFunction

bool function Is_Thrall()
    return Exists() && p_is_thrall
endFunction

bool function Isnt_Thrall()
    return Exists() && !p_is_thrall
endFunction

bool function Is_Immobile()
    return Exists() && p_is_immobile
endFunction

bool function Is_Mobile()
    return Exists() && !p_is_immobile
endFunction

bool function Is_Paralyzed()
    return Exists() && p_is_paralyzed
endFunction

bool function Is_Unparalyzed()
    return Exists() && !p_is_paralyzed
endFunction

bool function Is_Mannequin()
    return Exists() && p_is_mannequin
endFunction

bool function Isnt_Mannequin()
    return Exists() && !p_is_mannequin
endFunction

bool function Is_Reanimated()
    return Exists() && p_is_reanimated
endFunction

bool function Isnt_Reanimated()
    return Exists() && !p_is_reanimated
endFunction

bool function Is_Sneak()
    return Is_Follower() && Get_Follower().Is_Sneak()
endFunction

bool function Is_Unsneak()
    return Is_Follower() && Get_Follower().Is_Unsneak()
endFunction

bool function Is_Follower()
    return Exists() && p_is_follower
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

bool function Is_Styled_Coward()
    return Exists() && p_code_style == CODES.IS_COWARD
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

bool function Is_Alive()
    return Exists() && ACTORS.Is_Alive(p_ref_actor)
endFunction

bool function Is_Dead()
    return Exists() && ACTORS.Is_Dead(p_ref_actor)
endFunction

bool function Is_In_Combat()
    return Exists() && p_ref_actor.IsInCombat()
endFunction

; Events
event OnLoad()
    if !MAIN.Is_Ready()
        return
    endIf

    Enforce()
endEvent

event OnActivate(ObjectReference ref_activator)
    if VARS.is_updating || !Exists()
        return
    endIf

    if Is_Alive()
        ; this should allow the player to talk with npcs that don't normally talk, or refuse to
        if !p_ref_actor.IsInDialogueWithPlayer() && p_ref_actor.IsAIEnabled()
            ACTORS.Greet_Player(p_ref_actor)
        endIf

        Enforce()
        
        ; instead of polling, we might be able to set up a package that happens only when in dialogue
        ; and wait for the Package change or end event to let us know dialogue is over.
        while Exists() && p_ref_actor && p_ref_actor.IsInDialogueWithPlayer()
            ; we could do an outfit in here if we detect vanilla change
            ; we might also have npcp commands start up this func if it
            ; wasn't already called. it would lead to more consistency.
            Utility.Wait(2)
        endWhile

        ; it's entirely possible that the ref may no longer be a member at this
        ; point through dialogue selections. so we need to check to avoid error
        if Exists()
            ; we need to lock so that one ref at a time can do this check. we don't want
            ; every ref to get the new outfit, or we may be changing outfit on another ref.
            ; for the same reason we only check right after dialgoue, so the mod must have changed it by now.
NPCS.Lock_Base(p_ref_actor)
            Outfit outfit_vanilla = ACTORS.Get_Base_Outfit(p_ref_actor)
            Outfit outfit_default = NPCS.Get_Default_Outfit(p_ref_actor)
            ; we reset the default, so outfitter doesn't detect the base npc outfit has been changed, and set the default on NPCS
            ACTORS.Set_Base_Outfit(p_ref_actor, outfit_default)
NPCS.Unlock_Base(p_ref_actor)
            if outfit_vanilla && outfit_vanilla != outfit_default
                ; one drawback of this method is that there is no way to tell if the default
                ; outfit has been selected through an outfit mod. we could rig something through
                ; Set_Outfit in c++, but prob. not worth it atm
                p_outfit_vanilla = outfit_vanilla
                p_do_outfit_vanilla = true
                p_Outfit()
            endIf
        endIf
    else
        p_outfit2_current.Put()
        p_Outfit()
    endIf
endEvent

event OnHit(ObjectReference ref_attacker, Form _, Projectile __, bool ___, bool ____, bool _____, bool ______)
    if VARS.is_updating
        return
    endIf

    ; we did have a stack dump related to this function once. might keep an eye on it
    if !p_ref_actor.IsDead() && p_ref_actor.GetActorValue(CONSTS.STR_HEALTH) <= 0
        if p_code_vitality == CODES.IS_MORTAL || p_code_vitality == CODES.IS_PROTECTED && ref_attacker == CONSTS.ACTOR_PLAYER
            p_Kill()
        endIf
    elseIf p_code_vitality == CODES.IS_INVULNERABLE
        p_ref_actor.RestoreActorValue(CONSTS.STR_HEALTH, 99999)
    endIf
endEvent

event OnCombatStateChanged(Actor ref_target, int code_combat)
    if VARS.is_updating
        return
    endIf

    if ref_target == CONSTS.ACTOR_PLAYER
        ACTORS.Pacify(p_ref_actor)
    elseIf ACTORS.Has_Token(ref_target, CONSTS.TOKEN_MEMBER)
        ACTORS.Pacify(p_ref_actor)
        ACTORS.Pacify(ref_target)
    endIf

    if Is_Follower()
        ; see OnCombatStateChanged in doticu_npcp_follower
        return
    endIf

    if code_combat == CODES.COMBAT_NO
        Enforce()
    elseIf code_combat == CODES.COMBAT_YES

    elseIf code_combat == CODES.COMBAT_SEARCHING
        
    endIf
endEvent

event OnDeath(Actor ref_killer)
    if Is_Reanimated()
        p_Deanimate()
    endIf
endEvent

; Update Methods
doticu_npcp_queue p_queue_member = none
doticu_npcp_container p_container2_pack = none
function u_0_9_0()
    if Exists()
        p_queue_member.Disable()
        p_queue_member.Delete()
        p_queue_member = none

        p_container_pack = p_container2_pack
        p_container2_pack = none

        ; so that we can easily filter followers
        if FOLLOWERS.Has_Follower(p_ref_actor)
            p_is_follower = true
        endIf
    endIf
endFunction
