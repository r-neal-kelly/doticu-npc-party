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
Actor                   p_ref_actor                 =  none
bool                    p_is_clone                  = false
bool                    p_is_settler                = false
bool                    p_is_thrall                 = false
bool                    p_is_immobile               = false
bool                    p_is_paralyzed              = false
bool                    p_is_mannequin              = false
bool                    p_is_reanimated             = false
bool                    p_is_display                = false
bool                    p_do_outfit_vanilla         = false
int                     p_code_style                =     0
int                     p_code_vitality             =     0
int                     p_code_outfit2              =     0
int                     p_int_rating                =     0
ObjectReference         p_marker_mannequin          =  none
ObjectReference         p_marker_display            =  none
ObjectReference         p_marker_undisplay          =  none
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
doticu_npcp_outfit      p_outfit2_auto_backup       =  none

Faction[]               p_prev_factions             =  none
int[]                   p_prev_faction_ranks        =  none
Faction                 p_prev_faction_crime        =  none
float                   p_prev_aggression           =   0.0
float                   p_prev_confidence           =   0.0
float                   p_prev_assistance           =   0.0
float                   p_prev_morality             =   0.0

; Native Methods
Actor function Actor() native
int function ID() native

int function Style() native
int function Vitality() native
string function Name() native

bool function Is_Filled() native
bool function Is_Unfilled() native
bool function Is_Loaded() native
bool function Is_Unloaded() native
bool function Is_Unique() native
bool function Is_Generic() native
bool function Is_Original() native
bool function Is_Clone() native
bool function Is_Alive() native
bool function Is_Dead() native
bool function Is_Mobile() native
bool function Is_Immobile() native
bool function Is_Settler() native
bool function Isnt_Settler() native
bool function Is_Thrall() native
bool function Isnt_Thrall() native
bool function Is_Paralyzed() native
bool function Isnt_Paralyzed() native
bool function Is_Mannequin() native
bool function Isnt_Mannequin() native
bool function Is_Display() native
bool function Isnt_Display() native
bool function Is_Reanimated() native
bool function Isnt_Reanimated() native
bool function Is_Follower() native
bool function Isnt_Follower() native
bool function Is_Sneak() native
bool function Isnt_Sneak() native
bool function Is_Saddler() native
bool function Isnt_Saddler() native
bool function Is_Retreater() native
bool function Isnt_Retreater() native

bool function Has_Token(MiscObject token, int count = 1) native
function Token(MiscObject token, int count = 1) native
function Untoken(MiscObject token) native

function p_Member() native
function p_Unmember() native
function p_Mobilize() native
function p_Immobilize() native
function p_Settle() native
function p_Unsettle() native
function p_Enthrall() native
function p_Unthrall() native
function p_Paralyze() native
function p_Unparalyze() native
function p_Mannequinize(ObjectReference marker) native
function p_Unmannequinize() native

int function Stylize(int style) native
int function Stylize_Default() native
int function Stylize_Warrior() native
int function Stylize_Mage() native
int function Stylize_Archer() native
int function Stylize_Coward() native
function p_Restylize(Actor ref_actor) native
int function Unstylize() native

function p_Vitalize(int vitality) native
function p_Unvitalize() native

function p_Rename(string new_name) native

function Log_Variable_Infos() native

; Friend Methods
function f_Create(doticu_npcp_data DATA, Actor ref_actor, bool is_clone)
p_Lock()

    p_DATA = DATA

    ForceRefTo(ref_actor)

    p_ref_actor = GetActorReference()
    p_is_clone = is_clone
    p_is_settler = false
    p_is_thrall = false
    p_is_immobile = false
    p_is_paralyzed = false
    p_is_mannequin = false
    p_is_reanimated = false
    p_is_display = false
    
    p_do_outfit_vanilla = false
    p_code_outfit2 = doticu_npcp_codes.OUTFIT2_MEMBER()
    p_int_rating = 0
    p_marker_display = none
    p_marker_undisplay = none
    p_marker_mannequin = none
    p_outfit_vanilla = NPCS.Default_Outfit(p_ref_actor)

p_Unlock()

    p_Create_Container()
    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_MEMBER())
    p_Backup()

    p_Member()
    Stylize(VARS.auto_style)
    p_Vitalize(VARS.auto_vitality)
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
    Unstylize()
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

    p_Restore()
    p_Destroy_Outfits()
    p_Destroy_Containers()

