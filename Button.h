#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Main.hpp>

using namespace sf;

#include "pugixml.hpp"
using namespace pugi;

#include <vector>
#include <iostream>
//struct 

class Button
{
private:
	sf::Sprite button;
	sf::Texture texture;

	sf::Text text;

	//F()
	void initVariables();
	void initSprites();
	void initText();

	//varible
	sf::Font font;
	Vector2f origin;
	int id;
	std::string name;
	bool visible = 1;

	std::vector<std::string> dspText;

	void adjustSize();

	//alert disappear
	bool isAlterButton = false;
	int timer = 0;


public:
	Button();
	virtual ~Button();


	//F()
	void update();
	void render(sf::RenderTarget* target);

	void setPosition(float x = 0.f, float y = 0.f);
	void setPositionByOrgini(float x = 0.f, float y = 0.f);
	Vector2f getPosition();
	Vector2f getSize();

	void setTexture(sf::Texture* texture, sf::IntRect rect);

	void setFont(sf::Font* font);
	void setFontSize(int size);
	void setColor(sf::Color color);

	void set_Name(const char* name);
	void set_Id(int id);
	void setText(std::string text);
	void setVisible(bool val);

	int getId();
	bool getVisible();
	std::string getName();

	void setSpriteScale(float x, float y);
	sf::FloatRect getGlobalBounds();

	int isClicked(sf::Vector2i poz);

	Vector2f getOrigin();

	//alter f()
	void setIsAlterButton(bool val);
	bool getIsAlterButton();
};