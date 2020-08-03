;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_actors extends Quest

; Modules
doticu_npcp_consts property CONSTS hidden
    doticu_npcp_consts function Get()
        return p_DATA.CONSTS
    endFunction
endProperty
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return p_DATA.MODS.FUNCS
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
doticu_npcp_movee property MOVEE
    doticu_npcp_movee function Get()
        return GetAliasByName("movee") as doticu_npcp_movee
    endFunction
endProperty

; Private Constants
doticu_npcp_data    p_DATA          =  none

; Private Variables
bool                p_is_created    = false
Actor               p_ref_menu      =  none

; Friend Methods
function f_Create(doticu_npcp_data DATA)
    p_DATA = DATA

    p_is_created = true

    PLAYER.f_Create(DATA)
endFunction

function f_Destroy()
    if MOVEE.Exists()
        MOVEE.f_Destroy()
    endIf
    if GREETER.Exists()
        GREETER.f_Destroy()
    endIf
    PLAYER.f_Destroy()

    p_is_created = false
endFunction

function f_Register()
    PLAYER.f_Register()
    if GREETER.Exists()
        GREETER.f_Register()
    endIf
    if MOVEE.Exists()
        MOVEE.f_Register()
    endIf
endFunction

function f_Unregister()
    if MOVEE.Exists()
        MOVEE.f_Unregister()
    endIf
    if GREETER.Exists()
        GREETER.f_Unregister()
    endIf
    PLAYER.f_Unregister()
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

bool function Is_Leveled(Actor ref_actor)
    return ref_actor && ref_actor.GetLeveledActorBase() != ref_actor.GetActorBase()
endFunction

bool function Is_Unleveled(Actor ref_actor)
    return ref_actor && ref_actor.GetLeveledActorBase() == ref_actor.GetActorBase()
endFunction

bool function Is_Vampire(Actor ref_actor)
    return ref_actor && ref_actor.HasKeyword(doticu_npcp_consts.Vampire_Keyword())
endFunction

bool function Is_Male(Actor ref_actor)
    return Get_Sex(ref_actor) == doticu_npcp_codes.SEX_MALE()
endFunction

bool function Is_Female(Actor ref_actor)
    return Get_Sex(ref_actor) == doticu_npcp_codes.SEX_FEMALE()
endFunction

bool function Is_Essential(Actor ref_actor)
    if Is_Leveled(ref_actor)
        return Get_Base(ref_actor).IsEssential() || Get_Leveled_Base(ref_actor).IsEssential()
    else
        return ref_actor.IsEssential()
    endIf
endFunction

ActorBase function Get_Base(Actor ref_actor); Get_Static_Base
    if ref_actor
        ; only returns a real or static leveled base, never a dynamic leveled base
        return ref_actor.GetActorBase()
    else
        return none
    endIf
endFunction

ActorBase function Get_Leveled_Base(Actor ref_actor); Get_Dynamic_Base
    if ref_actor
        ; only returns a real or dynamic leveled base, never a static leveled base
        return ref_actor.GetLeveledActorBase()
    else
        return none
    endIf
endFunction

ActorBase function Get_Real_Base(Actor ref_actor)
    if ref_actor
        ; only returns a real base, never a static or dynamic leveled base
        ActorBase base_actor = ref_actor.GetActorBase()
        ActorBase leveled_actor = ref_actor.GetLeveledActorBase()
        if base_actor != leveled_actor; Is_Leveled
            return leveled_actor.GetTemplate()
        else
            return base_actor
        endIf
    else
        return none
    endIf
endFunction

string function Name(Actor ref_actor)
    if ref_actor
        return ref_actor.GetDisplayName()
    else
        return ""
    endIf
endFunction

function Rename(Actor ref_actor, string str_name)
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

Outfit function Get_Base_Outfit(Actor ref_actor)
    if ref_actor
        ; leveled have the outfit on leveled base only.
        ; GetLeveledActorBase() returns real base for unleveled/template.
        return ref_actor.GetLeveledActorBase().GetOutfit()
    else
        return none
    endIf
endFunction

function Set_Base_Outfit(Actor ref_actor, Outfit outfit_base)
    if ref_actor && outfit_base
        ; leveled have the outfit on leveled base only.
        ; GetLeveledActorBase() returns real base for unleveled/template.
        ; does not immediately affect the ref_actor's outfit
        ref_actor.GetLeveledActorBase().SetOutfit(outfit_base)
    endIf
endFunction

int function Get_Vitality(Actor ref_actor)
    ActorBase p_base_actor = ref_actor.GetLeveledActorBase()

    if p_base_actor.IsProtected()
        return doticu_npcp_codes.VITALITY_PROTECTED()
    elseIf p_base_actor.IsEssential()
        return doticu_npcp_codes.VITALITY_ESSENTIAL()
    elseIf p_base_actor.IsInvulnerable()
        return doticu_npcp_codes.VITALITY_INVULNERABLE()
    else
        return doticu_npcp_codes.VITALITY_MORTAL()
    endIf
endFunction

function Essentialize(Actor ref_actor)
    Get_Base(ref_actor).SetEssential(true)

    if Is_Leveled(ref_actor)
        Get_Leveled_Base(ref_actor).SetEssential(true)
    endIf
endFunction

function Unessentialize(Actor ref_actor)
    Get_Base(ref_actor).SetEssential(false)

    if Is_Leveled(ref_actor)
        Get_Leveled_Base(ref_actor).SetEssential(false)
    endIf
endFunction

function Kill(Actor ref_actor)
    bool is_essential = Is_Essential(ref_actor)

    if is_essential
        Unessentialize(ref_actor)
    endIf

    ref_actor.Kill(none)

    if is_essential
        Essentialize(ref_actor)
    endIf