p_Lock()

    p_prev_morality = 0.0
    p_prev_assistance = 0.0
    p_prev_confidence = 0.0
    p_prev_aggression = 0.0
    p_prev_faction_crime = none
    p_prev_faction_ranks = new int[1]
    p_prev_factions = new Faction[1]

    p_outfit2_auto_backup = none
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
    p_marker_undisplay = none
    p_marker_display = none
    p_int_rating = 0
    p_code_outfit2 = -1
    p_code_vitality = -1
    p_code_style = -1
    p_do_outfit_vanilla = false
    p_is_display = false
    p_is_reanimated = false
    p_is_mannequin = false
    p_is_paralyzed = false
    p_is_immobile = false
    p_is_thrall = false
    p_is_settler = false
    p_is_clone = false
    p_ref_actor = none

    Clear()
    
p_Unlock()
endFunction

int function f_Get_ID()
    return ID()
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

function p_Create_Container()
p_Lock()

    p_container_pack = CONTAINERS.Create_Perm()

p_Unlock()
endFunction

function p_Destroy_Containers()
p_Lock()

    doticu_npcp.Object_Ref_Categorize(p_container_pack)
    CONTAINERS.Destroy_Perm(p_container_pack)

p_Unlock()
endFunction

function p_Backup()
p_Lock()

    p_prev_factions = ACTORS.Get_Factions(p_ref_actor)
    p_prev_faction_ranks = ACTORS.Get_Faction_Ranks(p_ref_actor, p_prev_factions)
    p_prev_faction_crime = p_ref_actor.GetCrimeFaction()

    p_prev_aggression = p_ref_actor.GetBaseActorValue("Aggression")
    p_prev_confidence = p_ref_actor.GetBaseActorValue("Confidence")
    p_prev_assistance = p_ref_actor.GetBaseActorValue("Assistance")
    p_prev_morality = p_ref_actor.GetBaseActorValue("Morality")

p_Unlock()
endFunction

function p_Restore()
p_Lock()

    p_ref_actor.SetActorValue("Morality", p_prev_morality)
    p_ref_actor.SetActorValue("Assistance", p_prev_assistance)
    p_ref_actor.SetActorValue("Confidence", p_prev_confidence)
    p_ref_actor.SetActorValue("Aggression", 0.0)

    ACTORS.Set_Factions(p_ref_actor, p_prev_factions, p_prev_faction_ranks)
    p_ref_actor.SetCrimeFaction(p_prev_faction_crime)

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
    FUNCS.Wait(0.1)

p_Unlock()

    p_Paralyze()
endFunction

; we may not need this.
function p_Remannequinize()
    if !Is_Mannequin()
        return
    endIf
    
p_Lock()

    p_ref_actor.EnableAI(false)
    p_ref_actor.SetGhost(true)
    p_ref_actor.BlockActivation(true)

    ; this allows the mannequin to be called on display
    if !p_is_display
        p_ref_actor.MoveTo(p_marker_mannequin)
    endIf

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

function p_Create_Outfit(int code_outfit2)
p_Lock()

    if code_outfit2 == doticu_npcp_codes.OUTFIT2_CURRENT()
        code_outfit2 = p_code_outfit2
    endIf

    if code_outfit2 == doticu_npcp_codes.OUTFIT2_MEMBER()
        if !p_outfit2_member
            p_outfit2_member = OUTFITS.Create()
            if VARS.fill_outfits
                p_outfit2_member.Get(p_ref_actor, p_container_pack)
            else
                p_ref_actor.RemoveAllItems(p_container_pack, true, false)
            endIf
            p_outfit2_previous = p_outfit2_member
            p_outfit2_current = p_outfit2_member
        endIf
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_SETTLER()
        if !p_outfit2_settler
            p_outfit2_settler = OUTFITS.Create_Settler()
        endIf
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_THRALL()
        if !p_outfit2_thrall
            p_outfit2_thrall = OUTFITS.Create_Thrall()
        endIf
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_IMMOBILE()
        if !p_outfit2_immobile
            p_outfit2_immobile = OUTFITS.Create_Immobile()
        endIf
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_FOLLOWER()
        if !p_outfit2_follower
            p_outfit2_follower = OUTFITS.Create_Follower()
        endIf
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_VANILLA()
        if !p_outfit2_vanilla
            p_outfit2_vanilla = OUTFITS.Create_Vanilla()
        endIf
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_DEFAULT()
        if !p_outfit2_default
            p_outfit2_default = OUTFITS.Create_Default()
            p_outfit2_default.Get_Default(p_ref_actor)
        endIf
    endIf
    
