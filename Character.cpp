#include "Character.h"

Character::Character()
{

}

Character::~Character()
{

}

void Character::renderAvatar(sf::RenderTarget* target)
{
	target->draw(avatarProfile);
}

void Character::engine()
{
	initVarible();

	

	//getData();



}

//Item class
void Character::respawn()
{

	initName();
	initBasicValue();

	//helmet.GetDataEq("1");

	//armor.GetDataEq("101");

	//legs.GetDataEq("101");

	//shoes.GetDataEq("101");

	//gloves.GetDataEq("101");

	//ring doesnt spawn with char
	//ring.GetDataEq("armor", "101");
	
	// TODO
	//sword.GetDataEq("armor", "101");


}

void Character::statsUpdate()
{

	// Odpala sie 3 razy

	//ptrItem not working

	maxStrength = BaseStrength +
		helmet.getStatStrength() +
		armor.getStatStrength() +
		legs.getStatStrength() +
		shoes.getStatStrength() +
		gloves.getStatStrength() +
		ring_1.getStatStrength() +
		ring_2.getStatStrength() +
		necklaces.getStatStrength() + 
		weapon_1.getStatStrength() +
		weapon_2.getStatStrength();
	
	maxDexterity = BaseDexterity +
		helmet.getStatDexterity() +
		armor.getStatDexterity() +
		legs.getStatDexterity() +
		shoes.getStatDexterity() +
		gloves.getStatDexterity() +
		ring_1.getStatDexterity() +
		ring_2.getStatDexterity() +
		necklaces.getStatDexterity() +
		weapon_1.getStatDexterity() +
		weapon_2.getStatDexterity();
	
	maxIntelligence = BaseIntelligence +
		helmet.getStatIntelligence() +
		armor.getStatIntelligence() +
		legs.getStatIntelligence() +
		shoes.getStatIntelligence() +
		gloves.getStatIntelligence() +
		ring_1.getStatIntelligence() +
		ring_2.getStatIntelligence() +
		necklaces.getStatIntelligence() +
		weapon_1.getStatIntelligence() +
		weapon_2.getStatIntelligence();


	maxHp = hp +
		helmet.getHp() +
		armor.getHp() +
		legs.getHp() +
		shoes.getHp() +
		gloves.getHp() +
		ring_1.getHp() +
		ring_2.getHp() +
		necklaces.getHp() +
		weapon_1.getHp() +
		weapon_2.getHp();
	
	maxLuck = BaseLuck +
		helmet.getLuck() +
		armor.getLuck() +
		legs.getLuck() +
		shoes.getLuck() +
		gloves.getLuck() +
		ring_1.getLuck() +
		ring_2.getLuck() +
		necklaces.getLuck() +
		weapon_1.getLuck() +
		weapon_2.getLuck();
	
	maxCrit = BaseCrit +
		helmet.getCrit() +
		armor.getCrit() +
		legs.getCrit() +
		shoes.getCrit() +
		gloves.getCrit() +
		ring_1.getCrit() +
		ring_2.getCrit() +
		necklaces.getCrit() +
		weapon_1.getCrit() +
		weapon_2.getCrit();

	minAttack = ((lvl * 2) + (maxStrength / 2 + maxDexterity / 3)) + weapon_1.getMinDMG() + weapon_2.getMinDMG();
	maxAttack = ((lvl * 2) + (maxStrength + maxDexterity / 3)) + weapon_1.getMaxDMG() + weapon_2.getMaxDMG();

}

//make database change 
std::string Character::takeoff(int idItem, int idSlot)
{

	
	returnFirstEmptySlot(idItem);
	
	Item nullItem;

	nullItem.GetDataEq(0);

	switch (idSlot)
	{
	case 0:
		helmet = nullItem;
		break;
	case 1:
		armor = nullItem;
		break;
	case 2:
		legs = nullItem;
		break;
	case 3:
		shoes = nullItem;
		break;
	case 4:
		gloves = nullItem;
		break;
	case 5:
		ring_1 = nullItem;
		break;
	case 6:
		ring_2 = nullItem;
		break;
	case 7:
		necklaces = nullItem;
		break;
	case 8:
		weapon_1 = nullItem;
		break;
	case 9:
		weapon_2 = nullItem;
		break;
	default:
		break;
	}

	dataCharacterUpdateStats();

	return "";
}

