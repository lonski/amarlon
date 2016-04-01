#include "dialog_parser.h"
#include <fstream>
#include <xml/rapidxml.hpp>
#include <xml_utils.h>

namespace amarlon {

DialogParser::DialogParser(rapidxml::xml_node<> *xmlNode)
  : _xml(xmlNode)
{
}

std::vector<Dialog> DialogParser::parse(int id)
{
  std::vector<Dialog> dialogs;

  std::string fn = "scripts/talker/" + std::to_string(id) + "/dialogs.xml";
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');

    rapidxml::xml_document<> doc;
    doc.parse<0>(&buf[0]);

    rapidxml::xml_node<>* root = doc.first_node("dialogs");
    if ( root != nullptr )
    {
      _xml = root;
      dialogs = parseDialogs();
    }
  }

  return dialogs;
}

std::vector<Dialog> DialogParser::parseDialogs()
{
  std::vector<Dialog> dialogs;

  if ( _xml != nullptr )
  {
    rapidxml::xml_node<>* dialogNode = _xml->first_node("dialog");
    while ( dialogNode != nullptr )
    {
      Dialog d;
      d.id = getAttribute<int>(dialogNode, "id");
      d.text = getNodeValue<std::string>( dialogNode );
      trim(d.text);

      rapidxml::xml_node<>* choicesNode = dialogNode->first_node("choices");
      if ( choicesNode != nullptr )
      {
        rapidxml::xml_node<>* cNode = choicesNode->first_node("choice");
        while ( cNode != nullptr )
        {
          Choice c;
          c.id = getAttribute<int>(cNode, "id");
          c.jump = getAttribute<int>(cNode, "jump");
          c.text = getNodeValue<std::string>(cNode);

          d.choices.push_back(c);
          cNode = cNode->next_sibling();
        }
      }

      dialogs.push_back( d );
      dialogNode = dialogNode->next_sibling();
    }
  }

  return dialogs;
}

}

