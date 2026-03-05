# Lowest-Frequency Dice Betting Game (C)

Interactive dice simulation written in C that tests a lowest-frequency betting strategy based on the gambler’s fallacy.

## Idea

Players often believe outcomes that appear less frequently are “due” to occur soon.  
This program explores that belief using a fair six-sided die.

The game tracks how many times each face has appeared and allows the user to bet on the number that has appeared the least often.

## Game Rules

1. Choose the total number of rolls.
2. The program rolls a fair die and keeps a tally for each face (1–6).
3. When a **unique lowest-frequency face** appears, the program asks if you want to bet on it.
4. If multiple faces are tied for lowest, you may choose one of them or hold.
5. Profit per roll:
   - +$1 if the roll matches your bet
   - -$1 otherwise

The game stops after the chosen number of rolls and prints the final profit or loss.

## What this demonstrates

This project explores whether betting on the least frequently rolled number creates an advantage.

Because each die roll is independent, this strategy should **not** produce a long-term edge.

## Build and run

Compile:

dcc src/dice_game.c -o dice_game

Run:

./dice_game


## Concepts explored

- Probability and independence
- Simulation
- Empirical frequency vs true probability
- Gambler’s fallacy
