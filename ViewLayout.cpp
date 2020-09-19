#include "ViewLayout.h"

ViewLayout::ViewLayout(sf::FloatRect rect, sf::Vector2f w_size, TileGridView* picker_view, TileGridView* map_view, float div_x) :
	GuiElement(rect.left, rect.top, rect.width, rect.height) {
	this->div_x = div_x;
	this->w_size = w_size;
	this->map_view = map_view;
	this->picker_view = picker_view;
	this->picker_view->reset(sf::FloatRect(x,y,div_x,h));
	this->map_view->reset(sf::FloatRect(div_x+div_width,y,w-div_x-div_width,h));
	this->divider = sf::RectangleShape(sf::Vector2f(div_width, h));
	this->divider.setPosition(this->div_x, this->y);
	this->divider.setFillColor(this->divider_color);
	this->moving_divider = false;
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
}

void ViewLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(divider);
	target.draw(*picker_view);
	target.draw(*map_view);

}

void ViewLayout::moveDivider(float mouse_x) {
	divider.setPosition(mouse_x, y);
	div_x = mouse_x;
	//picker_view.reset(sf::FloatRect(0, 0, div_x, h));
	//picker_view.setViewport(sf::FloatRect(x / window_w, y / window_h,
	//	(div_x) / window_w, h / window_h));
	//picker_view.move(picker_scroll);
	//scrollView("picker", picker_scroll);
	//map_view.reset(sf::FloatRect(0, 0, window_w - div_x + div_width, h));
	//map_view.setViewport(sf::FloatRect((x + div_x + div_width) / window_w, y / window_h,
	//	(w - div_x + div_width) / window_w, h / window_h));
	//map_view.move(map_scroll);
	picker_view->reset(sf::FloatRect(x, y, div_x, h));
	map_view->reset(sf::FloatRect(div_x + div_width, y, w - div_x - div_width, h));
}