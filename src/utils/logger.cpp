#include "logger.h"

namespace amarlon {

Logger::Logger()
{
}

Logger::~Logger()
{
  closeStream();
}

void Logger::log(LogType type, LogFeature feature, const char *value)
{
  log(type, feature, value, "");
}

bool Logger::openStream()
{
  if ( !_log.is_open() )
    _log.open(Logger::log_fn, std::ios::out | std::ios::app);

  return _log.is_open();
}

bool Logger::closeStream()
{
  if ( _log.is_open() )
    _log.close();

  return !_log.is_open();
}

void Logger::clearFile()
{
  _log.open(Logger::log_fn, std::ios::out | std::ios::trunc);
  closeStream();
}

void Logger::setTypeState(LogType type, bool enabled)
{
  if ( enabled )
    _disabledTypes.erase(type);
  else
    _disabledTypes.insert(type);
}

void Logger::setTypeState(const std::string &type, bool enabled)
{
  for ( auto& kv : LogType2Str )
    if ( kv.second == type )
    {
      setTypeState(kv.first, enabled);
      break;
    }
}

void Logger::setFeatureState(LogFeature feature, bool enabled)
{
  if ( enabled )
    _disabledFeatures.erase(feature);
  else
    _disabledFeatures.insert(feature);
}

void Logger::setFeatureState(const std::string& feature, bool enabled)
{
  for ( auto& kv : LogFeature2Str )
    if ( kv.second == feature )
    {
      setFeatureState(kv.first, enabled);
      break;
    }
}

}
