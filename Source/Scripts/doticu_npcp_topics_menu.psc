;/
    Copyright © 2020 r-neal-kelly, aka doticu
/;

Scriptname doticu_npcp_topics_menu extends TopicInfo hidden

; Modules
doticu_npcp_funcs property FUNCS hidden
    doticu_npcp_funcs function Get()
        return doticu_npcp.Funcs()
    endFunction
endProperty
doticu_npcp_containers property CONTAINERS hidden
    doticu_npcp_containers function Get()
        return doticu_npcp.Funcs().CONTAINERS
    endFunction
endProperty
doticu_npcp_commands property COMMANDS hidden
    doticu_npcp_commands function Get()
        return doticu_npcp.Control().COMMANDS
    endFunction
endProperty

; Private Methods
function p_Open_Chest(ObjectReference ref_container, string str_name)
    doticu_npcp.Object_Ref_Categorize(doticu_npcp_consts.Input_Category())
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
    p_Open_Chest(doticu_npcp_consts.Input_Category(), " Input ")
endFunction

; Weapons
function Chests_Weapons_Swords(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Swords_Category(), " Swords ")
endFunction
function Chests_Weapons_Greatswords(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Greatswords_Category(), " Greatswords ")
endFunction
function Chests_Weapons_Waraxes(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Waraxes_Category(), " Waraxes ")
endFunction
function Chests_Weapons_Battleaxes(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Battleaxes_Category(), " Battleaxes ")
endFunction
function Chests_Weapons_Maces(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Maces_Category(), " Maces ")
endFunction
function Chests_Weapons_Warhammers(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Warhammers_Category(), " Warhammers ")
endFunction
function Chests_Weapons_Daggers(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Daggers_Category(), " Daggers ")
endFunction
function Chests_Weapons_Staves(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Staves_Category(), " Staves ")
endFunction
function Chests_Weapons_Bows(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Bows_Category(), " Bows ")
endFunction
function Chests_Weapons_Ammo(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Ammo_Category(), " Ammo ")
endFunction
function Chests_Weapons_Others(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Weapons_Category(), " Other Weapons ")
endFunction

; Apparel
function Chests_Apparel_Light_Armor(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Light_Armor_Category(), " Light Armor ")
endFunction
function Chests_Apparel_Heavy_Armor(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Heavy_Armor_Category(), " Heavy Armor ")
endFunction
function Chests_Apparel_Shields(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Shields_Category(), " Shields ")
endFunction
function Chests_Apparel_Jewelry(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Jewelry_Category(), " Jewelry ")
endFunction
function Chests_Apparel_Clothes(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Clothes_Category(), " Clothes ")
endFunction

; Edibles
function Chests_Edibles_Potions(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Potions_Category(), " Potions ")
endFunction
function Chests_Edibles_Poisons(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Poisons_Category(), " Poisons ")
endFunction
function Chests_Edibles_Ingredients(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Ingredients_Category(), " Ingredients ")
endFunction
function Chests_Edibles_Food(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Food_Category(), " Food ")
endFunction

; Misc
function Chests_Misc_Soulgems(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Soulgems_Category(), " Soulgems ")
endFunction
function Chests_Misc_Scrolls(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Scrolls_Category(), " Scrolls ")
endFunction
function Chests_Misc_Metals(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Metals_Category(), " Metals ")
endFunction
function Chests_Misc_Leather(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Leather_Category(), " Leather ")
endFunction
function Chests_Misc_Gems(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Gems_Category(), " Gems ")
endFunction
function Chests_Misc_Clutter(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Clutter_Category(), " Clutter ")
endFunction
function Chests_Misc_Keys(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Keys_Category(), " Keys ")
endFunction
function Chests_Misc_Others(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Misc_Category(), " Other Misc ")
endFunction

; Books
function Chests_Books_Spell_Tomes(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Spell_Tomes_Category(), " Spell Tomes ")
endFunction
function Chests_Books_Recipes(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Recipes_Category(), " Recipes ")
endFunction
function Chests_Books_A(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.A_Books_Category(), " Books A ")
endFunction
function Chests_Books_B(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.B_Books_Category(), " Books B ")
endFunction
function Chests_Books_C(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.C_Books_Category(), " Books C ")
endFunction
function Chests_Books_D(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.D_Books_Category(), " Books D ")
endFunction
function Chests_Books_E(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.E_Books_Category(), " Books E ")
endFunction
function Chests_Books_F(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.F_Books_Category(), " Books F ")
endFunction
function Chests_Books_G(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.G_Books_Category(), " Books G ")
endFunction
function Chests_Books_H(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.H_Books_Category(), " Books H ")
endFunction
function Chests_Books_I(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.I_Books_Category(), " Books I ")
endFunction
function Chests_Books_J(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.J_Books_Category(), " Books J ")
endFunction
function Chests_Books_K(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.K_Books_Category(), " Books K ")
endFunction
function Chests_Books_L(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.L_Books_Category(), " Books L ")
endFunction
function Chests_Books_M(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.M_Books_Category(), " Books M ")
endFunction
function Chests_Books_N(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.N_Books_Category(), " Books N ")
endFunction
function Chests_Books_O(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.O_Books_Category(), " Books O ")
endFunction
function Chests_Books_P(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.P_Books_Category(), " Books P ")
endFunction
function Chests_Books_Q(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Q_Books_Category(), " Books Q ")
endFunction
function Chests_Books_R(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.R_Books_Category(), " Books R ")
endFunction
function Chests_Books_S(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.S_Books_Category(), " Books S ")
endFunction
function Chests_Books_T(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.T_Books_Category(), " Books T ")
endFunction
function Chests_Books_U(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.U_Books_Category(), " Books U ")
endFunction
function Chests_Books_V(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.V_Books_Category(), " Books V ")
endFunction
function Chests_Books_W(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.W_Books_Category(), " Books W ")
endFunction
function Chests_Books_X(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.X_Books_Category(), " Books X ")
endFunction
function Chests_Books_Y(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Y_Books_Category(), " Books Y ")
endFunction
function Chests_Books_Z(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Z_Books_Category(), " Books Z ")
endFunction
function Chests_Books_Others(ObjectReference ___)
    p_Open_Chest(doticu_npcp_consts.Books_Category(), " Books # ")
endFunction
