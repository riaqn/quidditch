#include "SimpleMesh.hpp"
#include <istream>

class FileMesh : public SimpleMesh {
public:
  FileMesh(std::istream &is);
};
