# AGENTS.md

## Build

```bash
cmake -B build -S .
cmake --build build
```

## Run tests

```bash
./build/test/LOBTests
```

## Run simulation

```bash
./build/simulation/simulation
```

## Generate documentation

Requires Doxygen and Graphviz. On Debian/Ubuntu:

```bash
sudo apt update && sudo apt install doxygen graphviz
```

```bash
cmake --build build --target docs
```

Output: `build/docs/html/index.html`

## Project layout

- `lob/` -- core library (`liblob` static library)
  - `inc/public/lob/` -- public headers
  - `src/` -- implementation files
- `simulation/` -- randomized market demo
- `test/` -- GoogleTest unit tests
- `docs/` -- Doxygen documentation config

## Conventions

- C++17, no compiler extensions (`CMAKE_CXX_EXTENSIONS OFF`)
- Public headers under `lob/inc/public/lob/`
- `LOB_EXPORT` macro on public classes for shared library visibility
- GoogleTest is fetched via CMake FetchContent (no manual install needed)
