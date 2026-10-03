# Bakery Capitalist

Bakery Capitalist is a C++ console clicker game, based on Adventure Capitalist. Bake loaves, earn cash, and buy new breads with different click requirements and payouts. The game has twelve bread types, saved progress, and a restart option.

## Instructions for Build and Use

### Build

1. Install CMake 3.16 or newer and a compiler that supports C++17.
2. From the project directory, configure the project:

```sh
cmake -S . -B build
```
3. Build the executable:

```sh
cmake --build build --config Release
```

### Run

1. Run the executable from the project directory so that the save file is read and written there.
2. On Windows with the Visual Studio CMake generator, run:

```powershell
.\build\Release\bakery_capitalist.exe
```

	For a single-configuration generator on Windows, run `.build\bakery_capitalist.exe`. On Linux or macOS, run:

```sh
./build/bakery_capitalist
```

3. Enter `1` to bake. Each loaf takes multiple clicks; completing it earns the displayed bread's payout.
4. Enter `2` to choose an unlocked bread, `3` to buy a bread, or `4` to save.
5. Enter `5` to restart with zero cash and only Classic White Bread unlocked, or `6` to quit. The game loads `bakery_save.txt` at startup and saves on quit; restart saves the reset immediately.

## Development Environment

The project uses standard C++17 and CMake 3.16 or newer. No third-party libraries are required. It was built and tested with Microsoft Visual C++ 19.51 (Visual Studio 18 Community); another C++17-compatible compiler can be used with CMake.

## Requirements Demonstrated

1. **Conditionals:** menu choices, purchase checks, and bread unlock validation.
2. **Loops:** the main game loop and input-validation loop.
3. **Functions:** actions such as `bakeClick`, `buyBread`, and `saveGame` are separate functions.
4. **Classes:** `BakeryGame` and the bread classes organize game state and behavior.
5. **STL data structure:** `std::vector` stores the bread catalog and unlocked states.

### Stretch Challenge

`BreadType` is an abstract base class with virtual `description()`. The twelve bread types inherit from it and override that function. The game stores them polymorphically in a `std::vector<std::unique_ptr<BreadType>>`.

## Bread Types

Each loaf requires the listed number of clicks to bake. Purchased breads remain unlocked for the rest of the game.

| Bread | Clicks per loaf | Purchase cost | Payout per loaf |
| --- | ---: | ---: | ---: |
| Classic White Bread | 5 | Free | $8.00 |
| Sourdough | 8 | $60.00 | $22.00 |
| Cinnamon Roll | 12 | $180.00 | $45.00 |
| Golden Baguette | 18 | $450.00 | $90.00 |
| Rye Bread | 25 | $1,000.00 | $210.00 |
| Soft Pretzel | 32 | $2,200.00 | $340.00 |
| Herb Focaccia | 40 | $4,500.00 | $520.00 |
| Brioche | 50 | $9,000.00 | $800.00 |
| Croissant | 65 | $18,000.00 | $1,250.00 |
| Everything Bagel | 80 | $35,000.00 | $1,900.00 |
| Multigrain Bread | 100 | $65,000.00 | $2,900.00 |
| Chocolate Babka | 125 | $120,000.00 | $4,500.00 |

## Useful Websites to Learn More

* [C++ reference](https://en.cppreference.com/w/)
* [CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

## Future Work

* [ ] Save automatically after each loaf is sold or bread is purchased.
* [ ] Add bakery upgrades that change baking speed or payouts.
* [ ] Add a confirmation prompt before restarting and clearing progress.