#include "ViewLayout.h"

ViewLayout::ViewLayout(sf::FloatRect rect, sf::Vector2f w_size, TileGridView* picker_view, TileGridView* map_view, float div_x) :
	GuiElement(rect.left, rect.top, rect.width, rect.height) {
	this->div_x = div_x;
	this->w_size = w_size;
	this->picker_view = picker_view;
	this->picker_view->reset(sf::FloatRect(x, y, div_x, h));
	this->map_view = map_view;
	this->map_view->reset(sf::FloatRect(div_x + div_width, y, w - div_x - div_width, h));
	this->divider = sf::RectangleShape(sf::Vector2f(div_width, h));
	this->divider.setPosition(this->div_x, this->y);
	this->divider.setFillColor(this->divider_color);
	this->moving_divider = false;
	this->setOutlines();

}

void ViewLayout::setOutlines() {
	this->picker_outline = sf::RectangleShape(sf::Vector2f(div_x - x, h));
	this->picker_outline.setPosition(x, y);
	this->picker_outline.setFillColor(sf::Color::Transparent); //always transparent since its an outline
	this->picker_outline.setOutlineColor(view_outline_color);
	this->picker_outline.setOutlineThickness(view_outline_thickness);
	this->map_outline = sf::RectangleShape(sf::Vector2f(w - div_x - div_width, h));
	this->map_outline.setPosition(div_x + div_width, y);
	this->map_outline.setFillColor(sf::Color::Transparent); //always transparent since its an outline
	this->map_outline.setOutlineColor(view_outline_color);
	this->map_outline.setOutlineThickness(view_outline_thickness);
}

void ViewLayout::updateWindow(sf::Vector2f w_size) {
	this->w_size = w_size;
	picker_view->updateWindow(w_size);
	map_view->updateWindow(w_size);
}

void ViewLayout::resize(float w, float h) {
	this->w = w;
	this->h = h;
	picker_view->reset(sf::FloatRect(x, y, div_x, h));
	map_view->reset(sf::FloatRect(div_x + div_width, y, w - div_x - div_width, h));
	divider.setSize(sf::Vector2f(div_width, h));
	picker_outline.setSize(sf::Vector2f(div_x, h));
	map_outline.setSize(sf::Vector2f(w - div_x - div_width, h));
}

void ViewLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::View curr_view = target.getView();
	target.draw(*picker_view);
	target.draw(*map_view);
	target.setView(curr_view);
	target.draw(divider);
	target.draw(picker_outline);
	target.draw(map_outline);
}

void ViewLayout::moveDivider(float mouse_x) {
	if (mouse_x > divider_limit && mouse_x < w_size.x - divider_limit) {
		divider.setPosition(mouse_x, y);
		div_x = mouse_x;
		picker_view->reset(sf::FloatRect(x, y, div_x, h));
		map_view->reset(sf::FloatRect(div_x + div_width, y, w - div_x - div_width, h));
		picker_outline.setPosition(x,y);
		picker_outline.setSize(sf::Vector2f(div_x, h));
		map_outline.setPosition(div_x+div_width, y);
		map_outline.setSize(sf::Vector2f(w - div_x - div_width, h));
	}
}