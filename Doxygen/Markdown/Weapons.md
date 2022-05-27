# Weapon System

## Strategy Design Pattern

The weapons system uses the Strategy Design Pattern to have a context interface that allows for multiple different strategies to be interchanged with their own unique logic.
Firstly, the entities in the game (players and enemies) are given an instance of the context interface, this interface holds an instance of the base strategy.
When a player or enemy changes their weapon, the strategy instance changes the pointer to the strategy it is using, for example, from Dagger to Crossbow. 
This Design Pattern is great for a weapon system as it allows for weapons to be interchanged easily by only passing in the weapon pointer of the specific weapon and not having to have multiple objects created in memory for all weapons in the game.

## Why does this Design Pattern work

The Strategy Design Pattern works because all the strategies that are being interchanged all inherit from the same base class (Weapon in this case).
This means that all the subclasses of weapons that derive from the Weapon class and are strategies in the design pattern are all Weapon pointers at their base level because they have all inherited from Weapon at the base level of their inheritance tree.
Each strategy in the design pattern is its own subclass, all with its own unique logic that is used depending on the strategy that is currently being used in the context interface.
This is a basic relationship diagram of the weapon system implemented in the game.

![The Diagram](/Doxygen/Images/WeaponsStrategyDiagram.png)

## Weapons

The game has multiple different attack styles, Melee and Range weapons.
All Melee and Range weapons have base variants which the subclasses inherit from. 
These base classes have the shared logic through all the weapons of its kind, an example of this is the basic projectile spawning for ranged weapons. 
This is then overridden through the unique logic in the individual weapon.

### Melee Weapons

There are 3 melee weapons in the game:
-   Dagger
-   Rapier
-   Longsword

The melee weapons in the game use a system of calculating the damage position based on the direction of the attack and the range of the weapon. 
This damage position is then used to get the enemy that is in range of the player and the damage position, and then discarding the all enemies until the closest enemy in range is returned.
All the melee weapons use this method, dynamically calculating the damage position based on the different ranges of the weapons.

The Longsword has unique logic that creates an area-of-effect (AOE) attack using the same method that is used for the other melee weapons.
However, all entities that are within the range of weapons from the player AND within the range of the weapon from the damage position are damaged. 
This radius style range from 2 points creates a cone shape in the looking direction.

### Range Weapons
There are 3 range weapons in the game:
-   Crossbow
-   Fireball
-   Magic Missile (Homing)

The range weapons in the game use a Projectile class to spawn a CEntity into the world with a given direction, speed, position and sprite. 
These parameters are then used to constantly update the entity on a constant velocity.
The projectile also uses the same method of checking for closest entity in a given range around the projectile, this makes a sort of bounding area and if any entity is returned, then damage logic is applied to said entity.

The Magic Missile has unique logic that creates a Homing Projectile entity into the world.
This projectile creates a directional vector to the closest entity is finds in a given range, and then travels along that new direction vector towards the target.

## Relating Classes:

-   WeaponInterface
-   Weapon
-   MeleeWeapon
-   RangeWeapon
-   Dagger
-   Rapier
-   Longsword
-   Crossbow
-   MagicMissile
-   Fireball
-   Projectile
-   HomingProjectile