p_Unlock()
endFunction

function p_Destroy_Outfits()
p_Lock()

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
    if p_outfit2_member
        OUTFITS.Destroy(p_outfit2_member)
    endIf

p_Unlock()
endFunction

function p_Put_Outfit(int code_outfit2)
p_Lock()

    if code_outfit2 == doticu_npcp_codes.OUTFIT2_CURRENT()
        code_outfit2 = p_code_outfit2
    endIf

    if code_outfit2 == doticu_npcp_codes.OUTFIT2_MEMBER()
        p_outfit2_member.Rename(Name() + "'s Member Outfit")
        p_outfit2_member.Put()
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_SETTLER()
        p_outfit2_settler.Rename(Name() + "'s Settler Outfit")
        p_outfit2_settler.Put()
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_THRALL()
        p_outfit2_thrall.Rename(Name() + "'s Thrall Outfit")
        p_outfit2_thrall.Put()
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_IMMOBILE()
        p_outfit2_immobile.Rename(Name() + "'s Immobile Outfit")
        p_outfit2_immobile.Put()
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_FOLLOWER()
        p_outfit2_follower.Rename(Name() + "'s Follower Outfit")
        p_outfit2_follower.Put()
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_VANILLA()
        p_outfit2_vanilla.Rename(Name() + "'s Vanilla Outfit")
        p_outfit2_vanilla.Put()
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_DEFAULT()
        p_outfit2_default.Rename(Name() + "'s Default Outfit")
        p_outfit2_default.Put()
    else
        p_outfit2_member.Rename(Name() + "'s Member Outfit")
        p_outfit2_member.Put()
    endIf

p_Unlock()
endFunction

function p_Set_Outfit(int code_outfit2)
p_Lock()

    p_outfit2_previous = p_outfit2_current

    if code_outfit2 == doticu_npcp_codes.OUTFIT2_CURRENT()
        code_outfit2 = p_code_outfit2
    endIf

    if code_outfit2 == doticu_npcp_codes.OUTFIT2_MEMBER()
        p_outfit2_current = p_outfit2_member
        p_outfit2_auto_backup = p_outfit2_member
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_SETTLER()
        p_outfit2_current = p_outfit2_settler
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_THRALL()
        p_outfit2_current = p_outfit2_thrall
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_IMMOBILE()
        p_outfit2_current = p_outfit2_immobile
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_FOLLOWER()
        p_outfit2_current = p_outfit2_follower
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_VANILLA()
        p_outfit2_current = p_outfit2_vanilla
        p_outfit2_auto_backup = p_outfit2_vanilla
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_DEFAULT()
        p_outfit2_current = p_outfit2_default
        p_outfit2_auto_backup = p_outfit2_default
    else
        code_outfit2 = doticu_npcp_codes.OUTFIT2_MEMBER()
        p_outfit2_current = p_outfit2_member
        p_outfit2_auto_backup = p_outfit2_member
    endIf

    p_code_outfit2 = code_outfit2

p_Unlock()
endFunction

function p_Outfit()
    if VARS.auto_outfit
        if Is_Immobile() && VARS.auto_immobile_outfit
            p_Create_Outfit(doticu_npcp_codes.OUTFIT2_IMMOBILE())
            p_Set_Outfit(doticu_npcp_codes.OUTFIT2_IMMOBILE())
        elseIf Is_Follower()
            p_Create_Outfit(doticu_npcp_codes.OUTFIT2_FOLLOWER())
            p_Set_Outfit(doticu_npcp_codes.OUTFIT2_FOLLOWER())
        elseIf Is_Thrall()
            p_Create_Outfit(doticu_npcp_codes.OUTFIT2_THRALL())
            p_Set_Outfit(doticu_npcp_codes.OUTFIT2_THRALL())
        elseIf Is_Settler()
            p_Create_Outfit(doticu_npcp_codes.OUTFIT2_SETTLER())
            p_Set_Outfit(doticu_npcp_codes.OUTFIT2_SETTLER())
        elseIf p_outfit2_auto_backup
            if p_outfit2_auto_backup == p_outfit2_vanilla
                p_Set_Outfit(doticu_npcp_codes.OUTFIT2_VANILLA())
            elseIf p_outfit2_auto_backup == p_outfit2_default
                p_Set_Outfit(doticu_npcp_codes.OUTFIT2_DEFAULT())
            else
                p_Set_Outfit(doticu_npcp_codes.OUTFIT2_MEMBER())
            endif
        else
            p_Set_Outfit(doticu_npcp_codes.OUTFIT2_MEMBER())
        endIf
    endIf

