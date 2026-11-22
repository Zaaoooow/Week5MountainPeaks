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
Texture2D water_button = {};
Texture2D water_button_hover = {};
Texture2D dirt_seed_hover = {};
Texture2D plant_stage1 = {};
Texture2D plant_stage2 = {};
Texture2D plant_stage3 = {};
Texture2D water_seed1 = {};
Texture2D water_seed2 = {};
Texture2D harvest_hover = {};
Texture2D crop_display = {};
Texture2D crop_display_hover = {};
Texture2D sell = {};
Texture2D sell_hover = {};
Texture2D coindisplay = {};
Texture2D shop = {};
Texture2D shop_hover = {};
Texture2D shop_page = {};
Texture2D peach = {};
Texture2D peach_hover = {};
Texture2D water = {};
Texture2D water_hover = {};
Texture2D guide_page = {};
Texture2D gameover_screen = {};


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
    water_button = LoadTexture("assets/game/water_button.png");
    water_button_hover = LoadTexture("assets/game/water_button_hover.png");
    dirt_seed_hover = LoadTexture("assets/game/dirt_seed_hover.png");
    //plant stages
    water_seed1 = LoadTexture("assets/game/water_seed.png");
    water_seed2 = LoadTexture("assets/game/water_seed2.png");
    plant_stage1 = LoadTexture("assets/game/plant_stage1.png");
    plant_stage2 = LoadTexture("assets/game/plant_stage2.png");
    plant_stage3 = LoadTexture("assets/game/plant_stage3.png");
    harvest_hover = LoadTexture("assets/game/harvest_hover.png");
    crop_display = LoadTexture("assets/game/crop_display.png");
    crop_display_hover = LoadTexture("assets/game/crop_display_hover.png");
    sell = LoadTexture("assets/game/sell.png");
    sell_hover = LoadTexture("assets/game/sell_hover.png");
    coindisplay = LoadTexture("assets/game/coindisplay.png");
    shop = LoadTexture("assets/game/shop.png");
    shop_hover = LoadTexture("assets/game/shop_hover.png");
    shop_page = LoadTexture("assets/game/shop_page.png");
    peach = LoadTexture("assets/game/peach.png");
    peach_hover = LoadTexture("assets/game/peach_hover.png");
    water = LoadTexture("assets/game/water.png");
    water_hover = LoadTexture("assets/game/water_hover.png");
    guide_page = LoadTexture("assets/menu/guide_page.png");
    gameover_screen = LoadTexture("assets/menu/gameover.png");

    

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
    SetTextureFilter(water_button, TEXTURE_FILTER_POINT);
    SetTextureFilter(water_button_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(dirt_seed_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(plant_stage1, TEXTURE_FILTER_POINT);
    SetTextureFilter(plant_stage2, TEXTURE_FILTER_POINT);
    SetTextureFilter(plant_stage3, TEXTURE_FILTER_POINT);
    SetTextureFilter(water_seed1, TEXTURE_FILTER_POINT);
    SetTextureFilter(water_seed2, TEXTURE_FILTER_POINT);
    SetTextureFilter(harvest_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(crop_display, TEXTURE_FILTER_POINT);
    SetTextureFilter(crop_display_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(sell, TEXTURE_FILTER_POINT);
    SetTextureFilter(sell_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(coindisplay, TEXTURE_FILTER_POINT);
    SetTextureFilter(shop, TEXTURE_FILTER_POINT);
    SetTextureFilter(shop_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(shop_page, TEXTURE_FILTER_POINT);
    SetTextureFilter(peach, TEXTURE_FILTER_POINT);
    SetTextureFilter(peach_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(water, TEXTURE_FILTER_POINT);
    SetTextureFilter(water_hover, TEXTURE_FILTER_POINT);
    SetTextureFilter(guide_page, TEXTURE_FILTER_POINT);
    SetTextureFilter(gameover_screen, TEXTURE_FILTER_POINT);


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