# Usage Scenarios


### Scenario 1: Basic Gameplay Loop

- Start Game: System initializes 3x3 grid with player at center

- Move Player: Use WASD keys to move toward objects

- Collect Items: Automatic collection of weapons/gold

- Combat Enemies: Automatic resolution based on equipped weapon

- Progress: Gain XP from interactions


### Scenario 2: Combat System

- Weapon Check: System checks player's equipped weapon

#### Damage Calculation:

- No weapon: Player takes enemy's HP as damage

- With weapon: Enemy takes weapon damage, weapon loses durability

- Elemental Interactions: Additional calculations for elemental types

- Resolution: Enemy defeated or weapon broken


### Scenario 3: Trap Interaction

- Encounter Trap: Move into thorn/gun trap (immediate-pass)

- Direction Check: System checks if trap faces player direction

- Damage Application: Player takes damage if in active direction

- Trap Rotation: Trap directions rotate for next interaction


### Scenario 4: Chest Opening

- Move on Chest: Player open chest (trigger-on-stay)

- Content Generation: System generates loot based on chest type

- Replacement: Chest replaced with generated loot object

- Collection: Player can collect the generated item


### Acceptance Criteria
####Functional Requirements

- Game initializes with player at center position

- All object types generate with correct properties

- Movement respects grid boundaries

- Interactions resolve according to object types

- Damage calculations apply correct modifiers

- Economy system tracks gold and XP accurately

- Visual rendering uses different colors and symbols

#### Non-Functional Requirements

 - Response time < 1000ms for all actions

- No memory leaks after extended play

- Clear visual feedback for all actions

#### Edge Cases

- Handling invalid positions (-1, 9+)

- Zero-damage weapons and objects

- Maximum health overflow prevention

- Empty grid position handling

- Concurrent callback execution

### Classes description

**Object**: Base class for all game entities. Stores position, movement, and damage callbacks.

**Character**: Base class for characters with health management. All characters inherit from this.

**Player**: Playable character with weapon equipment system. Can collect weapon and fight enemies.

**Enemy**: Base enemy class. All enemy types inherit from this with combat-dependent interaction.

**Bat**: Basic enemy. Drops potion upon death.

**Elemental**: Enemy with elemental affinity. Takes double damage from opposite element, gets healed by same element.

**Mag**: Mage enemy that regenerates 1 HP per turn up to maximum health.

**Weapon**: Base weapon class. Has damage that decreases when used.

**ELmagic**: Magic wand with elemental damage. Deals damage to tile behind enemy.

**ELweapon**: Elemental weapon. Can be charged by same element.

**Gold**: Collectible currency. Can be damaged and destroyed.

**Ruby**: Premium currency. Gives double gold and bonus XP when collected.

**Potion**: Consumable item. Can be healing (restores HP) or poison (damages player).

**Bomb**: Timed explosive. Damages adjacent tiles after countdown.

**Dynamite**: Powerful explosive. Damages entire row when activated.

**Thorn**: Rotating trap. deals damage to the player if the spike is directed at him.

**Gun**: Rotating trap. Damages in specific directions that change each turn.

**Chest**: Loot container. Can be good (helpful items) or bad (harmful items).

**Game**: Main controller. Manages 3x3 grid, player input, and game state.

**Status**: Progression system. Handles XP, levels, gold, and loot table generation.

