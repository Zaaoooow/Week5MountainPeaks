#pragma once
#include <raylib.h>

//textures
//menu
extern Texture2D menu_background;
extern Texture2D menu_outline;
extern Texture2D menu_title;
extern Texture2D menu_play_button;
extern Texture2D menu_play_button_hover;
extern Texture2D menu_quit_button;
extern Texture2D menu_quit_button_hover;
extern Texture2D menu_guide_button;
extern Texture2D menu_guide_button_hover;
//game
extern Texture2D game_background;
extern Texture2D farmer_down;
extern Texture2D farmer_up;
extern Texture2D farmer_left;
extern Texture2D farmer_right;
extern Texture2D farmer_up_right;
extern Texture2D farmer_up_left;
extern Texture2D farmer_down_left;
extern Texture2D farmer_down_right;
//farm
extern Texture2D dirt_plot;
extern Texture2D dirt_seed;
extern Texture2D dirt_plot_hover;
extern Texture2D seed_button;
extern Texture2D seed_button_hover;
extern Texture2D water_button;
extern Texture2D water_button_hover;
extern Texture2D dirt_seed_hover;
extern Texture2D plant_stage1;
extern Texture2D plant_stage2;
extern Texture2D plant_stage3;
extern Texture2D water_seed1;
extern Texture2D water_seed2;
extern Texture2D harvest_hover;
extern Texture2D crop_display;
extern Texture2D crop_display_hover;
extern Texture2D sell;
extern Texture2D sell_hover;
extern Texture2D coindisplay;
extern Texture2D shop;
extern Texture2D shop_hover;
extern Texture2D shop_page;


void loadGameTextures();
void unloadGameTextures();