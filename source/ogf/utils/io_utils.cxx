#include <ogf/utils/io_utils.hxx>

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ogf {

    std::stringstream get_file_content(const std::string_view filename) {
        std::fstream file{filename.data()};
        if(!file.good()) {
            throw std::runtime_error{""};
        }
        std::stringstream file_stream{};
        while(!file.eof()) {
            std::string line{};
            std::getline(file, line);
            file_stream << line << '\n';
        }
        return file_stream;
    }

    std::string get_file_extension(const std::string_view filename) {
        return std::string{filename.substr(filename.find_last_of('.') + 1)};
    }

}
