#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

struct Index {
  std::string stringindex;
  void setIndex(std::string s) { stringindex = s; };
};

enum LadderType { creation, annihilation };

enum IndexType { core, excited, any, valence };

class LadderOperator {
private:
  Index m_index;
  LadderType m_laddertype;
  IndexType m_indextype;

public:
  LadderOperator(Index index, LadderType laddertype, IndexType indextype)
      : m_index(index), m_laddertype(laddertype), m_indextype(indextype) {};

  Index getindex() { return m_index; };
  LadderType getladdertype() { return m_laddertype; };
  IndexType getindextype() { return m_indextype; };

  void getInfo() {
    if (m_laddertype == creation) {
      printf("a\xCC\x86^†_%s\n", m_index.stringindex.c_str());
    } else {
      printf("a\xCC\x86_%s\n", m_index.stringindex.c_str());
    };
  }
};