/**
 * @file block.cpp
 * @brief Implementation of the Block class.
 */
#include "block.h"

/**
 * @brief Default constructor for the Block class.
 * Initializes the cell size, rotation state, colors, and offsets.
 */
Block::Block() {
  // The size of each cell in the block.
  cellSize = 30;
  // The current rotation state of the block.
  rotationState = 0;
  // The colors of the cells in the block.
  colors = GetCellColors();
  // The row offset of the block.
  rowOffset = 0;
  // The column offset of the block.
  columnOffset = 0;
  id = 0;
}


/**
 * @brief Draws the block at the specified position.
 * @param offsetX The x-coordinate offset.
 * @param offsetY The y-coordinate offset.
 */
void Block::Draw(int offsetX, int offsetY) {
  // Get the positions of the cells in the block.
  std::vector<Position> tiles = GetCellPositions();

  for (Position item : tiles) {
    DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1,
                  colors[id]);
  }
}

/**
 * @brief Moves the block by the specified number of rows and columns.
 * @param rows Number of ROWS to move the block.
 * @param columns Number of COLUMNS to move the block.
 */
void Block::Move(int rows, int columns) {
  rowOffset += rows;
  columnOffset += columns;
}

/**
 * @brief Returns POSITION and ROTATION of blocks.
 * @return List of moved tiles.
 */
std::vector<Position> Block::GetCellPositions() {
  // Get positions of cells for current rotation.
  std::vector<Position> tiles = cells[rotationState];
  // The positions of the cells after applying the offsets.
  std::vector<Position> movedTiles;
  // Look through all the tiles and add the offset to their positions.
  for (Position item : tiles) {
    // Calculate the new position of the cell.
    Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
    // Add new position to end of the list of moved tiles.
    movedTiles.push_back(newPos);
  }
  return movedTiles;
}

/**
 * @brief Rotates the block.
 */
void Block::Rotate() {
  rotationState++;
  // If the rotation state is equal to the number of rotation states...
  if (rotationState == static_cast<int>(cells.size())) {
    // Reset the rotation state to 0.
    rotationState = 0;
  }
}

/**
 * @brief Rotates the block to the previous rotation state.
 */
void Block::UndoRotation() {
  // Decrease the rotation state by 1.
  rotationState--;
  // If the rotation state is -1...
  if (rotationState == -1) {
    // Set the rotation state to the last rotation state.
    rotationState = static_cast<int>(cells.size()) - 1;
  }
}
