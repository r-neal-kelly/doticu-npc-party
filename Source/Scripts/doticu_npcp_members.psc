;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_members extends Quest

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
doticu_npcp_npcs property NPCS hidden
    doticu_npcp_npcs function Get()
        return p_DATA.MODS.FUNCS.NPCS
    endFunction
endProperty
doticu_npcp_tasklists property TASKLISTS hidden
    doticu_npcp_tasklists function Get()
        return p_DATA.MODS.FUNCS.TASKLISTS
    endFunction
endProperty
doticu_npcp_logs property LOGS hidden
    doticu_npcp_logs function Get()
        return p_DATA.MODS.FUNCS.LOGS
    endFunction
endProperty
doticu_npcp_aliases property ALIASES hidden
    doticu_npcp_aliases function Get()
        return (self as Quest) as doticu_npcp_aliases
    endFunction
endProperty

; Private Constants
doticu_npcp_data        p_DATA              =  none

int property p_DISPLAY_DISTANCE
    int function Get()
        return 120
    endFunction
endProperty
int property p_DISPLAY_SPREAD
    int function Get()
        return 24
    endFunction
endProperty

; Private Variables
bool                    p_is_created        = false
bool                    p_are_displayed     = false
int                     p_idx_display       =    -1
ObjectReference         p_marker_display    =  none
doticu_npcp_tasklist    p_tasklist          =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_are_displayed = false
    p_idx_display = -1
    p_marker_display = CONSTS.MARKER_STORAGE.PlaceAtMe(CONSTS.STATIC_MARKER_X)
    p_tasklist = TASKLISTS.Create()

    ALIASES.f_Create(DATA)
endFunction

function f_Destroy()
    ALIASES.f_Destroy()

    TASKLISTS.Destroy(p_tasklist)
    p_marker_display = none
    p_idx_display = -1
    p_are_displayed = false
    p_is_created = false
endFunction

function f_Register()
    ALIASES.f_Register()

    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_aliases = 0
    int num_aliases = arr_aliases.length
    while idx_aliases < num_aliases
        (arr_aliases[idx_aliases] as doticu_npcp_member).f_Register()
        idx_aliases += 1
    endWhile
endFunction

; Private Methods
int function p_Get_Alias_ID(Actor ref_actor)
    if !ref_actor
        return -1
    else
        return ref_actor.GetItemCount(CONSTS.TOKEN_MEMBER) - 1
    endIf
endFunction

doticu_npcp_member function p_Get_Member(int id_alias)
    return ALIASES.f_Get_Alias(id_alias) as doticu_npcp_member
endFunction

bool function p_Send_Members(string str_event)
    int handle = ModEvent.Create(str_event)

    if !handle
        return false
    endIf

    ModEvent.PushForm(handle, p_DATA as Form)

    if !ModEvent.Send(handle)
        ModEvent.Release(handle)
        return false
    endIf

    return true
endFunction

; Public Methods
int function Create_Member(Actor ref_actor, bool do_clone = false)
    int code_return
    bool was_dead = false

    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf

    if ref_actor.IsChild()
        return CODES.IS_CHILD
    endIf

    if Get_Count() >= Get_Max()
        ; check first so we don't have to unclone
        return CODES.HASNT_SPACE_MEMBER
    endIf

    if Should_Clone_Actor(ref_actor)
        do_clone = true
    endIf

    if do_clone
        if ACTORS.Is_Unique(ref_actor)
            LOGS.Create_Note("Adding clone to members...", false)
        else
            LOGS.Create_Note("Adding clone to members, please wait...", false)
        endIf

        ref_actor = NPCS.Clone(ref_actor)
        if !ref_actor
            return CODES.CANT_CLONE
        endIf
    else
        LOGS.Create_Note("Adding to members...", false)

        if ACTORS.Is_Dead(ref_actor)
            was_dead = true
            ACTORS.Resurrect(ref_actor)
            if ACTORS.Is_Dead(ref_actor)
                return CODES.CANT_RESURRECT
            endIf
        endIf
        NPCS.Register(ref_actor)
    endIf

    code_return = ALIASES.Create_Alias(ref_actor)
    if code_return < 0
        if do_clone
            ACTORS.Delete(ref_actor)
        elseIf was_dead
            ACTORS.Kill(ref_actor)
        endIf

        if code_return == CODES.HAS_ACTOR || code_return == CODES.HAS_ALIAS
            return CODES.HAS_MEMBER
        elseIf code_return == CODES.HASNT_SPACE
            return CODES.HASNT_SPACE_MEMBER
        else
            return code_return
        endIf
    endIf
    int id_alias = code_return

    doticu_npcp_member ref_member = p_Get_Member(id_alias)
    ref_member.f_Create(p_DATA, id_alias, do_clone)
    ref_member.f_Register()

    return CODES.SUCCESS
endFunction

