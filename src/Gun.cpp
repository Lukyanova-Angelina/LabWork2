#include "Gun.h"
Gun::Gun(int pos, int amount, const std::array<bool, 4>& dirs):Thorn(pos, amount, dirs){}

DisplayInfo Gun::print()const{ //←, →, ↑, ↓.
	auto dir = getDirections();
	return {
		(dir[0] ? "▲": ""),
		(dir[3] ? "◀   ": "  ") + std::to_string(getAmount()) + (dir[1] ? "   ▶": "  "),
		(dir[2] ? "▼": " "),
		Color::RED
	};
}
ObjectType Gun::returntype() const {
	return ObjectType::GUN;
}
