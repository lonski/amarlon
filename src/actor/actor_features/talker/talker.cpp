#include "talker.h"
#include <talker_description.h>
#include <lua_state.h>
#include <engine.h>

#include <dialog_parser.h>

namespace amarlon {

const ActorFeature::Type Talker::FeatureType = ActorFeature::TALKER;

TalkerPtr Talker::create(const TalkerData &data)
{
  return TalkerPtr( new Talker(data) );
}

Talker::Talker()
{
}

Talker::Talker(const Talker &rhs)
{
  *this = rhs;
}

Talker::~Talker()
{
}

bool Talker::operator==(const Talker &rhs) const
{
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Talker &Talker::operator=(const Talker &rhs)
{
  if ( this != &rhs )
  {
    _data.CopyFrom(rhs._data);
    initialize();
  }
  return *this;
}

const TalkerData &Talker::getData() const
{
  return _data;
}

const google::protobuf::Message& Talker::getDataPolymorphic() const
{
  return getData();
}

ActorFeature::Type Talker::getFeatureType()
{
  return Talker::FeatureType;
}

int Talker::getId() const
{
  return _data.id();
}

Dialog Talker::talk(ActorPtr talker, const Dialog &dialog, const Choice &choice)
{
  int dialogId = -1;

  lua_api::LuaState& lua = Engine::instance().getLuaState();
  if ( lua.execute( getScript() ) )
  {
    try
    {
      dialogId = luabind::call_function<int>(
                      lua()
                    , "onTalk"
                    , talker
                    , getOwner().lock()
                    , &dialog
                    , &choice
                  );
    }
    catch(luabind::error& e)
    {
      lua.logError(e);
    }
    catch(std::exception& e)
    {
      lua.logError(e);
    }
  }
  else
  {
    if ( choice.jump != 0 ) dialogId = choice.jump;
  }

  return getDialog( dialogId );
}

Dialog Talker::getDialog(int id) const
{
  auto it = std::find_if(_dialogs.begin(), _dialogs.end(),
                         [&](const Dialog& d){ return d.id == id;});

  return it == _dialogs.end() ? Dialog(-1) : *it;
}

std::string Talker::getScript() const
{
  return Talker::getScript( getId() );
}

std::string Talker::getScript(int id)
{
  return "scripts/talker/" + std::to_string(id) + "/script.lua";
}

Talker::Talker(const TalkerData &data)
{
  _data.CopyFrom(data);
  initialize();
}

void Talker::initialize()
{
  _dialogs = DialogParser().parse( getId() );
}

}
