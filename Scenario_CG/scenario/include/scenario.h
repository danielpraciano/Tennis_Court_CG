#pragma once

#include <vector>
#include <scenario/include/object/object.h>
#include <scenario/include/light/light.h>

#include <scenario/include/light/punctual_light.h>

namespace scenario {

class Scenario {

public:
    Scenario(light::Light *ambient_light) : ambient_light(ambient_light) {}
    ~Scenario() {}

    inline const light::Light *get_ambient_light() const { return ambient_light; }

    inline const light::Light *get_light(int index) const { return lights[index]; }

    inline const std::vector<light::Light*> &get_lights() const { return lights; }

    inline const object::Object &get_object(int index) const { return objects[index]; }

    inline const std::vector<object::Object> &get_objects() const { return objects; }

    inline void add_light(light::Light *light) { lights.push_back(light); }

    inline void add_object(object::Object obj) { objects.push_back(obj); }

    void apply_matrix(const core::util::Matrix4 &matrix);

    inline void make() {
        #pragma omp parallel for
        for (size_t i = 0; i < objects.size(); ++i)
            objects[i].make_ready();


//        for (object::Object &obj : objects)
//            obj.make_ready();
    }

private:
    light::Light *ambient_light;
    std::vector<light::Light*> lights;
    std::vector<object::Object> objects;

};

}
