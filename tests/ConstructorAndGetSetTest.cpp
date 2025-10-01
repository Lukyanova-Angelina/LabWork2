/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

#include "TestHelper.h"
#include <climits>


TEST(CharacterTest, ConstructorAndGetters) {
    Character character(4, "TestHero", 150, 200);
    
    EXPECT_EQ(character.getPosition(), 4);
    EXPECT_EQ(character.getName(), "TestHero");
    EXPECT_EQ(character.getHP(), 150);
    EXPECT_EQ(character.getMaxHP(), 200);
}

TEST(CharacterTest, SetterMethods) {
    Character character(0, "Initial", 100, 150);
    
    character.setName("UpdatedName");
    character.setHP(120);
    character.setMaxHP(180);
    
    EXPECT_EQ(character.getName(), "UpdatedName");
    EXPECT_EQ(character.getHP(), 120);
    EXPECT_EQ(character.getMaxHP(), 180);
}

TEST(PlayerTest, ConstructorAndWeaponManagement) {
    Player player(4, "Hero", 100, 150);
    
    EXPECT_EQ(player.getPosition(), 4);
    EXPECT_EQ(player.getName(), "Hero");
    EXPECT_EQ(player.getHP(), 100);
    EXPECT_EQ(player.getMaxHP(), 150);
    EXPECT_EQ(player.getWeapon(), nullptr);
}

TEST(PlayerTest, WeaponAssignment) {
    Player player(4, "Hero", 100, 150);
    
    auto weapon = std::make_unique<Weapon>(2, 25);
    Weapon* weaponPtr = weapon.get();
    player.setWeapon(std::move(weapon));
    
    EXPECT_EQ(player.getWeapon(), weaponPtr);
    EXPECT_NE(player.getWeapon(), nullptr);
    
    player.removeWeapon();
    EXPECT_EQ(player.getWeapon(), nullptr);
}
TEST(EnemyTest, Constructors) {
    Enemy enemy1(3, "Goblin", 50, 75);
    EXPECT_EQ(enemy1.getPosition(), 3);
    EXPECT_EQ(enemy1.getName(), "Goblin");
    EXPECT_EQ(enemy1.getHP(), 50);
    
    Enemy enemy2(5, 80);
    EXPECT_EQ(enemy2.getPosition(), 5);
    EXPECT_EQ(enemy2.getHP(), 80);
    EXPECT_GE(enemy2.getMaxHP(), 80);
}

TEST(BatTest, Constructors) {
    Bat bat1(4, 25);
    EXPECT_EQ(bat1.getPosition(), 4);
    EXPECT_EQ(bat1.getHP(), 25);
    
    Bat bat2(3);
    EXPECT_EQ(bat2.getPosition(), 3);
    EXPECT_GE(bat2.getHP(), 10);
    EXPECT_LE(bat2.getHP(), 19);
}
TEST(ElementalTest, ConstructorAndElement) {
    Elemental fireElemental(4, 60, DamageType::FIRE);
    EXPECT_EQ(fireElemental.getPosition(), 4);
    EXPECT_EQ(fireElemental.getHP(), 60);
    EXPECT_EQ(fireElemental.getElement(), DamageType::FIRE);
    
    Elemental iceElemental(5, 70, DamageType::ICE);
    EXPECT_EQ(iceElemental.getElement(), DamageType::ICE);
}

TEST(MagTest, Constructors) {
    Mag mag1(4, 30);
    EXPECT_EQ(mag1.getPosition(), 4);
    EXPECT_EQ(mag1.getHP(), 30);
    
    Mag mag2(3);
    EXPECT_EQ(mag2.getPosition(), 3);
    EXPECT_EQ(mag2.getHP(), 10);
}
TEST(WeaponTest, Constructors) {
    Weapon weapon1(2); // Random damage
    EXPECT_EQ(weapon1.getPosition(), 2);
    EXPECT_GE(weapon1.getDamage(), 0);
    EXPECT_LE(weapon1.getDamage(), 41);
    
    Weapon weapon2(3, 45);
    EXPECT_EQ(weapon2.getPosition(), 3);
    EXPECT_EQ(weapon2.getDamage(), 45);
}

TEST(WeaponTest, DamageManagement) {
    Weapon weapon(4, 30);
    
    weapon.setDamage(50);
    EXPECT_EQ(weapon.getDamage(), 50);
    
    weapon.takeDamage(10, DamageType::NORMAL);
    EXPECT_EQ(weapon.getDamage(), 40);
}

TEST(ELmagicTest, ConstructorsAndElement) {
    ELmagic magic1(4, DamageType::FIRE);
    EXPECT_EQ(magic1.getPosition(), 4);
    EXPECT_EQ(magic1.getElement(), DamageType::FIRE);
    
    ELmagic magic2(5, 35, DamageType::ICE);
    EXPECT_EQ(magic2.getPosition(), 5);
    EXPECT_EQ(magic2.getDamage(), 35);
    EXPECT_EQ(magic2.getElement(), DamageType::ICE);
}

