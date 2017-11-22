#include <scenario/include/light/punctual_infinity_light.h>

namespace scenario {
namespace light {

render::raycasting::Color PunctualInfinityLight::get_light_color(const object::Face &face_int, const core::util::Vector3 &p_int, bool prova) const {
    const object::Material &face_mat = face_int.get_material();
    core::util::Vector3 face_normal = face_int.get_normal();

    core::util::Vector3 l = -_direction_point;
    core::util::Vector3 v = normalise(-p_int);
    core::util::Vector3 r = 2 * dot(l, face_normal) * face_normal - l;

    if (prova) {
        std::cout << "VECTOR_n:" << std::endl << face_normal << std::endl;
        std::cout << "VECTOR_l:" << std::endl << l << std::endl;
        std::cout << "VECTOR_v:" << std::endl << v << std::endl;
        std::cout << "VECTOR_r:" << std::endl << r << std::endl;
    }

    double n_dot_l = dot(face_normal, l);
    double v_dot_r_m = std::pow(dot(v, r), face_mat.get_m());

    // = is valid?? I think!!
    if (n_dot_l <= 0 && v_dot_r_m <= 0) {
        return render::raycasting::Color { 0.0, 0.0, 0.0 };
    } else if (n_dot_l <= 0) {
        return render::raycasting::Color { v_dot_r_m * ( face_mat.get_k_specular().get_values() % _intensity.get_values() ) };
    } else if (v_dot_r_m <= 0) {
        return render::raycasting::Color { n_dot_l * ( face_mat.get_k_diffuse().get_values() % _intensity.get_values() ) };
    }

    core::util::Vector3 diffuse = n_dot_l * ( face_mat.get_k_diffuse().get_values() % _intensity.get_values() );
    core::util::Vector3 specular = v_dot_r_m * ( face_mat.get_k_specular().get_values() % _intensity.get_values() );

    return render::raycasting::Color { diffuse + specular };
}

}
}
