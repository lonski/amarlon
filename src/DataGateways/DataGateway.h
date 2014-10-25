#ifndef DATAGATEWAY_H
#define DATAGATEWAY_H

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstring>

class DataGateway
{
  typedef std::map<std::string, std::string> TagMap;
  typedef std::map<std::string, TagMap> SectionMap;

  SectionMap m_sections;

  const char newSectionMark;
  const char newTagMark;
  const char valueMark;
  const char vectorSeparator;

public:
  template<typename T>
  void addData(std::string section, std::string tag, T data);
  template<typename T>
  void addData(int section, std::string tag, T data);

  template<typename T>
  T retriveData(std::string section, std::string tag);
  template<typename T>
  T retriveData(int section, std::string tag);

  template<typename T>
  void addData(std::string section, std::string tag, std::vector<T>& data);
  template<typename T>
  void retriveData(std::string section, std::string tag, std::vector<T>& data);
  template<typename T>
  void addData(int section, std::string tag, std::vector<T>& data);
  template<typename T>
  void retriveData(int section, std::string tag, std::vector<T>& data);
  std::string retriveDataStr(std::string section, std::string tag);
  void retriveDataStr(std::string section, std::string tag, std::vector<std::string> &data);

  bool sectionExists(std::string section) const;
  bool tagExists(std::string section, std::string tag) const;

  size_t getSectionCount() const;

  void loadContent(std::string filename);
  void saveContent(std::string filename);

  std::vector<std::string> getSections();

  DataGateway();
};

std::vector<std::string> explode(std::string str, char ch);

template<typename T>
std::string toString(T& t, size_t prec = 2)
{
  std::stringstream ss;
  ss << std::setprecision(prec+1) << t;
  return ss.str();
}

template<typename T>
T fromString(std::string& str, size_t prec = 2)
{
  std::stringstream ss;
  ss << str;
  T t;
  ss >> std::setprecision(prec+1) >> t;

  return t;
}

template<typename T>
void DataGateway::addData(std::string section, std::string tag, T data)
{
  TagMap& tags = m_sections[section];

  if (std::is_pod<T>::value)
  {
    tags[tag] = toString(data);
  }
  else
  {
    tags[tag] = data;
  }
}

template<typename T>
void DataGateway::addData(int section, std::string tag, T data)
{
  addData<T>(toString(section), tag, data);
}


template<typename T>
T DataGateway::retriveData(std::string section, std::string tag)
{
  T t;
  if (std::is_pod<T>::value)
  {
    t = static_cast<T>(0);
  }

  if (m_sections.count(section))
  {
    TagMap& tags = m_sections.at(section);
    if (tags.count(tag))
    {
      t = fromString<T>(tags.at(tag));
    }
  }

  return t;
}

template<typename T>
T DataGateway::retriveData(int section, std::string tag)
{
  return retriveData<T>(toString(section), tag);
}

template<typename T>
void DataGateway::addData(std::string section, std::string tag, std::vector<T> &data)
{
  std::string vectoredTag;
  for (typename std::vector<T>::iterator dIter = data.begin(); dIter != data.end(); ++dIter)
  {
    vectoredTag += vectorSeparator;
    vectoredTag += toString(*dIter);
  }

  addData<std::string>(section, tag, vectoredTag);
}

template<typename T>
void DataGateway::addData(int section, std::string tag, std::vector<T> &data)
{
  addData(toString(section), tag, data);
}

template<typename T>
void DataGateway::retriveData(std::string section, std::string tag, std::vector<T> &data)
{
  std::string value = retriveData<std::string>(section, tag);
  std::vector<std::string> dataStr = explode(value, vectorSeparator);

  data.clear();
  for (auto dIter = dataStr.begin(); dIter != dataStr.end(); ++dIter)
  {
    data.push_back(fromString<T>(*dIter));
  }
}

template<typename T>
void DataGateway::retriveData(int section, std::string tag, std::vector<T> &data)
{
  retriveData(toString(section), tag, data);
}

#endif // DATAGATEWAY_H
