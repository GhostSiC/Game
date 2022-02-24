#include "Item.h"

Item::Item()
{
	initVarible();
}

Item::~Item()
{
}

void Item::initVarible()
{
	statStrength = 0;
	statDexterity = 0;
	statIntelligence = 0;
	crit = 0;
	luck = 0;

	minDMG = 0;
	maxDMG = 0;

	baseArmor = 0;
	hp = 0;
	mana = 0;
	block = 0;
	twoHand = false;

	upgrade = 0;
	quality = 1;
	isBroken = true;
	isWeapon = false;
	idSlot = 0;

	requireStrength = 0;
	requireDexterity = 0;
	requireIntelligence = 0;
	requireLvl = 0;
	
}

void Item::GetDataEq(int id)
{
	std::string idString = std::to_string(id);

	pugi::xml_document doc;
	if (!doc.load_file("Item.xml")) return;

	std::string nameXML;

	pugi::xml_node tools = doc.child("Item").child("Eq");

	tools = tools.find_child_by_attribute("Meta", "id", idString.c_str());

	this->id = id;

	if (tools.empty()) return;

	for (pugi::xml_node_iterator it = tools.begin(); it != tools.end(); ++it)
	{
		nameXML = it->name();

		if (nameXML == "require") {
			for (pugi::xml_node& ait : *it)
			{
				nameXML = ait.name();

				if (nameXML == "strength")
					requireStrength = std::atoi(ait.child_value());

				else if (nameXML == "dexterity")
					requireDexterity = std::atoi(ait.child_value());

				else if (nameXML == "intelligence")
					requireIntelligence = std::atoi(ait.child_value());

				else if (nameXML == "lvl")
					requireLvl = std::atoi(ait.child_value());

			}
		}

		else if (nameXML == "textureRect") {
			for (pugi::xml_node& ait : *it)
			{
				nameXML = ait.name();

				if (nameXML == "left")
					textureRect.left = std::atoi(ait.child_value());

				else if (nameXML == "top")
					textureRect.top = std::atoi(ait.child_value());

				else if (nameXML == "width")
					textureRect.width = std::atoi(ait.child_value());

				else if (nameXML == "height")
					textureRect.height = std::atoi(ait.child_value());

			}
		}	
		else if (nameXML == "baseStat") {
			for (pugi::xml_node& ait : *it)
			{
				nameXML = ait.name();

				if (nameXML == "statStrength")
					statStrength = std::atoi(ait.child_value());

				else if (nameXML == "statDexterity")
					statDexterity = std::atoi(ait.child_value());

				else if (nameXML == "statIntelligence")
					statIntelligence = std::atoi(ait.child_value());

				else if (nameXML == "luck")
					luck = std::atoi(ait.child_value());

				else if (nameXML == "crit")
					crit = std::atoi(ait.child_value());

			}
		}
		else if (nameXML == "eqStat") {
			for (pugi::xml_node& ait : *it)
			{
				nameXML = ait.name();

				if (nameXML == "baseArmor")
					baseArmor = std::atoi(ait.child_value());

				else if (nameXML == "hp")
					hp = std::atoi(ait.child_value());

				else if (nameXML == "mana")
					mana = std::atoi(ait.child_value());
				
				else if (nameXML == "block")
					block = std::atoi(ait.child_value());
			}
		}
		else if (nameXML == "weponStat") {
			isWeapon = true;
			for (pugi::xml_node& ait : *it)
			{
				nameXML = ait.name();

				if (nameXML == "typeDMG")
					typeDMG = std::atoi(ait.child_value());

				else if (nameXML == "range")
					range = std::atoi(ait.child_value());

				else if (nameXML == "minDMG")
					minDMG = std::atoi(ait.child_value());
				
				else if (nameXML == "maxDMG")
					maxDMG = std::atoi(ait.child_value());
			}
		}
		else if (nameXML == "name") {
			name = it->child_value();
			isBroken = false;
		}
		else if (nameXML == "type") 
			type = std::atoi(it->child_value());

		else if (nameXML == "upgrade")
			upgrade = std::atoi(it->child_value());
		else if (nameXML == "quality")
			quality = std::atoi(it->child_value());
	}
	

	if (type == 9 || type == 13)
		twoHand = true;
	else
		twoHand = false;
}

int Item::getType()
{
	return type;
}

int Item::getId()
{
	return id;
}

std::string Item::getName()
{
	return name;
}

int Item::getBaseArmor()
{
	return baseArmor;
}

int Item::getHp()
{
	return hp;
}

int Item::getMana()
{
	return mana;
}

int Item::getBlock()
{
	return block;
}

bool Item::getIsWeapon()
{
	return isWeapon;
}

bool Item::getIsTwoHand()
{
	return twoHand;
}

int Item::getStatStrength()
{
	return statStrength;
}

int Item::getStatDexterity()
{
	return statDexterity;
}

int Item::getStatIntelligence()
{
	return statIntelligence;
}

int Item::getLuck()
{
	return luck;
}

int Item::getCrit()
{
	return crit;
}

int Item::getUpgrade()
{
	return upgrade;
}

unsigned short Item::getQuality()
{
	return quality;
}

unsigned short Item::getBroken()
{
	return isBroken;
}

int Item::getRequireStrength()
{
	return requireStrength;
}

int Item::getRequireDexterity()
{
	return requireDexterity;
}

int Item::getRequireIntelligence()
{
	return requireIntelligence;
}

int Item::getRequireLvl()
{
	return requireLvl;
}

int Item::getTextureRectLeft()
{
	return textureRect.left;
}

int Item::getTextureRectTop()
{
	return textureRect.top;
}

int Item::getTextureRectWidth()
{
	return textureRect.width;
}

int Item::getTextureRectHeight()
{
	return textureRect.height;
}

short Item::getTypeDMG()
{
	return typeDMG;
}

short Item::getRange()
{
	return range;
}

int Item::getMinDMG()
{
	return minDMG;
}

int Item::getMaxDMG()
{
	return maxDMG;
}


