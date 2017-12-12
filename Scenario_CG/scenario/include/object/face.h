#pragma once

#include <memory>

#include <scenario/include/object/vertex.h>
#include <scenario/include/object/material.h>
#include <render/include/raycasting/ray.h>

namespace scenario {
namespace object {

class Face {

public:
    Face(const std::shared_ptr<Material> material, std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2,
         std::shared_ptr<Vertex> v3) : material(material), v1(v1), v2(v2), v3(v3) {}
    ~Face() {}

    inline const Material &get_material() const { return *material; }

    inline const core::util::Vector3 &get_normal() const { return normal_vec_; }

    inline void calculate_normal() {
        normal_vec_ = normalise(cross(v2->get_coordinates() - v1->get_coordinates(),
                                      v3->get_coordinates() - v1->get_coordinates()));
    }

    /**
     * @brief get_intercept
     * @param ray
     * @return t_int if intercepted, -1.0 otherwise.
     */

    double get_intercept(const render::raycasting::Ray &ray) const;

private:
    const std::shared_ptr<Material> material;
    std::shared_ptr<Vertex> v1, v2, v3;
    core::util::Vector3 normal_vec_;

};

}
}