int function Destroy_Member(Actor ref_actor, bool delete_clone = false)
    int code_return

    if !ref_actor
        return CODES.ISNT_ACTOR
    endIf
    
    int id_alias = p_Get_Alias_ID(ref_actor)
    if !ALIASES.Has_Alias(id_alias, ref_actor)
        return CODES.HASNT_MEMBER
    endIf

    doticu_npcp_member ref_member = p_Get_Member(id_alias)
    bool is_clone = ref_member.Is_Clone()

    ref_member.f_Unregister()
    ref_member.f_Destroy()

    code_return = ALIASES.Destroy_Alias(id_alias, ref_actor)
    if code_return < 0
        return code_return
    endIf

    if Should_Unclone_Actor(ref_actor)
        delete_clone = true
    endIf

    ; this must be done after alias destruction/unmember
    if is_clone && delete_clone
        ; also unregsiters
        NPCS.Unclone(ref_actor)
    else
        ; even though we don't remove clones from the
        ; system we still need to unregister them
        NPCS.Unregister(ref_actor)
    endIf

    return CODES.SUCCESS
endFunction

int function Get_Count()
    return ALIASES.Get_Count()
endFunction

int function Get_Max()
    return VARS.max_members
endFunction

int function Get_Real_Max()
    return ALIASES.Get_Max()
endFunction

bool function Will_Sort()
    return ALIASES.Will_Sort()
endFunction

bool function Has_Member(Actor ref_actor)
    return ALIASES.Has_Alias(p_Get_Alias_ID(ref_actor), ref_actor)
endFunction

bool function Has_Base(Actor ref_actor)
    Form[] arr_origs = NPCS.Get_Originals(ref_actor)
    if !(arr_origs.length == 1 && arr_origs[0] == none)
        int idx_origs = arr_origs.length
        while idx_origs > 0
            idx_origs -= 1
            if Has_Member(arr_origs[idx_origs] as Actor)
                return true
            endIf
        endWhile
    endIf

    Form[] arr_clones = NPCS.Get_Clones(ref_actor)
    if !(arr_clones.length == 1 && arr_clones[0] == none)
        int idx_clones = arr_clones.length
        while idx_clones > 0
            idx_clones -= 1
            if Has_Member(arr_clones[idx_clones] as Actor)
                return true
            endIf
        endWhile
    endIf

    return false
endFunction

int function Get_Base_Count(Actor ref_actor)
    int num_members = 0

    Form[] arr_origs = NPCS.Get_Originals(ref_actor)
    if !(arr_origs.length == 1 && arr_origs[0] == none)
        int idx_origs = arr_origs.length
        Form form_orig
        while idx_origs > 0
            idx_origs -= 1
            form_orig = arr_origs[idx_origs]
            if Has_Member(form_orig as Actor)
                num_members += 1
            endIf
        endWhile
    endIf

    Form[] arr_clones = NPCS.Get_Clones(ref_actor)
    if !(arr_clones.length == 1 && arr_clones[0] == none)
        int idx_clones = arr_clones.length
        Form form_clone
        while idx_clones > 0
            idx_clones -= 1
            form_clone = arr_clones[idx_clones]
            if Has_Member(form_clone as Actor)
                ; we don't want to count the same member twice
                if arr_origs.Find(form_clone) < 0
                    num_members += 1
                endIf
            endIf
        endWhile
    endIf

    return num_members
endFunction

bool function Are_Displayed()
    return p_are_displayed
endFunction

doticu_npcp_member function Get_Member(Actor ref_actor)
    return ALIASES.Get_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_member
endFunction

doticu_npcp_member function Get_Next_Member(doticu_npcp_member ref_member)
    Actor ref_actor = ref_member.Get_Actor()
    return ALIASES.Get_Next_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_member
endFunction

doticu_npcp_member function Get_Prev_Member(doticu_npcp_member ref_member)
    Actor ref_actor = ref_member.Get_Actor()
    return ALIASES.Get_Prev_Alias(p_Get_Alias_ID(ref_actor), ref_actor) as doticu_npcp_member
endFunction

Alias[] function Get_Members(int idx_from = 0, int idx_to_ex = -1)
    return ALIASES.Get_Aliases(idx_from, idx_to_ex)
endFunction

int function Update_Name(Actor ref_actor)
    int id_alias = p_Get_Alias_ID(ref_actor)
    return ALIASES.Update_Name(id_alias)
endFunction

function Sort()
    ALIASES.Sort()
endFunction

function Enforce()
    doticu_npcp_member ref_member
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_arr = 0
    while idx_arr < arr_aliases.length
        ref_member = arr_aliases[idx_arr] as doticu_npcp_member
        ref_member.Enforce()
        idx_arr += 1
    endWhile
endFunction

function Unmember()
    while !p_Send_Members("doticu_npcp_members_unmember")
        Utility.Wait(0.25)
    endWhile
endFunction

bool function Should_Clone_Actor(Actor ref_actor)
    if !ref_actor
        return false
    elseIf VARS.force_clone_unique && ACTORS.Is_Unique(ref_actor)
        return true
    elseIf VARS.force_clone_generic && ACTORS.Is_Generic(ref_actor)
        return true
    else
        return false
    endIf
