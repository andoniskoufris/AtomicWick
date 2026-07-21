#include "LadderOperator.hpp"
#include <cassert>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

class OperatorChain {
private:
  std::vector<LadderOperator> m_ochain;

public:
  OperatorChain(std::vector<LadderOperator> operator_prod)
      : m_ochain(operator_prod) {
    IndexType index_type = operator_prod.front().getIndexType();
    for (auto a : operator_prod) {
      assert(index_type == a.getIndexType() &&
             "All ladder operators in an operator product must have the same "
             "index type!");
    }
  };
};