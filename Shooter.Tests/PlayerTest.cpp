#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "InventoryMock.h"
#include "ItemMock.h"
#include "Player.h"
#include "WeaponMock.h"

using ::testing::Return;
using ::testing::ReturnRef;

using namespace Shooter::Inventory;
using namespace Shooter::Items;
using namespace Shooter::Items::Weapons;
using namespace Shooter::Math;

TEST(Player_canAttack, should_return_false_when_there_is_no_equipped_weapon)
{
	InventoryMock inventory;

	Player player(Vector2(), 1, inventory);

	bool canAttack = player.canAttack();

	EXPECT_FALSE(canAttack);
}

TEST(Player_canAttack, should_return_false_when_the_equipped_weapon_cannot_attack)
{
	InventoryMock inventory;

	Player player(Vector2(), 1, inventory);

	std::shared_ptr<WeaponMock> weapon = std::make_shared<WeaponMock>();
	EXPECT_CALL(*weapon, canAttack())
		.WillOnce(Return(false));

	player.equipWeapon(weapon);

	bool result = player.canAttack();

	EXPECT_FALSE(result);
}

TEST(Player_canAttack, should_return_true_when_the_equipped_weapon_can_attack)
{
	InventoryMock inventory;

	Player player(Vector2(), 1, inventory);

	std::shared_ptr<WeaponMock> weapon = std::make_shared<WeaponMock>();
	EXPECT_CALL(*weapon, canAttack())
		.WillOnce(Return(true));

	player.equipWeapon(weapon);

	bool result = player.canAttack();

	EXPECT_TRUE(result);
}

TEST(Player_collide, should_stop_movement_in_the_direction_opposite_to_the_collision_normal) {
	InventoryMock inventory;

	Player player(Vector2(), 1, inventory);

	player.setAcceleration(Vector2(1, 0));
	player.updateSpeed(sf::seconds(10));

	Vector2 speedBeforeCollision = player.getSpeed();

	player.collide(Vector2(-1, 0));

	Vector2& speedAfterCollision = player.getSpeed();
}

TEST(Player_hurt, should_decrement_hitpoints_with_the_damage)
{
	int hitpoints = 100;
	InventoryMock inventory;

	Player player(Vector2(), hitpoints, inventory);

	int damage = 33;

	player.hurt(damage);

	EXPECT_EQ(hitpoints - damage, player.getHitpoints());
}

TEST(Player_pickUpItem, should_return_true_when_the_item_is_within_reach_and_can_be_added_to_the_inventory)
{
	// Arrange.
	Vector2 playerPosition;
	Vector2 itemPosition = Vector2(playerPosition.x + 10, playerPosition.y);

	std::shared_ptr<ItemMock> itemMock = std::make_shared<ItemMock>();
	EXPECT_CALL(*itemMock, getPosition())
		.WillOnce(ReturnRef(itemPosition));

	InventoryMock inventory;

	std::shared_ptr<IItem> item = (std::shared_ptr<IItem>)itemMock;
	EXPECT_CALL(inventory, addItem(item))
		.WillOnce(Return(true));

	Player player(playerPosition, 1, inventory);

	// Act.
	bool result = player.pickUpItem(item);

	// Assert.
	EXPECT_TRUE(result);
}

TEST(Player_updateSpeed, should_increment_the_speed_according_to_the_acceleration_and_the_elapsed_time) {
	InventoryMock inventory;

	Player player(Vector2(), 1, inventory);

	player.setAcceleration(Vector2(1, 0));
	player.updateSpeed(sf::seconds(10));

	Vector2& speed = player.getSpeed();

	EXPECT_EQ(10, speed.x);
}
