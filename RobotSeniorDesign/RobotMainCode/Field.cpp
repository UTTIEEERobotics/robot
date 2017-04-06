
#include <Arduino.h>
#include "GlobalDefines.h"
#include "Field.h"

const char field[49][2]  =         {{'7', 'A'},{'7', 'B'},{'7', 'C'},{'7', 'D'},{'7', 'E'},{'7', 'F'},{'7', 'G'},
									{'6', 'G'},{'6', 'F'},{'6', 'E'},{'6', 'D'},{'6', 'C'},{'6', 'B'},{'6', 'A'},
									{'5', 'A'},{'5', 'B'},{'5', 'C'},{'5', 'D'},{'5', 'E'},{'5', 'F'},{'5', 'G'},
									{'4', 'G'},{'4', 'F'},{'4', 'E'},{'4', 'D'},{'4', 'C'},{'4', 'B'},{'4', 'A'},
									{'3', 'A'},{'3', 'B'},{'3', 'C'},{'3', 'D'},{'3', 'E'},{'3', 'F'},{'3', 'G'},
									{'2', 'G'},{'2', 'F'},{'2', 'E'},{'2', 'D'},{'2', 'C'},{'2', 'B'},{'2', 'A'},
									{'1', 'A'},{'1', 'B'},{'1', 'C'},{'1', 'D'},{'1', 'E'},{'1', 'F'},{'1', 'G'}};

volatile uint8_t  currCellIndex = getIndex('7','A');

uint8_t getCurrCellIndex()
{
    return currCellIndex;
}

char getCurrRow()
{
    return field[currCellIndex][ROW_INDEX];
}

char getCurrCol()
{
    return field[currCellIndex][COL_INDEX];
}

char getRow(uint8_t index)
{
	return field[index][ROW_INDEX];
}

char getCol(uint8_t index)
{
	return field[index][COL_INDEX];
}

uint8_t getIndex(char row, char col)
{
	for(int i = 0; i < FIELD_SIZE; i++)
	{
		if(field[i][ROW_INDEX] == row && col == field[i][COL_INDEX])
		{
			return i;
		}
	}
	
	return -1;
}

void incCellIndex()
{
    currCellIndex++;
    if(ENABLE_LOG_FIELD)
    {
        Serial.print("\nCurrent Cell:\t");
        Serial.print(getCurrRow());
        Serial.println(getCurrCol());
    }
}

void decCellIndex()
{
    currCellIndex--;
    if(ENABLE_LOG_FIELD)
    {
        Serial.print("\nCurrent Cell:\t");
        Serial.print(getCurrRow());
        Serial.println(getCurrCol());
    }
}

void downRow()
{
	switch (getCurrRow())
	{
		case '5': case '3': case '1':
		currCellIndex -= (8-(ASCII_LETTER_H - getCurrCol()))*2 - 1;
		break;
		
		case '6': case '4': case '2':
		currCellIndex -= (ASCII_LETTER_H - getCurrCol())*2 - 1;
		break;
		
		default:
		if(ENABLE_LOG_UTILS)
		{
			Serial.println("\n----------ERROR IN avoidObs()-----------\n");
		}
		break;
	}
    if(ENABLE_LOG_FIELD)
    {
        Serial.print("\nCurrent Cell:\t");
        Serial.print(getCurrRow());
        Serial.println(getCurrCol());
    }
}

void upRow()
{
	switch (getCurrRow())
	{
		case '7': case '5': case '3':
		currCellIndex += (ASCII_LETTER_H - getCurrCol())*2 - 1;
		break;
		
		case '2': case '4': case '6':
		currCellIndex += (8-(ASCII_LETTER_H - getCurrCol()))*2 - 1;
		break;
		
		default:
		if(ENABLE_LOG_UTILS)
		{
			Serial.println("\n----------ERROR IN avoidObs()-----------\n");
		}
		break;
	}
    if(ENABLE_LOG_FIELD)
    {
        Serial.print("\nCurrent Cell:\t");
        Serial.print(getCurrRow());
        Serial.println(getCurrCol());
    }
}

bool isLastCell()
{
    return !(currCellIndex < LAST_CELL_INDEX);
}

