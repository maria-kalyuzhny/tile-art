#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#pragma warning(pop)
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <typeinfo>
#include "TileArtGui.h"
#include "GuiElement.h"
#include "ViewLayout.h"
#include "ButtonMenu.h"
#include "Button.h"
#include "TileGrid.h"
#include "TileGridView.h"
namespace po = boost::program_options;
using namespace std;

/*const global variables */
const float init_width = 0.8*sf::VideoMode::getDesktopMode().width;
const float init_height = 0.8*sf::VideoMode::getDesktopMode().height;
const float menu_height = 0.08*init_height;
const float init_divider_pos = 0.3 * init_width;
const int icon_size = 128;
const static int num_buttons = 4;
const static string button_names[num_buttons] = \
{"save", "help", "rectangle", "erase"};
const static string button_icons[num_buttons] = \
{ "./img/save.png", "./img/help.png", "./img/rectangle.png", "./img/erase.png" };
const static string button_descriptions[num_buttons] = \
{ "Save (Ctrl+S)", "Help", "Rectangle", "Eraser" };
//real button list will be
//Save (Ctrl+S) Help(?) Fit Screen (F) Draw (D) Rectangle (R) Bucket Fill (B) Eraser (E)
const static string default_tileset="./img/transparent.png";	

/*global variables*/
int tile_size;
int map_w;
int map_h;
string atlas_file;
string output_file;
sf::Image texture_img;
sf::Texture texture;
sf::Vector2u texture_size;
sf::Texture button_textures[num_buttons];

/*function declarations*/

sf::Texture loadTexture(string file) {
	sf::Texture texture;
	if (!texture.loadFromFile(file))
	{
		std::cerr << "Failed to load texture from file " << file << std::endl;
		exit(1);
	}
	return texture;
}

int parse_args(int argc, char** argv) {
	po::options_description desc("Usage");
	desc.add_options()
		("help,h", "Print help message")
		("tilesize,t", po::value<int>()->default_value(128), "Width and height of tiles in pixels")
		("width,x", po::value<int>()->default_value(15), "Width of tile grid in number of tiles")
		("height,y", po::value<int>()->default_value(12), "Height of tile grid in number of tiles")
		("tileset,s", po::value<string>()->default_value(default_tileset), "Path to .png, "
			".jpg, or .gif image file to use as tileset. "
			"Please use an image with a whole number of tiles, i.e. the image width "
			"and height should be evenly divisible by the tile size.")
		("output,o", po::value<string>(), "REQUIRED. Path to the output file. Must be an image file "
			"in .png, .jpg, or .gif format. Your work will write to this file each "
			"time the save button is pressed.")
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
	tile_size = vm["tilesize"].as<int>();
	map_w = vm["width"].as<int>();
	map_h = vm["height"].as<int>();
	string tileset_file = vm["tileset"].as<string>();
	output_file = vm["output"].as<string>();

	/* notify user what default values are used */
	if (vm["tilesize"].defaulted()) {
		std::cout << "Tile size set to default value " << tile_size << "." << endl;
	}
	else {
		std::cout << "Tile size set to " << tile_size << "." << endl;
	}
	if (vm["width"].defaulted()) {
		std::cout << "Grid width set to default value " << map_w << "." << endl;
	}
	else {
		std::cout << "Grid width set to " << map_w << "." << endl;
	}
	if (vm["height"].defaulted()) {
		std::cout << "Grid height set to default value " << map_h << "." << endl;
	}
	else {
		std::cout << "Grid height set to " << map_h << "." << endl;
	}
	if (vm["tileset"].defaulted()) {
		std::cout << "Tileset set to default tileset " << tileset_file << "." << endl;
	}
	else {
		std::cout << "Tileset set to " << tileset_file << "." << endl;
	}

	/* catch errors related to tile size, width, and height */
	if (tile_size < 1) {
		std::cerr << "Error: Tilesize must be a positive number." << std::endl;
		std::cerr << visible_options << std::endl;
		return 1;
	}
	if (map_w < 1) {
		std::cerr << "Error: Grid width must be a positive number." << std::endl;
		std::cerr << visible_options << std::endl;
		return 1;
	}
	if (map_h < 1) {
		std::cerr << "Error: Grid height must be a positive number." << std::endl;
		std::cerr << visible_options << std::endl;
		return 1;
	}

	/* catch errors related to tileset file */
	if (!boost::algorithm::ends_with(tileset_file, ".png") &&
		!boost::algorithm::ends_with(tileset_file, ".gif") &&
		!boost::algorithm::ends_with(tileset_file, ".jpg")) {
		std::cerr << "Error: Tileset file must be a .png, .gif, or .jpg image file." << std::endl;
		std::cerr << visible_options << std::endl;
		return 1;
	}
	if (!texture_img.loadFromFile(tileset_file)) {
		std::cerr << "Error: The tile atlas image file " << tileset_file << " does not exist." << endl;
		std::cerr << visible_options << std::endl;
		return 1;
	}
	texture_size = texture_img.getSize();
	if (texture_size.x % tile_size != 0 || texture_size.y % tile_size != 0) {
		std::cerr << "Error: The tile atlas image file " << tileset_file << " does not have a "
			"whole number of tiles. The image width and height must be evenly divisible "
			"by the tile size, " << tile_size << "." << endl;
		std::cerr << visible_options << std::endl;
		return 1;
	}
	texture.loadFromImage(texture_img);

	/* catch errors related to output file */
	if (vm.count("output")) {

		if (!boost::algorithm::ends_with(output_file, ".png") &&
			!boost::algorithm::ends_with(output_file, ".gif") &&
			!boost::algorithm::ends_with(output_file, ".jpg")) {
			std::cerr << "Error: output file must be a .png, .gif, or .jpg image file." << std::endl;
			std::cerr << visible_options << std::endl;
			return 1;
		}
		cout << "Output set to "
			<< vm["output"].as<string>() << ".\n";
	}
	else {
		std::cerr << "Error: no output file was provided." << std::endl;
		std::cerr << visible_options << std::endl;
		return 1;
	}
	return 0;
}

