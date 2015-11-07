#ifndef TALKER_H
#define TALKER_H

#include <actor_feature.h>
#include <dialog.h>

namespace amarlon
{

class Talker;
typedef std::shared_ptr<Talker> TalkerPtr;

class Talker : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Talker();
  virtual ~Talker();

  static TalkerPtr create(DescriptionPtr dsc);
  virtual ActorFeature::Type getType();

  /**
   * @brief Proceeds a talk between actors.
   * @param talker - an actors who start talk (player)
   * @param dialog - last processed (displayed) dialog. If none,
   *                 then it means a new talk.
   * @param choice - choice from last procesed dialog
   */
  virtual Dialog talk(ActorPtr talker,
                      const Dialog& dialog = Dialog(),
                      const Choice& choice = Choice());

  /**
   * @brief Finds dialog with given id. If not found then
   *        returns a dialog with id = -1,
   *        which means "talk quit dialog".
   */
  virtual Dialog getDialog(int id) const;

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  virtual std::string getScript() const;

private:
  int _id;
  std::vector<Dialog> _dialogs;

};

}

#endif // TALKER_H
