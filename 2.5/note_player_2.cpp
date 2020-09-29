#include "iostream"
#include "fstream"
#include "string"
#include "note_player_2.hpp"


void note_player_2::play( const note & n ){
  std::string note = "";
  std::string duration = "";

  if( n.frequency == 440 ) {
    note = "A4";
  }
  else if( n.frequency == 466 ) {
    note = "A4S";
  }
  else if( n.frequency == 494 ) {
    note = "B4";
  }
  else if( n.frequency == 523 ) {
    note = "C5";
  }
  else if( n.frequency == 554 ) {
    note = "C5s";
  }
  else if( n.frequency == 587 ) {
    note = "D5";
  }
  else if( n.frequency == 622 ) {
    note = "D5s";
  }
  else if( n.frequency == 659 ) {
    note = "E5";
  }
  else if( n.frequency == 698 ) {
    note = "F5";
  }
  else if( n.frequency == 740 ) {
    note = "F5s";
  }
  else if( n.frequency == 784 ) {
    note = "G5";
  }
  else if( n.frequency == 830 ) {
    note = "G5s";
  }
  else if( n.frequency == 880 ) {
    note = "A5";
  }
  else if( n.frequency == 932 ) {
    note = "A5s";
  }
  else if( n.frequency == 987 ) {
    note = "B5";
    }
  if(n.duration == n.dF){
    duration = "dF";
  }
  else if(n.duration == n.dH){
    duration = "dH";
  }
  else if(n.duration == n.dQ){
    duration = "dQ";
  }
  std::fstream file ("meldody.hpp", std::ios_base::app);
  file << "   p.play( note{ note::" << note << ", " << "note::" << duration << " } );" << std::endl;
}
