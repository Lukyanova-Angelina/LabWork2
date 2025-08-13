#ifndef RUBY_H
#define RUBY_H

#include "Gold.h"

class Ruby: public Gold {

public:
	Ruby(int pos, int amount);
	DisplayInfo print() const override;
	ObjectType returntype() const override;
};

#endif