#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <map>

namespace amarlon {

class Configuration
{
public:
  Configuration();

  bool load(const std::string& fn);
  bool save(const std::string& fn);

  std::string get(const std::string& tag);
  Configuration& set(const std::string& tag, const std::string& value);

  const char *getFont();

private:
  std::map<std::string, std::string> _config;

};

}

#endif // CONFIGURATION_H
