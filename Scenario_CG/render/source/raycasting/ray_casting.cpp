#include <render/include/raycasting/ray_casting.h>

namespace render {
namespace raycasting {

void RayCasting::render(const Camera &camera, scenario::Scenario scenario, ProjectionType proj,
                        double oblique_angle, double oblique_factor) {
    camera.to_camera(scenario);

    scenario.make();

    #pragma omp parallel for
    for (int i = 0; i < core::constants::ROWS_PIXELS; ++i) {
        double y_i = (height_ / 2) - (delta_col_ / 2) - i * delta_col_;

        #pragma omp parallel for
        for (int j = 0; j < core::constants::COLS_PIXELS; ++j) {
            double x_ij = (-width_ / 2) + (delta_row_ / 2) + j * delta_row_;

            core::util::Vector3 p_ij { x_ij, y_i, -distance_ };

            Ray viewing_ray { core::util::Vector3 { 0.0, 0.0, 0.0 }, p_ij };

            switch (proj) {
            case ProjectionType::PERSPECTIVE:
                break;

            case ProjectionType::ORTHOGRAPHIC:
                viewing_ray = { p_ij, core::util::Vector3 { 0.0, 0.0, -1.0 } };
                break;

            case ProjectionType::OBLIQUE:
            {
                double x = -oblique_factor * std::cos(oblique_angle);
                double y = -oblique_factor * std::sin(oblique_angle);
                double z = -oblique_factor;

                viewing_ray = { p_ij, core::util::Vector3 { x, y, z } };
                break;
            }

            case ProjectionType::CAVALIER:
            {
                double x = -std::sqrt(2.0) / 2.0 * std::cos(oblique_angle);
                double y = -std::sqrt(2.0) / 2.0 * std::sin(oblique_angle);
                double z = -std::sqrt(2.0) / 2.0;

                viewing_ray = { p_ij, core::util::Vector3 { x, y, z } };
                break;
            }

            case ProjectionType::CABINET:
            {
                double x = -1.0 / std::sqrt(5.0) * std::cos(oblique_angle);
                double y = -1.0 / std::sqrt(5.0) * std::sin(oblique_angle);
                double z = -1.0 / std::sqrt(5.0) * 2;

                viewing_ray = { p_ij, core::util::Vector3 { x, y, z } };
                break;
            }
            }

            frame_buffer_[i][j] = calculate_color(viewing_ray, scenario);

        }
    }

}

Color RayCasting::calculate_color(const Ray &viewing_ray, const scenario::Scenario &scenario) const {
    double t_int = std::numeric_limits<double>::max();
    const scenario::object::Face *face_int = nullptr;

    for (const scenario::object::Object &obj : scenario.get_objects()) {
        auto inter_obj = obj.get_intercept(viewing_ray);

        if (inter_obj.first >= 1.0 && inter_obj.first < t_int) {
            t_int = inter_obj.first;
            face_int = inter_obj.second;
        }
    }

    if (t_int == std::numeric_limits<double>::max())
        return Color { background_color_.get_values()(0) * 255, background_color_.get_values()(1) * 255, background_color_.get_values()(2) * 255 };

    const core::util::Vector3 p_int = viewing_ray.get_point(t_int);

    core::util::Vector3 ambient_intensity = scenario.get_ambient_light()->get_intensity().get_values();

    core::util::Vector3 color_values = face_int->get_material().get_k_ambient().get_values() % ambient_intensity;

    for (const auto &light : scenario.get_lights()) {
        Ray shadow_ray { p_int, light->get_position() - p_int };

        bool there_is_another_obj = false;

        for (const scenario::object::Object &obj : scenario.get_objects()) {
            auto inter_obj = obj.get_intercept(shadow_ray, 0.0);

            if (inter_obj.first >= 0.0 && inter_obj.first <= 1.0 && inter_obj.second != face_int) {
                there_is_another_obj = true;
                break;
            }
        }

        if (!there_is_another_obj)
            color_values += light->get_light_color(viewing_ray.get_origin(), *face_int, p_int).get_values();
    }

    color_values = round(color_values * 255.0);

    color_values(0) = std::min(color_values(0), 255.0);
    color_values(1) = std::min(color_values(1), 255.0);
    color_values(2) = std::min(color_values(2), 255.0);

    return Color { color_values };

}

}
}
