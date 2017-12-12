#pragma once

#include <core/include/util.h>

namespace render {
namespace raycasting {

class Ray {

public:
    //ray(t) = origin + t * direction;
    Ray(core::util::Vector3 origin, core::util::Vector3 direction) : origin_(origin), direction_(direction) {}

    inline const core::util::Vector3 &get_origin() const { return origin_; }

    inline const core::util::Vector3 &get_direction() const { return direction_; }

    inline core::util::Vector3 get_point(double t) const { return origin_ + t * direction_; }

private:
    core::util::Vector3 origin_, direction_;

};

}
}