//check if is the same item
std::string Character::puton(int idItem)
{
	Item item, itemNull;

	item.GetDataEq(idItem);
	itemNull.GetDataEq(0);


	if (BaseStrength < item.getRequireStrength())
		return "Za malo bazowej sily!";
	else if (BaseDexterity < item.getRequireDexterity())
		return "Za malo bazowej zwinnosci!";
	else if (BaseIntelligence < item.getRequireIntelligence())
		return "Za malo bazowej inteligencji!";


	switch (item.getType())
	{
	case 1:
		helmet = item;
		break;
	case 2:
		armor = item;
		break;
	case 3:
		legs = item;
		break;
	case 4:
		shoes = item;
		break;
	case 5:
		gloves = item;
		break;
	case 6:

		if (ring_2.getId() == 0) 
			ring_2 = item;
		else 
			ring_1 = item;
		
		break;

	case 7:
		necklaces = item;
		break;

	case 8:
		weapon_1 = item;
		break;

	case 9:
		weapon_1 = item;
		weapon_2 = itemNull;
		break;

	case 10:

		if (weapon_2.getId() == 0) 
			weapon_2 = item;
		else 
			weapon_1 = item;
		
		break;

	case 11:
		weapon_2 = item;
		break;

	case 12:
		weapon_1 = item;
		break;

	case 13:
		weapon_1 = item;
		weapon_2 = itemNull;
		break;

	case 14:
		weapon_2 = item;
		break;
	default:
		break;
	}


	statsUpdate();
	return "";
}

std::string Character::getName()
{
	return name;
}

std::string Character::getSurname()
{
	return surname;
}

unsigned short Character::getId()
{
	return id;
}

unsigned short Character::getLvl()
{
	return lvl;
}

unsigned short Character::getRare()
{
	return rare;
}

unsigned int Character::getMaxHp()
{
	return maxHp;
}

unsigned int Character::getMinAttack()
{
	return minAttack;
}

unsigned int Character::getMaxAttack()
{
	return maxAttack;
}

unsigned int Character::getDef()
{
	return def;
}

//TODO
unsigned int Character::getBaseStrength()
{
	return BaseStrength;
}

unsigned int Character::getBaseDexterity()
{
	return BaseDexterity;
}

unsigned int Character::getBaseIntelligence()
{
	return BaseIntelligence;
}

unsigned int Character::getBaseLuck()
{
	return BaseLuck;
}

unsigned int Character::getMaxStrength()
{
	return maxStrength;
}

unsigned int Character::getMaxDexterity()
{
	return maxDexterity;
}

unsigned int Character::getMaxIntelligence()
{
	return maxIntelligence;
}

unsigned int Character::getMaxLuck()
{
	return maxLuck;
}

int Character::getCostGold()
{
	return costGold;
}

int Character::getIdSprite()
{
	return pozSprite;
}

