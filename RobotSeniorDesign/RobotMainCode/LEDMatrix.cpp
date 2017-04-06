

#include <Adafruit_NeoPixel.h>
#include "Mapping.h"
#include "LEDMatrix.h"
#include "Field.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_MATRIX_SIZE, LED_MATRIX_PIN, NEO_GRB + NEO_KHZ800);

Cell_t ledCellMap[LED_MATRIX_SIZE];

const char lookUp[64][2]  =           { {'7', 'A'},{'6', 'A'},{'5', 'A'},{'4', 'A'},{'3', 'A'},{'2', 'A'},{'1', 'A'}, {'0', '8'},
										{'7', 'B'},{'6', 'B'},{'5', 'B'},{'4', 'B'},{'3', 'B'},{'2', 'B'},{'1', 'B'}, {'1', '15'},
										{'7', 'C'},{'6', 'C'},{'5', 'C'},{'4', 'C'},{'3', 'C'},{'2', 'C'},{'1', 'C'}, {'2', '23'},
										{'7', 'D'},{'6', 'D'},{'5', 'D'},{'4', 'D'},{'3', 'D'},{'2', 'D'},{'1', 'D'}, {'3', '31'},
										{'7', 'E'},{'6', 'E'},{'5', 'E'},{'4', 'E'},{'3', 'E'},{'2', 'E'},{'1', 'E'}, {'4', '39'},
										{'7', 'F'},{'6', 'F'},{'5', 'F'},{'4', 'F'},{'3', 'F'},{'2', 'F'},{'1', 'F'}, {'5', '47'},
										{'7', 'G'},{'6', 'G'},{'5', 'G'},{'4', 'G'},{'3', 'G'},{'2', 'G'},{'1', 'G'}, {'6', '55'},
										{'7', '56'},{'7', '57'},{'7', '58'},{'7', '59'},{'7', '60'},{'7', '61'},{'7', '62'}, {'7', '63'}};
void matrixInit()
{
	strip.begin();
	strip.setBrightness(LED_BRIGHTNESS); //0 to 255 max brights.
}

										
char getLookupRow(uint8_t index)
{
	return lookUp[index][0];
} 

char getLookupCol(uint8_t index)
{
	return lookUp[index][1];
} 

void showFinalCellMap()
{
	for(int i = 0; i < LED_MATRIX_SIZE; i++)
	{
		lightLED(i);
		strip.show();
	}
}

void lightMatrix()
{
	ledMatrixInit();
	getCellMapInitial();
	showFinalCellMap();
	delay(2000);
	getFinalCellMap();
	showFinalCellMap();
}

void ledMatrixInit() 
{ 

	Cell_t* cellMapInitial = getInitCellMap();
	uint8_t ledIndex; 

	for (int i=0; i<8; i++)
	{ 
		for (int j=0; j<8; j++)
		{ 
			ledIndex = getLedIndex(j, i); 

			if( i > 6 || j > 6)
			{
				ledCellMap[ledIndex].type = FOAM;
				ledCellMap[ledIndex].location = NULL;
			}
			else
			{
				
				uint8_t cellIndex = getIndex(getLookupRow(ledIndex), getLookupCol(ledIndex));
				ledCellMap[ledIndex].type = cellMapInitial[cellIndex].type;
				ledCellMap[ledIndex].location = cellMapInitial[cellIndex].location;
				lightLED[ledIndex];
			}    
		}
	}
} 

void getFinalCellMap()
{  
	uint8_t ledIndex;

	for (int j = 1; j < 7; j++) 
	{               
		for (int i = 1; i < 7; i++)
		{
			analysis(i, j);
		}
	} 

	printCellMap();

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			fixEndpoints(i, j);
		}
	}
   
    printCellMap(); 
}

uint8_t getLedIndexJohn(uint8_t column, uint8_t row)
{
	uint8_t index;
	index = column * 8 + row;
	if(index >= 0 && index < LED_MATRIX_SIZE)
	{
		return index;
	}
	else
	{
		return 0;
	}
}


void getCellMapInitial()
{
	uint8_t ledIndex;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			ledIndex = getLedIndexJohn(i,j);
		}
	}
	printCellMap();
}

