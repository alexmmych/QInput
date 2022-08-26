# QInput
<p align="center">
   <img src="https://github.com/Shroomerian/QInput/blob/main/resources/Markdown/QInput.png">
</p>

## What is it?

QInput is a simple QT application which displays your keyboard input globally. This project was inspired by [GitHub - ThoNohT/NohBoard: A Keyboard Visualizer](https://github.com/ThoNohT/NohBoard) and [GitHub - univrsal/input-overlay: Show keyboard, gamepad and mouse input on stream](https://github.com/univrsal/input-overlay) and it's currently working on **Linux** and **Windows**

## Current State

The current state of the project is in development and it's only in its initial stage. As of current the application needs some tweaking , mouse support and only supports the en-eu layout.

## Installation

```
git clone https://github.com/Shroomerian/QInput.git && cd QInput
mkdir build && cd build  
cmake -S ..
cmake --build . 
```

## Dependencies and usage

This program uses:

- [GitHub - kwhat/libuiohook: A multi-platform C library to provide global keyboard and mouse hooks from userland.](https://github.com/kwhat/libuiohook)

- [MentalCheckpoint's](https://www.youtube.com/c/MentalCheckpoint/videos) [Xelu's FREE Controller Prompts](https://thoseawesomeguys.com/prompts/)

## How to create your own layout?

As of right now layout creation is very limited and not refined but it's still available as an option.

In order to create your own layout you will require:

- GIMP

- All of the keys separated into individual PNG files.

And these are the specific steps you will need to take to import your own layout:

1) Create your own layout by dragging your key PNG files unto the screen. Layer Groups can be used for convenience but the important part is that the individual layers MUST be named exactly the same as the files in question.

2) Install [LayerCoordinates.py](https://github.com/Shroomerian/QInput/blob/main/resources/Layout/LayerCoordinates.py) as a plugin in GIMP, in order to do so you need to find where GIMP stores plugins Edit->Preferences->Folders->Plug-ins and then copy the file into any of those directories. You can also open the python file in any text editor, copy it and paste it into the Filters->Python-Fu->Console.

<p align="center">
   <img src="https://github.com/Shroomerian/QInput/blob/main/resources/Markdown/Plug-in.png">
</p>
   The Python plugin will generate a layer-map.txt file which will be used by the program to set the position of the keys.

3) Import your individual key PNG files into their respective folders (Active and Inactive)

4) Enjoy!
