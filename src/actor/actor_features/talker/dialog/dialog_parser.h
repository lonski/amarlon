#ifndef DIALOG_SERIALIZER_H
#define DIALOG_SERIALIZER_H

#include <xml/rapidxml.hpp>
#include <dialog.h>

namespace amarlon {

class DialogParser
{
public:
  DialogParser(rapidxml::xml_node<>* xmlNode = nullptr);

  std::vector<Dialog> parse(int id);

private:
  rapidxml::xml_node<>* _xml;
  std::vector<Dialog> parseDialogs();

};

}

#endif // DIALOG_SERIALIZER_H
