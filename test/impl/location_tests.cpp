#include<iostream>
#include "gtest/gtest.h"
#include "location.h"
#include "item.h"

TEST(LocationTests, constructorGetterTest)
{
	Location l0("loc0ID", "This is descriptive");

	EXPECT_EQ(l0.getLocID(), "loc0ID");
}

TEST(LocationTests, beLookedAtTest)
{
    Location l0("loc0ID", "l0 is beautiful");
    Location l1("loc1ID", "l1 is beautiful");
    Location l2("loc2ID", "l2 is beautiful");
    Location l3("loc3ID", "l3 is beautiful");
    Location l4("loc0ID", "l4 is beautiful");

    Item *i0 = new Item("i0 is beautiful", true);
    Item *i1 = new Item("i1 is beautiful", false);

    l0.addItem(i0);
    l0.addItem(i1);

    EXPECT_EQ(l0.beLookedAt(), "l0 is beautiful\ni0 is beautiful\nThere is no path in front of you\nThere is no path to your left\nThere is no path to your right\nThere is no path behind you\n");

    i1->setVisibleTo(true);

    EXPECT_EQ(l0.beLookedAt(), "l0 is beautiful\ni0 is beautiful\ni1 is beautiful\nThere is no path in front of you\nThere is no path to your left\nThere is no path to your right\nThere is no path behind you\n");

    i0->setVisibleTo(false);
    i1->setVisibleTo(false);

    l0.setForwards(&l1, "a beautiful l1");
    l0.setLeft(&l2, "a beautiful l2");
    l0.setRight(&l3, "a beautiful l3");
    l0.setBackwards(&l4, "a beautiful l4");

    EXPECT_EQ(l0.beLookedAt(), "l0 is beautiful\nIn front of you there is a beautiful l1\nTo your left there is a beautiful l2\nTo your right there is a beautiful l3\nBehind you there is a beautiful l4\n");

    delete i0;
    delete i1;
}