p_Lock()

    if p_do_outfit_vanilla
        p_do_outfit_vanilla = false
        p_outfit2_current = p_outfit2_vanilla; we don't want the next Outfit() to call branch below unless changed otherwise
        p_Create_Outfit(doticu_npcp_codes.OUTFIT2_VANILLA())
        p_Set_Outfit(doticu_npcp_codes.OUTFIT2_VANILLA())
        p_outfit2_vanilla.Cache_Vanilla_Dynamic(p_ref_actor)
        p_outfit2_vanilla.Set(p_ref_actor, p_container_pack)
    elseIf p_outfit2_previous != p_outfit2_current
        p_outfit2_previous = p_outfit2_current
        if p_outfit2_current == p_outfit2_vanilla
            p_outfit2_current.Cache_Vanilla_Static(p_outfit_vanilla)
        elseIf p_outfit2_current == p_outfit2_default
            p_outfit2_current.Cache_Vanilla_Static(NPCS.Default_Outfit(p_ref_actor))
        endIf
        p_outfit2_current.Set(p_ref_actor, p_container_pack)
    else
        ; this is just a way to do asyncronous updating for 0.9.0+
        if p_outfit2_current == p_outfit2_vanilla
            p_outfit2_current.Try_Cache_Vanilla(p_outfit_vanilla)
        elseIf p_outfit2_current == p_outfit2_default
            p_outfit2_current.Try_Cache_Vanilla(NPCS.Default_Outfit(p_ref_actor))
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

function p_Pack()
p_Lock()

    CONTAINERS.Rename(p_container_pack, Name() + "'s Pack")
    CONTAINERS.Open(p_container_pack)

p_Unlock()
endFunction

function p_Stash()
p_Lock()

    doticu_npcp.Object_Ref_Categorize(p_container_pack)

p_Unlock()
endFunction

function p_Async(string str_func)
    string str_event = "doticu_npcp_member_async_" + ID()

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

    FUNCS.Wait(0.1)
    if !Exists() || Is_Dead()
        return
    endIf

    p_Outfit()

    p_Member()

    p_Restylize(p_ref_actor)

    p_Vitalize(p_code_vitality)

    FUNCS.Wait(0.1)
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

bool function Exists()
    return Is_Filled()
endFunction

doticu_npcp_follower function Get_Follower()
    if !Exists() || !Is_Follower()
        return none
    else
        return FOLLOWERS.Get_Follower(p_ref_actor)
    endIf
endFunction

int function Get_Outfit2()
    if !Exists() || p_outfit2_current == none
        return -1
    else
        return p_code_outfit2
    endIf
endFunction

int function Rename(string str_name)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Rename(str_name)
    
    return doticu_npcp_codes.SUCCESS()
endFunction

