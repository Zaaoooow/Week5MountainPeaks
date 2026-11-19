#include "textures.h"

//define textures
Texture2D menu_background = {};
Texture2D menu_outline = {};
Texture2D menu_title = {};
// menu buttons
Texture2D menu_play_button = {};
Texture2D menu_play_button_hover = {};
Texture2D menu_quit_button = {};
Texture2D menu_quit_button_hover = {};

void loadGameTextures(){
    //load textures
    menu_background = LoadTexture("assets/backgrounds/menu_background.png");
    menu_outline = LoadTexture("assets/menu/menu_outline.png");
    menu_title = LoadTexture("assets/menu/menu_title.png");
    menu_play_button = LoadTexture("assets/menu/menu_play_button.png");
    menu_play_button_hover = LoadTexture("assets/menu/menu_play_button_hover.png");
    menu_quit_button = LoadTexture("assets/menu/menu_quit_button.png");
    menu_quit_button_hover = LoadTexture("assets/menu/menu_quit_button_hover.png");


    //set texture filter
    SetTextureFilter(menu_background, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_outline, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_title, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_play_button, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_play_button_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_quit_button, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_quit_button_hover, TEXTURE_FILTER_POINT);

}

void unloadGameTextures(){
    //unload textures
    UnloadTexture(menu_background);
    UnloadTexture(menu_outline);
    UnloadTexture(menu_title);
    UnloadTexture(menu_play_button);
    UnloadTexture(menu_play_button_hover);
    UnloadTexture(menu_quit_button);
    UnloadTexture(menu_quit_button_hover);
}