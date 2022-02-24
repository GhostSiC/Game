#include "Game.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initTexture();
	this->initView();


	

	this->setTypeGame();


	this->getData("Main");

	initInfoButton();

	this->Engine();
}

Game::~Game()
{
	delete this->window;
}

void Game::Engine()
{
	while (this->running())
	{
		this->UpdateDt();

		this->Update();

		this->Render();

	}

}

void Game::Render()
{
	this->window->clear(); //Wyczyœci scenê na kolor czarny
	//this->player.render(this->window);



	//this->drawUi();

	this->window->setView(this->view_main_button);
	//this->view_main_button.move(10.f, 0.f);

	//this->ui_game.render(this->window);

	sf::RectangleShape rec;
	rec.setSize(Vector2f(2000, 1500));
	rec.setFillColor(sf::Color(0, 0, 100, 250));
	this->window->draw(rec);


	for (auto &i : this->containerMainButton)
	{
		i.render(this->window);
	}

	this->window->setView(this->gameContenerView);

	
	
	rec.setFillColor(sf::Color(100, 0, 200, 100));
	this->window->draw(rec);

	
	this->window->setView(this->infoSourceView);
	rec.setFillColor(sf::Color(100, 0, 100, 100));
	this->window->draw(rec);

	// render source info
	for (auto& i : sourceInfoText)
		window->draw(i);


	if (this->type_status == 1)
		city.render(this->window);

	if (this->type_status == 2)
		shop.render(this->window);
	
	if (type_status == 4)
		characterDetails.render(this->window);
	


	this->window->setView(this->window->getDefaultView());

	if (infoButton.getVisible())
		infoButton.render(window);

	if(alertButton.getVisible())
		alertButton.render(window);

	this->window->display();
}

void Game::Update()
{
	this->poolEvents();

}

void Game::UpdateDt()
{
	this->dt = this->dtClock.restart().asSeconds();

	this->second += this->dt;

	if (this->second > 1) {

		city.updateSource();

		if (alertButton.getVisible())
			alertButton.update();

		this->second = 0;
	}

	updateInfoText();

	

}

void Game::poolEvents()
{

	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		default:

			break;

		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		case Event::MouseButtonPressed:
			if (this->event.key.code == sf::Mouse::Button::Left) {

				Vector2i poz = sf::Mouse::getPosition(*this->window);
				int flag_click;

				if (this->type_status != 440) {
					for (auto& i : this->containerMainButton) {
						flag_click = i.isClicked(poz);
						if (flag_click && this->type_status != flag_click) {
							this->type_status = flag_click;
							this->setTypeGame();

						}
					}
				}
				
				if (type_status == 1) {
					city.poolEvents(&poz, window);
				}
				
				if (type_status == 2)
					shop.poolEvents(&poz, window);
				
				if (type_status == 4)
					characterDetails.poolEvents(&poz, window);
			}
			break;

		case sf::Event::MouseMoved: {


			Vector2i poz = sf::Mouse::getPosition(*this->window);
			auto pozz = Vector2i(this->window->mapPixelToCoords(poz, this->gameContenerView));

			
			if (this->type_status == 1)
				city.poolEventsMoved(&poz, window);
			if (this->type_status == 2 )
				shop.poolEventsMoved(&poz, window);

			if (this->type_status == 4)
				characterDetails.poolEventsMoved(&poz, window);
		}
		break;
		case sf::Event::MouseWheelScrolled: {
			Vector2i poz = sf::Mouse::getPosition(*this->window);
			if (this->type_status == 2) {
				shop.poolEventsWheel(&poz, window, event.mouseWheelScroll.delta);
			}
			else if (this->type_status == 4) {
				characterDetails.poolEventsWheel(&poz, window, event.mouseWheelScroll.delta);
			}
		}
		break;
		
		}
	}
}

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::initInfoButton()
{
	
	infoButton.set_Id(98);
	infoButton.set_Name("Info Box");

	infoButton.setFont(&this->font);
	infoButton.setFontSize(25);
	infoButton.setColor(sf::Color(0, 0, 0, 255));

	sf::IntRect intrec = sf::IntRect(0, 128, 32, 32);
	infoButton.setTexture(&this->texture, intrec);

	infoButton.setPositionByOrgini(videoMode.width / 2, videoMode.height / 2);

	infoButton.setText("Koszt:\n");
	infoButton.setVisible(0);
	infoButton.setIsAlterButton(0);


	alertButton.set_Id(97);
	alertButton.set_Name("Alert Box");
	
	alertButton.setFont(&this->font);
	alertButton.setFontSize(25);
	alertButton.setColor(sf::Color(0, 0, 0, 255));
	alertButton.setTexture(&this->texture, intrec);

	alertButton.setPositionByOrgini(videoMode.width / 2, videoMode.height / 2);

	alertButton.setText("Nie masz wystrczajacej ilosci surowcow.\nUzupelnij zapasy poprzez wymiane lub wyprawe.");
	alertButton.setVisible(0);
	alertButton.setIsAlterButton(1);
}

