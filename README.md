# Battleship Simulator

This repository contains a C++ program that simulates the game "Battleship." The game consists of a 10x10 grid where 10 ships of varying sizes (one to four squares) are placed horizontally or vertically. The objective is to sink all ships by launching "bombs" at specific grid coordinates.

### Authors:
- **Franco Nicolas Bottini**
- **Valentin Robledo**

## Game Strategies

### Queueing Strategies
The program simulates three queueing strategies for targeting positions to shoot at:

1. **Sequential Row Queueing (SRQ):** Queues positions sequentially by rows.
2. **Sequential Column Queueing (SCQ):** Queues positions sequentially by columns.
3. **Random Queueing (RQ):** Queues positions in a completely random order.

### Shooting Algorithms
The program also simulates three shooting algorithms:

1. **No Memory (NM):** The shooting algorithm has no "memory" of previously targeted positions, allowing multiple shots on the same square.
2. **With Memory (WM):** The shooting algorithm remembers previously targeted positions, avoiding repeated shots on the same square.
3. **Complete (C):** In addition to remembering positions, this shooting algorithm avoids targeting squares adjacent to a ship, adhering to game rules.

## Results and Conclusions
A total of 10,000 simulations were conducted for each combination of queueing strategy and shooting algorithm. The results are presented graphically in the `informe.pdf` file. In conclusion, row and column queueing strategies show similar performance. Additionally, the complete shooting algorithm proves to be the most efficient, regardless of the queueing strategy used. The most effective combination is the complete sequential queueing strategy (either by rows or columns).
