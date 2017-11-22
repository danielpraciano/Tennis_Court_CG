#pragma once

#include <core/include/util.h>

namespace render {
namespace raycasting {

class Color {

public:
    Color(double r = 0.0, double g = 0.0, double b = 0.0) : _r(r), _g(g), _b(b) {}
    Color(core::util::Vector3 rgb) : _r(rgb(0)), _g(rgb(1)), _b(rgb(2)) {}
    ~Color() {}

    inline double get_r() const { return _r; }
    inline double get_g() const { return _g; }
    inline double get_b() const { return _b; }

    // is it better &?
    inline core::util::Vector3 get_values() const {
        return core::util::Vector3 { _r, _g, _b };
    }

    inline void set_values(const core::util::Vector3 &rgb_values) {
        _r = rgb_values(0);
        _g = rgb_values(1);
        _b = rgb_values(2);
    }

private:
    double _r, _g, _b;

};

}
}
