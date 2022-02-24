#pragma once

#include "Ui.h"
#include "Button.h"

#include "Source.h"


#include "City.h"
#include "Character.h"
#include "Shop.h"
#include "CharacterDetails.h"


#include <fstream>
#include <iostream>


class Game
{
public:
	Game();
	virtual ~Game();
	void Engine();
	void Render();
	void Update();
	void UpdateDt();
	void poolEvents();
	const bool running() const;

	sf::Clock dtClock;
	float dt;
	


private:
	//varibles
	RenderWindow* window;
	VideoMode videoMode;
	Event event;
	float second;


	View view_main_button, gameContenerView, infoSourceView;

	sf::Texture texture;
	sf::Font font;

	Ui ui_game;

	Shop shop;
	CharacterDetails characterDetails;
	City city;

	std::vector<Character> charakters;

	//enum *ptr to class -> in class f() return name and -> to enum value
	/*
	 0 - pause
	 1 - miasto
	*/
	int type_status;

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

	} nextLvlSV;

	int gold;
	int stone;
	int wood;
	int food;
	int sulfur;

	std::vector<int*> ptrSource;

	std::vector<Button> containerMainButton;

	//Info Button
	Button alertButton, infoButton;
	void initInfoButton();

	
	//Info varible
	std::vector<sf::Text> sourceInfoText;


	void initVariables();

	sf::Vector2i MAXSIZEWINDOW;
	void initWindow();

	void initTexture();
	void initView();


	void updateInfoText(); 


	void getData(const char* tag);

	void setTypeGame();

};