TEST(ELweaponTest, ConstructorsAndElement) {
    ELweapon elweapon1(4, DamageType::FIRE);
    EXPECT_EQ(elweapon1.getPosition(), 4);
    EXPECT_EQ(elweapon1.getElement(), DamageType::FIRE);
    
    ELweapon elweapon2(5, 40, DamageType::ICE);
    EXPECT_EQ(elweapon2.getPosition(), 5);
    EXPECT_EQ(elweapon2.getDamage(), 40);
    EXPECT_EQ(elweapon2.getElement(), DamageType::ICE);
}
TEST(GoldTest, ConstructorAndAmountManagement) {
    Gold gold(4, 100);
    
    EXPECT_EQ(gold.getPosition(), 4);
    EXPECT_EQ(gold.getAmount(), 100);
    
    gold.setAmount(150);
    EXPECT_EQ(gold.getAmount(), 150);
    
    gold.takeAmount(30);
    EXPECT_EQ(gold.getAmount(), 120);
    
    gold.takeDamage(20, DamageType::NORMAL);
    EXPECT_EQ(gold.getAmount(), 100);
}
TEST(RubyTest, Constructor) {
    Ruby ruby(3, 50);
    
    EXPECT_EQ(ruby.getPosition(), 3);
    EXPECT_EQ(ruby.getAmount(), 50);
}
TEST(PotionTest, ConstructorsAndTypes) {
    Potion healPotion1(4, PotionType::HEAL);
    EXPECT_EQ(healPotion1.getPosition(), 4);
    EXPECT_EQ(healPotion1.getPotionType(), PotionType::HEAL);
    EXPECT_GE(healPotion1.getPower(), 20);
    EXPECT_LE(healPotion1.getPower(), 50);
    
    Potion poisonPotion(5, 25, PotionType::POISON);
    EXPECT_EQ(poisonPotion.getPosition(), 5);
    EXPECT_EQ(poisonPotion.getPotionType(), PotionType::POISON);
    EXPECT_EQ(poisonPotion.getPower(), 25);
}

TEST(PotionTest, PowerManagement) {
    Potion potion(4, 30, PotionType::HEAL);
    
    potion.setPower(40);
    EXPECT_EQ(potion.getPower(), 40);
    
    potion.setPotionType(PotionType::POISON);
    EXPECT_EQ(potion.getPotionType(), PotionType::POISON);
    
    potion.takeDamage(15, DamageType::NORMAL);
    EXPECT_EQ(potion.getPower(), 25);
}
TEST(BombTest, ConstructorAndProperties) {
    Bomb bomb(4, 20);
    
    EXPECT_EQ(bomb.getPosition(), 4);
    EXPECT_EQ(bomb.getAmount(), 20);
    EXPECT_EQ(bomb.getDuration(), 5);
}

TEST(BombTest, DurationAndAmountManagement) {
    Bomb bomb(4, 25);
    
    bomb.setAmount(30);
    EXPECT_EQ(bomb.getAmount(), 30);
    
    bomb.setDuration(3);
    EXPECT_EQ(bomb.getDuration(), 3);
    
    bomb.update(); // Countdown
    EXPECT_EQ(bomb.getDuration(), 2);
    
    bomb.takeDamage(10, DamageType::NORMAL);
    EXPECT_EQ(bomb.getAmount(), 20);
}
TEST(DynamiteTest, Constructor) {
    Dynamite dynamite(3, 15);
    
    EXPECT_EQ(dynamite.getPosition(), 3);
    EXPECT_EQ(dynamite.getAmount(), 15);
    EXPECT_EQ(dynamite.getDuration(), 5);
}
TEST(ThornTest, ConstructorAndDirections) {
    std::array<bool, 4> directions = {true, false, true, false};
    Thorn thorn(4, 15, directions);
    
    EXPECT_EQ(thorn.getPosition(), 4);
    EXPECT_EQ(thorn.getAmount(), 15);
    
    auto retrievedDirs = thorn.getDirections();
    EXPECT_EQ(retrievedDirs[0], true);
    EXPECT_EQ(retrievedDirs[1], false);
    EXPECT_EQ(retrievedDirs[2], true);
    EXPECT_EQ(retrievedDirs[3], false);
}

TEST(ThornTest, AmountManagementAndRotation) {
    std::array<bool, 4> directions = {true, false, false, true};
    Thorn thorn(4, 20, directions);
    
    thorn.setAmount(25);
    EXPECT_EQ(thorn.getAmount(), 25);
    
    thorn.update();
    auto newDirs = thorn.getDirections();
    EXPECT_EQ(newDirs[0], directions[3]);
    EXPECT_EQ(newDirs[1], directions[0]);
    EXPECT_EQ(newDirs[2], directions[1]);
    EXPECT_EQ(newDirs[3], directions[2]);
}

