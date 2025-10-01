/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

#include "TestHelper.h"


TEST(ThornTest, ThornDirectionalDamageAndRotation) {
    Game game;
    int initialHP;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    Player* player = testAccess.getPlayer();
    gameArray[1] = std::make_unique<Object>(1);
    game.handleInput('w');
    std::array<bool, 4> directions = {true, true, false, false}; 
    gameArray[4] = std::make_unique<Thorn>(4, 15, directions);
    initialHP = player->getHP();
    testAccess.getGame()->handleIMMEDIATE_PASS(1, 4);
    EXPECT_EQ(player->getHP(), initialHP - 15);


    gameArray[7] = std::make_unique<Object>(7);
    game.handleInput('s');
    gameArray[4] = std::make_unique<Thorn>(4, 15, directions);
    initialHP = player->getHP();
    testAccess.getGame()->handleIMMEDIATE_PASS(7, 4);
    EXPECT_EQ(player->getHP(), initialHP);

    gameArray[3] = std::make_unique<Object>(3);
    game.handleInput('a');
    gameArray[4] = std::make_unique<Thorn>(4, 15, directions);
    initialHP = player->getHP();
    testAccess.getGame()->handleIMMEDIATE_PASS(3, 4);
    EXPECT_EQ(player->getHP(), initialHP);

    gameArray[5] = std::make_unique<Object>(5);
    game.handleInput('d');
    gameArray[4] = std::make_unique<Thorn>(4, 15, directions);
    initialHP = player->getHP();
    testAccess.getGame()->handleIMMEDIATE_PASS(5, 4);
    EXPECT_EQ(player->getHP(), initialHP - 15);

    
    Thorn thorn(4, 15, directions);
    thorn.update();
    std::array<bool, 4> newDirs = thorn.getDirections();
    EXPECT_EQ(newDirs[0], directions[3]); 
    EXPECT_EQ(newDirs[1], directions[0]);
    EXPECT_EQ(newDirs[2], directions[1]);
    EXPECT_EQ(newDirs[3], directions[2]);
}





TEST(ExplosivesTest, BombAndDynamiteDamage) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    Player* player = testAccess.getPlayer();
    int initialHP = player->getHP();
    gameArray[1] = std::make_unique<Object>(1);
    gameArray[0] = std::make_unique<Object>(0);
    game.handleInput('w');
    game.handleInput('a');
    gameArray[4] = std::make_unique<Bomb>(4, 15);
    gameArray[4]->setOnDamageCallback([&game](int pos, DamageType type) {
        game.handleObjectDamage(pos, type);
    });
    
    gameArray[1] = std::make_unique<Gold>(1, 20);
    gameArray[1]->setOnDamageCallback([&game](int pos, DamageType type) {
        game.handleObjectDamage(pos, type);
    });
    gameArray[3] = std::make_unique<Gold>(3, 15);
    gameArray[3]->setOnDamageCallback([&game](int pos, DamageType type) {
        game.handleObjectDamage(pos, type);
    });
    gameArray[5] = std::make_unique<Gold>(5, 16);
    gameArray[5]->setOnDamageCallback([&game](int pos, DamageType type) {
        game.handleObjectDamage(pos, type);
    });
    gameArray[7] = std::make_unique<Gold>(7, 13);
    gameArray[7]->setOnDamageCallback([&game](int pos, DamageType type) {
        game.handleObjectDamage(pos, type);
    });
    
    testAccess.getGame()->handleObjectDeath(4);
    game.update();
    
    std::cout<<gameArray[4]->print().header<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
    EXPECT_EQ(dynamic_cast<Gold*>(gameArray[1].get())->getAmount(), 5);
    EXPECT_EQ(gameArray[3]->returntype(), ObjectType::OBJECT);
    EXPECT_EQ(gameArray[4]->returntype(), ObjectType::GOLD);
    EXPECT_EQ(dynamic_cast<Gold*>(gameArray[5].get())->getAmount(), 1);
    EXPECT_EQ(gameArray[7]->returntype(), ObjectType::OBJECT);


    gameArray[1] = std::make_unique<Gold>(1, 10);
    gameArray[2] = std::make_unique<Dynamite>(2, 8);
    for (int i = 0; i < 3; i++){
        gameArray[i]->setOnDamageCallback([&game](int pos, DamageType type) {
            game.handleObjectDamage(pos, type);
        });
    }
    testAccess.getGame()->handleObjectDeath(2);
    EXPECT_EQ(dynamic_cast<Gold*>(gameArray[1].get())->getAmount(), 2);
    EXPECT_EQ(gameArray[2]->returntype(), ObjectType::GOLD);
    EXPECT_EQ(player->getHP(), initialHP - 8);



}



TEST(ChestTest, ChestLootGeneration) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    

    gameArray[4] = std::make_unique<Chest>(4, ChestType::GOODCHEST);
    testAccess.getGame()->handleTRIGGER_ON_STAY(4);
    
    Object* loot = gameArray[4].get();
    ASSERT_NE(loot, nullptr);
    

    bool isHelpfulLoot = dynamic_cast<Gold*>(loot) != nullptr ||
                         dynamic_cast<Ruby*>(loot) != nullptr ||
                         (dynamic_cast<Potion*>(loot) != nullptr && 
                          dynamic_cast<Potion*>(loot)->getPotionType() == PotionType::HEAL) ||
                         dynamic_cast<Weapon*>(loot) != nullptr;
    EXPECT_TRUE(isHelpfulLoot);
    

    gameArray[4] = std::make_unique<Chest>(4, ChestType::BADCHEST);
    testAccess.getGame()->handleTRIGGER_ON_STAY(4);
    
    loot = gameArray[4].get();
    ASSERT_NE(loot, nullptr);
    

    bool isHarmfulLoot = dynamic_cast<Enemy*>(loot) != nullptr ||
                         dynamic_cast<Bomb*>(loot) != nullptr ||
                         (dynamic_cast<Potion*>(loot) != nullptr && 
                          dynamic_cast<Potion*>(loot)->getPotionType() == PotionType::POISON);
    EXPECT_TRUE(isHarmfulLoot);
}




