#pragma once

#include <vector>
#include <iostream>

#include <tuple>

#include "pugixml.hpp"
using namespace pugi;



class Building
{

public:
	Building();
	virtual ~Building();
	void update();
	virtual void initVarible();

	void setName(const char* name);
	std::string getName();

	int getLvl() const;
	void lvlUp();
	bool getIfMaxLvl();

	void setId(int id);
	int getId() const;

	void getData();
	void setTypeBuilding(const char* type);

	

	std::tuple<int,int,int,int,int> getNextlvlV();

private:


	struct NEXTLVL {
		int gold;
		int stone;
		int wood;
		int food;
		int sulfur;
	} nextLvl;

	std::string name;

	int lvl;
	int id;

	const char* typeBuilding;

	bool notMaxLvl;

private:
	//popraw
};


class Source : public Building
{

public:
	Source();
	virtual ~Source();
	void initVarible();

	//przyrost materialu na dany okres
	int updateValue();

	void setBaseValue(int val);
	void setSourceName(const char* name);
	std::string getSourceName() const;

private:

	//unsigned __int64 value;

	int baseValue;

	std::string sourceName;

};


