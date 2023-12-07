<a href="https://www.buymeacoffee.com/mingm"><img height='36' src="https://img.buymeacoffee.com/button-api/?text=Buy me a coffee&emoji=&slug=mingm&button_colour=FF5F5F&font_colour=ffffff&font_family=Comic&outline_colour=000000&coffee_colour=FFDD00"></a>
<a href='https://ko-fi.com/U6U572VOM' target='_blank'><img height='36' src='https://cdn.ko-fi.com/cdn/kofi1.png?v=3' alt='Buy Me a Coffee at ko-fi.com' /></a>
<a href='https://paypal.me/mingmc' target='_blank'><img height='36' src='https://cdn.jsdelivr.net/gh/Nats-ji/Nats-ji@main/paypal.png' alt='Donate me at paypal.com' /></a>

# CP77 Skip Main Menu

## Introduction

>Are you testing your mod?<br>
>Do you feel like waiting for the game to launch is a waste of your time?<br>
>Are you tired of clicking "load game" each time you restart your game?<br>

If so, consider installing this plugin. It will take care of all of those issues for you.

It does so by adding several settings that allow you to skip to the main menu or even load directly into your save.

Preview (Auto Load Last Save is off):

![skip_intro](./img/skip_intro.gif)

## Settings
The three newly added settings can be found under `Settings->Gameplay->Miscellaneous`.

![settings](./img/settings.png)

1. **Auto Load Last Save**<br>
Enable this option will automatically load into your last save game when you launch the game.

2. **Skip Intro Videos**<br>
Enable this option will skip all the logo videos and intro videos when launching the game.

## Fix: Skip Breaching Screen

You may notice that the game stops at the Breaching screen, if you only turn on the skip intro videos.

To fix this you have two options:

1. Install Cybercmd Mod ([nexus](https://www.nexusmods.com/cyberpunk2077/mods/5176), [github](https://github.com/jac3km4/cybercmd)) (Recommended)

   If **CP77 Skip Main Menu** detects the installation of Cybercmd, it will automatically add a config to skip the Breaching screen.
   
   There's nothing else for you to do.

2. Manually add a launch option to the game

   You will need to add `-skipStartScreen` to the launch options in your game.

   Here's the instruction on how to do it on Steam. You'll have to google if you are using Epic or Gog.

   ![launchOptions](./img/cmdline_arg.png)

## Credits
- Thanks to keanuWheeze's [Native Settings](https://github.com/justarandomguyintheinternet/CP77_nativeSettings), I was able to create the setting widgets without doing much if any research.
