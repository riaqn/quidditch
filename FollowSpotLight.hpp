#include "Light.hpp"
#include "Ball.hpp"

class FollowSpotLight : public Light {
  const Ball &ball_;
  const glm::vec4 position_;
  const glm::vec3 intensities_;
  const float attenuation_;
  const float coneAngle_;
public:
  FollowSpotLight(const Ball &ball, const glm::vec3 &position, const glm::vec3 &intensities,
                  const float attenuation, const float coneAngle);
  virtual glm::vec4 getPosition() const ;
  virtual glm::vec3 getIntensities() const ;
  virtual float getAttenuation() const;
  virtual float getAmbientCoefficient() const;
  virtual float getConeAngle() const;
  virtual glm::vec3 getConeDirection() const;
};

