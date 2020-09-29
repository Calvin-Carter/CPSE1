#include "hwlib.hpp"
#include "string"

constexpr double macht( double g, int n ){
   double result = 1;
   while( n > 0 ){
       result *= g;
       --n;
   }
   return result;
}

constexpr double fac( int n ){
   double result = 1;
   while( n > 0 ){
       result *= n;
       --n;
   }
   return result;
}

constexpr double calcsin( double a ){
   return
      a
      - macht( a, 3 ) / fac( 3 )
      + macht( a, 5 ) / fac( 5 )
      - macht( a, 7 ) / fac( 7 )
      + macht( a, 9 ) / fac( 9 )
      - macht( a, 11 ) / fac( 11 )
      + macht( a, 13 ) / fac( 13 )
      - macht( a, 15 ) / fac( 15 )
      + macht( a, 17 ) / fac( 17 )
      - macht( a, 19 ) / fac( 19 )
      + macht( a, 21 ) / fac( 21 )
      - macht( a, 23 ) / fac( 23 )
      + macht( a, 25 ) / fac( 25 );
}

constexpr double calccos( double x ){
   return
      1
      - macht( x, 2 ) / fac( 2 )
      + macht( x, 4 ) / fac( 4 )
      - macht( x, 6 ) / fac( 6 )
      + macht( x, 8 ) / fac( 8 )
      - macht( x, 10 ) / fac( 10 )
      + macht( x, 12 ) / fac( 12 )
      - macht( x, 14 ) / fac( 14 )
      + macht( x, 16 ) / fac( 16 )
      - macht( x, 18 ) / fac( 18 )
      + macht( x, 20 ) / fac( 20 )
      - macht( x, 22 ) / fac( 22 );
}

constexpr double degrees_to_radians( int degrees ){
   return 2 * 3.14 * ( degrees / 360.0 );
}

constexpr int scaled_sine_from_degrees( int degrees ){
   return 30 * ( 1.0 + calcsin( degrees_to_radians( degrees )));
}

constexpr int scaled_cos_from_degrees( int degrees ){
   return 30 * ( 1.0 + calccos( degrees_to_radians( degrees )));
}

template< int N, typename T >
class lookup {
private:
   std::array< T, N > values = {};

public:

   template< typename F >
   constexpr lookup( F function ){
      for( int i = 0; i < N; ++i ){
          values[ i ] = function( 10 * i );
      }
   }

   constexpr T get( int n ) const {
      return values[ n / 10 ];
   }
};

int main (void) {
  hwlib::wait_ms(2000);
  namespace target = hwlib::target;
  WDT->WDT_MR = WDT_MR_WDDIS; // Kill watchdogs
  auto scl = target::pin_oc( 2,12 );
  auto sda = target::pin_oc( 2,14 );
  auto vcc = target::pin_out( 1,14 );
  vcc.write(1);
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
  auto display = hwlib::glcd_oled( i2c_bus, 0x3c );
  display.clear();

  int radius = 1;
  int middlepoint_x = 32;
  int middlepoint_y = 2;

  display.flush();

  constexpr auto sinusses = lookup< 36, int > (scaled_sine_from_degrees);
  constexpr auto cosinusses = lookup< 36, int > (scaled_cos_from_degrees);

  for (int degrees = 0; degrees < 360; degrees += 30){
    hwlib::circle rondjes_cijfers(hwlib::xy((middlepoint_x + (cosinusses.get(degrees) * radius)), (middlepoint_y + (sinusses.get(degrees) * radius))), 2, hwlib::white);
        rondjes_cijfers.draw(display);

  }
  display.flush();
}
