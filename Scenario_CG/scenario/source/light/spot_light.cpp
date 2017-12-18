#include <scenario/include/light/spot_light.h>

namespace scenario {
namespace light {

render::raycasting::Color SpotLight::get_light_color(const core::util::Vector3 &ray_origin,
                                                     const object::Face &face_int, const core::util::Vector3 &p_int) const {
    const object::Material    &face_mat    = face_int.get_material();
    const core::util::Vector3 &face_normal = face_int.get_normal();

    const core::util::Vector3 l = normalise(position_ - p_int);

    double dir_dot_minus_l = dot(direction_vec_, -l);

    if (dir_dot_minus_l > std::cos(openning_angle_ * arma::datum::pi / 180 ))
        return render::raycasting::Color { 0.0, 0.0, 0.0 };

    const core::util::Vector3 v = normalise(ray_origin - p_int);
    const core::util::Vector3 r = 2 * dot(l, face_normal) * face_normal - l;

    const core::util::Vector3 intensity = dir_dot_minus_l * intensity_.get_values();

    double n_dot_l = dot(face_normal, l);
    double v_dot_r_m = std::pow(dot(v, r), face_mat.get_reflexive_coef());

    core::util::Vector3 diffuse;
    core::util::Vector3 specular;

    diffuse.zeros();
    specular.zeros();


//    // = is valid?? I think!!
//    if (n_dot_l <= 0 && v_dot_r_m <= 0) {
//        return render::raycasting::Color { 0.0, 0.0, 0.0 };
//    } else if (n_dot_l <= 0) {
//        return render::raycasting::Color { v_dot_r_m * ( face_mat.get_k_specular().get_values() % intensity ) };
//    } else if (v_dot_r_m <= 0) {
//        return render::raycasting::Color { n_dot_l * ( face_mat.get_k_diffuse().get_values() % intensity ) };
//    }

//    core::util::Vector3 diffuse = n_dot_l * ( face_mat.get_k_diffuse().get_values() % intensity );
//    core::util::Vector3 specular = v_dot_r_m * ( face_mat.get_k_specular().get_values() % intensity );

    if (n_dot_l > 0) {
        diffuse  = n_dot_l * ( face_mat.get_k_diffuse().get_values() % intensity );
        specular = std::max(0.0, v_dot_r_m) * ( face_mat.get_k_specular().get_values() % intensity );
    }

    return render::raycasting::Color { diffuse + specular };
}

}
}
