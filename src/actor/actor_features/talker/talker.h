#ifndef TALKER_H
#define TALKER_H

#include <actor_feature.h>
#include <dialog.h>
#include <actor.pb.h>

namespace amarlon
{

class Talker;
typedef std::shared_ptr<Talker> TalkerPtr;

class Talker : public ActorFeature
{
public:
  const static ActorFeature::Type FeatureType;

  static TalkerPtr create(const TalkerData& data);

  Talker();
  Talker(const Talker& rhs);
  virtual ~Talker();

  bool operator==(const Talker& rhs) const;
  Talker& operator=(const Talker& rhs);
  virtual const TalkerData& getData() const;
  virtual const ::google::protobuf::Message& getDataPolymorphic() const;

  virtual ActorFeature::Type getFeatureType();
  virtual int getId() const;

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

  virtual std::string getScript() const;
  static std::string getScript(int id);

private:
  TalkerData _data;
  std::vector<Dialog> _dialogs;

  Talker(const TalkerData& data);
  void initialize();

};

}

#endif // TALKER_H