uint8_t getFieldIndex()
{
	for(int i = LED_MATRIX_SIZE-1; i >= 0; i--)
	{
		if(ledCellMap[i].type == OT)
		{
			char row = getLookupRow(i);
			char col = getLookupCol(i);

			Serial.print("\nPossible Cache\t");
			Serial.print(row);
			Serial.println(col);

			if(row == '7' || row == '1' || col == 'A' || col == 'G')
			{
				Serial.print("\nCache Found\t");
				Serial.print(getIndex(row,col));
				Serial.print("\t");
				Serial.print(row);
				Serial.println(col);
				return getIndex(row, col);
			}
		}
	}
}

void lightLED(uint8_t ledIndex)
{
	switch (ledCellMap[ledIndex].type)
	{                    
		case OT:                                
			strip.setPixelColor(ledIndex, 255,0, 0);  //red LED
		break;

		case DE:                                
			strip.setPixelColor(ledIndex, 0, 0, 255);    //blue LED
		break;

		case OBS:                              
			strip.setPixelColor(ledIndex, 0, 255, 0);   //green LED
		break;

		case SC:                                
			strip.setPixelColor(ledIndex, 255, 255, 0);  //yellow LED
		break;

		case FOAM:
			//strip.setPixelColor(ledIndex, 225, 80, 140);  //pink LED
		break;

		case UNK:
			strip.setPixelColor(ledIndex, 255,0, 0);  //red LED
		break;

		default:
			Serial.println("invalid cell value at cell[");
		break; 
	}   
} 

void lightReady()
{
	strip.setPixelColor(0, 255, 255, 0);  //yellow LED
	strip.show();
}

uint8_t getLedIndex(uint8_t row, uint8_t column) 
{
	uint8_t index;
	index = column * 8 + row;
	return index;
}

uint8_t getLedIndexCellMap(uint8_t row, uint8_t column, uint8_t location)
{
	uint8_t index;
	char fieldRow = getRow(location);

	switch (fieldRow)
	{
		case 'A': case 'C': case 'E': case 'G':
			index = column * 8 + row;
		break;

		case 'B': case 'D': case 'F':
			index = (column * 8 + row);
		break;

		default:
		break;
	}
	index = column * 8 + row;
	return index;
} 

void printCellMap() 
{
	Serial.println("\nprintCellMap()");
	for (int i = 0; i < 8; i++)
	{
		Serial.print("\n");
		for (int j = 0; j < 8; j++)
		{
			printCellType(ledCellMap[getLedIndex(i, j)].type);
		}
	}
	Serial.println();
 }

void printCellType(CellType_t type) 
{
	switch (type) 
	{
		case OT: 
			Serial.print("\tOT"); 
		break;

		case OBS: 
			Serial.print("\tOBS"); 
		break;

		case DE: 
			Serial.print("\tDE"); 
		break;

		case SC: 
			Serial.print("\tSC"); 
		break;

		case FOAM: 
			Serial.print("\tFOAM"); 
		break;

		case UNK:
			Serial.print("\tUNK");
		break;

		default: 
			Serial.print("\t?");
			Serial.print(type); 
		break;
	}
}

