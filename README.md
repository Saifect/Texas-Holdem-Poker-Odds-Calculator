Poker Probability Calculator
============================

Status: Stable
Author: Saifect@mail.ru

A console application for calculating poker probabilities using Monte Carlo simulations.

------------------------------------------------
Key Features:
------------------------------------------------
- Interactive console interface (supports Russian and English).
- Customizable simulations (players: 2–12, configurable simulation count).
- Visual feedback: real-time progress bar, game state display, optional colors.
- Optimized performance with a multithreaded simulation engine.

------------------------------------------------
Technologies:
------------------------------------------------
- Language: C++17
- Key Libraries: <Windows.h>, <chrono>, <conio.h>

------------------------------------------------
Installation:
------------------------------------------------
1. Build the project in Visual Studio using the Release configuration.
2. Deploy by copying the contents of the "Release" folder.

------------------------------------------------
Usage Example:
------------------------------------------------
================================================
  Current Game Information                 
================================================
Player 1 Cards: King of Clubs and King of Diamonds
Player 2 Cards: Ace of Hearts and Ace of Spades
Board: None
Stage: Preflop
================================================
  Simulation Settings                
================================================
Simulations: 250,000
Estimated Time: 4.17 sec
[=====================>] 87% (Press Q to quit)
================================================

------------------------------------------------
Contributing:
------------------------------------------------
Contributions are welcome (e.g., algorithm optimizations, GPU acceleration,
additional translations, etc.).

------------------------------------------------
Disclaimer:
------------------------------------------------
For educational purposes only. Not intended for actual poker play.
Supports a maximum of 12 players and up to 100,000,000 simulations.
