#include <limits>
#include <scenario/include/object/object.h>

namespace scenario {
namespace object {

void Object::add_face(int index_v1, int index_v2, int index_v3, std::shared_ptr<Material> mat) {
//    auto v1 = std::make_shared<Vertex> ( _vertices[index_v1] );
//    auto v2 = std::make_shared<Vertex> ( _vertices[index_v2] );
//    auto v3 = std::make_shared<Vertex> ( _vertices[index_v3] );

    auto v1 = vertices[index_v1];
    auto v2 = vertices[index_v2];
    auto v3 = vertices[index_v3];

    if (mat)
        faces_.push_back(Face { mat, v1, v2, v3 });
    else
        faces_.push_back(Face { material, v1, v2, v3 });
}

void Object::apply_matrix(const core::util::Matrix4 &transformation) {
//    for (Vertex &vertex : _vertices)
    for (auto &vertex : vertices)
        vertex->apply_matrix(transformation);
}

void Object::make_ready() {
//    std::cout << _vertices[0]->get_coordinates() << std::endl;
//    for (const Vertex &vertex : _vertices)
    for (const auto &vertex : vertices)
        update_min_and_max(vertex->get_coordinates());

    boundary_.generate(coordinates_min_, coordinates_max_);

    #pragma omp parallel for
    for (size_t i = 0; i < faces_.size(); ++i)
        faces_[i].calculate_normal();

//    for (Face &face : faces_)
//        face.calculate_normal();
}

std::pair<double, const Face*> Object::get_intercept(const render::raycasting::Ray &ray, double t_int_minimum) const {
    double t_int_result = std::numeric_limits<double>::max();
    const Face *face_result = nullptr;
//verify this method!!!
    if (boundary_.is_intercepted(ray)) {
        for (const Face &face : faces_) {

            double t_int = face.get_intercept(ray);

            // > or > only ???
            if (t_int >= t_int_minimum && t_int < t_int_result) {
                t_int_result  = t_int;
                face_result = &face;
            }

        }
    }

    if (t_int_result == std::numeric_limits<double>::max())
        t_int_result = -1.0;

    return std::make_pair(t_int_result, face_result);
}

void Object::update_min_and_max(const core::util::Vector3 &coordinates) {
    if (coordinates(0) < coordinates_min_(0))
        coordinates_min_(0) = coordinates(0);

    if (coordinates(0) > coordinates_max_(0))
        coordinates_max_(0) = coordinates(0);

    if (coordinates(1) < coordinates_min_(1))
        coordinates_min_(1) = coordinates(1);

    if (coordinates(1) > coordinates_max_(1))
        coordinates_max_(1) = coordinates(1);

    if (coordinates(2) < coordinates_min_(2))
        coordinates_min_(2) = coordinates(2);

    if (coordinates(2) > coordinates_max_(2))
        coordinates_max_(2) = coordinates(2);
}

}
}
