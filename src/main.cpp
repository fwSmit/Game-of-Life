#include <iostream>
#include <armadillo>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

int main()
{
	std::cout << "Opening window" << std::endl;
	sf::RenderWindow window(sf::VideoMode(500, 500), "Game of Life");
	tgui::Gui gui(window);
	tgui::Button::Ptr button;
	arma::fvec2 circlePos {250, 250};
	sf::CircleShape shape(200.f);
	shape.setPointCount(300);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(circlePos[0], circlePos[1]);
	sf::Texture img;
	
	std::vector< std::vector<sf::RectangleShape> > rects;
	std::vector< std::vector<bool> > isRectVisible;
	int n_rects = 10;
	rects.resize(n_rects);
	for(auto& i : rects){
		i.resize(n_rects);
	}
	isRectVisible.resize(n_rects);
	for(auto& i : isRectVisible){
		i.resize(n_rects);
	}
	float rectSize = float( window.sf::Window::getSize().x )/float(n_rects);
	for(int x = 0; x < n_rects; x++){
		for(int y = 0; y < n_rects; y++){
			rects[x][y].setSize(sf::Vector2f(rectSize, rectSize));
			rects[x][y].setPosition(x*rectSize, y*rectSize);
			isRectVisible[x][y] = true;
		}
	}
	if(!img.loadFromFile("resources/background.jpg")){
		// could not load image
		std::cout << "Could not find image" << std::endl;
		return -1;
	}
	shape.setTexture(&img);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type){
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}
		}

		window.clear();
		for(int i = 0; i < rects.size(); i++){
			for(int j = 0; j < rects[i].size(); j++){
				if(isRectVisible[i][j])
				{
					window.draw(rects[i][i]);
				}
			}
		}
		window.display();
	}
}
