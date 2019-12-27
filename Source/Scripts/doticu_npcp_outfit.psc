Scriptname doticu_npcp_outfit extends ObjectReference

; Private Constants
doticu_npcp_consts      p_CONSTS        = none
doticu_npcp_actors      p_ACTORS        = none
doticu_npcp_containers  p_CONTAINERS    = none
doticu_npcp_logs        p_LOGS          = none

Outfit                  p_OUTFIT        = none
LeveledItem             p_LEVELED       = none

; Friend Methods
function f_Link(doticu_npcp_data DATA)
    p_CONSTS = DATA.CONSTS
    p_ACTORS = DATA.MODS.FUNCS.ACTORS
    p_CONTAINERS = DATA.MODS.FUNCS.CONTAINERS
    p_LOGS = DATA.MODS.FUNCS.LOGS
endFunction

function f_Initialize(Outfit form_outfit)
    p_OUTFIT = form_outfit
    p_LEVELED = form_outfit.GetNthPart(0) as LeveledItem
endFunction

function f_Register()
endFunction

function f_Create(string str_name)
    self.SetDisplayName(str_name, true)
    self.SetActorOwner(p_CONSTS.ACTOR_PLAYER.GetActorBase())
endFunction

function f_Destroy()
    self.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)
    self.Disable()
    self.Delete()
endFunction

; Public Methods
string function Get_Name()
    return self.GetDisplayName()
endFunction

function Set_Name(string str_name)
    self.SetDisplayName(str_name, true)
endFunction

int function Count_Items()
    return self.Count_Items()
endFunction

int function Count_Item(Form form_item)
    return self.Count_Item(form_item)
endFunction

function Put()
    self.Activate(p_CONSTS.ACTOR_PLAYER)
endFunction

function Get(Actor ref_actor)
    int num_forms
    int idx_forms
    Form ref_form

    self.RemoveAllItems(p_CONSTS.ACTOR_PLAYER, false, true)

    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form as Armor && ref_actor.IsEquipped(ref_form)
            self.AddItem(ref_form, 1, true)
        endIf
        idx_forms += 1
    endWhile
endFunction

function Set(Actor ref_actor, bool do_input = true)
    ObjectReference ref_container_temp = p_CONTAINERS.Create_Temp()
    Form[] arr_leveled
    int num_forms
    int idx_forms
    Form ref_form

    ; So we can determine what items are in the currently equipped outfit
    num_forms = p_LEVELED.GetNumForms()
    arr_leveled = Utility.CreateFormArray(num_forms, none)
    idx_forms = 0
    while idx_forms < num_forms
        arr_leveled[idx_forms] = p_LEVELED.GetNthForm(idx_forms)
        idx_forms += 1
    endWhile

    ; backup inventory minus current outfit, so we can clear items undesireably added after SetOutfit
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if ref_form as Armor && arr_leveled.Find(ref_form) > -1
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form) - 1, true, ref_container_temp)
            idx_forms += 1
        else
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form), true, ref_container_temp)
            num_forms -= 1
        endIf
    endWhile

    ; Accept User Input (now with the leveled list, we may actually be able to remove this finally, and always use Put instead.)
    if do_input
        self.Activate(p_CONSTS.ACTOR_PLAYER)
    endIf
    Utility.Wait(0.1)

    ; update the leveled list, which is attached to Outfit form
    p_LEVELED.Revert()
    num_forms = self.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = self.GetNthForm(idx_forms)
        p_LEVELED.AddForm(ref_form, 1, 1)
        idx_forms += 1
    endWhile

    ; the engine will actually apply the outfit in the correct way, which we cannot do manually
    ref_actor.SetOutfit(p_CONSTS.OUTFIT_EMPTY)
    ref_actor.SetOutfit(p_OUTFIT)
    Utility.Wait(0.1)

    ; we remove everything but the new outfit to clean out all the junk
    num_forms = ref_actor.GetNumItems()
    idx_forms = 0
    while idx_forms < num_forms
        ref_form = ref_actor.GetNthForm(idx_forms)
        if self.GetItemCount(ref_form) < 1
            ref_actor.RemoveItem(ref_form, ref_actor.GetItemCount(ref_form), true, none)
            num_forms -= 1
        else
            idx_forms += 1
        endIf
    endWhile

    ; then we add back the original inventory, without the old outfit to avoid dupes
    p_CONTAINERS.Take_All(ref_actor, ref_container_temp)

    ; make sure everything is equipped and rendered from the actor's main inventory also
    p_ACTORS.Update_Equipment(ref_actor)
endFunction

function Unset(Actor ref_actor)
    ObjectReference ref_container_temp = p_CONTAINERS.Create_Temp()

    self.RemoveAllItems(ref_container_temp, false, true)
    Set(ref_actor, false)
    ref_container_temp.RemoveAllItems(self, false, true)
endFunction

function Refresh(Actor ref_actor)
    Set(ref_actor, false)
endFunction

; Events
event OnItemAdded(Form form_item, int count_item, ObjectReference ref_item, ObjectReference ref_container_source)
    if form_item as Armor == none
        self.RemoveItem(form_item, count_item, true, ref_container_source)
        p_LOGS.Create_Note("Can only add apparel to an outfit.")
    endIf
endEvent
