/* TUFTS COMP 160
 * David Wilson */

#include <iostream>
#include <vector>
#include <algorithm>
#include "randSelect.h"

int main() {
  
  std::vector<int> test = {0, -43, 129, 21, 100, -50, -60, 70, -80, 100};
  int wantedRank = 3;
  int gotValue = randSelect(test, wantedRank);
  std::sort(test.begin(), test.end());
  int expected = test[wantedRank];

  if (expected != gotValue) {
    std::cout << "Nooo!\n";
  } else {
    std::cout << "Yayy!\n";
  }

  return 0;
}
