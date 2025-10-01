
/* Lukyanova Angelina st128743@student.spbu.ru
 * Lab Work 2 - Game
 */

#include "TestHelper.h"
#include <climits>

TEST(ExceptionTest, NullPointerAccess) {
    Game game;
    GameTestAccess testAccess(&game);
    
    EXPECT_NO_THROW(testAccess.getGame()->handleObjectDamage(-1, DamageType::NORMAL));
    EXPECT_NO_THROW(testAccess.getGame()->handleObjectDamage(10, DamageType::NORMAL));
}

TEST(ExceptionTest, InvalidDynamicCasts) {
    std::unique_ptr<Object> obj = std::make_unique<Object>(4);
    Player* player = dynamic_cast<Player*>(obj.get());
    EXPECT_EQ(player, nullptr);
    
    Weapon* weapon = dynamic_cast<Weapon*>(obj.get());
    EXPECT_EQ(weapon, nullptr);
}

TEST(ExceptionSafety, CallbackWithNullObjects) {
    Game game;
    GameTestAccess testAccess(&game);
    auto& gameArray = testAccess.getGameArray();
    
    EXPECT_NO_THROW(testAccess.getGame()->handleObjectDamage(4, DamageType::NORMAL));
    
    gameArray[4] = nullptr;
    EXPECT_NO_THROW(testAccess.getGame()->handleObjectDamage(4, DamageType::NORMAL));
}