endFunction

bool function Should_Unclone_Actor(Actor ref_actor)
    if !ref_actor
        return false
    elseIf VARS.force_unclone_unique && ACTORS.Is_Unique(ref_actor)
        return true
    elseIf VARS.force_unclone_generic && ACTORS.Is_Generic(ref_actor)
        return true
    else
        return false
    endIf
endFunction

bool function Should_Unclone_Member(doticu_npcp_member ref_member)
    return ref_member && ref_member.Is_Clone() && Should_Unclone_Actor(ref_member.Get_Actor())
endFunction

; would also like a display that skips followers, has only followers, etc. for immobile, settler, etc.
; this is getting into filter territory with aliases. need to work that out
int function Display_Start(Actor ref_actor)
    if Are_Displayed()
        return CODES.IS_DISPLAY
    endIf

    if Get_Count() < 1
        return CODES.HASNT_MEMBER
    endIf

    int idx_alias = ALIASES.f_ID_To_Idx(p_Get_Alias_ID(ref_actor))
    if idx_alias < 0
        idx_alias = 0
    endIf

    p_are_displayed = true
    p_idx_display = idx_alias
    ALIASES.Disable_Sort()

    p_marker_display.MoveTo(CONSTS.ACTOR_PLAYER)

    ; to make sure there is no ambiguity with idxs, we go ahead and render Next
    Display_Next()

    return CODES.SUCCESS
endFunction

int function Display_Stop()
    if !Are_Displayed()
        return CODES.ISNT_DISPLAY
    endIf

    Alias[] arr_prev = ALIASES.Get_Prev_Aliases(p_idx_display, CONSTS.MAX_DISPLAY)
    Alias[] arr_next = ALIASES.Get_Next_Aliases(p_idx_display, CONSTS.MAX_DISPLAY)

    p_Undisplay_Aliases(arr_prev)
    p_Undisplay_Aliases(arr_next)

    p_marker_display.MoveTo(CONSTS.MARKER_STORAGE)

    ALIASES.Enable_Sort()
    p_idx_display = -1
    p_are_displayed = false

    return CODES.SUCCESS
endFunction

int function Display_Next()
    if !Are_Displayed()
        return CODES.ISNT_DISPLAY
    endIf

    Alias[] arr_prev = ALIASES.Get_Prev_Aliases(p_idx_display, CONSTS.MAX_DISPLAY)
    Alias[] arr_next = ALIASES.Get_Next_Aliases(p_idx_display, VARS.num_display)
    
    p_Undisplay_Aliases(arr_prev)
    p_Display_Aliases(arr_next, p_DISPLAY_DISTANCE, p_DISPLAY_SPREAD)

    p_idx_display = ALIASES.f_To_Relative_Idx(p_idx_display + VARS.num_display)

    return CODES.SUCCESS
endFunction

int function Display_Previous()
    if !Are_Displayed()
        return CODES.ISNT_DISPLAY
    endIf

    p_idx_display = ALIASES.f_To_Relative_Idx(p_idx_display - VARS.num_display)

    Alias[] arr_prev = ALIASES.Get_Prev_Aliases(p_idx_display, VARS.num_display)
    Alias[] arr_next = ALIASES.Get_Next_Aliases(p_idx_display, CONSTS.MAX_DISPLAY)
    
    p_Undisplay_Aliases(arr_next)
    p_Display_Aliases(arr_prev, p_DISPLAY_DISTANCE, p_DISPLAY_SPREAD)

    return CODES.SUCCESS
endFunction

function p_Display_Aliases(Alias[] arr_aliases, int distance, int angle_offset)
    int idx_aliases = 0
    int num_aliases = arr_aliases.length
    int median = Math.Ceiling(num_aliases / 2)
    int angle = angle_offset * median

    if num_aliases % 2 == 0
        while idx_aliases < num_aliases
            (arr_aliases[idx_aliases] as doticu_npcp_member).Display(p_marker_display, distance, angle)
            idx_aliases += 1
            if idx_aliases == median
                angle -= angle_offset * 2
            else
                angle -= angle_offset
            endIf
        endWhile
    else
        while idx_aliases < num_aliases
            (arr_aliases[idx_aliases] as doticu_npcp_member).Display(p_marker_display, distance, angle)
            idx_aliases += 1
            angle -= angle_offset
        endWhile
    endIf
endFunction

function p_Undisplay_Aliases(Alias[] arr_aliases)
    int idx_aliases = 0
    int num_aliases = arr_aliases.length

    while idx_aliases < num_aliases
        (arr_aliases[idx_aliases] as doticu_npcp_member).Undisplay()
        idx_aliases += 1
    endWhile
endFunction

; Update Methods
function u_0_8_3()
    Alias[] arr_aliases = ALIASES.Get_Aliases()
    int idx_aliases = 0
    int num_aliases = arr_aliases.length
    while idx_aliases < num_aliases
        (arr_aliases[idx_aliases] as doticu_npcp_member).u_0_8_3()
        idx_aliases += 1
    endWhile
endFunction
