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
#include <render/include/raycasting/ray.h>

namespace scenario {
namespace object {

class Object {

public:
    Object(std::shared_ptr<Material> material) : _material(material) {
        _coordinates_min.fill(std::numeric_limits<double>::max());
        _coordinates_max.fill(std::numeric_limits<double>::min()); }
    ~Object() {}

//    inline void add_vertex(Vertex v) { _vertices.push_back(v); }
    inline void add_vertex(Vertex v) { _vertices.push_back(std::make_shared<Vertex>(v)); }

//    inline void add_vertices(std::vector<Vertex> &vertices) {
//        _vertices.insert(_vertices.end(), vertices.begin(), vertices.end());
//    }

    void add_face(int index_v1, int index_v2, int index_v3, std::shared_ptr<Material> mat = nullptr);

//    inline void add_face(Face f) { _faces.push_back(f); }

    void apply_matrix(const core::util::Matrix4 &transformation);

    void make_ready();

    inline int get_vertices_size() const { return _vertices.size(); }
    inline int get_faces_size() const { return _faces.size(); }

//    inline const std::vector<core::util::Shared<Vertex>> &get_vertices() const { return _vertices; }

    inline const std::shared_ptr<Vertex> &get_vertice(int id) const { return _vertices[id]; }
    inline const Boundary& get_boundary() const { return boundary; }

    /**
     * @brief get_intercept
     * @param ray
     * @return <t_int, face> if intercepted, <-1.0, nullptr> otherwise.
     */

    std::pair<double, const Face*> get_intercept(const render::raycasting::Ray &ray, double t_int_minimum = 1.0) const;

private:
    std::shared_ptr<Material> _material;
    core::util::Vector3 _coordinates_min;
    core::util::Vector3 _coordinates_max;
    std::vector<std::shared_ptr<Vertex>> _vertices;
    std::vector<Face> _faces;
    Boundary boundary;

    void update_min_and_max(const core::util::Vector3 &coordinates);

};

}
}
