#pragma once
#include "LadderOperator.hpp"
#include <cassert>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

//! struct for keeping track of the sign of an OperatorChain
// used for when we want to put operator products into normal order for Wick's
// theorem
enum Sign { Positive, Negative, Zero };

class OperatorChain {
private:
  std::vector<LadderOperator> m_ochain;
  bool m_is_in_normal_order;
  Sign m_sign;

public:
  //! constructor for an operator chain with a vector of ladder operators
  OperatorChain(std::vector<LadderOperator> operator_prod,
                Sign sign = Sign::Positive)
      : m_ochain(operator_prod), m_sign(sign) {
    // function goes here for setting m_is_in_normal_order
    m_is_in_normal_order = true;
  };

  //! constructor for an operator chain with an initialiser list of ladder
  //! operators
  OperatorChain(std::initializer_list<LadderOperator> operator_prod,
                Sign sign = Sign::Positive)
      : m_ochain(operator_prod), m_is_in_normal_order(false), m_sign(sign) {};

  //! function for returning sign of the operator product
  Sign getSign() { return m_sign; }

  //! returns by copy the i'th ladder operator in the chain
  LadderOperator at(int i) const { return m_ochain[i]; }

  //! returns by reference the i'th ladder operator in the chain so we can
  // change it
  LadderOperator &at(int i) { return m_ochain[i]; }

  //! similar to above but with regular C++ vector indexing
  // returns by copy
  LadderOperator operator[](int i) const { return at(i); }

  //! similar to above but with regular C++ vector indexing
  // returns by reference
  LadderOperator &operator[](int i) { return at(i); }

  //! function for normally ordering an operator product
  // moves all core creation operators and valence annihilation operators to the
  // right
  // updates sign from the permutation of the operators
  void NormalOrder();

  //! getter for if the function is in normal order
  bool is_in_normal_order() { return m_is_in_normal_order; }
};

void OperatorChain::NormalOrder() {

  int counter = m_ochain.size();
  OperatorChain out = m_ochain;

  for (int i = m_ochain.size() - 1; i = 0; i--) {
    LadderOperator a = m_ochain[i];
    if (a.getHoleParticleType() == HoleParticleType::annihilation) {
      out[counter] = a;
      counter = 0;
    }
    if (a.getHoleParticleType() == HoleParticleType::creation) {
      LadderOperator b = m_ochain[i];
      counter += 1;
      while (b.getHoleParticleType() == HoleParticleType::creation) {
        b = m_ochain[i - counter];
        out[i - counter] = m_ochain[i - counter - 1]; // not right
        counter += 1;
      }
      out[i] = m_ochain[i - counter];
      for (int j = 1; j < counter; j++) {
        out[i - j] = m_ochain[i - j - 1];
      }
    }
  }
}