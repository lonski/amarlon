#include "pickable_edit_panel.h"
#include <alabel.h>
#include <alabel_menu_item.h>
#include <atext_edit.h>

namespace amarlon { namespace map_editor {

PickableEditPanel::PickableEditPanel(ActorsDatabase *db)
  : ActorFeatureEditPanel(db)
{
  init();
}

void PickableEditPanel::init()
{
  removeAllWidgets();

  setPosition( 0, 0 );
  setFrame(true);

  int y_pos = 2;
  gui::ALabel* title = new gui::ALabel;
  title->setValue("== Edit pickable ==");
  title->setPosition(2, y_pos++);
  title->setColor(TCODColor::copper);
  addWidget(title);

  if ( getParent() )
  {
    if ( _actor )
    {
      ++y_pos;
      _fAmount.reset(new gui::ATextEdit(2, y_pos++, 25, "Amount"));
      _fAmount->setText( std::to_string(
                           getField<int, PickableDescription>
                           ( &PickableDescription::amount, (int)ActorFeature::PICKABLE ) ) );

      addWidget( _fAmount );

      ++y_pos;
      _fUses.reset(new gui::ATextEdit(2, y_pos++, 25, "Uses"));
      _fUses->setText( std::to_string(
                           getField<int, PickableDescription>
                           ( &PickableDescription::uses, (int)ActorFeature::PICKABLE ) ) );

      addWidget( _fUses );

      ++y_pos;
      _fPrice.reset(new gui::ATextEdit(2, y_pos++, 25, "Price"));
      _fPrice->setText( std::to_string(
                           getField<int, PickableDescription>
                           ( &PickableDescription::price, (int)ActorFeature::PICKABLE ) ) );

      addWidget( _fPrice );

      ++y_pos;
      _fWeight.reset(new gui::ATextEdit(2, y_pos++, 25, "Weight"));
      _fWeight->setText( std::to_string(
                           getField<int, PickableDescription>
                           ( &PickableDescription::weight, (int)ActorFeature::PICKABLE ) ) );

      addWidget( _fWeight );

      ++y_pos;
      _fScript.reset(new gui::ATextEdit(2, y_pos++, 25, "Script ID"));
      _fScript->setText( std::to_string(
                           getField<int, PickableDescription>
                           ( &PickableDescription::scriptId, (int)ActorFeature::PICKABLE ) ) );

      addWidget( _fScript );

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

void PickableEditPanel::saveActor()
{
  saveField<int,PickableDescription>
      ( &PickableDescription::amount, (int)ActorFeature::PICKABLE, _fAmount->getInt());
  saveField<int,PickableDescription>
      ( &PickableDescription::uses, (int)ActorFeature::PICKABLE, _fUses->getInt());
  saveField<int,PickableDescription>
      ( &PickableDescription::price, (int)ActorFeature::PICKABLE, _fPrice->getInt());
  saveField<int,PickableDescription>
      ( &PickableDescription::weight, (int)ActorFeature::PICKABLE, _fWeight->getInt());
  saveField<int,PickableDescription>
      ( &PickableDescription::scriptId, (int)ActorFeature::PICKABLE, _fScript->getInt());
}


}}
