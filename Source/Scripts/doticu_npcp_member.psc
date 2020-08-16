;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_member extends ReferenceAlias

; Modules
doticu_npcp_main property MAIN hidden
    doticu_npcp_main function Get()
        return doticu_npcp.Main()
    endFunction
endProperty
doticu_npcp_vars property VARS hidden
    doticu_npcp_vars function Get()
        return doticu_npcp.Vars()
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_actors property ACTORS hidden
    doticu_npcp_actors function Get()
        return doticu_npcp.Funcs().ACTORS
    endFunction
endProperty
doticu_npcp_mannequins property MANNEQUINS hidden
    doticu_npcp_mannequins function Get()
        return doticu_npcp.Funcs().MANNEQUINS
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return doticu_npcp.Funcs().CONTAINERS
    endFunction
endProperty
doticu_npcp_outfits property OUTFITS hidden
    doticu_npcp_outfits function Get()
        return doticu_npcp.Funcs().OUTFITS
    endFunction
endProperty
doticu_npcp_members property MEMBERS hidden
    doticu_npcp_members function Get()
        return doticu_npcp.Members()
    endFunction
endProperty
doticu_npcp_followers property FOLLOWERS hidden
    doticu_npcp_followers function Get()
        return doticu_npcp.Followers()
    endFunction
endProperty

; Private Variables
Actor                   p_ref_actor                         =  none
ObjectReference         p_container_pack                    =  none
ObjectReference         p_marker_mannequin                  =  none
ObjectReference         p_marker_display                    =  none
ObjectReference         p_marker_undisplay                  =  none
Outfit                  p_outfit_vanilla                    =  none
Outfit                  p_outfit_default                    =  none
doticu_npcp_outfit      p_outfit2_member                    =  none
doticu_npcp_outfit      p_outfit2_immobile                  =  none
doticu_npcp_outfit      p_outfit2_settler                   =  none
doticu_npcp_outfit      p_outfit2_thrall                    =  none
doticu_npcp_outfit      p_outfit2_follower                  =  none
doticu_npcp_outfit      p_outfit2_vanilla                   =  none
doticu_npcp_outfit      p_outfit2_default                   =  none
doticu_npcp_outfit      p_outfit2_current                   =  none
doticu_npcp_outfit      p_outfit2_auto_backup               =  none

bool                    p_is_clone                          = false
bool                    p_is_immobile                       = false
bool                    p_is_settler                        = false
bool                    p_is_thrall                         = false
bool                    p_is_paralyzed                      = false
bool                    p_is_mannequin                      = false
bool                    p_is_display                        = false
bool                    p_is_reanimated                     = false

int                     p_code_style                        =     0
int                     p_code_vitality                     =     0
int                     p_code_outfit2                      =     0
int                     p_int_rating                        =     0

string                  p_str_name                          =    ""

Faction                 p_prev_faction_crime                =  none
bool                    p_prev_faction_potential_follower   = false
bool                    p_prev_faction_no_body_cleanup      = false
float                   p_prev_aggression                   =   0.0
float                   p_prev_confidence                   =   0.0
float                   p_prev_assistance                   =   0.0
float                   p_prev_morality                     =   0.0

bool                    p_is_locked                         = false; to be deleted as soon as possible
Faction[]               p_prev_factions                     =  none; to be deleted in a future update

; Native Methods
Actor function Actor() native
int function ID() native

int function Style() native
int function Vitality() native
int function Outfit2() native
string function Name() native

bool function Is_Filled() native
bool function Is_Unfilled() native
bool function Is_Ready() native
bool function Is_Unready() native
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

function p_Member() native
function p_Unmember() native

int function Mobilize() native
int function Immobilize() native
int function Settle() native
int function Resettle() native
int function Unsettle() native
int function Enthrall() native
int function Unthrall() native
int function Paralyze() native
int function Unparalyze() native
int function Mannequinize(ObjectReference marker) native
int function Unmannequinize() native

int function Stylize(int style) native
int function Stylize_Default() native
int function Stylize_Warrior() native
int function Stylize_Mage() native
int function Stylize_Archer() native
int function Stylize_Coward() native
int function Unstylize() native

int function Vitalize(int vitality) native
int function Vitalize_Mortal() native
int function Vitalize_Protected() native
int function Vitalize_Essential() native
int function Vitalize_Invulnerable() native
int function Unvitalize() native

int function Change_Outfit2(int outfit2_code) native
int function Change_Member_Outfit2() native
int function Change_Immobile_Outfit2() native
int function Change_Settler_Outfit2() native
int function Change_Thrall_Outfit2() native
int function Change_Follower_Outfit2() native
int function Change_Vanilla_Outfit2() native
int function Change_Default_Outfit2() native
int function Change_Current_Outfit2() native
function p_Open_Outfit2() native
function p_Apply_Outfit2() native

function p_Rename(string new_name) native

function Enforce() native

function Log_Variable_Infos() native

function p_Restore_State(Actor ref_actor) native

; Friend Methods
function f_Destroy()
    if Is_Follower()
        FOLLOWERS.f_Destroy_Follower(p_ref_actor)
    endIf

    Unvitalize()
    Unstylize()
    if Is_Mannequin()
        Unmannequinize()
    endIf
    if Is_Paralyzed()
        Unparalyze()
    endIf
    if Is_Immobile()
        Mobilize()
    endIf
    if Is_Thrall()
        Unthrall()
    endIf
    if Is_Settler()
        Unsettle()
    endIf
    p_Unmember()
    if Is_Reanimated()
        p_Deanimate()
        p_Kill()
    endIf

    p_Restore_State(p_ref_actor)
    p_Destroy_Outfits()
    p_Destroy_Containers()

