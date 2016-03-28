#include "configuration.h"
#include <fstream>
#include <stdexcept>

namespace amarlon {

Configuration::Configuration()
{
}

bool Configuration::load(const std::string &fn)
{
  _config.clear();
  std::ifstream file(fn, std::ios::in);
  if ( file.is_open() )
  {
    std::string line;
    while( std::getline(file, line))
    {
      auto divider = line.find('=');
      if ( divider < line.size() && !line.empty() && line.at(0) != '#')
      {
        _config.insert( std::make_pair( line.substr(0, divider), line.substr(divider+1, line.size()) ) );
      }
    }
    return true;
  }

  return false;
}

bool Configuration::save(const std::string &fn)
{
  std::ofstream file(fn, std::ios::out);
  if ( file.is_open())
  {
    for ( auto vIter = _config.begin(); vIter != _config.end(); ++vIter)
    {
      file << vIter->first << "=" << vIter->second << "\n";
    }
    return true;
  }

  return false;
}

std::string Configuration::get(const std::string &tag)
{
  auto found = _config.find(tag);

  if ( found != _config.end() )
    return found->second;
  else
    throw std::runtime_error("Configuration tag \""+tag+"\" not available!");
}

Configuration& Configuration::set(const std::string &tag, const std::string &value)
{
  _config[tag] = value;

  return *this;
}

const char* Configuration::getFont()
{
  return _config["font"].c_str();
}

}

