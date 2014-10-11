#ifndef DESTRUCIBLE_H
#define DESTRUCIBLE_H

class Destrucible
{
public:
  Destrucible(float maxHp);

  bool isAlive() const;

private:
  float _maxHp;
  float _hp;

};

#endif // DESTRUCIBLE_H
