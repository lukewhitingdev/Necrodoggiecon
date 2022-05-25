# AI

## Naviagation and Pathfinding

The AI uses the A* algorithm with waypoints to navigate through the level and this is handled in the Pathfinding class. 
Firstly, all the walkable tiles are taken in a waypoints and converted into waypoint nodes. 
When the SetPath function is called, the start and end waypoint node is passed in and a vector of nodes is produced with the necessary waypoint nodes to traverse for the path.

## Decision Making using a Finite State Machine

The AI uses a Finite State Machine detailed in the State Class.
The FSM is implemented using a base state class and 
This is the AI State Machine Diagram.

![The Diagram](/Doxygen/Images/AIStateMachineDiagram.png)

## Relating Classes:

-   CAIController
-   Pathfinding
-   State

-   GruntEnemy
-   AlarmEnemy
-   DogEnemy