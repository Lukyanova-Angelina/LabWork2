# Unit Testing with Google Test Framework
### Overview
Unit test suite for game classes using Google Test framework.

### Test Scope
#### Tested Components

##### Core Systems
- Object positioning and movement
- Damage calculation system
- Interaction handling

##### Characters
- Player (with weapon management)
- Enemy, Bat, Elemental, Mag

##### Weapons
- Weapon, ELmagic, ELweapon

##### Items
- Gold, Ruby, Potion, Bomb, Dynamite, Thorn, Gun, Chest

#### Test Categories
  For each component:

1. Constructor Validation - Parameter initialization
2. Getter/Setter Verification - Data integrity checks
3. Method Functionality:
   - Combat actions (takeDamage(), calculateFinalDamage())
   - Interaction handling (OnINTERACT())
4. Edge Cases:
   - Zero/negative values
   - Boundary conditions

### Testing Tools
|     Tool    |      Purpose     |
|-------------|------------------|
| Google Test | Test framework   |
| Makefile    | Build automation |

#### Key Assertions:
- EXPECT_EQ - Value equality
- EXPECT_TRUE/FALSE - Boolean conditions
- EXPECT_NO_THROW - Exception safety

### Test Execution
Build & Run:

    make test
