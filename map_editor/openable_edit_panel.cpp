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
      _fClosed->setText( std::to_string(
                           getField<bool, OpenableDescription>
                           ( &OpenableDescription::closed, (int)ActorFeature::OPENABLE ) ) );

      addWidget( _fClosed );

      ++y_pos;
      _fLocked.reset(new gui::ATextEdit(2, y_pos++, 25, "Locked"));
      _fLocked->setText( std::to_string(
                           getField<bool, OpenableDescription>
                           ( &OpenableDescription::locked, (int)ActorFeature::OPENABLE ) ) );
      addWidget( _fLocked );

      ++y_pos;
      _fLockId.reset(new gui::ATextEdit(2, y_pos++, 25, "Lock ID"));
      _fLockId->setText( std::to_string(
                           getField<int, OpenableDescription>
                           ( &OpenableDescription::lockId, (int)ActorFeature::OPENABLE ) ) );
      addWidget( _fLockId );

      ++y_pos;
      _fLockLevel.reset(new gui::ATextEdit(2, y_pos++, 25, "Lock level"));
      _fLockLevel->setText( std::to_string(
                              getField<int, OpenableDescription>
                              ( &OpenableDescription::lockLevel, (int)ActorFeature::OPENABLE ) ) );
      addWidget( _fLockLevel );

      ++y_pos;
      _fScriptId.reset(new gui::ATextEdit(2, y_pos++, 25, "Script ID"));
      _fScriptId->setText( std::to_string(
                             getField<int, OpenableDescription>
                             ( &OpenableDescription::scriptId, (int)ActorFeature::OPENABLE ) ) );
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
  saveField<bool,OpenableDescription>
      ( &OpenableDescription::closed, (int)ActorFeature::OPENABLE, _fClosed->getText() == "1");
  saveField<bool,OpenableDescription>
      ( &OpenableDescription::locked, (int)ActorFeature::OPENABLE, _fLocked->getText() == "1");
  saveField<int,OpenableDescription>
      ( &OpenableDescription::lockId, (int)ActorFeature::OPENABLE, _fLockId->getInt());
  saveField<int,OpenableDescription>
      ( &OpenableDescription::lockLevel, (int)ActorFeature::OPENABLE, _fLockLevel->getInt());
  saveField<int,OpenableDescription>
      ( &OpenableDescription::scriptId, (int)ActorFeature::OPENABLE, _fScriptId->getInt());
}


}}
