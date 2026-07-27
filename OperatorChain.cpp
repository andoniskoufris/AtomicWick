#include "OperatorChain.hpp"

//! member function that normally orders a product of operators
void OperatorChain::NormalOrder() {

  // keeps track of how many creation operators there are
  // in a given chain of them
  int num_creation = 0;
  // keeps track of how many swaps we have to make to get it in normal order
  int num_swaps = 0;

  // vector to store the creation operators we wish to place at the left of the
  // chain
  std::vector<LadderOperator> creation_operators;

  // vector to store the annihilation operators we wish to place at the right of
  // the chain
  std::vector<LadderOperator> destruction_operators;

  // loops through operators in m_ochain
  for (int i = 0; i < m_ochain.size(); i++) {
    LadderOperator a = m_ochain[i];

    if (a.getHoleParticleType() ==
            HoleParticle::HoleParticleType::annihilation ||
        a.getHoleParticleType() ==
            HoleParticle::HoleParticleType::undetermined) {
      destruction_operators.emplace_back(a);
      // very inefficient way to do this but it works
      for (int j = i + 1; j < m_ochain.size(); j++) {
        LadderOperator b = m_ochain[j];
        if (b.getHoleParticleType() ==
            HoleParticle::HoleParticleType::creation) {
          num_swaps += 1;
        }
      }
    } else {
      creation_operators.emplace_back(a);
    }
  }

  // appends the annihilation operators to the end of the creation operators
  creation_operators.insert(creation_operators.end(),
                            destruction_operators.begin(),
                            destruction_operators.end());

  // replaces the operator product with the normally-ordered ones
  m_ochain = creation_operators;

  // sets the sign of the product according to the number of swaps we had to
  // make
  Sign normal_sign = num_swaps % 2 == 0 ? Sign::Positive : Sign::Negative;
  setSign(normal_sign);

  // declares that the operator chain is now in normal order
  m_is_in_normal_order = true;
}

//=============================================================================
//=============================================================================

//! function definition that checks if a vector of ladder operators is in normal
// order (as read from left to right in the vector)
bool check_is_in_normal_order(std::vector<LadderOperator> chain) {

  // keeps track of how many creation operators there are
  // in a given chain of them
  int num_creation = 0;
  // keeps track of how many swaps we have to make to get it in normal order
  int num_swaps = 0;

  // loops through operators in m_ochain
  for (int i = 0; i < chain.size(); i++) {
    LadderOperator a = chain[i];

    if (a.getHoleParticleType() ==
            HoleParticle::HoleParticleType::annihilation ||
        a.getHoleParticleType() ==
            HoleParticle::HoleParticleType::undetermined) {
      // very inefficient way to do this but it works
      for (int j = i + 1; j < chain.size(); j++) {
        LadderOperator b = chain[j];
        if (b.getHoleParticleType() ==
            HoleParticle::HoleParticleType::creation) {
          num_swaps += 1;
        }
      }
    }
  }

  // the operator product is in normal order if we never had to make any swaps
  std::cout << num_swaps << std::endl;
  return num_swaps == 0;
}

//=============================================================================
//=============================================================================
void OperatorChain::print() {
  // print negative sign in case the function is negative
  if (m_sign == Sign::Negative) {
    std::cout << "- ";
  }
  for (auto a : m_ochain) {
    a.printInfo();
  }
  std::cout << std::endl;
}

//=============================================================================
//=============================================================================
void OperatorChain::is_in_normal_order() {
  const char *qualifier = m_is_in_normal_order == true ? " " : " _not_ ";

  printf("This operator is%sin normal order!", qualifier);
  std::cout << std::endl;
}

//=============================================================================
//=============================================================================
void OperatorChain::print_HPform() {
  if (m_sign == Sign::Negative) {
    std::cout << "- ";
  }
  for (auto a : m_ochain) {
    a.print_HPInfo();
    std::cout << " ";
  }
  std::cout << std::endl;
}