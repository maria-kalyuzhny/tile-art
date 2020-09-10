#include "TileGridView.h"

TileGridView::TileGridView(const sf::FloatRect& rect, sf::Vector2f w_size, TileGrid* grid) : 
	GuiElement(rect.left, rect.top, rect.width, rect.height) {
	this->w_size = w_size;
	this->grid = grid;
	this->view = sf::View(sf::FloatRect(0,0,w,h));
	this->view.setViewport(sf::FloatRect(x / w_size.x, y / w_size.y, w / w_size.x, h / w_size.y));
	this->centerOnElement();
}

void TileGridView::reset(const sf::FloatRect& rect) {
	this->x = rect.left; this->y = rect.top;
	this->w = rect.width; this->h = rect.height;
	resize(w, h);
	cout << "view rect set to " << view.getSize().x << ", " << view.getSize().y << endl;
	cout << "viewport set to " << view.getViewport().width*w_size.x << ", " << view.getViewport().height* w_size.y << endl;
}

void TileGridView::resize(float w, float h) {
	view.reset(sf::FloatRect(0, 0, w, h));
	view.setViewport(sf::FloatRect(x / w_size.x, y / w_size.y, w / w_size.x, h / w_size.y));
	centerOnElement();
}

void TileGridView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.setView(view);
	target.draw(*grid);
}

void TileGridView::centerOnElement() {
	sf::Vector2f center = view.getCenter();
	if (this->w > this->grid->w && this->h > this->grid->h) {
		view.setCenter(grid->w / 2, grid->h / 2);
		cout << "center set to " << grid->w / 2 << ", " << grid->h / 2 << endl;
	}
	else if (this->w > this->grid->w) {
		view.setCenter(grid->w/2, center.y);
	}
	else if (this->h > this->grid->h) {
		view.setCenter(center.x, grid->h/2);
	}
}

void TileGridView::updateWindow(sf::Vector2f w_size) {
	this->w_size = w_size;
}