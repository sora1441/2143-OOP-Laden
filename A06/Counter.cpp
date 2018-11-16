/*
Brent Laden
Git:sora1441
OOP 2143
A06
11-2-18
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include<cstdlib>

using namespace std;

class Counter {
	sf::Text time;			// contains time variables
	sf::Clock clock;
	sf::Time elapsed;		// time gone by
	sf::Time start;
	sf::Time end;

	int fontSize;
	sf::Font font;			// font of clock
	sf::Color fontColor;   		// color of clock

	sf::Vector2f clockLocation;	// location of clock

	sf::Color backgroundColor;      // background rectangle color
	sf::RectangleShape counterBackground; 

public:

	//input:	start and ending time
	//purpose:	creates clock
	Counter(int startTime, int endTime) {
		fontSize = 50;

		elapsed = clock.getElapsedTime();
		start = sf::seconds(startTime);
		end = sf::seconds(endTime);

		if (!font.loadFromFile("arial.ttf"))
		{
			cout << "Couldn't find your text File";
		}

		counterBackground.setSize(sf::Vector2f(100.f, 100.f));
		counterBackground.setFillColor(backgroundColor.White);
		time.setFont(font);
		time.setString("0");
		time.setCharacterSize(fontSize);
		time.setFillColor(fontColor.Green);
		time.setPosition(sf::Vector2f(300.f, 300.f));
		changeClockPosition(300.0, 300.0);  //calls function to center clock
	}
	//input:	number for the clock to start at
	//purpose:	turns int timer  to string
	void setTime(int timer) {
		string txt = to_string(timer);
		time.setString(txt);
	}

	//input:	sf window
	//purpose:	draws the counter and background
	void drawCounter(sf::RenderWindow &window) {
		window.draw(counterBackground);
		window.draw(time);
		
	}

	//to close when done
	bool isFinished(int startTime, int endTime) {
		elapsed = clock.getElapsedTime();
		if (startTime < endTime) {
			if (elapsed.asSeconds() >= endTime + 1)
				return true;
			else
				return false;
		}
		else if (endTime < startTime) {
			if (elapsed.asSeconds() <= endTime)
				return true;
			else
				return false;
		}
	}

	//input:	starting and ending time
	//purpose:	whether to count up or down
	void clockDirection(int startTime, int endTime) {
		elapsed = clock.getElapsedTime();
		if (startTime < endTime)
			setTime(elapsed.asSeconds());
		else if (startTime > endTime)
			setTime(start.asSeconds() - elapsed.asSeconds() + 1);
	//input:	color
	//purpose:	changes color of font
	void changeFontColor(sf::Color color) {

		time.setFillColor(color);

	}
	//input:	size number
	//purpose:	change size of text
	void changeFontSize(int size) {

		time.setCharacterSize(size);

	}
	//input:	color name
	//purpose:	changes color of background rectangle
	void changeBackgroundColor(sf::Color color) {

		counterRectangle.setFillColor(color);

	}
	//input:	color name
	//purpose:	changes the border color of background rectanglw
	void changeBorderColor(sf::Color color) {

		counterRectangle.setOutlineColor(color);

	}
	//input:	x position and y position
	//purpose:	change location of clock
	void changeClockPosition(float X, float Y) {
		time.setPosition(sf::Vector2f(X, Y));
		counterBackground.setPosition(sf::Vector2f(X, Y));
	}
	//input: nothing
	//purpose: moves clock and background
	void moveClock() {
		elapsed = clock.getElapsedTime();
		int e = elapsed.asSeconds();


		if (e <= 1) {
			time.move(0.4f, 0.4f);
			counterBackground.move(0.4f, 0.4f);
		}
		else if (e > 1 && e <= 5) {
			time.move(-0.4f, -0.4f);
			counterBackground.move(-0.4f, -0.4f);
		}
		else if (e > 5) {
			time.move(0.4f, 0.2f);
			counterBackground.move(0.4f, 0.2f);
		}
	}
};


int main() {
	sf::RenderWindow window(sf::VideoMode(900, 900), "");

	int start = 0;
	int end = 5;

	Counter C1(start, end);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		C1.clockDirection(start, end);
		C1.moveClock();

		window.clear();
		C1.drawCounter(window);
		window.display();

		if (C1.isFinished(start, end))
			window.close();
	}
	return 0;
}
