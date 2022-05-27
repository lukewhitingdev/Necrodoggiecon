# World
The world classes are responsible for containing all of the level infomation. It also handles the loading and saving (Depending on the World Class)
## WorldManager
The worlds are accessed through the CWorldManager static class. This allows you to access the currently loaded level as well as handles the bulk of loading and unloading the levels.
This is further assisted by the TransitionHelepr that makes sure that the level is instantiated after the previous level is unloaded.

## Classes

### CWorld
CWorld is the base class that all worlds inherit from. This contains alot of the base functionality such as loading a level and saving.
#### Navigation
CWorld contains the AI's navigation grid and is generated at the start of the level.

### CWorld_Edit
This class is responsible for the Editor's backend operations and contains much of the core functionality in regards to editing the tilesets and containing data.
This class also has an extended save system, used to save all assets to the JSON file for the game to load.

### CWorld_Game
This class is one of the extended CWorld class used by the game. this handles loading of all assets the game requires as due to the project's structure, the engine cannot access the game's assets. This is one of the primary ways the engine can be extended.

### CWorld_Menu

Similar to CWorld_Game, this class is the other extended CWorld class.
CWorld_Menu forgoes loading of a tileset and simply instantiates the menu required.

## Relating Classes:

- CWorld
- CWorld_Edit
- CWorld_Game
- CWorld_Menu
- CWorldManager
- TransitionHelper