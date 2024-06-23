/**
 * @file game.cpp
 * @brief Implementation of the Game class.
 */
#include "game.h"
#include <random>

/**
 * @brief Constructs a new Game object.
 *
 * Initializes the game grid, loads blocks, sets the initial current and next blocks,
 * and initializes the audio device with the necessary sounds and music.
 */
Game::Game() {
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;
  score = 0;
  isSoundMuted = false;
  muteButton = {340, 410, 130, 40};
  InitAudioDevice();
  // Source: https://www.youtube.com/watch?v=5_L-4JrUGZk
  music = LoadMusicStream("../Sounds/music.mp3");
  PlayMusicStream(music);
  // rotateSound = LoadSound("../Sounds/rotate.mp3");
  clearSound = LoadSound("../Sounds/clear.wav");
}

/**
 * @brief Destroys the Game object.
 *
 * Unloads sounds and music, and closes the audio device.
 */
Game::~Game() {
  // UnloadSound(rotateSound);
  UnloadSound(clearSound);
  UnloadMusicStream(music);
  CloseAudioDevice();
}

/**
 * @brief Gets a random block from the list of available blocks.
 *
 * @return Block A randomly selected block.
 */
Block Game::GetRandomBlock() {
  if (blocks.empty()) {
    blocks = GetAllBlocks();
  }
  int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return block;
}

/**
 * @brief Retrieves all possible blocks for the game.
 *
 * @return std::vector<Block> A vector containing all possible blocks.
 */
std::vector<Block> Game::GetAllBlocks() {
  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

/**
 * @brief Draws the game elements on the screen.
 *
 * Draws the grid, current block, and next block at specified positions.
 */
void Game::Draw() {
  grid.Draw();
  currentBlock.Draw(11, 11);
  switch (nextBlock.id) {
  case 3:
    nextBlock.Draw(255, 290);
    break;
  case 4:
    nextBlock.Draw(255, 280);
    break;
  default:
    nextBlock.Draw(270, 270);
    break;
  }
}

/**
 * @brief Handles user input for controlling the game.
 *
 * Handles movement and rotation of the current block based on key presses.
 */
void Game::HandleInput() {
  if (CheckCollisionPointRec(GetMousePosition(), muteButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    isSoundMuted = !isSoundMuted;
    if (isSoundMuted) {
      PauseMusicStream(music);
    }
    else {
      ResumeMusicStream(music);
    }
  }

  if (IsKeyPressed(KEY_G)) {
    isSoundMuted = !isSoundMuted;
    if (isSoundMuted) {
      PauseMusicStream(music);
    }
    else {
      ResumeMusicStream(music);
    }
  }

  if (IsKeyPressed(KEY_P)) {
    TogglePause();
  }
  if (isPaused) {
    return;
  }

  if (gameOver && IsKeyDown(KEY_ENTER)) {
    gameOver = false;
    Reset();
  }

  if (KeySpam(0.09)) {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
      MoveBlockLeft();
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
      MoveBlockRight();
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
      MoveBlockDown();
      UpdateScore(0, 1);
    }
  }
  if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
    RotateBlock();
  }
}

/**
 * @brief Pauses the game.
 */
void Game::TogglePause() {
  isPaused = !isPaused;
}

/**
 * @brief Moves the current block to the left.
 *
 * Checks if the block can move left without going outside the grid or colliding with other blocks.
 */
void Game::MoveBlockLeft() {
  if (!gameOver) {
    currentBlock.Move(0, -1);
    if (IsBlockOutside() || !BlockFits()) {
      currentBlock.Move(0, 1);
    }
  }
}

/**
 * @brief Moves the current block to the right.
 *
 * Checks if the block can move right without going outside the grid or colliding with other blocks.
 */
void Game::MoveBlockRight() {
  if (!gameOver) {
    currentBlock.Move(0, 1);
    if (IsBlockOutside() || !BlockFits()) {
      currentBlock.Move(0, -1);
    }
  }
}

/**
 * @brief Moves the current block down.
 *
 * Checks if the block can move down without going outside the grid or colliding with other blocks.
 * If the block can't move further down, it locks the block in place.
 */
void Game::MoveBlockDown() {
  if (!gameOver) {
    currentBlock.Move(1, 0);
    if (IsBlockOutside() || !BlockFits()) {
      currentBlock.Move(-1, 0);
      LockBlock();
    }
  }
}

double lastUpdateTime = 0;

bool Game::EventTriggered(double interval) {
  double currentTime = GetTime();
  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  }
  return false;
}


double lastKeyPressed = 0;

bool Game::KeySpam(double interval) {
  double currentTime = GetTime();
  if (currentTime - lastKeyPressed >= interval) {
    lastKeyPressed = currentTime;
    return true;
  }
  return false;
}

/**
 * @brief Checks if the current block is outside the grid.
 *
 * @return true If the block is outside the grid.
 * @return false If the block is inside the grid.
 */
bool Game::IsBlockOutside() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles) {
    if (grid.IsCellOutside(item.row, item.column)) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Rotates the current block.
 *
 * Checks if the rotated block fits within the grid without colliding with other blocks.
 * If the rotation is not possible, it reverts the rotation.
 */
void Game::RotateBlock() {
  if (!gameOver) {
    currentBlock.Rotate();
    if (IsBlockOutside() || !BlockFits()) {
      currentBlock.UndoRotation();
    }
    // else {
    // PlaySound(rotateSound);
    // }
  }
}

/**
 * @brief Locks the current block in place on the grid.
 *
 * Checks for and clears full rows, updates the score accordingly, and sets the next block as the current block.
 */
void Game::LockBlock() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles) {
    grid.grid[item.row][item.column] = currentBlock.id;
  }
  currentBlock = nextBlock;
  if (!BlockFits()) {
    gameOver = true;
  }
  nextBlock = GetRandomBlock();
  int rowsCleared = grid.ClearFullRows();
  if (rowsCleared > 0) {
    PlaySound(clearSound);
    UpdateScore(rowsCleared, 0);
  }
}

/**
 * @brief Checks if the current block fits within the grid without colliding.
 *
 * @return true If the block fits.
 * @return false If the block does not fit.
 */
bool Game::BlockFits() {
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles) {
    if (!grid.IsCellEmpty(item.row, item.column)) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Resets the game to its initial state.
 *
 * Reinitializes the grid, resets the blocks, and sets the score to zero.
 */
void Game::Reset() {
  grid.Initialize();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  score = 0;
}

/**
 * @brief Updates the game score based on the number of lines cleared and points for moving down.
 *
 * @param linesCleared Number of lines cleared.
 * @param moveDownPoints Points awarded for moving the block down.
 */
void Game::UpdateScore(int linesCleared, int moveDownPoints) {
  switch (linesCleared) {
  case 1:
    score += 100;
    break;
  case 2:
    score += 300;
    break;
  case 3:
    score += 500;
    break;
  default:
    break;
  }

  score += moveDownPoints;
}
