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
Texture2D menu_guide_button = {};
Texture2D menu_guide_button_hover = {};
//game
Texture2D game_background = {};
Texture2D farmer_down = {};
Texture2D farmer_up = {};
Texture2D farmer_left = {};
Texture2D farmer_right = {};
Texture2D farmer_up_right = {};
Texture2D farmer_up_left = {};
Texture2D farmer_down_left = {};
Texture2D farmer_down_right = {};
Texture2D dirt_plot = {};
Texture2D dirt_seed = {};
Texture2D dirt_plot_hover = {}; 
Texture2D seed_button = {};
Texture2D seed_button_hover = {};


void loadGameTextures(){
    //load textures
    //menu
    menu_background = LoadTexture("assets/backgrounds/menu_background.png");
    menu_outline = LoadTexture("assets/menu/menu_outline.png");
    menu_title = LoadTexture("assets/menu/menu_title.png");
    menu_play_button = LoadTexture("assets/menu/menu_play_button.png");
    menu_play_button_hover = LoadTexture("assets/menu/menu_play_button_hover.png");
    menu_quit_button = LoadTexture("assets/menu/menu_quit_button.png");
    menu_quit_button_hover = LoadTexture("assets/menu/menu_quit_button_hover.png");
    menu_guide_button = LoadTexture("assets/menu/menu_guide_button.png");
    menu_guide_button_hover = LoadTexture("assets/menu/menu_guide_button_hover.png");
    //game
    game_background = LoadTexture("assets/backgrounds/game_background.png");
    farmer_down = LoadTexture("assets/game/farmer_down.png");
    farmer_right = LoadTexture("assets/game/farmer_right.png");
    farmer_up = LoadTexture("assets/game/farmer_up.png");
    farmer_left = LoadTexture("assets/game/farmer_left.png");
    farmer_up_right = LoadTexture("assets/game/farmer_up_right.png");
    farmer_up_left = LoadTexture("assets/game/farmer_up_left.png");
    farmer_down_left = LoadTexture("assets/game/farmer_down_left.png");
    farmer_down_right = LoadTexture("assets/game/farmer_down_right.png");
    //farm
    dirt_plot = LoadTexture("assets/game/dirt_plot.png");
    dirt_seed = LoadTexture("assets/game/dirt_seed.png");
    dirt_plot_hover = LoadTexture("assets/game/dirt_plot_hover.png");
    seed_button = LoadTexture("assets/game/seed_button.png");
    seed_button_hover = LoadTexture("assets/game/seed_button_hover.png");
    

    //set texture filter
    //menu
    SetTextureFilter(menu_background, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_outline, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_title, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_play_button, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_play_button_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_quit_button, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_quit_button_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_guide_button, TEXTURE_FILTER_POINT);
    SetTextureFilter(menu_guide_button_hover, TEXTURE_FILTER_POINT);
    //game
    SetTextureFilter(game_background, TEXTURE_FILTER_POINT);
    SetTextureFilter(farmer_down, TEXTURE_FILTER_POINT);
    SetTextureFilter(farmer_up, TEXTURE_FILTER_POINT);
    SetTextureFilter(farmer_left, TEXTURE_FILTER_POINT);
    SetTextureFilter(farmer_right, TEXTURE_FILTER_POINT);
    SetTextureFilter(farmer_up_right, TEXTURE_FILTER_POINT);
    SetTextureFilter(farmer_up_left, TEXTURE_FILTER_POINT);
    SetTextureFilter(farmer_down_left, TEXTURE_FILTER_POINT);
    SetTextureFilter(farmer_down_right, TEXTURE_FILTER_POINT);
    //farm
    SetTextureFilter(dirt_plot, TEXTURE_FILTER_POINT);
    SetTextureFilter(dirt_seed, TEXTURE_FILTER_POINT);
    SetTextureFilter(dirt_plot_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(seed_button, TEXTURE_FILTER_POINT);
    SetTextureFilter(seed_button_hover, TEXTURE_FILTER_POINT);

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
    UnloadTexture(menu_guide_button);
    UnloadTexture(menu_guide_button_hover);
}