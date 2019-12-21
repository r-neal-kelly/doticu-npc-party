# API
The program is distributed among many modules, each of which encompass several sub modules in their own domain. Modules and their sub modules are extended from the `Quest` type, and are made accessible globally throughout the program by initialization through `MAIN`. Each module instance contains their own scope and state, and each sub module is the same instance (`Quest`) but with state secluded from other sub modules.

---

## The `DATA` Module
Contains public values and all but one property in the entire program, the other being in `MAIN`. Each `f_Initialize()` function, with the exception of its own, is passed this module as its first parameter, making it globally accessible anywhere it is needed.

        Scriptname doticu_npcp_data extends Quest

### : `CONSTS`
Contains values that do not change after `MAIN` initialization.

        Scriptname doticu_npcp_consts extends Quest

### : `CODES`
Contains constant ints that indicate mostly certain types of errors.

        Scriptname doticu_npcp_codes extends Quest

### : `VARS`
Contains variable values that can be changed by any and every module throughout the life of the program. MCM Settings gives the user to change these global variables.

        Scriptname doticu_npcp_vars extends Quest

### : `MODS`
Contains a property pointing to every module, so they are all accessible from anywhere that has access to `DATA`. Each module is in turn expected to point to its sub modules so that, e.g. `CONTROL` can access the sub module `ACTOR2` from the module `FUNCS`.

        Scriptname doticu_npcp_mods extends Quest

---

## The `FUNCS` Module
Contains smaller types that may consist only of a handful of functions. Their subjects must be passed in manually as the first argument to each method, thus acting like a C style type as opposed to the common Object oriented class/instance model.

        Scriptname doticu_npcp_funcs extends Quest

        ; Public Methods
        function Close_Menus()

### : `ACTOR2`
An extension of the Actor class that acts as a simple helper, and more importantly allows for ease of use in tagging npcs with tokens that are strictly used in the vanilla condition system.

        Scriptname doticu_npcp_actor extends Actor

        ; Public Methods
        bool function Is_Dead(Actor ref_actor)
        bool function Is_Unique(Actor ref_actor)
        bool function Is_Generic(Actor ref_actor)
        ActorBase function Get_Base(Actor ref_actor)
        string function Get_Name(Actor ref_actor)
        function Set_Name(Actor ref_actor, string str_name)
        string function Get_Base_Name(Actor ref_actor)
        function Set_Base_Name(Actor ref_actor, string str_name)
        function Resurrect(Actor ref_actor)
        function Open_Inventory(Actor ref_actor)
        function Token(Actor ref_actor, MiscObject misc_token)
        function Untoken(Actor ref_actor, MiscObject misc_token)
        bool function Has_Token(Actor ref_actor, MiscObject misc_token)
        Actor function Clone(Actor ref_actor)
        function Delete(Actor ref_actor)
        function Move_To(ObjectReference ref_subject, ObjectReference ref_object, int distance = 60, int angle = 0)
        function Greet_Player(Actor ref_actor)

---

## The `MEMBERS` Module
Contains a unique alias for each registered npc that may or may not be a current *`IMMOBILE`*, *`SETTLER`*, or *`FOLLOWER`*. It is used to control basic behaviors of an npc, most of which occur when they are not an active *`FOLLOWER`* of the player.

        Scriptname doticu_npcp_members extends Quest

        ; Public Methods
        int function Create_Member(Actor ref_actor, bool make_clone = false)
        int function Destroy_Member(Actor ref_actor)
        bool function Has_Member(Actor ref_actor)
        doticu_npcp_member function Get_Member(Actor ref_actor)

### : `ALIASES`
Contains data and methods related to creating and destroying aliases. Each alias has several types with which to track and manipulate an alias's state.

        Scriptname doticu_npcp_aliases extends Quest

        ; Public Methods
        int function Create_Alias(Actor ref_actor)
        int function Destroy_Alias(Actor ref_actor)
        ReferenceAlias function Get_Alias(Actor ref_actor)
        bool function Has_Alias(Actor ref_actor)
        bool function Is_Full()
        int function Get_Count()
        int function Get_Max()