void analysis(uint8_t i, uint8_t j)
{
	if (ledCellMap[getLedIndex(i, j)].type == FOAM)
	{
		////////////////////////////////////////////////////////////////////////////
		//If FOAM cell has an OT on the left and Right and FOAM on the top and bottom
		//or
		//IF FOAM cell has an OT on the top and bottom and FOAM on the top and bottom
		///////////////////////////////////////////////////////////////////////////
		if (((ledCellMap[getLedIndex(i, j - 1)].type == OT) && (ledCellMap[getLedIndex(i, j + 1)].type == OT) && (ledCellMap[getLedIndex(i - 1, j)].type == FOAM) && (ledCellMap[getLedIndex(i + 1, j)].type == FOAM)) || ((ledCellMap[getLedIndex(i, j - 1)].type == FOAM) && (ledCellMap[getLedIndex(i, j + 1)].type == FOAM) && (ledCellMap[getLedIndex(i - 1, j)].type == OT) && (ledCellMap[getLedIndex(i + 1, j)].type == OT)))
		{
			ledCellMap[getLedIndex(i, j)].type = OT;
		}
		////////////////////////////////////////////////////////////////////////////
		//If the OT has a right angle
		///////////////////////////////////////////////////////////////////////////
		else if (
			// left=FOAM, right=OT, up=OT, down=FOAM, and right-up=FOAM
			((ledCellMap[getLedIndex(i, j - 1)].type == FOAM) && (ledCellMap[getLedIndex(i, j + 1)].type == OT) && (ledCellMap[getLedIndex(i - 1, j)].type == OT) && (ledCellMap[getLedIndex(i + 1, j)].type == FOAM) && (ledCellMap[getLedIndex(i - 1, j + 1)].type == FOAM)) ||

			// left=FOAM, right=OT, up=FOAM, down=OT,   and right-down=FOAM
			((ledCellMap[getLedIndex(i, j - 1)].type == FOAM) && (ledCellMap[getLedIndex(i, j + 1)].type == OT) && (ledCellMap[getLedIndex(i - 1, j)].type == FOAM) && (ledCellMap[getLedIndex(i + 1, j)].type == OT) && (ledCellMap[getLedIndex(i + 1, j + 1)].type == FOAM)) ||

			// left=OT, right=FOAM, up=OT, down=FOAM,  and left-up=FOAM
			((ledCellMap[getLedIndex(i, j - 1)].type == OT) && (ledCellMap[getLedIndex(i, j + 1)].type == FOAM) && (ledCellMap[getLedIndex(i - 1, j)].type == OT) && (ledCellMap[getLedIndex(i + 1, j)].type == FOAM) && (ledCellMap[getLedIndex(i - 1, j - 1)].type == FOAM)) ||

			// left=OT, right=FOAM, up=FOAM, down=OT, and left-down=FOAM
			((ledCellMap[getLedIndex(i, j - 1)].type == OT) && (ledCellMap[getLedIndex(i, j + 1)].type == FOAM) && (ledCellMap[getLedIndex(i - 1, j)].type == FOAM) && (ledCellMap[getLedIndex(i + 1, j)].type == OT) && (ledCellMap[getLedIndex(i + 1, -1)].type == FOAM))
			)
		{
			ledCellMap[getLedIndex(i, j)].type = UNK;	//makes a guess 
		}
	}
}//end of Analysis Method 


