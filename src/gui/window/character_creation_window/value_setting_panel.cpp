#include "value_setting_panel.h"

namespace amarlon { namespace gui {

ValueSettingPanel::ValueSettingPanel(const std::string& name, int value, MinMax constrains, int& pointsPool)
  : ASubPanel(20,5)
  , _menu( new AHorizontalMenu )
  , _plus( new ALabelMenuItem("+") )
  , _minus( new ALabelMenuItem("-") )
  , _nameLabel( new ALabel )
  , _valueLabel( new ALabel )
  , _constrains(constrains)
  , _currentValue(value)
  , _name(name)
  , _pool(pointsPool)
{
  setFrame(true);
  deactivate();
}

void ValueSettingPanel::activate()
{
  ASubPanel::activate();
  _menu->select( _plus );
  setFrameColor(TCODColor::orange);
}

void ValueSettingPanel::deactivate()
{
  ASubPanel::deactivate();
  _menu->deselect();
  setFrameColor(TCODColor::desaturatedOrange);
}

void ValueSettingPanel::selectNext()
{
  _menu->selectNext();
}

void ValueSettingPanel::selectPrevious()
{
  _menu->selectPrevious();
}

void ValueSettingPanel::update()
{
  _menu->addItem( _plus );
  _menu->addItem( _minus );

  _menu->setPosition( getWidth() - (_menu->getWidth() + 2),2);
  addWidget( _menu );

  _nameLabel->setValue(_name + ":");
  _nameLabel->setPosition(2,2);
  addWidget( _nameLabel );

  _valueLabel->setValue(toStr(_currentValue));
  _valueLabel->setPosition( _menu->getX() - 3, 2);
  addWidget( _valueLabel );

  setValue(_currentValue);
}

void ValueSettingPanel::manage()
{
  if ( _plus->isSelected() )
  {
    setValue( _currentValue + 1 );
  }
  else if ( _minus->isSelected() )
  {
    setValue( _currentValue - 1 );
  }
}

int ValueSettingPanel::getValue() const
{
  return _currentValue;
}

void ValueSettingPanel::setValue(int val)
{
  if ( val >= _constrains.min && val <= _constrains.max )
  {
    int diff = val - _currentValue;
    if ( diff <= _pool )
    {
      _currentValue = val;
      _valueLabel->setValue( toStr(_currentValue) );
      _pool -= diff;
    }
  }
}

}}