Character Character::getData(int id)
{
	pugi::xml_document doc;

	if (doc.load_file("Character.xml")) {

		pugi::xml_node tools = doc.child("Character");

		if (!tools.empty()) {

			int characterHaveCount = 0;
			std::string idXML, nameXML;

			for (pugi::xml_node_iterator it = tools.begin(); it != tools.end(); ++it)
			{
				for (pugi::xml_attribute_iterator ait = it->attributes_begin(); ait != it->attributes_end(); ++ait) {

					idXML = ait->value();

					if (id == std::stoi(idXML)) {
						this->id = id;

						for (pugi::xml_node& value : *it) {

							nameXML = value.name();

							if (nameXML == "name")
								name = value.child_value();
							else if (nameXML == "surname") {
								surname = value.child_value();
							}
							else if (nameXML == "lvl")
								lvl = std::stoi(value.child_value());
							else if (nameXML == "rare")
								rare = std::stoi(value.child_value());

							else if (nameXML == "hp")
								hp = std::stoi(value.child_value());
							else if (nameXML == "currentyHp")
								currentyHp = std::stoi(value.child_value());
							else if (nameXML == "def")
								def = std::stoi(value.child_value());

							else if (nameXML == "BaseStrength")
								BaseStrength = std::stoi(value.child_value());
							else if (nameXML == "BaseDexterity")
								BaseDexterity = std::stoi(value.child_value());
							else if (nameXML == "BaseIntelligence")
								BaseIntelligence = std::stoi(value.child_value());
							else if (nameXML == "BaseLuck")
								BaseLuck = std::stoi(value.child_value());
							else if (nameXML == "BaseCrit")
								BaseCrit = std::stoi(value.child_value());

							else if (nameXML == "eq") {
								for (pugi::xml_node& eq : value)
									puton(std::stoi(eq.child_value()));
							}
							else if (nameXML == "sprite") {
								pozSprite = std::stoi(value.child_value());
							}
						}
					}
				}
			}
		}
	}
	return *this;
}

bool Character::saveCharacterData()
{
	pugi::xml_document doc;

	if (!doc.load_file("Character.xml")) return false;


	pugi::xml_node root = doc.child("Character");


	pugi::xml_node count = root.first_child();
	std::string idLastCount = count.child_value();
	int countLastInt = (idLastCount == "") ? -1 : std::stoi(idLastCount);
	countLastInt++;

	//count.set_value(std::to_string(idLastInt).c_str());

	count.first_child().set_value(std::to_string(countLastInt).c_str());

	//std::cout << count.child_value();

	int lastId = 0;

	for (pugi::xml_node_iterator it = root.begin(); it != root.end(); ++it)
	{
		for (pugi::xml_attribute_iterator rt = it->attributes().begin(); rt != it->attributes().end(); ++rt) {
			std::string nameXML = rt->name();

			if (nameXML == "id")
				lastId = std::atoi(rt->value());
		}
	}
	lastId++;

	pugi::xml_node node = root.append_child("Meta");


	node.append_attribute("id") = std::to_string(lastId).c_str();

	pugi::xml_node subNode = node.append_child("name");

	std::string stringValue = name;
	const char* valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);


	subNode = node.append_child("surname");

	stringValue = surname;
	valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);


	subNode = node.append_child("lvl");

	int intValue = lvl;
	stringValue = std::to_string(intValue);
	valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);



	subNode = node.append_child("rare");

	intValue = rare;
	stringValue = std::to_string(intValue);
	valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);
	
	subNode = node.append_child("hp");
	subNode.append_child(pugi::node_pcdata).set_value(std::to_string(hp).c_str());
	
	subNode = node.append_child("currentyHp");
	subNode.append_child(pugi::node_pcdata).set_value(std::to_string(currentyHp).c_str());


	subNode = node.append_child("def");

	intValue = def;
	stringValue = std::to_string(intValue);
	valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);

	subNode = node.append_child("BaseStrength");

	intValue = BaseStrength;
	stringValue = std::to_string(intValue);
	valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);

	subNode = node.append_child("BaseDexterity");

	intValue = BaseDexterity;
	stringValue = std::to_string(intValue);
	valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);

	subNode = node.append_child("BaseIntelligence");

	intValue = BaseIntelligence;
	stringValue = std::to_string(intValue);
	valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);

	subNode = node.append_child("BaseLuck");

	intValue = BaseLuck;
	stringValue = std::to_string(intValue);
	valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);
	
	subNode = node.append_child("BaseCrit");

	intValue = BaseCrit;
	stringValue = std::to_string(intValue);
	valueChar = stringValue.c_str();
	subNode.append_child(pugi::node_pcdata).set_value(valueChar);

	int idItemOn;
	const int MAXITEMCOUNT = 10;
	std::string mapName[MAXITEMCOUNT] =
	{ "helmet",
	"armor",
	"legs",
	"shoes",
	"gloves",
	"ring_1",
	"ring_2",
	"necklaces",
	"weapon_1",
	"weapon_2" };

	pugi::xml_node eq = node.append_child("eq");

	for (size_t i = 0; i < MAXITEMCOUNT; i++) {

		pugi::xml_node item = eq.append_child(mapName[i].c_str());

		idItemOn = getIdItemOn(mapName[i]);
		item.append_child(pugi::node_pcdata).set_value(std::to_string(idItemOn).c_str());
	}


	subNode = node.append_child("sprite");

	intValue = pozSprite;
	stringValue = std::to_string(intValue);
	valueChar = stringValue.c_str();

	subNode.append_child(pugi::node_pcdata).set_value(valueChar);

	doc.save_file("Character.xml");

	
	return true;
}

