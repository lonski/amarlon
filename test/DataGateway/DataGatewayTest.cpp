#include "gtest/gtest.h"
#include "DataGateways/DataGateway.h"

TEST(DataGatewayTest, addData_TagAndSectionExitsts)
{
  DataGateway data;
  data.addData<int>("sekcja1", "tag1", 55);

  EXPECT_TRUE(data.sectionExists("sekcja1"));
  EXPECT_TRUE(data.tagExists("sekcja1", "tag1"));
}

TEST(DataGatewayTest, AddingNewSectionIncrementSectionCount)
{
  DataGateway data;
  data.addData<int>("sekcja1", "tag1", 55);
  data.addData<int>("sekcja1", "tag2", 55);
  data.addData<int>("sekcja2", "tag1", 55);

  EXPECT_EQ(data.getSectionCount(), (size_t)2);
}

TEST(DataGatewayTest, IfTheresNoSectionThenItNotExists)
{
  DataGateway data;
  EXPECT_FALSE(data.sectionExists("dupa"));
}

TEST(DataGatewayTest, WhenAddTag_ItExists)
{
  DataGateway data;
  data.addData<std::string>("sec", "tag1", "sdf");

  EXPECT_TRUE(data.tagExists("sec", "tag1"));
  EXPECT_FALSE(data.tagExists("sec", "cycki"));
}

TEST(DataGatewayTest, WhenAddTwoTag_TheyBothExists)
{
  DataGateway data;
  data.addData<int>("sec", "tag1", 1);
  data.addData<int>("sec", "tag2", 54);

  EXPECT_TRUE(data.tagExists("sec", "tag1"));
  EXPECT_TRUE(data.tagExists("sec", "tag2"));
}

TEST(DataGatewayTest, WhenAddTwoSectionTheyExists)
{
  DataGateway data;
  data.addData<float>("sec1", "tag1", 1);
  data.addData<int>("sec2", "tag2", 54);

  EXPECT_TRUE(data.sectionExists("sec1"));
  EXPECT_TRUE(data.sectionExists("sec2"));
}

TEST(DataGatewayTest, WhenAddedOneDataYouCanRetriveIt)
{
  DataGateway data;
  data.addData<int>("s1", "t1", 43);
  int i = data.retriveData<int>("s1", "t1");

  EXPECT_EQ(i, 43);
}

TEST(DataGatewayTest, retriveDifferentDataFromDifferentSections)
{
  DataGateway data;
  data.addData<int>("s1", "t1", 10);
  data.addData<double>("s1", "t2", 6.66);
  data.addData<std::string>("s2", "t1", "lol");

  data.saveContent("test.sav");

  DataGateway data2;
  data2.loadContent("test.sav");

  EXPECT_EQ(data2.retriveData<double>("s1", "t2"), 6.66);
  EXPECT_EQ(data2.retriveData<std::string>("s2","t1"), "lol");
  EXPECT_EQ(data2.retriveData<int>("s1", "t1"), 10);
  EXPECT_EQ(data2.retriveData<std::string>("s1", "t1"), "10");
}

TEST(DataGatewayTest, addVectorOfData_retriveSameValues)
{
  DataGateway data;

  std::vector<int> numbers{3, 56, 23, 666, 8};
  data.addData<int>("some_section","tagVector", numbers);

  std::vector<int> new_nums;
  data.retriveData<int>("some_section", "tagVector", new_nums);

  ASSERT_EQ(new_nums.size(), numbers.size() );
  EXPECT_TRUE(std::equal(numbers.begin(), numbers.end(), new_nums.begin()));
}

TEST(DataGatewayTest, notExistingIntField_ReturnsZero)
{
  DataGateway data;
  ASSERT_EQ(data.retriveData<int>("x", "xx"), 0);
  data.retriveData<int>("s_id", "ai");
}

TEST(DataGatewayTest, notExistingStringField_ReturnsEmptyString)
{
  DataGateway data;
  ASSERT_EQ(data.retriveData<std::string>("x", "xx"), "");
}

TEST(DataGatewayTest, exploteStringWithSpaces)
{
  std::string str = ";ala ma kota;kot ma ale";
  std::vector<std::string> vec = explode(str,';');

  ASSERT_EQ(vec.size(), (size_t)2);
  EXPECT_EQ(vec[0], "ala ma kota");
  EXPECT_EQ(vec[1], "kot ma ale");
}

TEST(DataGatewayTest, retriveStringWithSpaces)
{
  DataGateway data;
  data.addData<std::string>("s1","t1", "ala ma kota");
  ASSERT_EQ(data.retriveDataStr("s1", "t1"), "ala ma kota");
}

