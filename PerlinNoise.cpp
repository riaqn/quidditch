#include <cmath>
#include <random>
#include <algorithm>
#include <glm/glm.hpp>
#include "PerlinNoise.hpp"
#include "Log.hpp"
#include <stdexcept>

PerlinNoise::PerlinNoise() {
  p = {
    151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
    8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
    35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
    134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
    55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
    18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
    250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
    189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 
    43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
    97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
    107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };
  p.insert(p.end(), p.begin(), p.end());
}

// Generate a new permutation vector based on the value of seed
PerlinNoise::PerlinNoise(unsigned int seed) {
  p.resize(256);

  std::iota(p.begin(), p.end(), 0);

  std::default_random_engine engine(seed);

  std::shuffle(p.begin(), p.end(), engine);

  p.insert(p.end(), p.begin(), p.end());

}

float PerlinNoise::noise(const glm::vec2 &vec) const {
  return noise(glm::vec3(vec.x, vec.y, 0));
}

float PerlinNoise::noise(const glm::vec3 &vec) const {
  glm::vec3 dummy;
  auto vec1 = glm::abs(glm::modf(vec, dummy));
  glm::vec3 vec256 = vec1 * (float)256;
  glm::vec3 vec_f = glm::floor(vec256);
  
  unsigned x = ((unsigned)vec_f.x) & 255,
    y = ((unsigned)vec_f.y)  & 255,
    z = ((unsigned)vec_f.z) & 255;
  
  glm::vec3 fvec = vec256 - vec_f;

  glm::fvec3 f = fade(fvec);

  /*
  debug << "vec = " << vec << '\n';
  debug << "fvec =" << fvec << '\n';
  debug << "f = " << f << '\n';
  */

  float c00 = lerp(f.x, grad(glm::uvec3(x, y, z), vec256), grad(glm::uvec3(x+1, y, z), vec256));
  float c01 = lerp(f.x, grad(glm::uvec3(x, y, z+1), vec256), grad(glm::uvec3(x+1, y, z+1), vec256));
  float c10 = lerp(f.x, grad(glm::uvec3(x, y+1, z), vec256), grad(glm::uvec3(x+1, y+1, z), vec256));
  float c11 = lerp(f.x, grad(glm::uvec3(x, y+1, z+1), vec256), grad(glm::uvec3(x+1, y+1, z+1), vec256));
  
  float c0 = lerp(f.y, c00, c10);
  float c1 = lerp(f.y, c01, c11);

  float c = lerp(f.z, c0, c1);
  //debug << "noise = " << c << '\n';
  return c;
}

glm::vec3 PerlinNoise::fade(const glm::fvec3 &t) {
  return t * t * t * (t * (t * (float)6 - (float)15) + (float)10);
}

float PerlinNoise::lerp(float t, float a, float b) { 
  return a + t * (b - a); 
}

float PerlinNoise::grad(const glm::uvec3 &t, const glm::fvec3 &v) const {
  glm::fvec3 f = v - (glm::fvec3)t;
  unsigned char hash = t.x ^ t.y ^ t.z;
  glm::fvec3 g(p[hash + t.x] - 128,
               p[hash + t.y] - 128,
               p[hash + t.z] - 128);
  return glm::dot(f, glm::normalize(g));
}
