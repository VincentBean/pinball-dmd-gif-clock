#include <list>
#include <iterator>
#include "Globals.h"
#include "components/gif/MatrixGif.hpp"
#include "components/gif/GifLoader.hpp"

#define DEFAULT_GIF "boot.gif"

bool autoPlay = true;
bool allowNextGif = true;

unsigned long gifStart = 0;
int minPlaytime = 2000; // TODO: Make configurable
String current_gif;
int currentGifIndex = 0;

void nextGif()
{
    current_gif = getNextGif();

    gifStart = millis();
    interruptGif = true;
}

void setGif(String gif)
{
    current_gif = gif;
    interruptGif = true;
}

void handleGif()
{
    if (queueEmpty() && !gifPlaying)
    {
        // TODO: Add placeholder GIF
        // ShowGIF(LOGO_GIF, true);
        Serial.println("Queue empty");
        return;
    }

    if (current_gif.length() == 0)
    {
        nextGif();
    }

    while (!current_gif.endsWith(".gif"))
    {
        nextGif();
    }

    allowNextGif = autoPlay && millis() - gifStart > minPlaytime;
    if (!gifPlaying && allowNextGif)
    {
        nextGif();
    }

    char gif[current_gif.length() + 1];
    current_gif.toCharArray(gif, sizeof(gif));

    ShowGIF(gif);
}
