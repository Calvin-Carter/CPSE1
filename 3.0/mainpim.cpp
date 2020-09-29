#include <array>
#include "hwlib.hpp"

constexpr double pow(double g, int n) {
    double result = 1;
    while (n > 0) {
        result *= g;
        --n;
    }
    return result;
}

constexpr double fac(int n) {
    double result = 1;
    while (n > 0) {
        result *= n;
        --n;
    }
    return result;
}

constexpr double radians_from_degrees(int degrees) {
    return 2 * 3.14 * (degrees / 360.0);
}

constexpr double sin(double a) {
    return
        a
        - pow(a, 3) / fac(3)
        + pow(a, 5) / fac(5)
        - pow(a, 7) / fac(7)
        + pow(a, 9) / fac(9)
        - pow(a, 11) / fac(11)
        + pow(a, 13) / fac(13)
        - pow(a, 15) / fac(15)
        + pow(a, 17) / fac(17)
        - pow(a, 19) / fac(19)
        + pow(a, 21) / fac(21);
}

constexpr double cos(double x) {
    return
        1
        - pow(x, 2) / fac(2)
        + pow(x, 4) / fac(4)
        - pow(x, 6) / fac(6)
        + pow(x, 8) / fac(8)
        - pow(x, 10) / fac(10)
        + pow(x, 12) / fac(12)
        - pow(x, 14) / fac(14)
        + pow(x, 16) / fac(16)
        - pow(x, 18) / fac(18)
        + pow(x, 20) / fac(20);
}

constexpr int scaled_sine_from_degrees(int degrees) {
    return 30 * (1.0 + sin(radians_from_degrees(degrees)));
}

constexpr int scaled_cosine_from_degrees(int degrees) {
    return 30 * (1.0 + cos(radians_from_degrees(degrees)));
}

template< int N, typename T >
class lookup {
private:
    std::array< T, N > values = {};

public:

    template< typename F >
    constexpr lookup(F function) {
        for (int i = 0; i < N; ++i) {
            values[i] = function(10 * i);
        }
    }

    constexpr T get(int n) const {
        return values[n / 10];
    }
};

int main(void) {
    hwlib::wait_ms(2000);//wait for the console to get a connection from the arduino
    namespace target = hwlib::target;
    auto scl = target::pin_oc( 2,12 );
    auto sda = target::pin_oc( 2,14 );
    auto vcc = target::pin_out( 1,14 );
    vcc.write(1);
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    auto oled = hwlib::glcd_oled( i2c_bus, 0x3c );
    oled.clear();

    int middelpoint_x = 32;//64
    int middelpoint_y = 2;//32
    int diameter = 1;

    oled.flush();

    constexpr auto cosiness = lookup< 36, int >(scaled_cosine_from_degrees);
    constexpr auto sinusses = lookup< 36, int >(scaled_sine_from_degrees);

    for (int angle_degrees = 0; angle_degrees < 360; angle_degrees += 30) {
        hwlib::circle rondjes_cijfers(hwlib::xy((middelpoint_x + (cosiness.get(angle_degrees) * diameter)), (middelpoint_y + (sinusses.get(angle_degrees) * diameter))), 2, hwlib::white);
        rondjes_cijfers.draw(oled);
    }
    oled.flush();
  }
