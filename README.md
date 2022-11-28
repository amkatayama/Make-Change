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

The recursive algorithm for MC uses a table to store and reuse returned values (memoization). To be more specific here is a demonstration of a non-memoized purely recursive algorithm:

```
input: target=8, coins_val=[1,4,5]
output: 2 (2 fours)
```
<img width="740" alt="Screen Shot 2022-11-27 at 19 22 19" src="https://user-images.githubusercontent.com/113309314/204168010-110b2e35-3a36-455f-97fe-f97b553bb085.png">
Fig.1: Recursion tree for non-memoized aproach </br></br>

Note that in Fig.1, the node 4 in the left bottom would have more nodes, if not for  the limit in how many items I could add in free version of LucidChart. Here we can see that a lot of the same nodes exist, for example 3. For a subtarget of 3, a coin of value 1 can be used three times. This same recursive call is being done three different times, as demonstrated in Fig.1. Fig.2 shows a recursive tree of the memoized version:

<img width="652" alt="Screen Shot 2022-11-27 at 20 07 02" src="https://user-images.githubusercontent.com/113309314/204171084-ea28a134-a50a-4d9a-b18e-21017d2290bb.png">
Fig.2: Recursing tree for memoized approach </br></br>

In Fig.2, we can see that there is less recursive call than Fig.1. This is because the optimal solution for the subtargets is being memoized (stored in a table), so that when the same value is encountered later in its execution it can refer back to the table. Here is a brief pseudocode: 

```
func divideAndConquer(target, table, coins_val)
  if target == 0
    return 0
  else if table contains target
    return table[target]
  
  min = infinity
  for i from 0 to coins_val.length
    sol = divideAndConquer(target-i, table, coins_val, c+1)
    if (table[target] does not contain value) or (sol < min)
      min = sol + 1

   table[target] = sol
   
   return min
```

### Dynamic Programming



## Development 
## Evaluation