void Game::initVariables()
{
	this->window = nullptr;
	MAXSIZEWINDOW = sf::Vector2i(1920, 1080);

	std::srand(time(0));

	

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "nie uda³o sie wczytaæ fonta\n";
	}
	
	this->type_status = 1;

	gold = 0;
	stone = 0;
	wood = 0;
	food = 0;
	sulfur = 0;

	ptrSource.push_back(&gold);
	ptrSource.push_back(&stone);
	ptrSource.push_back(&wood);
	ptrSource.push_back(&food);
	ptrSource.push_back(&sulfur);


	
}

void Game::initWindow()
{
	videoMode = sf::VideoMode(MAXSIZEWINDOW.x, MAXSIZEWINDOW.y);
	window = new RenderWindow(videoMode, "Game", sf::Style::Default);
	window->setFramerateLimit(60);
}



void Game::setTypeGame()
{

	initView();

	switch (this->type_status)
	{
	case 1:
		city.pushSourceValue(&ptrSource);
		city.setTexture(&texture);
		city.setFont(&font);
		city.setViewMax(this->videoMode.width, this->videoMode.height / 10 * 8);

		city.getButtons(&alertButton, &infoButton);
		city.engine();
		break;

	case 2:
		shop.setTexture(&texture);
		shop.setFont(&font);
		shop.setViewMax(this->videoMode.width, this->videoMode.height / 10 * 8);

		shop.engine();
		shop.getButtons(&alertButton, &infoButton);

		break;
	
	case 3:


		break;

	case 4:
		

		characterDetails.setTexture(&texture);
		characterDetails.setFont(&font);
		characterDetails.setViewMax(this->videoMode.width, this->videoMode.height / 10 * 8);

		//characterDetails.resetCharacterOffSetX();
		characterDetails.getButtons(&alertButton, &infoButton);
		characterDetails.engine();

		break;

	default:
		break;
	}

}

void Game::initTexture()
{
	this->texture.loadFromFile("img\\item.png");

}

void Game::initView()
{

	this->view_main_button.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 0.1f));
	this->view_main_button.setSize(sf::Vector2f(videoMode.width, videoMode.height / 10));
	this->view_main_button.setCenter(this->view_main_button.getSize().x / 2, this->view_main_button.getSize().y / 2);

	this->infoSourceView.setViewport(sf::FloatRect(0.f, 0.1f, 1.f, 0.1f));
	this->infoSourceView.setCenter(this->infoSourceView.getSize().x / 2, this->infoSourceView.getSize().y / 2);
	this->infoSourceView.setSize(sf::Vector2f(videoMode.width, videoMode.height / 10));
	
	this->gameContenerView.setViewport(sf::FloatRect(0.f, 0.2f, 1.f, 0.8f));
	this->gameContenerView.setCenter(this->gameContenerView.getSize().x / 2, this->gameContenerView.getSize().y / 2);
	this->gameContenerView.setSize(sf::Vector2f(videoMode.width, videoMode.height / 10 * 9));


}


void Game::updateInfoText()
{
	sourceInfoText.clear();
	sf::Text workTekxt;
	std::string sText;
	
	workTekxt.setFont(font);
	workTekxt.setCharacterSize(24);
	workTekxt.setOrigin(workTekxt.getGlobalBounds().width / 2, workTekxt.getGlobalBounds().height / 2);

	std::string nameSource[5] = { "zloto", "kamien", "drewno", "jedzenie", "siarka" };

	for (size_t i = 0; i < ptrSource.size(); i++)
	{
		//Info text display 
		sText = "Posiadane " + nameSource[i] + ": " + std::to_string(*ptrSource.at(i));
		
		//sText += "\nna sekunde: " + std::to_string(productionBuilding.at(i).updateValue());
		
		workTekxt.setString(sText);
		workTekxt.setPosition(sf::Vector2f((infoSourceView.getSize().x / 5) * i + 50, infoSourceView.getSize().y - videoMode.height / 13));
		sourceInfoText.push_back(workTekxt);
	}
}

void Game::getData(const char* tag)
{
	xml_document doc;

	if (doc.load_file("Button.xml")) {

		Button work_button;

		sf::Vector2f rect_Button;
		sf::IntRect rect_Tex_Button;

		String name;

		xml_node tools = doc.child("Ui").child("Button").child(tag);

		
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
			work_button.setSpriteScale(6, 3.5);

			work_button.setFontSize(25);

			work_button.setPosition(rect_Button.x, rect_Button.y);

			this->containerMainButton.push_back(work_button);
		}
	}
}
