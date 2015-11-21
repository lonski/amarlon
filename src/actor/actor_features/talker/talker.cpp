#include "talker.h"
#include <talker_description.h>
#include <lua_state.h>
#include <engine.h>


namespace amarlon {

const ActorFeature::Type Talker::featureType = ActorFeature::TALKER;

Talker::Talker(DescriptionPtr dsc)
  : _id(0)
{
  upgrade(dsc);
}

Talker::~Talker()
{
}

TalkerPtr Talker::create(DescriptionPtr dsc)
{
  return TalkerPtr(new Talker(dsc));
}

void Talker::upgrade(DescriptionPtr dsc)
{
  TalkerDescriptionPtr tDsc = std::dynamic_pointer_cast<TalkerDescription>(dsc);
  if ( tDsc )
  {
    if ( tDsc->id ) _id = *tDsc->id;
    _dialogs.insert( _dialogs.begin(), tDsc->dialogs.begin(), tDsc->dialogs.end());
  }
}

ActorFeature::Type Talker::getType()
{
  return Talker::featureType;
}

int Talker::getId() const
{
  return _id;
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

ActorFeaturePtr Talker::clone()
{
  return TalkerPtr(new Talker(*this));
}

bool Talker::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  TalkerPtr tRhs = std::dynamic_pointer_cast<Talker>(rhs);
  if ( tRhs )
  {
    equal =  tRhs->_id == _id
          && _dialogs.size() == tRhs->_dialogs.size()
          && std::equal(_dialogs.begin(), _dialogs.end(), tRhs->_dialogs.begin());
  }

  return equal;
}

std::string Talker::getScript() const
{
  return Talker::getScript(_id);
}

std::string Talker::getScript(int id)
{
  return "scripts/talker/" + std::to_string(id) + "/script.lua";
}

}
