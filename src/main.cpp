#include <iostream>
#include <armadillo>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

std::vector< std::vector<bool> > nextFrame(std::vector< std::vector<bool> > visibile);

using namespace std;

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
			isRectVisible[x][y] = false;
		}
	}
	isRectVisible[6][5] = true;
	isRectVisible[5][5] = true;
	isRectVisible[4][5] = true;
	// isRectVisible[4][4] = true;
	// isRectVisible[5][4] = true;
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
				case sf::Event::MouseButtonReleased:
					if(event.mouseButton.button == sf::Mouse::Left){
						cout << "calculating next frame" << endl;
						isRectVisible = nextFrame(isRectVisible);
					}
				default:
					break;
			}
		}

		window.clear();
		for(int i = 0; i < rects.size(); i++){
			for(int j = 0; j < rects[i].size(); j++){
				if(isRectVisible[i][j])
				{
					window.draw(rects[i][j]);
				}
			}
		}
		window.display();
	}
}

std::vector< std::vector<bool> > nextFrame(std::vector< std::vector<bool> > visibile){
	// skipping the edges
	std::vector< std::vector<bool> > result = visibile;
	for(int i = 1; i < visibile.size()-1; i++){
		for(int j = 1; j < visibile[i].size() - 1; j++){
			int surroundCount = 0;
			for(int dx = -1; dx <= 1; dx++){
				for(int dy = -1; dy <= 1; dy++){
					if(!(dx == 0 && dy == 0)){
						if(visibile[i+dx][j+dy]){
							surroundCount++;
						}
					}
				}
			}
			if(surroundCount == 3){
				result[i][j] = true;
			}
			else{
				if(surroundCount != 2){
					result[i][j] = false;
				}
			}
		}
	}
	return result;
}
