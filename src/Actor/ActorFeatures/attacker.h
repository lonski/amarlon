#ifndef ATTACKER_H
#define ATTACKER_H

class Actor;

class Attacker
{
public:
  Attacker(float power);
  void setOwner(Actor* owner);

  void attack(Actor* enemy);

private:
  Actor* _owner;
  float _power;

};

#endif // ATTACKER_H
