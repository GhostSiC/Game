#include "Button.h"

void Button::initVariables()
{

}

void Button::initSprites()
{
}

void Button::initText()
{


	this->text.setCharacterSize(24); // in pixels, not points!

	this->text.setFillColor(sf::Color::Red);
	

}

Button::Button()
{
	this->initVariables();
	this->initSprites();
	this->initText();
	
}

Button::~Button()
{

}

void Button::update()
{
	
	if (timer == 3) {
		visible = 0;
	}

	timer++;
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->button);

	target->draw(this->text);

}

void Button::setPosition(float x, float y)
{

	this->button.setOrigin(this->button.getLocalBounds().width / 2, this->button.getLocalBounds().height / 2);
	this->button.setPosition(x , y);

	this->text.setOrigin(this->text.getLocalBounds().width/2 , this->text.getLocalBounds().height/2);
	this->text.setPosition(x, y);

}

void Button::setPositionByOrgini(float x, float y)
{
	button.setOrigin(this->button.getLocalBounds().width / 2, this->button.getLocalBounds().height / 2);
	button.setPosition(x - button.getOrigin().x, y - button.getOrigin().y);

	//text.setOrigin(button.getOrigin().x, button.getOrigin().y);
	text.setOrigin(button.getOrigin().x, button.getOrigin().y);
	text.setPosition(button.getPosition().x , button.getPosition().y);
}

Vector2f Button::getPosition()
{
	return this->button.getPosition();
}

Vector2f Button::getSize()
{
	Vector2f res;
	res.x = this->button.getGlobalBounds().width;
	res.y = this->button.getGlobalBounds().height;

	return res;
	
}

void Button::setTexture(sf::Texture* texture, sf::IntRect rect)
{
	this->button.setTexture(*texture);
	this->button.setTextureRect(rect);

}

void Button::setFont(sf::Font* font)
{
	this->text.setFont(*font);
}

void Button::setFontSize(int size)
{
	text.setCharacterSize(size);
}

void Button::setColor(sf::Color color)
{
	text.setFillColor(color);
}

void Button::set_Name(const char* name)
{
	this->name = name;
	this->text.setString(name);
}

void Button::set_Id(int id)
{
	this->id = id;
}

void Button::setText(std::string text)
{

	this->text.setString(text);
	//this->text.setCharacterSize(24);

	adjustSize();
}

void Button::setVisible(bool val)
{
	visible = val;
}

int Button::getId()
{
	return this->id;
}

bool Button::getVisible()
{
	return visible;
}

std::string Button::getName()
{
	return name;
}

//fix
void Button::adjustSize()
{
	float width = this->text.getGlobalBounds().width;
	float height = this->text.getGlobalBounds().height;


	//sf::IntRect a = sf::IntRect(infoButtonRect->x, infoButtonRect->y, 32, 32);
	//button.setTextureRect(a);

	float scaleX = 1;
	float scaleY = 1;


	while (scaleX * 32 < width)
	{
		scaleX++;
	}

	while (scaleY * 32 < height)
	{
		scaleY++;
	}
	scaleX += 4;
	scaleY += 2.5;

	button.setScale(scaleX, scaleY);

	this->text.setOrigin(width / static_cast<float>(2), height / static_cast<float>(2));
}

void Button::setSpriteScale(float x, float y)
{
	button.setScale(x, y);

	//this->button.setOrigin(this->button.getLocalBounds().width / 2, this->button.getLocalBounds().height / 2);
}

sf::FloatRect Button::getGlobalBounds()
{
	return button.getGlobalBounds();

}

int Button::isClicked(sf::Vector2i poz)
{
	
	if(this->button.getGlobalBounds().contains(poz.x, poz.y))
		return this->id;
	else 
		return 0;
	
}

Vector2f Button::getOrigin()
{
	return this->button.getOrigin();
}

void Button::setIsAlterButton(bool val)
{
	isAlterButton = val;
}

bool Button::getIsAlterButton()
{
	return isAlterButton;
}