#### : : *`MEMBER`* Type
Contains the methods and state that allow for the most basic of manipulations of an npc, including the ability to turn them into a *`SETTLER`*, an *`IMMOBILE`*, and or a *`FOLLOWER`*.

        Scriptname doticu_npcp_member extends ReferenceAlias

        ; Public Methods
        int function Create(bool make_clone)
        int function Destroy()
        bool function Exists()
        int function Settle()
        int function Unsettle()
        int function Immobilize()
        int function Mobilize()
        int function Enforce()
        int function Access()
        doticu_npcp_settler function Get_Settler()
        doticu_npcp_immobile function Get_Immobile()

#### : : *`SETTLER`* Type
Contains the methods and state to give a *`MEMBER`* a new home in-game, with sandboxing capabilities.

        Scriptname doticu_npcp_settler extends ReferenceAlias

        ; Public Methods
        int function Create()
        int function Destroy()
        bool function Exists()
        int function Enforce()

#### : : *`IMMOBILE`* Type
Contains the methods and state to make a *`MEMBER`* stay put exactly where you tell them to. It's my intention to attempt to add animation capabilities in this type, which are remembered across game sessions.

        Scriptname doticu_npcp_immobile extends ReferenceAlias

        ; Public Methods
        int function Create()
        int function Destroy()
        bool function Exists()
        int function Enforce()

---

## The `FOLLOWERS` Module
Contains a unique alias for each current follower. These aliases are wholly distinct from `MEMBERS` aliases. A `FOLLOWERS` alias is used in addition to a `MEMBERS` alias in order to control the behavior of npcs who are actively following the player.

        Scriptname doticu_npcp_followers extends Quest

        ; Public Methods
        int function Create_Follower(Actor ref_actor)
        int function Destroy_Follower(Actor ref_actor)
        bool function Has_Follower(Actor ref_actor)
        doticu_npcp_follower function Get_Follower(Actor ref_actor)

### : `ALIASES`
(See `ALIASES` sub module in `MEMBERS` module.)

#### : : *`FOLLOWER`* Type
Contains the methods and state that make up the heart of any *`FOLLOWER`* framework, allowing for the most direct manipulation of any npc currently following the player.

        Scriptname doticu_npcp_follower extends ReferenceAlias

        ; Public Methods
        int function Create()
        int function Destroy()
        bool function Exists()
        int function Enforce()
        int function Sneak()
        int function Unsneak()
        doticu_npcp_member function Get_Member()

---

## The `CONTROL` Module
Contains all the methods with which the user interacts with the program, by keyboard, mouse, and talking to npcs.

        Scriptname doticu_npcp_control extends Quest

### : `COMMANDS`
Contains functions to control *`MEMBER`*, *`SETTLER`*, *`IMMOBILE`*, and *`FOLLOWER`* instances and notifies the user in-game of the results.

        Scriptname doticu_npcp_commands extends Quest

        ; Public Methods
        function Member_Access(Actor ref_actor)
        function Member_Settle(Actor ref_actor)
        function Member_Unsettle(Actor ref_actor)
        function Member_Immobilize(Actor ref_actor)
        function Member_Mobilize(Actor ref_actor)

### : `KEYS`
Contains helper functions to deal with *`MEMBER`*, *`SETTLER`*, *`IMMOBILE`*, and *`FOLLOWER`* instances through in-game key strokes.

        Scriptname doticu_npcp_keys extends Quest

        ; Friend Methods
        function f_Initialize(doticu_npcp_data DATA)

        ; Public Methods
        function Update_Keys()

### : `MCM`
Creates an in-game menu to control almost every aspect of the mod, from commanding followers and members, to changing global variables. This sub modules is itself divided into sub modules, one for each page that the MCM menu will have.

        Scriptname doticu_npcp_mcm extends SKI_ConfigBase

#### : : *`Followers`* Page

        Scriptname doticu_npcp_mcm_followers extends Quest

#### : : *`Members`* Page

        Scriptname doticu_npcp_mcm_members extends Quest

#### : : *`Filter`* Page

        Scriptname doticu_npcp_mcm_filter extends Quest

#### : : *`Settings`* Page
        Scriptname doticu_npcp_mcm_settings extends Quest
        
---

## The `MAIN` Module
This module is responsible for calling the `f_Initialize()` function of each module, which in turn call their own sub initializers, etc. It contains a single property pointing to `DATA`, which is passed into every `f_Initialize()` function called throughout the program. It is my intention to add a unit test sub module to `MAIN`.

        Scriptname doticu_npcp_main extends Quest
