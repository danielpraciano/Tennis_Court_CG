#pragma once

#include <scenario/include/object/face.h>
#include <render/include/raycasting/color.h>

namespace scenario {
namespace light {

class Light {

public:
    virtual ~Light() {}

    virtual render::raycasting::Color get_light_color(const core::util::Vector3 &ray_origin,
                                                      const object::Face &face_int, const core::util::Vector3 &p_int) const = 0;

    inline const render::raycasting::Color &get_intensity() const {
        return intensity_;
    }

    virtual const core::util::Vector3 &get_position() const = 0;

    virtual void apply_matrix(const core::util::Matrix4 &matrix) = 0;

protected:
    render::raycasting::Color intensity_;

    Light(render::raycasting::Color intensity) : intensity_(intensity) {}

};

}
}
