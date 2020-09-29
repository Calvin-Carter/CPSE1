#include "hwlib.hpp"
#include "note_player_2.hpp"

void note_player_2::play( const note & n ){
  if( n.frequency == 0 ){
     hwlib::wait_us( n.duration );
}
  else if( n.frequency == 440 ) {
    hwlib::cout << "A4" << hwlib::endl;
  }
  else if( n.frequency == 466 ) {
    hwlib::cout << "A4s" << hwlib::endl;
  }
  else if( n.frequency == 494 ) {
    hwlib::cout << "B4" << hwlib::endl;
  }
  else if( n.frequency == 523 ) {
    hwlib::cout << "C5" << hwlib::endl;
  }
  else if( n.frequency == 554 ) {
    hwlib::cout << "C5s" << hwlib::endl;
  }
  else if( n.frequency == 587 ) {
    hwlib::cout << "D5" << hwlib::endl;
  }
  else if( n.frequency == 622 ) {
    hwlib::cout << "D5s" << hwlib::endl;
  }
  else if( n.frequency == 659 ) {
    hwlib::cout << "E5" << hwlib::endl;
  }
  else if( n.frequency == 698 ) {
    hwlib::cout << "F5" << hwlib::endl;
  }
  else if( n.frequency == 740 ) {
    hwlib::cout << "F5s" << hwlib::endl;
  }
  else if( n.frequency == 784 ) {
    hwlib::cout << "G5" << hwlib::endl;
  }
  else if( n.frequency == 830 ) {
    hwlib::cout << "G5s" << hwlib::endl;
  }
  else if( n.frequency == 880 ) {
    hwlib::cout << "A5" << hwlib::endl;
  }
  else if( n.frequency == 932 ) {
    hwlib::cout << "A5s" << hwlib::endl;
  }
  else if( n.frequency == 987 ) {
    hwlib::cout << "B5" << hwlib::endl;
    }
    hwlib::wait_us( n.duration );
  }
