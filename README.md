# doticu-npc-party
A follower framework for The Elder Scrolls V: Skyrim Special Edition

## Features:
- upto **512** npcs can be members
- upto **16** members can actively follow you around at a time
- **clones** of any unique npc, and even generic npcs like guards, bandits, and more can join your party
- every member can individually be:
  - a **settler** in any part of the world, making it their home
  - an **immobile** who never leaves their location and waits for you to come back to them
  - a **warrior**, **mage**, **archer**, or classless teammate
  - **mortal**, **protected**, **essential**, or **invulnerable**, you decide their fate
  - **resurrected** if ever they should die
  - and for vampire players only, a willing **thrall** who will sustain you
- several **outfits** are customizable for each individual member and can be set to change automatically or manually, whichever you choose
- a comprehensive dialogue menu can be used to command individual members and followers
- an exhaustive SkyUI MCM menu that has:
  - a **member manager**, with every member individually listed and commandable
  - a **follower manager**, with commands for individuals or even the entire team
  - **settings** where you can customize your experience
  - a **logger** that keeps track of recent notes and any rare errors
- a **display** function, which successively summons each member in a cycle, so you can literally see your members. This means you don't have to remember the names for all your teammates
- **hotkeys** you can set for your favorite commands
- **movable npcs** for when they get in your way, you can literally pick them up and move them where you will

### Future Features May Include:
- a filter to sort through all your members
- more vanilla dialogue spoken by members
- a "Yell" dialogue to command all followers
- a "Banish" command, which sends a member away
- and perhaps more member slots!

## Requires:
- [Skyrim SE 1.5.97+](https://store.steampowered.com/app/489830/The_Elder_Scrolls_V_Skyrim_Special_Edition/)
- [SKSE 2.0.17+](https://skse.silverlock.org/)
- [SkyUI 5.2SE+](https://www.nexusmods.com/skyrimspecialedition/mods/12604)
- [PapyrusUtil 3.8+](https://www.nexusmods.com/skyrimspecialedition/mods/13048)

(Some older versions of the above may work with my mod, but they are not supported.)

## Incompatibilities:
- One of the goals of this mod was to touch as few vanilla assets as possible. The primary assets that have been touched, as of right now, are dialogue topics.
- so there will be some incompatibilities with Relationship Dialogue Overhaul because many "Follow me" dialogues will conflict.
- it's extremely likely that this follower framework will conflict with any other follower framework. It is advised to use only one framework at a time

## Recommended:
- [Mod Organizer 2](https://www.nexusmods.com/skyrimspecialedition/mods/6194) for all your modding needs

## Thank You:
- [Bethesda](https://bethesda.net) for Skryim, which is such an endearing masterpiece.
- [SSEEdit/TesVEdit/xEdit Team](https://github.com/TES5Edit/TES5Edit) for such an amazing [tool](https://www.nexusmods.com/skyrimspecialedition/mods/164).
- [Mod Organizer 2 Team](https://github.com/ModOrganizer2) for your indispensable [program](https://www.nexusmods.com/skyrimspecialedition/mods/6194).
- [SKSE Team](http://skse.silverlock.org/) for their extender, which has extended the life of the game itself.
- [SkyUI Team](https://github.com/schlangster/skyui) for not only the [mod](https://www.nexusmods.com/skyrimspecialedition/mods/12604) and the MCM menu, but also for the fairly good [wiki](https://github.com/schlangster/skyui/wiki/MCM-API-Reference) that goes along with it.
- [PapyrusUtil Team](https://www.nexusmods.com/skyrimspecialedition/mods/13048) for their work and especially their sorting functions, which are wonderfully useful and yet lacking in vanilla Papyrus.
- [Amazing Follower Tweaks](https://www.nexusmods.com/skyrimspecialedition/mods/6656) developers! Your mod is a great inspiration for how a follower framework can be fun and easy to use for the player.
- [My Home is Your Home](https://www.nexusmods.com/skyrimspecialedition/mods/20227) developers for such a wonderful idea, and the methods with which you implement it.
- [Dress Up Lover's NPC Outfit Changer](https://www.nexusmods.com/skyrimspecialedition/mods/28736) developer kuroko137 for inspiring me with your awesome mod to make my own outfit management.
- [Simple NPC Outfit Manager](https://www.nexusmods.com/skyrimspecialedition/mods/15211) developer confusedchim, for showing the basics of how to get outfits to work.
- [joelday](https://github.com/joelday) for [papyrus-lang](https://github.com/joelday/papyrus-lang) and the excellent [guide](https://github.com/joelday/papyrus-lang/wiki/Using-Mod-Organizer-2) on how to use the Creation Kit with Mod Organizer 2.
- [fireundubh](https://github.com/fireundubh) for your parallel papyrus compiler [pyro](https://github.com/fireundubh/pyro) and the [wiki](https://wiki.fireundubh.com/pyro) that goes with it.
- [OldMansBeard](https://forums.nexusmods.com/index.php?/user/3897072-oldmansbeard/) for helping me [reuse vanilla voices](https://forums.nexusmods.com/index.php?/topic/8223653-reusing-voice-files/) without copying and redistributing them.
- [cumbrianlad](https://forums.nexusmods.com/index.php?/user/31338325-cumbrianlad/) for a [discussion on persistent references](https://forums.nexusmods.com/index.php?/topic/8082738-is-512-persistent-actor-references-bad/), and how this can take a toll on the player's gameplay.
- [Creation Kit Wiki](https://www.creationkit.com/index.php?title=Main_Page) for the wealth of knowledge with which this mod was made.
- and every one else who has helped me directly or indirectly, if I have failed to mention you!
