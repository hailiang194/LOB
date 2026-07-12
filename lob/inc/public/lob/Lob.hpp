#ifndef LOB_LOB_H
#define LOB_LOB_H

#include <deque>
#include <functional>
#include <map>
#include <unordered_map>

#include "lob/Definition.hpp"
#include "lob/Order.hpp"
#include "lob/lob_export.h"

/** @brief Map of price -> queue of orders, parameterised by comparator. */
template<typename Compare>
using OrderMap = std::map<Price, std::deque<Order>, Compare>;

/** @brief Bids side: highest price first. */
using BidsMap = OrderMap<std::greater<Price>>;

/** @brief Asks side: lowest price first. */
using AsksMap = OrderMap<std::less<Price>>;

/**
 * @brief Limit Order Book engine.
 *
 * Maintains bid and ask sides, supports add/modify/cancel and
 * price-time priority matching.
 */
class LOB_EXPORT Lob
{
public:
  /** @brief Construct an empty order book. */
  Lob();

  /** @brief Destructor. */
  ~Lob();

  Lob(const Lob&) = delete;
  Lob& operator=(const Lob&) = delete;
  Lob(Lob&&) = delete;
  Lob& operator=(Lob&&) = delete;

  /** @return Const reference to the bids map. */
  const BidsMap& Bids(); 
  /** @return Const reference to the asks map. */
  const AsksMap& Asks(); 

  /**
   * @brief Add a new order to the book.
   * @param order The order to add.
   * @return True if the order was added successfully.
   */
  bool AddOrder(const Order& order);

  /**
   * @brief Modify an existing order (cancel + re-add).
   * @param order The replacement order (same ID).
   * @return True if the modification succeeded.
   */
  bool ModifyOrder(const Order& order);

  /**
   * @brief Cancel an order by ID.
   * @param id The order ID to cancel.
   * @return True if the order was found and cancelled.
   */
  bool CancelOrder(const ID& id);

  /**
   * @brief Match outstanding orders using price-time priority.
   * @return Number of shares matched.
   */
  std::size_t MatchOrders();

private:
  BidsMap m_bids;
  AsksMap m_asks;
  std::unordered_map<ID, Order*> m_orders; 
};

inline const BidsMap& Lob::Bids()
{
  return m_bids;
}

inline const AsksMap& Lob::Asks()
{
  return m_asks;
}


#endif // !LOB_LOB_H
