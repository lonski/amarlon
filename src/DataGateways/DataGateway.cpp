#include "DataGateway.h"
#include <iostream>
#include <iterator>
#include <fstream>
#include <iterator>

using namespace std;

vector<string> explode(string str, char ch)
{
  vector<string> result;
  string line;

  for (auto s = str.begin(); s != str.end(); ++s)
  {
    if (*s == ch)
    {
      if (!line.empty())
      {
        result.push_back(line);
        line.clear();
      }
    }
    else
    {
      line += *s;
    }
  }

  if (!line.empty())
  {
    result.push_back(line);
    line.clear();
  }

  return result;
}

void DataGateway::retriveDataStr(std::string section, std::string tag, std::vector<std::string> &data)
{
  std::string value = retriveDataStr(section, tag);
  std::vector<std::string> dataStr = explode(value, vectorSeparator);

  data.clear();
  for (auto dIter = dataStr.begin(); dIter != dataStr.end(); ++dIter)
  {
    data.push_back(*dIter);
  }
}

std::string DataGateway::retriveDataStr(std::string section, std::string tag)
{
  std::string t;

  if (m_sections.count(section))
  {
    TagMap& tags = m_sections.at(section);
    if (tags.count(tag))
    {
      t = tags.at(tag);
    }
  }

  return t;
}

DataGateway::DataGateway()
  : newSectionMark('|')
  , newTagMark(';')
  , valueMark('=')
  , vectorSeparator('^')
{
}

void DataGateway::loadContent(string filename)
{
  ifstream file(filename, ios::binary);
  string data((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());

  vector<string> sections = explode(data,newSectionMark);

  for (auto sIter = sections.begin(); sIter != sections.end(); ++sIter)
  {
    TagMap tagMap;
    string section;
    vector<string> tags = explode(*sIter, newTagMark);
    if (!tags.empty())
    {
      tagMap.clear();
      section = tags[0];
      for (auto tIter = tags.begin()+1; tIter != tags.end(); ++tIter)
      {
        vector<string> tVal = explode(*tIter, valueMark);
        if (tVal.size() == 2)
        {
          tagMap[tVal[0]] = tVal[1];
        }
      }
    }

    if (!tagMap.empty())
    {
      m_sections[section] = tagMap;
    }
  }

}

void DataGateway::saveContent(string filename)
{
  vector<char> data;

  for (SectionMap::iterator sectionIter = m_sections.begin(); sectionIter != m_sections.end(); ++sectionIter)
  {
    string section = sectionIter->first;
    TagMap& tags = sectionIter->second;

    data.push_back(newSectionMark);
    data.insert(data.end(), section.begin(), section.end());

    for (TagMap::iterator tagIter = tags.begin(); tagIter != tags.end(); ++tagIter)
    {
      data.push_back(newTagMark);
        data.insert(data.end(), tagIter->first.begin(), tagIter->first.end());

      data.push_back(valueMark);
        data.insert(data.end(), tagIter->second.begin(), tagIter->second.end());
    }
  }

  ofstream ofs(filename, ios::binary);
  ofs.write(&data[0], data.size());
  ofs.close();
}

std::vector<string> DataGateway::getSections()
{
  std::vector<string> s;
  for (SectionMap::iterator sectionIter = m_sections.begin(); sectionIter != m_sections.end(); ++sectionIter)
  {
    s.push_back(sectionIter->first);
  }
  return s;
}

bool DataGateway::sectionExists(string section) const
{
  return m_sections.count(section);
}

bool DataGateway::tagExists(string section, string tag) const
{    
  return m_sections.count(section) && m_sections.at(section).count(tag);
}

size_t DataGateway::getSectionCount() const
{
  return m_sections.size();
}
