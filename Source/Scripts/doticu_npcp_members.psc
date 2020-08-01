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
doticu_npcp_outfits property OUTFITS hidden
    doticu_npcp_outfits function Get()
        return p_DATA.MODS.FUNCS.OUTFITS
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

; Private Constants
doticu_npcp_data        p_DATA              =  none

; Private Variables
bool                    p_is_created        = false
bool                    p_has_display       = false
int                     p_idx_display       =     0
ObjectReference         p_marker_display    =  none

; Native Methods
Alias function p_From_ID(int unique_id)         native
Alias function p_From_Actor(Actor ref_actor)    native
Alias function p_From_Unfilled()                native

bool function Has_Space()                   native
bool function Hasnt_Space()                 native
bool function Has_Actor(Actor ref_actor)    native
bool function Hasnt_Actor(Actor ref_actor)  native
bool function Has_Base(Actor ref_actor)     native
bool function Hasnt_Base(Actor ref_actor)   native
bool function Has_Head(Actor ref_actor)     native
bool function Hasnt_Head(Actor ref_actor)   native
bool function Has_Display()                 native
bool function Hasnt_Display()               native

int function Max()                          native
int function Count_Filled()                 native
int function Count_Unfilled()               native
int function Count_Loaded()                 native
int function Count_Unloaded()               native
int function Count_Unique()                 native
int function Count_Generic()                native
int function Count_Alive()                  native
int function Count_Dead()                   native
int function Count_Originals()              native
int function Count_Clones()                 native
int function Count_Mobile()                 native
int function Count_Immobile()               native
int function Count_Settlers()               native
int function Count_Non_Settlers()           native
int function Count_Thralls()                native
int function Count_Non_Thralls()            native
int function Count_Paralyzed()              native
int function Count_Non_Paralyzed()          native
int function Count_Mannequins()             native
int function Count_Non_Mannequins()         native
int function Count_Reanimated()             native
int function Count_Non_Reanimated()         native
int function Count_Followers()              native
int function Count_Non_Followers()          native
int function Count_Sneaks()                 native
int function Count_Non_Sneaks()             native
int function Count_Saddlers()               native
int function Count_Non_Saddlers()           native
int function Count_Retreaters()             native
int function Count_Non_Retreaters()         native
int function Count_Base(Actor ref_actor)    native
int function Count_Heads(Actor ref_actor)   native

Alias[] function All()      native
Alias[] function Filled()   native

Alias[] function Sort_Filled(int begin, int end) native

Alias[] function Slice(Alias[] members, int begin, int end) native

string[] function Race_Names() native

function Enforce_Loaded() native

string[]    function Filter_Strings(string sex = "", string race = "", string search = "")          native
int[]       function Filter_Ints(int style = 0, int vitality = 0, int outfit2 = 0, int rating = -1) native
int         function Add_Filter_Flag_1(int flags_1, string flag_1)                                  native
int         function Add_Filter_Flag_2(int flags_2, string flag_2)                                  native
Alias[]     function Filter(string[] strings, int[] ints, int flags_1, int flags_2)                 native

int function Display_Start()    native
int function Display_Stop()     native
int function Display_Next()     native
int function Display_Previous() native

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true
    p_has_display = false
    p_idx_display = -1
    p_marker_display = CONSTS.MARKER_STORAGE.PlaceAtMe(CONSTS.STATIC_MARKER_X)
endFunction

function f_Destroy()
    p_marker_display = none
    p_idx_display = -1
    p_has_display = false
    p_is_created = false
endFunction

function f_Register()
    ; just in case, see ALIASES.f_Register()
    int filled_count = Count_Filled()
    if VARS.max_members < filled_count
        VARS.max_members = filled_count
    endIf

    RegisterForModEvent("doticu_npcp_load_mod", "On_Load_Mod")
endFunction

