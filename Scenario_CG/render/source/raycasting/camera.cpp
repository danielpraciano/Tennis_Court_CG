#include <render/include/raycasting/camera.h>
//#include <scenario/include/object.h>

namespace render {
namespace raycasting {

//void Camera::to_world(scenario::Object &obj) {
//    obj.apply_matrix(M_c_to_w);
//}

//void Camera::to_camera(scenario::Object &obj) {
//    obj.apply_matrix(M_w_to_c);
//}

void Camera::calculate_matrices() {
    kc_ = normalise(eye_ - look_at_);
    ic_ = normalise(cross(view_up_ - eye_, kc_));
    jc_ = cross(kc_, ic_);

    M_c_to_w_.eye();

    M_c_to_w_.col(0).head(3) = ic_;
    M_c_to_w_.col(1).head(3) = jc_;
    M_c_to_w_.col(2).head(3) = kc_;
    M_c_to_w_.col(3).head(3) = eye_;

    M_w_to_c_.eye();

    M_w_to_c_.row(0).head(3) = ic_.t();
    M_w_to_c_.row(1).head(3) = jc_.t();
    M_w_to_c_.row(2).head(3) = kc_.t();
    M_w_to_c_.col(3).head(3) = core::util::Vector3 {-dot(ic_, eye_), -dot(jc_, eye_), -dot(kc_, eye_)};

}

}
}
