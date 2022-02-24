#include "CharacterDetails.h"

CharacterDetails::CharacterDetails()
{
}

CharacterDetails::~CharacterDetails()
{
}

void CharacterDetails::render(sf::RenderTarget* target)
{
	sf::RectangleShape rec;
	rec.setSize(Vector2f(2000, 1500));


	
	//right
	target->setView(charView);
	rec.setFillColor(sf::Color(0, 0, 100, 100));
	target->draw(rec);
	target->draw(profile);

	for (auto& i : text)
		target->draw(i);

	//middle
	target->setView(eqView);
	rec.setFillColor(sf::Color(150, 220, 0, 100));
	target->draw(rec);
	for (auto& i : eqItem) {
		target->draw(i.bgSprite);
		target->draw(i.eqSprite);
	}

	target->setView(backpackView);
	rec.setFillColor(sf::Color(15, 220, 150, 100));
	target->draw(rec);
	for (auto& i : backpackMap) {
		target->draw(i.bgSprite);
		target->draw(i.eqSprite);
	}
	

	target->setView(characterView);
	rec.setFillColor(sf::Color(100, 200, 0, 100));
	target->draw(rec);

	for (auto& i : characters) {
		i.renderAvatar(target);
	}


	target->setView(target->getDefaultView());

}

void CharacterDetails::poolEvents(Vector2i* poz, sf::RenderTarget* target)
{
	
	auto pozz = Vector2i(target->mapPixelToCoords(*poz, characterView));
	//(characterView.getViewport().top) * target->getSize().y
	if (poz->y > 0) {
		for (auto& i : characters) {
			idClicked = i.getIdByClick(&pozz, target);


			if (idClicked) {
				characterPTR = &i;
				initText();
				initUiSprite();

				initEqItemSprite();

				//saveData();

				return;
			}
		}
	}

	if (characterPTR == nullptr) return;
	
	pozz = Vector2i(target->mapPixelToCoords(*poz, eqView));

	if (pozz.x < 0) {
		ptrInfoButton->setVisible(0);
	}
	else if (pozz.x > eqView.getSize().x) {
		ptrInfoButton->setVisible(0);
		
	}
	else if (poz->y > (eqView.getViewport().height + 0.2f) * target->getSize().y) {
		ptrInfoButton->setVisible(0);
	}
	//top
	else if (poz->y < eqView.getViewport().top * target->getSize().y) {
		ptrInfoButton->setVisible(0);
	}
	else {
		for (auto& i : eqItem) {
			if (i.eqSprite.getGlobalBounds().contains(pozz.x, pozz.y)) {

				std::string textDSP = characterPTR->takeoff(i.idItem, i.idSLot);

				if (textDSP == "") {
					reloadCharacterDisplay();
					initBackpack();
					//save data change
				}
				else {
					ptrAlertButton->setText(textDSP);
					ptrAlertButton->setVisible(1);
				}
				return;
			}
			else {
				ptrAlertButton->setVisible(0);
			}
		}
	}
	
	if (poz->y > (backpackView.getViewport().height + 0.2f) * target->getSize().y) {
		ptrInfoButton->setVisible(0);
	}
	//top
	else if (poz->y < backpackView.getViewport().top * target->getSize().y) {
		ptrInfoButton->setVisible(0);
	}
	else {
		pozz = Vector2i(target->mapPixelToCoords(*poz, backpackView));
		for (auto& i : backpackMap) {

			if (i.eqSprite.getGlobalBounds().contains(pozz.x, pozz.y)) {

				std::string textDSP = characterPTR->changeCharacterData(i.idItem, i.idSLot);

				if (textDSP == "") {
					reloadCharacterDisplay();
					initBackpack();
					//save data change
				}
				else {
					ptrAlertButton->setText(textDSP);
					ptrAlertButton->setVisible(1);
				}


				return;
			}
			else {
				ptrAlertButton->setVisible(0);
			}
		}
	}
}

