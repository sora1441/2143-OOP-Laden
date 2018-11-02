/*
Brent Laden
Git:sora1441
OOP 2143
A05
11-2-18
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include<cstdlib>

using namespace std;

class Counter{
	sf::Text time;			// contains time variables
	sf::Clock clock;
	sf::Time start;
	sf::Time end;
	sf::Time elapsed;		// time gone by

	int fontSize;
	sf::Font font;			// font of clock
	sf::Color fontColor;    // color of clock

	sf::Vector2f clockLocation;		// location of clock

public:

	//input:	start and ending time
	//purpose:	creates clock
	Counter(int startTime, int endTime){
		fontSize = 50;

		elapsed = clock.getElapsedTime();
		start = sf::seconds(startTime);
		end = sf::seconds(endTime);

		if (!font.loadFromFile("arial.ttf"))
		{
			cout << "Couldn't find your text File";
		}
		time.setFont(font);
		time.setString("0");
		time.setCharacterSize(fontSize);
		time.setFillColor(fontColor.Green);
		time.setPosition(sf::Vector2f(85.f, 65.f));
	}

	//turns int timer to string
	void setTime(int timer){
		string txt = to_string(timer);
		time.setString(txt);
	}

	//input:	sf window
	//purpose:	draws ther counter
	void drawCounter(sf::RenderWindow &window){
		window.draw(time);
	}

	//to close when done
	bool isFinished(int startTime, int endTime){
		elapsed = clock.getElapsedTime();
		if (startTime < endTime){
			if (elapsed.asSeconds() >= endTime + 1)
				return true;
			else
				return false;
		}
		else if (endTime < startTime){
			if (elapsed.asSeconds() <= endTime)
				return true;
			else
				return false;
		}
	}

	//input:	starting and ending time
	//purpose:	whether to count up or down
	void clockDirection(int startTime, int endTime){
		elapsed = clock.getElapsedTime();
		if (startTime < endTime)
			setTime(elapsed.asSeconds());
		else if (startTime > endTime)
			setTime(start.asSeconds() - elapsed.asSeconds()+1);
	}
};


int main(){
	sf::RenderWindow window(sf::VideoMode(200, 200), "");
	
	int start = 0;
	int end = 5;
	
	Counter C1(start,end);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		C1.clockDirection(start, end);
		
		window.clear();
		C1.drawCounter(window);
		window.display();

		if (C1.isFinished(start,end))
			window.close();
	}
	return 0;
}