#include <raylib.h>
#include "settings.h"
#include "textures.h"
#include <cmath>
#include <fstream>
#include <cstdio>

int main(){
    initGame();
    loadGameTextures();

    enum class screen {
        menu,
        guide,
        screen2,
        shop,
        pause,
        gameover
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
    const double growthduration = 2.0f;

    //harvest
    int cropcount = 0;
    bool showcropcount = false;
    int coins = 0;
    int soldcount = 0;
    bool showsoldcount = false;

    // rent system
    double renttimer = 0;
    const double rentduration = 90.0;
    int rentcost = 20;
    bool rentstarted = false;
    bool gameover = false;
    int rentpaid = 0;
    int rentincrease = 5;
    int totalrentpaid = 0;
    int totalearned = 0;
    double savedrentremaining = rentduration;

    //load saved game
    std:: ifstream loadfile("save.txt");
    if(loadfile.is_open()){
        loadfile >> coins;
        loadfile >> seedcount;
        loadfile >> watercount;
        loadfile >> cropcount;
        loadfile >> soldcount;

        //load farm plots
        for(int row = 0; row < 3; row++){
            for(int col = 0; col < 3; col++){
                loadfile >> farm[row][col];
            }
        }

        //load growth time left
        for(int row = 0; row < 3; row++){
            for(int col = 0; col < 3; col++){
                double remaining = 0;
                if(loadfile >> remaining){
                    if(farm[row][col] >= 2 && farm[row][col] < 6){
                        growthtimers[row][col] = GetTime() - (growthduration - remaining);
                    }
                }
                else if(farm[row][col] >= 2 && farm[row][col] < 6){
                    growthtimers[row][col] = GetTime();
                }
            }
        }

        //load rent data
        double rentremaining = rentduration;
        if(loadfile >> rentremaining >> rentcost >> rentpaid){
            if(rentremaining < 0){
                rentremaining = 0;
            }
            if(rentremaining > rentduration){
                rentremaining = rentduration;
            }
            savedrentremaining = rentremaining;
            rentstarted = false;
        }

        loadfile >> totalrentpaid;
        loadfile >> totalearned;

        loadfile.close();

    }
    //save notifications
    bool showsavemessage = false;
    double savetimer = 0;
    // reset
    bool confirmreset = false;

    //notifications
    int shopmessage = 0;
    double messagetimer = 0;

    //pause
    bool paused = false;



    while(!WindowShouldClose() && running){
        Vector2 cursor = GetMousePosition();

        //fstream!!
        if(IsKeyPressed(KEY_L)){
            std::ofstream savefile("save.txt");

            if(savefile.is_open()){
                savefile << coins << "\n";
                savefile << seedcount << "\n";
                savefile << watercount << "\n";
                savefile << cropcount << "\n";
                savefile << soldcount << "\n";


                //save plots
                for(int row = 0; row < 3; row++){
                    for(int col = 0; col < 3; col++){
                        savefile << farm[row][col] << " ";
                    }
                    savefile << "\n";
                }

                //save growth time left
                for(int row = 0; row < 3; row++){
                    for(int col = 0; col < 3; col++){
                        double remaining = 0;
                        if(farm[row][col] >= 2 && farm[row][col] < 6){
                            remaining = growthduration - (GetTime() - growthtimers[row][col]);
                            if(remaining < 0){
                                remaining = 0;
                            }
                        }
                        savefile << remaining << " ";
                    }
                    savefile << "\n";
                }

                //save rent data
                double rentremaining = savedrentremaining;
                if(rentstarted){
                    rentremaining = rentduration - (GetTime() - renttimer);
                }
                if(rentremaining < 0){
                    rentremaining = 0;
                }

                savefile << rentremaining << "\n";
                savefile << rentcost << "\n";
                savefile<< rentpaid << "\n";
                savefile << totalrentpaid << "\n";
                savefile << totalearned << "\n";

                savefile.close();

                showsavemessage = true;
                savetimer = GetTime();
            }
        }
        //rset data
        if(IsKeyPressed(KEY_BACKSPACE)){
            if(!confirmreset){
                confirmreset = true;
            }
            else{
                savedrentremaining = rentduration;
                rentstarted = false;
                //reset rent
                rentcost = 20;
                rentpaid = 0;
                gameover = false;
                renttimer = GetTime();
                //reset totals
                totalearned = 0;
                totalrentpaid = 0;
                //reset inveotry
                coins = 0;
                seedcount = 2;
                watercount = 2;
                cropcount = 0;
                soldcount = 0;
                //reset farm
                for(int row = 0; row < 3; row++){
                    for(int col = 0; col < 3; col++){
                        farm[row][col] = 0;
                        growthtimers[row][col] = 0;
                    }
                }
                //deleete save file
                std::remove("save.txt");
                confirmreset = false;
            }
        }
        if(IsKeyPressed(KEY_P)){
            confirmreset = false;
        }

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
                    if(!rentstarted){
                        renttimer = GetTime() - (rentduration - savedrentremaining);
                        rentstarted = true;
                    }
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
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currentscreen = screen::guide;
                }
            }
            else{
                DrawTextureEx(menu_guide_button, {0, 0}, 0, 4.0f, WHITE);
            }

        }
        else if(currentscreen == screen::screen2){
            if(IsKeyPressed(KEY_ESCAPE)){
                currentscreen = screen::pause;
            }
            ClearBackground(WHITE);
            DrawTextureEx(game_background, {0, 0}, 0, 4.0f, WHITE);

            //rent countdown
            double timeleft = rentduration - (GetTime() - renttimer);
            if(timeleft < 0){
                timeleft = 0;
            }

            int minutes = (int)timeleft / 60;
            int seconds = (int)timeleft % 60;

            DrawText(
                TextFormat("Rent: %02d:%02d", minutes, seconds),
                450, 30, 40, WHITE
            );

            DrawText(
                TextFormat("Rent Due: %d Coins", rentcost),
                450, 80, 30, YELLOW
            );

            DrawText(
                TextFormat("Round: %d", rentpaid + 1),
                450, 120, 30, GREEN
            );

            if(timeleft <= 0 && !gameover){
                if(coins >= rentcost){
                    totalrentpaid += rentcost;
                    coins -= rentcost;
                    rentpaid++;
                    renttimer = GetTime();
                    rentcost += rentincrease;
                }
                else{
                    gameover = true;
                    currentscreen = screen::gameover;
                }
            }
            

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

            //crop count invetory
            Rectangle cropdisplayhitbox = {
                28, 
                47 * 4,
                72,
                72
            };
            
            if(CheckCollisionPointRec(cursor, cropdisplayhitbox)){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    showcropcount = !showcropcount;
                }
            }

            //sell button
            Rectangle sellbuttonhitbox = {
                28, 
                67 * 4,
                72,
                72
            };

            if(CheckCollisionPointRec(cursor, sellbuttonhitbox)){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    showsoldcount = !showsoldcount;
                    if(cropcount > 0){
                        coins += 3;
                        cropcount --;
                        soldcount++;
                        totalearned += 3;

                    }
                }
            }

            //shop button
            Rectangle shopbuttonhitbox = {
                28, 
                87 * 4,
                72,
                72 
            };

            if(CheckCollisionPointRec(cursor, shopbuttonhitbox)){
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    currentscreen = screen::shop;
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
            if(selectedRow != -1 && IsKeyPressed(KEY_E)){
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
            //harvest interaction message
            if(selectedRow != -1){
                if(farm[selectedRow][selectedCol] == 6){
                    int x = startX + selectedCol * (plotSize + gap);
                    int y = startY + selectedRow * (plotSize + gap);
                    DrawText("Press E to Harvest", x, y - 160, 24, WHITE);
                }
            }
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
            // draw crop display
            if(CheckCollisionPointRec(cursor, cropdisplayhitbox)){
                DrawTextureEx(crop_display_hover, {0, 0}, 0, scale, WHITE);
            }
            else{
                DrawTextureEx(crop_display, {0, 0}, 0, scale, WHITE);
            }
            //cshow crop count
            if(showcropcount){
                DrawText(TextFormat("Peaches: %d", cropcount), 110, 210, 30, WHITE);
            }
            //draw sell button
            if(CheckCollisionPointRec(cursor, sellbuttonhitbox)){
                DrawTextureEx(sell_hover, {0, 0}, 0, scale, WHITE);
            }
            else{
                DrawTextureEx(sell, {0, 0}, 0, scale, WHITE);
            }
            DrawTextureEx(coindisplay, {0, 0}, 0, scale, WHITE);
            DrawText(TextFormat("Coins: %d", coins), 100, 1194, 30, YELLOW);
            DrawText(TextFormat("Sold: %d", soldcount), 110, 290, 30, WHITE);
            //draw shop button
            if(CheckCollisionPointRec(cursor, shopbuttonhitbox)){
                DrawTextureEx(shop_hover, {0, 0}, 0, scale, WHITE);
            }
            else{
                DrawTextureEx(shop, {0, 0}, 0, scale, WHITE);
            }

        }
        else if(currentscreen == screen::shop){
            DrawTextureEx(shop_page, {0, 0}, 0, scale, WHITE);
            //peach buy
            Rectangle peachhitbox = {
                87 * 4,
                86 * 4,
                18 * 4,
                17 * 4
            };

            bool buypeachhover = CheckCollisionPointRec(cursor, peachhitbox);

            //buy it
            if(buypeachhover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if(coins >= 4){
                    coins -= 4;
                    seedcount++;
                    shopmessage = 1;
                }
                else{
                    shopmessage = 3;
                }
                messagetimer = GetTime();
            }
            //draw peach button
            if(buypeachhover){
                DrawTextureEx(peach_hover, {0, 0}, 0, scale, WHITE);
            }
            else{
                DrawTextureEx(peach, {0, 0}, 0, scale, WHITE);
            }

            //water buy
            Rectangle waterhitbox = {
                87 * 4,
                109 * 4,
                18 * 4,
                17 * 4
            };

            bool buywaterhover = CheckCollisionPointRec(cursor, waterhitbox);

            //buy it
            if(buywaterhover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if(coins >= 5){
                    coins -= 5;
                    watercount++;
                    shopmessage = 2;
                }
                else{
                    shopmessage = 3;
                }
                messagetimer = GetTime();
            }
            //draw water button
            if(buywaterhover){
                DrawTextureEx(water_hover, {0, 0}, 0, scale, WHITE);
            }
            else{
                DrawTextureEx(water, {0, 0}, 0, scale, WHITE);
            }

            //draw price
            DrawText("5 COINS", 430, 460, 30, YELLOW);
            DrawText("4 COINS", 430, 365, 30, YELLOW);
            DrawText(TextFormat("Coins: %d", coins), 830, 950, 30, YELLOW);

            //ntoification animation
            double elapsed = GetTime() - messagetimer;
            if(shopmessage != 0 && elapsed < 1.0){
                float alpha = 1.0f;
                //fade out
                if(elapsed > 0.3){
                    alpha = (float)(0.6 - elapsed) / 0.3;
                }
                //float up
                float y = 800 - (float)(elapsed) * 25;
                const char* message = "";
                Color messagecolor = GREEN;
                // messages
                if(shopmessage == 1){
                    message = "+1 Peach Seed!";
                }
                else if(shopmessage == 2){
                    message = "+1 Water Bucket!";
                }
                else if(shopmessage == 3){
                    message = "Not Enough Coins!";
                    messagecolor = RED;
                }

                int fontsize = 30;
                int textwidth = MeasureText(message, fontsize);
                int x = (screenWidth - textwidth) / 2;

                //rounded bg
                DrawRectangleRounded(
                    {(float)x - 20, y - 10, (float)textwidth + 40, 55},
                    0.2f,
                    8, 
                    Fade(BLACK, alpha * 0.6f)
                );

                //text shadow
                DrawText(message, x + 2, (int)y + 2, fontsize, Fade(BLACK, alpha * 0.5f));

                //draw it
                DrawText(message, x, (int)y, fontsize, Fade(messagecolor, alpha));

                
            }

            if(IsKeyPressed(KEY_ESCAPE)){
                currentscreen = screen::screen2;
            }

        }
        else if(currentscreen == screen::guide){
            DrawTextureEx(guide_page, {0, 0}, 0, scale, WHITE);
            DrawText("HOW TO PLAY", 450, 300, 50, DARKGREEN);
            DrawText("WASD - Move your farmer", 400, 400, 30, BLACK);
            DrawText("E - Plant, water, and harvest", 400, 460, 30, BLACK);
            DrawText("Click icons to select tools", 400, 520, 30, BLACK);
            DrawText("Sell peaches to earn coins", 400, 580, 30, BLACK);
            DrawText("Buy seeds and water in the shop", 400, 640, 30, BLACK);
            DrawText("ESC - Return to Menu", 400, 800, 50, BLACK);
            if(IsKeyPressed(KEY_ESCAPE)){
                currentscreen = screen::menu;
            }
        }
        else if(currentscreen == screen::pause){
            SetWindowOpacity(0.7f);
            DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
            DrawText("PAUSED", 530, 400, 50, WHITE);

            //play triangle
            DrawTriangle({610, 560}, {610, 680}, {710, 620}, WHITE);

            if(IsKeyPressed(KEY_ESCAPE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                currentscreen = screen::screen2;
                SetWindowOpacity(1.0f);
            }
        }
        else if(currentscreen == screen::gameover){
            DrawTextureEx(gameover_screen, {0, 0}, 0, scale, WHITE);
            DrawText(TextFormat("Round Reached: %d", rentpaid + 1), 400, 500, 60, YELLOW);
            DrawText(TextFormat("Total Earned: %d Coins", totalearned), 375, 575, 40, YELLOW);
            DrawText(TextFormat("Total Rent paid: %d Coins", totalrentpaid), 375, 650, 40, YELLOW);
            DrawText("Press R to return", 400, 750, 60, GREEN);

            if(IsKeyPressed(KEY_R)){
                //reset inventory
                coins = 0;
                seedcount = 2;
                watercount = 2;
                cropcount = 0;
                soldcount = 0;

                //reset farm
                for(int row = 0; row < 3; row++){
                    for(int col = 0; col < 3; col++){
                        farm[row][col] = 0;
                        growthtimers[row][col] = 0;
                    }
                }

                //reset rent
                rentcost = 20;
                rentpaid = 0;
                gameover = false;
                renttimer = GetTime();
                rentstarted = false;
                savedrentremaining = rentduration;

                //reset playuer
                playerPos = {600, 600};
                currentfarmer = farmer_down;
                //restart game
                currentscreen = screen::menu;

                std::remove("save.txt");

            }

        }
        
        if(showsavemessage){
            double elapsed = GetTime() - savetimer;
            if(elapsed < 1.0){
                float alpha = 1.0f;
                //fade out after 0.5
                if(elapsed > 0.5){
                    alpha = (float)((1.0 - elapsed) / 0.5);
                }
                //float up
                float y = 800 - (float)elapsed * 25;

                const char* message = "Game Saved!";
                int fontsize = 30;
                int textwidth = MeasureText(message, fontsize);
                int x = (screenWidth - textwidth) / 2;

                DrawRectangleRounded(
                    {(float)x - 20, y - 10, (float)textwidth + 40, 55},
                    0.2f,
                    8,
                    Fade(BLACK, alpha * 0.6f)
                );

                //text shadow!
                DrawText(message, x + 2, (int)y + 2, fontsize, Fade(BLACK, alpha * 0.5f));
                //green notification
                DrawText(message, x, (int)y, fontsize, Fade(GREEN, alpha));
            }
            else{
                showsavemessage = false;
            }
        }
        if(confirmreset){
            const char* message = "Press Backspace again to reset (P to cancel)";

            int fontsize = 25;
            int textwidth = MeasureText(message, fontsize);
            int x = (screenWidth - textwidth) / 2;
            DrawRectangleRounded(
                {(float)x - 20, 850, (float)textwidth + 40, 55},
                0.2f,
                8,
                Fade(BLACK, 0.7f)
            );
            DrawText(message, x, 860, fontsize, RED);
        }

        
        EndDrawing();

    }

        //automatically save when exiting
    if(!gameover){
        std::ofstream savefile("save.txt");

        if(savefile.is_open()){
            //save inventory
            savefile << coins << "\n";
            savefile << seedcount << "\n";
            savefile << watercount << "\n";
            savefile << cropcount << "\n";
            savefile << soldcount << "\n";

            //save farm plots
            for(int row = 0; row < 3; row++){
                for(int col = 0; col < 3; col++){
                    savefile << farm[row][col] << " ";
                }
                savefile << "\n";
            }

            //save growth timers
            for(int row = 0; row < 3; row++){
                for(int col = 0; col < 3; col++){
                    double remaining = 0;

                    if(farm[row][col] >= 2 && farm[row][col] < 6){
                        remaining = growthduration - (GetTime() - growthtimers[row][col]);

                        if(remaining < 0){
                            remaining = 0;
                        }
                    }

                    savefile << remaining << " ";
                }
                savefile << "\n";
            }

            //save rent
            double rentremaining = savedrentremaining;

            if(rentstarted){
                rentremaining = rentduration - (GetTime() - renttimer);
            }

            if(rentremaining < 0){
                rentremaining = 0;
            }

            savefile << rentremaining << "\n";
            savefile << rentcost << "\n";
            savefile << rentpaid << "\n";
            savefile << totalrentpaid << "\n";
            savefile << totalearned << "\n";

            savefile.close();
        }
    }
    unloadGameTextures();
    CloseWindow();
    return 0;
}