TEST(PotionTest, PotionEffects) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    Player* player = testAccess.getPlayer();
    

    gameArray[1] = std::make_unique<Potion>(1, 25, PotionType::HEAL);
    player->setHP(50);
    int initialHP = player->getHP();
    
    testAccess.getGame()->handleIMMEDIATE_PASS(4, 1);
    EXPECT_EQ(player->getHP(), initialHP + 25);
    
 
    gameArray[4] = std::make_unique<Potion>(4, 15, PotionType::POISON);
    initialHP = player->getHP();
    
    testAccess.getGame()->handleIMMEDIATE_PASS(1, 4);
    EXPECT_EQ(player->getHP(), initialHP - 15);
}




TEST(RubyTest, RubyBonusCollection) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    auto& status = testAccess.getStatus();
    
    gameArray[1] = std::make_unique<Object>(1);
    game.handleInput('w');
    

    gameArray[4] = std::make_unique<Ruby>(4, 10);
    int initialGold = status.getGold();
    int initialXP = status.getXp();
    
    testAccess.getGame()->handleIMMEDIATE_PASS(1, 4);

    EXPECT_EQ(status.getGold(), initialGold + 20);
    EXPECT_EQ(status.getXp(), initialXP + 50);
}



TEST(BombTest, BombTimerCountdown) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    
    gameArray[1] = std::make_unique<Bomb>(1, 10);
    Bomb* bomb = dynamic_cast<Bomb*>(gameArray[1].get());
    
    EXPECT_EQ(bomb->getDuration(), 5);
    bomb->update();
    EXPECT_EQ(bomb->getDuration(), 4);
    bomb->update();
    EXPECT_EQ(bomb->getDuration(), 3);
    bomb->update();
    EXPECT_EQ(bomb->getDuration(), 2);
}



TEST(GunTest, GunMultiDirectionalFireDamage) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    Player* player = testAccess.getPlayer();
    int initialHP = player->getHP();
    gameArray[1] = std::make_unique<Object>(1);
    game.handleInput('w');
    
    std::array<bool, 4> directions = {true, true, false, false}; 
    gameArray[4] = std::make_unique<Gun>(4, 12, directions);
    
    gameArray[3] = std::make_unique<Gold>(3, 20);
    gameArray[5] = std::make_unique<ELweapon>(5, 10, DamageType::FIRE);
    gameArray[7] = std::make_unique<Gold>(7, 20);
    
    testAccess.getGame()->handleIMMEDIATE_PASS(1, 4);
    
    EXPECT_EQ(player->getHP(), initialHP - 12);
    EXPECT_EQ(dynamic_cast<Gold*>(gameArray[3].get())->getAmount(), 20);
    EXPECT_EQ(dynamic_cast<ELweapon*>(gameArray[5].get())->getDamage(), 22);
    EXPECT_EQ(dynamic_cast<Gold*>(gameArray[7].get())->getAmount(), 20);
    initialHP = player->getHP();
    gameArray[3] = std::make_unique<Object>(3);
    game.handleInput('a');
    directions = {true, true, true, false};
    gameArray[4] = std::make_unique<Gun>(4, 12, directions);
    
    gameArray[1] = std::make_unique<Elemental>(1, 20, DamageType::ICE);
    gameArray[1]->setOnDamageCallback([&game](int pos, DamageType type) {
        game.handleObjectDamage(pos, type);
    });

    gameArray[5] = std::make_unique<ELmagic>(5, 10, DamageType::FIRE);
    gameArray[7] = std::make_unique<Gold>(7, 20);
    testAccess.getGame()->handleIMMEDIATE_PASS(3, 4);
    game.update();
    EXPECT_EQ(player->getHP(), initialHP);
    EXPECT_EQ(gameArray[1]->returntype(), ObjectType::GOLD);
    EXPECT_EQ(dynamic_cast<ELmagic*>(gameArray[5].get())->getDamage(), 22);
    EXPECT_EQ(dynamic_cast<Gold*>(gameArray[7].get())->getAmount(), 8);
    


    Gun gun(4, 15, directions);
    gun.update();
    std::array<bool, 4> newDirs = gun.getDirections();
    EXPECT_EQ(newDirs[0], directions[3]); 
    EXPECT_EQ(newDirs[1], directions[0]);
    EXPECT_EQ(newDirs[2], directions[1]);
    EXPECT_EQ(newDirs[3], directions[2]);
}





TEST(SwapTest, BombAndDynamiteSwap) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    Player* player = testAccess.getPlayer();
    
    gameArray[1] = std::make_unique<Object>(1);
    game.handleInput('w');
    int initialHP = player->getHP();

    gameArray[4] = std::make_unique<Bomb>(4, 15);
    testAccess.getGame()->handleSWAP_REQUIRED(1, 4);
    EXPECT_EQ(player->getPosition(), 4);
    EXPECT_EQ(player->getHP(), initialHP);
    EXPECT_EQ(gameArray[4]->returntype(), ObjectType::PLAYER);
    EXPECT_EQ(gameArray[1]->returntype(), ObjectType::BOMB);
}

TEST(DamageCalculationTest, ThornDamageCalculation) {
    std::array<bool, 4> directions = {true, false, true, false};
    Thorn thorn(4, 15, directions);
    
    EXPECT_EQ(thorn.calculateFinalDamage(10, DamageType::NORMAL), 10);
}

