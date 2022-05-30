# Necrodoggiecon

# How the project works
The engine holds all the intrinsic components and the other outer projects can create classes that inherit these components and then the class can be used to create the game ontop of the engine.

# Specific Areas I Worked on:
#### Audio - See [Audio](Doxygen/Markdown/Audio.md) <br>
#### Utility - See [Utility](Doxygen/Markdown/Utility.md) <br>
#### AssetManagement - See [AssetManagement](Doxygen/Markdown/AssetManagement.md) <br>
#### Event System - See [Event System](https://github.com/lukewhitingdev/Necrodoggiecon/blob/57046ed2e0a56e2bc1db4d80ddb107e72a69795f/Cerberus/Core/Utility/EventSystem/EventSystem.h) <br>
#### Debug + Error Logging - See [Debug](https://github.com/lukewhitingdev/Necrodoggiecon/blob/57046ed2e0a56e2bc1db4d80ddb107e72a69795f/Cerberus/Core/Utility/DebugOutput/Debug.h) <br>
#### Camera Manager - See [Camera Manager](https://github.com/lukewhitingdev/Necrodoggiecon/blob/57046ed2e0a56e2bc1db4d80ddb107e72a69795f/Cerberus/Core/Utility/CameraManager/CameraManager.h) <br>
#### IO Utility - See [IO](https://github.com/lukewhitingdev/Necrodoggiecon/blob/57046ed2e0a56e2bc1db4d80ddb107e72a69795f/Cerberus/Core/Utility/IO.h) <br>



I also worked on Build scripts and general build improvements like de-coupling the game and engine by compiling the engine into a static library and also creating post-build scripts within visual studio which copies resources from project to project to allow for easy coherence across all the projects built ontop of the engine and game.
<br>
#### See [Game project settings](https://github.com/lukewhitingdev/Necrodoggiecon/blob/main/Necrodoggiecon/Necrodoggiecon.vcxproj) <br>
#### See [Engine project settings](https://github.com/lukewhitingdev/Necrodoggiecon/blob/main/Cerberus/CerberusEngine.vcxproj) <br>
For a easier time looking at the Build Steps etc, I recommend opening the project in Visual Studio.

Furthermore, I also helped create the engine architecture and helped other developers on this project improve areas of their code through code review which the whole team conducted on other team members pull requests.

# Instructions

## How to compile the Engine
Open the CerberusEngine project in Visual Studio.
Right click on the project and click build.
Do not debug the engine, just build it. 

## How to compile the Game
Firstly, compile the engine.
Open the Necrodoggicon project in Visual Studio.
Right click on the project and set as startup project.
Set to release mode and press F5 to run the game.

## How to play the Game
### Controls:
-   WASD - Movement
-   Left click - Fire weapon
-   F - Interact

## Naming Convention

### Variables:
varNameHere.

### Functions:
FunctionNameHere.

### Enums, Defines:
ANGRYENUMS

## Links to the aspects of the Engine/Game

-   [AI](Doxygen/Markdown/AI.md)
-   [AssetManagement](Doxygen/Markdown/AssetManagement.md)
-   [Audio](Doxygen/Markdown/Audio.md)
-   [Editor](Doxygen/Markdown/Editor.md)
-   [UI](Doxygen/Markdown/UI.md)
-   [Utility](Doxygen/Markdown/Utility.md)
-   [Weapons](Doxygen/Markdown/Weapons.md)
-   [World](Doxygen/Markdown/World.md)


