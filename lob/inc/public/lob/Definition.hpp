#ifndef LOB_DEFINITION_HPP
#define LOB_DEFINITION_HPP

#include <cstddef>
#include <cstdint>

/** @brief Price type in cents. */
using Price = std::uint32_t;

/** @brief Quantity type representing number of shares. */
using Quantity = std::size_t;

/** @brief Unique order identifier. */
using ID = std::uint64_t;

/** @brief Order side enumeration. */
enum class Side: int
{
  BUY,   ///< Buy order
  SELL   ///< Sell order
};

#endif //!LOB_DEFINITION_HPP
