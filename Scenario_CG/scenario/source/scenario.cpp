 #include <scenario/include/scenario.h>

namespace scenario {

void Scenario::apply_matrix(const core::util::Matrix4 &matrix) {
//    ambient_light->apply_matrix(matrix);

    #pragma omp parallel for
    for (size_t i = 0; i < lights.size(); ++i)
        lights[i]->apply_matrix(matrix);


//    for (auto &light : lights)
//        light->apply_matrix(matrix);

    #pragma omp parallel for
    for (size_t i = 0; i < objects.size(); ++i)
        objects[i].apply_matrix(matrix);

//    for (object::Object &obj : objects)
//        obj.apply_matrix(matrix);
}

}
