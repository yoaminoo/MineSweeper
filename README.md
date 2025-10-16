# 🧨 Minesweeper Clone (Terminal Edition)

A **classic Minesweeper clone** built entirely in **C++**, designed to run directly in your **terminal window**.  
It includes colorful UI borders, a leaderboard system, and a light story mode to make the gameplay more immersive and fun.

---

## 📑 Table of Contents

1. [🎮 Features](#-features)  
2. [🧩 How to Play](#-how-to-play)  
3. [⚙️ Requirements](#️-requirements)  
4. [🧱 How to Build & Run](#-how-to-build--run)
5. [🗺️ Game Flow](#️-game-flow)  
6. [🏆 Leaderboard](#-leaderboard)  
7. [💡 Developer Notes](#-developer-notes)  
8. [📚 Inspiration](#-inspiration)  
9. [🙏 Credits](#-credits)
10. [🧑‍💻 Creator](#-creator)

---

## 🎮 Features

- **Text-based terminal gameplay**
- **Colorful ASCII interface**
- **Customizable grid size and difficulty**
- **Three difficulty levels:** Easy, Normal, Hard  
- **Safe first move** (no bomb on your first click)
- **Recursive reveal system**
- **Leaderboard system** — saves player stats such as:
  - Name  
  - Points (based on bombs)  
  - Time  
  - Moves  
  - Win/Loss result
- **Restart and quit anytime**
- **Simple story and rules presentation**

---

## 🧩 How to Play

| Key | Action |
|-----|---------|
| `Arrow Keys` | Move cursor |
| `O` | Open a cell |
| `F` | Flag/Unflag a cell |
| `Q` | Quit game |
| `R` | Restart game |

**Goal:**  
Reveal all cells that do **not** contain bombs 💣.  
If you open a bomb — **boom**, game over!

---

## ⚙️ Requirements

- C++ compiler (e.g. `g++`)
- Runs on **Windows** (uses `<conio.h>` and `<windows.h>`)
- Console must support **UTF-8** and **ANSI color codes**

---

## 🧱 How to Build & Run

1. Clone or download this repository.  
2. Open a terminal in the project directory.  
3. Compile the program:

   ```bash
   g++ amin_minesweeper.cpp -o minesweeper

    Run the game:

    ./minesweeper
    ```

---

## 🗺️ Game Flow

1. **Launch the game.**  
   Start the executable in your terminal window.

2. **Choose an option from the Main Menu:**
   - 1 → Start a new game  
   - 2 → View leaderboard  
   - 3 → Exit  

3. **Select your difficulty level and board size.**  
   Choose from Easy, Normal, or Hard, then define the height and width of your board.

4. **Make your first move.**  
   Your first move is always safe — no bombs nearby!

5. **Play the game.**  
   Use the arrow keys to move, O to open cells, and F to flag suspected bombs.

6. **Win or lose.**  
   - Reveal all non-bomb cells to **win** 🎉  
   - Open a bomb to **lose** 💥  

7. **Save your result.**  
   After finishing, your score and stats will automatically be saved to the leaderboard.

## 🏆 Leaderboard

After each game, your stats are saved in a leaderboard.txt file:

`NAME POINTS GAMETIME MOVES WON/LOST`

You can view the leaderboard from the main menu to see previous players’ scores.

## 💡 Developer Notes

### The project demonstrates

- Use of structs, dynamic memory allocation, and recursion

- File I/O for leaderboard persistence

- Basic ANSI color codes for styling

    The code is commented to help with understanding.

## 📚 Inspiration

Inspired by classic Minesweeper and the episode "Honor of Kings: The Way of All Things" from Secret Level.

## 🙏 Credits

- [Dr. Kheradpishe](https://github.com/SRKH) (Instructor)
- [Ehsan Habibagaahi](https://github.com/Ehsan-Habibagahi) (Mentor)
- And special thanks to [Parsa](https://github.com/Parsa-Tajik)

## 🧑‍💻 Creator

**Amin** — Creator & Developer

**Contact Me:**
[✉️ E-mail:](asadi.m.a.1385@gmail.com)