//zamaiana itemów miedzy postaci¹ a plecakiem
std::string Character::changeCharacterData(int idItem, int idSlot)
{
	Item item, itemNull;

	item.GetDataEq(idItem);
	itemNull.GetDataEq(0);

	if (BaseStrength < item.getRequireStrength())
		return "Za malo bazowej sily!";
	else if (BaseDexterity < item.getRequireDexterity())
		return "Za malo bazowej zwinnosci!";
	else if (BaseIntelligence < item.getRequireIntelligence())
		return "Za malo bazowej inteligencji!";
	
	std::cout << "weapon_1.getIsTwoHand(): " << weapon_1.getIsTwoHand() << '\n';
	std::cout << "item.getId(): " << item.getType() << '\n';

	if (weapon_1.getIsTwoHand())
		if (item.getType() == 10 || item.getType() == 11 || item.getType() == 14)
			return "Nie mozesz miec broni dwurecznej i pomocniczej!";

	pugi::xml_document doc;

	pugi::xml_node root;

	pugi::xml_node node;

	int idItemTakeOff = 0;
	int idItemTakeOffSecond = 0;

	switch (item.getType())
	{
	case 1:
		idItemTakeOff = helmet.getId();
		helmet = item;
		break;
	case 2:
		idItemTakeOff = armor.getId();
		armor = item;
		break;
	case 3:
		idItemTakeOff = legs.getId();
		legs = item;
		break;
	case 4:
		idItemTakeOff = shoes.getId();
		shoes = item;
		break;
	case 5:
		idItemTakeOff = gloves.getId();
		gloves = item;
		break;
	case 6:

		if (ring_2.getId() == 0) {
			idItemTakeOff = ring_2.getId();
			ring_2 = item;
		}
		else {
			idItemTakeOff = ring_1.getId();
			ring_1 = item;
		}
		break;
	case 7:
		idItemTakeOff = necklaces.getId();
		necklaces = item;
		break;
	
	case 8:
		idItemTakeOff = weapon_1.getId();
		weapon_1 = item;
		break;

	case 9:
		idItemTakeOff = weapon_1.getId();
		idItemTakeOffSecond = weapon_2.getId();
		weapon_1 = item;
		weapon_2 = itemNull;
		break;

	case 10:

		if (weapon_2.getId() == 0) {
			idItemTakeOff = weapon_2.getId();
			weapon_2 = item;
		}
		else {
			idItemTakeOff = weapon_1.getId();
			weapon_1 = item;
		}
		break;

	case 11:
		idItemTakeOff = weapon_2.getId();
		weapon_2 = item;
		break;

	case 12:
		idItemTakeOff = weapon_1.getId();
		weapon_1 = item;
		break;

	case 13:
		idItemTakeOff = weapon_1.getId();
		idItemTakeOffSecond = weapon_2.getId();
		weapon_1 = item;
		weapon_2 = itemNull;
		break;

	case 14:
		idItemTakeOff = weapon_2.getId();
		weapon_2 = item;
		break;

	default:
		break;
	}

	dataCharacterUpdateStats();
	
	if (!doc.load_file("Backpack.xml")) return "Nie udalo sie zaladowac Backpack.xml";

	pugi::xml_node tools = doc.child("Backpack");
	std::string nameXML;

	if (!tools.empty()) {

		for (pugi::xml_node_iterator it = tools.begin(); it != tools.end(); ++it){
			nameXML = it->name();
			if (nameXML == "Slot") {

				for (pugi::xml_attribute_iterator rt = it->attributes_begin(); rt != it->attributes_end(); ++rt) {
					nameXML = rt->name();

					if (nameXML == "idSlot")
						if (std::stoi(rt->value()) == idSlot) 
							node = *it;
						
				}
			}
		}
	}

	for (pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it)
	{

		nameXML = it->name();
		if (nameXML == "idItem")
			it->first_child().set_value(std::to_string(idItemTakeOff).c_str());

	}
	
	doc.save_file("Backpack.xml");

	returnFirstEmptySlot(idItemTakeOffSecond); //dsa

	statsUpdate();
	return "";
}