endFunction

function Open_Inventory(Actor ref_actor)
    ref_actor.OpenInventory(true)
endFunction

function Token(Actor ref_actor, MiscObject misc_token, int count_token = 1)
    if !ref_actor || !misc_token
        return
    endIf

    int curr_count_token = ref_actor.GetItemCount(misc_token)
    if curr_count_token != count_token
        if curr_count_token > 0
            ref_actor.RemoveItem(misc_token, curr_count_token, true)
        endIf
        ref_actor.AddItem(misc_token, count_token, true)            
    endIf
endFunction

function Untoken(Actor ref_actor, MiscObject misc_token)
    if !ref_actor || !misc_token
        return
    endIf
    
    int curr_count_token = ref_actor.GetItemCount(misc_token)
    if curr_count_token > 0
        ref_actor.RemoveItem(misc_token, curr_count_token, true)
    endIf
endFunction

bool function Has_Token(Actor ref_actor, MiscObject misc_token, int count_token = 1)
    return ref_actor && ref_actor.GetItemCount(misc_token) == count_token
endFunction

function Delete(Actor ref_actor)
    ref_actor.Disable()
    ref_actor.Delete()
endFunction

function Apply_Ability(Actor ref_actor, Spell ability)
    ; it's necessary to remove it before adding it back, because
    ; the engine simply will not do everything correctly otherwise
    ref_actor.RemoveSpell(ability)
    ref_actor.AddSpell(ability, false)
endFunction

function Unapply_Ability(Actor ref_actor, Spell ability)
    ref_actor.RemoveSpell(ability)
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

function Stop_If_Playing_Music(Actor ref_actor)
    BardSongsScript script = doticu_npcp_consts.Bard_Songs_Quest() as BardSongsScript

    if script.BardSongs_Bard.GetActorReference() == ref_actor
        script.StopAllSongs()
        script.BardSongs_Bard.Clear()
        ref_actor.Disable()
        ref_actor.Enable()
    elseIf script.BardSongs_Bard2.GetActorReference() == ref_actor
        script.StopAllSongs()
        script.BardSongs_Bard2.Clear()
        ref_actor.Disable()
        ref_actor.Enable()
    elseIf script.BardSongsInstrumental_Bard.GetActorReference() == ref_actor
        script.StopAllSongs()
        script.BardSongsInstrumental_Bard.Clear()
        ref_actor.Disable()
        ref_actor.Enable()
    elseIf script.BardSongsInstrumental_Bard2.GetActorReference() == ref_actor
        script.StopAllSongs()
        script.BardSongsInstrumental_Bard2.Clear()
        ref_actor.Disable()
        ref_actor.Enable()
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

function Create_Menu()
    if p_ref_menu
        Destroy_Menu()
    endIf

    p_ref_menu = doticu_npcp_consts.Player_Actor().PlaceAtMe(doticu_npcp_consts.Menu_Actor_Base(), 1, false, true) as Actor
    FUNCS.ACTORS.Move_To(p_ref_menu, doticu_npcp_consts.Player_Actor())
    p_ref_menu.Enable()
endFunction

function Destroy_Menu()
    if !p_ref_menu
        return
    endIf

    p_ref_menu.Disable()
    p_ref_menu.Delete()
endFunction

int function Toggle_Move(Actor ref_actor)
    if !MOVEE.Exists()
        if !ref_actor
            return doticu_npcp_codes.ACTOR()
        endIf
        
        doticu_npcp_member ref_member = p_DATA.MODS.MEMBERS.Get_Member(ref_actor)
        if ref_member
            if ref_member.Is_Mannequin()
                return doticu_npcp_codes.MANNEQUIN()
            elseIf ref_member.Is_Display()
                return doticu_npcp_codes.DISPLAY()
            endIf
        endIf

        MOVEE.f_Create(p_DATA, ref_actor)
        MOVEE.f_Register()

        return doticu_npcp_codes.IS()
    else
        MOVEE.f_Unregister()
        MOVEE.f_Destroy()

        return doticu_npcp_codes.ISNT()
    endIf
endFunction

function Pacify(Actor ref_actor)
    if !ref_actor
        return
    endIf

    ref_actor.SetActorValue("Aggression", 0)
    ref_actor.StopCombat()
    ref_actor.StopCombatAlarm()
    ref_actor.EvaluatePackage()
endFunction

function Ragdoll(Actor ref_actor)
    ; maybe should accept a timer, which can be done async or parallel
    ref_actor.SetActorValue("Paralysis", 1); should this come after the push?
    doticu_npcp_consts.Player_Actor().PushActorAway(ref_actor, 0.0)
endFunction

function Unragdoll(Actor ref_actor)
    while ref_actor.GetActorValue("Paralysis") != 0
        ref_actor.SetActorValue("Paralysis", 0)
    endwhile
    ref_actor.EvaluatePackage()
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

function Set_Factions(Actor ref_actor, Faction[] arr_factions, int[] arr_ranks); arr_ranks = none
    ref_actor.RemoveFromAllFactions()
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

function Set_Faction_Ranks(Actor ref_actor, Faction[] arr_factions, int[] arr_ranks); arr_ranks = none
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

function Add_Factions(Actor ref_actor, Faction[] arr_factions, int[] arr_ranks); arr_ranks = none
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

function Remove_Factions(Actor ref_actor, Faction[] arr_factions)
    int idx_factions = 0
    int num_factions = arr_factions.length
    while idx_factions < num_factions
        ref_actor.RemoveFromFaction(arr_factions[idx_factions])
        idx_factions += 1
    endWhile
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

    doticu_npcp.Print(str_inventory)
endFunction
