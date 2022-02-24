#include "Tavern.h"

Tavern::Tavern()
{
	initVarible();

}

Tavern::~Tavern()
{
}

//zrob f() contain

void Tavern::initVarible()
{
	idClicked = 0;
	characterOffSetX = 0;

	initTextureAvatar();
}

void Tavern::poolEventsWheel(Vector2i* poz, sf::RenderTarget* target, float delta)
{

	if (poz->y > (characterView.getViewport().top) * target->getSize().y) {
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

void Tavern::initView()
{

	characterView.setViewport(sf::FloatRect(0.f, 0.9f, 1.f, 1.f));
	characterView.setCenter(characterView.getSize().x / 2, characterView.getSize().y / 2);

	charView.setViewport(sf::FloatRect(0.6f, 0.2f, 0.4f, 0.7f));
	charView.setCenter(charView.getSize().x / 2, charView.getSize().y / 2);

	eqView.setViewport(sf::FloatRect(0.3f, 0.2f, 0.3f, 0.7f));
	eqView.setCenter(eqView.getSize().x / 2, eqView.getSize().y / 2);

}

void Tavern::setViewMax(unsigned int sizeX, unsigned int sizeY)
{
	MAXSIZEVIEW.x = sizeX;
	MAXSIZEVIEW.y = sizeY;

	initView();
}

//fix
void Tavern::setTexture(sf::Texture* texture)
{
	this->texture.loadFromFile("img\\item.png");
}

void Tavern::setFont(sf::Font* font)
{
	this->font = *font;
}

void Tavern::initText()
{

	const short lenght = 11;

	std::string value[lenght];
	sf::Vector2f textPoz[lenght];
	sf::Text workdText;

	text.clear();

	textPoz[0] = sf::Vector2f(350, 20);
	textPoz[1] = sf::Vector2f(550, 20);

	textPoz[2] = sf::Vector2f(100, 200);
	textPoz[3] = sf::Vector2f(400, 200);
	textPoz[4] = sf::Vector2f(600, 200);

	textPoz[5] = sf::Vector2f(100, 400);
	textPoz[6] = sf::Vector2f(400, 400);
	textPoz[7] = sf::Vector2f(600, 400);

	textPoz[8] = sf::Vector2f(100, 600);
	textPoz[9] = sf::Vector2f(400, 600);
	textPoz[10] = sf::Vector2f(600, 600);

	

	value[0] = "Imie: \n" + characterPTR->getName();
	value[1] = "Nazwisko: \n" + characterPTR->getSurname();

	value[2] = "Rzadkosc: \n" + std::to_string(characterPTR->getRare());
	value[3] = "Lvl: \n" + std::to_string(characterPTR->getLvl());
	value[4] = "Zycie: \n" + std::to_string(characterPTR->getMaxHp());

	std::string minMaxAtackString;
	minMaxAtackString = std::to_string(characterPTR->getMinAttack());
	minMaxAtackString += " - ";
	minMaxAtackString += std::to_string(characterPTR->getMaxAttack());

	value[5] = "Atak: \n" + minMaxAtackString;
	value[6] = "Obrona: \n" + std::to_string(characterPTR->getDef());

	value[7] = "Szczescie: \n" + std::to_string(characterPTR->getBaseLuck());
	value[7] += "\nz eq: \n" + std::to_string(characterPTR->getMaxLuck());

	value[8] = "Sila: \npodstawowa:" + std::to_string(characterPTR->getBaseStrength());
	value[8] += "\nz eq:" + std::to_string(characterPTR->getMaxStrength());


	value[9] = "Zwinnosc: \npodstawowa \n" + std::to_string(characterPTR->getBaseDexterity());
	value[9] += "\nz eq: \n" + std::to_string(characterPTR->getMaxDexterity());


	value[10] = "Inteligencja: \npodstawowa: \n" + std::to_string(characterPTR->getBaseIntelligence());
	value[10] += "\nz eq: \n" + std::to_string(characterPTR->getMaxIntelligence());

	workdText.setCharacterSize(32);
	workdText.setFillColor(sf::Color::Red);

	for (int i = 0; i < lenght ; i++) {

		workdText.setFont(font);

		workdText.setPosition(textPoz[i]);

		
		workdText.setString(value[i]);
		text.push_back(workdText);
	}
}

void Tavern::getButtons(Button* btnAlert, Button* btnInfo)
{
	ptrInfoButton = btnInfo;
	ptrAlertButton = btnAlert;
}

void Tavern::initUiSprite()
{
	profile.setTexture(texture);
	profile.setPosition(sf::Vector2f(50,50));
	profile.setTextureRect(sf::IntRect(0,0,32,32));
	profile.setScale(4.f, 4.f);	
}

void Tavern::initTextureAvatar()
{
	avatarTexture.loadFromFile("img\\avatar.png");
}

void Tavern::initEqItemSprite()
{

	eqItem.clear();

	sf::Sprite workSprite;
	workSprite.setTexture(this->texture);
	int idItemOn;

	const int MAXITEMCOUNT = 10;
	std::string mapName[MAXITEMCOUNT] = 
		{"helmet",
		"armor",
		"legs",
		"shoes",
		"gloves",
		"ring_1",
		"ring_2",
		"necklaces",
		"weapon_1",
		"weapon_2"};

	eqItem.resize(MAXITEMCOUNT);

	std::vector<sf::Vector2f> eqPozSprite;


	// 1000 x 1000
	eqPozSprite.push_back(sf::Vector2f(500, 160)); // helmet
	eqPozSprite.push_back(sf::Vector2f(500, 320)); // armor
	eqPozSprite.push_back(sf::Vector2f(500, 480)); // legs
	eqPozSprite.push_back(sf::Vector2f(500, 640)); // shoes
	eqPozSprite.push_back(sf::Vector2f(750, 320)); // gloves

	eqPozSprite.push_back(sf::Vector2f(250, 480)); // ring_1
	eqPozSprite.push_back(sf::Vector2f(750, 480)); // ring_2

	eqPozSprite.push_back(sf::Vector2f(750, 160)); // necklaces

	eqPozSprite.push_back(sf::Vector2f(250, 640)); // weapon_1
	eqPozSprite.push_back(sf::Vector2f(750, 640)); // weapon_2
	
	workSprite.setScale(6.f, 4.f);
	
	int index = 0;
	//Render box sprite
	for (auto& i : eqItem) {

		i.idSLot = index;

		workSprite.setTextureRect(
			sf::IntRect(
				1888,
				768,
				32,
				32
			));

		workSprite.setPosition(
			eqPozSprite.at(index).x - (workSprite.getTextureRect().width / 2) * workSprite.getScale().x,
			eqPozSprite.at(index).y - (workSprite.getTextureRect().height / 2) * workSprite.getScale().y
		);

		i.bgSprite = workSprite;

		idItemOn = characterPTR->getIdItemOn(mapName[index]);

		if(idItemOn != 0){

			Item workItem;
		

			workItem.GetDataEq(idItemOn);

			i.bgSprite.setTextureRect(i.getQualityBorder(workItem.getQuality()));

			workSprite.setTextureRect(
				sf::IntRect(
					workItem.getTextureRectLeft(),
					workItem.getTextureRectTop(),
					workItem.getTextureRectWidth(),
					workItem.getTextureRectHeight()
				));


			workSprite.setPosition(
				eqPozSprite.at(index).x - (workSprite.getTextureRect().width / 2.f) * workSprite.getScale().x,
				eqPozSprite.at(index).y - (workSprite.getTextureRect().height / 2.f) * workSprite.getScale().y
			);

			//eqItem.push_back(workSprite);
			i.idItem = workItem.getId();
			i.eqSprite = workSprite;
		}
		index++;
	}
}

void Tavern::reloadCharacterDisplay()
{
	initEqItemSprite();
	initText();
}

//if 0 mb dont show
void Tavern::setInfoEqText(int id)
{
	if (!id) return;

	Item workItem;
	workItem.GetDataEq(id);

	std::string descriptionEq;

	descriptionEq += workItem.getName();
	descriptionEq += " +" + std::to_string(workItem.getUpgrade()) + '\n';

	descriptionEq += "Jakosc: ";

	switch (workItem.getQuality())
	{
	case 1:
		descriptionEq += "Zwykla\n";
		break;
	
	case 2:
		descriptionEq += "Rzadka\n";
		break;
	
	case 3:
		descriptionEq += "Unikatowy\n";
		break;
	
	case 4:
		descriptionEq += "Legendarny\n";
		break;
	
	case 5:
		descriptionEq += "Mityczny\n";
		break;

	default:
		break;
	}

	

	if (workItem.getMinDMG() != 0 && workItem.getMaxDMG() != 0) {
		descriptionEq += "Obrazenia: \n";
		descriptionEq += std::to_string(workItem.getMinDMG()) + " - ";
		descriptionEq += std::to_string(workItem.getMaxDMG()) + '\n';
	}

	if(workItem.getBaseArmor() != 0)
		descriptionEq += "Szansa na blok: " + std::to_string(workItem.getBaseArmor()) + '\n';
	
	if(workItem.getBaseArmor() != 0)
		descriptionEq += "Pancerz: " + std::to_string(workItem.getBaseArmor()) + '\n';

	if (workItem.getHp() != 0)
		descriptionEq += "Zycie: " + std::to_string(workItem.getHp()) + '\n';
	if (workItem.getMana() != 0)
		descriptionEq += "Mana: " + std::to_string(workItem.getMana()) + '\n';

	if (workItem.getStatStrength() != 0)
		descriptionEq += "Sila: " + std::to_string(workItem.getStatStrength()) + '\n';
	if (workItem.getStatDexterity() != 0)
		descriptionEq += "Zwinnosc: " + std::to_string(workItem.getStatDexterity()) + '\n';
	if (workItem.getStatIntelligence() != 0)
		descriptionEq += "Inteligencja: " + std::to_string(workItem.getStatIntelligence()) + '\n';

	if (workItem.getLuck() != 0)
		descriptionEq += "Szczescie: " + std::to_string(workItem.getLuck()) + '\n';
	if (workItem.getCrit() != 0)
		descriptionEq += "Crit: " + std::to_string(workItem.getCrit()) + '\n';

	descriptionEq += "Potrzebne statystyki: \n";
	if (workItem.getRequireLvl() != 0)
		descriptionEq += "\tLvl: " + std::to_string(workItem.getRequireLvl()) + '\n';
	if (workItem.getRequireStrength() != 0)
		descriptionEq += "\tSila: " + std::to_string(workItem.getRequireStrength()) + '\n';
	if (workItem.getRequireDexterity() != 0)
		descriptionEq += "\tZwinnosc: " + std::to_string(workItem.getRequireDexterity()) + '\n';
	if (workItem.getRequireIntelligence() != 0)
		descriptionEq += "\tInteligencja: " + std::to_string(workItem.getRequireIntelligence()) + '\n';

	ptrInfoButton->setText(descriptionEq);
}
