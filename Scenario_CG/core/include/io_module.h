#pragma once

#include <string>

#include <scenario/include/object/object.h>
#include <scenario/include/object/material.h>

namespace core {
namespace io_module {

class ObjReader {

public:
    ObjReader() {}

    std::shared_ptr<scenario::object::Object> read(const std::string &filename,
                                                   const std::shared_ptr<scenario::object::Material>
                                                    &material);
};

}
}
