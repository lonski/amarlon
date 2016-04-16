#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <memory>

namespace amarlon {

class Module
{
public:
  Module(const std::string& name = "");

  std::string getName() const;
  std::string getPath() const;

private:
  std::string _name;

};

}

#endif // MODULE_H
