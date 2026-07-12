#include <gtest/gtest.h>
#include "lob/Lob.hpp"

TEST(LobTest, AddBidOrder)
{
  Lob lob;
  Order order(1, Side::BUY, 100, 5000);
  EXPECT_TRUE(lob.AddOrder(order));
  EXPECT_EQ(lob.Bids().size(), 1u);
  EXPECT_EQ(lob.Bids().at(5000).size(), 1u);
  EXPECT_TRUE(lob.Asks().empty());
}

TEST(LobTest, AddAskOrder)
{
  Lob lob;
  Order order(2, Side::SELL, 200, 3000);
  EXPECT_TRUE(lob.AddOrder(order));
  EXPECT_EQ(lob.Asks().size(), 1u);
  EXPECT_EQ(lob.Asks().at(3000).size(), 1u);
  EXPECT_TRUE(lob.Bids().empty());
}

TEST(LobTest, AddMultipleOrdersSamePrice)
{
  Lob lob;
  Order o1(1, Side::BUY, 100, 5000);
  Order o2(2, Side::BUY, 200, 5000);
  EXPECT_TRUE(lob.AddOrder(o1));
  EXPECT_TRUE(lob.AddOrder(o2));
  EXPECT_EQ(lob.Bids().size(), 1u);
  EXPECT_EQ(lob.Bids().at(5000).size(), 2u);
}

TEST(LobTest, AddMultipleOrdersDifferentPrices)
{
  Lob lob;
  Order o1(1, Side::BUY, 100, 5000);
  Order o2(2, Side::BUY, 200, 4500);
  Order o3(3, Side::BUY, 300, 5500);
  EXPECT_TRUE(lob.AddOrder(o1));
  EXPECT_TRUE(lob.AddOrder(o2));
  EXPECT_TRUE(lob.AddOrder(o3));
  EXPECT_EQ(lob.Bids().size(), 3u);
}

TEST(LobTest, CancelBidOrder)
{
  Lob lob;
  Order order(1, Side::BUY, 100, 5000);
  lob.AddOrder(order);
  EXPECT_TRUE(lob.CancelOrder(1));
  EXPECT_TRUE(lob.Bids().empty());
}

TEST(LobTest, CancelAskOrder)
{
  Lob lob;
  Order order(2, Side::SELL, 200, 3000);
  lob.AddOrder(order);
  EXPECT_TRUE(lob.CancelOrder(2));
  EXPECT_TRUE(lob.Asks().empty());
}

TEST(LobTest, CancelNonExistentOrder)
{
  Lob lob;
  EXPECT_FALSE(lob.CancelOrder(999));
}

TEST(LobTest, CancelOneOfMultipleSamePrice)
{
  Lob lob;
  Order o1(1, Side::BUY, 100, 5000);
  Order o2(2, Side::BUY, 200, 5000);
  lob.AddOrder(o1);
  lob.AddOrder(o2);
  EXPECT_TRUE(lob.CancelOrder(1));
  EXPECT_EQ(lob.Bids().size(), 1u);
  EXPECT_EQ(lob.Bids().at(5000).size(), 1u);
}

TEST(LobTest, ModifyOrder)
{
  Lob lob;
  Order original(1, Side::BUY, 100, 5000);
  lob.AddOrder(original);
  Order modified(1, Side::BUY, 150, 4800);
  EXPECT_TRUE(lob.ModifyOrder(modified));
  EXPECT_TRUE(lob.Bids().find(5000) == lob.Bids().end());
  EXPECT_EQ(lob.Bids().at(4800).size(), 1u);
  EXPECT_EQ(lob.Bids().at(4800).front().Quantity(), 150u);
}

TEST(LobTest, MatchExactFill)
{
  Lob lob;
  Order bid(1, Side::BUY, 100, 5000);
  Order ask(2, Side::SELL, 100, 5000);
  lob.AddOrder(bid);
  lob.AddOrder(ask);
  std::size_t matched = lob.MatchOrders();
  EXPECT_EQ(matched, 2u);
  EXPECT_TRUE(lob.Bids().empty());
  EXPECT_TRUE(lob.Asks().empty());
}

TEST(LobTest, MatchBidHigherThanAsk)
{
  Lob lob;
  Order bid(1, Side::BUY, 100, 5000);
  Order ask(2, Side::SELL, 100, 4000);
  lob.AddOrder(bid);
  lob.AddOrder(ask);
  std::size_t matched = lob.MatchOrders();
  EXPECT_EQ(matched, 2u);
  EXPECT_TRUE(lob.Bids().empty());
  EXPECT_TRUE(lob.Asks().empty());
}

TEST(LobTest, MatchNoCross)
{
  Lob lob;
  Order bid(1, Side::BUY, 100, 4000);
  Order ask(2, Side::SELL, 100, 5000);
  lob.AddOrder(bid);
  lob.AddOrder(ask);
  std::size_t matched = lob.MatchOrders();
  EXPECT_EQ(matched, 0u);
  EXPECT_EQ(lob.Bids().size(), 1u);
  EXPECT_EQ(lob.Asks().size(), 1u);
}

TEST(LobTest, MatchPartialFill)
{
  Lob lob;
  Order bid(1, Side::BUY, 100, 5000);
  Order ask(2, Side::SELL, 200, 5000);
  lob.AddOrder(bid);
  lob.AddOrder(ask);
  std::size_t matched = lob.MatchOrders();
  EXPECT_EQ(matched, 2u);
  EXPECT_TRUE(lob.Bids().empty());
  EXPECT_EQ(lob.Asks().size(), 1u);
  EXPECT_EQ(lob.Asks().at(5000).front().Filled(), 100u);
}

TEST(LobTest, MatchMultipleOrders)
{
  Lob lob;
  Order bid1(1, Side::BUY, 100, 5000);
  Order bid2(2, Side::BUY, 100, 5000);
  Order ask1(3, Side::SELL, 50, 5000);
  Order ask2(4, Side::SELL, 50, 5000);
  lob.AddOrder(bid1);
  lob.AddOrder(bid2);
  lob.AddOrder(ask1);
  lob.AddOrder(ask2);
  std::size_t matched = lob.MatchOrders();
  EXPECT_EQ(matched, 4u);
  EXPECT_EQ(lob.Bids().size(), 1u);
  EXPECT_EQ(lob.Bids().at(5000).size(), 1u);
  EXPECT_EQ(lob.Bids().at(5000).front().Id(), 2u);
  EXPECT_TRUE(lob.Asks().empty());
}

TEST(LobTest, MatchPricePriority)
{
  Lob lob;
  Order bid1(1, Side::BUY, 100, 4500);
  Order bid2(2, Side::BUY, 100, 5000);
  Order ask(3, Side::SELL, 100, 4800);
  lob.AddOrder(bid1);
  lob.AddOrder(bid2);
  lob.AddOrder(ask);
  std::size_t matched = lob.MatchOrders();
  EXPECT_EQ(matched, 2u);
  EXPECT_EQ(lob.Bids().size(), 1u);
  EXPECT_TRUE(lob.Bids().find(5000) == lob.Bids().end());
  EXPECT_EQ(lob.Bids().at(4500).size(), 1u);
  EXPECT_TRUE(lob.Asks().empty());
}
