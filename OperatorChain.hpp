#pragma once
#include "LadderOperator.hpp"
#include <cassert>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

bool check_is_in_normal_order(std::vector<LadderOperator> chain);

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
    // checks if the vector list is in normal order
    m_is_in_normal_order = check_is_in_normal_order(operator_prod);
  };

  //! constructor for an operator chain with an initialiser list of ladder
  //! operators
  OperatorChain(std::initializer_list<LadderOperator> operator_prod,
                Sign sign = Sign::Positive)
      : m_ochain(operator_prod), m_sign(sign) {
    m_is_in_normal_order =
        check_is_in_normal_order(std::vector<LadderOperator>{operator_prod});
  };

  //! function for returning sign of the operator product
  Sign getSign() { return m_sign; }

  //! function for setting sign of the operator product
  void setSign(Sign in_sign) { m_sign = in_sign; }

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

  int size() { return m_ochain.size(); }

  //! function for normally ordering an operator product
  // moves all core creation operators and valence annihilation operators to the
  // right
  // updates sign from the permutation of the operators
  void NormalOrder();

  //! prints if if the function is in normal order
  void is_in_normal_order();

  //! prints the operators in the chain
  // right now it just prints c if the operator corresponds to a core state and
  // n if it corresponds to an excited state not sure how best to deal with the
  // index problem...
  void print();

  //!  prints the operators in the chain but writes them as hole-particle
  //!  operators (b or b^†)
  void print_HPform();
};