int function Mobilize()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if !Is_Immobile()
        return doticu_npcp_codes.IS()
    endIf

    p_Mobilize()

    p_Async("On_Outfit")

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Immobilize()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if Is_Immobile()
        return doticu_npcp_codes.IS()
    endIf

    p_Immobilize()

    p_Async("On_Outfit")

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Settle()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if Is_Settler()
        return doticu_npcp_codes.IS()
    endIf

    p_Settle()

    p_Async("On_Outfit")

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Resettle()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if !Is_Settler()
        return doticu_npcp_codes.ISNT()
    endIf

    p_Settle()

    p_Async("On_Outfit")

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Unsettle()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if !Is_Settler()
        return doticu_npcp_codes.IS()
    endIf

    p_Unsettle()

    p_Async("On_Outfit")

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Enthrall()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if !ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
        return doticu_npcp_codes.VAMPIRE()
    endIf
    if Is_Thrall()
        return doticu_npcp_codes.IS()
    endIf

    p_Enthrall()

    p_Async("On_Outfit")

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Unthrall()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if !ACTORS.Is_Vampire(CONSTS.ACTOR_PLAYER)
        return doticu_npcp_codes.VAMPIRE()
    endIf
    if !Is_Thrall()
        return doticu_npcp_codes.IS()
    endIf

    p_Unthrall()

    p_Async("On_Outfit")

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Paralyze()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if Is_Paralyzed()
        return doticu_npcp_codes.IS()
    endIf

    p_Paralyze()

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Unparalyze()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if !Is_Paralyzed()
        return doticu_npcp_codes.IS()
    endIf

    p_Unparalyze()

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Mannequinize(ObjectReference ref_marker)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if Is_Mannequin()
        return doticu_npcp_codes.IS()
    endIf
    if !ref_marker
        return doticu_npcp_codes.MARKER()
    endIf

    p_Mannequinize(ref_marker)

    ; this should be moved over to the c++ func when ready.
    if Is_Follower()
        Unfollow()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Unmannequinize()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if !Is_Mannequin()
        return doticu_npcp_codes.IS()
    endIf

    p_Unmannequinize()

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Vitalize(int code_vitality)
    if code_vitality == doticu_npcp_codes.VITALITY_MORTAL()
        return Vitalize_Mortal()
    elseIf code_vitality == doticu_npcp_codes.VITALITY_ESSENTIAL()
        return Vitalize_Essential()
    elseIf code_vitality == doticu_npcp_codes.VITALITY_INVULNERABLE()
        return Vitalize_Invulnerable()
    else ; doticu_npcp_codes.VITALITY_PROTECTED()
        return Vitalize_Protected()
    endIf
endFunction

int function Vitalize_Mortal()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if Vitality() == doticu_npcp_codes.VITALITY_MORTAL()
        return doticu_npcp_codes.IS()
    endIf

    p_Vitalize(doticu_npcp_codes.VITALITY_MORTAL())

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Vitalize_Protected()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if Vitality() == doticu_npcp_codes.VITALITY_PROTECTED()
        return doticu_npcp_codes.IS()
    endIf

    p_Vitalize(doticu_npcp_codes.VITALITY_PROTECTED())

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Vitalize_Essential()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if Vitality() == doticu_npcp_codes.VITALITY_ESSENTIAL()
        return doticu_npcp_codes.IS()
    endIf

    p_Vitalize(doticu_npcp_codes.VITALITY_ESSENTIAL())

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Vitalize_Invulnerable()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf
    if Vitality() == doticu_npcp_codes.VITALITY_INVULNERABLE()
        return doticu_npcp_codes.IS()
    endIf

    p_Vitalize(doticu_npcp_codes.VITALITY_INVULNERABLE())

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Revoice()
    ; the problem is that we would have to change the voice on the actor base. so maybe put in npcs?
    ; maybe there is a way to change the ref? look at the types a little closer.
endFunction

int function Unrevoice()
endFunction

int function Follow()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    if Is_Follower()
        return doticu_npcp_codes.FOLLOWER()
    endIf

    if Is_Mannequin()
        return doticu_npcp_codes.MANNEQUIN()
    endIf

p_Lock()
    int code_return = FOLLOWERS.f_Create_Follower(p_ref_actor)
p_Unlock()
    if code_return != doticu_npcp_codes.SUCCESS()
        return code_return
    endIf

    p_Async("On_Outfit")

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Unfollow()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    if !Is_Follower()
        return doticu_npcp_codes.FOLLOWER()
    endIf

p_Lock()
    int code_return = FOLLOWERS.f_Destroy_Follower(p_ref_actor)
