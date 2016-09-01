//
// Created by Justin Turney on 9/1/16.
//

#ifndef PSI4_CORE_PATH_H
#define PSI4_CORE_PATH_H

#include <string>
#include <vector>

namespace psi {
namespace filesystem {

/**
 * \brief Class for manipulating paths.
 *
 */
class path
{
protected:
    std::vector<std::string> path_;
    bool absolute_;

    static std::vector<std::string> tokenize(const std::string &string, const std::string &delim)
    {
        std::string::size_type lastPos = 0, pos = string.find_first_of(delim, lastPos);
        std::vector<std::string> tokens;

        while (lastPos != std::string::npos) {
            if (pos != lastPos)
                tokens.push_back(string.substr(lastPos, pos - lastPos));
            lastPos = pos;
            if (lastPos == std::string::npos || lastPos + 1 == string.length())
                break;
            pos = string.find_first_of(delim, ++lastPos);
        }

        return tokens;
    }

public:

    path() : absolute_(false)
    {}

    path(const path &path) : path_(path.path_), absolute_(path.absolute_)
    {}

    path(path &&path) : path_(std::move(path.path_)), absolute_(path.absolute_)
    {}

    path(const std::string &string)
    { set(string); }

    void set(const std::string &str);

    size_t length() const
    { return path_.size(); }

    bool empty() const
    { return path_.empty(); }

    bool is_absolute() const
    { return absolute_; }

    path make_absolute() const;

    bool exists() const;

    std::string str() const;

    bool is_directory() const;

    bool is_file() const;

    std::string basename() const;

    std::string filename() const;

    std::string extension() const;

    bool remove_file();

    bool resize_file(size_t target_length);

    path parent_path() const;

    path operator/(const path &other) const;

    path &operator=(const path &path);

    path &operator=(path &&path);

    bool operator==(const path &p) const
    { return path_ == p.path_; }

    bool operator!=(const path &p) const
    { return path_ != p.path_; }

    static path getcwd();
};

bool create_directory(const path &p);

} // filesystem
} // psi

#endif //PSI4_CORE_PATH_H
