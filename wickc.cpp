#include "LadderOperator.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

int main() {

  Index index;
  index.setIndex("i");

  LadderOperator operator1 =
      LadderOperator(index, LadderType::creation, IndexType::any);

  operator1.getInfo();

  return 0;
}