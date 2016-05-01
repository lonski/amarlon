#ifndef LOGGER_H
#define LOGGER_H

#include <map>
#include <set>
#include <singleton.h>
#include <fstream>

namespace amarlon {

enum class LogFeature {
  General,
  Character,
  AttackAction
};

static std::map<LogFeature, const char*> LogFeature2Str {
  { LogFeature::General,      "General" },
  { LogFeature::Character,    "Character" },
  { LogFeature::AttackAction, "AttackAction" }
};

enum class LogType {
  Info,
  Warning,
  Error,
  Debug
};

static std::map<LogType, const char*> LogType2Str {
  { LogType::Info,    "INF" },
  { LogType::Warning, "WRN" },
  { LogType::Error,   "ERR" },
  { LogType::Debug,   "DBG" }
};

class Logger : public Singleton<Logger>
{
  friend class Singleton;
  Logger();

public:
  constexpr static const char* log_fn = "log.txt";

  ~Logger();

  template<typename T, typename... Targs>
  void log(LogType type, LogFeature feature, const char* format, T value, Targs... Fargs)
  {
    if ( _disabledFeatures.find(feature) != _disabledFeatures.end() )
      return;

    if ( _disabledTypes.find(type) != _disabledTypes.end() )
      return;

    if ( !openStream() )
      return;

    _log << "[" << LogType2Str[type] << "/" << LogFeature2Str[feature] << "] ";

    tprintf(format, value, Fargs...);

    _log << std::endl;

    closeStream();
  }

  void log(LogType type, LogFeature feature, const char* value);

  void clearFile();
  void setTypeState(LogType type, bool enabled);
  void setTypeState(const std::string& type, bool enabled);
  void setFeatureState(LogFeature feature, bool enabled);
  void setFeatureState(const std::string& feature, bool enabled);

private:
  std::set<LogFeature> _disabledFeatures;
  std::set<LogType> _disabledTypes;

  std::ofstream _log;

  bool openStream();
  bool closeStream();

  void tprintf(const char* format);

  template<typename T, typename... Targs>
  void tprintf(const char* format, T value, Targs... Fargs)
  {
      for ( ; *format != '\0'; format++ ) {
          if ( *format == '%' ) {
             _log << value;
             tprintf(format+1, Fargs...);
             return;
          }
          _log << *format;
      }
  }

};

}

#define LOG amarlon::Logger::instance().log

#endif // LOGGER_H
