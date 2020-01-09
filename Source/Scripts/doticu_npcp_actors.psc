Scriptname doticu_npcp_actors extends Quest

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
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return p_DATA.MODS.FUNCS.CONTAINERS
    endFunction
endProperty
doticu_npcp_player property PLAYER
    doticu_npcp_player function Get()
        return GetAliasByName("player") as doticu_npcp_player
    endFunction
endProperty
doticu_npcp_greeter property GREETER
    doticu_npcp_greeter function Get()
        return GetAliasByName("greeter") as doticu_npcp_greeter
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

    PLAYER.f_Create(DATA)
endFunction

function f_Destroy()
    if GREETER.Exists()
        GREETER.f_Destroy()
    endIf
    PLAYER.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    PLAYER.f_Register()
    GREETER.f_Register()
endFunction

; Private Methods
bool function p_Has_Same_Head(Actor ref_actor_1, Actor ref_actor_2)
    ActorBase ref_base_1 = ref_actor_1.GetLeveledActorBase(); returns unleveled base too
    ActorBase ref_base_2 = ref_actor_2.GetLeveledActorBase()
    int int_slots_1 = ref_base_1.GetNumHeadParts()
    int int_slots_2 = ref_base_2.GetNumHeadParts()

    if int_slots_1 != int_slots_2
        return false
    endIf

    int int_slot_idx = 0
    while int_slot_idx < int_slots_1
        if ref_base_1.GetNthHeadPart(int_slot_idx) != ref_base_2.GetNthHeadPart(int_slot_idx)
            return false
        endIf
        int_slot_idx += 1
    endWhile

    return true
endFunction

; Public Methods
bool function Is_Alive(Actor ref_actor)
    return ref_actor && !ref_actor.IsDead()
endFunction

bool function Is_Dead(Actor ref_actor)
    return ref_actor && ref_actor.IsDead()
endFunction

bool function Is_Sleeping(Actor ref_actor)
    ; 0 Not Sleeping
    ; 2 Not Sleeping, Wants to Sleep
    ; 3 Sleeping
    ; 4 Sleeping, Wants to Wake
    return ref_actor && ref_actor.GetSleepState() == 3
endFunction

bool function Is_Unique(Actor ref_actor)
    return ref_actor && ref_actor.GetActorBase().IsUnique()
endFunction

bool function Is_Generic(Actor ref_actor)
    return ref_actor && !ref_actor.GetActorBase().IsUnique()
endFunction

bool function Is_Vampire(Actor ref_actor)
    return ref_actor && ref_actor.HasKeyword(CONSTS.KEYWORD_VAMPIRE)
endFunction

bool function Is_Male(Actor ref_actor)
    return Get_Sex(ref_actor) == CODES.GENDER_MALE
endFunction

bool function Is_Female(Actor ref_actor)
    return Get_Sex(ref_actor) == CODES.GENDER_FEMALE
endFunction

bool function Is_Essential(Actor ref_actor)
    return ref_actor.IsEssential()
endFunction

ActorBase function Get_Base(Actor ref_actor)
    if ref_actor
        return ref_actor.GetActorBase(); should this be leveled base?
    else
        return none
    endIf
endFunction

string function Get_Name(Actor ref_actor)
    if ref_actor
        return ref_actor.GetDisplayName()
    else
        return ""
    endIf
endFunction

function Set_Name(Actor ref_actor, string str_name)
    if ref_actor && str_name != ""
        ref_actor.SetDisplayName(str_name, true)
    endIf
endFunction

string function Get_Base_Name(Actor ref_actor)
    if ref_actor
        return ref_actor.GetName()
    else
        return ""
    endIf
endFunction

function Set_Base_Name(Actor ref_actor, string str_name)
    if ref_actor && str_name != ""
        ref_actor.SetDisplayName(str_name, true)
        ref_actor.SetName(str_name)
    endIf
endFunction

int function Get_Sex(Actor ref_actor)
    if ref_actor
        return Get_Base(ref_actor).GetSex()
    else
        return 1234567
    endIf
endFunction

