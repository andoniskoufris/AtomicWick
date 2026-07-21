#include "OperatorChain.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

int main()
{

  Index index1;
  Index index2;
  index1.setIndexString("i");
  index2.setIndexString("j");
  index1.setIndexType(IndexType::any);
  index2.setIndexType(IndexType::any);

  LadderOperator operator1 = LadderOperator(LadderType::creation, index1);
  LadderOperator operator2 = LadderOperator(LadderType::annihilation, index2);

  operator1.getInfo();
  operator2.getInfo();

  OperatorChain test_chain =
      OperatorChain(std::vector<LadderOperator>{operator1, operator2});

  return 0;
}