void fixEndpoints(uint8_t i, uint8_t j)
{
	
	Serial.println("\nfixEndpoint()");

	uint8_t adjOT = 0;
	uint8_t diagOT = 0;
	Cell_t currCell = ledCellMap[getLedIndexJohn(i, j)];

	char currRow = getRow(currCell.location);
	char currCol = getCol(currCell.location);

	Serial.print("\nFixing Cell:\t");
	Serial.print(currRow);
	Serial.print(currCol);
	Serial.print("\tat Location:\t");
	Serial.println(currCell.location);

	if( (currRow != '1') && (currRow != '7') && (currCol != 'A') && (currCol != 'G') && currCell.type == OT)
	{
		uint8_t eastIndex = getLedIndexJohn(i+1, j);
		uint8_t westIndex = getLedIndexJohn(i-1, j);
		uint8_t northIndex = getLedIndexJohn(i, j+1);
		uint8_t southIndex = getLedIndexJohn(i, j-1);

		uint8_t northEastIndex = getLedIndexJohn(i+1, j+1);
		uint8_t northWestIndex = getLedIndexJohn(i-1, j+1);

		uint8_t southEastIndex = getLedIndexJohn(i+1, j-1);
		uint8_t southWestIndex = getLedIndexJohn(i-1, j-1);


		Cell_t east = ledCellMap[eastIndex];
		Cell_t west = ledCellMap[westIndex];
		Cell_t north = ledCellMap[northIndex];
		Cell_t south = ledCellMap[southIndex];

		Cell_t northWest = ledCellMap[northWestIndex];
		Cell_t northEast = ledCellMap[northEastIndex];

		Cell_t southWest = ledCellMap[southWestIndex];
		Cell_t southEast = ledCellMap[southEastIndex];


		if(west.type == OT)
		{
			Serial.print("\nWest Cell:\t");
			Serial.print(getRow(west.location));
			Serial.print(getCol(west.location));
			Serial.println("\tis OT");
			adjOT++;
		}

		if(east.type == OT)
		{
			Serial.print("\nEast Cell:\t");
			Serial.print(getRow(east.location));
			Serial.print(getCol(east.location));
			Serial.println("\tis OT");
			adjOT++;
		}

		if(north.type == OT)
		{
			Serial.print("\nNorth Cell:\t");
			Serial.print(getRow(north.location));
			Serial.print(getCol(north.location));
			Serial.println("\tis OT");
			adjOT++;
		}

		if(south.type == OT)
		{
			Serial.print("\nSouth Cell:\t");
			Serial.print(getRow(south.location));
			Serial.print(getCol(south.location));
			Serial.println("\tis OT");
			adjOT++;
		}

		Serial.print("\nNumber of adjacent OT's:\t");
		Serial.println(adjOT);

		if(northWest.type == OT)
		{
			Serial.print("\nNorth West Cell:\t");
			Serial.print(getRow(northWest.location));
			Serial.print(getCol(northWest.location));
			Serial.println("\tis OT");
			diagOT++;
		}

		if(southEast.type == OT)
		{
			Serial.print("\nSouth East Cell:\t");
			Serial.print(getRow(southEast.location));
			Serial.print(getCol(southEast.location));
			Serial.println("\tis OT");
			diagOT++;
		}

		if(northEast.type == OT)
		{
			Serial.print("\nNorth East Cell:\t");
			Serial.print(getRow(northEast.location));
			Serial.print(getCol(northEast.location));
			Serial.println("\tis OT");
			diagOT++;
		}

		if(southWest.type == OT)
		{
			Serial.print("\nSouth West Cell:\t");
			Serial.print(getRow(southWest.location));
			Serial.print(getCol(southWest.location));
			Serial.println("\tis OT");
			diagOT++;
		}

		Serial.print("\nNumber of diagonal OT's:\t");
		Serial.println(diagOT);

		switch (adjOT)
		{
			case 1:
			switch(currCell.location)
			{
				//Cell 6F
				case 8:
				Serial.println("\nChecking cell 6F");
				if(north.type == OT)
				{
					ledCellMap[southIndex].type = UNK;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(south.location));
					Serial.print(getCol(south.location));
					Serial.println("\tto OT");
				}
				else if (west.type == OT)
				{
					ledCellMap[eastIndex].type = UNK;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(east.location));
					Serial.print(getCol(east.location));
					Serial.println("\tto OT");
				}
				break;

				//Cell 6B
				case 12:
				Serial.println("\nChecking cell 6B");
				if(north.type == OT)
				{
					ledCellMap[southIndex].type = UNK;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(south.location));
					Serial.print(getCol(south.location));
					Serial.println("\tto OT");
				}
				else if (east.type == OT)
				{
					ledCellMap[westIndex].type = UNK;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(west.location));
					Serial.print(getCol(west.location));
					Serial.println("\tto OT");
				}
				break;

				//Cell 2B
				case 40:
				Serial.println("\nChecking cell 2B");
				if(south.type == OT)
				{
					ledCellMap[northIndex].type = UNK;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(north.location));
					Serial.print(getCol(north.location));
					Serial.println("\tto OT");
				}
				else if (east.type == OT)
				{
					ledCellMap[westIndex].type = UNK;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(east.location));
					Serial.print(getCol(east.location));
					Serial.println("\tto OT");
				}
				break;

				//Cell 2F
				case 36:
				Serial.println("\nChecking cell 2F");
				if(south.type == OT)
				{
					ledCellMap[northIndex].type = UNK;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(north.location));
					Serial.print(getCol(north.location));
					Serial.println("\tto OT");
				}
				else if (west.type == OT)
				{
					ledCellMap[eastIndex].type = UNK;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(west.location));
					Serial.print(getCol(west.location));
					Serial.println("\tto OT");
				}
				break;

				default:
				if(getCol(west.location) == 'A' && diagOT < 2)
				{
					ledCellMap[westIndex].type = OT;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(west.location));
					Serial.print(getCol(west.location));
					Serial.println("\tto OT");
				}
				else if(getCol(east.location) == 'G' && diagOT < 2)
				{
					ledCellMap[eastIndex].type = OT;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(east.location));
					Serial.print(getCol(east.location));
					Serial.println("\tto OT");
				}
				else if(getRow(north.location) == '1' && diagOT < 2)
				{
					ledCellMap[northIndex].type = OT;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(north.location));
					Serial.print(getCol(north.location));
					Serial.println("\tto OT");
				}
				else if(getRow(south.location) == '7' && diagOT < 2)
				{
					ledCellMap[southIndex].type = OT;
					Serial.print("\nChanged Cell:\t");
					Serial.print(getRow(south.location));
					Serial.print(getCol(south.location));
					Serial.println("\tto OT");
				}
				break;
			}
			break;

			case 2:
			break;

			case 3:
			break;

			case 4:
			break;

			default:
			break;
		}

	}
	else
	{
		Serial.println("\nPerimeter Cell or not OT");
	}
}