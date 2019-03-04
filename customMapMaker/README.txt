customMapMaker
Written by Alexander Carlsson

The custom map maker converts bitmaps representing pixel on/off statuses into the compacted
array used for the I/O shield display.

This is how to properly use the customMapMaker:

Go to "https://www.dcode.fr/binary-image" and upload your image. The image has to be the same size
as the screen or scaled to the screen size.
There are plenty of setting which are summed up below:

  "Width of picture"
    Sets the width of the converted picture.
    As you want your picture to remain 128x32(or whatever screen size you have) you want to choose "ORIGINAL SIZE"
    or a "CUSTOM WIDTH" of a value equal to your SCREEN_WIDTH found in settings.h file.

  "Threshold Black/White"
    This has always been left on 50%

  "Binary Chars"
    Black and White have to be represented by zeroes and ones. Which represents which, however,
    is determined by if you have your screen values inverted or not. I recommend trying one and
    if it does not give the results expected, try the other one.

    If I recall correctly our screen is not inverted.
    I use "WHITE = 0, BLACK = 1"


After choosing settings you are now ready to hit convert.
Copy the bitmap provided in the results window on the left and copy the contents
into the "customMap.txt" file.

With that done you are ready to open your command line to compile and run the "customMapTranslator.c" file
using your C compiler. The program will print your converted array contents.

These contents are now ready to be pasted into an array in the "customMaps.c" file where there are a couple
of pre-uploaded ones.

Newly added maps are not automatically added to the menu so you may have to write over the pre-uploaded maps.
