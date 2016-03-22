#include "gtest/gtest.h"
#include "item.h"

using std::string;

TEST(ItemTest, constructorGetterTest)
{
	Item i0("i0 is beautiful", true);
	Item i1("i1 is beautiful", false);
	string n0[] = {"i0"};
	string n1[] = {"i1"};

	i0.setNames(n0,1);
	i1.setNames(n1,1);

	EXPECT_TRUE(i0.isVisible());
	EXPECT_FALSE(i1.isVisible());
	EXPECT_EQ(i0.beLookedAt(), "i0 is beautiful");
	EXPECT_EQ(i1.beLookedAt(), "");
}

TEST(ItemTest, setVisibilityTest)
{
    Item i0("i0 is beautiful", false);
    string n0[] = {"i0"};
    i0.setNames(n0, 1);

    EXPECT_EQ(i0.beLookedAt(), "");

    i0.setVisibleTo(true);

    EXPECT_EQ(i0.beLookedAt(), "i0 is beautiful");
}

TEST(ItemTest, hasNameTest)
{
    Item i0("i0 is beautiful", true);
    string n0[] = {"i0", "pretty thing"};
    i0.setNames(n0, 2);

    EXPECT_TRUE(i0.hasName("i0"));
    EXPECT_TRUE(i0.hasName("pretty thing"));
    EXPECT_FALSE(i0.hasName("i1"));
}
