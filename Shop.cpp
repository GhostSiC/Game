#include "Shop.h"

Shop::Shop()
{
}

Shop::~Shop()
{
}

void Shop::render(sf::RenderTarget* target)
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

	if (!respNewCharacter)
		boughtButton.render(target);


	//middle
	target->setView(eqView);
	rec.setFillColor(sf::Color(150, 220, 0, 100));
	target->draw(rec);
	for (auto& i : eqItem) {
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

void Shop::engine()
{
	characterOffSetX = 0;

	charaktersSpawnCount = 16;

	for (size_t i = 0; i < charaktersSpawnCount; i++) {
		spriteCharStaticPoz.push_back(sf::Vector2f(250 * i, 200));
	}

	

	if (respNewCharacter) {
	initCharakter();
		respNewCharacter = false;
	}

	initButtons();
}

//fix text "kupiony"
void Shop::poolEvents(Vector2i* poz, sf::RenderTarget* target)
{
	

	auto pozz = Vector2i(target->mapPixelToCoords(*poz, charView));

	if (boughtButton.isClicked(pozz)) {


		for (auto& i : ifBought)
			if (i.second == false) {
				if (i.first == characterPTR->getId()) {

					i.second = true;
					characterPTR->saveCharacterData();
					//saveData();
					boughtTextButton = "Kupiono";
					boughtButton.setText(boughtTextButton);
				}
			}
			else {
				boughtTextButton = "Kupiono";
				boughtButton.setText(boughtTextButton);
			}


		return;
	}


	pozz = Vector2i(target->mapPixelToCoords(*poz, characterView));

	for (auto& i : characters) {
		idClicked = i.getIdByClick(&pozz, target);


		if (idClicked) {
			characterPTR = &i;
			initText();
			initUiSprite();

			initEqItemSprite();

			return;
		}
	}
}

void Shop::poolEventsMoved(Vector2i* poz, sf::RenderTarget* target)
{


	auto pozz = Vector2i(target->mapPixelToCoords(*poz, charView));

	//difference
	if (boughtButton.isClicked(pozz)) {

		for (auto& i : ifBought)
			if (i.first == characterPTR->getId())
				if (i.second == false) {

					boughtCharacterInfoText();


					if (pozz.y - ptrInfoButton->getGlobalBounds().height > 0)
						ptrInfoButton->setPosition(poz->x + ptrInfoButton->getGlobalBounds().width / 2, poz->y - ptrInfoButton->getGlobalBounds().height / 2);
					else
						ptrInfoButton->setPosition(poz->x + ptrInfoButton->getGlobalBounds().width / 2, poz->y + ptrInfoButton->getGlobalBounds().height / 2);

					return;
				}
	}

	pozz = Vector2i(target->mapPixelToCoords(*poz, eqView));
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
	
}

void Shop::initCharakter()
{
	//characters.clear();
	std::srand(time(NULL));

	for (size_t i = 0; i < charaktersSpawnCount; i++)
	{
		//create new empty charakter
		Character wokrCharakters;
		wokrCharakters.setTexture(&avatarTexture);
		wokrCharakters.setPosition(sf::Vector2f(16 + (i * 96), 16));

		wokrCharakters.setId(i + 1);

		wokrCharakters.engine();


		wokrCharakters.respawn();


		characters.push_back(wokrCharakters);
		ifBought[i + 1] = false;
	}
	//pointMaxOffSetCharacterX = characters.back().getPosition().x - characterView.getSize().x;
	pointMaxOffSetCharacterX = (16 + (characters.size() * 96)) - characterView.getSize().x;

	//init first saw character
	characterPTR = &characters.front();
	idClicked = characterPTR->getId();

	if (idClicked) {
		initText();
		initUiSprite();

		initEqItemSprite();

		return;
	}

}

void Shop::initButtons()
{
	boughtButton.set_Id(97);
	boughtButton.set_Name("Bought button");

	boughtButton.setFont(&this->font);
	boughtButton.setFontSize(40);
	boughtButton.setColor(sf::Color(0, 0, 0, 255));

	sf::IntRect intrec = sf::IntRect(128, 128, 32, 32);
	boughtButton.setTexture(&this->texture, intrec);


	boughtTextButton = "kup";
	boughtButton.setText(boughtTextButton);

	boughtButton.setVisible(1);
	boughtButton.setPosition(charView.getCenter().x, 900);

}

void Shop::boughtCharacterInfoText()
{
	std::string descriptionEq;


	goldCost = characterPTR->getCostGold();

	descriptionEq = "Kup: \n";
	descriptionEq += "zloto: " + std::to_string(goldCost) + '\n';


	ptrInfoButton->setText(descriptionEq);
}
