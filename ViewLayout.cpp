#include "ViewLayout.h"

ViewLayout::ViewLayout(float x, float y, float w, float h, float div_pos, float window_w, float window_h) : GuiElement(x,y,w,h) {
	this->div_x = div_pos;
	this->window_w = window_w;
	this->window_h = window_h;
	//Picker and map Views both start the View at upper left corner, with given width and height
	//Moving objects in these Views will be performed through scrolling
	//Picker and map Viewports correspond to areas to the left and right of divider 
	this->picker_view = sf::View(sf::FloatRect(0,0,div_pos,h));
	this->picker_view.setViewport(sf::FloatRect(x/window_w, y/window_h,
		(div_pos)/window_w, h/window_h));
	this->map_view = sf::View(sf::FloatRect(0,0,window_w-div_pos+div_width,h));
	this->map_view.setViewport(sf::FloatRect((x+div_pos+div_width)/window_w, y/window_h,
		(w - div_pos + div_width)/window_w, h/window_h));
	this->map_scroll, this->picker_scroll = sf::Vector2f(0, 0);
	this->divider = sf::RectangleShape(sf::Vector2f(this->div_width, this->h));
	this->divider.setPosition(this->div_x, this->y);
	this->divider.setFillColor(this->divider_color);
	this->moving_divider = false;
	cout << "view layout" << this->x << " " << this->y << " " << this->h << endl;
}

void ViewLayout::updateWindow(float window_w, float window_h) {
	this->window_w = window_w;
	this->window_h = window_h;
}

void ViewLayout::resize(float w, float h) {
	this->w = w;
	this->h = h;
	picker_view.reset(sf::FloatRect(0, 0, div_x, h));
	picker_view.setViewport(sf::FloatRect(x / window_w, y / window_h,
		(div_x) / window_w, h / window_h));
	map_view.reset(sf::FloatRect(0, 0, window_w - div_x + div_width, h));
	map_view.setViewport(sf::FloatRect((x + div_x + div_width) / window_w, y / window_h,
		(w - div_x + div_width) / window_w, h / window_h));
	//picker_view.move(sf::Vector2f(map_scroll_x, map_scroll_y));
	scrollView("picker", picker_scroll);
	divider.setSize(sf::Vector2f(div_width, h));
}

void ViewLayout::scrollView(string view, sf::Vector2f scroll) {
	if (view == "map") {
		map_scroll = scroll;
		map_view.move(scroll);
	}
	else if (view == "picker") {
		picker_scroll = scroll;
		picker_view.move(scroll);
	}
	else {
		cout << "attempting to scroll unknown view" << endl;
	}
}

//void ViewLayout::centerView(string view) {
//	sf::Vector2f scroll;
//	if (view == "map") {
//		//scroll.x = 0 - div_x / 2 + picker->w / 2,
//			//	0 - layout->h / 2 + picker->h / 2 + menu_height/2)
//		map_scroll = scroll;
//		map_view.move(scroll);
//	}
//	else if (view == "picker") {
//		//scroll.x = 0 - div_x / 2 + pickerw / 2,
//		picker_scroll = scroll;
//		picker_view.move(scroll);
//	}
//	else {
//		cout << "attempting to scroll unknown view" << endl;
//	}
//}

void ViewLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(divider);
}

void ViewLayout::moveDivider(float mouse_x) {
	divider.setPosition(mouse_x, y);
	div_x = mouse_x;
	picker_view.reset(sf::FloatRect(0, 0, div_x, h));
	picker_view.setViewport(sf::FloatRect(x / window_w, y / window_h,
		(div_x) / window_w, h / window_h));
	//picker_view.move(picker_scroll);
	scrollView("picker", picker_scroll);
	map_view.reset(sf::FloatRect(0, 0, window_w - div_x + div_width, h));
	map_view.setViewport(sf::FloatRect((x + div_x + div_width) / window_w, y / window_h,
		(w - div_x + div_width) / window_w, h / window_h));
	//map_view.move(map_scroll);
}