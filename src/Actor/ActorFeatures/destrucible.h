#ifndef DESTRUCIBLE_H
#define DESTRUCIBLE_H

class Actor;

class Destrucible
{
public:
  Destrucible(float maxHp);
  void setOwner(Actor* owner);

  bool isAlive() const;
  float takeDamage(float power);
  void die();

private:
  Actor* _owner;
  float _maxHp;
  float _hp;

};

#endif // DESTRUCIBLE_H
