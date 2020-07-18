;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_topics_menu extends TopicInfo hidden

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
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return p_DATA.MODS.CONTROL.COMMANDS
    endFunction
endProperty

; Private Constants
doticu_npcp_data p_DATA = none

; Public Constants
doticu_npcp_data property DATA
    doticu_npcp_data function Get()
        return p_DATA
    endFunction
    function Set(doticu_npcp_data val)
        if p_DATA == none
            p_DATA = val
        endIf
    endFunction
endProperty

; Private Methods
function p_Open_Chest(ObjectReference ref_container, string str_name)
    doticu_npcp.Object_Ref_Categorize(CONSTS.CATEGORY_INPUT)
    CONTAINERS.Rename(ref_container, str_name)
    CONTAINERS.Open(ref_container)
endFunction

; Public Methods
function Exit(ObjectReference ___)
    FUNCS.ACTORS.Destroy_Menu()
endFunction

function Followers_Summon_All(ObjectReference ___)
    COMMANDS.Followers_Summon_All()
endFunction
function Followers_Summon_Mobile(ObjectReference ___)
    COMMANDS.Followers_Summon_Mobile()
endFunction
function Followers_Summon_Immobile(ObjectReference ___)
    COMMANDS.Followers_Summon_Immobile()
endFunction
function Followers_Stash(ObjectReference ___)
    COMMANDS.Followers_Stash()
endFunction
function Followers_Mobilize(ObjectReference ___)
    COMMANDS.Followers_Mobilize()
endFunction
function Followers_Immobilize(ObjectReference ___)
    COMMANDS.Followers_Immobilize()
endFunction
function Followers_Settle(ObjectReference ___)
    COMMANDS.Followers_Settle()
endFunction
function Followers_Unsettle(ObjectReference ___)
    COMMANDS.Followers_Unsettle()
endFunction
function Followers_Sneak(ObjectReference ___)
    COMMANDS.Followers_Sneak()
endFunction
function Followers_Unsneak(ObjectReference ___)
    COMMANDS.Followers_Unsneak()
endFunction
function Followers_Saddle(ObjectReference ___)
    COMMANDS.Followers_Saddle()
endFunction
function Followers_Unsaddle(ObjectReference ___)
    COMMANDS.Followers_Unsaddle()
endFunction
function Followers_Unfollow(ObjectReference ___)
    COMMANDS.Followers_Unfollow()
endFunction
function Followers_Unmember(ObjectReference ___)
    COMMANDS.Followers_Unmember()
endFunction

function Chests_Input(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_INPUT, " Input ")
endFunction

; Weapons
function Chests_Weapons_Swords(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_SWORDS, " Swords ")
endFunction
function Chests_Weapons_Greatswords(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_GREATSWORDS, " Greatswords ")
endFunction
function Chests_Weapons_Waraxes(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_WARAXES, " Waraxes ")
endFunction
function Chests_Weapons_Battleaxes(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BATTLEAXES, " Battleaxes ")
endFunction
function Chests_Weapons_Maces(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_MACES, " Maces ")
endFunction
function Chests_Weapons_Warhammers(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_WARHAMMERS, " Warhammers ")
endFunction
function Chests_Weapons_Daggers(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_DAGGERS, " Daggers ")
endFunction
function Chests_Weapons_Staves(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_STAVES, " Staves ")
endFunction
function Chests_Weapons_Bows(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOWS, " Bows ")
endFunction
function Chests_Weapons_Ammo(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_AMMO, " Ammo ")
endFunction
function Chests_Weapons_Others(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_WEAPONS, " Other Weapons ")
endFunction

; Apparel
function Chests_Apparel_Light_Armor(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_LIGHT_ARMOR, " Light Armor ")
endFunction
function Chests_Apparel_Heavy_Armor(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_HEAVY_ARMOR, " Heavy Armor ")
endFunction
function Chests_Apparel_Shields(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_SHIELDS, " Shields ")
endFunction
function Chests_Apparel_Jewelry(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_JEWELRY, " Jewelry ")
endFunction
function Chests_Apparel_Clothes(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_CLOTHES, " Clothes ")
endFunction

; Edibles
function Chests_Edibles_Potions(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_POTIONS, " Potions ")
endFunction
function Chests_Edibles_Poisons(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_POISONS, " Poisons ")
endFunction
function Chests_Edibles_Ingredients(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_INGREDIENTS, " Ingredients ")
endFunction
function Chests_Edibles_Food(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_FOOD, " Food ")
endFunction

; Misc
function Chests_Misc_Soulgems(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_SOULGEMS, " Soulgems ")
endFunction
function Chests_Misc_Scrolls(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_SCROLLS, " Scrolls ")
endFunction
function Chests_Misc_Metals(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_METALS, " Metals ")
endFunction
function Chests_Misc_Leather(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_LEATHER, " Leather ")
endFunction
function Chests_Misc_Gems(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_GEMS, " Gems ")
endFunction
function Chests_Misc_Clutter(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_CLUTTER, " Clutter ")
endFunction
function Chests_Misc_Keys(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_KEYS, " Keys ")
endFunction
function Chests_Misc_Others(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_OTHERS, " Other Misc ")
endFunction

; Books
function Chests_Books_Spell_Tomes(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_SPELL_TOMES, " Spell Tomes ")
endFunction
function Chests_Books_Recipes(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_RECIPES, " Recipes ")
endFunction
function Chests_Books_A(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_A, " Books A ")
endFunction
function Chests_Books_B(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_B, " Books B ")
endFunction
function Chests_Books_C(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_C, " Books C ")
endFunction
function Chests_Books_D(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_D, " Books D ")
endFunction
function Chests_Books_E(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_E, " Books E ")
endFunction
function Chests_Books_F(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_F, " Books F ")
endFunction
function Chests_Books_G(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_G, " Books G ")
endFunction
function Chests_Books_H(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_H, " Books H ")
endFunction
function Chests_Books_I(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_I, " Books I ")
endFunction
function Chests_Books_J(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_J, " Books J ")
endFunction
function Chests_Books_K(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_K, " Books K ")
endFunction
function Chests_Books_L(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_L, " Books L ")
endFunction
function Chests_Books_M(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_M, " Books M ")
endFunction
function Chests_Books_N(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_N, " Books N ")
endFunction
function Chests_Books_O(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_O, " Books O ")
endFunction
function Chests_Books_P(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_P, " Books P ")
endFunction
function Chests_Books_Q(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_Q, " Books Q ")
endFunction
function Chests_Books_R(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_R, " Books R ")
endFunction
function Chests_Books_S(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_S, " Books S ")
endFunction
function Chests_Books_T(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_T, " Books T ")
endFunction
function Chests_Books_U(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_U, " Books U ")
endFunction
function Chests_Books_V(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_V, " Books V ")
endFunction
function Chests_Books_W(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_W, " Books W ")
endFunction
function Chests_Books_X(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_X, " Books X ")
endFunction
function Chests_Books_Y(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_Y, " Books Y ")
endFunction
function Chests_Books_Z(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS_Z, " Books Z ")
endFunction
function Chests_Books_Others(ObjectReference ___)
    p_Open_Chest(CONSTS.CATEGORY_BOOKS, " Books # ")
endFunction
