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
#### Grunt Enemy


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