#ifndef TILETYPE_H
#define TILETYPE_H

namespace amarlon {

enum class TileType
{
  Null,
  PlainFloor,
  PlainWall,
  Tree,
  Grass,
  Dirt,
  Water,
  END
};

inline TileType operator++(TileType& x) { return x = (TileType)(std::underlying_type<TileType>::type(x) + 1); }
inline TileType operator*(TileType c) {return c;}
inline TileType begin(TileType) {return TileType::Null;}
inline TileType end(TileType)   {return TileType::END;}

}

#endif // TILETYPE_H
