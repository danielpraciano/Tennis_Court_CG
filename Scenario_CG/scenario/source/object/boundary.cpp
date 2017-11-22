#include <scenario/include/object/boundary.h>

namespace scenario {
namespace object {

void Boundary::generate(const core::util::Vector3 &coord_min, const core::util::Vector3 &coord_max) {
    _center(0) = coord_max(0) - coord_min(0);
    _center(1) = coord_max(1) - coord_min(1);
    _center(2) = coord_max(2) - coord_min(2);

    _radius_square = std::pow(coord_max(0) - _center(0), 2) + std::pow(coord_max(1) - _center(1), 2) +
            std::pow(coord_max(2) - _center(2), 2);

    _center_square = dot(_center, _center);
}

}
}
