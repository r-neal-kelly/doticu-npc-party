;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_keys extends Quest

; Modules
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
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return p_DATA.MODS.CONTROL.COMMANDS
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
endFunction

function f_Destroy()
    p_is_created = false
endFunction

function f_Register()
    Update_Keys()
endFunction

; Public Methods
function Update_Keys()
    UnregisterForAllKeys()

    ; temp
    RegisterForKey(22); U

    ; Followers
    if VARS.key_fs_summon_all > -1
        RegisterForKey(VARS.key_fs_summon_all)
    endIf
    if VARS.key_fs_summon_mobile > -1
        RegisterForKey(VARS.key_fs_summon_mobile)
    endIf
    if VARS.key_fs_summon_immobile > -1
        RegisterForKey(VARS.key_fs_summon_immobile)
    endIf
    if VARS.key_fs_settle > -1
        RegisterForKey(VARS.key_fs_settle)
    endIf
    if VARS.key_fs_unsettle > -1
        RegisterForKey(VARS.key_fs_unsettle)
    endIf
    if VARS.key_fs_immobilize > -1
        RegisterForKey(VARS.key_fs_immobilize)
    endIf
    if VARS.key_fs_mobilize > -1
        RegisterForKey(VARS.key_fs_mobilize)
    endIf
    if VARS.key_fs_sneak > -1
        RegisterForKey(VARS.key_fs_sneak)
    endIf
    if VARS.key_fs_unsneak > -1
        RegisterForKey(VARS.key_fs_unsneak)
    endIf
    if VARS.key_fs_resurrect > -1
        RegisterForKey(VARS.key_fs_resurrect)
    endIf
    if VARS.key_fs_unfollow > -1
        RegisterForKey(VARS.key_fs_unfollow)
    endIf
    if VARS.key_fs_unmember > -1
        RegisterForKey(VARS.key_fs_unmember)
    endIf

    ; Members Display
    if VARS.key_ms_display_toggle > -1
        RegisterForKey(VARS.key_ms_display_toggle)
    endIf
    if VARS.key_ms_display_next > -1
        RegisterForKey(VARS.key_ms_display_next)
    endIf
    if VARS.key_ms_display_previous > -1
        RegisterForKey(VARS.key_ms_display_previous)
    endIf

    ; Actors Move
    if VARS.key_move_toggle
        RegisterForKey(VARS.key_move_toggle)
    endIf
    ACTORS.MOVEE.Update_Keys()

    ; Member/Follower
    if VARS.key_resurrect > -1
        RegisterForKey(VARS.key_resurrect)
    endIf
    if VARS.key_pack > -1
        RegisterForKey(VARS.key_pack)
    endIf
    if VARS.key_outfit > -1
        RegisterForKey(VARS.key_outfit)
    endIf

    ; Member/Follower Toggles
    if VARS.key_m_toggle_member > -1
        RegisterForKey(VARS.key_m_toggle_member)
    endIf
    if VARS.key_m_toggle_clone > -1
        RegisterForKey(VARS.key_m_toggle_clone)
    endIf
    if VARS.key_m_toggle_settler > -1
        RegisterForKey(VARS.key_m_toggle_settler)
    endIf
    if VARS.key_m_toggle_thrall > -1
        RegisterForKey(VARS.key_m_toggle_thrall)
    endIf
    if VARS.key_m_toggle_immobile > -1
        RegisterForKey(VARS.key_m_toggle_immobile)
    endIf
    if VARS.key_m_toggle_paralyzed > -1
        RegisterForKey(VARS.key_m_toggle_paralyzed)
    endIf
    if VARS.key_m_toggle_follower > -1
        RegisterForKey(VARS.key_m_toggle_follower)
    endIf
    if VARS.key_m_toggle_sneak > -1
        RegisterForKey(VARS.key_m_toggle_sneak)
    endIf

    ; Member/Follower Cycles
    if VARS.key_cycle_style > -1
        RegisterForKey(VARS.key_cycle_style)
    endIf
    if VARS.key_cycle_vitality > -1
        RegisterForKey(VARS.key_cycle_vitality)
    endIf
    if VARS.key_cycle_outfit > -1
        RegisterForKey(VARS.key_cycle_outfit)
    endIf
endFunction

