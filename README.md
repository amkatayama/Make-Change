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
> input1: target = 10, coins_val = [5, 1] </br>
> output1: 2 (2 nickels make up 10)

**Example 2:**
> input2: target = 35, coins_val = [10, 5, 1] </br>
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
input: target=8, coins_val=[5, 4, 1]
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

Dynamic Programming is also known as the bottom-up approach, and in MC, we are going to build a table containing the optimal solutions of subproblems. 
```
input: target=8, coins_val=[5, 4, 1]
table: 
i   count 
1     1
2     2
3     3
4     1
5     1
6     2
7     3
8     2
output: 2 (2 fours)
```
In this is example, it first calculates the optimal solution if the target was 1. Then it uses this value, to calculate the optimal solution of target 2. However, when the optimal solution is smaller than the one derived from previous solution, it updates the table value to the optimal solution. By the time it returns the solution for the actual target, the table would contain an optimal solution for every subtarget value smaller than the actual target value. 
Here is the pseudocode for this algorithm:
```
table.length = target 
for i from 0 to table.length 
  for j in coin_vals 
    if j < i
      break 
    else if j == coin_vals
      table[i] = 1  
    else 
      if (table[i] has no sol) or (1 + table[i-j] < ]table[i])
        table[i] = 1 + table[i-j]

return table[target]
```

## Development 
### Greedy Algorithm 

```c
int greedy(int val, int* coins, int n) {

    int score = 0;
    int i = 0;

    while (val > 0) {
        // making sure i never gets out of index
        while (i < n-1 && coins[i] > val) {
            i++;
        }
        val -= coins[i];
        score += 1;
    }
    // score is returned only if exact change can be made
    if (val == 0) {
        return score;
    }
    return -1;
}
```

The greedy algorithm turned out to work almost flawlessly based on the pseudocode above. In the while loop inside the outer loop, I am checking for every coin value that is smaller than the target. If the coin value is bigger than the target, then that coin cannot be used in the first place, hence we `i++`, and do nothing else. In my previous version of this algorothm, I had my inner while loop as below:
```c
// making sure i never gets out of index
while (coins[i] > val) {
  i++;
}
```
This was working almost flawlessly until I found a case where it did not work. The reason this was happening was because whenever `coins[last_index] > val` was called, `last_index + 1` is out of range. To solve this problem, I added one condition, `i < n-1` in the while loop to prevent from indexing out of range. This solved the error, and `int greedy` now works well. </br>

One important thing to note about this greedy algorithm for MC, is that it doesn't necessarily give us an optimal solution. Here is an example: 
```
input: target = 8, coins_val=[5, 4, 1]

demonstration: 
1. new_target = 8-5 = 3,  coin_count = 1
2. new_target = 3-1 = 2,  coin_count = 2 
3. new_target = 2-1 = 1,  coin_count = 3
3. new_target = 1-1 = 0,  coin_count = 4

output: 4, sol=[5, 1, 1, 1]
```
The output when processing the input above is a 4

### Divide and Conquer with Memoization 
```c
int divide_and_conquer(int val, int* coins, int n, int* table) {


    if (val == 0) {
        return 0;
    }
    // memoization
    if (table[val] != -1) {
        return table[val];
    }
    int min = -1;
    for (int i = 0; i < n; i++) {
        if (coins[i] > val) {
            continue;  // if coin value is bigger continue to the next coin value in array
        }
        int r = divide_and_conquer(val-coins[i], coins, n, table);
        // update m if there is not yet a sol or this is a better sol
        // check if the last recursive call returned a sol
        if (r != -1) {
            if (min == -1 || (min != -1 && r < min)) {
                min = r+1;
            }
        }
    }

    table[val] = min;
    return min;
}
```

### Dynamic Programming 

```c
int dyn_prog(int val, int* coins, int n, int* table, int* sol) {

    for (int i = 1; i < val+1; i++) {
        // looking through coins from smallest
        for (int j = n-1; j >= 0; j--) {
            // break if coin is bigger than the value
            if (i == coins[j]) {
                table[i] = 1;
                sol[i] = coins[j];
                break;
            } else if (coins[j] > i) {
                break;
            }

            // update table if no sol is found or
            if (table[i] == -1 || (table[i] != -1 && (1 + table[i-coins[j]] < table[i])))  {
                if (table[i-coins[j]] == -1) {
                    continue;
                }
                table[i] = 1 + table[i-coins[j]];
                // update solVal when ever table[i] is also updated
                // if it doesn't use that coin then get the largest used coin value
                sol[i] = sol[i-coins[j]];
            }


        }
    }

    return table[val];
}
```

## Evaluation
