#pragma once
#include "TileGridView.h"

TileGridView::TileGridView(const sf::FloatRect& rect, sf::Vector2f w_size, TileGrid* grid) : 
	GuiElement(rect.left, rect.top, rect.width, rect.height) {
	this->w_size = w_size;
	this->grid = grid;
	this->z = 1.0;
	this->max_scroll_x = this->grid->w;
	this->max_scroll_y = this->grid->h;
	this->s = sf::Vector2f(0, 0);
	this->s_delta = 0.01 * w_size.y;
	this->view = sf::View(sf::FloatRect(0,0,w,h));
	this->view.setViewport(sf::FloatRect(x / w_size.x, y / w_size.y, w / w_size.x, h / w_size.y));
	this->centerOnGrid();
}

void TileGridView::reset(const sf::FloatRect& rect) {
	this->x = rect.left; this->y = rect.top;
	this->w = rect.width; this->h = rect.height;
	resize(w, h);
	centerOnGrid();
	view.setSize(w * z, h * z);
	view.move(s);
}

void TileGridView::resize(float w, float h) {
	view.reset(sf::FloatRect(0, 0, w, h));
	view.setViewport(sf::FloatRect(x / w_size.x, y / w_size.y, w / w_size.x, h / w_size.y));
	//centerOnGrid();
}

void TileGridView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.setView(view);
	target.draw(*grid);
}

void TileGridView::zoom(int delta) {
	float temp_z = z - 0.1 * delta;
	if (temp_z <= max_zoom && temp_z >= min_zoom) {
		this->z = temp_z;
		view.setSize(w * z, h * z);
		s_delta = 0.01*w_size.y*z;
	}
}

void TileGridView::scroll(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Key::A) {
		if (s.x + s_delta < max_scroll_x) {
			view.move(s_delta, 0);
			s.x = s.x + s_delta;
		}

	}
	else if (key == sf::Keyboard::Key::D) {
		if (s.x - s_delta > -max_scroll_x) {
			view.move(-s_delta, 0);
			s.x = s.x - s_delta;
		}
	}
	else if (key == sf::Keyboard::Key::W) {
		if (s.y + s_delta < max_scroll_y) {
			view.move(0, s_delta);
			s.y = s.y + s_delta;
		}
	}
	else if (key == sf::Keyboard::Key::S) {
		if (s.y - s_delta > -max_scroll_y) {
			view.move(0, -s_delta);
			s.y = s.y - s_delta;
		}
	}
}

void TileGridView::centerOnGrid() {
	sf::Vector2f center = view.getCenter();
	if (this->w*z > this->grid->w && this->h*z > this->grid->h) {
		view.setCenter(grid->w / 2, grid->h / 2);
	}
	else if (this->w*z > this->grid->w) {
		view.setCenter(grid->w/2, center.y);
	}
	else if (this->h*z > this->grid->h) {
		view.setCenter(center.x, grid->h/2);
	}
}

void TileGridView::updateWindow(sf::Vector2f w_size) {
	this->w_size = w_size;
}