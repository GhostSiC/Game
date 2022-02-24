#pragma once

#include "Button.h"
#include "Character.h"
#include "Source.h"


class City {

public:
	City();
	virtual ~City();
	void render(sf::RenderTarget* target);
	void update();
	void engine();
	void poolEvents(Vector2i* poz, sf::RenderTarget* target);
	void poolEventsMoved(Vector2i* poz, sf::RenderTarget* target);

	void pushSourceValue(std::vector<int*>* value);

	
	void updateSource();

	
	void setViewMax(unsigned int sizeX, unsigned int sizeY);

	void setTexture(sf::Texture* texture);
	void setFont(sf::Font* font);

	void getButtons(Button* btnAlert, Button* btnInfo);

private:

	void initVarible();
	void initView();


	void initSource();

	void buttonClickAction(int& id);

	void updateInfoText();
	void throwAlertButton(int id);

	//zrob odzzielna klase
	void getData();
	//varible



	sf::Sprite profile;
	sf::Texture texture;

	std::vector<sf::Text> text;

	sf::Font font;

	sf::View mainView, charView, eqView;
	bool showDetail;

	sf::Vector2i MAXSIZEVIEW;

	


	std::vector<Source> productionBuilding;
	std::vector<Building> noProductionBuilding;

	struct SourceValue
	{
		int gold;
		int stone;
		int wood;
		int food;
		int sulfur;

		int const SIZE = 5;

		int getValue(short i){
			switch (i)
			{
			case 0:
				return gold;
				break;
			case 1:
				return stone;
				break;
			case 2:
				return wood;
				break;
			case 3:
				return food;
				break;
			case 4:
				return sulfur;
				break;
			default:
				break;
			}
		}

		std::string getName(short i) {
			switch (i)
			{
			case 0:
				return "Zloto";
				break;
			case 1:
				return "Kamien";
				break;
			case 2:
				return "Drewno";
				break;
			case 3:
				return "Jedzenia";
				break;
			case 4:
				return "Siarka";
				break;
			default:
				break;
			}
		}

	}nextLvlSV;


	std::vector<int*> ptrSource;
	

	std::vector<Button> containerButton;

	Button* ptrInfoButton, * ptrAlertButton;

	int idNextLvlV;
	std::vector<sf::Text> sourceInfoText;


	//varible info Button
	int idBuildingLastFocus;
	sf::Vector2f pozInfoButton;
	bool flagVisible;


};

