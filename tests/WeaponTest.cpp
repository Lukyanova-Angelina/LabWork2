/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

#include "TestHelper.h"

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

TEST(DamageCalculationTest, ElementalWeaponInteractions) {
    ELmagic fireMagic(4, 20, DamageType::FIRE);
    ELweapon iceWeapon(5, 25, DamageType::ICE);
    
    EXPECT_EQ(fireMagic.calculateFinalDamage(10, DamageType::FIRE), -10);
    EXPECT_EQ(fireMagic.calculateFinalDamage(10, DamageType::ICE), 20);
    EXPECT_EQ(iceWeapon.calculateFinalDamage(10, DamageType::ICE), -10);
}