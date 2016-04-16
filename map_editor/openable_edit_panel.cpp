#include "openable_edit_panel.h"
#include <alabel.h>
#include <alabel_menu_item.h>
#include <atext_edit.h>

namespace amarlon { namespace map_editor {

OpenableEditPanel::OpenableEditPanel(ActorsDatabase *db)
  : ActorFeatureEditPanel(db)
{
  init();
}

void OpenableEditPanel::init()
{
  removeAllWidgets();

  setPosition( 0, 0 );
  setFrame(true);

  int y_pos = 2;
  gui::ALabel* title = new gui::ALabel;
  title->setValue("== Edit openable ==");
  title->setPosition(2, y_pos++);
  title->setColor(TCODColor::copper);
  addWidget(title);

  if ( getParent() )
  {
    if ( _actor )
    {
      ++y_pos;
      _fClosed.reset(new gui::ATextEdit(2, y_pos++, 25, "Closed"));
      _fClosed->setText( std::to_string( getField<bool>( &OpenableDescription::closed ) ) );
      addWidget( _fClosed );

      ++y_pos;
      _fLocked.reset(new gui::ATextEdit(2, y_pos++, 25, "Locked"));
      _fLocked->setText( std::to_string( getField<bool>( &OpenableDescription::locked ) ) );
      addWidget( _fLocked );

      ++y_pos;
      _fLockId.reset(new gui::ATextEdit(2, y_pos++, 25, "Lock ID"));
      _fLockId->setText( std::to_string( getField<int>( &OpenableDescription::lockId ) ) );
      addWidget( _fLockId );

      ++y_pos;
      _fLockLevel.reset(new gui::ATextEdit(2, y_pos++, 25, "Lock level"));
      _fLockLevel->setText( std::to_string( getField<int>( &OpenableDescription::lockLevel ) ) );
      addWidget( _fLockLevel );

      ++y_pos;
      _fScriptId.reset(new gui::ATextEdit(2, y_pos++, 25, "Script ID"));
      _fScriptId->setText( std::to_string( getField<int>( &OpenableDescription::scriptId ) ) );
      addWidget( _fScriptId );
    }

    y_pos += 2;
    addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                       "[SAVE]", [=](){
      saveActor();
    } ));
    ++y_pos;
    addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                       "[CLOSE]", [=](){
      setActive(false);
      static_cast<gui::APanel*>(getParent())->removeWidget(this);
    } ));
  }
}

void OpenableEditPanel::saveActor()
{
  saveField<bool>( &OpenableDescription::closed, _fClosed->getText() == "1");
  saveField<bool>( &OpenableDescription::locked, _fLocked->getText() == "1");
  saveField<int>( &OpenableDescription::lockId, _fLockId->getInt());
  saveField<int>( &OpenableDescription::lockLevel, _fLockLevel->getInt());
  saveField<int>( &OpenableDescription::scriptId, _fScriptId->getInt());
}

OpenableDescriptionPtr OpenableEditPanel::getOpenable() const
{
  return std::dynamic_pointer_cast<OpenableDescription>(
        _actor->features[ (int)ActorFeature::OPENABLE ] );
}

OpenableDescriptionPtr OpenableEditPanel::getOpenablePrototype() const
{
  ActorDescriptionPtr prototype = _db->fetch( *_actor->id );
  return std::dynamic_pointer_cast<OpenableDescription>(
        prototype->features[ (int)ActorFeature::OPENABLE ] );
}

}}
