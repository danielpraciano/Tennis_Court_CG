#pragma once

#include <armadillo>

namespace core {
namespace util {

using Vector3 = arma::Col<double>::fixed<3ULL>;
using Matrix3 = arma::Mat<double>::fixed<3ULL, 3ULL>;

using Vector4 = arma::Col<double>::fixed<4ULL>;
using Matrix4 = arma::Mat<double>::fixed<4ULL, 4ULL>;

}
}
