#include <raylib.h>

bool RectanglesCollide(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2){
  return x1 <= x2 + width2 &&
       x1 + width1 >= x2 &&
       y1 <= y2 + height2 &&
       y1 + height1 >= y2;
}

int main(){
    int screenWidth = 600;
    int screenHeight = 800;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Flappy bird");
    // int currentMonitor = GetCurrentMonitor();
    // SetTargetFPS(GetMonitorRefreshRate(currentMonitor));
    SetTargetFPS(60);

    bool alive = true;

    int birdX = 100; // screen position
    int birdY = 400;
    float birdVelocity = 0;
    const int BIRDWIDTH = 30;
    const int BIRDHEIGHT = 30;

    int pipesX = 500;
    int pipesMidPoint = 400;
    const int GAP = 98;
    const int PIPESWIDTH = 70;
    
    int score = 0;
    bool hasScored = false;

    while (!WindowShouldClose()){
        // int cm = GetCurrentMonitor();
        int sw = GetScreenWidth();
        int sh = GetScreenHeight();
        if (sw != screenWidth || sh != screenHeight){screenWidth = sw; screenHeight = sh;}
        // if (currentMonitor != cm){currentMonitor = cm; SetTargetFPS(GetMonitorRefreshRate(currentMonitor));}
        
        // logic loop
        if (alive){
            birdVelocity += 0.5f;
            birdY += birdVelocity;

            pipesX -= 2;

            if (IsKeyPressed(KEY_SPACE)){
                birdVelocity = -11.5f;
            }

            if (pipesX <= -PIPESWIDTH){ // pipe of screen
                pipesX = screenWidth;
                pipesMidPoint = GetRandomValue(GAP, screenHeight - GAP);
                hasScored = false;
            }

            if (RectanglesCollide(birdX, birdY, BIRDWIDTH, BIRDHEIGHT, pipesX, 0, PIPESWIDTH, pipesMidPoint - GAP)){ // top pipe collision
                alive = false;
            }

            if (RectanglesCollide(birdX, birdY, BIRDWIDTH, BIRDHEIGHT, pipesX, pipesMidPoint + GAP, PIPESWIDTH, 1000)){ // bottom pipe collision
                alive = false;
            }

            if (birdY >= screenHeight - BIRDHEIGHT){ // ground collision
                alive = false;
            }

            if ((pipesX >= birdX && pipesX <= birdX + BIRDWIDTH) && hasScored == false){
                score++;
                hasScored = true;
                
            }
        } 
        else {
            if (IsKeyPressed(KEY_R)){
                birdX = 100; // screen position
                birdY = 400;
                birdVelocity = 0;
                pipesX = 500;
                pipesMidPoint = 400;
                alive = true;
                score = 0;
                hasScored = false;
            }
        }

        // drawloop
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawRectangle(birdX, birdY, 30, 30, YELLOW);
        DrawRectangle(pipesX, 0, PIPESWIDTH, pipesMidPoint - GAP, GREEN); // top pipe
        DrawRectangle(pipesX, pipesMidPoint + GAP, PIPESWIDTH, 1000, GREEN); // bottom pipe
        DrawText(TextFormat("%i", score), screenWidth / 2, 100, 32, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}