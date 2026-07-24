#include "LadderOperator.hpp"
#include "OperatorChain.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

int main() {

  Index index1("a", Ladder::IndexType::core);
  Index index2("v", Ladder::IndexType::valence);
  Index index3("n", Ladder::IndexType::excited);

  LadderOperator operator1 =
      LadderOperator(Ladder::LadderType::creation, index1);
  LadderOperator operator2 =
      LadderOperator(Ladder::LadderType::annihilation, index2);
  LadderOperator operator3 =
      LadderOperator(Ladder::LadderType::creation, index3);

  OperatorChain test_chain = OperatorChain(
      std::vector<LadderOperator>{operator3, operator3, operator3, operator3,
                                  operator3, operator1, operator2});

  // operator1.printHoleParticleType();

  test_chain.print_HPform();
  std::cout << std::endl << std::endl;

  test_chain.is_in_normal_order();
  std::cout << std::endl;

  return 0;
}