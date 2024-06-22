#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int id;
    std::map<int, std::vector<Position>> cells;

private:
    ///< The size of each cell in the block.
    int cellSize;
    ///< The current rotation state of the block.
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
};
