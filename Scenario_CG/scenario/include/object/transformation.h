#pragma once

#include <memory>

#include <string>
#include <vector>
#include <core/include/util.h>
#include <scenario/include/object/object.h>
#include <scenario/include/scenario.h>

namespace scenario {
namespace object {

class Transformation {

public:
    Transformation() : _was_applied(false) {}
    ~Transformation() {}

    void add_rotation(const core::util::Vector3 axis, const double angle, const bool inDegrees = true);
    void add_scale(const core::util::Vector3 scale_factors);
    void add_translation(const core::util::Vector3 translate_vector);
    // the other transformations are necessary???

    void add_to_apply(std::shared_ptr<Object> obj);

    void make_apply();

    inline bool is_applicable() const { return !_was_applied; }
    inline const core::util::Matrix4 &get_matrix() const { return _final_matrix; }
    inline const std::string &get_transformations_string() const { return _transformations_text; }

private:
    bool _was_applied;
    std::string _transformations_text;
    core::util::Matrix4 _final_matrix;
    std::vector<core::util::Matrix4> _matrices;
    std::vector<std::shared_ptr<Object>> _objects_to_apply;

    void calculate_final_matrix();

};

}
}
