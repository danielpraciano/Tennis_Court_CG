#pragma once

#include <core/include/util.h>

namespace render {
namespace raycasting {

class Color {

public:
    Color(double r = 0.0, double g = 0.0, double b = 0.0) : r_(r), g_(g), b_(b) {}
    Color(core::util::Vector3 rgb) : r_(rgb(0)), g_(rgb(1)), b_(rgb(2)) {}
    ~Color() {}

    inline double get_r() const { return r_; }
    inline double get_g() const { return g_; }
    inline double get_b() const { return b_; }

    // is it better &?
    inline core::util::Vector3 get_values() const {
        return core::util::Vector3 { r_, g_, b_ };
    }

    inline void set_values(const core::util::Vector3 &rgb_values) {
        r_ = rgb_values(0);
        g_ = rgb_values(1);
        b_ = rgb_values(2);
    }

private:
    double r_, g_, b_;

};

}
}
