#include "settings.h"

const int gameWidth = 320;
const int gameHeight = 320;
const int scale = 4;

const int screenWidth = gameWidth * scale;
const int screenHeight = gameHeight * scale;

const int fps = 60;
void initGame(){
    InitWindow(screenWidth, screenHeight, "Mountain Peaks");
    SetTargetFPS(fps);
    SetExitKey(KEY_NULL);
}