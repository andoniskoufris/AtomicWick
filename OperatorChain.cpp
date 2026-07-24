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

  //   int i = chain.size() - 1;
  //   // keeps track of how many creation operators there are
  //   // in a given chain of them
  //   int num_creation = 0;
  //   int pos_last_destruction = i;
  //   int num_swaps = 0;

  //   // loops through positions in m_ochain
  //   while (i >= 0) {
  //     LadderOperator a = chain[i];

  //     // the number of swaps we made is equal to the number of creation
  //     operators
  //     // that _weren't_ at the end of the original chain
  //     num_swaps += num_creation;

  //     // if the operator at position i is creation or undetermined (because
  //     it has
  //     // an index for any state), we just keep going
  //     if (a.getHoleParticleType() ==
  //             HoleParticle::HoleParticleType::annihilation ||
  //         a.getHoleParticleType() ==
  //             HoleParticle::HoleParticleType::undetermined) {
  //       i -= 1;
  //     }
  //     if (a.getHoleParticleType() ==
  //     HoleParticle::HoleParticleType::creation) {
  //       LadderOperator c = chain[i];
  //       num_creation = 0;
  //       // index of last creation operator in the chain so that we know to
  //       place
  //       // the destruction operator we eventually find next to this one
  //       pos_last_destruction = i - 1;

  //       // this now loops through every operator past the HP creation
  //       operator we
  //       // found until we get to a HP creation operator
  //       while (c.getHoleParticleType() ==
  //                  HoleParticle::HoleParticleType::creation &&
  //              i - num_creation >= 1) {
  //         // incrementing num_creation in this while loop ensures that it is
  //         1 if
  //         // there is only one operator we need to move through
  //         num_creation += 1;
  //         c = chain[i - num_creation];
  //       }
  //       // decrease i by the number of creation operators we encountered, so
  //       we
  //       // don't revisit creation operators we have already gone through
  //       // the +1 means that we go past the next creation operator we found
  //       as
  //       // well
  //       if (i == 0) {
  //         num_swaps = 0;
  //       } else {
  //         i -= num_creation + 1;
  //       }
  //     }
  //   }

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
  for (auto a : m_ochain) {
    a.printInfo();
  }
}

//=============================================================================
//=============================================================================
void OperatorChain::is_in_normal_order() {
  const char *qualifier = m_is_in_normal_order == true ? " " : " _not_ ";

  printf("This operator is%sin normal order!", qualifier);
}

//=============================================================================
//=============================================================================
void OperatorChain::print_HPform() {
  for (auto a : m_ochain) {
    a.print_HPInfo();
    std::cout << " ";
  }
}