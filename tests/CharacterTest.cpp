/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

#include "TestHelper.h"

TEST(EnemyTest, BasicEnemyCombat) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    Player* player = testAccess.getPlayer();
    gameArray[1] = std::make_unique<Enemy>(1, 25);
    int initialHP = player->getHP();
    
    testAccess.getGame()->handleCOMBAT_DEPENDENT(4, 1);
    
    EXPECT_EQ(player->getHP(), initialHP - 25);
    EXPECT_EQ(gameArray[1]->returntype(), ObjectType::PLAYER);
}

TEST(BatTest, BatTurnsToPotionOnDeath) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    Player* player = testAccess.getPlayer();
    
    gameArray[1] = std::make_unique<Object>(1);
    game.handleInput('w');
    
    gameArray[4] = std::make_unique<Bat>(4, 5);
    gameArray[4]->setOnDamageCallback([&game](int pos, DamageType type) {
        game.handleObjectDamage(pos, type);
    });
    
    auto weapon = std::make_unique<Weapon>(5, 10);
    player->setWeapon(std::move(weapon));
    
    testAccess.getGame()->handleCOMBAT_DEPENDENT(1, 4);
    
    EXPECT_EQ(gameArray[4]->returntype(), ObjectType::POTION);
    
    Potion* potion = dynamic_cast<Potion*>(gameArray[4].get());
    EXPECT_EQ(potion->getPotionType(), PotionType::HEAL);
}

TEST(MagTest, MagRegeneration) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    gameArray[4] = std::make_unique<Mag>(4, 4);
    
    Mag* mag = dynamic_cast<Mag*>(gameArray[4].get());
    int initialHP = mag->getHP();
    
    for (int i = 1; i <= 10 ; i++) {
        mag->update();
        EXPECT_EQ(mag->getHP(), std::min(mag->getMaxHP(), initialHP + i));
    }
}
TEST(CriticalEdgeCases, CharacterTakeDamageWithWeapon) {
    Player player(4, "Hero", 100, 150);
    auto weapon = std::make_unique<Weapon>(2, 30);
    Weapon* weaponPtr = weapon.get();
    
    player.takeDamage(weaponPtr);
    EXPECT_LT(player.getHP(), 100);
}