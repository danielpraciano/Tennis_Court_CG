#pragma once

#include <exception>

#include <scenario/include/light/light.h>
#include <scenario/include/object/face.h>

namespace scenario {
namespace light {

class PunctualInfinityLight : public Light {

public:
    PunctualInfinityLight(core::util::Vector3 direction_point, render::raycasting::Color intensity) :
        Light(intensity), direction_point_(direction_point) {}

    inline virtual const core::util::Vector3 &get_position() const override { throw std::logic_error("PunctualInfinityLight doesn't have a position!"); }

    inline virtual void apply_matrix(const core::util::Matrix4 &matrix) override {
        core::util::Vector4 direction4;

        direction4.head(3) = direction_point_;
        direction4(3)      = 1.0;

        direction4 = matrix * direction4;

        direction_point_ = direction4.head(3);
    }

    inline core::util::Vector3 get_direction_point() const { return direction_point_; }

    virtual render::raycasting::Color get_light_color(const core::util::Vector3 &ray_origin,
                                                      const object::Face &face_int, const core::util::Vector3 &p_int) const override;

private:
    core::util::Vector3 direction_point_;

};

}
}
