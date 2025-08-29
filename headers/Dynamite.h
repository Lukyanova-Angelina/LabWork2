#ifndef DYNAMITE_H
#define DYNAMITE_H

#include "Bomb.h"

class Dynamite: public Bomb {
public:
	Dynamite(int pos, int amount);
	DisplayInfo print() const override;
	ObjectType returntype() const override;
};

#endif