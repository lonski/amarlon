#include "tile_inspect_panel.h"
#include <alabel.h>
#include <alabel_menu_item.h>

namespace amarlon { namespace map_editor {

TileInspectPanel::TileInspectPanel()
  : APanel( 30, 60 )
{

}

void TileInspectPanel::init(int x, int y, const std::vector<ActorDescriptionPtr> &actors,
                            ActorsDatabase *actorDb, gui::APanel *parent)
{
  removeAllWidgets();

  setPosition( 100, 0 );
  setFrame(true);

  int y_pos = 2;
  gui::ALabel* title = new gui::ALabel;
  title->setValue("== Tile inspect: ==");
  title->setPosition(2, y_pos++);
  title->setColor(TCODColor::copper);
  addWidget(title);

  ++y_pos;
  addWidget( new gui::ALabel("X: "+std::to_string(x), 2, y_pos++) );
  addWidget( new gui::ALabel("Y: "+std::to_string(y), 2, y_pos++) );

  ++y_pos;
  gui::ALabel* title2 = new gui::ALabel;
  title2->setValue("== Actors: ==");
  title2->setPosition(2, y_pos++);
  title2->setColor(TCODColor::copper);
  addWidget(title2);

  ++y_pos;
  for ( ActorDescriptionPtr a : actors )
  {
    ActorDescriptionPtr def = actorDb->fetch(*a->id);
    addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                       *def->name + "["+std::to_string(*a->id)+"]", [](){
      //TODO something
    } ));
  }

  ++y_pos;
  gui::ALabel* title3 = new gui::ALabel;
  title3->setValue("== Operations: ==");
  title3->setPosition(2, y_pos++);
  title3->setColor(TCODColor::copper);
  addWidget(title3);

  y_pos+=2;
  addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                     "Add actor", [](){
    //TODO
  } ));

  y_pos += 2;
  addWidget( new gui::ALabelMenuItem(2, y_pos++,
                                     "[CLOSE]", [=](){
    parent->removeWidget(this);
  } ));
}

}}
