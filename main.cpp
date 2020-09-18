#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <iostream>
//#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <typeinfo>
#include <boost/program_options.hpp>
#include "TileArtGui.h"
#include "GuiElement.h"
#include "ViewLayout.h"
#include "ButtonMenu.h"
#include "Button.h"
#include "TileGrid.h"
#include "TileGridView.h"

namespace po = boost::program_options;
using namespace std;

const float init_width = 0.8*sf::VideoMode::getDesktopMode().width;
const float init_height = 0.8*sf::VideoMode::getDesktopMode().height;
const float menu_height = 0.08*init_height;
const float init_divider_pos = 0.3 * init_width;
const float divider_width = 0.005 * init_width;
const int icon_size = 128;
const int tile_size = 128;
const int map_w_tiles = 16;
const int map_h_tiles = 10;

//string texture_files[2] = { "texture1.jpg","texture2.jpg" };
const static int num_buttons = 8;
const static string button_names[num_buttons] = \
{"load","save","save_as","help","draw","rect","del","clear"};
const static string button_icons[num_buttons] = \
{ "./img/load.png","./img/save.png","./img/save_as.png","./img/help.png",
    "./img/draw.png","./img/rect.png","./img/del.png","./img/clear.png" };
sf::Texture button_textures[num_buttons];

sf::Texture loadTexture(string file);

int main(int argc, char** argv) {	
	po::options_description desc("Usage");
	desc.add_options()
		("help,h", "Produce help message")
		("tilesize,t", po::value<int>()->default_value(64), "Width and height of tiles in pixels")
		("width,w", po::value<int>()->default_value(15), "Width of tile grid in number of tiles")
		("height,h", po::value<int>()->default_value(12), "Height of tile grid in number of tiles")
		("image,i", po::value<string>()->default_value("./img/transparent.png"), "Path to image file to use as tile atlas. "
			"Please use an image with a whole number of tiles, i.e. the image width "
			"and height should be evenly divisible by the tile size.")
		("output,o", po::value<string>()->default_value("/c/Users/Maria/Desktop/test1.png"), "Path to the output file. Must be an image file "
			"in .png, .jpg, or .gif format. The tile grid will be saved to this file each "
			"time save is pressed.")
		;
	po::options_description visible_options;
	visible_options.add(desc);
	po::variables_map vm;
	try {
		po::store(po::parse_command_line(argc, argv, desc), vm);
	}
	catch (const po::error& e) {
		std::cerr << "Error: ";
		std::cerr << e.what() << '\n';
		std::cerr << visible_options << '\n';
		return 1;
	}
	po::notify(vm);
	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}
	if (vm.count("output")) {
		string value = vm["output"].as<string>();
		cout << "Output was set to "
			<< vm["output"].as<string>() << ".\n";
	}
	else {
		cout << "Error: please specify an output file." << endl;
		return 1;
	}
	if (vm.count("tilesize")) {
		int value = vm["tilesize"].as<int>();
		cout << "Tilesize was set to "
			<< vm["tilesize"].as<int>() << ".\n";
	}
	else {
			cout << "Tilesize was not set." << endl;
		}
	if (vm.count("width")) {
		int value = vm["width"].as<int>();
		cout << "Width was set to "
			<< vm["width"].as<int>() << ".\n";
	}
	else {
		cout << "Width was not set." << endl;
	}
	if (vm.count("Height")) {
		int value = vm["height"].as<int>();
		cout << "Height was set to "
			<< vm["height"].as<int>() << ".\n";
	}
	else {
		cout << "Height was not set." << endl;
	}
	if (vm.count("image")) {
		string value = vm["image"].as<string>();
		cout << "Image was set to "
			<< vm["image"].as<string>() << ".\n";
	}
	else {
		cout << "Image was not set." << endl;
	}



	sf::Image texture_img;
	string t_file = "./img/transparent.png";
	if (!texture_img.loadFromFile(t_file)) {
		cout << "Failed to load image";
		return -1;
	}

	sf::Vector2u size = texture_img.getSize();

	sf::Texture texture;
	texture.loadFromImage(texture_img);

	/*Initialize all components of the GUI*/
    
	//Window
	sf::RenderWindow window(sf::VideoMode(init_width,init_height), "Tile Art");
	sf::Vector2f w_size = sf::Vector2f(init_width, init_height);
    
	//Button menu
	ButtonMenu menu = ButtonMenu(0, 0, init_width, menu_height);
	vector <Button> buttons(num_buttons);
	for (int i = 0; i < num_buttons; i += 1) {
		button_textures[i] = loadTexture(button_icons[i]);
		buttons[i] = Button(10, 10, 10, 10, button_names[i], &button_textures[i]);
		menu.addButton(&buttons[i], true);
	}
    
	//Views containing tile picker and user-created tilemap
	TileGrid picker = TileGrid(tile_size,static_cast<int>(size.x/tile_size), static_cast<int>(size.y/tile_size),&texture);
	TileGrid map = TileGrid(tile_size, map_w_tiles, map_h_tiles, &texture);   
	TileGridView picker_view = TileGridView(sf::FloatRect(0, 0, 0, 0), w_size, &picker);
	TileGridView map_view = TileGridView(sf::FloatRect(0, 0, 0, 0), w_size, &map);
	sf::FloatRect view_layout_rect = sf::FloatRect(0, menu_height, init_width, init_height - menu_height);
	ViewLayout view_layout = ViewLayout(view_layout_rect, w_size, &picker_view, &map_view, init_divider_pos);
	//Set tile grid in picker to look the same as the original image 
	picker.setTextureRect(sf::Vector2f(0, 0), sf::Vector2f(size.x - tile_size, size.y - tile_size),
		sf::Vector2f(0, 0), sf::Vector2f(size.x - tile_size, size.y - tile_size));

	/*Initialize the GUI and handle input*/
	TileArtGui gui = TileArtGui(&window, &menu, &view_layout);
	gui.handleInput();
	return 0;
}

sf::Texture loadTexture(string file) {
    sf::Texture texture;
    if (!texture.loadFromFile(file))
    {
        cout << "Failed to load texture\n";
        exit(1);
    }
    return texture;
}