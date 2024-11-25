# Project Structure

A simple AI-generated overview of the project structure.

---

## Root Directory
- **`CMakeLists.txt`**: The primary CMake configuration file for the project.
- **`LICENSE.txt`**: License information for the project.
- **`README.md`**: Documentation and introduction to the project.

---

## Subdirectories

### 1. **`board/`**
Handles board-related functionality.

- **`CMakeLists.txt`**: Build configuration for the board module.
- **`include/`**: Header files:
    - `board.h`: Core board structure and logic.
    - `board_serializer.h`: Serialization logic for the board state.
- **`src/`**: Source files:
    - `board.c`: Implementation of board logic.
    - `board_serializer.c`: Implementation of serialization functionality.

---

### 2. **`connect_four_core/`**
Core logic for the Connect-Four game.

- **`CMakeLists.txt`**: Build configuration for the core module.
- **`include/`**: Header files:
    - `game_context.h`: Defines the game context structure.
    - `game_context_serializer.h`: Handles game context serialization.
    - `game_functionality.h`: Core game rules and logic.
    - `game_state.h`: State management for the game.
    - `save_system.h`: Handles saving and loading of game data.
- **`src/`**: Source files:
    - `game_context.c`, `game_context_serializer.c`, `game_functionality.c`, `game_state.c`, `save_system.c`: Implementations of the respective header files.

---

### 3. **`connect_four_game/`**
Executable entry point for the game.

- **`CMakeLists.txt`**: Build configuration for the game executable.
- **`src/`**: Source files:
    - `main.c`: Entry point for the application.

---

### 4. **`error_handling/`**
Manages error codes and handling.

- **`CMakeLists.txt`**: Build configuration for error handling.
- **`include/`**: Header files:
    - `error_codes.h`: Definitions of error codes used across the project.

---

### 5. **`tests/`**
Unit tests for the project.

- **`CMakeLists.txt`**: Build configuration for tests.
- **`src/`**: Test files:
    - `test_board.c`: Tests for board logic.
    - `test_board_serializer.c`: Tests for board serialization.
    - `test_game_context_serializer.c`: Tests for game context serialization.
    - `test_game_state.c`: Tests for game state management.
    - `test_id_generator.c`: Tests for the ID generator utility.
    - `test_string_utility.c`: Tests for string utilities.

---

### 6. **`utility/`**
Utility functions used throughout the project.

- **`CMakeLists.txt`**: Build configuration for utilities.
- **`include/`**: Header files:
    - `id_generator.h`: Utility for generating unique IDs.
    - `io_utility.h`: Input/output-related utilities.
    - `string_utility.h`: String manipulation utilities.
- **`src/`**: Source files:
    - `id_generator.c`, `io_utility.c`, `string_utility.c`: Implementations of respective utilities.