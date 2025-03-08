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
    int x, y;
    // Game config stuff
    int resolution_width = 854;
    int resolution_height = 480;

    // Note : paddle_height is "to the right" and paddle_width is "to the top"
    size_t paddle_height = 5;
    size_t paddle_width = 100;
    size_t paddle_speed = 8;

    int ball_size = 10;
    int ball_speed = 6;
    int ball_speed_y = rand() % 6;
    int paddle_spacement = 20;

    int textWidth = MeasureText("Game over !", 20);

    MovingObject ball = {{resolution_width/2, resolution_height/2}, {-ball_speed, ball_speed_y}, ball_size};

    Color red = {255, 0, 0, 255}; // {r, g, b, alpha (transparency)}
    
    // Position at start calculated
    x = paddle_height + 10;
    y = resolution_height/2;

    bool close = false;
    bool game_over = false;
    InitWindow(resolution_width, resolution_height, "Pong");
    SetTargetFPS(60);
    

    // Game Loop
    while (!close)
    {
            // Event handler
            if (IsKeyDown(KEY_UP))
            {
                if (y > 0)
                {
                    y -= paddle_speed;
                }
            }
            else if (IsKeyDown(KEY_DOWN))
            { 
                if (y < resolution_height - paddle_width)
                {
                    y += paddle_speed;
                }
            }	
            else if (IsKeyDown(KEY_A))
            {
                close = true;
            }
        
            if (ball.position.x - ball_size < x + paddle_height)
            {
                ball.speed.x = ball_speed;
                ball.speed.y = rand() % 6;
                if (ball.position.y < y || ball.position.y > y + paddle_width) // En dehors du paddle
                {
                    game_over = true;
                }
            }
            

            if (ball.position.x - ball_size >= resolution_width-ball_size-paddle_height-paddle_spacement)
            {
                ball.speed.x = -ball_speed;
            }

            // Checking ball collisions
            if (ball.position.y-ball_size <= 0 || ball.position.y+ball_size >= resolution_height)
            {
                ball.speed.y *= -1;
            }

            
            ball.position.x += ball.speed.x;
            ball.position.y += ball.speed.y;
            

            // Drawing objects
            BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(x, y, paddle_height, paddle_width, WHITE); // Paddle
            DrawCircle(ball.position.x, ball.position.y, (float)ball.size, red); // Ball
            DrawRectangle(resolution_width-paddle_spacement, 0, paddle_height, resolution_height, WHITE); // Wall
            EndDrawing();

            // Handling game over
            while (game_over)
            {
                BeginDrawing();
                ClearBackground(BLACK);
                DrawText("Game over !", (resolution_width - textWidth)/2, (resolution_height - 20)/2, 20, WHITE);
                EndDrawing();
                if (IsKeyDown(KEY_A))
                {
                    close = false;
                    game_over = false;
                }
                else if (IsKeyDown(KEY_R))
                {
                    ball.position.x = resolution_width/2;
                    ball.position.y = resolution_height/2;
                    ball.speed = (Vector2){-ball_speed, ball_speed_y};
                    game_over = false;
                }
            }
    }
    
    CloseWindow();
    return 0;
}
