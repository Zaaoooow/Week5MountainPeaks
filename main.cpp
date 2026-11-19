#include <raylib.h>
#include "settings.h"
#include "textures.h"

int main(){
    initGame();
    loadGameTextures();

    enum class screen {
        menu,
        screen2,
        third,
        fourth
    };

    bool running = true;

    screen currentscreen = screen::menu;

    while(!WindowShouldClose() && running){
        Vector2 cursor = GetMousePosition();
        BeginDrawing();

        if(currentscreen == screen::menu){
            //collision booleans
            bool playBool = CheckCollisionPointRec(cursor, {400, 576, 480, 108});
            bool quitBool = CheckCollisionPointRec(cursor, {400, 880, 480, 108});

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

        }
        else if(currentscreen == screen::screen2){
            ClearBackground(WHITE);
            DrawText("Screen 2", 300, 300, 40, GREEN);
        }
        




        EndDrawing();
    }
    unloadGameTextures();
    CloseWindow();
    return 0;
}