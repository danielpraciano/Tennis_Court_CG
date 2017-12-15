#include <exception>

#include <scenario/include/object/face.h>

namespace scenario {
namespace object {

double Face::get_intercept(const render::raycasting::Ray &ray) const {
    double normal_dot_direction = dot(normal_vec_, ray.get_direction());

    if (normal_dot_direction >= 0)
        return -1.0;

    double t_int = dot(v1->get_coordinates() - ray.get_origin(), normal_vec_) / normal_dot_direction;

    const core::util::Vector3 point_int = ray.get_point(t_int);

    const core::util::Vector3 p1 = cross(v1->get_coordinates() - point_int, v2->get_coordinates() - point_int);
    const core::util::Vector3 p2 = cross(v2->get_coordinates() - point_int, v3->get_coordinates() - point_int);
    const core::util::Vector3 p3 = cross(v3->get_coordinates() - point_int, v1->get_coordinates() - point_int);

    return ( dot(normal_vec_, p1) >= 0.0 && dot(normal_vec_, p2) >= 0.0 && dot(normal_vec_, p3) >= 0.0 ) ? t_int : -1.0;

}

render::raycasting::Color Face::get_rgb_tex(const core::util::Vector3 &p_int) const {
    if (tex == nullptr)
        throw new std::logic_error("Not exist texture in this face.");

    if (vertex_left_ref_to_tex == nullptr)
        throw new std::logic_error("Not exist vertex reference for texture in this face.");

    core::util::Vector3 distance = arma::abs(arma::abs(p_int) - arma::abs(vertex_left_ref_to_tex->get_coordinates()));

    auto dimensions = tex->get_dimensions();

    int i = 0, j = 0;

    switch (plan_to_tex_) {
    case 0:
        i = 2;
        j = 1;
        break;

    case 1:
        i = 0;
        j = 2;
        break;

    case 2:
        i = 0;
        j = 1;
        break;
    }

    if (distance(i) > 1)
        std::cout << "test" << std::endl;

    if (distance(j) > 1)
        std::cout << "test" << std::endl;

    uint64_t u = std::floor(distance(i) / dx_ * dimensions.first);
    uint64_t v = std::floor(distance(j) / dy_ * dimensions.second);

//    std::cout << dx_ << " " << dy_ << std::endl;

//    std::cout << dimensions.first << " " << dimensions.second << std::endl;

    return tex->get_rgb_tex(u, v);
}

//double Face::get_intercept(const render::raycasting::Ray &ray) const {
//    if (dot(_normal_vec, ray.get_p_ij_normalized()) >= 0)
//        return -1.0;

//    core::util::Matrix3 A;

//    A.col(0) = _v3->get_coordinates() - _v1->get_coordinates();
//    A.col(1) = _v3->get_coordinates() - _v2->get_coordinates();
//    A.col(2) = ray.get_p_ij();

////    core::util::Vector3 lamb1_lamb2_tint = inv(A) * _v3->get_coordinates();
//    // The two below lines are more efficient than the above one, is it true??
//    core::util::Vector3 lamb1_lamb2_tint;
//    if ( !solve(lamb1_lamb2_tint, A, _v3->get_coordinates(), arma::solve_opts::fast + arma::solve_opts::no_approx) )
//        return -1.0;

//    double lamb1 = lamb1_lamb2_tint(0);
//    double lamb2 = lamb1_lamb2_tint(1);
//    double t_int = lamb1_lamb2_tint(2);

//    return ( lamb1 >= 0 && lamb2 >= 0 && lamb1 + lamb2 < 1 ) ? t_int : -1.0;

//}

}
}
