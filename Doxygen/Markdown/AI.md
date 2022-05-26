# AI

## Naviagation and Pathfinding

The AI uses the A* algorithm with waypoints to navigate through the level and this is handled in the Pathfinding class. 
Firstly, all the walkable tiles are taken in a waypoints and converted into waypoint nodes. 
When the SetPath function is called, the start and end waypoint node is passed in and a vector of nodes is produced with the necessary waypoint nodes to traverse for the path.

## Perception

The AI perception is done using a CanSee and CanHear function.
The CanSee function checks to see if the player position is within the vision range and return true if that is the case.
The CanHear funciton is a lambda function that is called whenever the SoundPlayed event occurs.
It gets all the emitters in range that are playing and return the position of the closest one.
The AI will then investigate this position. 

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

All the enemies inherit from the CAIController class which acts as the base class for the AI behaviour.
This class handles the movement of the enemies and the view semi circle. 
It also handles the interaction with the pathfinding class the holds virtual functions to be overriden in the inheritted classes.
There are 3 types of enemies that inherited from CAIController:
-   AlarmEnemy
-   DogEnemy
-   GruntEnemy

### AlarmEnemy

The AlarmEnemy is an enemy that will alert nearby enemies by playing the bell it is holding to make a sound if it sees the player.
The nearby enemies will then head to the location of the bell sound.
This enemy does not attack the player and is meant to punish the player if they are caught by it.

### DogEnemy

The DogEnemy will attack the player using a dash.
This works by using 2 timers, one for the attack and one for the cooldown.
The dash is emulated by increasing the speed of the dog for a small period of time and the dog will dash in a straight line towards the player.
The indication of when the dog is about to attack is done by slowing the dog drastically for a brief period of time before dashing.

### GruntEnemy

The GruntEnemy holds a weapon and it will use the weapon if it gets within the weapon's range of the player.
This works for both melee and ranged weapons.

## Relating Classes:

-   CAIController
-   Pathfinding
-   State

-   GruntEnemy
-   AlarmEnemy
-   DogEnemy