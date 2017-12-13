#pragma once

#include <render/include/raycasting/color.h>

namespace scenario {
namespace object {

class Material {

public:
    Material(double m, render::raycasting::Color k_amb, render::raycasting::Color k_diff, render::raycasting::Color k_spec) :
        reflexive_coef_(m), k_ambient_(k_amb), k_diffuse_(k_diff), k_specular_(k_spec) {}
    ~Material() {}

    inline double get_reflexive_coef() const { return reflexive_coef_; }

    inline const render::raycasting::Color &get_k_ambient() const  { return k_ambient_; }

    inline const render::raycasting::Color &get_k_diffuse() const  { return k_diffuse_; }

    inline const render::raycasting::Color &get_k_specular() const { return k_specular_; }

private:
    double reflexive_coef_;
    render::raycasting::Color k_ambient_, k_diffuse_, k_specular_;

};

}
}
