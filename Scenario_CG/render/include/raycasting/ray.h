#pragma once

#include <core/include/util.h>

namespace render {
namespace raycasting {

class Ray {

public:
    //ray(t) = origin + t * direction;
    Ray(core::util::Vector3 origin, core::util::Vector3 direction) : _origin(origin), _direction(direction), _direction_normalized(normalise(direction)) {}

    inline core::util::Vector3 get_point_direction_normalized(double t) const {
        return _origin + t * _direction_normalized;
    }

    inline core::util::Vector3 get_point(double t) const {
        return _origin + t * _direction;
    }

    inline const core::util::Vector3 &get_origin() const {
        return _origin;
    }

    inline const core::util::Vector3 &get_direction() const {
        return _direction;
    }

    inline const core::util::Vector3 &get_direction_normalized() const {
        return _direction_normalized;
    }

private:
    core::util::Vector3 _origin, _direction, _direction_normalized;

};

}
}
