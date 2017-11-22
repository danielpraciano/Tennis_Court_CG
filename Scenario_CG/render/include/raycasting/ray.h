#pragma once

#include <core/include/util.h>

namespace render {
namespace raycasting {

class Ray {

public:
    Ray(core::util::Vector3 p_ij) : _p_ij(p_ij), _p_ij_normalized(normalise(p_ij)) {}

    inline core::util::Vector3 get_point_pij_normalized(double t) const {
        return t * _p_ij_normalized;
    }

    inline core::util::Vector3 get_point(double t) const {
        return t * _p_ij;
    }

    inline const core::util::Vector3 &get_p_ij() const {
        return _p_ij;
    }

    inline const core::util::Vector3 &get_p_ij_normalized() const {
        return _p_ij_normalized;
    }

private:
    core::util::Vector3 _p_ij, _p_ij_normalized;

};

}
}
