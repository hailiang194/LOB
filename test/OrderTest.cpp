#include <gtest/gtest.h>
#include "lob/Order.hpp"

TEST(OrderTest, Construction)
{
  Order order(1, Side::BUY, 100, 5000);
  EXPECT_EQ(order.Id(), 1u);
  EXPECT_EQ(order.Side(), Side::BUY);
  EXPECT_EQ(order.Quantity(), 100u);
  EXPECT_EQ(order.Price(), 5000u);
  EXPECT_EQ(order.Filled(), 0u);
}

TEST(OrderTest, CopyConstruction)
{
  Order original(2, Side::SELL, 200, 3000);
  Order copy(original);
  EXPECT_EQ(copy.Id(), original.Id());
  EXPECT_EQ(copy.Side(), original.Side());
  EXPECT_EQ(copy.Quantity(), original.Quantity());
  EXPECT_EQ(copy.Price(), original.Price());
}

TEST(OrderTest, CopyAssignment)
{
  Order a(3, Side::BUY, 50, 1000);
  Order b(4, Side::SELL, 60, 2000);
  b = a;
  EXPECT_EQ(b.Id(), a.Id());
  EXPECT_EQ(b.Side(), a.Side());
  EXPECT_EQ(b.Quantity(), a.Quantity());
  EXPECT_EQ(b.Price(), a.Price());
}

TEST(OrderTest, MoveConstruction)
{
  Order original(5, Side::BUY, 300, 4000);
  Order moved(std::move(original));
  EXPECT_EQ(moved.Id(), 5u);
  EXPECT_EQ(moved.Side(), Side::BUY);
  EXPECT_EQ(moved.Quantity(), 300u);
  EXPECT_EQ(moved.Price(), 4000u);
}

TEST(OrderTest, MoveAssignment)
{
  Order a(6, Side::SELL, 150, 2500);
  Order b(7, Side::BUY, 100, 1000);
  b = std::move(a);
  EXPECT_EQ(b.Id(), 6u);
  EXPECT_EQ(b.Side(), Side::SELL);
  EXPECT_EQ(b.Quantity(), 150u);
  EXPECT_EQ(b.Price(), 2500u);
}

TEST(OrderTest, FillComplete)
{
  Order order(8, Side::BUY, 100, 5000);
  EXPECT_TRUE(order.Fill(100));
  EXPECT_EQ(order.Filled(), 100u);
  EXPECT_TRUE(order.IsFileed());
}

TEST(OrderTest, FillPartial)
{
  Order order(9, Side::SELL, 100, 3000);
  EXPECT_TRUE(order.Fill(40));
  EXPECT_EQ(order.Filled(), 40u);
  EXPECT_FALSE(order.IsFileed());
}

TEST(OrderTest, FillMultipleTimes)
{
  Order order(10, Side::BUY, 100, 5000);
  EXPECT_TRUE(order.Fill(30));
  EXPECT_TRUE(order.Fill(30));
  EXPECT_TRUE(order.Fill(40));
  EXPECT_EQ(order.Filled(), 100u);
  EXPECT_TRUE(order.IsFileed());
}

TEST(OrderTest, FillExceedsQuantity)
{
  Order order(11, Side::SELL, 50, 2000);
  EXPECT_FALSE(order.Fill(60));
  EXPECT_EQ(order.Filled(), 0u);
  EXPECT_FALSE(order.IsFileed());
}
