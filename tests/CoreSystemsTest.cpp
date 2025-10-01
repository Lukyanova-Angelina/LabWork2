/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

#include "TestHelper.h"

TEST(StatusTest, ExperienceAndLevelProgression) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& status = testAccess.getStatus();
    
    int initialXP = status.getXp();
    int initialLevel = status.getLevel();
    
    status.addXp(50);
    EXPECT_EQ(status.getXp(), initialXP + 50);
    
    status.addXp(status.getXpToNextLevel());
    EXPECT_EQ(status.getLevel(), initialLevel + 1);
}


TEST(GoldConversionTest, GoldToRubyConversion) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    gameArray[0] = std::make_unique<Gold>(0, 10);
    gameArray[1] = std::make_unique<Gold>(1, 20);
    gameArray[2] = std::make_unique<Gold>(2, 30);
    
    testAccess.getGame()->checkAndConvertGoldToRubies();
    EXPECT_EQ(gameArray[0]->returntype(), ObjectType::RUBY);
    EXPECT_EQ(gameArray[1]->returntype(), ObjectType::RUBY);
    EXPECT_EQ(gameArray[2]->returntype(), ObjectType::RUBY);
}

TEST(ObjectDeathTest, VariousObjectDeathScenarios) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    gameArray[1] = std::make_unique<Weapon>(1, 5);
    gameArray[1]->setOnDamageCallback([&game](int pos, DamageType type) {
        game.handleObjectDamage(pos, type);
    });
    
    gameArray[1]->takeDamage(10, DamageType::NORMAL);
    testAccess.getGame()->handleObjectDamage(4, DamageType::NORMAL);
    
    EXPECT_EQ(gameArray[1]->returntype(), ObjectType::GOLD);
    
    Player* player = testAccess.getPlayer();
    player->setHP(5);
    player->takeDamage(10, DamageType::NORMAL);
    testAccess.getGame()->handleObjectDamage(4, DamageType::NORMAL);
    
    EXPECT_TRUE(testAccess.getGame()->isGameOver());
}


TEST(MovementTest, BoundaryConditions) {
    Game game;
    GameTestAccess testAccess(&game);
    Player* player = testAccess.getPlayer();

    player->setPosition(0);
    EXPECT_FALSE(player->possibletomove(0));
    EXPECT_FALSE(player->possibletomove(3));
    
    player->setPosition(8);
    EXPECT_FALSE(player->possibletomove(1));
    EXPECT_FALSE(player->possibletomove(2));

    player->setPosition(0);
    EXPECT_TRUE(player->possibletomove(1));
    EXPECT_TRUE(player->possibletomove(2));
}


TEST(CallbackTest, DamageCallbackSystem) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    
    bool callbackCalled = false;
    int callbackPos = -1;
    DamageType callbackType = DamageType::NORMAL;
    gameArray[4] = std::make_unique<Gold>(4, 20);
    gameArray[4]->setOnDamageCallback([&](int pos, DamageType type) {
        callbackCalled = true;
        callbackPos = pos;
        callbackType = type;
        game.handleObjectDamage(pos, type);
    });
    
    gameArray[4]->takeDamage(5, DamageType::FIRE);
    EXPECT_TRUE(callbackCalled);
    EXPECT_EQ(callbackPos, 4);
    EXPECT_EQ(callbackType, DamageType::FIRE);
}