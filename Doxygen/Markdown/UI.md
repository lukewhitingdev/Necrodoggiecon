# UI
this project implements a widget system. These are responsbiel for all interactable UI elements. These have been utilised by the Menus.
## Widget classes 
This section will go into detail over the different types of widgets and their uses.

### CWidget
CWidget is the base class of all widgets and contains the parenting, visibility and positional functionality that all widgets require.

### CWidget_Canvas

CWidget_Canvas is the main container for all Widget objects. 
It also contains functionality to correctly instantiate each derivative widget class which will correctly parent them to the Canvas.
Canvas is responsible for updating any children that require updates as unless the canvas is recieving updates, the child widgets should not be updated.

### CWidget_Button
CWidget_Button contains all button functionality, it has the ability to change the visuals on being hovered and clicked or when not interacted with.
It can also bind functions to it's events, these are the following:
- OnButtonPressed
- OnButtonReleased
- OnButtonHoverStart
- OnButtonHoverEnd

### CWidget_Image
Standard Image widget

### CWidget_Text
Standard Text Widget


## Relating Classes:

- CWidget
- CWidget_Canvas
- CWidget_Button
- CWidget_Image
- CWidget_Text
- MainMenu
- PauseMenu
- LevelCompleteMenu
- LevelSelectMenu

