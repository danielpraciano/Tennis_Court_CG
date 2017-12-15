#pragma once

#include <scenario/include/light/light.h>
#include <scenario/include/object/face.h>

namespace scenario {
namespace light {

class SpotLight : public Light {

public:
    SpotLight(core::util::Vector3 position, core::util::Vector3 direction_point,
              double openning_angle, render::raycasting::Color intensity) :
        Light(intensity), openning_angle_(openning_angle * arma::datum::pi / 180.0), position_(position),
        direction_point_(direction_point), direction_vec_(normalise(direction_point_ - position_)) {}

    inline virtual const core::util::Vector3 &get_position() const override { return position_; }

    inline virtual void apply_matrix(const core::util::Matrix4 &matrix) override {
        core::util::Vector4 position4, direction4;

        position4.head(3)  = position_;
        direction4.head(3) = direction_point_;
        position4(3)       = direction4(3) = 1.0;

        position4  = matrix * position4;
        direction4 = matrix * direction4;

        position_        = position4.head(3);
        direction_point_ = direction4.head(3);
    }

    inline double get_openning_angle() const { return openning_angle_; }

    virtual render::raycasting::Color get_light_color(const core::util::Vector3 &ray_origin,
                                                      const object::Face &face_int, const core::util::Vector3 &p_int) const override;

private:
    double openning_angle_;
    core::util::Vector3 position_, direction_point_, direction_vec_;

};

}
}