string function Get_Control(int code_key)
    if false

    ; Followers
    elseIf code_key == VARS.key_fs_summon_all
        return CONSTS.STR_KEY_FS_SUMMON_ALL
    elseIf code_key == VARS.key_fs_summon_mobile
        return CONSTS.STR_KEY_FS_SUMMON_MOBILE
    elseIf code_key == VARS.key_fs_summon_immobile
        return CONSTS.STR_KEY_FS_SUMMON_IMMOBILE
    elseIf code_key == VARS.key_fs_settle
        return CONSTS.STR_KEY_FS_SETTLE
    elseIf code_key == VARS.key_fs_unsettle
        return CONSTS.STR_KEY_FS_UNSETTLE
    elseIf code_key == VARS.key_fs_immobilize
        return CONSTS.STR_KEY_FS_IMMOBILIZE
    elseIf code_key == VARS.key_fs_mobilize
        return CONSTS.STR_KEY_FS_MOBILIZE
    elseIf code_key == VARS.key_fs_sneak
        return CONSTS.STR_KEY_FS_SNEAK
    elseIf code_key == VARS.key_fs_unsneak
        return CONSTS.STR_KEY_FS_UNSNEAK
    elseIf code_key == VARS.key_fs_resurrect
        return CONSTS.STR_KEY_FS_RESURRECT

    ; Members Display
    elseIf code_key == VARS.key_ms_display_toggle
        return CONSTS.STR_KEY_MS_DISPLAY_TOGGLE
    elseIf code_key == VARS.key_ms_display_next
        return CONSTS.STR_KEY_MS_DISPLAY_NEXT
    elseIf code_key == VARS.key_ms_display_previous
        return CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS

    ; Actors Move
    elseIf code_key == VARS.key_move_toggle
        return CONSTS.STR_KEY_MOVE_TOGGLE
    elseIf code_key == VARS.key_move_farther
        return CONSTS.STR_KEY_MOVE_FARTHER
    elseIf code_key == VARS.key_move_nearer
        return CONSTS.STR_KEY_MOVE_NEARER
    elseIf code_key == VARS.key_move_rotate_right
        return CONSTS.STR_KEY_MOVE_ROTATE_RIGHT
    elseIf code_key == VARS.key_move_rotate_left
        return CONSTS.STR_KEY_MOVE_ROTATE_LEFT

    ; Member/Follower Toggles
    elseIf code_key == VARS.key_m_toggle_member
        return CONSTS.STR_KEY_M_TOGGLE_MEMBER
    elseIf code_key == VARS.key_m_toggle_clone
        return CONSTS.STR_KEY_M_TOGGLE_CLONE
    elseIf code_key == VARS.key_m_toggle_settler
        return CONSTS.STR_KEY_M_TOGGLE_SETTLER
    elseIf code_key == VARS.key_m_toggle_thrall
        return CONSTS.STR_KEY_M_TOGGLE_THRALL
    elseIf code_key == VARS.key_m_toggle_immobile
        return CONSTS.STR_KEY_M_TOGGLE_IMMOBILE
    elseIf code_key == VARS.key_m_toggle_paralyzed
        return CONSTS.STR_KEY_M_TOGGLE_PARALYZED
    elseIf code_key == VARS.key_m_toggle_follower
        return CONSTS.STR_KEY_M_TOGGLE_FOLLOWER
    elseIf code_key == VARS.key_m_toggle_sneak
        return CONSTS.STR_KEY_M_TOGGLE_SNEAK
    
    else
        return ""

    endIf
endFunction

