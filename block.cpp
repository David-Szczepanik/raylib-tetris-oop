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
}


/**
 * @brief Draws the block at the specified offset.
 * @param offsetX The x-coordinate offset.
 * @param offsetY The y-coordinate offset.
 */
void Block::Draw(int offsetX, int offsetY) {
  // Get the positions of the cells in the block.
  std::vector<Position> tiles = GetCellPositions();

  // For each cell in the block...
  for (Position item : tiles) {
    // Draw a rectangle at the cell's position, with the color corresponding to the block's ID.
    DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1,
                  colors[id]);
  }
}

/**
 * @brief Moves the block by the specified number of rows and columns.
 * @param rows The number of rows to move the block by.
 * @param columns The number of columns to move the block by.
 */
void Block::Move(int rows, int columns) {
  // Increase the row offset by the specified number of rows.
  rowOffset += rows;
  // Increase the column offset by the specified number of columns.
  columnOffset += columns;
}

/**
 * @brief Returns the positions of the cells in the block, taking into account the current rotation state and offsets.
 * @return The list of moved tiles.
 */
std::vector<Position> Block::GetCellPositions() {
  // Get the positions of the cells in the current rotation state.
  std::vector<Position> tiles = cells[rotationState];
  // The positions of the cells after applying the offsets.
  std::vector<Position> movedTiles;
  // Look through all the tiles and add the offset to their positions.
  for (Position item : tiles) {
    // Calculate the new position of the cell.
    Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
    // Add the new position to the list of moved tiles.
    movedTiles.push_back(newPos);
  }
  // Return the list of moved tiles.
  return movedTiles;
}

/**
 * @brief Rotates the block to the next rotation state.
 */
void Block::Rotate() {
  // Increase the rotation state by 1.
  rotationState++;
  // If the rotation state is equal to the number of rotation states...
  if (rotationState == (int)cells.size())
  {
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
    if (rotationState == -1)
    {
        // Set the rotation state to the last rotation state.
        rotationState = cells.size() - 1;
    }
}
