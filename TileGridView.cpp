#pragma once
#include "TileGridView.h"

TileGridView::TileGridView(const sf::FloatRect& rect, sf::Vector2f w_size, TileGrid* grid) : 
	GuiElement(rect.left, rect.top, rect.width, rect.height) {
	this->w_size = w_size;
	this->grid = grid;
	this->view = sf::View(sf::FloatRect(0,0,w,h));
	this->view.setViewport(sf::FloatRect(x / w_size.x, y / w_size.y, w / w_size.x, h / w_size.y));
	init_zoom=false;
}

void TileGridView::initZoom(float in_zoom) {
	//set initial zoom to fit the screen and save the original zoom value for future reference
	default_zoom = in_zoom;
	z = in_zoom;
	cout << "init zoom set to" << z << endl;
	init_zoom=true;
}

void TileGridView::reset(const sf::FloatRect& rect) {
	this->x = rect.left; this->y = rect.top;
	this->w = rect.width; this->h = rect.height;
	resize(w, h);
	full_zoom = std::max(grid->w / w, grid->h / h);
	if (!init_zoom) {
		initZoom(full_zoom);
		default_zoom=full_zoom;
		z = full_zoom;
	}
	view.setSize(w*z,h*z);
	//view.move(-w/2 + (w*z)/2,-h/2 + (h*z)/2);
	handleZoom();
}

void TileGridView::resize(float w, float h) {
	view.reset(sf::FloatRect(0, 0, w, h));
	view.setViewport(sf::FloatRect(x / w_size.x, y / w_size.y, w / w_size.x, h / w_size.y));
}

void TileGridView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.setView(view);
	target.draw(*grid);
	//sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(500,250));
	//target.draw(rect);
}

void TileGridView::zoom(int delta) {
	float temp_z;
	if (delta < 0) {
		for (int i = 0; i >= delta; i -= 1) {
			temp_z = z + 0.01;
			if (temp_z <= max_zoom*default_zoom) {
				z = temp_z;
				view.setSize(w * z, h * z);
				handleZoom();
			}
		}
	}
	else if (delta > 0) {
		for (int i = 0; i <= delta; i += 1) {
			temp_z = z - 0.01;
			if (temp_z >= min_zoom*default_zoom) {
				z = temp_z;
				view.setSize(w * z, h * z);
				handleZoom();
			}
		}
	}
}

void TileGridView::handleZoom() {
	cout << "zoom " << z << endl;
	cout << "view width " << w << endl;
	cout << "grid width " << grid->w / z << endl;
	if (w - grid->w / z > 0) {
		view.setCenter(grid->w / 2, view.getCenter().y);
	}
	else {
		view.setCenter(w/2, view.getCenter().y);
		view.move(-w / 2 + (w * z) / 2, 0);
		cout << "moving view x " << -w / 2 + (w * z) / 2 << endl;
	}
	if (h - grid->h / z > 0) {
		view.setCenter(view.getCenter().x, grid->h / 2);
	}
	else {
		view.setCenter(view.getCenter().x, h / 2);
		view.move(0, -h / 2 + (h * z) / 2);
	}
}

void TileGridView::centerOnGrid() {
	cout << "zoom " << z << endl;
	cout << "view width " << w << endl;
	cout << "grid width " << grid->w/z << endl;
	if (w - grid->w/z > 0) {
		view.setCenter(grid->w/2,view.getCenter().y);
	}
	if (h - grid->h/z > 0) {
		view.setCenter(view.getCenter().x, grid->h/2);
	}
}

void TileGridView::fitToScreen() {
	float x_ratio = grid->w/w;
	float y_ratio = grid->h/h;
	z = std::max(x_ratio, y_ratio);
	cout << "init zoom set to" << z << endl;
	view.setSize(w*z,h*z);
}

void TileGridView::updateWindow(sf::Vector2f w_size) {
	this->w_size = w_size;
}