#include <scenario/include/object/boundary.h>

namespace scenario {
namespace object {

void Boundary::generate(const core::util::Vector3 &coord_min, const core::util::Vector3 &coord_max) {
    center_(0) = ( coord_max(0) + coord_min(0) ) / 2;
    center_(1) = ( coord_max(1) + coord_min(1) ) / 2;
    center_(2) = ( coord_max(2) + coord_min(2) ) / 2;

    auto distance_x = std::abs(coord_max(0)) + std::abs(coord_min(0));
    auto distance_y = std::abs(coord_max(1)) + std::abs(coord_min(1));
    auto distance_z = std::abs(coord_max(2)) + std::abs(coord_min(2));

    _radius_square = std::pow(std::max(distance_x, std::max(distance_y,  distance_z)) / 2, 2);
}

}
}
