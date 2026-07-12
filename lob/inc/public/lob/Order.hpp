#ifndef LOB_ORDER_HPP
#define LOB_ORDER_HPP

#include "lob/Definition.hpp"
#include "lob/lob_export.h"

/**
 * @brief Represents a single order in the limit order book.
 *
 * An order carries an ID, side (BUY/SELL), price, quantity, and
 * tracks how much has been filled.
 */
class LOB_EXPORT Order
{
public:
  /**
   * @brief Construct a new Order.
   * @param id       Unique order identifier.
   * @param side     BUY or SELL.
   * @param quantity Number of shares.
   * @param price    Price in cents.
   */
  Order(const ::ID& id, const ::Side& side, const ::Quantity& quantity, const ::Price& price);

  /** @brief Copy construct. */
  Order(const Order& order);

  /** @brief Copy assign. */
  Order& operator=(const Order& order);

  /** @brief Move construct. */
  Order(const Order&& order);

  /** @brief Move assign. */
  Order& operator=(const Order&& order);

  /** @brief Destructor. */
  ~Order();

  /** @return The order ID (const). */
  const ID& Id() const;
  /** @return The order ID. */
  const ID& Id();
  /** @return The order side (const). */
  const ::Side& Side() const;
  /** @return The order side. */
  const ::Side& Side();
  /** @return The total quantity (const). */
  const ::Quantity& Quantity() const;
  /** @return The total quantity. */
  const ::Quantity& Quantity();
  /** @return The order price (const). */
  const ::Price& Price() const;
  /** @return The order price. */
  const ::Price& Price();
  /** @return The filled quantity (const). */
  const ::Quantity& Filled() const;
  /** @return The filled quantity. */
  const ::Quantity& Filled();
  /** @return True if the order is fully filled (const). */
  const bool IsFileed() const;
  /** @return True if the order is fully filled. */
  const bool IsFileed();
 
  /**
   * @brief Fill (partially) the order.
   * @param filled Number of shares to fill.
   * @return True if the fill succeeded.
   */
  const bool Fill(const ::Quantity& filled);
private:
  ID m_id;
  ::Side m_side;
  ::Quantity m_quantity;
  ::Price m_price;
  ::Quantity m_filled;
};

inline const ID& Order::Id() const 
{ 
  return m_id; 
}

inline const ID& Order::Id()
{ 
  return m_id; 
}

inline const ::Side& Order::Side() const 
{ 
  return m_side; 
}

inline const ::Side& Order::Side()
{ 
  return m_side; 
}

inline const ::Quantity& Order::Quantity() const 
{ 
  return m_quantity; 
}

inline const ::Quantity& Order::Quantity()
{ 
  return m_quantity; 
}

inline const ::Price& Order::Price() const 
{ 
  return m_price; 
}

inline const ::Price& Order::Price()
{ 
  return m_price; 
}

inline const ::Quantity& Order::Filled() const 
{ 
  return m_filled; 
}

inline const ::Quantity& Order::Filled()
{ 
  return m_filled; 
}

inline const bool Order::IsFileed() const
{
  return m_quantity == m_filled;
}

inline const bool Order::IsFileed()
{
  return m_quantity == m_filled;
}
 

#endif //!LOB_ORDER_HPP
