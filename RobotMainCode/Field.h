

#ifndef __FIELD_H__
#define __FIELD_H__

#define FIELD_SIZE                  49

#define LAST_CELL_INDEX             FIELD_SIZE - 1

#define ROW_INDEX                   0

#define COL_INDEX                   1

#define ASCII_LETTER_ZERO			'@'

#define ASCII_LETTER_H				'H'

#define ASCII_NUM_ZERO				'0'	


char getCurrRow();
char getCurrCol();
char getRow(uint8_t index);
char getCol(uint8_t index);
uint8_t getCurrCellIndex();
uint8_t getIndex(char row, char col);
void incCellIndex();
void decCellIndex();
void downRow();
void upRow();
bool isLastCell();

#endif                      
