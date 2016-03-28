#ifndef TALKER_DESCRIPTION_H
#define TALKER_DESCRIPTION_H

#include <description.h>
#include <dialog.h>
#include <experimental/optional>

namespace amarlon
{

struct TalkerDescription : Description
{
  std::experimental::optional<int> id;
  std::vector<Dialog> dialogs;
};

typedef std::shared_ptr<TalkerDescription> TalkerDescriptionPtr;

}

#endif // TALKER_DESCRIPTION_H

