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
    _kc = normalise(_eye - _look_at);
    _ic = normalise(cross(_view_up - _eye, _kc));
    _jc = cross(_kc, _ic);

    _M_c_to_w.eye();

    _M_c_to_w.col(0).head(3) = _ic;
    _M_c_to_w.col(1).head(3) = _jc;
    _M_c_to_w.col(2).head(3) = _kc;
    _M_c_to_w.col(3).head(3) = _eye;

    _M_w_to_c.eye();

    _M_w_to_c.row(0).head(3) = _ic.t();
    _M_w_to_c.row(1).head(3) = _jc.t();
    _M_w_to_c.row(2).head(3) = _kc.t();
    _M_w_to_c.col(3).head(3) = core::util::Vector3 {-dot(_ic, _eye), -dot(_jc, _eye), -dot(_kc, _eye)};

}

}
}
