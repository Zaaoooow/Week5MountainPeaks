#pragma once
#include <raylib.h>

//textures
extern Texture2D menu_background;
extern Texture2D menu_outline;
extern Texture2D menu_title;
extern Texture2D menu_play_button;
extern Texture2D menu_play_button_hover;
extern Texture2D menu_quit_button;
extern Texture2D menu_quit_button_hover;

void loadGameTextures();
void unloadGameTextures();