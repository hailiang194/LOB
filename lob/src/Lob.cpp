#include "lob/Lob.hpp"
#include "lob/Definition.hpp"
#include <algorithm>


Lob::Lob()
  :m_bids(), m_asks(), m_orders()
{
}

Lob::~Lob()
{
}


bool Lob::AddOrder(const Order& order)
{
  switch(order.Side())
  {
    case ::Side::BUY:
      m_bids[order.Price()].push_back(order);
      m_orders.insert({ order.Id(), &m_bids[order.Price()].back() });
      break;
    case ::Side::SELL:
      m_asks[order.Price()].push_back(order);
      m_orders.insert({ order.Id(), &m_asks[order.Price()].back() });
      break;
    default:
      return false;
  }
  return true;
}

bool Lob::ModifyOrder(const Order& order)
{
  return CancelOrder(order.Id()) && AddOrder(order);
}

bool Lob::CancelOrder(const ID& id)
{
  std::unordered_map<ID, Order*>::iterator it = m_orders.find(id);
  if (it == m_orders.end())
    return false;

  Order* order = it->second;
  Price price = order->Price();
  ::Side side = order->Side();

  std::deque<Order>* deque = nullptr;
  if (side == ::Side::BUY)
  {
    BidsMap::iterator mapIt = m_bids.find(price);
    if (mapIt == m_bids.end())
      return false;
    deque = &mapIt->second;
    for (std::deque<Order>::iterator dit = deque->begin(); dit != deque->end(); ++dit)
    {
      if (dit->Id() == id)
      {
        deque->erase(dit);
        break;
      }
    }
    for (size_t i = 0; i < deque->size(); ++i)
      m_orders[(*deque)[i].Id()] = &(*deque)[i];
    if (deque->empty())
      m_bids.erase(mapIt);
  }
  else
  {
    AsksMap::iterator mapIt = m_asks.find(price);
    if (mapIt == m_asks.end())
      return false;
    deque = &mapIt->second;
    for (std::deque<Order>::iterator dit = deque->begin(); dit != deque->end(); ++dit)
    {
      if (dit->Id() == id)
      {
        deque->erase(dit);
        break;
      }
    }
    for (size_t i = 0; i < deque->size(); ++i)
      m_orders[(*deque)[i].Id()] = &(*deque)[i];
    if (deque->empty())
      m_asks.erase(mapIt);
  }

  m_orders.erase(it);
  return true;
}


std::size_t Lob::MatchOrders()
{
  Quantity matched = 0x0;
  while(true)
  {
    if(m_bids.empty() || m_asks.empty())
      return matched;

    BidsMap::iterator lowestBid = m_bids.begin();
    AsksMap::iterator highestAsk = m_asks.begin();
    if(lowestBid-> first < highestAsk->first)
      break;
    
    while(!lowestBid->second.empty() && !highestAsk->second.empty())
    {
      Order& bidOrder = lowestBid->second.front();
      Order& askOrder = highestAsk->second.front();

      Quantity filled = std::min(
          bidOrder.Quantity() - bidOrder.Filled(), 
          askOrder.Quantity() - askOrder.Filled());
      if(!bidOrder.Fill(filled) || !askOrder.Fill(filled))
        continue;
      
      matched += 2;
      if(bidOrder.IsFileed())
      {
        ID bidId = bidOrder.Id();
        lowestBid->second.pop_front();
        m_orders.erase(bidId);
      }
      if(askOrder.IsFileed())
      {
        ID askId = askOrder.Id();
        highestAsk->second.pop_front();
        m_orders.erase(askId);
      }
    }

    if(lowestBid->second.empty())
    {
      m_bids.erase(lowestBid);
    }
    if(highestAsk->second.empty())
    {
      m_asks.erase(highestAsk);
    }
  }
  return matched;
}
