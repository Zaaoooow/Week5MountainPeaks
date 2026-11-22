#include <raylib.h>
#include "settings.h"
#include "textures.h"
#include <cmath>

int main(){
    initGame();
    loadGameTextures();

    enum class screen {
        menu,
        guide,
        screen2,
        fourth
    };

    bool running = true;

    screen currentscreen = screen::menu;

    //player variables
    Vector2 playerPos = {600, 600};
    float playerSpeed = 3.0f;
    Texture2D currentfarmer = farmer_down;

    //farm variables
    const int plotSize = 64 * 4;
    const int gap = 8 * 4;
    const int gridSize = 3 * plotSize + 2 * gap;
    const int startX = (screenWidth - gridSize) / 2;
    const int startY = (screenHeight - gridSize) / 2 + 160;

    int farm[3][3] = {};
    int seedcount = 2;
    bool showseedcount = false;

    int watercount = 2;
    bool showwatercount = false;

    // plant stage growth atnimations made by me (: i love it
    double growthtimers[3][3] = {};
    const double growthduration = 3.0;

    //harvest
    int cropcount = 0;


    while(!WindowShouldClose() && running){
        Vector2 cursor = GetMousePosition();
        BeginDrawing();

        if(currentscreen == screen::menu){
            //collision booleans
            bool playBool = CheckCollisionPointRec(cursor, {400, 576, 480, 108});
            bool quitBool = CheckCollisionPointRec(cursor, {400, 880, 480, 108});
            bool guideBool = CheckCollisionPointRec(cursor, {400, 728, 480, 108});

            ClearBackground(WHITE);

            DrawTextureEx(menu_background, {0, 0}, 0, 4.0f, WHITE);
            DrawTextureEx(menu_outline, {0, 0}, 0, 4.0f, WHITE);
            DrawTextureEx(menu_title, {0, 0}, 0, 4.0f, WHITE);
            
            // if play is hovered or not
            if(playBool){
                DrawTextureEx(menu_play_button_hover, {0, 0}, 0, 4.0f, WHITE);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currentscreen = screen::screen2;
                }
            }
            else{
                DrawTextureEx(menu_play_button, {0, 0}, 0, 4.0f, WHITE);
            }

            //if quit is hovered or not
            if(quitBool){
                DrawTextureEx(menu_quit_button_hover, {0, 0}, 0, 4.0f, WHITE);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    running = false;
                }
            }
            else{
                DrawTextureEx(menu_quit_button, {0, 0}, 0, 4.0f, WHITE);
            }

            //if guide is hovered or not
            if(guideBool){
                DrawTextureEx(menu_guide_button_hover, {0, 0}, 0, 4.0f, WHITE);
            }
            else{
                DrawTextureEx(menu_guide_button, {0, 0}, 0, 4.0f, WHITE);
            }

        }
        else if(currentscreen == screen::screen2){
            ClearBackground(WHITE);
            DrawTextureEx(game_background, {0, 0}, 0, 4.0f, WHITE);

            //seed inventory button
            Rectangle seedbuttonhitbox = {
                28,
                28, 
                72,
                72
            };

            if(CheckCollisionPointRec(cursor, seedbuttonhitbox)){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    showseedcount = !showseedcount;

                    if(showseedcount){
                        showwatercount = false;
                    }
                }
            }

            // water inventory button
            Rectangle waterbuttonhitbox = {
                28, 
                108,
                72,
                72
            };

            if(CheckCollisionPointRec(cursor, waterbuttonhitbox)){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    showwatercount = !showwatercount;

                    if(showwatercount){
                        showseedcount = false;
                    }
                }
            }
            
            //player movement
            if(IsKeyDown(KEY_W)){
                playerPos.y -=playerSpeed;
                currentfarmer = farmer_up;
            }
            if(IsKeyDown(KEY_S)){
                playerPos.y +=playerSpeed;
                currentfarmer = farmer_down;
            }
            if(IsKeyDown(KEY_A)){
                playerPos.x -=playerSpeed;
                currentfarmer = farmer_left;
            }
            if(IsKeyDown(KEY_D)){
                playerPos.x +=playerSpeed;
                currentfarmer = farmer_right;
            }
            if(IsKeyDown(KEY_W) && IsKeyDown(KEY_D)){
                currentfarmer = farmer_up_right;
            }
            if(IsKeyDown(KEY_W) && IsKeyDown(KEY_A)){
                currentfarmer = farmer_up_left;
            }
            if(IsKeyDown(KEY_S) && IsKeyDown(KEY_D)){
                currentfarmer = farmer_down_right;
            }
            if(IsKeyDown(KEY_S) && IsKeyDown(KEY_A)){
                currentfarmer = farmer_down_left;
            }
            
            Rectangle playerhitbox = {
                playerPos.x,
                playerPos.y,
                (float)currentfarmer.width * scale,
                (float)currentfarmer.height * scale
            };
            // select closest dirt plot
            int selectedRow = -1;
            int selectedCol = -1;

            float closestdistance = 999999.0f;

            Vector2 playercenter = {
                playerhitbox.x + playerhitbox.width / 2,
                playerhitbox.y + playerhitbox.height / 2
            };

            //farm hitbox
            for(int row = 0; row < 3; row++){
                for(int col = 0; col < 3; col++){
                    int x = startX + col * (plotSize + gap);
                    int y = startY + row * (plotSize + gap);

                    Rectangle plothitbox = {
                        (float)x,
                        (float)y,
                        (float)plotSize,
                        (float)plotSize
                    };

                    if(CheckCollisionRecs(playerhitbox, plothitbox)){
                        float centerX = x + plotSize / 2.0f;
                        float centerY = y + plotSize / 2.0f;
                        float dx = playercenter.x - centerX;
                        float dy = playercenter.y - centerY;

                        float distance = dx * dx + dy * dy;

                        if(distance < closestdistance){
                            closestdistance = distance;
                            selectedRow = row;
                            selectedCol = col;
                        }
                    }
                }
            }

            //plant seed in selected plot
            if(selectedRow != -1 && IsKeyPressed(KEY_E) && showseedcount){
                if(farm[selectedRow][selectedCol] == 0 && seedcount > 0){
                    farm[selectedRow][selectedCol] = 1;
                    seedcount--;
                }
            }
            //water planted seed
            if(selectedRow != -1 && IsKeyPressed(KEY_E) && showwatercount){
                if(farm[selectedRow][selectedCol] == 1 && watercount > 0){
                    farm[selectedRow][selectedCol] = 2;
                    growthtimers[selectedRow][selectedCol] = GetTime();
                    watercount--;
                }
            }
            //harvest full grown peach tree
            if(selectedRow != -1 && IsKeyPressed(KEY_E) && !showseedcount && !showwatercount){
                if(farm[selectedRow][selectedCol] == 6){
                    farm[selectedRow][selectedCol] = 0;
                    cropcount += 4;
                    growthtimers[selectedRow][selectedCol] = 0;
                }
            }

            //automatic plant growth after watering
            for(int row = 0; row < 3; row++){
                for(int col = 0; col < 3; col++){
                    if(farm[row][col] >= 2 && farm[row][col] < 6){
                        if(GetTime() - growthtimers[row][col] >= growthduration){
                            farm[row][col]++;
                            growthtimers[row][col] = GetTime();
                        }
                    }
                }
            }
            
            //farm
            for(int row = 0; row < 3; row++){
                for(int col = 0; col < 3; col++){
                    int x =  startX + col * (plotSize + gap);
                    int y =  startY + row * (plotSize + gap);
                    
                    if(farm[row][col] == 0){
                        if(row == selectedRow && col == selectedCol){
                            DrawTextureEx(dirt_plot_hover, {(float)x, (float)y}, 0, scale, WHITE);
                        }
                        else{
                            DrawTextureEx(dirt_plot, {(float)x, (float)y}, 0, scale, WHITE);
                        }
                    }
                    else if(farm[row][col] == 1){
                        if(row == selectedRow && col == selectedCol && showwatercount){
                            DrawTextureEx(dirt_seed_hover, {(float)x, (float)y}, 0, scale, WHITE);
                        }
                        else{
                            DrawTextureEx(dirt_seed, {(float)x, (float)y}, 0, scale, WHITE);
                        }
                    }
                    else if(farm[row][col] == 2){
                        DrawTextureEx(water_seed1, {(float)x, (float)y}, 0, scale, WHITE);
                    }
                    else if(farm[row][col] == 3){
                        DrawTextureEx(water_seed2, {(float)x, (float)y}, 0, scale, WHITE);
                    }
                    else if(farm[row][col] == 4){
                        DrawTextureEx(plant_stage1, {(float)x, (float)y}, 0, scale, WHITE);
                    }
                    else if(farm[row][col] == 5){
                        DrawTextureEx(plant_stage2, {(float)x, (float)y}, 0, scale, WHITE);
                    }
                    else if(farm[row][col] == 6){
                        if(row == selectedRow && col == selectedCol){
                            DrawTextureEx(harvest_hover, {(float)x, (float)y - 33.0f * 4}, 0, scale, WHITE);
                        }
                        else{
                            DrawTextureEx(plant_stage3, {(float)x, (float)y - 33.0f * 4}, 0, scale, WHITE);
                        }
                    }
                }
            }
            // draw farmer
            DrawTextureEx(currentfarmer, playerPos, 0, 4.0f, WHITE);
            //draw seed button
            if(CheckCollisionPointRec(cursor, seedbuttonhitbox) || showseedcount){
                DrawTextureEx(seed_button_hover, {0, 0}, 0, scale, WHITE);
            }
            else{
                DrawTextureEx(seed_button, {0, 0}, 0, scale, WHITE);
            }
            //show seed count when clicked
            if(showseedcount){
                DrawText(TextFormat("Seeds: %d", seedcount), 110, 50, 30, WHITE);
            }
            //draw water button
            if(CheckCollisionPointRec(cursor, waterbuttonhitbox) || showwatercount){
                DrawTextureEx(water_button_hover, {0, 0}, 0, scale, WHITE);
            }
            else{
                DrawTextureEx(water_button, {0, 0}, 0, scale, WHITE);
            }
            //show water count
            if(showwatercount){
                DrawText(TextFormat("Water: %d", watercount), 110, 130, 30, WHITE);
            }

        }   
            
        
        EndDrawing();
    }
    unloadGameTextures();
    CloseWindow();
    return 0;
}