#pragma once

#include <memory>

#include <scenario/include/object/vertex.h>
#include <scenario/include/object/material.h>
#include <scenario/include/object/texture.h>
#include <render/include/raycasting/ray.h>
#include <render/include/raycasting/color.h>

namespace scenario {
namespace object {

class Face {

public:
    Face(const std::shared_ptr<Material> material, std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2,
         std::shared_ptr<Vertex> v3, int plan_to_tex = -1, const Vertex *vertex_left_ref_to_tex = nullptr,
         const Vertex *vertex_right_ref_to_tex = nullptr, const Texture *tex = nullptr) : material(material), v1(v1), v2(v2), v3(v3), plan_to_tex_(plan_to_tex),
            vertex_left_ref_to_tex(vertex_left_ref_to_tex), vertex_right_ref_to_tex(vertex_right_ref_to_tex), tex(tex) {
//                if (vertex_left_ref_to_tex != nullptr && vertex_right_ref_to_tex != nullptr) {
//                    dx_ = vertex_right_ref_to_tex->get_coordinates()(0) - vertex_left_ref_to_tex->get_coordinates()(0);
//                    dy_ = vertex_right_ref_to_tex->get_coordinates()(1) - vertex_left_ref_to_tex->get_coordinates()(1);
//                }
    }
    ~Face() {}

    inline bool has_tex() const { return tex != nullptr; }

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

    inline void set_dx_dy(double dx, double dy) { dx_ = dx; dy_ = dy; }
    render::raycasting::Color get_rgb_tex(const core::util::Vector3 &p_int) const;

private:
    const std::shared_ptr<Material> material;
    std::shared_ptr<Vertex> v1, v2, v3;
    core::util::Vector3 normal_vec_;
    int plan_to_tex_; // 0 - x, 1 - y, 2 - z.
    const Vertex *vertex_left_ref_to_tex, *vertex_right_ref_to_tex;
    const Texture *tex;
    double dx_, dy_;
};

}
}
