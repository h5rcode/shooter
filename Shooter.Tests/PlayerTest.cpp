#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "AnimatedRenderableMock.h"
#include "InventoryMock.h"
#include "ItemMock.h"
#include "Player.h"
#include "ResourceManagerMock.h"
#include "WeaponMock.h"

using ::testing::Return;
using ::testing::ReturnRef;

using namespace Shooter::Inventory;
using namespace Shooter::Items;
using namespace Shooter::Items::Weapons;
using namespace Shooter::Math;
using namespace Shooter::Rendering;
using namespace Shooter::Rendering::Renderables;

TEST(PlayerTest_canAttack, should_return_false_when_there_is_no_equipped_weapon)
{
	AnimatedRenderableMock animatedRenderable;
	ResourceManagerMock resourceManager;
	InventoryMock inventory;

	sf::SoundBuffer soundBuffer;
	EXPECT_CALL(resourceManager, getSoundBuffer("Resources/sounds/138476__randomationpictures__step-tap.wav"))
		.WillOnce(Return(&soundBuffer));

	Player player(Vector2(), 1, animatedRenderable, inventory, resourceManager);

	bool canAttack = player.canAttack();

	EXPECT_FALSE(canAttack);
}

TEST(PlayerTest_canAttack, should_return_false_when_the_equipped_weapon_cannot_attack)
{
	AnimatedRenderableMock animatedRenderable;
	ResourceManagerMock resourceManager;
	InventoryMock inventory;

	sf::SoundBuffer soundBuffer;
	EXPECT_CALL(resourceManager, getSoundBuffer("Resources/sounds/138476__randomationpictures__step-tap.wav"))
		.WillOnce(Return(&soundBuffer));

	Player player(Vector2(), 1, animatedRenderable, inventory, resourceManager);

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
	ResourceManagerMock resourceManager;
	InventoryMock inventory;

	sf::SoundBuffer soundBuffer;
	EXPECT_CALL(resourceManager, getSoundBuffer("Resources/sounds/138476__randomationpictures__step-tap.wav"))
		.WillOnce(Return(&soundBuffer));

	Player player(Vector2(), 1, animatedRenderable, inventory, resourceManager);

	std::shared_ptr<WeaponMock> weapon = std::make_shared<WeaponMock>();
	EXPECT_CALL(*weapon, canAttack())
		.WillOnce(Return(true));

	player.equipWeapon(weapon);

	bool result = player.canAttack();

	EXPECT_TRUE(result);
}

TEST(PlayerTest_hurt, should_decrement_hitpoints_with_the_damage)
{
	int hitpoints = 100;
	AnimatedRenderableMock animatedRenderable;
	ResourceManagerMock resourceManager;
	InventoryMock inventory;

	sf::SoundBuffer soundBuffer;
	EXPECT_CALL(resourceManager, getSoundBuffer("Resources/sounds/138476__randomationpictures__step-tap.wav"))
		.WillOnce(Return(&soundBuffer));

	Player player(Vector2(), hitpoints, animatedRenderable, inventory, resourceManager);

	int damage = 33;

	player.hurt(damage);

	EXPECT_EQ(hitpoints - damage, player.getHitpoints());
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
	ResourceManagerMock resourceManager;
	InventoryMock inventory;

	sf::SoundBuffer soundBuffer;
	EXPECT_CALL(resourceManager, getSoundBuffer("Resources/sounds/138476__randomationpictures__step-tap.wav"))
		.WillOnce(Return(&soundBuffer));

	std::shared_ptr<IItem> item = (std::shared_ptr<IItem>)itemMock;
	EXPECT_CALL(inventory, addItem(item))
		.WillOnce(Return(true));

	Player player(playerPosition, 1, animatedRenderable, inventory, resourceManager);

	// Act.
	bool result = player.pickUpItem(item);

	// Assert.
	EXPECT_TRUE(result);
}
