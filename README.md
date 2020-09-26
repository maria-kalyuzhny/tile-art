# TileArt

TileArt is a raster graphics editor for creating tile-based images using a tile set provided by the user. It's perfect for quickly designing tile-based 2D video game levels without the complexity and learning curve required by software like Unity and Unreal Engine, as well as creating pixel art and geometric patterns.

TileArt was built from scratch in C++ using minimal external libraries (SFML and Boost), and designed for an efficient, intuitive, and aesthetically pleasing workflow. 

## Demo

Efficient tile editing tools include draw, fill, and stamp, as well as 'eraser' versions of these tools.
(gif coming soon)


## Usage

(coming soon)
TileArt is currently only available for Windows devices. To install it, simply download and unzip the folder TileArt.zip.

### Running TileArt
From a terminal, navigate to the folder containing TileArt.exe. Ensure that the /img folder is in the same location as the .exe file. 

Run the command
```bash
./TileArt.exe -t <tile_size> -x <width> -y <height> -s <tileset_image> -o <output_image>
```

### Keyboard Shortcuts
Zoom in and out using mouse wheel
Scroll using W,A,S,D

### Tools
Save - saves updated image to the file indicated by the -o flag earlier.
Pencil - draw using a single free form line
Stamp - select a rectangular region from the tile palette, and draw a rectangle on the tile map to fill it with the selected region.
Fill - regular paintbucket fill
Erase - Toggle-able button to allow erasing with each of the three above tools (Pencil, Stamp, and Fill)
Fit Screen - fits both the tile palette and the tile map to screen.

### Default Tilesets
The following default tilesets are included in the /img folder to play around with.
(coming soon)

###Future Scope
-Integrate Windows API to allow saving and loading without using the terminal
-Add layers tool
-Allow save as 2D array for easy integration with game code