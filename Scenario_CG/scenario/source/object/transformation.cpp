#include <exception>
//#include <armadillo>
#include <scenario/include/object/transformation.h>
//#include <core/include/util.h>

namespace scenario {
namespace object {

void Transformation::add_rotation(const core::util::Vector3 axis, const double angle, const bool inDegrees) {
    double angle_rad = inDegrees ? angle * arma::datum::pi / 180 : angle;

    if (axis(0) == 1.0 && axis(1) == 0.0 && axis(2) == 0.0) { // x
        _transformations_text.append("Rx(" + std::to_string(angle_rad) + ")");

        core::util::Matrix4 R;

        R.eye();

        R(1, 1) =  cos(angle_rad);
        R(1, 2) = -sin(angle_rad);
        R(2, 1) =  sin(angle_rad);
        R(2, 2) =  cos(angle_rad);

        _matrices.push_back(R);

    } else if (axis(0) == 0.0 && axis(1) == 1.0 && axis(2) == 0.0) { // y
        _transformations_text.append("Ry(" + std::to_string(angle_rad) + ")");

        core::util::Matrix4 R;

        R.eye();

        R(0, 0) =  cos(angle_rad);
        R(0, 2) =  sin(angle_rad);
        R(2, 0) = -sin(angle_rad);
        R(2, 2) =  cos(angle_rad);

        _matrices.push_back(R);

    } else if (axis(0) == 0.0 && axis(1) == 0.0 && axis(2) == 1.0) { // z
        _transformations_text.append("Rz(" + std::to_string(angle_rad) + ")");

        core::util::Matrix4 R;

        R.eye();

        R(0, 0) =  cos(angle_rad);
        R(0, 1) = -sin(angle_rad);
        R(1, 0) =  sin(angle_rad);
        R(1, 1) =  cos(angle_rad);

        _matrices.push_back(R);

    } else { // quaternion
        _transformations_text.append("Rarb(" + std::to_string(angle_rad) + ")");

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

        _matrices.push_back(Lq * Rq_);

        add_translation(axis);
    }
}

void Transformation::add_scale(const core::util::Vector3 scale_factors) {
    core::util::Matrix4 S;

    S.eye();

    S(0, 0) = scale_factors(0);
    S(1, 1) = scale_factors(1);
    S(2, 2) = scale_factors(2);

    _matrices.push_back(S);
}

void Transformation::add_translation(const core::util::Vector3 translate_vector) {
    core::util::Matrix4 T;

    T.eye();

    T.col(3).head(3) = translate_vector;

    _matrices.push_back(T);
}

void Transformation::add_to_apply(std::shared_ptr<Object> obj) {
    _objects_to_apply.push_back(obj);
}

void Transformation::make_apply() {
    if (_was_applied)
        throw std::logic_error("Transformation could only be applied once!");

    calculate_final_matrix();

    for (auto obj : _objects_to_apply)
        obj->apply_matrix(_final_matrix);

    _was_applied = true;
    _objects_to_apply.clear();
}

void Transformation::calculate_final_matrix() {
    if (_matrices.empty())
        throw std::logic_error("Transformation need to have at least one kind of scale, translation, etc!");

    _final_matrix.eye();

    for (auto matrix : _matrices)
        _final_matrix *= matrix;

    _matrices.clear();
}

}
}
