#pragma once

#include "Button.h"
#include "Character.h"

//dziedziczenie 
class Tavern{

public:
	Tavern();
	virtual ~Tavern();

	virtual void initVarible();
	virtual void poolEventsWheel(Vector2i* poz, sf::RenderTarget* target, float delta);



	void setViewMax(unsigned int sizeX, unsigned int sizeY);
	void setTexture(sf::Texture* texture);
	void setFont(sf::Font* font);

	void initText();

	void getButtons(Button* btnAlert, Button* btnInfo);

protected:

	void initUiSprite();
	void initEqItemSprite();

	void reloadCharacterDisplay();

	//varible
	sf::Texture avatarTexture;
	Character* characterPTR;
	std::vector<Character> characters;

	float characterOffSetX;
	const unsigned short speedMove = 16;
	float pointMaxOffSetCharacterX;

	sf::Sprite profile;
	sf::Texture texture;

	std::vector<sf::Text> text;
	sf::Font font;

	sf::View characterView, charView, eqView;

	//info
	//bool showDetail;

	sf::Vector2i MAXSIZEVIEW;

	//mo¿e mo¿na daæ do StructCharakters
	//std::vector<Character> charakters;


	Button *ptrInfoButton, *ptrAlertButton;

	

	//id active character
	unsigned short idClicked;
	
	void setInfoEqText(int id);


	struct MapItemSpriteStruct
	{
		//check if not double
		unsigned int idSLot;
		unsigned int idItem;
		bool consume = false;
		bool ifEq = false;

		sf::Sprite bgSprite;
		sf::Sprite eqSprite;

		sf::IntRect getQualityBorder(unsigned int idQuality) {

			sf::IntRect borderQualityItem;
			
			if (idQuality == 0)
				borderQualityItem = sf::IntRect(
					1888,
					768,
					32,
					32
				);
			//zwykly
			else if (idQuality == 1)
				borderQualityItem = sf::IntRect(
					224,
					128,
					32,
					32
				);
			//rzadki
			else if (idQuality == 2)
				borderQualityItem = sf::IntRect(
					160,
					128,
					32,
					32
				);
			//unikatowy
			else if (idQuality == 3)
				borderQualityItem = sf::IntRect(
					2016,
					96,
					32,
					32
				);
			//legendarny
			else if (idQuality == 4)
				borderQualityItem = sf::IntRect(
					1920,
					96,
					32,
					32
				);
			//mityczny
			else if (idQuality == 5)
				borderQualityItem = sf::IntRect(
					1920,
					96,
					32,
					32
				);

			return borderQualityItem;
		}

	};

	std::vector<MapItemSpriteStruct> eqItem;

	
private:
	void initView();
	
	void initTextureAvatar();
};