int function Get_Key(string str_control)
    if false

    ; Followers
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_ALL
        return VARS.key_fs_summon_all
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_MOBILE
        return VARS.key_fs_summon_mobile
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_IMMOBILE
        return VARS.key_fs_summon_immobile
    elseIf str_control == CONSTS.STR_KEY_FS_SETTLE
        return VARS.key_fs_settle
    elseIf str_control == CONSTS.STR_KEY_FS_UNSETTLE
        return VARS.key_fs_unsettle
    elseIf str_control == CONSTS.STR_KEY_FS_IMMOBILIZE
        return VARS.key_fs_immobilize
    elseIf str_control == CONSTS.STR_KEY_FS_MOBILIZE
        return VARS.key_fs_mobilize
    elseIf str_control == CONSTS.STR_KEY_FS_SNEAK
        return VARS.key_fs_sneak
    elseIf str_control == CONSTS.STR_KEY_FS_UNSNEAK
        return VARS.key_fs_unsneak
    elseIf str_control == CONSTS.STR_KEY_FS_RESURRECT
        return VARS.key_fs_resurrect

    ; Members Display
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_TOGGLE
        return VARS.key_ms_display_toggle
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_NEXT
        return VARS.key_ms_display_next
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS
        return VARS.key_ms_display_previous

    ; Actors Move
    elseIf str_control == CONSTS.STR_KEY_MOVE_TOGGLE
        return VARS.key_move_toggle
    elseIf str_control == CONSTS.STR_KEY_MOVE_FARTHER
        return VARS.key_move_farther
    elseIf str_control == CONSTS.STR_KEY_MOVE_NEARER
        return VARS.key_move_nearer
    elseIf str_control == CONSTS.STR_KEY_MOVE_ROTATE_RIGHT
        return VARS.key_move_rotate_right
    elseIf str_control == CONSTS.STR_KEY_MOVE_ROTATE_LEFT
        return VARS.key_move_rotate_left

    ; Member/Follower Toggles
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_MEMBER
        return VARS.key_m_toggle_member
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_CLONE
        return VARS.key_m_toggle_clone
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_SETTLER
        return VARS.key_m_toggle_settler
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_THRALL
        return VARS.key_m_toggle_thrall
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_IMMOBILE
        return VARS.key_m_toggle_immobile
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_PARALYZED
        return VARS.key_m_toggle_paralyzed
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_FOLLOWER
        return VARS.key_m_toggle_follower
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_SNEAK
        return VARS.key_m_toggle_sneak
        
    else
        return -1
    
    endIf
endFunction

int function Get_Key_Default(string str_control)
    if false

    ; Followers
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_ALL
        return CONSTS.KEY_DEF_FS_SUMMON_ALL
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_MOBILE
        return CONSTS.KEY_DEF_FS_SUMMON_MOBILE
    elseIf str_control == CONSTS.STR_KEY_FS_SUMMON_IMMOBILE
        return CONSTS.KEY_DEF_FS_SUMMON_IMMOBILE
    elseIf str_control == CONSTS.STR_KEY_FS_SETTLE
        return CONSTS.KEY_DEF_FS_SETTLE
    elseIf str_control == CONSTS.STR_KEY_FS_UNSETTLE
        return CONSTS.KEY_DEF_FS_UNSETTLE
    elseIf str_control == CONSTS.STR_KEY_FS_IMMOBILIZE
        return CONSTS.KEY_DEF_FS_IMMOBILIZE
    elseIf str_control == CONSTS.STR_KEY_FS_MOBILIZE
        return CONSTS.KEY_DEF_FS_MOBILIZE
    elseIf str_control == CONSTS.STR_KEY_FS_SNEAK
        return CONSTS.KEY_DEF_FS_SNEAK
    elseIf str_control == CONSTS.STR_KEY_FS_UNSNEAK
        return CONSTS.KEY_DEF_FS_UNSNEAK
    elseIf str_control == CONSTS.STR_KEY_FS_RESURRECT
        return CONSTS.KEY_DEF_FS_RESURRECT
    
    ; Members Display
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_TOGGLE
        return CONSTS.KEY_DEF_MS_DISPLAY_TOGGLE
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_PREVIOUS
        return CONSTS.KEY_DEF_MS_DISPLAY_PREVIOUS
    elseIf str_control == CONSTS.STR_KEY_MS_DISPLAY_NEXT
        return CONSTS.KEY_DEF_MS_DISPLAY_NEXT
    
    ; Actors Move
    elseIf str_control == CONSTS.STR_KEY_MOVE_TOGGLE
        return CONSTS.KEY_DEF_MOVE_TOGGLE
    elseIf str_control == CONSTS.STR_KEY_MOVE_FARTHER
        return CONSTS.KEY_DEF_MOVE_FARTHER
    elseIf str_control == CONSTS.STR_KEY_MOVE_NEARER
        return CONSTS.KEY_DEF_MOVE_NEARER
    elseIf str_control == CONSTS.STR_KEY_MOVE_ROTATE_RIGHT
        return CONSTS.KEY_DEF_MOVE_ROTATE_RIGHT
    elseIf str_control == CONSTS.STR_KEY_MOVE_ROTATE_LEFT
        return CONSTS.KEY_DEF_MOVE_ROTATE_LEFT
    
    ; Member/Follower Toggles
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_MEMBER
        return CONSTS.KEY_DEF_M_TOGGLE_MEMBER
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_CLONE
        return CONSTS.KEY_DEF_M_TOGGLE_CLONE
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_SETTLER
        return CONSTS.KEY_DEF_M_TOGGLE_SETTLER
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_THRALL
        return CONSTS.KEY_DEF_M_TOGGLE_THRALL
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_IMMOBILE
        return CONSTS.KEY_DEF_M_TOGGLE_IMMOBILE
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_PARALYZED
        return CONSTS.KEY_DEF_M_TOGGLE_PARALYZED
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_FOLLOWER
        return CONSTS.KEY_DEF_M_TOGGLE_FOLLOWER
    elseIf str_control == CONSTS.STR_KEY_M_TOGGLE_SNEAK
        return CONSTS.KEY_DEF_M_TOGGLE_SNEAK
            
    else
        return -1
        
    endIf