void CharacterDetails::poolEventsMoved(Vector2i* poz, sf::RenderTarget* target)
{
	

	auto pozz = Vector2i(target->mapPixelToCoords(*poz, eqView));

	if (poz->y > (backpackView.getViewport().height + 0.2f) * target->getSize().y) {
		ptrInfoButton->setVisible(0);
	}
	//top
	else if (poz->y < backpackView.getViewport().top * target->getSize().y) {
		ptrInfoButton->setVisible(0);
	}
	else {
		for (auto& i : eqItem) {

			if (i.eqSprite.getGlobalBounds().contains(pozz.x, pozz.y)) {

				setInfoEqText(i.idItem);

				ptrInfoButton->setVisible(1);

				if (pozz.y - ptrInfoButton->getGlobalBounds().height > 0)
					ptrInfoButton->setPosition(poz->x + ptrInfoButton->getGlobalBounds().width / 2, poz->y - ptrInfoButton->getGlobalBounds().height / 2);
				else
					ptrInfoButton->setPosition(poz->x + ptrInfoButton->getGlobalBounds().width / 2, poz->y + ptrInfoButton->getGlobalBounds().height / 2);

				return;
			}
			else {
				ptrInfoButton->setVisible(0);
			}
		}

		pozz = Vector2i(target->mapPixelToCoords(*poz, backpackView));
		for (auto& i : backpackMap) {

			if (i.eqSprite.getGlobalBounds().contains(pozz.x, pozz.y)) {

				setInfoEqText(i.idItem);
				ptrInfoButton->setVisible(1);

				if (pozz.y - ptrInfoButton->getGlobalBounds().height > 0)
					ptrInfoButton->setPosition(poz->x + ptrInfoButton->getGlobalBounds().width / 2, poz->y - ptrInfoButton->getGlobalBounds().height / 2);
				else
					ptrInfoButton->setPosition(poz->x + ptrInfoButton->getGlobalBounds().width / 2, poz->y + ptrInfoButton->getGlobalBounds().height / 2);

				return;
			}
			else {
				ptrInfoButton->setVisible(0);
			}
		}
	}
}


void CharacterDetails::poolEventsWheel(Vector2i* poz, sf::RenderTarget* target, float delta)
{
	


	//fix info item show if item is up ( if move)
	bool canMove = true;

	//Y bottom
	//if (pozz.y > 0) {
	if (poz->y > (backpackView.getViewport().height + 0.2f) * target->getSize().y) {
		canMove = false;
	}
	//top
	else if (poz->y < backpackView.getViewport().top * target->getSize().y) {
		canMove = false;
	}
	
	else if (poz->x < MAXSIZEVIEW.x * backpackView.getViewport().width) {

		if (maxPoz + (delta * speedMove) <= 0)
			canMove = false;
		
		if (maxPoz + (delta * speedMove) >= pointMaxSizeBackpackViewY)
			canMove = false;

		if (canMove) {
			backpackView.move(sf::Vector2f(0, delta * speedMove));
			maxPoz += delta * speedMove;
		}
	}

	if(poz->y > (characterView.getViewport().top) * target->getSize().y) {
		bool canMove = true;

		if (characterOffSetX + (delta * speedMove / 2) <= 0)
			canMove = false;

		if (characterOffSetX + (delta * speedMove / 2) > pointMaxOffSetCharacterX)
			canMove = false;

		if (canMove) {
			characterView.move(sf::Vector2f(delta * speedMove / 2, 0));
			characterOffSetX += delta * speedMove / 2;
		}
	}
}

void CharacterDetails::engine()
{
	initView();
	loadCharakter();

	characterOffSetX = 0;
	maxPoz = 0;

	initBackpack();
}

