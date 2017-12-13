#pragma once

#include <memory>

#include <vector>
#include <utility>
#include <limits>
#include <core/include/util.h>
#include <scenario/include/object/material.h>
#include <scenario/include/object/vertex.h>
#include <scenario/include/object/face.h>
#include <scenario/include/object/boundary.h>
#include <scenario/include/object/texture.h>
#include <render/include/raycasting/ray.h>

namespace scenario {
namespace object {

class Object {

public:
    Object(const std::shared_ptr<Material> material) : material(material) {
        coordinates_min_.fill(std::numeric_limits<double>::max());
        coordinates_max_.fill(std::numeric_limits<double>::min()); }
    ~Object() {}

    inline size_t get_vertices_size() const { return vertices.size(); }
    inline size_t get_faces_size()    const { return faces_.size(); }

    inline const std::shared_ptr<Vertex> &get_vertice(int id) const { return vertices[id]; }
    inline const Boundary &get_boundary() const { return boundary_; }

    inline void add_vertex(Vertex v) { vertices.push_back(std::make_shared<Vertex>(v)); }

    void add_face(int index_v1, int index_v2, int index_v3, std::shared_ptr<Material> mat = nullptr,
                  int index_vertex_left_ref_to_tex = -1, int index_vertex_right_ref_to_tex = -1, const Texture *tex = nullptr);

    void apply_matrix(const core::util::Matrix4 &transformation);

    void make_ready();

    /**
     * @brief get_intercept
     * @param ray
     * @return <t_int, face> if intercepted, <-1.0, nullptr> otherwise.
     */

    std::pair<double, const Face*> get_intercept(const render::raycasting::Ray &ray, double t_int_minimum = 1.0) const;

private:
    const std::shared_ptr<Material> material;
    std::vector<std::shared_ptr<Vertex>> vertices;
    core::util::Vector3 coordinates_min_;
    core::util::Vector3 coordinates_max_;
    std::vector<Face> faces_;
    Boundary boundary_;

    void update_min_and_max(const core::util::Vector3 &coordinates);

};

}
}
