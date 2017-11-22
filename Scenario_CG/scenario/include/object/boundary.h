#pragma once

#include <core/include/util.h>

namespace scenario {
namespace object {

class Boundary {

public:
    Boundary() {}

    void generate(const core::util::Vector3 &coord_min, const core::util::Vector3 &coord_max);

    inline bool is_intercepted(const core::util::Vector3 &p_ij) const {
        return std::pow(-2 * dot(p_ij, _center), 2) -
                4 * dot(p_ij, p_ij) * (_center_square - _radius_square) >= 0 ? true : false;
    }

private:
    core::util::Vector3 _center;
    double _radius_square, _center_square;

};

}
}
