#include "hwlib.hpp"

extern "C" char changeletters(char c){
  if((c < 91) && (c > 64)){
    c = (c + 32);
  }

  if((c < 123) && (c > 96)){
    c = (c - 32);
  }
  return c;
}

extern "C" void uart_put_char( char c ){
   hwlib::cout << c;
}

extern "C" void print_asciz(const char * s);

extern "C" void application();

int main( void ){

   namespace target = hwlib::target;

   // wait for the PC console to start
   hwlib::wait_ms( 2000 );

   application();
}