int main(int argc, char** argv) {	
	int pa = parse_args(argc, argv);
	if (pa != 0) { return 1; }

	/*Initialize all components of the GUI*/
    
	//Window
	sf::RenderWindow window(sf::VideoMode(init_width,init_height), "Tile Art");
	sf::Vector2f w_size = sf::Vector2f(init_width, init_height);
    
	//Button menu
	ButtonMenu menu = ButtonMenu(0, 0, init_width, menu_height);
	vector <Button> buttons(num_buttons);
	vector <TextBox> descriptions(num_buttons);
	for (int i = 0; i < num_buttons; i += 1) {
		button_textures[i] = loadTexture(button_icons[i]);
		descriptions[i] = TextBox(0, 0, GuiElement::textbox_width,
			GuiElement::text_padding*2+GuiElement::font_size, button_descriptions[i]);
		buttons[i] = Button(0, 0, 0, 0, button_names[i], &button_textures[i]);
		menu.addButton(&buttons[i], true);
		buttons[i].addDescription(&descriptions[i]);
	}
    
	//Views containing tile picker and user-created tilemap
	TileGrid picker = TileGrid(tile_size,static_cast<int>(texture_size.x/tile_size),
		static_cast<int>(texture_size.y/tile_size),&texture);
	TileGrid map = TileGrid(tile_size, map_w, map_h, &texture);   
	TileGridView picker_view = TileGridView(sf::FloatRect(0, 0, 0, 0), w_size, &picker);
	TileGridView map_view = TileGridView(sf::FloatRect(0, 0, 0, 0), w_size, &map);
	sf::FloatRect view_layout_rect = sf::FloatRect(0, menu_height, init_width, init_height - menu_height);
	ViewLayout view_layout = ViewLayout(view_layout_rect, w_size, &picker_view, &map_view, init_divider_pos);
	//Set tile grid in picker to look the same as the original image 
	picker.setTextureRect(sf::Vector2f(0, 0), sf::Vector2f(texture_size.x - tile_size, texture_size.y - tile_size),
		sf::Vector2f(0, 0), sf::Vector2f(texture_size.x - tile_size, texture_size.y - tile_size));

	/*Initialize the GUI and handle input*/
	TileArtGui gui = TileArtGui(&window, &menu, &view_layout, output_file);
	gui.handleInput();
	return 0;
}
