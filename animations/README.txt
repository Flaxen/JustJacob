animations and tileLoader
Written by Alexander Carlsson

The custom tile loader is a lot like its mapMaker counterpart in that it loads bitmaps intro arrays
representing pixel on/off statuses for use on the I/O shield display.

This is how to properly use the tileLoader:

DISCLAIMER:
  Unlike its mapMaker counterpart the values for tileLoader image sizes are not hard coded and
  settings for TILE_WIDTH and TILE_HEIGHT can be found in ../settings.h

Go to https://www.dcode.fr/binary-image and upload your TILE_WIDTH x TILE_HEIGHT image.
There are plenty of setting which are summed up below:

  "Width of picture"
    Sets the width of the converted picture.
    This has to be set to the width you want your picture to have. If the image of your choice
    already if of the correct size you can choose "ORIGINAL SIZE".
    If you wish to scale down a rather large picture you can set a "CUSTOM WIDTH". Results for this may vary.

    Use of tiles larger than the screen itself is not recommended and not guaranteed to work.

  "Threshold Black/White"
    This has always been left on 50% for already black and white images. If your image is colored you could
    play around with this value if 50% does not give the expected results.

  "Binary Chars"
    Black and White have to be represented by ones and zeroes. Which represents which, however,
    is determined by if you have your screen values inverted or not. I recommend trying one and
    if it does not give the results expected, try the other one.

    If I recall correctly our screen is not inverted.
    I use "WHITE = 0, BLACK = 1"


After choosing settings you are now ready to hit convert.
Copy the bitmap provided in the results window on the left and copy the contents
into the "tileBinary.txt" file.

With that done however you are ready to open your command line to compile and run the "tileLoader.c" file
using you C compiler. The program will print your converted array contents. Note that these themselves are
arrays.

These contents are now ready to be pasted into a new array in the "customTiles.h" file where there are a couple
of pre-uploaded ones.
