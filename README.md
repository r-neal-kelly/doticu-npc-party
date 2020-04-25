# doticu-npc-party
*A follower framework for The Elder Scrolls V: Skyrim Special Edition that allows you to manage and keep track of hundreds of NPCs.*

It can be tough to manage all my followers, as I always end up getting a lot of them. It's hard to know: who is a follower, how many do I have, how can I easily switch one out for another, where can I find them, and why can't I have more? In order to handle all the followers, I knew I needed to use a follower framework, a mod that manages multiple followers at a time. But what mods are available? How many do they allow? How well do they manage my followers? And to what extent? With all the quirks of managing, outfitting, cloning, resurrecting, and more, I realized that I really wanted something that can handle a *lot* of followers. So I set out to make:

# *NPC Party*

## Features
- a pool of **512 members**
- up to **16 followers** at a time
- **clones** of humanoid NPCs
- a **pack** per member to carry your items
- multiple **outfits** per member you can customize
- **settings** to fine tune your experience
- **dialogue** commands
- an **MCM menu**
- numerous **hotkeys**
- **settlers** who will live where you tell them to
- **immobile** members who will stay where you leave them
- **warriors**, **mages**, **archers**, and **classless** teammates
- **mortal**, **protected**, **essential**, or **invulnerable** followers
- and **thralls** to sustain vampire players
- they can be **renamed** to whatever you want
- **summoned** to wherever you are
- **moved** out of the way
- **displayed** as you cycle through members
- and they **level** as you level

