#include "libraries/raylib/raylib.h"
#include "libraries/raygui.h"
#include <iostream>
#include <string>

//Variables
//Menus
bool isTitle = true;
bool isGame = false;
int mousex, mousey;
//Game
bool isDead = false;
int score = 0;
//Phisics
float velocity = 10, acceleration = 0;
//Player
struct Player {
    int positionx;
    int positiony;
    int direction;
};
struct Player Player = {500, 500, 1};
//Obsticles 
struct Spikes {
    bool spike1, spike2, spike3, spike4, spike5, spike6, spike7, spike8, spike9, spike10;
    int spike1_posx, spike2_posx, spike3_posx, spike4_posx, spike5_posx, spike6_posx, spike7_posx, spike8_posx, spike9_posx, spike10_posx;
    int spike1_posy, spike2_posy, spike3_posy, spike4_posy, spike5_posy, spike6_posy, spike7_posy, spike8_posy, spike9_posy, spike10_posy;
};
struct Spikes Spikes = {true, true, true, true, true, true, true, true, true, true};
//Coin
struct Coin {
    int positionx, positiony;
    bool collected;
};
struct Coin Coin = {250, 250, false};
//Textures
struct Textures {
    Texture2D spikeleft, spikeright, coin, bird;
};
//Sounds
struct Sounds {
    Sound left, right, coin, death, jump;
};
//Funtions
void spike_posx(){
    int x;
    if (Player.direction == 1){
        x = 980;
    }
    else if (Player.direction == -1){
        x = 0;
    }
    Spikes.spike1_posx = x;
    Spikes.spike2_posx = x;
    Spikes.spike3_posx = x;
    Spikes.spike4_posx = x;
    Spikes.spike5_posx = x;
    Spikes.spike6_posx = x;
    Spikes.spike7_posx = x;
    Spikes.spike8_posx = x;
    Spikes.spike9_posx = x;
    Spikes.spike10_posx = x;
}
void spike_posy(int y){
    Spikes.spike1_posy = y * 0;
    Spikes.spike2_posy = y * 1;
    Spikes.spike3_posy = y * 2;
    Spikes.spike4_posy = y * 3;
    Spikes.spike5_posy = y * 4;
    Spikes.spike6_posy = y * 5;
    Spikes.spike7_posy = y * 6;
    Spikes.spike8_posy = y * 7;
    Spikes.spike9_posy = y * 8;
    Spikes.spike10_posy = y * 9;
}
void spike(bool spike, int spike_posx, int spike_posy, Texture2D spiketextureleft, Texture2D spiketextureright){
    if (spike){
        if (Player.direction == 1) {
            DrawTexture(spiketextureleft, spike_posx, spike_posy, WHITE);
        }
        if (Player.direction == -1) {
            DrawTexture(spiketextureright, spike_posx, spike_posy, WHITE);
        }
    }
}
void exesistance() {
    int kill = rand() % 10 + 1, i = 0;
    while(i != 1){
        if(kill == 3){
            Spikes.spike3 = false;
            i = 1;
        }
        else if(kill == 4){
        }
        else if(kill == 4){
            Spikes.spike4 = false;
            i = 1;
        }
        else if(kill == 5){
            Spikes.spike5 = false;
            Spikes.spike4 = false;
            i = 1;
        }
        else if(kill == 5){
            Spikes.spike5 = false;
            i = 1;
        }
        else if(kill == 6){
            Spikes.spike6 = false;
            i = 1;
        }
        else if(kill == 7){
            Spikes.spike7 = false;
            i = 1;
        }
        else if(kill == 8){
            Spikes.spike8 = false;
            i = 1;
        }
        if (i != 1){
            kill = rand() % 10 + 1, i = 0;
        }
    }
}
void spike_existace(){
    Spikes = {true, true, true, true, true, true, true, true, true, true};
    exesistance();
    exesistance();
}
void spike_colision(int obj_posx, int obj_posy, bool spike){
    int obj_startposx = obj_posx;
    int obj_endposx = obj_posx + 40;
    int obj_startposy = obj_posy;
    int obj_endposy = obj_posy + 100;
    if (spike){
        if (spike && Player.positionx >= obj_startposx && Player.positionx <= obj_endposx && Player.positiony >= obj_startposy && Player.positiony <= obj_endposy){
            isDead = true;
            isGame = false;
        }
    }
}
void coin_random_pos(){
    int x = rand() % 700 + 1;
    if (x <= 100 or x >= 900){
        x = x + 200;
    }
    int y =  rand() % 1000 + 1;
    if (y <= 300){
        y = y + 400;
    }
    Coin.positionx = x;
    Coin.positiony = y;
}
void coin_colision(){
    int obj_startposx = Coin.positionx - 20;
    int obj_endposx = Coin.positionx + 20;
    int obj_startposy = Coin.positiony - 20;
    int obj_endposy = Coin.positiony + 20;
    if (Player.positionx >= obj_startposx && Player.positionx <= obj_endposx && Player.positiony >= obj_startposy && Player.positiony <= obj_endposy){
        coin_random_pos();
        score ++;
    }
}
bool button(int x, int y, const char *text){
    int obj_startposx = x;
    int obj_endposx = x + 200;
    int obj_startposy = y;
    int obj_endposy = y + 100; 
    DrawRectangle(x, y, 200, 100, RED);
    DrawText(text ,obj_startposx +20, obj_startposy + 30, 45, WHITE);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mousex >= obj_startposx && mousex <= obj_endposx && mousey >= obj_startposy && mousey <= obj_endposy){
        return true;
    }
    return false;
}
//Main
int main(){
    //Initialization
    InitWindow(1000,1000,"Birdy watch out!");
    InitAudioDevice();
    SetTargetFPS(60);
    spike_existace();
    spike_posy(100);
    coin_random_pos();
    struct Textures Textures = {LoadTexture("textures/spike.png"), LoadTexture("textures/spike.png"), LoadTexture("textures/coin.png"), LoadTexture("textures/bird.png")};
    struct Sounds Sounds = {LoadSound("sounds/left.wav"),LoadSound("sounds/right.wav"),LoadSound("sounds/coin.wav"),LoadSound("sounds/dead.wav")};
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);
        mousex = { GetMousePosition().x};
        mousey = { GetMousePosition().y};
        if (isTitle){
            DrawText("Birdy watch out!", 300, 400, 50, BLACK);
            if (button(400, 550, "START")){
                isGame = true;
                isTitle = false;
            }
        }
        if (isGame){
            //Gui
            DrawText(std::to_string(score).c_str(), 450, 50, 100, GRAY);
            // Dead
            spike_colision(Spikes.spike1_posx, Spikes.spike1_posy, Spikes.spike1);
            spike_colision(Spikes.spike2_posx, Spikes.spike2_posy, Spikes.spike2);
            spike_colision(Spikes.spike3_posx, Spikes.spike3_posy, Spikes.spike3);
            spike_colision(Spikes.spike4_posx, Spikes.spike4_posy, Spikes.spike4);
            spike_colision(Spikes.spike5_posx, Spikes.spike5_posy, Spikes.spike5);
            spike_colision(Spikes.spike6_posx, Spikes.spike6_posy, Spikes.spike6);
            spike_colision(Spikes.spike7_posx, Spikes.spike7_posy, Spikes.spike7);
            spike_colision(Spikes.spike8_posx, Spikes.spike8_posy, Spikes.spike8);
            spike_colision(Spikes.spike9_posx, Spikes.spike9_posy, Spikes.spike9);
            spike_colision(Spikes.spike10_posx, Spikes.spike10_posy, Spikes.spike10);
            //Player
            //Rendering player
            DrawRectangle(Player.positionx - 10, Player.positiony - 10, 20, 20, BLACK);
            // Bouncing player
            //  X
            if(Player.positionx >= 1001){
                Player.direction = -1;
                Player.positionx = 1000;
                score ++;
                spike_existace();
                PlaySound(Sounds.left);
            }
            if(Player.positionx <= 10){
                Player.direction = 1;
                Player.positionx = 11;
                score ++;
                spike_existace();
                PlaySound(Sounds.right);
            }
            //  Y
            if(Player.positiony >= 992){
                Player.positiony = 991;
                acceleration = -20;
            }
            if(Player.positiony <= 20){
                Player.positiony = 21;
                acceleration = 0;
            }
            // Obsticles
            spike_posx();
            spike_posy(100);
            spike(Spikes.spike1,Spikes.spike1_posx, Spikes.spike1_posy, Textures.spikeleft, Textures.spikeright);
            spike(Spikes.spike2,Spikes.spike2_posx, Spikes.spike2_posy, Textures.spikeleft, Textures.spikeright);
            spike(Spikes.spike3,Spikes.spike3_posx, Spikes.spike3_posy, Textures.spikeleft, Textures.spikeright);
            spike(Spikes.spike4,Spikes.spike4_posx, Spikes.spike4_posy, Textures.spikeleft, Textures.spikeright);
            spike(Spikes.spike5,Spikes.spike5_posx, Spikes.spike5_posy, Textures.spikeleft, Textures.spikeright);
            spike(Spikes.spike6,Spikes.spike6_posx, Spikes.spike6_posy, Textures.spikeleft, Textures.spikeright);
            spike(Spikes.spike7,Spikes.spike7_posx, Spikes.spike7_posy, Textures.spikeleft, Textures.spikeright);
            spike(Spikes.spike8,Spikes.spike8_posx, Spikes.spike8_posy, Textures.spikeleft, Textures.spikeright);
            spike(Spikes.spike9,Spikes.spike9_posx, Spikes.spike9_posy, Textures.spikeleft, Textures.spikeright);
            spike(Spikes.spike10,Spikes.spike10_posx, Spikes.spike10_posy, Textures.spikeleft, Textures.spikeright);
            //Coin
            if (Coin.collected == false){
                DrawTexture(Textures.coin, Coin.positionx - 20, Coin.positiony - 20, YELLOW);
                coin_colision();
            }
            // Controls
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if (acceleration <= 0){
                    acceleration = 0;
                }
                acceleration = acceleration = -20;
            }
            // Phisics
            if (acceleration != 20){
                acceleration = acceleration + 1;
            }
            Player.positiony = Player.positiony + acceleration;
            Player.positionx = Player.positionx + (velocity * Player.direction);
        }
        if(isDead){
            DrawText("you died lol", 350, 450, 20, BLACK);
            if (button(400, 550, "AGAIN?")){
                isGame = true;
                isDead = false;
                score = 0;
                coin_random_pos();
                Player.positionx = 500;
                Player.positiony = 500;
                Player.direction = 1;
                spike_existace();

            }
        }
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    return 0;
}
