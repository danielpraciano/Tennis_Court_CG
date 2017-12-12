#pragma once

#include <core/include/util.h>
#include <scenario/include/scenario.h>

namespace render {
namespace raycasting {

class Camera {

public:
    Camera(core::util::Vector3 eye, core::util::Vector3 look_at, core::util::Vector3 view_up) :
        eye_(eye), look_at_(look_at), view_up_(view_up) { calculate_matrices(); }
    ~Camera() {}

    inline void to_world(scenario::Scenario &sc)  const { sc.apply_matrix(M_c_to_w_); }
    inline void to_camera(scenario::Scenario &sc) const { sc.apply_matrix(M_w_to_c_); }

    inline const core::util::Matrix4 &get_world_to_camera() const { return M_w_to_c_; }
    inline const core::util::Matrix4 &get_camera_to_world() const { return M_c_to_w_; }

private:
    core::util::Vector3 eye_, look_at_, view_up_;
    core::util::Vector3 ic_, jc_, kc_;
    core::util::Matrix4 M_w_to_c_, M_c_to_w_;

    void calculate_matrices();

};

}
}
