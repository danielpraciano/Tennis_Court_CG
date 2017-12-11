//#include <utility>
//#include <functional>
#include <render/include/raycasting/ray_casting.h>

namespace render {
namespace raycasting {

void RayCasting::render(Camera camera, scenario::Scenario scenario, bool Falta_Escolher_Qual_Tipo_Projecao) {
    camera.to_camera(scenario);

    scenario.make();

//    for (int i = 0; i < _rows_pixels; i++) {
    #pragma omp parallel for
    for (int i = 0; i < core::constants::ROWS_PIXELS; i++) {
//    for (int i = 0; i < core::constants::COLS_PIXELS; i++) {
        double y_i = (_height / 2) - (_delta_col / 2) - i * _delta_col;

//        for (int j = 0; j < _cols_pixels; j++) {
        #pragma omp parallel for
        for (int j = 0; j < core::constants::COLS_PIXELS; j++) {
//        for (int j = 0; j < core::constants::ROWS_PIXELS; j++) {
            double x_ij = (-_width / 2) + (_delta_row / 2) + j * _delta_row;
//            std::cout << i << " " << j << std::endl;
            core::util::Vector3 p_ij { x_ij, y_i, -_distance };
            Ray viewing_ray { core::util::Vector3 { 0.0, 0.0, 0.0 }, p_ij };

//            viewing_ray = { core::util::Vector3 { 0.0, 0.0, 0.0 }, p_ij };

            viewing_ray = { p_ij, core::util::Vector3 { 0.0, 0.0, -1.0 } };

            _frame_buffer[i][j] = calculate_color(viewing_ray, scenario);

        }
    }

}

//Color RayCasting::calculate_color_prova(const core::util::Vector3 &p_ij, const scenario::Scenario &scenario,
//                                        scenario::object::Face& face_int, double t_int) const {
//    Ray ray { core::util::Vector3 { 0.0, 0.0, 0.0 }, p_ij };

////    core::util::Vector3 p_int = ray.get_point(t_int);
//    core::util::Vector3 p_int = ray.get_point_direction_normalized(t_int);

//    core::util::Vector3 normal = core::util::Vector3 { -4.0, 4.0, -3.0 } - p_int;
//    // face_int.set_normal(normalise(cam.get_world_to_camera() * normal));
//    face_int.set_normal(normalise(normal));

//    std::cout << "Pij:" << std::endl << p_ij << std::endl;

//    std::cout << "Pint:" << std::endl << p_int << std::endl;

//    core::util::Vector3 ambient_intensity = scenario.get_ambient_light()->get_intensity().get_values();

//    core::util::Vector3 color_values = face_int.get_material().get_k_ambient().get_values() % ambient_intensity;

//    std::cout << "COLOR_AMBIENT:" << std::endl << color_values << std::endl;

//    for (const auto &light : scenario.get_lights()) {
//        color_values += light->get_light_color(face_int, p_int, true).get_values();
//    }

//    return Color { color_values };

//}

Color RayCasting::calculate_color(const Ray &viewing_ray, const scenario::Scenario &scenario) const {
    double t_int = std::numeric_limits<double>::max();
    const scenario::object::Face *face_int = nullptr;

    for (const scenario::object::Object &obj : scenario.get_objects()) {
        auto inter_obj = obj.get_intercept(viewing_ray);
//std::cout << inter_obj.first << std::endl;
        //>= or only >???
        if (inter_obj.first >= 1.0 && inter_obj.first < t_int) {
            t_int = inter_obj.first;
            face_int = inter_obj.second;
        }
    }

    if (t_int == std::numeric_limits<double>::max())
        return Color { _background_color.get_values()(0) * 255, _background_color.get_values()(1) * 255, _background_color.get_values()(2) * 255 };
//std::cout << t_int << std::endl;
    core::util::Vector3 p_int = viewing_ray.get_point(t_int);

    core::util::Vector3 ambient_intensity = scenario.get_ambient_light()->get_intensity().get_values();
//    core::util::Vector3 ambient_intensity = scenario.get_ambient_light().get_intensity().get_values();
    core::util::Vector3 color_values = face_int->get_material().get_k_ambient().get_values() % ambient_intensity;

    for (const auto &light : scenario.get_lights()) {

        Ray shadow_ray { p_int, light->get_position() - p_int };

        bool there_is_another_obj = false;

        for (const scenario::object::Object &obj : scenario.get_objects()) {
            auto inter_obj = obj.get_intercept(shadow_ray, 0.0);

            // is it necessary to have inter_obj.first >= 0.0 && inter_obj.first <= 1.0??? YES!!!!
            if (inter_obj.first >= 0.0 && inter_obj.first <= 1.0 && inter_obj.second != face_int) {
                there_is_another_obj = true;
                break;
            }

        }

        if (!there_is_another_obj)
            color_values += light->get_light_color(viewing_ray.get_origin(), *face_int, p_int).get_values();
//        color_values += light.get_light_color(*face_int, p_int).get_values();
    }

    //255 or 256???
    color_values = round(color_values * 255.0);

    color_values(0) = std::min(color_values(0), 255.0);
    color_values(1) = std::min(color_values(1), 255.0);
    color_values(2) = std::min(color_values(2), 255.0);

    return Color { color_values };

}

}
}
