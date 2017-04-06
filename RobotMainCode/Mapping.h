

#ifndef __MAPPING_H__
#define __MAPPING_H__

typedef enum{OT,OBS,DE,SC,FOAM,UNK} CellType_t;

typedef struct {
  CellType_t type;
  uint8_t location; 
}Cell_t;

void mapInit();
Cell_t getCurrCell();
void setCurrCell(CellType_t type, uint8_t index);
void setCellRelative(CellType_t type, uint8_t relativeIndex);
Cell_t getCellRelative(uint8_t relativeIndex);
Cell_t * getInitCellMap();
#endif
