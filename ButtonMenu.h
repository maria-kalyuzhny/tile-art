#pragma once

#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include "Button.h"
#include "GuiElement.h"
#include <vector>
using namespace std;

class ButtonMenu : public GuiElement
//displays buttons over a rectangular bar, horizontally with even spacing starting from the left
{
public:
	sf::RectangleShape rect;
	int num_buttons;
	ButtonMenu();
	ButtonMenu(float x, float y, float w, float h);
	void resize(float w, float h);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void addButton(Button* button, bool fit_to_menu = true);
	Button* getButton(string name);
	vector<Button*> buttons;

private:
	float button_size;
	const float padding = 15;
};