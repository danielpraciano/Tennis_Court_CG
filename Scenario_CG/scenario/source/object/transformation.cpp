#include <exception>
//#include <armadillo>
#include <scenario/include/object/transformation.h>
//#include <core/include/util.h>

namespace scenario {
namespace object {

void Transformation::add_rotation(const core::util::Vector3 &axis, double angle, bool in_degrees) {
    double angle_rad = in_degrees ? angle * arma::datum::pi / 180 : angle;

    if (axis(0) == 1.0 && axis(1) == 0.0 && axis(2) == 0.0) { // x
        transformations_text_.append("Rx(" + std::to_string(angle_rad) + ")");

        core::util::Matrix4 R;

        R.eye();

        R(1, 1) =  cos(angle_rad);
        R(1, 2) = -sin(angle_rad);
        R(2, 1) =  sin(angle_rad);
        R(2, 2) =  cos(angle_rad);

        matrices_.push_back(R);

    } else if (axis(0) == 0.0 && axis(1) == 1.0 && axis(2) == 0.0) { // y
        transformations_text_.append("Ry(" + std::to_string(angle_rad) + ")");

        core::util::Matrix4 R;

        R.eye();

        R(0, 0) =  cos(angle_rad);
        R(0, 2) =  sin(angle_rad);
        R(2, 0) = -sin(angle_rad);
        R(2, 2) =  cos(angle_rad);

        matrices_.push_back(R);

    } else if (axis(0) == 0.0 && axis(1) == 0.0 && axis(2) == 1.0) { // z
        transformations_text_.append("Rz(" + std::to_string(angle_rad) + ")");

        core::util::Matrix4 R;

        R.eye();

        R(0, 0) =  cos(angle_rad);
        R(0, 1) = -sin(angle_rad);
        R(1, 0) =  sin(angle_rad);
        R(1, 1) =  cos(angle_rad);

        matrices_.push_back(R);

    } else { // quaternion
        transformations_text_.append("Rarb(" + std::to_string(angle_rad) + ")");

        angle_rad /= 2;

        add_translation(-axis);

        core::util::Vector3 u = normalise(axis, 2);
        core::util::Vector4 q, q_;

        q.head(3) = sin(angle_rad) * u;
        q_.head(3) = -q.rows(0, 2);
        q(3) = q_(3) = cos(angle_rad);

        core::util::Matrix4 Lq, Rq_;

        Lq.eye();

        Lq.row(0) = core::util::Vector3 { q(3), -q(2),  q(1),  q(0) };
        Lq.row(1) = core::util::Vector3 { q(2),  q(3), -q(0),  q(1) };
        Lq.row(2) = core::util::Vector3 {-q(1),  q(0),  q(3),  q(2) };
        Lq.row(3) = core::util::Vector3 {-q(0), -q(1), -q(2),  q(3) };

        Rq_.eye();

        Rq_.row(0) = core::util::Vector3 { q_(3),  q_(2), -q_(1),  q_(0) };
        Rq_.row(1) = core::util::Vector3 {-q_(2),  q_(3),  q_(0),  q_(1) };
        Rq_.row(2) = core::util::Vector3 { q_(1), -q_(0),  q_(3),  q_(2) };
        Rq_.row(3) = core::util::Vector3 {-q_(0), -q_(1), -q_(2),  q_(3) };

        matrices_.push_back(Lq * Rq_);

        add_translation(axis);
    }
}

void Transformation::add_scale(const core::util::Vector3 &scale_factors) {
    core::util::Matrix4 S;

    S.eye();

    S(0, 0) = scale_factors(0);
    S(1, 1) = scale_factors(1);
    S(2, 2) = scale_factors(2);

    matrices_.push_back(S);
}

void Transformation::add_translation(const core::util::Vector3 &translate_vector) {
    core::util::Matrix4 T;

    T.eye();

    T.col(3).head(3) = translate_vector;

    matrices_.push_back(T);
}

void Transformation::add_to_apply(std::shared_ptr<Object> obj) {
    objects_to_apply.push_back(obj);
}

void Transformation::make_apply() {
    if (was_applied_)
        throw std::logic_error("Transformation could only be applied once!");

    calculate_final_matrix();

    for (auto obj : objects_to_apply)
        obj->apply_matrix(final_matrix_);

    was_applied_ = true;
    objects_to_apply.clear();
}

void Transformation::calculate_final_matrix() {
    if (matrices_.empty())
        throw std::logic_error("Transformation need to have at least one kind of scale, translation, etc!");

    final_matrix_.eye();

    for (auto matrix : matrices_)
        final_matrix_ *= matrix;

    matrices_.clear();
}

}
}
