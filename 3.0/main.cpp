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

void clockdraw(){}

int main (void) {
  hwlib::wait_ms(2000);
  namespace target = hwlib::target;
  WDT->WDT_MR = WDT_MR_WDDIS; // Kill watchdogs
  auto scl = target::pin_oc( 2,12 );
  auto sda = target::pin_oc( 2,14 );
  auto vcc = target::pin_out( 1,14 );
  auto uurpin = target::pin_in( target::pins::d38);
  auto minuutpin = target::pin_in( target::pins::d36);
  vcc.write(1);
  auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
  auto display = hwlib::glcd_oled( i2c_bus, 0x3c );
  display.clear();

//#############################################################//

  //bool minuutbutton = !minuutpin.read();
  //bool uurbutton = !uurpin.read();
  int radius = 1;
  int middlepoint_x = 32;
  int middlepoint_y = 2;
  hwlib::xy middlepoint(62,30);
  int hoek_uur = 270;
  int hoek_minuut = 276;
  uint64_t time = ((hwlib::now_us() / 1000000) / 60);

  constexpr auto sinusses = lookup< 36, int > (scaled_sine_from_degrees);
  constexpr auto cosinusses = lookup< 36, int > (scaled_cos_from_degrees);


//#############################################################//

  time = 0;
  display.clear();
  while(true){
    uint64_t previoustime = time;
    time = ((hwlib::now_us() / 1000000) / 60);

    for (int degrees = 0; degrees < 360; degrees += 30){
      hwlib::circle circles(hwlib::xy((middlepoint_x + (cosinusses.get(degrees) * radius)), (middlepoint_y + (sinusses.get(degrees) * radius))), 2, hwlib::white);
          circles.draw(display);
      hwlib::line minuutwijzer(middlepoint, hwlib::xy((middlepoint_x + (cosinusses.get(hoek_minuut) * radius)), (middlepoint_y + (sinusses.get(hoek_minuut) * radius))));
          minuutwijzer.draw(display);
      hwlib::line uurwijzer(middlepoint, hwlib::xy((middlepoint_x + (cosinusses.get(hoek_uur) * radius)), (middlepoint_y + (sinusses.get(hoek_uur) * radius))));
          uurwijzer.draw(display);
    }

    if(previoustime != time){
      hoek_minuut = hoek_minuut + 6;
      if(hoek_minuut == 270){
        hoek_uur += 30;
      }
      display.clear();
    }

    if(hoek_uur == 360){
      hoek_uur = 0;
      display.clear();
      display.flush();
    }
    if(hoek_minuut == 360){
      hoek_minuut = 0;
      display.clear();
      display.flush();
    }


    bool minuutbutton = !minuutpin.read();
    bool uurbutton = !uurpin.read();
    minuutpin.refresh();
    uurpin.refresh();
    if(minuutbutton == 1){
      display.clear();
      hoek_minuut += 6;
      hwlib::cout << minuutbutton << hwlib::endl;
      for (int degrees = 0; degrees < 360; degrees += 30){
        hwlib::circle circles(hwlib::xy((middlepoint_x + (cosinusses.get(degrees) * radius)), (middlepoint_y + (sinusses.get(degrees) * radius))), 2, hwlib::white);
            circles.draw(display);
        hwlib::line minuutwijzer(middlepoint, hwlib::xy((middlepoint_x + (cosinusses.get(hoek_minuut) * radius)), (middlepoint_y + (sinusses.get(hoek_minuut) * radius))));
            minuutwijzer.draw(display);
        hwlib::line uurwijzer(middlepoint, hwlib::xy((middlepoint_x + (cosinusses.get(hoek_uur) * radius)), (middlepoint_y + (sinusses.get(hoek_uur) * radius))));
            uurwijzer.draw(display);
      }
      display.flush();
    }
    if(uurbutton == 1){
      display.clear();
      hoek_uur += 30;
      hwlib::cout << uurbutton << hwlib::endl;
      for (int degrees = 0; degrees < 360; degrees += 30){
        hwlib::circle circles(hwlib::xy((middlepoint_x + (cosinusses.get(degrees) * radius)), (middlepoint_y + (sinusses.get(degrees) * radius))), 2, hwlib::white);
            circles.draw(display);
        hwlib::line minuutwijzer(middlepoint, hwlib::xy((middlepoint_x + (cosinusses.get(hoek_minuut) * radius)), (middlepoint_y + (sinusses.get(hoek_minuut) * radius))));
            minuutwijzer.draw(display);
        hwlib::line uurwijzer(middlepoint, hwlib::xy((middlepoint_x + (cosinusses.get(hoek_uur) * radius)), (middlepoint_y + (sinusses.get(hoek_uur) * radius))));
            uurwijzer.draw(display);
      }
      display.flush();
    }
    display.flush();
  }
}
