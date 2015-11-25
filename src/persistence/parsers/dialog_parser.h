#ifndef DIALOG_SERIALIZER_H
#define DIALOG_SERIALIZER_H

#include <persistence/parsers/parser.h>
#include <dialog.h>

namespace amarlon {

class DialogParser : public Parser
{
public:
  DialogParser() {}
  DialogParser(rapidxml::xml_node<>* xmlNode);

  std::vector<Dialog> parse(int id);

private:
  std::vector<Dialog> parseDialogs();

};

}

#endif // DIALOG_SERIALIZER_H
