#include "LadderOperator.hpp"

//!!! should write unit test that checks if every possible combination of index
// and ladder type actually gives the right hole-particle type

//! function to determine if the ladder operator is a particle/hole creation or
// annihilation operator
// used when determining if it needs to be moved when normal ordering strings of
// creation/annihilation operators
HoleParticle::HoleParticleType
determineHoleParticleType(Ladder::LadderType ltype, Ladder::IndexType itype) {
  HoleParticle::HoleParticleType out;
  if ((itype == Ladder::IndexType::valence ||
       itype == Ladder::IndexType::excited ||
       itype == Ladder::IndexType::excited_but_valence) &&
      ltype == Ladder::LadderType::annihilation) {
    out = HoleParticle::HoleParticleType::annihilation;
  } else if (itype == Ladder::IndexType::core &&
             ltype == Ladder::LadderType::creation) {
    out = HoleParticle::HoleParticleType::annihilation;
  } else if (itype == Ladder::IndexType::any ||
             itype == Ladder::IndexType::any_but_valence) {
    out = HoleParticle::HoleParticleType::undetermined;
  } else {
    out = HoleParticle::HoleParticleType::creation;
  }
  return out;
}

//=============================================================================
//=============================================================================
void LadderOperator::printHoleParticleType() {
  const char *hp_type =
      getHoleParticleType() == HoleParticle::HoleParticleType::creation
          ? "creation"
      : getHoleParticleType() == HoleParticle::HoleParticleType::annihilation
          ? "annihilation"
          : "undetermined";
  printf("HP %s", hp_type);
}

//=============================================================================
//=============================================================================
void LadderOperator::printInfo(bool verbose) {

  const char *dagger_str =
      m_laddertype == Ladder::LadderType::creation ? "^†" : "";
  printf("a\xCC\x82%s(%s) (%s)", dagger_str, m_index.getIndexString(),
         m_index.parseIndexType());
}

//=============================================================================
//=============================================================================
void LadderOperator::print_HPInfo() {
  const char *HP_str =
      determineHoleParticleType(m_laddertype, m_index.getIndexType()) ==
              HoleParticle::HoleParticleType::annihilation
          ? "b"
      : determineHoleParticleType(m_laddertype, m_index.getIndexType()) ==
              HoleParticle::HoleParticleType::creation
          ? "b^†"
          : "C (unsure)";

  printf("%s(%s)", HP_str, m_index.getIndexString());
}