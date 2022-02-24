#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <map>
#include <random>

#include "pugixml.hpp"

class Item
{
public:
	Item();
	virtual ~Item();

	void initVarible();

	//TODO? make f() to render?

	// type item
	// id item
	void GetDataEq(int id);

	int getType();
	int getId();

	std::string getName();

	//return eq value
	int getBaseArmor();
	int getHp();
	int getMana();
	int getBlock();
	bool getIsWeapon();
	bool getIsTwoHand();

	//return basic value
	int getStatStrength();
	int getStatDexterity();
	int getStatIntelligence();
	int getLuck();
	int getCrit();

	//return state of item
	int getUpgrade();
	unsigned short getQuality();
	unsigned short getBroken();

	//return require value
	int getRequireStrength();
	int getRequireDexterity();
	int getRequireIntelligence();
	int getRequireLvl();           

	//return texture value
	int getTextureRectLeft();
	int getTextureRectTop();
	int getTextureRectWidth();
	int getTextureRectHeight();

	//return weapon value
	short getTypeDMG();
	short getRange();
	int getMinDMG();
	int getMaxDMG();

private:

	struct TextureRect
	{
		int left;
		int top;
		int width;
		int height;

	} textureRect;

	//core data
	int type;
	int id;
	bool isWeapon;
	bool twoHand;

	
	int idSlot;

	//core info
	std::string name;

	int statStrength;
	int statDexterity;
	int statIntelligence;
	int luck;
	int crit;
	int block;

	int upgrade;
	unsigned short quality;
	bool isBroken;
	 
	int requireStrength;
	int requireDexterity;
	int requireIntelligence;

	int requireLvl;                        

	//armor 
	int baseArmor;
	int hp;
	int mana;

	//Weapon
	short typeDMG;
	short range;
	int minDMG;
	int maxDMG;

};