p_Lock()

    p_prev_morality = 0.0
    p_prev_assistance = 0.0
    p_prev_confidence = 0.0
    p_prev_aggression = 0.0
    p_prev_faction_no_body_cleanup = false
    p_prev_faction_potential_follower = false
    p_prev_faction_crime = none
    p_prev_factions = new Faction[1]

    p_outfit2_auto_backup = none
    p_outfit2_current = none
    p_outfit2_default = none
    p_outfit2_vanilla = none
    p_outfit2_follower = none
    p_outfit2_immobile = none
    p_outfit2_thrall = none
    p_outfit2_settler = none
    p_outfit2_member = none
    p_container_pack = none
    p_outfit_default = none
    p_outfit_vanilla = none
    p_marker_mannequin = none
    p_marker_undisplay = none
    p_marker_display = none
    p_int_rating = 0
    p_code_outfit2 = -1
    p_code_vitality = -1
    p_code_style = -1
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

function p_Destroy_Containers()
p_Lock()

    doticu_npcp.Object_Ref_Categorize(p_container_pack)
    CONTAINERS.Destroy_Perm(p_container_pack)

p_Unlock()
endFunction

function p_Reparalyze()
    if !Is_Paralyzed() || Is_Mannequin()
        return
    endIf

    Unparalyze()

p_Lock()

    Debug.SendAnimationEvent(p_ref_actor, "IdleForceDefaultState"); go to cached animation? FNIS?
    ;Debug.SendAnimationEvent(p_ref_actor, "IdleCiceroDance1")
    ;p_ref_actor.WaitForAnimationEvent("done")
    FUNCS.Wait(0.1)

p_Unlock()

    Paralyze()
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

function p_Resurrect()
p_Lock()

    ; don't yet know if this triggers and OnLoad
    doticu_npcp.Actor_Resurrect(p_ref_actor, false)

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

    ACTORS.Token(p_ref_actor, doticu_npcp_consts.Reanimated_Token())

    ; we could have an option for what shader is player, including none
    ; we go ahead and make sure that the shader is stopped so we don't stack them
    doticu_npcp_consts.Reanimate_Effect_Shader().Stop(p_ref_actor)
    doticu_npcp_consts.Reanimate_Effect_Shader().Play(p_ref_actor, -1.0)

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

    doticu_npcp_consts.Reanimate_Effect_Shader().Stop(p_ref_actor)

    ACTORS.Untoken(p_ref_actor, doticu_npcp_consts.Reanimated_Token())

    p_ref_actor.EvaluatePackage()

p_Unlock()
endFunction

; Public Methods
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

int function Rename(string str_name)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_Rename(str_name)
    
    return doticu_npcp_codes.SUCCESS()
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

    p_Apply_Outfit2()

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

    p_Apply_Outfit2()

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Resurrect(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    if ACTORS.Is_Alive(p_ref_actor)
        return doticu_npcp_codes.IS()
    endIf

    p_Resurrect()

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Reanimate(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    if Is_Alive()
        return doticu_npcp_codes.ALIVE()
    endIf

    p_is_reanimated = true

    ; we accept an already alive member to make it easier on creation, but maybe not once we make a dedicated Create_Reanimated()
    if Is_Dead()
        p_Resurrect()
    endIf
    p_Reanimate()

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Deanimate(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    p_is_reanimated = false

    if Is_Alive()
        p_Kill()
    endIf
    p_Deanimate()

    return doticu_npcp_codes.SUCCESS()
endFunction

; can this one actually be async?
int function Pack(int code_exec)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    CONTAINERS.Rename(p_container_pack, Name() + "'s Pack")
    CONTAINERS.Open(p_container_pack)

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Stash()
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    doticu_npcp.Object_Ref_Categorize(p_container_pack)

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

    return MEMBERS.Add_Clone(p_ref_actor)
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

    ACTORS.Move_To(p_ref_actor, doticu_npcp_consts.Player_Actor(), distance, angle)

    ;p_Remannequinize()
    ;p_Reparalyze()
    Enforce()

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Goto(int distance = 120, int angle = 0)
    if !Exists()
        return doticu_npcp_codes.MEMBER()
    endIf

    ; this is done so that we can exit expo gracefully
    MANNEQUINS.f_Try_Set_Teleport(self)

    ACTORS.Move_To(doticu_npcp_consts.Player_Actor(), p_ref_actor, distance, angle)

    ;p_Remannequinize()
    ;p_Reparalyze()
    Enforce()

    return doticu_npcp_codes.SUCCESS()
endFunction

bool function Is_In_Combat()
    return Exists() && p_ref_actor.IsInCombat()
endFunction

; Events
event OnLoad()
    if MAIN.Is_Ready() && Is_Ready()
        Enforce()
    endIf
endEvent

event OnActivate(ObjectReference activator_obj)
    if !Exists() || activator_obj != doticu_npcp_consts.Player_Actor()
        return
    endIf

    if Is_Alive()
        if !p_ref_actor.IsInDialogueWithPlayer() && p_ref_actor.IsAIEnabled()
            ACTORS.Greet_Player(p_ref_actor)
        endIf
        Enforce()
    else
        p_Open_Outfit2()
    endIf
endEvent

event On_Update_Equipment()
    p_ref_actor.AddItem(doticu_npcp_consts.Blank_Weapon(), 1, true)
    p_ref_actor.RemoveItem(doticu_npcp_consts.Blank_Weapon(), 1, true, none)
endEvent

event OnHit(ObjectReference ref_attacker, Form form_tool, Projectile ref_projectile, bool is_power, bool is_sneak, bool is_bash, bool is_blocked) native

event OnCombatStateChanged(Actor ref_target, int code_combat)
    if ref_target == doticu_npcp_consts.Player_Actor()
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
