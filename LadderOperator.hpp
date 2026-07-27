#pragma once
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace Ladder {
//! enum struct to track the type of ladder diagram i.e. if it is a
// creation/annihilation operator
enum class LadderType { creation, annihilation };

//! enum struct to track index type
enum IndexType {
  core,
  excited,
  any,
  valence,
  excited_but_valence,
  any_but_valence
};
} // namespace Ladder

//! struct to store the index type and index string of a ladder operator
struct Index {
private:
  std::string m_stringindex;
  Ladder::IndexType m_indextype;

public:
  Index() {};
  Index(std::string in_stringindex, Ladder::IndexType in_type)
      : m_stringindex(in_stringindex), m_indextype(in_type) {};

  void setIndexString(std::string s) { m_stringindex = s; };
  void setIndexType(Ladder::IndexType i_type) { m_indextype = i_type; };
  Ladder::IndexType getIndexType() { return m_indextype; };
  const char *getIndexString() { return m_stringindex.c_str(); };
  const char *parseIndexType() {
    if (m_indextype == Ladder::core) {
      return "core";
    } else if (m_indextype == Ladder::excited) {
      return "excited";
    } else if (m_indextype == Ladder::any) {
      return "any";
    } else if (m_indextype == Ladder::valence) {
      return "valence";
    } else if (m_indextype == Ladder::excited_but_valence) {
      return "excited != valence";
    } else if (m_indextype == Ladder::any_but_valence) {
      return "any != valence";
    } else {
      throw std::runtime_error("bad");
    }
  };
};

namespace HoleParticle {
//! struct for the type of HoleParticle operator
// - creation operator if it excites a particle/hole
// - annihilation operator if it destroys a particle/hole
// - it is undetermined if the index is neither core nor excited/valence, and
// can take any value
enum HoleParticleType { creation, annihilation, undetermined };
} // namespace HoleParticle

HoleParticle::HoleParticleType
determineHoleParticleType(Ladder::LadderType ltype, Ladder::IndexType itype);

class LadderOperator {
private:
  Index m_index;
  Ladder::LadderType m_laddertype;
  HoleParticle::HoleParticleType m_hptype;

public:
  LadderOperator(Ladder::LadderType laddertype, Index index)
      : m_index(index), m_laddertype(laddertype) {

    m_hptype = determineHoleParticleType(laddertype, index.getIndexType());
  };

  // overload for when we individually want to give it an index string and an
  // index type
  LadderOperator(Ladder::LadderType laddertype, Ladder::IndexType i_type,
                 std::string i_string) {
    m_index.setIndexString(i_string);
    m_index.setIndexType(i_type);
    m_laddertype = laddertype;
    m_hptype = determineHoleParticleType(laddertype, i_type);
  };

  // get the index
  Index getindex() { return m_index; };
  // get the type of ladder operator (annihilation/creation)
  Ladder::LadderType getLadderType() { return m_laddertype; };
  // get the type of index (core/valence/excited/any)
  Ladder::IndexType getIndexType() { return m_index.getIndexType(); };
  // get if the operator is a HP creation/annihilation operator
  HoleParticle::HoleParticleType getHoleParticleType() { return m_hptype; };

  //! print the HP type
  void printHoleParticleType();

  //! print the ladder operator out
  void printInfo(bool verbose = true);

  //! print the ladder operator as a hole-particle operator
  void print_HPInfo();
};