p_Unlock()
    if code_return != doticu_npcp_codes.SUCCESS()
        return code_return
    endIf

    p_Async("On_Outfit")

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Resurrect(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    if ACTORS.Is_Alive(p_ref_actor)
        return doticu_npcp_codes.IS()
    endIf

    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Resurrect")
    else
        p_Resurrect()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction
event On_Resurrect()
    if Is_Dead()
        p_Resurrect()
    endIf
endEvent

int function Reanimate(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    if Is_Alive()
        return doticu_npcp_codes.ALIVE()
    endIf

    p_is_reanimated = true

    ; we accept an already alive member to make it easier on creation, but maybe not once we make a dedicated Create_Reanimated()
    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Reanimate")
    else
        if Is_Dead()
            p_Resurrect()
        endIf
        p_Reanimate()
    endIf

    return doticu_npcp_codes.SUCCESS()
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
        return doticu_npcp_codes.MEMBER()
    endIf

    p_is_reanimated = false

    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Deanimate")
    else
        if Is_Alive()
            p_Kill()
        endIf
        p_Deanimate()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction
event On_Deanimate()
    if Isnt_Reanimated()
        if Is_Alive()
            p_Kill()
        endIf
        p_Deanimate()
    endIf
endEvent

; can this one actually be async?
int function Pack(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Pack")
    else
        p_Pack()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction
event On_Pack()
    p_Pack()
endEvent

int function Stash()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Stash()

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Outfit(int code_exec, int code_outfit2)
    if code_outfit2 == doticu_npcp_codes.OUTFIT2_MEMBER()
        return Outfit_Member(code_exec)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_SETTLER()
        return Outfit_Settler(code_exec)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_THRALL()
        return Outfit_Thrall(code_exec)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_IMMOBILE()
        return Outfit_Immobile(code_exec)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_FOLLOWER()
        return Outfit_Follower(code_exec)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_VANILLA()
        return Outfit_Vanilla(code_exec)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_DEFAULT()
        return Outfit_Default(code_exec)
    elseIf code_outfit2 == doticu_npcp_codes.OUTFIT2_CURRENT()
        return Outfit_Current(code_exec)
    endIf
endFunction
event On_Outfit()
    p_Outfit()
endEvent

int function Outfit_Member(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_MEMBER())
    p_Set_Outfit(doticu_npcp_codes.OUTFIT2_MEMBER())
    p_Put_Outfit(doticu_npcp_codes.OUTFIT2_MEMBER())
    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Outfit_Settler(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_SETTLER())
    p_Set_Outfit(doticu_npcp_codes.OUTFIT2_SETTLER())
    p_Put_Outfit(doticu_npcp_codes.OUTFIT2_SETTLER())
    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Outfit_Thrall(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_THRALL())
    p_Set_Outfit(doticu_npcp_codes.OUTFIT2_THRALL())
    p_Put_Outfit(doticu_npcp_codes.OUTFIT2_THRALL())
    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Outfit_Immobile(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_IMMOBILE())
    p_Set_Outfit(doticu_npcp_codes.OUTFIT2_IMMOBILE())
    p_Put_Outfit(doticu_npcp_codes.OUTFIT2_IMMOBILE())
    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Outfit_Follower(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_FOLLOWER())
    p_Set_Outfit(doticu_npcp_codes.OUTFIT2_FOLLOWER())
    p_Put_Outfit(doticu_npcp_codes.OUTFIT2_FOLLOWER())
    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Outfit_Vanilla(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_VANILLA())
    p_Set_Outfit(doticu_npcp_codes.OUTFIT2_VANILLA())
    p_Put_Outfit(doticu_npcp_codes.OUTFIT2_VANILLA())
    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Outfit_Default(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_DEFAULT())
    p_Set_Outfit(doticu_npcp_codes.OUTFIT2_DEFAULT())
    p_Put_Outfit(doticu_npcp_codes.OUTFIT2_DEFAULT())
    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Outfit_Current(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Create_Outfit(doticu_npcp_codes.OUTFIT2_CURRENT())
    p_Set_Outfit(doticu_npcp_codes.OUTFIT2_CURRENT())
    p_Put_Outfit(doticu_npcp_codes.OUTFIT2_CURRENT())
    if code_exec == doticu_npcp_codes.ASYNC()
        p_Async("On_Outfit")
    else
        p_Outfit()
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Get_Rating()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    return p_int_rating
endFunction

int function Set_Rating(int int_rating)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    if int_rating < 0 || int_rating > 5
        return doticu_npcp_codes.ISNT()
    endIf

    p_int_rating = int_rating

    return doticu_npcp_codes.SUCCESS()
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

int function Unmember()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    return MEMBERS.Destroy_Member(p_ref_actor)
endFunction

int function Clone()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    return MEMBERS.Clone(p_ref_actor)
endFunction

int function Unclone()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    return MEMBERS.Unclone(p_ref_actor, true)
endFunction

int function Summon(int distance = 120, int angle = 0)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    ; we don't allow mannequins to be removed, until they are unmannequinized
    if Is_Mannequin()
        return doticu_npcp_codes.MANNEQUIN()
    endIf

    ACTORS.Move_To(p_ref_actor, CONSTS.ACTOR_PLAYER, distance, angle)

    p_Remannequinize()
    p_Reparalyze()

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Summon_Ahead(int distance = 120)
    return Summon(distance, 0)
endFunction

int function Summon_Behind(int distance = 120)
    return Summon(distance, 180)
endFunction

int function Goto(int distance = 120, int angle = 0)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    ; this is done so that we can exit expo gracefully
    MANNEQUINS.f_Try_Set_Teleport(self)

    ACTORS.Move_To(CONSTS.ACTOR_PLAYER, p_ref_actor, distance, angle)

    p_Remannequinize()
    p_Reparalyze()

    return doticu_npcp_codes.SUCCESS()
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

event OnActivate(ObjectReference activator_obj)
    if VARS.is_updating || !Exists() || activator_obj != CONSTS.ACTOR_PLAYER
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
            FUNCS.Wait(2)
        endWhile

        ; it's entirely possible that the ref may no longer be a member at this
        ; point through dialogue selections. so we need to check to avoid error
        if Exists()
            ; we need to lock so that one ref at a time can do this check. we don't want
            ; every ref to get the new outfit, or we may be changing outfit on another ref.
            ; for the same reason we only check right after dialgoue, so the mod must have changed it by now.

            Outfit outfit_vanilla = ACTORS.Get_Base_Outfit(p_ref_actor)
            if outfit_vanilla && outfit_vanilla != NPCS.Default_Outfit(p_ref_actor)
                ; one drawback of this method is that there is no way to tell if the default
                ; outfit has been selected through an outfit mod. we could rig something through
                ; Set_Outfit in c++, but prob. not worth it atm
                ;NPCS.Update_Base_Outfit(p_ref_actor); so outfitter doesn't detect it has been changed (what? maybe just delete this)
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

event OnHit(ObjectReference ref_attacker, Form form_tool, Projectile ref_projectile, bool is_power, bool is_sneak, bool is_bash, bool is_blocked) native

function Restore_Health(float amount)
    p_ref_actor.RestoreActorValue(CONSTS.STR_HEALTH, amount)
endFunction

event OnCombatStateChanged(Actor ref_target, int code_combat)
    if VARS.is_updating
        return
    endIf

    if ref_target == CONSTS.ACTOR_PLAYER
        ACTORS.Pacify(p_ref_actor)
    elseIf MEMBERS.Has_Actor(ref_target)
        ACTORS.Pacify(p_ref_actor)
        ACTORS.Pacify(ref_target)
    endIf

    if Is_Follower()
        ; see OnCombatStateChanged in doticu_npcp_follower
        return
    endIf

    if code_combat == doticu_npcp_codes.COMBAT_NO()
        Enforce()
    elseIf code_combat == doticu_npcp_codes.COMBAT_YES()

    elseIf code_combat == doticu_npcp_codes.COMBAT_SEARCHING()
        
    endIf
endEvent

event OnDeath(Actor ref_killer)
    if Is_Reanimated()
        p_Deanimate()
    endIf
endEvent

; Update Methods
doticu_npcp_container p_container2_pack = none
function u_0_9_0()
    if !Exists()
        return
    endIf

    if p_container2_pack
        p_container_pack = p_container2_pack
        p_container2_pack = none
    endIf

    ; so that we can filter outfit
    if p_outfit2_current == p_outfit2_member
        p_code_outfit2 = doticu_npcp_codes.OUTFIT2_MEMBER()
    elseIf p_outfit2_current == p_outfit2_settler
        p_code_outfit2 = doticu_npcp_codes.OUTFIT2_SETTLER()
    elseIf p_outfit2_current == p_outfit2_thrall
        p_code_outfit2 = doticu_npcp_codes.OUTFIT2_THRALL()
    elseIf p_outfit2_current == p_outfit2_follower
        p_code_outfit2 = doticu_npcp_codes.OUTFIT2_FOLLOWER()
    elseIf p_outfit2_current == p_outfit2_immobile
        p_code_outfit2 = doticu_npcp_codes.OUTFIT2_IMMOBILE()
    elseIf p_outfit2_current == p_outfit2_vanilla
        p_code_outfit2 = doticu_npcp_codes.OUTFIT2_VANILLA()
    elseIf p_outfit2_current == p_outfit2_default
        p_code_outfit2 = doticu_npcp_codes.OUTFIT2_DEFAULT()
    else
        p_code_outfit2 = doticu_npcp_codes.OUTFIT2_MEMBER()
    endIf
endFunction
