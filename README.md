# LOB

A C++17 Limit Order Book implementation for simulating financial exchange order matching.

## Features

- **Add / Modify / Cancel** orders by side (BUY/SELL), price, and quantity
- **Price-time priority matching engine** -- matches best bid against best ask, supports partial fills
- **O(1) order lookup** by ID via hash map index
- Header-only-style public API with a static library (`liblob`)
- Zero external dependencies (GoogleTest fetched automatically for tests only)

## Types

| Alias     | Underlying     | Unit    |
|-----------|----------------|---------|
| `Price`   | `uint32_t`     | cents   |
| `Quantity`| `size_t`       | shares  |
| `ID`      | `uint64_t`     | --      |
| `Side`    | `enum class`   | BUY/SELL|

## Building

Requires CMake 3.10+ and a C++17 compiler.

```bash
cmake -B build -S .
cmake --build build
```

### Targets

| Target       | Description                  |
|--------------|------------------------------|
| `lob`        | Static library               |
| `simulation` | Randomized market simulation |
| `LOBTests`   | Unit tests (GoogleTest)      |
| `docs`       | API documentation (Doxygen)  |

### Documentation

Requires Doxygen and Graphviz. On Debian/Ubuntu:

```bash
sudo apt update && sudo apt install doxygen graphviz
```

Then build the docs target:

```bash
cmake --build build --target docs
```

Output will be in `build/docs/html/index.html`.

## Running

```bash
# Run the simulation
./build/simulation/simulation

# Run the tests
./build/test/LOBTests
```

## Project Structure

```
LOB/
├── CMakeLists.txt
├── lob/                    # Core library
│   ├── inc/public/lob/     # Public headers
│   │   ├── Definition.hpp  # Type aliases and Side enum
│   │   ├── Order.hpp       # Order class
│   │   └── Lob.hpp         # Limit Order Book class
│   └── src/
│       ├── Order.cpp
│       └── Lob.cpp
├── simulation/             # Demo simulation executable
│   └── src/main.cpp
├── test/                   # Unit tests
│   ├── OrderTest.cpp
│   └── LobTest.cpp
└── docs/                   # Doxygen documentation config
    ├── CMakeLists.txt
    └── Doxyfile.in
```

## API

```cpp
Lob lob;

lob.AddOrder(Order(id, Side::BUY, quantity, price));
lob.ModifyOrder(Order(id, Side::BUY, newQty, newPrice));
lob.CancelOrder(id);

size_t matched = lob.MatchOrders();

const BidsMap& bids = lob.Bids();  // std::map<Price, deque<Order>, std::greater>
const AsksMap& asks = lob.Asks();  // std::map<Price, deque<Order>, std::less>
```

## License

MIT
