#pragma once

#include <render/include/raycasting/color.h>

namespace scenario {
namespace object {

class Material {

public:
    Material(double m, render::raycasting::Color k_amb, render::raycasting::Color k_diff, render::raycasting::Color k_spec) :
        reflexive_coef_(m), _k_ambient(k_amb), _k_diffuse(k_diff), _k_specular(k_spec) {}
    ~Material() {}

    inline double get_reflexive_coef() const { return reflexive_coef_; }

    inline const render::raycasting::Color &get_k_ambient() const  { return _k_ambient; }

    inline const render::raycasting::Color &get_k_diffuse() const  { return _k_diffuse; }

    inline const render::raycasting::Color &get_k_specular() const { return _k_specular; }

private:
    double reflexive_coef_;
    render::raycasting::Color _k_ambient, _k_diffuse, _k_specular;

};

}
}
