#include "Source.h"

Building::Building() 
{
	this->initVarible();
}

Building::~Building()
{
}

void Building::update()
{
}

void Building::initVarible()
{
	lvl = 1;
	notMaxLvl = true;
	typeBuilding = "NonProduction";
}


void Building::setName(const char* name)
{
	this->name = name;
}

std::string Building::getName()
{
	return name;
}

int Building::getLvl() const
{
	return lvl;
}

void Building::lvlUp()
{
	if(notMaxLvl)
		lvl++;
}

void Building::setId(int id)
{
	this->id = id;
}

int Building::getId() const
{
	return id;
}

void Building::getData()
{
	xml_document doc;

	if (doc.load_file("BuildingCost.xml")) {

		std::string name;

		std::string id_s = std::to_string(this->id);
		const char* id = id_s.c_str();

		xml_node tools = doc.child("BuildingCost").find_child_by_attribute(typeBuilding, "id", id);

		id_s = std::to_string(this->lvl + 1);
		id = id_s.c_str();

		tools = tools.find_child_by_attribute("lvl", "id", id);

		if (!tools.empty())
			for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it)
			{
				for (xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
				{
					name = ait->name();

					if (name == "goldCost")
						nextLvl.gold = std::atoi(ait->value());
					else if (name == "stoneCost")
						nextLvl.stone = std::atoi(ait->value());
					else if (name == "woodCost")
						nextLvl.wood = std::atoi(ait->value());
					else if (name == "foodCost")
						nextLvl.food = std::atoi(ait->value());
					else if (name == "sulfurCost")
						nextLvl.sulfur = std::atoi(ait->value());
				}
			}
		else
			notMaxLvl = false;
	}
}

void Building::setTypeBuilding(const char* type)
{
	typeBuilding = type;
}

bool Building::getIfMaxLvl()
{
	return notMaxLvl;
}

std::tuple<int, int, int, int, int> Building::getNextlvlV()
{
	this->getData();
	return std::tuple<int, int, int, int, int>(nextLvl.gold, nextLvl.stone, nextLvl.wood, nextLvl.food, nextLvl.sulfur);
}



Source::Source()
{
	this->initVarible();
}

Source::~Source()
{
}


void Source::initVarible()
{
	this->baseValue = 1;
	setTypeBuilding("Production");
}

int Source::updateValue()
{
	return this->baseValue + static_cast<int>(this->getLvl()) * 3;
}


void Source::setBaseValue(int val)
{
	this->baseValue = val;
}

void Source::setSourceName(const char* name)
{
	this->sourceName = name;
}

std::string Source::getSourceName() const
{
	return this->sourceName;
}
