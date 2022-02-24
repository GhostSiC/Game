#pragma once

#include "Tavern.h"

class Shop : public Tavern
{
public:
	Shop();
	virtual ~Shop();

	void render(sf::RenderTarget* target);
	void engine();

	void poolEvents(Vector2i* poz, sf::RenderTarget* target);
	void poolEventsMoved(Vector2i* poz, sf::RenderTarget* target);

	void initCharakter();

	bool respNewCharacter = true;

private:
	void initButtons();

	unsigned short charaktersSpawnCount;

	//delete?
	std::vector<sf::Vector2f> spriteCharStaticPoz;

	void boughtCharacterInfoText();
	int goldCost;
	std::string boughtTextButton;
	sf::Vector2i boughtButtonRect;
	Button boughtButton;


	//if yes then only show in shop to reset 
	std::map<int, bool> ifBought;

};

