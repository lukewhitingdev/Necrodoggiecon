# Editor System

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





## Relating Classes:

- CWorld_Edit
- CT_EditorWindows
- CT_EditorGrid
- CT_EditorEntity
- CT_EditorEntity_Enemy