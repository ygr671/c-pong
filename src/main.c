#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
    Vector2 position;
    Vector2 speed;
    int size;
} MovingObject;

typedef struct
{
    size_t width;
    size_t height;
    size_t speed;
    int x;
    int y;
}  Paddle;

int main(void)
{
    srand(time(NULL));
    // Game config stuff
    int resolutionWidth = 854;
    int resolutionHeight = 480;
    Color red = {255, 0, 0, 255};
    // Note : player.height is paddle's "width" and player.width is the "height"
    Paddle player1 = {100, 5, 8};
    Paddle player2 = {100, 5, 8};
    // Paddles position at the start
    player1.x = player1.height + 10;
    player1.y = resolutionHeight / 2;
    
    player2.x = resolutionWidth - 20;
    player2.y = resolutionHeight / 2;

    
    
    int ballSize = 10;
    int randomBallSpeedX = rand() % 2;
    int ballSpeedX = 6;
    if (randomBallSpeedX == 0)
    {
        ballSpeedX = 6;
    }
    else if (randomBallSpeedX == 1)
    {
        ballSpeedX = -6;
    }
    int ballSpeedY = rand() % 6;
    int textWidth = MeasureText("Game over !", 20);

    MovingObject ball = {{resolutionWidth/2, resolutionHeight/2}, {-ballSpeedX, ballSpeedY}, ballSize};

    bool close = false; // Game Loop boolean
    bool gameOver = false; // Game Over screen boolean
    InitWindow(resolutionWidth, resolutionHeight, "Pong");
    SetTargetFPS(60);
    

    // Game Loop
    while (!close)
    {
            // Event handler
            // Player 1 movement
            if (IsKeyDown(KEY_W))
            {
                if (player1.y > 0)
                {
                    player1.y -= player1.speed;
                }
            }
            else if (IsKeyDown(KEY_S))
            { 
                if (player1.y < resolutionHeight - player1.width)
                {
                    player1.y += player1.speed;
                }
            }
            // Player 2 movement
            else if (IsKeyDown(KEY_UP))
            {
                if (player2.y > 0)
                {
                    player2.y -= player2.speed;
                }
            }
            else if (IsKeyDown(KEY_DOWN))
            {
                if (player2.y < resolutionHeight - player2.width)
                {
                    player2.y += player2.speed;
                }
            }
            else if (IsKeyDown(KEY_A))
            {
                close = true;
            }
        
            // Checking ball collisions with the player 1's paddle
            if (ball.position.x - ballSize < player1.x + player1.height)
            {
                ball.speed.x = -ball.speed.x;
                ball.speed.y = rand() % 11 - 6;
                if (ball.position.y < player1.y || ball.position.y > player1.y + player1.width) // Checking if the ball goes behing the paddle
                {
                    gameOver = true;
                }
            }
            
            // Checking ball collisiions with the player 2's paddle
            if (ball.position.x - ballSize >= resolutionWidth - ballSize - player1.height - 20)
            {
                ball.speed.x = -ball.speed.x;
                ball.speed.y = rand() % 11 - 6;
                if (ball.position.y < player2.y || ball.position.y > player2.y + player2.width)
                {
                    gameOver = true;
                }
            }

            // Checking ball collisions with the top and bottom
            if (ball.position.y - ballSize <= 0 || ball.position.y + ballSize >= resolutionHeight)
            {
                ball.speed.y *= -1;
            }

            
            ball.position.x += ball.speed.x;
            ball.position.y += ball.speed.y;
            

            // Drawing objects
            BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(player1.x, player1.y, player1.height, player1.width, WHITE); // Paddle player1
            DrawRectangle(player2.x, player2.y, player2.height, player2.width, WHITE); // Paddle player2
            DrawCircle(ball.position.x, ball.position.y, (float)ball.size, red); // Ball
            //DrawRectangle(resolutionWidth - wallSpacement, 0, player1.height, resolutionHeight, WHITE); // Wall
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
                    // Resetting players positions
                    ball.position.x = resolutionWidth / 2;
                    ball.position.y = resolutionHeight / 2;
                    
                    player2.x = resolutionWidth - 20;
                    player2.y = resolutionHeight / 2;
                    
                    // Resetting ball speed
                    ball.speed = (Vector2){-ballSpeedX, ballSpeedY};
                    gameOver = false;
                }
            }
    }
    
    CloseWindow();
    return 0;
}
