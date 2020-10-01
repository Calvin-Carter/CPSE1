#include "iostream"
#include "fstream"
#include "string"
#include "note_player_2.hpp"


void note_player_2::play( const note & n ){
  std::string note = "";
  std::string duration = "";

  std::fstream file ("melody.cpp", std::ios_base::app);
  file << "   p.play( note{ " << n.frequency << ", " << n.duration << " } );" << std::endl;
}
