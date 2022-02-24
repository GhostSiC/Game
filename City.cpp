#include "City.h"

City::City()
{
	initVarible();

	
}

City::~City()
{
}

void City::render(sf::RenderTarget* target)
{
	sf::RectangleShape rec;
	rec.setSize(Vector2f(2000, 1500));
	rec.setFillColor(sf::Color(100, 200, 0, 200));

	target->setView(mainView);
	target->draw(rec);

	

	//down
	target->setView(charView);
	rec.setFillColor(sf::Color(80, 0, 100, 250));
	target->draw(rec);

	for (auto& i : containerButton)
		i.render(target);

		

	target->setView(target->getDefaultView());

}

void City::update()
{

}

void City::engine()
{
	//0
	initView();
	

	//1
	initVarible();

	//2
	initSource();
	getData();
	//3

	//std::cout << idClicked << '\n';
}

void City::poolEvents(Vector2i* poz, sf::RenderTarget* target)
{

	auto pozz = Vector2i(target->mapPixelToCoords(*poz, charView));
	int flag_click;

	for (auto& i : this->containerButton) {
		flag_click = i.isClicked(pozz);
		if (flag_click ) {
			this->buttonClickAction(flag_click);
			updateInfoText();
			ptrInfoButton->setVisible(1);
			ptrInfoButton->setPosition((poz->x + ptrInfoButton->getSize().x / 2) + 5, (poz->y - ptrInfoButton->getSize().y / 2) - 5);

		}
	}

}

void City::poolEventsMoved(Vector2i* poz, sf::RenderTarget* target)
{

	int msover;
	auto pozz = Vector2i(target->mapPixelToCoords(*poz, charView));

	for (auto& i : this->containerButton) {

		msover = i.isClicked(pozz);
		if (msover) {

			if (idNextLvlV != msover) {
				updateInfoText();

				//auto pozFixToGlobal = target->mapCoordsToPixel(poz, target);

				for (auto& j : productionBuilding) {

					if (j.getId() == msover) {

						idBuildingLastFocus = j.getId();

						ptrInfoButton->setVisible(1);
						ptrInfoButton->setPosition((poz->x + ptrInfoButton->getSize().x / 2) + 5, (poz->y - ptrInfoButton->getSize().y / 2) - 5);

						return;
					}
				}
				for (auto& j : noProductionBuilding) {

					if (j.getId() == msover) {
						idBuildingLastFocus = j.getId();

						ptrInfoButton->setVisible(1);
						ptrInfoButton->setPosition((poz->x + ptrInfoButton->getSize().x / 2) + 5, (poz->y - ptrInfoButton->getSize().y / 2) - 5);

						return;
					}
				}
			}
		}
		else {
			ptrInfoButton->setVisible(0);
		}

	}

}

void City::pushSourceValue(std::vector<int*>* value)
{
	ptrSource = *value;
}

void City::initVarible()
{
	idNextLvlV = 0;
	idNextLvlV = 0;
}

void City::updateSource()
{
	int index = 0;

	for (auto& i : productionBuilding)
	{
		//tutaj by³ error o przekroczeniu miejsca w pamiêci
		//Unhandled exception at 0x7762B662 in Game.exe: Microsoft C++ exception: std::out_of_range at memory location 0x0055DF28.
		if(index < 5)
			*ptrSource.at(index) += i.updateValue();
		index++;
	}
}

void City::initView()
{

	mainView.setViewport(sf::FloatRect(0.f, 0.2f, 1.f, 0.7f));
	mainView.setSize(MAXSIZEVIEW.x, MAXSIZEVIEW.y / 10.f * 7);
	mainView.setCenter(this->mainView.getSize().x / 2, this->mainView.getSize().y / 2);


	charView.setViewport(sf::FloatRect(0.f, 0.7f, 1.f, 0.3f));
	charView.setSize(MAXSIZEVIEW.x, MAXSIZEVIEW.y / 10.f * 3);
	charView.setCenter(this->charView.getSize().x / 2, this->charView.getSize().y / 2);

}

void City::setViewMax(unsigned int sizeX, unsigned int sizeY)
{
	MAXSIZEVIEW.x = sizeX;
	MAXSIZEVIEW.y = sizeY;
}

void City::setTexture(sf::Texture* texture)
{
	this->texture = *texture;
}

void City::setFont(sf::Font* font)
{
	this->font = *font;
}

void City::getButtons(Button* btnAlert, Button* btnInfo)
{
	ptrInfoButton = btnInfo;
	ptrAlertButton = btnAlert;
}



