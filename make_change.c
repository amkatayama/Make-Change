// Created by Arata Katayama 11/10/2022
// Collaborators: Professor and 3 other peers (Hidden for confidentiality)

#include <stdio.h>
#include <limits.h>

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
  // printf("%d %d \n" ,val, table[val]);
  return min;
}


int dyn_prog(int val, int* coins, int n, int* table, int* sol) {
  // printf("i t s\n");
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
      
      // printf("%d %d %d\n",i, table[i], sol[i]);
      // printf("when the change is %d, the minimum number coins that can be used is %d\n", i, table[i]);
    }
    return table[val];
}

void print_sol(int val, int* sol) {
  printf("Solution: ");
  while (val > 0) {
    printf("%d ", sol[val]);
    val -= sol[val];
  }
  printf("\n");
}

int main(int argc, char** argv) {
  int n = argc - 2;
  int val;
  sscanf(argv[argc-1], "%d", &val);
  int coins[n];

  for(int i=0; i < n; i++) {
    sscanf(argv[i+1], "%d", &coins[i]);
  }

  printf("Making change for %d.\n", val);

  int res;

  res = greedy(val, coins, n);

  if(res != -1) {
	printf("Greedy found change using %d coins.\n", res);
  } else {
	printf("Greedy could not find change.\n");
  }
  //
  int table[val+1];
  for(int i=0; i < val+1; i++) {
	table[i] = -1;
  }
  table[0] = 0;
  res = divide_and_conquer(val, coins, n, table);

  if(res != -1) {
	printf("Divide & conquer found change using %d coins.\n", res);
  } else {
	printf("Divide & conquer could not find change.\n");
  }

  int sol[val+1];
  for(int i=0; i < val+1; i++) {
	table[i] = -1;
	sol[i] = -1;
  }
  table[0] = 0;
  sol[0] = 0;

  res = dyn_prog(val, coins, n, table, sol);

  if(res != -1) {
	printf("Dynamic programming found change using %d coins.\n", res);
	print_sol(val, sol);
  } else {
	printf("Dynamic programming could not find change.\n");
  }
}
