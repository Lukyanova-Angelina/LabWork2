# Architectural Description of the System
### General System Description
This system is a turn-based game implemented in C++. The player controls a character on a 3x3 grid, interacting with various objects: collecting gold and rubies, using weapons and potions, fighting enemies, activating traps, and opening chests.

### Key Characteristics:

- Turn-based game mechanics
- Card damage system with various damage types (physical, fire, ice)
- Map progression system (experience, levels)
- Random content generation (enemies, items, traps)
- Interface with color visualization
### Functionality:
##### Character Control:
- Movement on a 3x3 grid in four directions
- Interaction with objects on adjacent cells
- Using and swapping weapons

##### Combat System:
- Dealing damage to enemies considering the weapon type
- Receiving damage from enemies and traps
- Accounting for elemental damage (fire/ice)

##### Item System:
- Collecting gold and rubies
- Using health potions and poisons
- Opening good and bad chests

###### Progression:
- Gaining experience from victories and collecting resources
- Leveling up with increasing difficulty
- Updating the probability table for object generation

###### Visualization:
- Displaying the game field with color coding
- Displaying player status (health, weapon)

### Usage Scenarios:

###### Resource Gathering:
- Player moves to a cell with gold/ruby
- The system adds resources to the inventory (Status)

###### Fighting an Enemy:
- Player attacks an enemy with a weapon
- The system calculates damage considering the weapon type
- Upon victory, the enemy turns into gold (or a potion), the player gains experience

###### Trap Activation:
- Player steps on a spikes/cannon card
- The system deals damage depending on the trap's direction

###### Using a Potion:
- Player picks up a health/poison potion
- The system increases/decreases health

###### Opening a Chest:
- Player activates a chest
- The system generates a random item
- The chest is replaced with the obtained item
