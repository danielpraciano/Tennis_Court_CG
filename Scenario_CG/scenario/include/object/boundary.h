#pragma once

#include <core/include/util.h>
#include <render/include/raycasting/ray.h>

namespace scenario {
namespace object {

class Boundary {

public:
    Boundary() {}

    void generate(const core::util::Vector3 &coord_min, const core::util::Vector3 &coord_max);

    inline const core::util::Vector3& get_center() const { return center_; }

    inline double get_radius() const { return std::sqrt(_radius_square); }

    inline bool is_intercepted(const render::raycasting::Ray &ray) const {
        auto origin_minus_center = ray.get_origin() - center_;

        double A = dot(ray.get_direction(), ray.get_direction());
        double B = 2 * dot(ray.get_direction(), origin_minus_center);
        double C = dot(origin_minus_center, origin_minus_center) - _radius_square;

        return std::pow(B, 2) - 4 * A * C >= 0 ? true : false;
    }

private:
    core::util::Vector3 center_;
    double _radius_square;

};

}
}