void City::initSource()
{
	xml_document doc;

	if (doc.load_file("building.xml")) {

		String name;

		Source workSource;

		xml_node tools = doc.child("Building").child("Production");

		for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it)
		{

			for (xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
			{

				name = ait->name();

				if (name == "id") {
					workSource.setId(atoi(ait->value()));
				}
				else if (name == "name") {
					workSource.setName(ait->value());
				}
				else if (name == "nameSource") {
					workSource.setSourceName(ait->value());

				}
				else if (name == "baseValue") {
					workSource.setBaseValue(atoi(ait->value()));
				}
			}

			productionBuilding.push_back(workSource);
		}

		xml_node toolsnon = doc.child("Building").child("NonProduction");

		Building workBuilding;

		for (xml_node_iterator it = toolsnon.begin(); it != toolsnon.end(); ++it)
		{
			for (xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
			{

				name = ait->name();



				if (name == "id") {
					workBuilding.setId(atoi(ait->value()));
				}
				else if (name == "name") {
					workBuilding.setName(ait->value());
				}
			}
			noProductionBuilding.push_back(workBuilding);
		}
	}
}


void City::buttonClickAction(int& id)
{

	bool lvlUpFlag = true;

	for (size_t j = 0; j < ptrSource.size(); j++)
	{
		if (*ptrSource.at(j) < nextLvlSV.getValue(j))
			lvlUpFlag = false;

		
	}

	if (lvlUpFlag) {

		*ptrSource.at(0) -= nextLvlSV.gold;
		*ptrSource.at(1) -= nextLvlSV.stone;
		*ptrSource.at(2) -= nextLvlSV.wood;
		*ptrSource.at(3) -= nextLvlSV.food;
		*ptrSource.at(4) -= nextLvlSV.sulfur;


		for (auto& i : productionBuilding) {

			if (i.getId() == id) {
				i.lvlUp();
			}
		}

		for (auto& i : noProductionBuilding) {
			if (i.getId() == id) {
				i.lvlUp();
			}
		}
	}
	else
		throwAlertButton(1);
		

}

void City::updateInfoText()
{
	std::string text;
	bool notMaxLvl = true;

	for (auto& i : productionBuilding)
		if (idBuildingLastFocus == i.getId()) {
			text = "Obecny poziom: " + std::to_string(i.getLvl()) + '\n';
			text += "Do nastepmego poziomu (" + std::to_string(i.getLvl() + 1) + ") potrzebujesz:\n";
			std::tie(nextLvlSV.gold, nextLvlSV.stone, nextLvlSV.wood, nextLvlSV.food, nextLvlSV.sulfur) = i.getNextlvlV();
			notMaxLvl = i.getIfMaxLvl();
			
		}
		//else{} daj for tutaj
		else{
			for (auto& i : noProductionBuilding)
				if (idBuildingLastFocus == i.getId()) {
					text = "Obecny poziom: " + std::to_string(i.getLvl()) + '\n';
					text += "Do nastepmego poziomu (" + std::to_string(i.getLvl() + 1) + ") potrzebujesz:\n";
					std::tie(nextLvlSV.gold, nextLvlSV.stone, nextLvlSV.wood, nextLvlSV.food, nextLvlSV.sulfur) = i.getNextlvlV();
					notMaxLvl = i.getIfMaxLvl();

				}
		}

	for (size_t i = 0; i < nextLvlSV.SIZE; i++) {

		if (notMaxLvl) {
		text += "potrzebne " + nextLvlSV.getName(i) + ": " + std::to_string(nextLvlSV.getValue(i)) + '\n';
	}
		else {
			text = "Max lvl";
		}
		ptrInfoButton->setText(text);
	}
}

//1 - not enough soruce
void City::throwAlertButton(int id)
{
	switch (id)
	{
	case 1:
		ptrAlertButton->setText("Za malo surowcow");
		ptrAlertButton->setVisible(1);
		break;

	default:
		ptrAlertButton->setVisible(0);
		break;
	}
	
}

void City::getData()
{
	xml_document doc;

	if (doc.load_file("Button.xml")) {

		Button work_button;

		sf::Vector2f rect_Button;
		sf::IntRect rect_Tex_Button;

		String name;

		xml_node tools = doc.child("Ui").child("Button").child("City");

		containerButton.clear();

		for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it)
		{

			for (xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait)
			{

				name = ait->name();

				if (name == "id") {
					work_button.set_Id(atoi(ait->value()));
				}
				else if (name == "name") {
					work_button.set_Name(ait->value());
				}
				else if (name == "left") {
					rect_Button.x = atoi(ait->value());
				}
				else if (name == "top") {
					rect_Button.y = atoi(ait->value());
				}
				else if (name == "t_left") {
					rect_Tex_Button.left = atoi(ait->value());
				}
				else if (name == "t_top") {
					rect_Tex_Button.top = atoi(ait->value());
				}
				else if (name == "t_width") {
					rect_Tex_Button.width = atoi(ait->value());
				}
				else if (name == "t_height") {
					rect_Tex_Button.height = atoi(ait->value());
				}
			}

			work_button.setFont(&this->font);
			

			sf::IntRect intrec = sf::IntRect(160, 128, 32, 32);
			work_button.setTexture(&this->texture, intrec);

			work_button.setSpriteScale(6, 4);
			work_button.setFontSize(25);

			work_button.setPosition(rect_Button.x, rect_Button.y);

			this->containerButton.push_back(work_button);



		}
	}
}
