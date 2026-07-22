#pragma once
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

//! enum struct to track the type of ladder diagram i.e. if it is a
// creation/annihilation operator
enum LadderType { creation, annihilation };

//! enum struct to track index type
enum IndexType {
  core,
  excited,
  any,
  valence,
  excited_but_valence,
  any_but_valence
};

//! struct to store the index type and index string of a ladder operator
struct Index {
private:
  std::string m_stringindex;
  IndexType m_indextype;

public:
  void setIndexString(std::string s) { m_stringindex = s; };
  void setIndexType(IndexType i_type) { m_indextype = i_type; };
  IndexType getIndexType() { return m_indextype; };
  const char *getIndexString() { return m_stringindex.c_str(); };
  const char *parseIndexType() {
    if (m_indextype == core) {
      return "core";
    } else if (m_indextype == excited) {
      return "excited";
    } else if (m_indextype == any) {
      return "any";
    } else if (m_indextype == valence) {
      return "valence";
    } else if (m_indextype == excited_but_valence) {
      return "excited != valence";
    } else if (m_indextype == any_but_valence) {
      return "any != valence";
    } else {
      throw std::runtime_error("bad");
    }
  };
};

//! struct for the type of HoleParticle operator it is
// creation operator if it excites a particle/hole
// annihilation operator if it destroys a particle/hole
enum HoleParticleType { creation, annihilation };

//! function to determine if the ladder operator is a particle/hole creation or
// annihilation operator
// used when determining if it needs to be moved when normal ordering strings of
// creation/annihilation operators
HoleParticleType determineHoleParticleType(LadderOperator a) {
  HoleParticleType out;
  if ((a.getIndexType() == IndexType::valence ||
       a.getIndexType() == IndexType::excited ||
       a.getIndexType() == IndexType::excited_but_valence) &&
      a.getLadderType() == annihilation) {
    out = HoleParticleType::annihilation;
  } else if (a.getIndexType() == IndexType::core &&
             a.getLadderType() == creation) {
    out = HoleParticleType::annihilation;
  } else {
    out = HoleParticleType::creation;
  }
  return out;
}

class LadderOperator {
private:
  Index m_index;
  LadderType m_laddertype;
  HoleParticleType m_hptype;

public:
  LadderOperator(LadderType laddertype, Index index)
      : m_index(index), m_laddertype(laddertype) {

    m_hptype = determineHoleParticleType(this);
  };

  // overload for when we individually want to give it an index string and an
  // index type
  LadderOperator(LadderType laddertype, IndexType i_type,
                 std::string i_string) {
    m_index.setIndexString(i_string);
    m_index.setIndexType(i_type);
    m_laddertype = laddertype;
  };

  Index getindex() { return m_index; };
  LadderType getLadderType() { return m_laddertype; };
  IndexType getIndexType() { return m_index.getIndexType(); };
  HoleParticleType getHoleParticleType() { return m_hptype; };

  void getInfo() {

    const char *dagger_str = m_laddertype == creation ? "^†" : "";
    printf("a\xCC\x82%s(%s)  (%s index)\n", dagger_str,
           m_index.getIndexString(), m_index.parseIndexType());
    ;
  }
};