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

  int getStartMap() const;
  int getStartX() const;
  int getStartY() const;

private:
  std::string _name;
  std::string _prettyName;
  int _startMap;
  int _startX;
  int _startY;

};

}

#endif // MODULE_H
