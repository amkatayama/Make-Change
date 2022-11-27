# Make-Change
Create 3 different algorithms for making change (MC)

## Table of Contents
1. [Problem Definition](#problem-definition)
2. [Design](#design)
3. [Development](#development)
4. [Evaluation](#evaluation)

## Problem Definition

The main problem for this project is making change for a given amount with the fewest possible coins, using a given set of possible coin values.
Example inputs and outputs: 

**Example 1:**
> input1: target = 10, coins_val = [1, 5] </br>
> output1: 2 (2 nickels make up 10)

**Example 2:**
> input2: target = 35, coins_val = [1, 5, 10] </br>
> output2: 4 (3 dimes and 1 nickel)

The coin values can be passed a non-coin value (e.g., 4, 17), and the program should still return the optimal number of coins that can be used to make change for target amount. 

## Design

### Greedy Algorithm

The greedy algorithm takes the best option possible at that moment and returns a solution. A simple greedy algorithm of this MC problem will: <br/> 
1. Get the largest coin that is smaller than the current target 
2. Keep updating target and keep count until target reaches 0

Pseudocode: 
```
count = 0
while target > 0
  c = larget coin value < current target
  count ++
  target -= c
```

To find the largest coin value within the range of the current target, we will need another loop which iterates through the coin_val array. 

### Recursion (with Memoization)

The recursive algorithm for MC uses a table to store returned values to be reused in  

### Dynamic Programming

## Development 
## Evaluation
