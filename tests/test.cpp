/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */
#include "gtest/gtest.h"
#include "Game.h"


class GameTestAccess {
private:
    Game* game;
    
public:
    GameTestAccess(Game* gameInstance) : game(gameInstance) {}
    Game* getGame(){return game;}
    std::array<std::unique_ptr<Object>, 9>& getGameArray() { return game->game; }
    Player* getPlayer() { return game->player; }
    Status& getStatus() { return game->_STATUS; }
    bool& getGameOver() { return game->gameOver; }
};

TEST(ELmagicTest, ELmagicHitsThroughEnemy) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    Player* player = testAccess.getPlayer();
    gameArray[1] = std::make_unique<Object>(1);
    game.handleInput('w');
    struct TestCase {
        ObjectType type;
        std::function<std::unique_ptr<Object>()> factory;
    };
    
    std::vector<TestCase> testObjects = {
        {ObjectType::ENEMY, []() { return std::make_unique<Enemy>(7, 20);}},
        {ObjectType::ELEMENTAL, []() { return std::make_unique<Elemental>(7, 20, DamageType::FIRE);}},
        {ObjectType::ELEMENTAL, []() { return std::make_unique<Elemental>(7, 20, DamageType::ICE);}},
        {ObjectType::WEAPON, []() { return std::make_unique<Weapon>(7, 20);}},
        {ObjectType::ELWEAPON, []() { return std::make_unique<ELweapon>(7, 20, DamageType::ICE);}},
        {ObjectType::ELMAGIC, []() { return std::make_unique<ELmagic>(7, 20, DamageType::ICE);}},
        {ObjectType::ELWEAPON, []() { return std::make_unique<ELweapon>(7, 20, DamageType::FIRE); }},
        {ObjectType::ELMAGIC, []() { return std::make_unique<ELmagic>(7, 20, DamageType::FIRE); }},
        {ObjectType::GOLD, []() { return std::make_unique<Gold>(7, 20); }},
        {ObjectType::CHEST, []() { return std::make_unique<Chest>(7, ChestType::GOODCHEST); }},
        {ObjectType::OBJECT, []() { return std::make_unique<Object>(7); }}
    };

    for (auto& p: testObjects){
        gameArray[4] = std::make_unique<Enemy>(4, 20);
        Enemy* enemy = dynamic_cast<Enemy*>(gameArray[4].get());
        gameArray[7] = p.factory();
        auto magicWand = std::make_unique<ELmagic>(5, 9, DamageType::FIRE);
        player->setWeapon(std::move(magicWand));
        testAccess.getGame()->handleCOMBAT_DEPENDENT(1, 4);
        EXPECT_EQ(enemy->getHP(), 11);
        Object* objectBehind = gameArray[7].get();

        switch(p.type) {
            case ObjectType::ENEMY: {
                Enemy* behindEnemy = dynamic_cast<Enemy*>(objectBehind);
                EXPECT_EQ(behindEnemy->getHP(), 11);
                break;
            }
            case ObjectType::ELEMENTAL: {
                Elemental* behindEnemy = dynamic_cast<Elemental*>(objectBehind);
                EXPECT_EQ(behindEnemy->getHP(), (behindEnemy->getElement() == DamageType::FIRE) ? 29 : 2);
                break;
            }
            case ObjectType::WEAPON:
                {
                    Weapon* weapon = dynamic_cast<Weapon*>(objectBehind);
                    EXPECT_EQ(weapon->getDamage(), 11);
                    break;
                }
            case ObjectType::ELWEAPON:
                {
                    ELweapon* weapon = dynamic_cast<ELweapon*>(objectBehind);
                    EXPECT_EQ(weapon->getDamage(), (weapon->getElement() == DamageType::FIRE) ? 29 : 11);
                    break;
                }
            case ObjectType::ELMAGIC:
                {
                    ELmagic* weapon = dynamic_cast<ELmagic*>(objectBehind);
                    EXPECT_EQ(weapon->getDamage(), (weapon->getElement() == DamageType::FIRE) ? 29 : 2);
                    break;
                }
            case ObjectType::GOLD:
                {
                    Gold* gold = dynamic_cast<Gold*>(objectBehind);
                    EXPECT_EQ(gold->getAmount(), 11);
                    break;
                }
            case ObjectType::CHEST:
                {
                    EXPECT_EQ(gameArray[7]->returntype(), ObjectType::CHEST);
                    break; 
                }
            case ObjectType::OBJECT:
                {
                    EXPECT_EQ(gameArray[7]->returntype(), ObjectType::OBJECT);
                    break; 
                }
            default:
                std::cerr<<"None ObjectType in ELmagicHitsThroughEnemy";
        }
        
        player->removeWeapon();
        gameArray[4].reset();
        gameArray[7].reset();
    }
}


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