endFunction

; Events
event OnKeyDown(int code_key)
    if !FUNCS.Can_Use_Keys()
        return
    endIf
    
    Actor ref_actor = Game.GetCurrentCrosshairRef() as Actor

    ; temp
    if code_key == 22; U
        ;Outfit outfit_current = ref_actor.GetLeveledActorBase().GetOutfit()
        ref_actor.SetOutfit(CONSTS.OUTFIT_TEMP)
        ref_actor.SetOutfit(p_DATA.MODS.FUNCS.NPCS.Get_Default_Outfit(ref_actor))
        ;ref_actor.GetLeveledActorBase().SetOutfit(CONSTS.OUTFIT_TEMP)
        Debug.Notification("switching to default outfit.")
    endIf

    ; can add a 'Yell' command to topics, so that all funcs can be used in dialogue, e.g. "Summon All"

    if false

    ; Followers
    elseIf code_key == VARS.key_fs_summon_all
        COMMANDS.Followers_Summon_All()
    elseIf code_key == VARS.key_fs_summon_mobile
        COMMANDS.Followers_Summon_Mobile()
    elseIf code_key == VARS.key_fs_summon_immobile
        COMMANDS.Followers_Summon_Immobile()
    elseIf code_key == VARS.key_fs_settle
        COMMANDS.Followers_Settle()
    elseIf code_key == VARS.key_fs_unsettle
        COMMANDS.Followers_Unsettle()
    elseIf code_key == VARS.key_fs_immobilize
        COMMANDS.Followers_Immobilize()
    elseIf code_key == VARS.key_fs_mobilize
        COMMANDS.Followers_Mobilize()
    elseIf code_key == VARS.key_fs_sneak
        COMMANDS.Followers_Sneak()
    elseIf code_key == VARS.key_fs_unsneak
        COMMANDS.Followers_Unsneak()
    elseIf code_key == VARS.key_fs_resurrect
        COMMANDS.Followers_Resurrect()

    ; Members Display
    elseIf code_key == VARS.key_ms_display_toggle
        COMMANDS.Toggle_Members_Display(ref_actor)
    elseIf code_key == VARS.key_ms_display_next
        COMMANDS.Members_Display_Next()
    elseIf code_key == VARS.key_ms_display_previous
        COMMANDS.Members_Display_Previous()

    ; Actors Move
    elseIf code_key == VARS.key_move_toggle
        COMMANDS.Move_Sync(ref_actor)
    
    ; Member/Follower Toggles
    elseIf code_key == VARS.key_m_toggle_member
        COMMANDS.Toggle_Member_Sync(ref_actor)
    elseIf code_key == VARS.key_m_toggle_clone
        COMMANDS.Toggle_Clone_Sync(ref_actor)
    elseIf code_key == VARS.key_m_toggle_settler
        COMMANDS.Toggle_Settler_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_thrall
        COMMANDS.Toggle_Thrall_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_immobile
        COMMANDS.Toggle_Immobile_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_paralyzed
        COMMANDS.Toggle_Paralyzed_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_follower
        COMMANDS.Toggle_Follower_Async(ref_actor)
    elseIf code_key == VARS.key_m_toggle_sneak
        COMMANDS.Toggle_Sneak_Async(ref_actor)

    ; Member/Follower
    elseIf code_key == VARS.key_resurrect
        COMMANDS.Resurrect_Async(ref_actor, true)
    elseIf code_key == VARS.key_pack
        COMMANDS.Pack_Sync(ref_actor, true)
    elseIf code_key == VARS.key_outfit
        COMMANDS.Outfit_Current_Sync(ref_actor, true)
    
    ; Member/Follower Cycles
    elseIf code_key == VARS.key_cycle_style
        COMMANDS.Cycle_Style(ref_actor, false)
    endIf
endEvent
