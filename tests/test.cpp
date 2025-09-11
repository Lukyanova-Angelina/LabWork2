#include "Characters.h"
#include "gtest/gtest.h"

TEST(CharacterTest, ConstructorTest)
{
	Character character("Player", 100, 10, 20, 50, true, true);

	EXPECT_EQ(character.getName(), "Player");
	EXPECT_EQ(character.getHP(), 100);
	EXPECT_EQ(character.getX(), 10);
	EXPECT_EQ(character.getY(), 20);
	EXPECT_EQ(character.getMana(), 50);
	EXPECT_TRUE(character.getJump());
	EXPECT_TRUE(character.getAlive());
}

TEST(CharacterTest, SetterTest)
{
	Character character;

	character.setName("New Player");
	character.setHP(150);
	character.setX(30);
	character.setY(40);
	character.setMana(60);
	character.setJump(false);
	character.setAlive(false);

	EXPECT_EQ(character.getName(), "New Player");
	EXPECT_EQ(character.getHP(), 150);
	EXPECT_EQ(character.getX(), 30);
	EXPECT_EQ(character.getY(), 40);
	EXPECT_EQ(character.getMana(), 60);
	EXPECT_FALSE(character.getJump());
	EXPECT_FALSE(character.getAlive());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}