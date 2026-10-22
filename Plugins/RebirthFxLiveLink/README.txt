Rebirth FX Live Link 1.6 - FINAL FANTASY VII REBIRTH effects and materials in the editor, live in the running game

WHAT IT IS
  An editor plugin for the End project (UE 4.26, RebirthEngineV5) and a small UE4SS mod for the game. Together they
  add the Rebirth FX menu to the editor's main menu:

  Effects
    Open Game Effect...       pick one of the game's effects (search by name); its colour and float curves become
                              Curve assets in /Game/RebirthFx/<effect>: gradient view, colour pickers, curve editor
    Recolour Effect...        every colour curve of the open effect to one hue (keeps brightness and saturation)
    Export Effects To Game    every changed effect into one mod, RebirthFx_P, installed in the game's ~mods folder
  Live link (the game running, with the RebirthLiveLink mod)
    Play Effect In Game       the game plays the open effect in front of your character, again every few seconds
    Stop Effect In Game       removes what Play Effect In Game spawned
    Live Edits On/Off         while on, curve changes go to the running game as you make them, and the game plays
                              the effect in front of your character so you see them (also after a game restart:
                              your edits go to it again)
  Materials
    Open Game Material...     one of the game's material instances becomes an editable Material Instance
    Materials On My Character...  the same, picked from what your character wears right now (game running)
    Material Live Edits On/Off, Reset Materials In Game, Export Materials To Game (RebirthMat_P in ~mods)

NEEDS
  Editor: the End project on RebirthEngineV5 (engine build 17c11882-043f-4330-9e21-2efa519533c5). The plugin turns on
  Python Editor Script Plugin and Editor Scripting Utilities. With another engine build the editor offers to rebuild
  the plugin from Source (needs Visual Studio).
  Game: UE4SS 3.0.1 (c0a8d4c) and the RebirthLiveLink mod (ue4ss\Mods\RebirthLiveLink). Live edits of curves and
  materials also need Create a Character System 3.7.9 or newer in the game (its UE4SS mod gives the link memory access
  and an every-frame update); effects still play without it.

FILES
  <End project>\Plugins\RebirthFxLiveLink\          this plugin (Binaries, Source, Content\Python\rebirth_fx_link)
  <game>\End\Binaries\Win64\ue4ss\Mods\RebirthLiveLink\   the game side (Scripts\main.lua, enabled.txt)
  The editor finds the game through Steam (or asks once for its folder); the choice is kept per project.

HOW THE LINK WORKS
  The editor writes a command into ue4ss\Mods\RebirthLiveLink\link\command.lua; the game runs each new one and answers
  in link\status.json (and link\log.txt). Other tools can use link\tool.lua / link\tool_status.json. The game only
  reads commands while it is running (not while it is minimised or in a loading screen).

CREDITS
  Made by Kade with Claude. Uses UE4SS.
