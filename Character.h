#pragma once

#include "Item.h"
#include <SFML/Graphics.hpp>



class Character
{
public:

	Character();
	virtual ~Character();

	void renderAvatar(sf::RenderTarget* target);

	void engine();

	void respawn();

	void statsUpdate();

	std::string takeoff(int idItem, int idSlot);
	std::string puton(int idItem);

	


	std::string getName();
	std::string getSurname();


	unsigned short getId();
	unsigned short getLvl();
	unsigned short getRare();
	unsigned int getMaxHp();
	unsigned int getMinAttack();
	unsigned int getMaxAttack();
	unsigned int getDef();

	unsigned int getBaseStrength();
	unsigned int getBaseDexterity();
	unsigned int getBaseIntelligence();

	unsigned int getBaseLuck();

	unsigned int getMaxStrength();
	unsigned int getMaxDexterity();
	unsigned int getMaxIntelligence();
	unsigned int getMaxLuck();

	int getCostGold();
	int getIdSprite();

	Character getData(int id);
	bool saveCharacterData();
	std::string changeCharacterData(int idItem, int idSlot);



	int getIdItemOn(std::string nameSlot);

	void setTexture(sf::Texture* tex);


	int getIdByClick(sf::Vector2i* poz, sf::RenderTarget* target);
	
	void setPosition(sf::Vector2f poz);
	sf::Vector2f getPosition();
	
	void setId(int id);

private:
	void initVarible();
	void initName();
	void initBasicValue();

	std::string dataCharacterUpdateStats();
	std::string returnFirstEmptySlot(int idItem);
	//return self


	sf::Sprite avatarProfile;

	//witch one fragment sprite load
	unsigned short pozSprite;


	unsigned int id;

	//base stat
	std::string name;
	std::string surname;

	//basic varible
	unsigned short lvl;
	unsigned short rare;

	//exp max and currently

	unsigned int maxHp;
	unsigned int hp;
	unsigned int minAttack;
	unsigned int maxAttack;
	unsigned int def;
	
	
	//basic
	unsigned int BaseStrength;
	unsigned int BaseDexterity;
	unsigned int BaseIntelligence;
	unsigned int BaseLuck;
	unsigned int BaseCrit;
	
	//max stat to count
	unsigned int maxStrength;
	unsigned int maxDexterity;
	unsigned int maxIntelligence;
	unsigned int maxLuck;
	unsigned int maxCrit;

	//cost 
	int costGold, costFood;

	//must count
	unsigned int currentyHp;

	//czy pobierac jedzenie na dany okres (wprowadzac?)
	bool foodPerDay;

	//perk

	//Item
	int howManyIntem;
	

	std::vector<int> startIdItem;
	std::map<int, const char*> dictonaryIdItem;

	//eq
	//On 

	Item helmet;
	Item armor;
	Item legs;
	Item shoes;
	Item gloves;
	Item ring_1;
	Item ring_2;
	Item necklaces;

	Item weapon_1;
	Item weapon_2;


	//In backpack
	//mb storage only id

};

/*
	eq graf zrób oddzielny plik xml do przechowywania poz, skali, textureRect


*/