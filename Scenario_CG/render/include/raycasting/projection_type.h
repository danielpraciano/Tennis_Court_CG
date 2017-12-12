#pragma once

#include <cstdint>

namespace render {
namespace raycasting {

enum class ProjectionType : int8_t {
    PERSPECTIVE,
    ORTHOGRAPHIC,
    OBLIQUE,
    CAVALIER,
    CABINET
};

}
}
