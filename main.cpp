/**
 * @file main.cpp
 * @brief Main file for the raylib Tetris game.
 */
#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

/**
 * @brief Time of the last update.
 */
double lastUpdateTime = 0;

/**
 * @brief Checks if a certain time interval has passed since the last update.
 * @param interval The time interval to check.
 * @return True if the interval has passed, false otherwise.
 */
bool EventTriggered(double interval) {
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}

/**
 * @brief Main function for the raylib Tetris game.
 * Initializes the window, loads the font, and starts the game loop.
 * @return 0 on successful execution.
 */
int main() {
  InitWindow(500, 620, "raylib Tetris");
  SetTargetFPS(60);

  Font font = LoadFontEx("../Font/monogram.ttf", 64, 0, 0);
  // std::cout << GetWorkingDirectory();

  Game game = Game();

  while (WindowShouldClose() == false) {
    UpdateMusicStream(game.music);
    game.HandleInput();
   // 1000 ms between each update
    if (EventTriggered(1.0)) {
      game.MoveBlockDown();
    }

    BeginDrawing();
    ClearBackground(darkBlue);
    DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
    if (game.gameOver) {
      DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
    }
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

    char scoreText[10];
    sprintf(scoreText, "%d", game.score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
    game.Draw();
    EndDrawing();
  }

  CloseWindow();
}