; Public Methods
; these should be renamed to Add_Original, Remove_Original, Add_Clone, Remove_Clone
int function Create_Member(Actor ref_actor)
    if !ref_actor
        return doticu_npcp_codes.ACTOR()
    endIf

    if ref_actor.IsChild()
        return doticu_npcp_codes.CHILD()
    endIf

    if Count_Filled() >= Get_Limit()
        return doticu_npcp_codes.MEMBERS()
    endIf

    if Should_Clone_Actor(ref_actor)
        return Clone(ref_actor)
    endIf

    if Has_Actor(ref_actor)
        return doticu_npcp_codes.MEMBER()
    endIf

    LOGS.Create_Note("Adding to members...", false)

    if ACTORS.Is_Dead(ref_actor)
        ACTORS.Resurrect(ref_actor)
        if ACTORS.Is_Dead(ref_actor)
            return doticu_npcp_codes.DEAD()
        endIf
    endIf

    NPCS.Add_Original(ref_actor)

    doticu_npcp_member ref_member = p_From_Unfilled() as doticu_npcp_member
    if !ref_member
        return doticu_npcp_codes.FAILURE()
    endIf

    ref_member.f_Create(p_DATA, ref_actor, false)

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Destroy_Member(Actor ref_actor)
    if !ref_actor
        return doticu_npcp_codes.ACTOR()
    endIf

    doticu_npcp_member ref_member = p_From_Actor(ref_actor) as doticu_npcp_member
    if !ref_member
        return doticu_npcp_codes.MEMBER()
    endIf

    if ref_member.Is_Clone()
        return Unclone(ref_actor, false)
    endIf

    ref_member.f_Destroy()

    NPCS.Remove_Original(ref_actor)

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Clone(Actor ref_actor)
    if !ref_actor
        return doticu_npcp_codes.ACTOR()
    endIf

    if ref_actor.IsChild()
        return doticu_npcp_codes.CHILD()
    endIf

    if Count_Filled() >= Get_Limit()
        return doticu_npcp_codes.MEMBERS()
    endIf

    LOGS.Create_Note("Adding clone to members...", false)

    Actor ref_clone = NPCS.Add_Clone(ref_actor)
    if !ref_clone
        return doticu_npcp_codes.CLONE()
    endIf
    OUTFITS.Outfit_Clone(ref_clone, ref_actor)

    doticu_npcp_member ref_member = p_From_Unfilled() as doticu_npcp_member
    if !ref_member
        ACTORS.Delete(ref_clone)
        return doticu_npcp_codes.FAILURE()
    endIf

    ref_member.f_Create(p_DATA, ref_clone, true)

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Unclone(Actor ref_actor, bool delete_clone)
    if !ref_actor
        return doticu_npcp_codes.ACTOR()
    endIf

    doticu_npcp_member ref_member = p_From_Actor(ref_actor) as doticu_npcp_member
    if !ref_member
        return doticu_npcp_codes.MEMBER()
    endIf

    if !ref_member.Is_Clone()
        return doticu_npcp_codes.CLONE()
    endIf

    ref_member.f_Destroy()

    if delete_clone || Should_Unclone_Actor(ref_actor)
        NPCS.Remove_Clone(ref_actor)
    endIf

    return doticu_npcp_codes.SUCCESS()
endFunction

int function Get_Count()
    return Count_Filled()
endFunction

int function Get_Limit()
    return VARS.max_members
endFunction

int function Get_Max()
    return Max()
endFunction

bool function Has_Member(Actor ref_actor)
    return Has_Actor(ref_actor)
endFunction

doticu_npcp_member function Get_Member(Actor ref_actor)
    return p_From_Actor(ref_actor) as doticu_npcp_member
endFunction

Alias[] function Get_Members(int begin = 0, int end = -1)
    return Sort_Filled(begin, end)
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
    return ref_member && ref_member.Is_Clone() && Should_Unclone_Actor(ref_member.Actor())
endFunction

; Events
event On_Load_Mod()
    Enforce_Loaded()
endEvent

; Update Methods
function u_0_9_0()
    Alias[] arr_aliases = All()
    int idx_aliases = 0
    int num_aliases = arr_aliases.length
    int prev_percent = -1
    int curr_percent = -1

    while idx_aliases < num_aliases
        curr_percent = (idx_aliases * 100 / num_aliases) as int
        if prev_percent != curr_percent
            LOGS.Print("%%" + curr_percent)
            prev_percent = curr_percent
        endIf
        
        (arr_aliases[idx_aliases] as doticu_npcp_member).u_0_9_0()
        
        idx_aliases += 1
    endWhile

    LOGS.Print("%%100")
endFunction
