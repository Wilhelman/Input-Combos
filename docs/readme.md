
## **Our project** 

Project for Videogame Development subject. The main goal here is to create a simple plattaformer with two levels done in Tiled, having a main character moving around while being able to save and load game’s state. On top of this enemies pathfinding is implemented along other stuff such as stable frame rate (30fps), normalized movement, structured entity system described in an UML file and code with Brofiler integration. We also have added an intro menu and HUD implemented through a strucured ui system described in a UML file. 

This project has been done by two catalan students of CITM - UPC (Terrasa, Spain).

## **About the game**

Simple platformer with a temple-type theme featuring a yellow character. Equipped with a gun, he will have to reach the end of the level avoiding obstacles and killing enemies.

## **Our Team**

![](team_photo.jpg)

_García Subirana, Guillermo's responsability and Github account_

* In charge of all code related to IA, pathfinding, preservation of changes, interaction between modules and other parts of code.
* [Github account](https://github.com/Wilhelman)

_Masó Garcia, Víctor's responsability and Github account_

* Management of all tasks / team organization. In charge of sprites and audio and some modules of code. 
* [Github account](https://github.com/nintervik)

## **Main core subsystems of the game**

Our game code is structured in modules. The main module (called j1App.cpp) manages all the other modules calling in a loop its respective awake, preupdate, update, postupdte, cleanup that they share thorugh a base class j1Module. Down below a basic scheme of this (some modules are missing) shows what has been explained:

![](code_scheme.JPG)

For a better organization and performance a entity factory system has been implemented along with an UI module that manages all the events that happen in UI and it's independent to everything else.

Animations, file paths, and levels are read and loaded through parsing xml files to avoid 'magic numbers', improve readability and boost changes when testing. 

### Innovations
* Player and enemy animations are read from an xml file.
* Spawn enemy points are created with Tiled and read from the tmx file of the map.
* Pause menu implemented.
* You can change game language (dictionary read from an xml file) in settings: available in english, spanish, catalan... and even klingon if you don't belong to our planet!

## **Tools used**
* IDE: Microsoft Visual Studio 2017
* Language: C++
* Graphics and audio: SDL 2.0
* Data: pugixml 1.8
* Level editor: Tiled 0.17
* Profiler: Brofiler
* Code repository: GitHub
* Others: Adobe Photoshop CS6, MS Paint and Aseprite


## **Gameplay**
___
<iframe width="1280" height="720" src="https://www.youtube.com/embed/isoApESpyFE" frameborder="0" gesture="media" allow="encrypted-media" allowfullscreen></iframe>

___
## **Installation instructions**

Download the zip file and unzip it. Open the folder, execute the .exe and enjoy!

_IMPORTANT: do not modify, change or add any folder or file as you might not be able to execute the game._
___

## **How to play**

The game is quite simple. You must reach the end of each level (there are two) collecting all the coins you can while killing enemies and avoiding obstacles. You start with three lives but every time you collect 10 coins you earn an extra life (up to 6). you can can consult game controls down below. Have fun!

### Controls
~~~~~~~~~~~~~~~

Player controls:
- JUMP: W key (twice for double jump)
- LEFT: A key
- RIGHT: D key
- SHOOT: SPACE key (hold for continuous shooting)

General/developer controls:
- PAUSE GAME: ESC key
- EXIT CREDITS: ESC key
- SKIP INTRO TITLE: SPACE key
- SKIP CREDITS: hold SPACE key
- START FROM THE VERY FIRST LEVEL: F1 key
- START FROM THE BEGGINING OF THE CURRENT LEVEL: F2 key
- SHOW COLLIDERS: F3
- GOD_MODE (NO FLYING) = F4
- SAVE GAME (player position and current level):  F5 key
- LOAD GAME (player position and level saved): F6 key
- UI DEBUG MODE: F8
- GOD MODE (FLYING): F10
- CAP FRAMERATE: F11

~~~~~~~~~~~~~~~


## **Credits for artwork, music/sound fx and fonts**

### *Sprites*:

* Artwork created by Luis Zuno (@ansimuz). Sprites can be found [here](https://ansimuz.itch.io/grotto-escape-game-art-pack)
* Artwork created by [Henry Sofware](https://henrysoftware.itch.io/). Sprites can be found [here](https://henrysoftware.itch.io/free-pixel-mob)
* UI artwork created by [Kenny](http://www.kenney.nl/). Sprites can be found [here](https://opengameart.org/content/ui-pack-rpg-extension)

### *Tilesets*:

* Artwork created by Luis Zuno (@ansimuz). Tileset can be found [here](https://ansimuz.itch.io/grotto-escape-ii-art-pack-)

### *Music*:

* Game music from [DL SOUNDS](https://www.dl-sounds.com/). It can be found [here](https://www.dl-sounds.com/royalty-free/arcade-funk/)
* Main menu music from [DL SOUNDS](https://www.dl-sounds.com/). It can be found [here](https://www.dl-sounds.com/royalty-free/8-bit-detective/)

### *Sound FX*:

* Player shot and jump sound fx can be found [here](https://ansimuz.itch.io/grotto-escape-game-art-pack)
* This game uses these sounds from freesound:
      
	- 249616__vincentm400__function-fail.wav by [OwlStorm / Natalie Kirk](https://freesound.org/people/OwlStorm/)
	- 341695__projectsu012__coins-1.wav by  [ProjectsU012](https://freesound.org/people/ProjectsU012/)
	- 345299__scrampunk__okay [Scrampunk](https://freesound.org/people/Scrampunk/)
	
### *Fonts*:
* Font used can be found [here](http://tenbytwenty.com/?xxxx_posts=munro) 

___

> ### *Download the last version of the game [HERE](https://github.com/Wilhelman/Temple-Escape/releases/tag/v1.0)*
> ### *Check our Github repository [HERE](https://github.com/Wilhelman/Temple-Escape)*

***
***

## **License**

~~~~~~~~~~~~~~~

MIT License

Copyright (c) 2017 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

~~~~~~~~~~~~~~~
