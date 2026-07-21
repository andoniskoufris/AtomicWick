#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

//! enum struct to track the type of ladder diagram i.e. if it is a
// creation/annihilation operator
enum LadderType { creation, annihilation };

//! enum struct to track index type
enum IndexType { core, excited, any, valence };

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
  const char *parseIndexType() { return "sss"; }
};

class LadderOperator {
private:
  Index m_index;
  LadderType m_laddertype;

public:
  LadderOperator(LadderType laddertype, Index index)
      : m_index(index), m_laddertype(laddertype) {};

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

  void getInfo() {

    const char *dagger_str = m_laddertype == creation ? "^†" : "";
    printf("a\xCC\x82%s_%s  (%s index)\n", m_index.getIndexString(), dagger_str,
           m_index.parseIndexType());
    ;
  }
};