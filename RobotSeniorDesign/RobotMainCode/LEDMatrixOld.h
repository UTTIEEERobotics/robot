

#define LED_MATRIX_PIN			6
#define LED_MATRIX_SIZE			64
#define LED_BRIGHTNESS			5

void matrixInit();
void lightReady();
void lightMatrix();
void ledMatrixInit();
void getFinalCellMap();
void checkForObstacle();
void getCellMapInitial();
uint8_t getFieldIndex();
uint8_t getLedIndex(uint8_t column, uint8_t row);
uint8_t getLedIndexCellMap(uint8_t row, uint8_t column, uint8_t location);
void analysis(uint8_t i, uint8_t j);
void lightLED(uint8_t ledIndex);
void printCellMap();
void printCellType(CellType_t type);
void fixEndpoints(uint8_t i, uint8_t j);
void showFinalCellMap();