//ptrItem dont work
int Character::getIdItemOn(std::string nameSlot)
{

	if(nameSlot == "helmet")
		return helmet.getId();

	else if (nameSlot == "armor")
		return armor.getId();

	else if (nameSlot == "legs")
		return legs.getId();

	else if (nameSlot == "shoes")
		return shoes.getId();

	else if (nameSlot == "gloves")
		return gloves.getId();

	else if (nameSlot == "ring_1")
		return ring_1.getId();
	else if (nameSlot == "ring_2") 
		return ring_2.getId();
	

	else if (nameSlot == "necklaces")
		return necklaces.getId();

	else if (nameSlot == "weapon_1")
		return weapon_1.getId();
	else if (nameSlot == "weapon_2")
		return weapon_2.getId();


	return 0;
}


void Character::initVarible()
{
	dictonaryIdItem[0] = "Null";
	dictonaryIdItem[1] = "helmet";
	dictonaryIdItem[2] = "armor";
	dictonaryIdItem[3] = "legs";
	dictonaryIdItem[4] = "shoes";
	dictonaryIdItem[5] = "gloves";
	dictonaryIdItem[6] = "ring";
	dictonaryIdItem[7] = "sword"; 


	/*helmetId = 0;
	armorId = 0;
	legsId = 0;
	shoesId = 0;
	glovesId = 0;
	ringId = 0;
	swordId = 0;*/

	/*ptrItem.push_back(&helmet);
	ptrItem.push_back(&armor);
	ptrItem.push_back(&legs);
	ptrItem.push_back(&shoes);
	ptrItem.push_back(&gloves);*/


	//ptrItem.push_back(&ring);
	//ptrItem.push_back(&sword);


}

void Character::initName()
{
	const char* name[6] = {
		"madara",
		"tobi",
		"nagato",
		"pain",
		"kakashi",
		"danzou"
	};
	
	const char* surname[6] = {
		"Sarutobi",
		"Yamanaka",
		"Uchiha",
		"Hatake",
		"Tsurugi",
		"Namikaze"
	};

	this->name = name[std::rand() % 6];
	this->surname = surname[std::rand() % 6];
}

