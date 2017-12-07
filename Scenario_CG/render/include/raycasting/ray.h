#pragma once

#include <core/include/util.h>

namespace render {
namespace raycasting {

class Ray {

public:
    //ray obs: source = Po and destiny = P_ij
    Ray(core::util::Vector3 source, core::util::Vector3 destiny) : _source(source), _destiny(destiny), _destiny_normalized(normalise(destiny)) {}

    inline core::util::Vector3 get_point_destiny_normalized(double t) const {
        return _source + t * (_destiny_normalized - _source);
    }

    inline core::util::Vector3 get_point(double t) const {
        return _source + t * (_destiny - _source);
    }

    inline const core::util::Vector3 &get_destiny() const {
        return _destiny;
    }

    inline const core::util::Vector3 &get_destiny_normalized() const {
        return _destiny_normalized;
    }

private:
    core::util::Vector3 _source, _destiny, _destiny_normalized;

};

}
}
