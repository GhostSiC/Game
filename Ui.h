#pragma once

#include "Button.h"


class Ui : public Button {
public:
	Ui();
	virtual ~Ui();

	void renderAlert(sf::RenderTarget* target);
	void update();
	void engine();
//	void poolEvents(Vector2i* poz, sf::RenderTarget* target);

	void makeAllertInfo();
	//old name infoButton
	void makeInfoBox();
//
private:

	Button infoButton;
//
//	void initVarible();
//	void initView();
//	void getData();
};

//info if building compl 
//alert info
//info button
//not enough source
//
