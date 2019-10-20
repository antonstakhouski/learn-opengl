#include <glm/glm.hpp>

namespace Material {

struct Material {
    Material(const glm::vec3& ambient_, const glm::vec3& diffuse_,
             const glm::vec3& specular_, float shineness_)
        : ambient(ambient_),
          diffuse(diffuse_),
          specular(specular_),
          shineness(shineness_ * 128.0f)
    {
    }

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shineness;
};

const Material Ruby = {
    glm::vec3(0.1745f, 0.01175f, 0.01175f),
    glm::vec3(0.61424f, 0.04136f, 0.04136f),
    glm::vec3(0.727811f, 0.626959f, 0.626959f),
    0.6f
};

const Material Chrome = {
    glm::vec3(0.25f),
    glm::vec3(0.4f),
    glm::vec3(0.774597f),
    0.6f
};

}  // namespace Material
