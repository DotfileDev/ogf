#pragma once

#include <string>

namespace ogf {

    std::stringstream get_file_content_as_sstream(const std::string_view filename);
    std::string get_file_extension(const std::string_view filename);

}
