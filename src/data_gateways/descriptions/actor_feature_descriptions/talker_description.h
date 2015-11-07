#ifndef TALKER_DESCRIPTION_H
#define TALKER_DESCRIPTION_H

#include <description.h>
#include <dialog.h>

namespace amarlon
{

struct TalkerDescription : Description
{
  TalkerDescription()
    : id(0)
  {}

  int id;
  std::vector<Dialog> dialogs;
};

typedef std::shared_ptr<TalkerDescription> TalkerDescriptionPtr;

}

#endif // TALKER_DESCRIPTION_H

