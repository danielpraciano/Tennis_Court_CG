#pragma once

#include <scenario/include/light/light.h>
#include <scenario/include/object/face.h>

namespace scenario {
namespace light {

class PunctualLight : public Light {

public:
    PunctualLight(core::util::Vector3 position, render::raycasting::Color intensity) :
        Light(intensity), _position(position) {}

    virtual render::raycasting::Color get_light_color(const core::util::Vector3 &eye, const object::Face &face_int, const core::util::Vector3 &p_int, bool prova=false) const override;

//    inline core::util::Vector3 get_position() const { return _position; }

    inline virtual const core::util::Vector3 &get_position() const override { return _position; }

    inline virtual void apply_matrix(const core::util::Matrix4 &matrix) override {
        core::util::Vector4 position4;

        position4.head(3) = _position;
        position4(3) = 1.0;

        position4 = matrix * position4;

        _position = position4.head(3);
    }

private:
    core::util::Vector3 _position;

};

}
}