TEST(GunTest, Constructor) {
    std::array<bool, 4> directions = {false, true, false, true};
    Gun gun(4, 18, directions);
    
    EXPECT_EQ(gun.getPosition(), 4);
    EXPECT_EQ(gun.getAmount(), 18);
    
    auto retrievedDirs = gun.getDirections();
    EXPECT_EQ(retrievedDirs[1], true);
    EXPECT_EQ(retrievedDirs[3], true);
}

TEST(ChestTest, ConstructorAndType) {
    Chest goodChest(4, ChestType::GOODCHEST);
    EXPECT_EQ(goodChest.getPosition(), 4);
    EXPECT_EQ(goodChest.getChestType(), ChestType::GOODCHEST);
    
    Chest badChest(5, ChestType::BADCHEST);
    EXPECT_EQ(badChest.getChestType(), ChestType::BADCHEST);
}

TEST(ObjectTest, ConstructorAndPosition) {
    Object obj(7);
    EXPECT_EQ(obj.getPosition(), 7);
    
    obj.setPosition(3);
    EXPECT_EQ(obj.getPosition(), 3);
}

TEST(StatusTest, ConstructorAndInitialValues) {
    Status status;
    
    EXPECT_EQ(status.getSteps(), 0);
    EXPECT_EQ(status.getLevel(), 1);
    EXPECT_EQ(status.getGold(), 0);
    EXPECT_EQ(status.getXp(), 0);
    EXPECT_EQ(status.getXpToNextLevel(), 500);
}

TEST(StatusTest, ResourceManagement) {
    Status status;
    
    status.addGold(100);
    EXPECT_EQ(status.getGold(), 100);
    
    status.takeGold(30);
    EXPECT_EQ(status.getGold(), 70);
    
    status.addXp(200);
    EXPECT_EQ(status.getXp(), 200);
    
    status.StepsUp();
    EXPECT_EQ(status.getSteps(), 1);
}

TEST(EdgeCaseTest, ZeroAndNegativeDamage) {
    Player player(4, "Hero", 100, 150);
    player.takeDamage(0, DamageType::NORMAL);
    EXPECT_EQ(player.getHP(), 100);
    
    player.takeDamage(-10, DamageType::NORMAL);
    EXPECT_GE(player.getHP(), 90);
}

TEST(EdgeCaseTest, OverflowValues) {
    Status status;
    status.addGold(INT_MAX);
    status.addXp(INT_MAX);
    EXPECT_GE(status.getGold(), 0);
    EXPECT_GE(status.getXp(), 0);
}

TEST(MethodTest, ObjectCloneMethod) {
    Weapon original(4, 25);
    auto clone = original.clone();
    
    Weapon* weaponClone = dynamic_cast<Weapon*>(clone.get());
    ASSERT_NE(weaponClone, nullptr);
    
    EXPECT_EQ(weaponClone->getDamage(), 25);
    EXPECT_EQ(weaponClone->getPosition(), 4);
}

TEST(MethodTest, LootTableGeneration) {
    Status status;
    status.setLevel(5);
    
    for (int i = 0; i < 50; i++) {
        auto obj = status.generateCard(4);
        EXPECT_NE(obj, nullptr);
        EXPECT_EQ(obj->getPosition(), 4);
    }
}

TEST(EdgeCaseTest, ZeroValueWeapons) {
    Weapon weapon(4, 0);
    EXPECT_EQ(weapon.getDamage(), 0);
    
    weapon.takeDamage(5, DamageType::NORMAL);
    EXPECT_EQ(weapon.getDamage(), 0);
}
TEST(MethodTest, StatusStepsIncrement) {
    Status status;
    int initialSteps = status.getSteps();
    status.StepsUp();
    EXPECT_EQ(status.getSteps(), initialSteps + 1);
}

TEST(MethodTest, ObjectMovementExecution) {
    Object obj(4);
    obj.move(0);
    EXPECT_EQ(obj.getPosition(), 1);
    
    obj.move(1);
    EXPECT_EQ(obj.getPosition(), 2);
}
TEST(GameStateTest, FullLevelProgression) {
    Status status;
    int targetLevel = 3;
    
    while (status.getLevel() < targetLevel) {
        status.addXp(status.getXpToNextLevel() + 100);
    }
    
    EXPECT_EQ(status.getLevel(), targetLevel);
}

TEST(BoundaryConditions, ObjectMovementBoundaries) {
    std::vector<int> boundaryPositions = {0, 2, 6, 8};
    
    for (int pos : boundaryPositions) {
        Object obj(pos);
        
        for (int dir = 0; dir < 4; dir++) {
            bool canMove = obj.possibletomove(dir);
            int targetPos = obj.getTargetPosition(dir);
            
            if (canMove) {
                EXPECT_GE(targetPos, 0);
                EXPECT_LE(targetPos, 8);
            } else {
                EXPECT_EQ(targetPos, -1);
            }
        }
    }
}