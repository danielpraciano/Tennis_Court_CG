#pragma once

#include <scenario/include/light/light.h>
#include <scenario/include/object/face.h>

namespace scenario {
namespace light {

class PunctualInfinityLight : public Light {

public:
    PunctualInfinityLight(core::util::Vector3 direction_point, render::raycasting::Color intensity) :
        Light(intensity), _direction_point(direction_point) {}

    virtual render::raycasting::Color get_light_color(const object::Face &face_int, const core::util::Vector3 &p_int, bool prova=false) const override;

    inline core::util::Vector3 get_direction_point() const { return _direction_point; }

    inline virtual void apply_matrix(const core::util::Matrix4 &matrix) override {
        core::util::Vector4 direction4;

        direction4.head(3) = _direction_point;
        direction4(3) = 1.0;

        direction4 = matrix * direction4;

        _direction_point = direction4.head(3);
    }

private:
    core::util::Vector3 _direction_point;

};

}
}
