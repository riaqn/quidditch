#pragma  once
template<typename T, typename U>
class Noise {
public:
  virtual T noise(const U &u) const = 0;
};