## Requires
- [Skyrim SE 1.5.97+](https://store.steampowered.com/app/489830/The_Elder_Scrolls_V_Skyrim_Special_Edition/)
- [SKSE 2.0.17+](https://skse.silverlock.org/)
- [SkyUI 5.2SE+](https://www.nexusmods.com/skyrimspecialedition/mods/12604)

# 
## Members and Followers
A member is an NPC that is managed by the framework, and a follower is an active member who will travel with you and fight for you. You can have up to 512 managed NPCs at a time, and up to 16 followers at a time. Whenever you please, you can switch out followers for different members by using the MCM menu. No longer will you have to go searching for a lost follower! It's as easy as clicking a few buttons and they will come to you. Members and Followers are the bread and butter of NPC Party, and you'll see these terms used often.

# 
## Clones
Cloning NPCs allows for less conflicts with other mods and also vanilla Skyrim, because any changes made to an original NPC can lead to a bug. Even though in the vanilla game, a clone can still cause conflicts, this framework has solved many of the traditional problems with cloning. Now clones can change more while altering the original NPC less. Additionally, cloning an exact lookalike of a generic NPC, such as a town guard or bandit, is now possible with this framework. Cloning gives you more stable followers and copies of NPCs, whether they be unique or generic, friend or foe.

# 
## Packs and Outfits
It is frustrating when follower's randomly add items to their inventory, or when they equip things you only want them to carry. With NPC Party, each member has a separate pack, which acts as their basic inventory, and they will never equip anything within it. They also have several outfits that are their own containers, which will not randomly fill up with junk. Each member will consistently wear what you tell them to. Optionally their outfits can be filled with equipment, or start out empty. You may also have members automatically change their outfit depending on their role. Both original and cloned NPCs within the framework have their own pack and outfits. Only items that are in each individual outfit are equipped, while the items in their pack remain untouched.

# 
## Style and Vitality
Followers can be styled as a warrior, a mage, an archer, or fight however they choose. A follower's style effects their in-game attributes and skills as well as what weapons they are most likely to use. Vitality is the state of their vulnerability in combat. If they are mortal they may die at the hands of your enemies. Protected status shields them from outright death, except should you be the one to deal the final blow. Essential status will keep even you from killing them, but they will take a knee when they run out of health. And Invulnerable status speaks for itself. Style and Vitality gracefully allow you to change how your followers handle combat and allow you to get the most fun out of the framework.

# 
## Beta
This mod is currently in beta testing. You may run into a few hiccups every now and then, including slow execution, unpolished features, unexpected behaviors, and sometimes even outright bugs. I hope to resolve any issues and bring the mod out of beta into version 1.0.0. Mid-game updates are supported in the mod and will be the usual method. But sometimes updating may require a fresh save game. Also, there is currently no uninstall feature. Just uninstalling the mod is not the end of one's save game, but it will leave behind data that is no longer in use. This and several other features are being planned.

# 
## Compatibility
One of the goals of this mod was to touch as few vanilla assets as possible, but no promises can be made regarding compatibility. Currently, the vanilla follower system has been disabled, and the consequences have not been fully tested. There will be issues with other full-scale follower frameworks being used at the same time. Custom followers who use the vanilla system will need to use the framework. If they don't use the vanilla system, they may be fully compatible alongside the framework. Other outfitting mods are now compatible when using a member's "Vanilla" outfit.

# 
## Conclusion
I hope that this mod changes your follower experience for the better. My goal was to spend less time dilly dallying with obscure issues in the follower system, vanilla or modded, and to enjoy the game with as many followers as I want to. I wish the same for you. Whether you want to have one cherished follower who defines your journey, or amass a cult following of NPCs to do your every whim, whether you want to have mortal followers who can truly die, or a team of invincible power-houses to rock the world, whether you want them to wear armor, or no armor, whether you want them to carry all your items, or nothing at all, whether you want to rename them, clone them, resurrect them, or even just move them out of the way when they are blocking a door, I hope this mod benefits you. Thank you for playing NPC Party!

# 
## Thank You
- [Bethesda](https://bethesda.net/) for Skryim, which is such an endearing masterpiece.
- [SSEEdit/TesVEdit/xEdit Team](https://github.com/TES5Edit/TES5Edit) for such an amazing [tool](https://www.nexusmods.com/skyrimspecialedition/mods/164).
- [Mod Organizer 2 Team](https://github.com/ModOrganizer2) for your indispensable [program](https://www.nexusmods.com/skyrimspecialedition/mods/6194).
- [SKSE Team](http://skse.silverlock.org/) for your extender, which has extended the life of the game itself.
- [SkyUI Team](https://github.com/schlangster/skyui) for not only the [mod](https://www.nexusmods.com/skyrimspecialedition/mods/12604) and the MCM menu, but also for the fairly good [wiki](https://github.com/schlangster/skyui/wiki/MCM-API-Reference) that comes with it.
- [PapyrusUtil Team](https://www.nexusmods.com/skyrimspecialedition/mods/13048) for your work and especially the sorting functions, which are wonderfully useful and lacking in vanilla Papyrus.
- [Amazing Follower Tweaks](https://www.nexusmods.com/skyrimspecialedition/mods/6656) developers! Your mod is a great inspiration for how a follower framework can be fun and consistent.
- [My Home is Your Home](https://www.nexusmods.com/skyrimspecialedition/mods/20227) developers for such a wonderful idea, and the methods with which you implement it.
- [Dress Up Lover's NPC Outfit Changer](https://www.nexusmods.com/skyrimspecialedition/mods/28736) developer kuroko137 for inspiring me with your awesome mod.
- [Simple NPC Outfit Manager](https://www.nexusmods.com/skyrimspecialedition/mods/15211) developer confusedchim, for showing the basics of how to get things to work.
- [joelday](https://github.com/joelday) for [papyrus-lang](https://github.com/joelday/papyrus-lang) and the excellent [guide](https://github.com/joelday/papyrus-lang/wiki/Using-Mod-Organizer-2) on how to use the Creation Kit with Mod Organizer 2.
- [fireundubh](https://github.com/fireundubh) for your parallel papyrus compiler [pyro](https://github.com/fireundubh/pyro) and the [wiki](https://wiki.fireundubh.com/pyro) that goes with it.
- OldMansBeard for helping me [reuse vanilla voices](https://forums.nexusmods.com/index.php?/topic/8223653-reusing-voice-files/) without copying and redistributing them.
- cumbrianlad for a [discussion on persistent references](https://forums.nexusmods.com/index.php?/topic/8082738-is-512-persistent-actor-references-bad/), and how this can take a toll on the player's gameplay.
- [Creation Kit Wiki](https://www.creationkit.com/index.php?title=Main_Page) for the wealth of knowledge with which this mod was made.
- [GitHub](https://github.com) for giving my codebase a place to live online.
- [NexusMods](https://www.nexusmods.com/) for such a great site, and for hosting my mod!
- beta testers, for your interest, bug reports, and suggestions to make this mod better and better.
- my family, for giving me the time, space, and sustenance to make this mod.
- and every one else who has helped me directly or indirectly, if I have failed to mention you!

Last but not least, a **big** thank you to all who try out my mod, and to all of you who enjoy it and find value in it.
