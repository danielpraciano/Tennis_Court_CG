//#pragma once

//#include <string>
//#include <utility>
//#include <cstdint>

//#include <boost/gil/gil_all.hpp>
//#include <boost/gil/extension/io/jpeg_io.hpp>

//#include <render/include/raycasting/color.h>

//namespace scenario {
//namespace object {

//class Texture {

//public:
//    Texture(const std::string &filename) { img_ = new boost::gil::rgb8_image_t {};
//        boost::gil::jpeg_read_image(filename, *img_); }
//    ~Texture() { delete img_; }

//    inline render::raycasting::Color get_rgb_tex(uint64_t u, uint64_t v) const {
//        auto texel = boost::gil::view(*img_)(u, v);

//        return render::raycasting::Color { static_cast<int>(texel[0]) / 255.0, static_cast<int>(texel[1]) / 255.0, static_cast<int>(texel[2]) / 255.0 };
//    }

//    inline std::pair<uint64_t, uint64_t> get_dimensions() const { return std::make_pair(boost::gil::view(*img_).dimensions()[0], boost::gil::view(*img_).dimensions()[1]); }

//private:
//    boost::gil::rgb8_image_t *img_;

//};

//}
//}
