#ifndef ACTORDB_H
#define ACTORDB_H

#include <string>
#include <vector>
#include <memory>

namespace amarlon {

class Actor;
struct ActorDescription;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;

class ActorDB
{
public:
  ActorDB();

  ActorPtr fetch(int type);
  ActorDescriptionPtr fetchDescription(int type);

  /**
   * @brief loads given file, parses xml and creates actor descriptions
   * @param path to file to be loaded
   */
  void load(const std::string& fn);

  /**
   * @brief Loads file which contains additional actor definitions
   *        or overrides base actors.
   */
  void loadPlugin(const std::string& fn);

private:
  std::vector<ActorDescriptionPtr> _descriptions;
  std::vector<ActorDescriptionPtr> _pluginDescriptions;

  void parseActors(std::vector<char>& dataToParse, std::vector<ActorDescriptionPtr>& dst);
  ActorPtr fetch(int type, std::vector<ActorDescriptionPtr>& src);
  ActorDescriptionPtr fetchDescription(int type, std::vector<ActorDescriptionPtr>& src);

};

}
#endif // ACTORDB_H
