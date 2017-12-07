#pragma once

#include <scenario/include/light/light.h>
#include <scenario/include/object/face.h>

namespace scenario {
namespace light {

class SpotLight : public Light {

public:
    SpotLight(core::util::Vector3 position, core::util::Vector3 direction_point,
              double openning_angle, render::raycasting::Color intensity) :
        Light(intensity), _openning_angle(openning_angle), _position(position),
        _direction_point(direction_point), _direction_vec(_direction_point - _position) {}

    virtual render::raycasting::Color get_light_color(const object::Face &face_int, const core::util::Vector3 &p_int, bool prova=false) const override;

//    inline const core::util::Vector3 &get_position() const { return _position; }

    inline double get_openning_angle() const { return _openning_angle; }

    inline virtual const core::util::Vector3 &get_position() const override { return _position; }

    inline virtual void apply_matrix(const core::util::Matrix4 &matrix) override {
        core::util::Vector4 position4, direction4;

        position4.head(3) = _position;
        direction4.head(3) = _direction_point;
        position4(3) = direction4(3) = 1.0;

        position4 = matrix * position4;
        direction4 = matrix * direction4;

        _position = position4.head(3);
        _direction_point = direction4.head(3);
    }

private:
    double _openning_angle;
    core::util::Vector3 _position, _direction_point, _direction_vec;

};

}
}