int function Get_Vitality(Actor ref_actor)
    ActorBase p_base_actor

    if Is_Unique(ref_actor)
        p_base_actor = ref_actor.GetActorBase()
    else
        p_base_actor = ref_actor.GetLeveledActorBAse()
    endIf

    if p_base_actor.IsProtected()
        return CODES.IS_PROTECTED
    elseIf p_base_actor.IsEssential()
        return CODES.IS_ESSENTIAL
    elseIf p_base_actor.IsInvulnerable()
        return CODES.IS_INVULNERABLE
    else
        return CODES.IS_MORTAL
    endIf
endFunction

function Vitalize(Actor ref_actor, int code_vitality)
    ; maybe we can do more to make this affect only instances, instead of base

    ActorBase p_base_actor = Get_Base(ref_actor)

    if code_vitality == CODES.IS_MORTAL
        p_base_actor.SetProtected(false)
        p_base_actor.SetEssential(false)
        ;p_base_actor.SetInvulnerable(false)
        ref_actor.SetGhost(false)
    elseIf code_vitality == CODES.IS_PROTECTED
        p_base_actor.SetProtected(true)
        p_base_actor.SetEssential(false)
        ;p_base_actor.SetInvulnerable(false)
        ref_actor.SetGhost(false)
    elseIf code_vitality == CODES.IS_ESSENTIAL
        p_base_actor.SetProtected(false)
        p_base_actor.SetEssential(true)
        ;p_base_actor.SetInvulnerable(false)
        ref_actor.SetGhost(false)
    elseIf code_vitality == CODES.IS_INVULNERABLE
        p_base_actor.SetProtected(false)
        p_base_actor.SetEssential(false)
        ;p_base_actor.SetInvulnerable(true)
        ref_actor.SetGhost(true)
    endIf
endFunction

function Essentialize(Actor ref_actor)
    ActorBase base_actor = Get_Base(ref_actor)
    base_actor.SetEssential(true)
endFunction

function Unessentialize(Actor ref_actor)
    ActorBase base_actor = Get_Base(ref_actor)
    base_actor.SetEssential(false)
endFunction

function Kill(Actor ref_actor)
    bool is_essential = Is_Essential(ref_actor)

    if is_essential
        Unessentialize(ref_actor)
    endIf

    ref_actor.Kill(none)
    ;ref_actor.DamageActorValue(CONSTS.STR_HEALTH, -1000000.0)

    if is_essential
        Essentialize(ref_actor)
    endIf
endFunction

function Resurrect(Actor ref_actor)
    ObjectReference ref_container_temp = CONTAINERS.Create_Temp()

    CONTAINERS.Take_All(ref_container_temp, ref_actor)
    ref_actor.Disable()
    ref_actor.SetCriticalStage(CODES.CRITICAL_NONE)
    ref_actor.Resurrect()
    Pacify(ref_actor)
    ref_actor.Enable()
    CONTAINERS.Empty(ref_actor)
    CONTAINERS.Take_All(ref_actor, ref_container_temp)
    Update_Equipment(ref_actor)
endFunction

function Open_Inventory(Actor ref_actor)
    ref_actor.OpenInventory(true)
endFunction

function Token(Actor ref_actor, MiscObject misc_token, int count_token = 1)
    int curr_count_token = ref_actor.GetItemCount(misc_token)
    if curr_count_token != count_token
        if curr_count_token > 0
            ref_actor.RemoveItem(misc_token, curr_count_token, true)
        endIf
        ref_actor.AddItem(misc_token, count_token, true)            
    endIf
endFunction

function Untoken(Actor ref_actor, MiscObject misc_token)
    int curr_count_token = ref_actor.GetItemCount(misc_token)
    if curr_count_token > 0
        ref_actor.RemoveItem(misc_token, curr_count_token, true)
    endIf
endFunction

bool function Has_Token(Actor ref_actor, MiscObject misc_token, int count_token = 1)
    return ref_actor && ref_actor.GetItemCount(misc_token) == count_token
endFunction

