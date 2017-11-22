 #include <scenario/include/scenario.h>

namespace scenario {

void Scenario::apply_matrix(const core::util::Matrix4 &matrix) {
    _ambient_light->apply_matrix(matrix);
//    _ambient_light.apply_matrix(matrix);

    for (auto &light : _lights)
        light->apply_matrix(matrix);
//        light.apply_matrix(matrix);

    for (object::Object &obj : _objects)
        obj.apply_matrix(matrix);
}

}
