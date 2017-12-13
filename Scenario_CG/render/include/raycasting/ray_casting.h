#pragma once

#include <render/include/raycasting/color.h>
#include <render/include/raycasting/camera.h>
#include <render/include/raycasting/projection_type.h>
#include <scenario/include/scenario.h>
#include <core/include/constants.h>

namespace render {
namespace raycasting {

class RayCasting {

public:
    RayCasting(double distance, double width, double height, Color background_color = Color {}) :
        distance_(distance), width_(width), height_(height), background_color_(background_color) {
          delta_row_ = width_ / core::constants::COLS_PIXELS;
          delta_col_ = height_ / core::constants::ROWS_PIXELS;

        frame_buffer_ = new Color*[core::constants::ROWS_PIXELS];

        #pragma omp parallel for
        for (uint64_t i = 0; i < core::constants::ROWS_PIXELS; ++i)
            frame_buffer_[i] = new Color[core::constants::COLS_PIXELS];

         }

    ~RayCasting() {
        #pragma omp parallel for
        for (uint64_t i = 0; i < core::constants::ROWS_PIXELS; ++i)
            delete[] frame_buffer_[i];

        delete[] frame_buffer_;
    }

    inline Color** get_frame_buffer() const { return frame_buffer_; }

    void render(const Camera &camera, scenario::Scenario scenario, ProjectionType proj = ProjectionType::PERSPECTIVE,
                double oblique_angle = 0.0, double oblique_factor = 1.0);

private:
    double distance_, width_, height_, delta_row_, delta_col_;
    Color background_color_, **frame_buffer_;

    Color calculate_color(const Ray &viewing_ray, const scenario::Scenario &scenario) const;

};

}
}
