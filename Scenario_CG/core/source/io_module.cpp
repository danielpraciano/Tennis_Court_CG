#include <core/include/io_module.h>

#include <fstream>
#include <vector>

namespace core {
namespace io_module {

std::shared_ptr<scenario::object::Object> ObjReader::read(const std::string &filename,
                                                          const std::shared_ptr<scenario::object::Material>
                                                          &material) {
    std::ifstream in(filename);

    std::shared_ptr<scenario::object::Object> obj { new scenario::object::Object { material } };

    if (!in.is_open()) {
        std::cout << "Failed openning file: " << filename << std::endl;
        return nullptr;
    }

    while (!in.eof()) {
        std::string letter;
        double x, y, z;
        int count = 0;

        in >> letter >> x >> y >> z;

        if (letter.c_str()[0] == 'v') {
            obj->add_vertex(scenario::object::Vertex { x, y, z });
        } else if (letter.c_str()[0] == 'f') {
            obj->add_face(static_cast<int>(x) - 1, static_cast<int>(y) - 1, static_cast<int>(z) - 1);
        } else if (letter.c_str()[0] == 'vn') {
            obj->set_vertice_normal(count, core::util::Vector3 {x, y, z});
            count++;
        }
    }

    in.close();

    return obj;

}

}
}