void CharacterDetails::loadCharakter()
{
	xml_document doc;

	if (doc.load_file("Character.xml")) {
		characters.clear();
		std::string nameXML;
		int pozX = 0;

		xml_node tools = doc.child("Character");

		if (!tools.empty()) {

			for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it)
			{
				nameXML = it->name();
				if (nameXML == "Meta") {
					for (pugi::xml_attribute_iterator rt = it->attributes_begin(); rt != it->attributes_end(); ++rt) {
						nameXML = rt->name();
						if (nameXML == "id") {
							//create new empty charakter
							Character wokrCharakters;
							wokrCharakters.engine();
							wokrCharakters = wokrCharakters.getData(std::atoi(rt->value()));

							wokrCharakters.setTexture(&avatarTexture);
							wokrCharakters.setPosition(
								sf::Vector2f(16 + (pozX * 96),
								16
									));
							pozX++;
							characters.push_back(wokrCharakters);
						}
					}
				}
			}
			//pointMaxOffSetCharacterX = characters.back().getPosition().x - characterView.getSize().x;
			pointMaxOffSetCharacterX = (16 + (characters.size() * 96)) - characterView.getSize().x;
		}
	}
}

void CharacterDetails::initView()
{
	backpackView.setViewport(sf::FloatRect(0.f, 0.2f, 0.3f, 0.7f));
	backpackView.setCenter(backpackView.getSize().x / 2, backpackView.getSize().y / 2);
	
}

void CharacterDetails::initBackpack()
{
	xml_document doc;

	if (doc.load_file("Backpack.xml")) {

		std::string nameXML;
		int pozX = 0;
		MapItemSpriteStruct workStr;

		backpackMap.clear();

		xml_node tools = doc.child("Backpack");

		if (!tools.empty()) {

			for (xml_node_iterator it = tools.begin(); it != tools.end(); ++it)
			{
				nameXML = it->name();
				if (nameXML == "MaxSlot") {
					backpackSlotMaxSize = std::stoi(it->child_value());
					backpackMap.resize(backpackSlotMaxSize);
				}
				else if (nameXML == "Slot") {
					for (pugi::xml_attribute_iterator rt = it->attributes_begin(); rt != it->attributes_end(); ++rt) {
						nameXML = rt->name(); 
						if (nameXML == "idSlot")
							workStr.idSLot = std::stoi(rt->value());
					}
					for (pugi::xml_node_iterator rt = it->begin(); rt != it->end(); ++rt) {
						nameXML = rt->name();

						if (nameXML == "idItem") {
							workStr.idItem = std::stoi(rt->child_value());
						}
					}
					backpackMap.at(workStr.idSLot) = workStr;
				}
			}
		}

		sf::Sprite workSprite;
		workSprite.setTexture(this->texture);
		workSprite.setScale(6.f, 4.f);
		Item workItem;
		int rowSpriteBackPack = 3;

		int i = 0;

		for (auto& j : backpackMap) {

			workSprite.setTextureRect(
				sf::IntRect(
					224,
					128,
					32,
					32
				));

			float width = workSprite.getGlobalBounds().width;

			workSprite.setPosition(
				(i % rowSpriteBackPack * width * 1.5) + width / 2,
				(i / rowSpriteBackPack * width) + width / 2
			);

			j.bgSprite = workSprite;

			// Render item

			if (j.idItem) {

				workItem.GetDataEq(j.idItem);

				j.bgSprite.setTextureRect(j.getQualityBorder(workItem.getQuality()));

				workSprite.setTextureRect(
					sf::IntRect(
						workItem.getTextureRectLeft(),
						workItem.getTextureRectTop(),
						workItem.getTextureRectWidth(),
						workItem.getTextureRectHeight()
					));


				workSprite.setPosition(
					(i % rowSpriteBackPack * width * 1.5) + width / 2,
					(i / rowSpriteBackPack * width) + width / 2
				);

				j.eqSprite = workSprite;
			}
			i++;
		}

		//pointMaxSizeBackpackViewY = backpackMap.back().bgSprite.getPosition().y - backpackView.getSize().y;
		pointMaxSizeBackpackViewY = backpackMap.back().bgSprite.getPosition().y - (backpackMap.front().bgSprite.getPosition().y * 8);
	}
}
