#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "AnimatedRenderableMock.h"
#include "InventoryMock.h"
#include "ItemMock.h"
#include "Player.h"
#include "WeaponMock.h"

using ::testing::Return;
using ::testing::ReturnRef;

TEST(PlayerTest_canAttack, should_return_false_when_there_is_no_equipped_weapon)
{
	AnimatedRenderableMock animatedRenderable;
	InventoryMock inventory;
	Player player(Vector2(), animatedRenderable, inventory);

	bool canAttack = player.canAttack();

	EXPECT_FALSE(canAttack);
}

TEST(PlayerTest_canAttack, should_return_false_when_the_equipped_weapon_cannot_attack)
{
	AnimatedRenderableMock animatedRenderable;
	InventoryMock inventory;
	Player player(Vector2(), animatedRenderable, inventory);

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
	InventoryMock inventory;
	Player player(Vector2(), animatedRenderable, inventory);

	std::shared_ptr<WeaponMock> weapon = std::make_shared<WeaponMock>();
	EXPECT_CALL(*weapon, canAttack())
		.WillOnce(Return(true));

	player.equipWeapon(weapon);

	bool result = player.canAttack();

	EXPECT_TRUE(result);
}

TEST(PlayerTest_pickUpItem, should_return_true_when_the_item_is_within_reach_and_can_be_added_to_the_inventory)
{
	// Arrange.
	Vector2 playerPosition;
	Vector2 itemPosition = Vector2(playerPosition.x + 10, playerPosition.y);

	std::shared_ptr<ItemMock> itemMock = std::make_shared<ItemMock>();
	EXPECT_CALL(*itemMock, getPosition())
		.WillOnce(ReturnRef(itemPosition));

	AnimatedRenderableMock animatedRenderable;
	InventoryMock inventory;

	std::shared_ptr<IItem> item = (std::shared_ptr<IItem>)itemMock;

	EXPECT_CALL(inventory, addItem(item))
		.WillOnce(Return(true));

	Player player(playerPosition, animatedRenderable, inventory);

	// Act.
	bool result = player.pickUpItem(item);

	// Assert.
	EXPECT_TRUE(result);
}