void Character::initBasicValue()
{
	
	//skalowanie z tawerna lub ratuszem
	rare = 1;

	//id avatar
	pozSprite = std::rand() % 12;
	avatarProfile.setTextureRect(sf::IntRect((pozSprite % 5) * 32, int(pozSprite / 5) * 32, 32, 32));

	lvl = 1;

	// 100 - 120
	hp = lvl * 100 + (std::rand() % 20);


	// 2 - 5
	def = (lvl * 2) + (std::rand() % 5);

	// luck
	// 0 - 50
	BaseLuck = (lvl * 5) + (std::rand() % 30);

	costGold = rare * 10 + (std::rand() % 100);

	BaseStrength = std::rand() % 10;
	BaseDexterity = std::rand() % 10;
	BaseIntelligence = std::rand() % 10;
	//podstawowy item



	//howManyIntem = std::rand() % 5;
	howManyIntem = 5;

	std::vector<int> idItemRandCat;

	for (size_t i = 0; i < 5; i++) 
		idItemRandCat.push_back(i);

	std::random_shuffle(idItemRandCat.begin(), idItemRandCat.end());


	
	for (int i = 0; i < howManyIntem; i++) {
		switch (idItemRandCat.at(i))
		{
		case 0:
			puton(std::rand() % 3);
			break;
		case 1:
			puton((std::rand() % 3) + 100);
			break;
		case 2:
			puton((std::rand() % 3) + 200);
			break;
		case 3:
			puton((std::rand() % 3) + 300);
			break;
		case 4:
			puton((std::rand() % 3) + 400);
			break;
		default:
			break;
		}
	}

	// 5 - 10
	minAttack = (lvl * 2) + (maxStrength / 2 + maxDexterity / 3);
	maxAttack = (lvl * 2) + (maxStrength + maxDexterity / 3);

	//ringSecondSlotIsFree = true;

	/*
	
	std::cout << "helmetId: " << helmetId << '\n';
	std::cout << "armorId: " << armorId << '\n';
	std::cout << "legsId: " << legsId << '\n';
	std::cout << "shoesId: " << shoesId << '\n';
	std::cout << "glovesId: " << glovesId << '\n';

	
	
		rand 5
		if helmet
			int helmet = rand % 3
		else if 
			int legs = rand % 3

		random how much item
		random cat item 
		loop if much_item
			get 1 id from cat
			get different cat
	



	//TODO
	std::cout << "   |   \n";
	std::vector<int> idItemRandId, idItemRandCat, idItem;
	howManyIntem = std::rand() % 5;

	std::cout << "howManyIntem: " << howManyIntem << '\n';


	//get Cat

	for (size_t i = 0; i < 5; i++) {
		idItemRandCat.push_back(i);

	}


	//Get first value, its id
	for (size_t i = 1; i < 3; i++) {
		idItemRandId.push_back(i);
	}

	std::random_shuffle(idItemRandCat.begin(), idItemRandCat.end());
	std::random_shuffle(idItemRandId.begin(), idItemRandId.end());
	
	for (size_t i = 0; i < howManyIntem; i++) {
		//idItem.push_back(idItemRand.at(i));
		//std::cout << idItem.at(i) << '\n';
		std::cout << idItemRandCat.at(i) << '\n';
		std::cout << idItemRandId.at(0) << '\n';
		std::random_shuffle(idItemRandId.begin(), idItemRandId.end());
	}
	*/
}

