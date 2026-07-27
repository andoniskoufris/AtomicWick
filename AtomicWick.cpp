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
  Index index4("b", Ladder::IndexType::core);
  Index index5("m", Ladder::IndexType::excited);
  Index index6("r", Ladder::IndexType::excited);

  LadderOperator operator1 =
      LadderOperator(Ladder::LadderType::creation, index1);
  LadderOperator operator2 =
      LadderOperator(Ladder::LadderType::annihilation, index2);
  LadderOperator operator3 =
      LadderOperator(Ladder::LadderType::creation, index3);
  LadderOperator operator4 =
      LadderOperator(Ladder::LadderType::annihilation, index4);
  LadderOperator operator5 =
      LadderOperator(Ladder::LadderType::creation, index5);
  LadderOperator operator6 =
      LadderOperator(Ladder::LadderType::annihilation, index6);

  OperatorChain test_chain = OperatorChain(std::vector<LadderOperator>{
      operator1, operator2, operator3, operator4, operator5, operator6});
  std::cout << "Before normal-ordering:\n";
  test_chain.print();
  test_chain.print_HPform();
  test_chain.is_in_normal_order();
  std::cout << std::endl;

  std::cout << "Now we normal order the above operator to get:\n";
  test_chain.NormalOrder();
  test_chain.print();
  test_chain.print_HPform();

  test_chain.is_in_normal_order();
  std::cout << std::endl;

  return 0;
}