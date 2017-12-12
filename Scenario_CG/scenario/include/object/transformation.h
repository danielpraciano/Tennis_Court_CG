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
    Transformation() : was_applied_(false) {}
    ~Transformation() {}

    inline bool is_applicable() const { return !was_applied_; }
    inline const std::string &get_transformations_string() const { return transformations_text_; }
    inline const core::util::Matrix4 &get_matrix() const { return final_matrix_; }

    void add_rotation(const core::util::Vector3 &axis, double angle, bool in_degrees = true);
    void add_scale(const core::util::Vector3 &scale_factors);
    void add_translation(const core::util::Vector3 &translate_vector);

    void add_to_apply(std::shared_ptr<Object> obj);

    void make_apply();

private:
    bool was_applied_;
    std::string transformations_text_;
    core::util::Matrix4 final_matrix_;
    std::vector<core::util::Matrix4> matrices_;
    std::vector<std::shared_ptr<Object>> objects_to_apply;

    void calculate_final_matrix();

};

}
}
