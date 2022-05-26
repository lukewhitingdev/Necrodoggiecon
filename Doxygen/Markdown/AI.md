# AI

## Naviagation and Pathfinding

The AI uses the A* algorithm with waypoints to navigate through the level and this is handled in the Pathfinding class. 
Firstly, all the walkable tiles are taken in a waypoints and converted into waypoint nodes. 
When the SetPath function is called, the start and end waypoint node is passed in and a vector of nodes is produced with the necessary waypoint nodes to traverse for the path.

## Decision Making using a Finite State Machine

The AI uses a Finite State Machine detailed in the State Class.
The FSM is implemented using a base state class and the different states are inheritted.
The different states are:
-   PatrolState
-   ChaseState
-   AttackState
-   InvestigateState
-   SearchState

These are setup so that the state machine can be built for any enemy but can also call the specific functions for each state.
Each state has a enter, update and exit function. The enter and exit functions are called once on first switching to the state and upon switching out of the state.
These functions are used for switching sprite to the relevant look for the state and to setting a pth before traversing this path in the patrol state.
This is the AI State Machine Diagram.

![The Diagram](/Doxygen/Images/AIStateMachineDiagram.png)

## Enemies



## Relating Classes:

-   CAIController
-   Pathfinding
-   State

-   GruntEnemy
-   AlarmEnemy
-   DogEnemy