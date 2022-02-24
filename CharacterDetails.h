#pragma once

#include "Tavern.h"

class CharacterDetails : public Tavern{

public:
	CharacterDetails();
	virtual ~CharacterDetails();

	void render(sf::RenderTarget* target);

	void poolEvents(Vector2i* poz, sf::RenderTarget* target);
	void poolEventsMoved(Vector2i* poz, sf::RenderTarget* target);
	void poolEventsWheel(Vector2i* poz, sf::RenderTarget* target, float delta);

	void engine();

	void loadCharakter();

private:
	void initView();

	void initBackpack();

	sf::View backpackView;

	unsigned short backpackSlotMaxSize;
	std::vector<MapItemSpriteStruct> backpackMap;

	float maxPoz;
	
	float pointMaxSizeBackpackViewY;
	
};

