#include "gtest/gtest.h"

#include "Inventory.h"
#include "ItemMock.h"

using ::testing::Return;

TEST(Inventory_addItem, should_return_false_when_the_item_is_too_heavy)
{
	Inventory inventory(10);
	std::shared_ptr<ItemMock> item = std::make_shared<ItemMock>();

	EXPECT_CALL(*item, getWeight())
		.WillOnce(Return(inventory.getMaxWeight() + 1));

	bool itemWasAdded = inventory.addItem(item);

	EXPECT_FALSE(itemWasAdded);
}

TEST(Inventory_addItem, should_return_true_when_the_item_is_not_too_heavy)
{
	int itemWeight = 10;
	Inventory inventory(itemWeight);
	std::shared_ptr<ItemMock> item = std::make_shared<ItemMock>();

	EXPECT_CALL(*item, getWeight())
		.WillOnce(Return(itemWeight));

	bool itemWasAdded = inventory.addItem(item);

	EXPECT_TRUE(itemWasAdded);
	EXPECT_EQ(itemWeight, inventory.getCurrentWeight());
}