Actor function Clone(Actor ref_actor)
    ; can prob make this parallel with the jobs pattern

    CONSTS.MARKER_CLONER.MoveTo(CONSTS.ACTOR_PLAYER, 1000.0, 1000.0, -1000.0)
    
    Form ref_form = ref_actor.GetBaseObject() as Form
    Actor ref_clone = CONSTS.MARKER_CLONER.PlaceAtMe(ref_form, 1, true, false) as Actor; persist, disable
    ref_clone.EnableAI(false)
    ref_clone.MoveTo(CONSTS.MARKER_CLONER)

    if Is_Generic(ref_actor)
        while !p_Has_Same_Head(ref_actor, ref_clone); we may need to limit this to a couple hundred tries, because I ran into an infinite somehow. an unclonable?
            ref_clone.Disable()
            ref_clone.Delete()
            ref_clone = CONSTS.MARKER_CLONER.PlaceAtMe(ref_form, 1, true, false) as Actor; persist, disable
            ref_clone.EnableAI(false)
            ref_clone.MoveTo(CONSTS.MARKER_CLONER)
        endWhile
    endIf

    CONSTS.MARKER_CLONER.MoveTo(CONSTS.MARKER_STORAGE)

    ref_clone.EnableAI(true)
    Pacify(ref_clone)
    Set_Name(ref_clone, "Clone of " + Get_Name(ref_actor))

    return ref_clone
endFunction

function Delete(Actor ref_actor)
    ref_actor.Disable()
    ref_actor.Delete()
endFunction

function Move_To(ObjectReference ref_subject, ObjectReference ref_object, int distance = 120, int angle = 0)
    Actor ref_actor = ref_subject as Actor
    bool has_enabled_ai = ref_actor && ref_actor.IsAIEnabled()
    float object_angle_z = ref_object.GetAngleZ()

    if !has_enabled_ai
        ref_actor.EnableAI(true)
    endIf

    ref_subject.MoveTo(ref_object, distance * Math.Sin(object_angle_z - angle), distance * Math.Cos(object_angle_z - angle), 0.0)
    ref_subject.SetAngle(0.0, 0.0, object_angle_z - 180 - angle)

    if !has_enabled_ai
        ref_actor.EnableAI(false)
    endIf
endFunction

bool function Is_Near_Player(Actor ref_actor, int max_distance = 1024)
    Actor ref_player = CONSTS.ACTOR_PLAYER
    Cell cell_player = ref_player.GetParentCell()
    Cell cell_actor = ref_actor.GetParentCell()

    if cell_player && cell_player.IsInterior() || cell_actor && cell_actor.IsInterior()
        if cell_player == cell_actor
            if ref_player.GetDistance(ref_actor) > max_distance
                return false
            else
                return true
            endIf
        else
            return false
        endIf
    else
        if ref_player.GetDistance(ref_actor) > max_distance
            return false
        else
            return true
        endIf
    endIf
endFunction

function Greet_Player(Actor ref_actor)
    if !ref_actor
        return
    endIf

    if GREETER.Exists()
        GREETER.f_Destroy()
    endIf

    GREETER.f_Create(p_DATA, ref_actor)
endFunction

function Pacify(Actor ref_actor)
    ref_actor.SetActorValue("Aggression", 0)
    ref_actor.StopCombat()
    ref_actor.StopCombatAlarm()
    ref_actor.EvaluatePackage()
endFunction

function Ragdoll(Actor ref_actor)
    ; maybe should accept a timer, which can be done async or parallel
    ref_actor.SetActorValue("Paralysis", 1); should this come after the push?
    CONSTS.ACTOR_PLAYER.PushActorAway(ref_actor, 0.0)
endFunction

function Unragdoll(Actor ref_actor)
    while ref_actor.GetActorValue("Paralysis") != 0
        ref_actor.SetActorValue("Paralysis", 0)
    endwhile
    ref_actor.EvaluatePackage()
endFunction

function Update_Equipment(Actor ref_actor)
    bool is_player_teammate = ref_actor.IsPlayerTeammate()
    
    if !is_player_teammate
        ref_actor.SetPlayerTeammate(true, true)
    endIf

    ref_actor.AddItem(CONSTS.WEAPON_BLANK, 1, true)
    ref_actor.RemoveItem(CONSTS.WEAPON_BLANK, 1, true, none)

    if !is_player_teammate
        ref_actor.SetPlayerTeammate(false, false)
    endIf
