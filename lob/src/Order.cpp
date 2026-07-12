#include "lob/Order.hpp"


Order::Order(const ID& id, const ::Side& side, const ::Quantity& quantity, const ::Price& price)
  :m_id(id), m_side(side), m_quantity(quantity), m_price(price), m_filled(0)
{

}

Order::Order(const Order& order)
  :m_id(order.m_id), m_side(order.m_side), m_quantity(order.m_quantity), m_price(order.m_price), m_filled(order.m_filled)
{

}

Order& Order::operator=(const Order& order)
{
  m_id = order.m_id;
  m_side = order.m_side;
  m_quantity = order.m_quantity;
  m_price = order.m_price;
  m_filled = order.m_filled;
  return (*this);
}

Order::Order(const Order&& order)
  :m_id(order.m_id), m_side(order.m_side), m_quantity(order.m_quantity), m_price(order.m_price), m_filled(order.m_filled)
{

}

Order& Order::operator=(const Order&& order)
{
  m_id = order.m_id;
  m_side = order.m_side;
  m_quantity = order.m_quantity;
  m_price = order.m_price;
  m_filled = order.m_filled;
  return (*this);
}

Order::~Order()
{

}

const bool Order::Fill(const ::Quantity& filled)
{
  ::Quantity remain = m_quantity - m_filled;
  if(remain < filled)
    return false;

  m_filled += filled;
  return true;
}
