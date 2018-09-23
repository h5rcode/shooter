#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "Player.h"
#include "AnimatedRenderableMock.h"
#include "WeaponMock.h"

using ::testing::Return;

TEST(PlayerTest_canAttack, should_return_false_when_there_is_no_equipped_weapon)
{
	AnimatedRenderableMock animatedRenderable;
	Player player(Vector2(), animatedRenderable);

	bool canAttack = player.canAttack();

	EXPECT_FALSE(canAttack);
}

TEST(PlayerTest_canAttack, should_return_false_when_the_equipped_weapon_cannot_attack)
{
	AnimatedRenderableMock animatedRenderable;
	Player player(Vector2(), animatedRenderable);

	std::shared_ptr<WeaponMock> weapon = std::make_shared<WeaponMock>();
	EXPECT_CALL(*weapon, canAttack())
		.WillOnce(Return(false));

	player.equipWeapon(weapon);

	bool result = player.canAttack();

	EXPECT_FALSE(result);
}

TEST(PlayerTest_canAttack, should_return_true_when_the_equipped_weapon_can_attack)
{
	AnimatedRenderableMock animatedRenderable;
	Player player(Vector2(), animatedRenderable);

	std::shared_ptr<WeaponMock> weapon = std::make_shared<WeaponMock>();
	EXPECT_CALL(*weapon, canAttack())
		.WillOnce(Return(true));

	player.equipWeapon(weapon);

	bool result = player.canAttack();

	EXPECT_TRUE(result);
}
