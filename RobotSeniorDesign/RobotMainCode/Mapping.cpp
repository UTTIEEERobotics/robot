
#include <Arduino.h>
#include "Mapping.h"
#include "Field.h"

Cell_t initCellMap[FIELD_SIZE];
Cell_t finalCellMap[FIELD_SIZE];

void testData()
{
	//initCellMap[getIndex('3', 'A')].type = OT;
	//initCellMap[getIndex('3', 'A')].location = getIndex('3', 'A');


	initCellMap[getIndex('3', 'B')].type = OT;
	initCellMap[getIndex('3', 'B')].location = getIndex('3', 'B');

	initCellMap[getIndex('3', 'C')].type = OT;
	initCellMap[getIndex('3', 'C')].location = getIndex('3', 'C');

	initCellMap[getIndex('4', 'C')].type = OT;
	initCellMap[getIndex('4', 'C')].location = getIndex('4', 'C');

	//initCellMap[getIndex('5', 'D')].type = OT;
	//initCellMap[getIndex('5', 'D')].location = getIndex('5', 'D');

	initCellMap[getIndex('5', 'E')].type = OT;
	initCellMap[getIndex('5', 'E')].location = getIndex('5', 'E');

	initCellMap[getIndex('5', 'F')].type = OT;
	initCellMap[getIndex('5', 'F')].location = getIndex('5', 'F');

	//initCellMap[getIndex('5', 'C')].type = OT;
	//initCellMap[getIndex('5', 'C')].location = getIndex('5', 'C');

	initCellMap[getIndex('6', 'F')].type = OT;
	initCellMap[getIndex('6', 'F')].location = getIndex('6', 'F');

	//initCellMap[getIndex('7', 'F')].type = OT;
	//initCellMap[getIndex('7', 'F')].location = getIndex('7', 'F');
}

void mapInit()
{
	Cell_t initCell = {.type = SC, .location = 0}; 
	initCellMap[0] = initCell;
	initCell.type = FOAM;
	for(int i = 1; i < FIELD_SIZE; i++)
	{
		initCell.location = i;
		initCellMap[i] = initCell;
	}

	initCellMap[getIndex('7', 'A')].type = SC;
	initCellMap[getIndex('7', 'A')].location = getIndex('7', 'A');
	//testData();
}



Cell_t getCurrCell()
{
    return initCellMap[getCurrCellIndex()];
}

void setCurrCell(CellType_t type, uint8_t index)
{
    Cell_t cell = {.type = type, .location = index};
    initCellMap[getCurrCellIndex()] = cell;
}

void setCellRelative(CellType_t type, uint8_t relativeIndex)
{
	Cell_t cell = {.type = type, .location = getCurrCellIndex()+relativeIndex};
	initCellMap[getCurrCellIndex()+relativeIndex] = cell;
}

Cell_t getCellRelative(uint8_t relativeIndex)
{
	return initCellMap[getCurrCellIndex()+relativeIndex];
}

Cell_t * getInitCellMap()
{
	return initCellMap;
}