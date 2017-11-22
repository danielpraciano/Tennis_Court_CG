#include <scenario/include/object/face.h>

namespace scenario {
namespace object {

double Face::get_intercept(const render::raycasting::Ray &ray) const {
    if (dot(_normal_vec, ray.get_p_ij_normalized()) >= 0)
        return -1.0;

    double t_int = _v1_dot_normal / dot(ray.get_p_ij(), _normal_vec);
    core::util::Vector3 point_int = ray.get_point(t_int);

    core::util::Vector3 p1 = cross(_v1->get_coordinates() - point_int, _v2->get_coordinates() - point_int);
    core::util::Vector3 p2 = cross(_v2->get_coordinates() - point_int, _v3->get_coordinates() - point_int);
    core::util::Vector3 p3 = cross(_v3->get_coordinates() - point_int, _v1->get_coordinates() - point_int);
//if ( dot(p1, p2) >= 0.0 && dot(p2, p3) >= 0.0 )
//std::cout << "t " << t_int << std::endl;
//    return ( dot(p1, p2) >= 0.0 && dot(p2, p3) >= 0.0 ) ? t_int : -1.0;
    return ( dot(_normal_vec, p1) >= 0.0 && dot(_normal_vec, p2) >= 0.0 && dot(_normal_vec, p3) >= 0.0 ) ? t_int : -1.0;

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