endFunction

bool function Has_Faction(Actor ref_actor, Faction form_faction)
    return ref_actor.IsInFaction(form_faction)
endFunction

bool function Has_Faction_Rank(Actor ref_actor, Faction form_faction, int rank)
    return ref_actor.IsInFaction(form_faction) && ref_actor.GetFactionRank(form_faction) == rank
endFunction

function Add_Faction(Actor ref_actor, Faction form_faction, int rank = 0)
    ref_actor.AddToFaction(form_faction)
    ref_actor.SetFactionRank(form_faction, rank)
endFunction

function Remove_Faction(Actor ref_actor, Faction form_faction)
    ref_actor.RemoveFromFaction(form_faction)
endFunction

int function Get_Faction_Rank(Actor ref_actor, Faction form_faction)
    return ref_actor.GetFactionRank(form_faction)
endFunction

function Set_Faction_Rank(Actor ref_actor, Faction form_faction, int rank)
    ref_actor.SetFactionRank(form_faction, rank)
endFunction

Faction[] function Get_Factions(Actor ref_actor, int min_rank = -128, int max_rank = 127)
    return ref_actor.GetFactions(min_rank, max_rank)
endFunction

function Set_Factions(Actor ref_actor, Faction[] arr_factions, int[] arr_ranks = none)
    Remove_Factions(ref_actor)
    if arr_factions
        Add_Factions(ref_actor, arr_factions, arr_ranks)
    endIf
endFunction

int[] function Get_Faction_Ranks(Actor ref_actor, Faction[] arr_factions)
    int[] arr_ranks = Utility.CreateIntArray(arr_factions.length)

    int idx_factions = 0
    int num_factions = arr_factions.length
    while idx_factions < num_factions
        arr_ranks[idx_factions] = ref_actor.GetFactionRank(arr_factions[idx_factions])
        idx_factions += 1
    endWhile
endFunction

function Set_Faction_Ranks(Actor ref_actor, Faction[] arr_factions, int[] arr_ranks = none)
    if !arr_ranks || arr_factions.length != arr_ranks.length
        arr_ranks = Utility.CreateIntArray(arr_factions.length, 0)
    endIf

    int idx_factions = 0
    int num_factions = arr_factions.length
    while idx_factions < num_factions
        ref_actor.SetFactionRank(arr_factions[idx_factions], arr_ranks[idx_factions])
        idx_factions += 1
    endWhile
endFunction

function Add_Factions(Actor ref_actor, Faction[] arr_factions, int[] arr_ranks = none)
    int idx_factions = 0
    int num_factions = arr_factions.length

    if arr_ranks
        while idx_factions < num_factions
            ref_actor.AddToFaction(arr_factions[idx_factions])
            ref_actor.SetFactionRank(arr_factions[idx_factions], arr_ranks[idx_factions])
            idx_factions += 1
        endWhile
    else
        while idx_factions < num_factions
            ref_actor.AddToFaction(arr_factions[idx_factions])
            idx_factions += 1
        endWhile
    endIf
endFunction

function Remove_Factions(Actor ref_actor, Faction[] arr_factions = none)
    if arr_factions
        int idx_factions = 0
        int num_factions = arr_factions.length
        while idx_factions < num_factions
            ref_actor.RemoveFromFaction(arr_factions[idx_factions])
            idx_factions += 1
        endWhile
    else
        ref_actor.RemoveFromAllFactions()
    endIf
endFunction

function Print_Inventory(Actor ref_actor)
    string str_inventory = ""
    int idx_forms = 0
    int num_forms = ref_actor.GetNumItems()
    Form form_form
    int num_form

    str_inventory += "[ "

    while idx_forms < num_forms
        form_form = ref_actor.GetNthForm(idx_forms)
        if form_form
            num_form = ref_actor.GetItemCount(form_form)
            str_inventory += form_form.GetName() + " (" + num_form + "),"
        else
            str_inventory += "none (0),"
        endIf
        idx_forms += 1
    endWhile

    str_inventory += " ]\n"

    MiscUtil.PrintConsole(str_inventory)
endFunction
