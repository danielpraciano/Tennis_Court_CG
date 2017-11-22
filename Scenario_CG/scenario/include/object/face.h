#pragma once

#include <memory>

#include <scenario/include/object/vertex.h>
#include <scenario/include/object/material.h>
#include <render/include/raycasting/ray.h>

namespace scenario {
namespace object {

class Face {

public:
    Face(std::shared_ptr<Material> material, std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2,
         std::shared_ptr<Vertex> v3) : _material(material), _v1(v1), _v2(v2), _v3(v3) {}
    ~Face() {}

    inline void calculate_normal() {
        _normal_vec = normalise(cross(_v2->get_coordinates() - _v1->get_coordinates(),
                               _v3->get_coordinates() - _v1->get_coordinates()));

        _v1_dot_normal = dot(_v1->get_coordinates(), _normal_vec);
    }

    inline void set_normal(core::util::Vector3 normal) {
        _normal_vec = normal;
    }

    inline const core::util::Vector3 &get_normal() const {
        return _normal_vec;
    }

    inline const Material &get_material() const {
        return *_material;
    }

    /**
     * @brief get_intercept
     * @param ray
     * @return t_int if intercepted, -1.0 otherwise.
     */

    double get_intercept(const render::raycasting::Ray &ray) const;

private:
    std::shared_ptr<Material> _material;
    std::shared_ptr<Vertex> _v1, _v2, _v3;
    core::util::Vector3 _normal_vec;
    double _v1_dot_normal;

};

}
}
