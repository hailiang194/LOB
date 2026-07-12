#include "lob/Definition.hpp"
#include "lob/Lob.hpp"
#include "lob/Order.hpp"
#include <iostream>
#include <random>

int main()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  Price midPrice = 340000;
  std::uniform_int_distribution<int> sideDist(0, 1);
  std::uniform_int_distribution<int> eventDist(0, 9);
  std::uniform_int_distribution<Quantity> quantityDist(100, 1000);
  std::uniform_int_distribution<Price> spreadDist(1, 50);
  std::uniform_int_distribution<Price> depthDist(0, 100);
  Lob lob;

  for(std::size_t i = 0; i < 100; ++i)
  {
    std::cout << "\n--- Tick " << i << " (mid=" << midPrice << ") ---" << std::endl;
    int event = eventDist(gen);
    if(event < 7)
    {
      Side side = static_cast<Side>(sideDist(gen));
      Price offset = spreadDist(gen) + depthDist(gen);
      Price price = (side == Side::BUY) ? midPrice - offset : midPrice + offset;
      Order order(
          static_cast<ID>(i), 
          side,
          quantityDist(gen),
          price
          );
      lob.AddOrder(order);
      std::cout << "  + Added " << (order.Side() == Side::BUY ? "BUY " : "SELL")
        << " id=" << order.Id()
        << " px=" << order.Price()
        << " qty=" << order.Quantity() << std::endl;
    }
    else
    {
      int drift = static_cast<int>(spreadDist(gen)) - 25;
      if(drift > 0 || midPrice > static_cast<Price>(-drift))
        midPrice += drift;
      std::cout << "  ~ Mid price drifted to " << midPrice << std::endl;
    }
    Quantity filled = lob.MatchOrders();
    if(filled > 0)
      std::cout << "  >> MATCHED " << filled << " order(s)" << std::endl;
  }

  std::cout << "\n=== ORDER BOOK ===" << std::endl;
  std::cout << "=== BIDS (best first) ===" << std::endl;
  for(const auto& [price, orders] : lob.Bids())
  {
    Quantity volume = 0;
    for(const auto& order : orders)
    {
      volume += order.Quantity();
    }
    std::cout << "  " << price << " | " << volume << " (" << orders.size() << " order(s))" << std::endl;
  }

  std::cout << "=== ASKS (best first) ===" << std::endl;
  for(const auto& [price, orders] : lob.Asks())
  {
    Quantity volume = 0;
    for(const auto& order : orders)
    {
      volume += order.Quantity();
    }
    std::cout << "  " << price << " | " << volume << " (" << orders.size() << " order(s))" << std::endl;
  }

  return 0;
}
