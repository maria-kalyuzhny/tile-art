#pragma warning(push, 0)
#include <SFML/Graphics.hpp>
#pragma warning(pop)
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include "TileEditorGui.h"
#include "GuiElement.h"
#include "ViewLayout.h"
#include "ButtonMenu.h"
#include "Button.h"
#include "TileGrid.h"

using namespace std;

const float init_width = 0.8*sf::VideoMode::getDesktopMode().width;
const float init_height = 0.8*sf::VideoMode::getDesktopMode().height;
const float menu_height = 0.08*init_height;
const float init_divider_pos = 0.3 * init_width;
//const float divider_width = 0.005 * init_width;
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

int main() {
    sf::Image texture_img;
    string t_file = "./img/transparent.png";
    if (!texture_img.loadFromFile(t_file)) {
        cout << "Failed to load image";
        return -1;
    }

    sf::Vector2u size = texture_img.getSize();

    sf::Texture texture;
    texture.loadFromImage(texture_img);
    //sf::Vector2i tex_coors = sf::Vector2i(0, 0);



    sf::RenderWindow window(sf::VideoMode(init_width,init_height), "TileMapEditor");
    ButtonMenu menu = ButtonMenu(0, 0, init_width, menu_height);
    vector <Button> buttons(num_buttons);
    ViewLayout view_layout = ViewLayout(0,menu_height,init_width,init_height-menu_height,init_divider_pos,init_width,init_height);
    TileGrid picker = TileGrid(tile_size,static_cast<int>(size.x/tile_size), static_cast<int>(size.y/tile_size),&texture);
    //set tile grid in picker to look the same as the original image 
    picker.setTextureRect(0,0,size.x-tile_size,size.y-tile_size,0,0, size.x, size.y);
    TileGrid map = TileGrid(tile_size, map_w_tiles, map_h_tiles, &texture);    

    for (int i = 0; i < num_buttons; i += 1) {
        button_textures[i] = loadTexture(button_icons[i]);
        buttons[i] = Button(10, 10, 10, 10, button_names[i], &button_textures[i]);
        menu.addButton(&buttons[i], true);
    }
    //gui.addElement(&menu);
    TileEditorGui gui = TileEditorGui(&window, &menu, &view_layout, &picker, &map);
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