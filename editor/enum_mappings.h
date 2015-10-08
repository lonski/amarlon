#ifndef ENUM_MAPPINGS
#define ENUM_MAPPINGS

#include <QStringList>

static QStringList char_classes = {
  "NoClass",
  "Fighter",
  "Cleric",
  "MagicUser",
  "Thief",
  "Monster"
};

static QStringList target_types = {
  "Single neighbour",
  "Single range",
  "Area range",
  "Area neighbour",
  "Self",
  "Single range projectile",
  "Caster area"
};

#endif // ENUM_MAPPINGS

