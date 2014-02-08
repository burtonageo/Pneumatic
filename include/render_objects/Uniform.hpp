

#pragma once

#ifndef PNEUMATIC_UNIFORM_HPP
#define PNEUMATIC_UNIFORM_HPP

#include <string>
#include <vector>

namespace Pneumatic {
class Shader;

class Uniform {
public:
  Uniform(std::string const &name, Shader *shader);
  virtual ~Uniform() = 0;

  std::string const& GetName() {return fUniformName;}

protected:
  auto NotifyOwners() -> void;

private:
  std::vector<Shader*> fOwners;
  std::string fUniformName;
};

} // namespace Pneumatic

#endif // PNEUMATIC_UNIFORM_HPP
