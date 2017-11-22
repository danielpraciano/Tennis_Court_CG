#pragma once

#include <vector>
#include <scenario/include/object/object.h>
#include <scenario/include/light/light.h>

#include <scenario/include/light/punctual_light.h>

namespace scenario {

class Scenario {

public:
    Scenario(light::Light *ambient_light) : _ambient_light(ambient_light) {}
//    Scenario(light::PunctualLight ambient_light) : _ambient_light(ambient_light) {}
    ~Scenario() {}

    inline void make() {
        for (object::Object &obj : _objects)
            obj.make_ready();
    }

    void apply_matrix(const core::util::Matrix4 &matrix);

//    inline void set_ambient_light(core::util::Unique<Light> ambient_light) { _ambient_light = std::move(ambient_light); }

    inline void add_light(light::Light *light) { _lights.push_back(light); }
//    inline void add_light(light::PunctualLight light) { _lights.push_back(std::move(light)); }

    // implement deletion after!!
//    inline void rmv_light(const int index) { _lights. }

    inline const light::Light *get_ambient_light() const { return _ambient_light; }
//    inline const light::PunctualLight &get_ambient_light() const { return _ambient_light; }

    inline const light::Light *get_light(int index) const { return _lights[index]; }
//    inline const light::PunctualLight &get_light(int index) const { return _lights[index]; }

    inline const std::vector<light::Light*> &get_lights() const { return _lights; }
//    inline const std::vector<light::PunctualLight> &get_lights() const { return _lights; }

    inline void add_object(object::Object obj) { _objects.push_back(obj); }

    //const??
    inline const object::Object &get_object(int index) const { return _objects[index]; }

    inline const std::vector<object::Object> &get_objects() const { return _objects; }

private:
//    light::PunctualLight _ambient_light;
    light::Light *_ambient_light;
    std::vector<light::Light*> _lights;
//    std::vector<light::PunctualLight> _lights;
    std::vector<object::Object> _objects;

};

}
