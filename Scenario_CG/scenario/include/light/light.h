#pragma once

#include <scenario/include/object/face.h>
#include <render/include/raycasting/color.h>

namespace scenario {
namespace light {

class Light {

public:
    virtual ~Light() {}

    virtual render::raycasting::Color get_light_color(const core::util::Vector3 &eye, const object::Face &face_int, const core::util::Vector3 &p_int, bool prova=false) const = 0;

    inline const render::raycasting::Color &get_intensity() const {
        return _intensity;
    }

    inline virtual const core::util::Vector3 &get_position() const = 0;

    inline virtual void apply_matrix(const core::util::Matrix4 &matrix) = 0;

protected:
    render::raycasting::Color _intensity;

    Light(render::raycasting::Color intensity) : _intensity(intensity) {}

};

}
}