std::string Character::dataCharacterUpdateStats()
{
	pugi::xml_document doc;

	if (!doc.load_file("Character.xml"))  return "Nie udalo sie zaladowac Character.xml";


	pugi::xml_node root = doc.child("Character");

	pugi::xml_node node;

	for (pugi::xml_node_iterator it = root.begin(); it != root.end(); ++it)
	{
		for (pugi::xml_attribute_iterator rt = it->attributes().begin(); rt != it->attributes().end(); ++rt) {

			std::string nameXML = rt->name();

			if (nameXML == "id") {
				if (rt->as_int() == id) {
					node = *it;

				}
			}
		}
	}

	for (pugi::xml_node_iterator it = node.begin(); it != node.end(); ++it)
	{
		std::string nameXML = it->name();

		if (nameXML == "name")
			it->first_child().set_value(name.c_str());
		else if (nameXML == "surname")
			it->first_child().set_value(surname.c_str());
		else if (nameXML == "lvl")
			it->first_child().set_value(std::to_string(lvl).c_str());
		else if (nameXML == "rare")
			it->first_child().set_value(std::to_string(rare).c_str());
		else if (nameXML == "hp")
			it->first_child().set_value(std::to_string(hp).c_str());
		else if (nameXML == "currentyHp")
			it->first_child().set_value(std::to_string(currentyHp).c_str());
		else if (nameXML == "def")
			it->first_child().set_value(std::to_string(def).c_str());
		else if (nameXML == "BaseStrength")
			it->first_child().set_value(std::to_string(BaseStrength).c_str());
		else if (nameXML == "BaseDexterity")
			it->first_child().set_value(std::to_string(BaseDexterity).c_str());
		else if (nameXML == "BaseIntelligence")
			it->first_child().set_value(std::to_string(BaseIntelligence).c_str());
		else if (nameXML == "BaseLuck")
			it->first_child().set_value(std::to_string(BaseLuck).c_str());
		else if (nameXML == "BaseCrit")
			it->first_child().set_value(std::to_string(BaseCrit).c_str());
		else if (nameXML == "eq") {
			for (pugi::xml_node_iterator rt = it->begin(); rt != it->end(); ++rt) {
				nameXML = rt->name();
				if (nameXML == "helmet")
					rt->first_child().set_value(std::to_string(helmet.getId()).c_str());
				else if (nameXML == "armor")
					rt->first_child().set_value(std::to_string(armor.getId()).c_str());
				else if (nameXML == "legs")
					rt->first_child().set_value(std::to_string(legs.getId()).c_str());
				else if (nameXML == "shoes")
					rt->first_child().set_value(std::to_string(shoes.getId()).c_str());
				else if (nameXML == "gloves")
					rt->first_child().set_value(std::to_string(gloves.getId()).c_str());
				else if (nameXML == "ring_1")
					rt->first_child().set_value(std::to_string(ring_1.getId()).c_str());
				else if (nameXML == "ring_2")
					rt->first_child().set_value(std::to_string(ring_2.getId()).c_str());
				else if (nameXML == "necklaces")
					rt->first_child().set_value(std::to_string(necklaces.getId()).c_str());
				else if (nameXML == "weapon_1")
					rt->first_child().set_value(std::to_string(weapon_1.getId()).c_str());
				else if (nameXML == "weapon_2")
					rt->first_child().set_value(std::to_string(weapon_2.getId()).c_str());
			}
		}
	}

	doc.save_file("Character.xml");


	statsUpdate();
	return "";
}

std::string Character::returnFirstEmptySlot(int idItem)
{

	pugi::xml_document doc;

	if (!doc.load_file("Backpack.xml")) return "Nie udalo sie zaladowac Backpack.xml";

	pugi::xml_node tools = doc.child("Backpack");

	if (tools.empty()) return "Plik jest pusty";

	std::string nameXML;

	[&, idItem]{
		for (pugi::xml_node_iterator it = tools.begin(); it != tools.end(); ++it) {
			nameXML = it->name();
			if (nameXML == "Slot") {

				for (pugi::xml_node_iterator data = it->begin(); data != it->end(); ++data) {
					nameXML = data->name();
					if (nameXML == "idItem") {
						if (std::stoi(data->child_value()) == 0) {

							for (pugi::xml_node_iterator rt = data->begin(); rt != data->end(); ++rt) {
								rt->set_value(std::to_string(idItem).c_str());
								std::cout << "idItem: " << idItem << '\n';
								return "";
							}
						}
					}
				}
			}
		}
		return "Nie masz miejsca w plecaku";
	}();

	doc.save_file("Backpack.xml");

	return "";
}

void Character::setTexture(sf::Texture* tex)
{

	

	avatarProfile.setTexture(*tex);

	avatarProfile.setTextureRect(sf::IntRect((pozSprite % 5) * 32, int(pozSprite / 5) * 32, 32, 32));

	avatarProfile.setScale(2,2);

}

int Character::getIdByClick(sf::Vector2i* poz, sf::RenderTarget* target)
{

	if(avatarProfile.getGlobalBounds().contains(poz->x, poz->y))
		return id;
	return 0;
}

void Character::setPosition(sf::Vector2f poz)
{
	avatarProfile.setPosition(poz);
}

sf::Vector2f Character::getPosition()
{
	return avatarProfile.getPosition();
}

void Character::setId(int id)
{
	this->id = id;
}
