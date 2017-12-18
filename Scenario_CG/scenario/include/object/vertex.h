#pragma once

#include <core/include/util.h>

namespace scenario {
namespace object {

class Vertex {

public:
    Vertex(double x, double y, double z) : _coordinates(core::util::Vector4 { x, y, z, 1.0 }) {}
    Vertex(core::util::Vector3 coordinates) {
        _coordinates.head(3) = coordinates; _coordinates(3) = 1.0; }

//    inline const core::util::Vector3 &get_coordinates() const {
//        return _coordinates.head(3);
//    }
    inline core::util::Vector3 get_normal() const {
        return _normal;
    }

    inline core::util::Vector3 get_coordinates() const {
        return _coordinates.head(3);
    }

    inline void set_normal(core::util::Vector3 normal) {
        _normal = normal;
    }

    inline void apply_matrix(const core::util::Matrix4 &matrix) {
        _coordinates = matrix * _coordinates;
    }

private:
    core::util::Vector4 _coordinates;
    core::util::Vector3 _normal;
};

}
}
