#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    Vector2 position;
    Vector2 speed;
    int size;
} MovingObject;

int main(void)
{
    // Game config stuff
    int resolutionWidth = 854;
    int resolutionHeight = 480;
    Color red = {255, 0, 0, 255};
    // Note : paddle_height is "to the right" and paddle_width is "to the top"
    int paddleX, paddleY;
    size_t paddleHeight = 5;
    size_t paddleWidth = 100;
    size_t paddleSpeed = 8;
    int ballSize = 10;
    int ballSpeedX = 6;
    int ballSpeedY = rand() % 6;
    int paddleSpacement = 20;

    int textWidth = MeasureText("Game over !", 20);

    MovingObject ball = {{resolutionWidth/2, resolutionHeight/2}, {-ballSpeedX, ballSpeedY}, ballSize};

    
    
    // Paddle position at the start
    paddleX = paddleHeight + 10;
    paddleY = resolutionHeight/2;

    bool close = false; // Game Loop boolean
    bool gameOver = false; // Game Over screen boolean
    InitWindow(resolutionWidth, resolutionHeight, "Pong");
    SetTargetFPS(60);
    

    // Game Loop
    while (!close)
    {
            // Event handler
            if (IsKeyDown(KEY_UP))
            {
                if (paddleY > 0)
                {
                    paddleY -= paddleSpeed;
                }
            }
            else if (IsKeyDown(KEY_DOWN))
            { 
                if (paddleY < resolutionHeight - paddleWidth)
                {
                    paddleY += paddleSpeed;
                }
            }	
            else if (IsKeyDown(KEY_A))
            {
                close = true;
            }
        
            if (ball.position.x - ballSize < paddleX + paddleHeight)
            {
                ball.speed.x = ballSpeedX;
                ball.speed.y = rand() % 6;
                if (ball.position.y < paddleY || ball.position.y > paddleY + paddleWidth) // En dehors du paddle
                {
                    gameOver = true;
                }
            }
            

            if (ball.position.x - ballSize >= resolutionWidth-ballSize-paddleHeight-paddleSpacement)
            {
                ball.speed.x = -ballSpeedX;
            }

            // Checking ball collisions
            if (ball.position.y-ballSize <= 0 || ball.position.y+ballSize >= resolutionHeight)
            {
                ball.speed.y *= -1;
            }

            
            ball.position.x += ball.speed.x;
            ball.position.y += ball.speed.y;
            

            // Drawing objects
            BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(paddleX, paddleY, paddleHeight, paddleWidth, WHITE); // Paddle
            DrawCircle(ball.position.x, ball.position.y, (float)ball.size, red); // Ball
            DrawRectangle(resolutionWidth-paddleSpacement, 0, paddleHeight, resolutionHeight, WHITE); // Wall
            EndDrawing();

            // Handling game over
            while (gameOver)
            {
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Game over !", (resolutionWidth - textWidth)/2, (resolutionHeight - 20)/2, 20, WHITE);
                EndDrawing();
                if (IsKeyDown(KEY_A))
                {
                    close = false;
                    gameOver = false;
                }
                else if (IsKeyDown(KEY_R))
                {
                    ball.position.x = resolutionWidth/2;
                    ball.position.y = resolutionHeight/2;
                    ball.speed = (Vector2){-ballSpeedX, ballSpeedY};
                    gameOver = false;
                }
            }
    }
    
    CloseWindow();
    return 0;
}
