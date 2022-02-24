#pragma once

#include "Item.h"


class Weapon : Item
{
public:
	Weapon();
	virtual ~Weapon();

private:


	struct MinMax
	{
		int min;
		int max;
	} dmg;

	/*
	1: shield
	2: mele
	3: 50/50
	4: range
	*/
	int range;

	/*
	0: true dmg
	1: Psychic
	2: Magick
	*/
	int typeDmg;

};

