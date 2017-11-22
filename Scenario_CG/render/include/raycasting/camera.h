#pragma once

#include <core/include/util.h>
#include <scenario/include/scenario.h>

namespace render {
namespace raycasting {

class Camera {

public:
    Camera(core::util::Vector3 eye, core::util::Vector3 look_at, core::util::Vector3 view_up) :
        _eye(eye), _look_at(look_at), _view_up(view_up) { calculate_matrices(); }
    ~Camera() {}

    inline void to_world(scenario::Scenario &sc) { sc.apply_matrix(_M_c_to_w); }
    inline void to_camera(scenario::Scenario &sc) { sc.apply_matrix(_M_w_to_c); }

    inline const core::util::Matrix4 &get_world_to_camera() const { return _M_w_to_c; }
    inline const core::util::Matrix4 &get_camera_to_world() const { return _M_c_to_w; }

private:
    core::util::Vector3 _eye, _look_at, _view_up;
    core::util::Vector3 _ic, _jc, _kc;
    core::util::Matrix4 _M_w_to_c, _M_c_to_w;

    void calculate_matrices();

};

}
}
