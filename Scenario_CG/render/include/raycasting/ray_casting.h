#pragma once

#include <render/include/raycasting/color.h>
#include <render/include/raycasting/camera.h>
#include <scenario/include/scenario.h>
#include <core/include/constants.h>

namespace render {
namespace raycasting {

class RayCasting {

public:
    RayCasting(double distance, double width, double height, Color background_color = Color {}) :
        _distance(distance), _width(width), _height(height), _background_color(background_color) {
//        _delta_row = _height / core::constants::ROWS_PIXELS; _delta_col = _width / core::constants::COLS_PIXELS;
          _delta_row = _width / core::constants::COLS_PIXELS; _delta_col = _height / core::constants::ROWS_PIXELS;

        _frame_buffer = new Color*[core::constants::ROWS_PIXELS];

        for (uint64_t i = 0; i < core::constants::ROWS_PIXELS; ++i)
            _frame_buffer[i] = new Color[core::constants::COLS_PIXELS];

         }

    ~RayCasting() {
        for (uint64_t i = 0; i < core::constants::ROWS_PIXELS; ++i)
            delete[] _frame_buffer[i];

        delete[] _frame_buffer;
    }

    Color calculate_color_prova(const core::util::Vector3 &p_ij, const scenario::Scenario &scenario,
                                scenario::object::Face& face_int, double t_int) const;

    void render(Camera camera, scenario::Scenario scenario);

    inline Color** get_frame_buffer() const { return _frame_buffer; }

private:
    double _distance, _width, _height, _delta_row, _delta_col;
    Color **_frame_buffer, _background_color;

    Color calculate_color(const core::util::Vector3 &p_ij, const scenario::Scenario &scenario) const;

};

}
}
