# TileArt

TileArt is a Windows-based raster graphics editor for creating tile-based images using a tile set provided by the user. It's perfect for quickly designing tile-based 2D video game levels without the complexity and learning curve required by software like Unity and Unreal Engine, as well as creating pixel art and geometric patterns.

TileArt was built from scratch in C++ using minimal external libraries (SFML and Boost), and designed for an efficient, intuitive, and aesthetically pleasing workflow. 

## Demo

Editing tools include draw, fill, erase, and rectangle, allowing quick and intuitive tilemap creation. 

![Alt Text](https://github.com/maria-kalyuzhny/tile-art/blob/master/media/gif1.gif)
<br/><br/>
<br/><br/>
<br/><br/>
User interface navigation allows zoom, scroll, and resize using mouse wheel and keyboard shortcuts.

![Alt Text](https://github.com/maria-kalyuzhny/tile-art/blob/master/media/gif2.gif)

## Usage
To download TileArt, simply download and unzip the TileArt.zip folder above.

### Running TileArt
Navigate to the unzipped folder containing TileArt.exe from a terminal. This folder includes the executable and an /img folder, which contains required image and font assets.

Run the command
```
./TileArt.exe -t <tile_size> -x <width> -y <height> -s <tileset_image> -o <output_image>
```
Option descriptions:
```
-h, --help
  Print the help message
-t, --tilesize
  Width and height of tiles in pixels
-x, --width
  Width of tile grid (in number of tiles)
-y, --height
  Height of tile grid (in number of tiles)
-s, --tileset
  Path to .png, jpg, or .gif image file to use as tileset.
  Please use an image with a whole number of tiles, i.e. the image
  width and height should be evenly divisible by the tile size.
-o, --output
  REQUIRED. Path to the output image file. Must be an image file in
  .png, .jpg, or .gif format. Your work will write to this file each
  time the save button is pressed.
```

### User interface navigation
Zoom in:	Mouse wheel up

Zoom out:	Mouse wheel down

Scroll:		W,A,S,D

### Tools
Save - saves updated image to the file indicated by the -o flag earlier.

Fit Screen - fits both the tile palette and the tile map to screen.

Pencil - draw using a single free form line

Rectangle - select a rectangular region from the tile palette, and draw a rectangle on the tile map to fill it with the selected region.

Fill - fill an area of uniform tiles with a different tile (regular paintbucket fill)

Erase - toggle eraser (use Pencil and Rectangle buttons for different eraser modes)

### Default Tilesets
The following default tilesets are included in the /img folder:

/img/motherload_tiles.png (tilesize: 64)

/img/cavesofgallet_tiles.png (tilesize: 8)

## Future Scope
Integrate Windows API to allow saving and loading without using the terminal

Add undo

Add layers tool

Add drag tool

Allow save as 2D array for easy integration with game code
