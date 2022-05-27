# Editor System
## Keybinds
- W (Enables movement of Entities)
- C (Clears current operation type)
- DELETE (Deletes inspected entity)

## ImGui

The editor implements ImGui as the primary user interface. There are 3 panels that are instantiated and they provide the designer with the required controls and infomation.
Panels: 
- Editor Window
- Content
- Details

Editor window contains the bulk of the editor controls, providing methods to edit the tile map, change level and save. 
The Content panel provides the player with the ability to place entities into the scene. These are the weapon holder and enemy characters.
The Details panel will provde the desiger with infomation pertaining to any entity that gets inspected. Each entity has unique data that can be edited or displayed.

## Detail Panels
### Enemy Characters
All Enemy characters share the ability to place Waypoints and to toggle their visibility. 
Furthermore all Enemy characters can have their stat tweaked induvisually but load the default values when created.
The section bellow will highlight the unique elements inside a character's properties.
#### Grunt Enemy
-Ability to set a weapon.

# Content Panel 
## Gameplay Controllers
### Player Start
Defines the location the player will start in each level. This is an entity that is always added to the scene but this is here as a backup.

### Weapon Holder
The weapon holder will allow you to add a weapon pickup to the scene. These ca be customized in the details panel.

## Enemy Units
Enemy units section, this contains all AI that can be added to a scene.
- Grunt
- Dog
- Alarm
## Editor Window
This panel contains all grid operations that are available
### Grid Manipulation
The grid manipulators; these are used to edit the tile-map.
- Add Walkable (Box)
- Add Wall (Box)
- Add Walkable (Single)
- Add Wall (Single) 
### Debug
#### ToggleDebug
using this will toggle the debug display, switching between the gameplay visuals and a black and white version that clearly ilustrates the walkable and unwalkable spaces.

### Utility
#### Clear Grid
Clears all tiles from the grid.

### Levels
In this section you can define which level to save to and which level to load.

## Editor Entities
### Enemy Entitiy
Enemy entity is the base class of the enemy entities and contains all of the stats and weapons that the AI can be provided with. Additional entities are defined through slots which changes which data is loaded at runtime.

### Player Start
This entity defines where the player will start in the scene.

### Waypoints
Waypoints are used by Enemy entities to define their patrol routes.

#### Weapon Holders
These are used to place weapon pickups and scrolls through out the levels. You can set which item the pickup will spawn with in the inspector.




## Relating Classes:

- CWorld_Edit
- CT_EditorWindows
- CT_EditorGrid
- CT_EditorEntity
- CT_EditorEntity_Enemy
- CT_EditorEntity_Waypoint
- CT_EditorEntity_PlayerStart
- CT_EditorEntity_WeaponHolder
- CT_EditorMain
- CT_GridCursor
- 