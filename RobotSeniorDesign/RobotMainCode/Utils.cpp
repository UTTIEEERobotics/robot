
#include "Utils.h"

void utilInit()
{
    ussInit();
    motorInit();
    liveWireInit();
    piCommInit();
	mapInit();	
	matrixInit();
	grabberInit();
	camereLedInit();
}

void fixDistDiffFront()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nfixDistDiffFront()");
    }
    float distDiff = getFrontDiff();
    
    while( abs(distDiff) > MAX_DIST_DIFF )
    { 
        if(distDiff > 0)
        {
            cw(STEP_ANGLE);
        }
        else if(distDiff < 0)
        {
            ccw(STEP_ANGLE);
        }
        
        delay(SAMPLE_DELAY);
        
        distDiff = getFrontDiff();
             
    }
}

void fixDistDiffBack()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nfixDistDiffFBack()");
    }
    
    float distDiff = getBackDiff();
    
    while( abs(distDiff) > MAX_DIST_DIFF )
    { 
        if(distDiff > 0)
        {
            ccw(STEP_ANGLE);
        }
        else if(distDiff < 0)
        {
            cw(STEP_ANGLE);
        }
        
        delay(SAMPLE_DELAY);
        
        distDiff = getBackDiff();
              
    }
}

void fixDistLeft()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nfixDistLeft()");
    }
	bool dir = true;
	bool lastDir = dir;
    int count = 0;
    float setDist = 12 * (getCurrRow() - '1');

    float distDiff = distL()-setDist;

    if(ENABLE_LOG_UTILS)
    {
        Serial.print("\nLeft Distance Set Point: ");
        Serial.println(setDist);           
        Serial.print("\nLeft Distance Difference: ");
        Serial.println(distDiff);
    }
    
    while( abs(distDiff) > MIN_DIST_DIFF_SIDE )
    { 
        if(distDiff > 0)
        {	
			dir = true;
            left(STEP_DIST);
        }
        else if(distDiff < 0)
        {
			dir = false;
            right(STEP_DIST);
        }
        
        delay(SAMPLE_DELAY);
        
        distDiff = distL()-setDist;

        if(ENABLE_LOG_UTILS)
        {
            Serial.print("\nLeft Distance Set Point: ");
            Serial.println(setDist);           
            Serial.print("\nLeft Distance Difference: ");
            Serial.println(distDiff);
        }
		
		if(dir != lastDir)
		{
			count++;
		}

		lastDir = dir;
		
		if(count > MAX_STEP_COUNT)
		{
			break;
		}     
    }
}

void fixDistLeftCol()
{
	if(ENABLE_LOG_UTILS)
	{
		Serial.println("\nfixDistLeftCol()");
	}
	
	bool dir = true;
	bool lastDir = dir;
	int count = 0;

	float setDist = 0;

	float distDiff = distL()-setDist;

	if(ENABLE_LOG_UTILS)
	{
		Serial.print("\nLeft Distance Set Point: ");
		Serial.println(setDist);
		Serial.print("\nLeft Distance Difference: ");
		Serial.println(distDiff);
	}

	while( abs(distDiff) > MIN_DIST_DIFF_SIDE )
	{
		if(distDiff > 0)
		{
			dir = true;
			left(STEP_DIST);
		}
		else if(distDiff < 0)
		{
			dir = false;
			right(STEP_DIST);
		}
		
		delay(SAMPLE_DELAY);
		
		distDiff = distL()-setDist;

		if(ENABLE_LOG_UTILS)
		{
			Serial.print("\nLeft Distance Set Point: ");
			Serial.println(setDist);
			Serial.print("\nLeft Distance Difference: ");
			Serial.println(distDiff);
		}

		if(dir != lastDir)
		{
			count++;
		}

		lastDir = dir;
		
		if(count > MAX_STEP_COUNT)
		{
			break;
		}
		
	}
}

void fixDistRight()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nfixDistRight()");
    }
    
	bool dir = true;
	bool lastDir = dir;
	int count = 0;

    float setDist = 12 * ('7' - getCurrRow());

    float distDiff = distR()-setDist;

    if(ENABLE_LOG_UTILS)
    {
        Serial.print("\nRight Distance Set Point: ");
        Serial.println(setDist);
        Serial.print("\nRight Distance Difference: ");
        Serial.println(distDiff);
    }

	 while( abs(distDiff) > MIN_DIST_DIFF_SIDE )
	 {
		if(distDiff > 0)
		{
			dir = true;
			right(STEP_DIST);
		}
		else if(distDiff < 0)
		{
			dir = true;
			left(STEP_DIST);
		}
		 
		delay(SAMPLE_DELAY);
		 
		distDiff = distR()-setDist;

		if(ENABLE_LOG_UTILS)
		{
			Serial.print("\nRight Distance Set Point: ");
			Serial.println(setDist);
			Serial.print("\nRight Distance Difference: ");
			Serial.println(distDiff);
		}

		if(dir != lastDir)
		{
			count++;
		}

		lastDir = dir;
		 
		if(count > MAX_STEP_COUNT)
		{
			break;
		}
	 }
}

void fixDistRightCol()
{
	if(ENABLE_LOG_UTILS)
	{
		Serial.println("\nfixDistRightCol()");
	}
	
	bool dir = true;
	bool lastDir = dir;
	int count = 0;

	float setDist = 0;

	float distDiff = distR()-setDist;

	if(ENABLE_LOG_UTILS)
	{
		Serial.print("\nRight Distance Set Point: ");
		Serial.println(setDist);
		Serial.print("\nRight Distance Difference: ");
		Serial.println(distDiff);
	}

    while( abs(distDiff) > MIN_DIST_DIFF_SIDE )
    { 
        if(distDiff > 0)
        {
            dir = true;
            right(STEP_DIST);
        }
        else if(distDiff < 0)
        {
			dir = false;
            left(STEP_DIST);
        }
        
        delay(SAMPLE_DELAY);
        
        distDiff = distR()-setDist;

        if(ENABLE_LOG_UTILS)
        {
            Serial.print("\nRight Distance Set Point: ");
            Serial.println(setDist);
            Serial.print("\nRight Distance Difference: ");
            Serial.println(distDiff);
        } 
		
		if(dir != lastDir)
		{
			count++;
		}

		lastDir = dir;
		
		if(count > MAX_STEP_COUNT)
		{
			break;
		}     
    }
}

void fixDistFront()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nfixDistFront()");
    }

	bool dir = true;
	bool lastDir = dir;
	int count = 0;

    float setDist = 12 * ('G' - getCurrCol());

    float distDiff = distFR()-setDist;

    if(ENABLE_LOG_UTILS)
    {
        Serial.print("\nFront Distance Set Point: ");
        Serial.println(setDist);
        Serial.print("\nFront Distance Difference: ");
        Serial.println(distDiff); 
    }

    while( abs(distDiff) > MIN_DIST_DIFF )
    { 
        if(distDiff > 0)
        {
			dir = true;
            forward(STEP_DIST);
        }
        else if(distDiff < 0)
        {
			dir = false;
            backward(STEP_DIST);
        }
        
        delay(SAMPLE_DELAY);
        
        distDiff = distFR()-setDist;

        if(ENABLE_LOG_UTILS)
        {
            Serial.print("\nFront Distance Set Point: ");
            Serial.println(setDist);           
            Serial.print("\nFront Distance Difference: ");
            Serial.println(distDiff);
        }

		if(dir != lastDir)
		{
			count++;
		}

		lastDir = dir;
		
		if(count > MAX_STEP_COUNT)
		{
			break;
		}
              
    }
}

void fixDistFrontCol()
{
	if(ENABLE_LOG_UTILS)
	{
		Serial.println("\nfixDistFront()");
	}

	bool dir = true;
	bool lastDir = dir;
	int count = 0;

	float setDist = 12 * ('7' - getCurrRow());

	float distDiff = distFR()-setDist;

	if(ENABLE_LOG_UTILS)
	{
		Serial.print("\nFront Distance Set Point: ");
		Serial.println(setDist);
		Serial.print("\nFront Distance Difference: ");
		Serial.println(distDiff);
	}
	
	while( abs(distDiff) > MIN_DIST_DIFF )
	{
		if(distDiff > 0)
		{
			dir = true;
			forward(STEP_DIST);
		}
		else if(distDiff < 0)
		{
			dir = false;
			backward(STEP_DIST);
		}
		
		delay(SAMPLE_DELAY);
		
		distDiff = distFR()-setDist;

		if(ENABLE_LOG_UTILS)
		{
			Serial.print("\nFront Distance Set Point: ");
			Serial.println(setDist);
			Serial.print("\nFront Distance Difference: ");
			Serial.println(distDiff);
		}

		if(dir != lastDir)
		{
			count++;
		}

		lastDir = dir;
		
		if(count > MAX_STEP_COUNT)
		{
			break;
		}
		
	}
}

void fixDistBack()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nfixDistBack()");
    }
    
	bool dir = true;
	bool lastDir = dir;
	int count = 0;

    float setDist = 12 * (getCurrCol()-'A');

    float distDiff = distBR()-setDist;

    if(ENABLE_LOG_UTILS)
    {
        Serial.print("\nBack Distance Set Point: ");
        Serial.println(setDist);
        Serial.print("\nBack Distance Difference: ");
        Serial.println(distDiff); 
    }

    while( abs(distDiff) > MIN_DIST_DIFF)
    { 
        if(distDiff > 0)
        {	
			dir = true;
            backward(STEP_DIST);
        }
        else if(distDiff < 0)
        {
			dir = false;
            forward(STEP_DIST);
        }
        
        delay(SAMPLE_DELAY);
        
        distDiff = distBR()-setDist;

        if(ENABLE_LOG_UTILS)
        {
            Serial.print("\nBack Distance Set Point: ");
            Serial.println(setDist);           
            Serial.print("\nBack Distance Difference: ");
            Serial.println(distDiff);
        }

		if(dir != lastDir)
		{
			count++;
		}

		lastDir = dir;
		
		if(count > MAX_STEP_COUNT)
		{
			break;
		}
              
    }
}

void fixDistBackCol()
{
	if(ENABLE_LOG_UTILS)
	{
		Serial.println("\nfixDistBack()");
	}

	bool dir = true;
	bool lastDir = dir;
	int count = 0;
	
	float setDist = 12 * (getCurrRow()-'1');

	float distDiff = distBR()-setDist;

	if(ENABLE_LOG_UTILS)
	{
		Serial.print("\nBack Distance Set Point: ");
		Serial.println(setDist);
		Serial.print("\nBack Distance Difference: ");
		Serial.println(distDiff);
	}

	while( abs(distDiff) > MIN_DIST_DIFF)
	{
		if(distDiff > 0)
		{
			dir = true;
			backward(STEP_DIST);
		}
		else if(distDiff < 0)
		{
			dir = false;
			forward(STEP_DIST);
		}
		
		delay(SAMPLE_DELAY);
		
		distDiff = distBR()-setDist;

		if(ENABLE_LOG_UTILS)
		{
			Serial.print("\nBack Distance Set Point: ");
			Serial.println(setDist);
			Serial.print("\nBack Distance Difference: ");
			Serial.println(distDiff);
		}

		if(dir != lastDir)
		{
			count++;
		}

		lastDir = dir;
		
		if(count > MAX_STEP_COUNT)
		{
			break;
		}
		
	}
}

void nextCell()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nnextCell()");
    }
       
    if(!isLastCell())
    {
        char row = getCurrRow();
        char col = getCurrCol();

        switch (row)
        {
            case '1': case '3': case '5': case '7':
                switch (col)
                {
                    case 'G':
						backward(3);
						delay(100);
						left(1);
						delay(100);
						ccw(90);
						forward(12);
						cw(90);
						forward(1.5);

                    break;
    
                    case 'A': case 'B': case 'C': case 'D': case 'E':
                        forward(CELL_DIST);
                    break;

					case 'F':
						forward(CELL_DIST - 1.5);
					break;

                    default:
                        if(ENABLE_LOG_UTILS)
                        {
                            Serial.println("\n----------ERROR IN nextCell()-----------\n");
                        }
                    break;
                }
            break;
            
            case '2': case '4': case '6':
                switch (col)
                {
                    case 'A':
						forward(3);
						delay(100);
						left(1);
						delay(100);
						ccw(90);
						forward(12);
						cw(90);
						backward(1.5);

                    break;
    
                    case 'C': case 'D': case 'E': case 'F': case 'G':
                        backward(CELL_DIST);
                    break;

					case 'B':
						backward(CELL_DIST - 1.5); 
					break;
                        
                    default:
                        if(ENABLE_LOG_UTILS)
                        {
                            Serial.println("\n----------ERROR IN nextCell()-----------\n");
                        }
                    break;
                }
            break;
            
            default:
                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\n----------ERROR IN nextCell()-----------\n");
                }
            break;
        }

        incCellIndex();

		adjustOrientation();
		adjustSidePosition();
		adjustFrontBackPosition();

        if(ENABLE_LOG_UTILS)
        {
            char newRow = getCurrRow();
            char newCol = getCurrCol();

            Serial.print("\nMoved from cell ");
            Serial.print(row);
            Serial.print(col);
            Serial.print(" to cell ");
            Serial.print(newRow);
            Serial.println(newCol);
            Serial.println();
        }
    }
}


void adjustOrientation()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nadjustOrientation()");
    }
    
    if(!isLastCell())
    {
        char col = getCurrCol();
        
        switch (col)
        {
            case 'A': case 'D': case 'G':
                break;
    
            case 'B': case 'C':
                fixDistDiffBack();
                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\nFixed Angle with Front");
                }
            break;
    
            case 'E': case 'F':
                fixDistDiffFront();

                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\nFixed Angle with Back");
                }
            break;
    
            default:
                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\n----------ERROR IN adjustOrientation()-----------\n");
                }
            break;
        }
    }
}


void adjustSidePosition()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nadjustSidePosition()");
    }
    if(!isLastCell())
    {
        char row = getCurrRow();

        switch (row)
        {

            case '7': case '6': case '5': case '4':
                fixDistRight();
                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\nLeft Adjust Done");
                }
             break;
            
            case '3': case '2': case '1':
                fixDistLeft();
                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\nRight Adjust Done");
                }
            break;
            
            default:
                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\n----------ERROR IN nextCell()-----------\n");
                }
            break;
        }
    }
}

void adjustFrontBackPosition()
{
    if(ENABLE_LOG_UTILS)
    {
        Serial.println("\nadjustFrontBackPosition()");
    }
    if(!isLastCell())
    {
        char col = getCurrCol();
        
        switch (col)
        {
            case 'D':
            break;
    
            case 'A': case 'B': case 'C':
                fixDistBack();
                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\nFixed Distance with Front");
                }
            break;
    
            case 'G': case 'E': case 'F':
                fixDistFront();
                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\nFixed Distance with Back");
                }
            break;
    
            default:
                if(ENABLE_LOG_UTILS)
                {
                    Serial.println("\n----------ERROR IN adjustFrontBackPosition()-----------\n");
                }
            break;
        }
    }
}

void checkForOT()
{
	if(ENABLE_LOG_UTILS)
	{
		Serial.println("\ncheckForOT()");
	}
	if(isOT())
	{
		setCurrCell(OT, getCurrCellIndex());
		if(ENABLE_LOG_UTILS)
		{
			Serial.print("\nFound Objective Tunnel:\t");
			Serial.print(getCurrRow());
			Serial.println(getCurrCol());
		}
	}
}

void moveToCache()
{
	if(ENABLE_LOG_UTILS)
	{
		Serial.println("\nmoveToCache()");
	}
	uint8_t targetCellIndex = getFieldIndex();
	char row = getRow(targetCellIndex);
	char col = getCol(targetCellIndex);
	
	if(ENABLE_LOG_UTILS)
	{
		Serial.print("\nMoveing to Cache at:\t");
		Serial.print(row);
		Serial.println(col);
	}


	if(row == getCurrRow())
	{
		while(col != getCurrCol())
		{
			backward(12);
			decCellIndex();
			adjustOrientation();
			adjustSidePosition();
			adjustFrontBackPosition();
			delay(100);
		}
	}
	else if( col == getCurrCol())
	{
		backward(3);
		delay(100);
		right(1);
		cw(90);
		forward(1.5);

		while(row != getCurrRow())
		{
			forward(12);
			downRow();
			switch (getCurrRow())
			{
				case '1': case '2': case '3': case '4':
					fixDistDiffBack();
					fixDistBackCol();
					break;
					
				case '5': case '6': case '7':
					fixDistDiffFront();
					fixDistFrontCol();
					break;
			}
			fixDistLeftCol();
			delay(100);
		}
	}
	else if( col == 'A' )
	{
		while(col != getCurrCol())
		{

			backward(12);
			decCellIndex();
			adjustOrientation();
			adjustSidePosition();
			adjustFrontBackPosition();
			delay(100);
		}

		forward(3);
		delay(100);
		right(1);
		cw(90);
		backward(1.5);

		while(row != getCurrRow())
		{
			forward(12);
			downRow();
			switch (getCurrRow())
			{
				case '1': case '2': case '3': case '4':
				fixDistDiffBack();
				fixDistBackCol();
				break;
				
				case '5': case '6': case '7':
				fixDistDiffFront();
				fixDistFrontCol();
				break;
			}
			fixDistRightCol();
			delay(100);
		}
	}
	else if(row == '7' )
	{
		backward(3);
		delay(100);
		right(1);
		cw(90);
		forward(1.5);

		while(row != getCurrRow())
		{
			forward(12);
			downRow();
			switch(getCurrRow())
			{
				case '1': case '2': case '3': case '4':
				fixDistDiffBack();
				fixDistBackCol();
				break;
				
				case '5': case '6': case '7':
				fixDistDiffFront();
				fixDistFrontCol();
				break;
			}
			fixDistLeftCol();
			delay(100);
		}

		backward(3);
		delay(100);
		right(1);
		ccw(90);
		forward(1.5);

		while(col != getCurrCol())
		{
			backward(12);
			decCellIndex();
			adjustOrientation();
			adjustSidePosition();
			adjustFrontBackPosition();
			delay(100);
		}
	}
}

void moveToStart()
{
	if(ENABLE_LOG_UTILS)
	{
		Serial.println("\nmoveToStart()");
	}

	char row = '7';
	char col = 'A';
	
	if(row == getCurrRow())
	{
		while(col != getCurrCol())
		{
			backward(12);
			decCellIndex();
			adjustOrientation();
			adjustSidePosition();
			adjustFrontBackPosition();
			delay(100);
		}
	}
	else if( col == getCurrCol())
	{
		while(row != getCurrRow())
		{
			forward(12);
			downRow();
			switch (getCurrRow())
			{
				case '1': case '2': case '3': case '4':
				fixDistDiffBack();
				fixDistBackCol();
				break;
				
				case '5': case '6': case '7':
				fixDistDiffFront();
				fixDistFrontCol();
				break;
			}
			fixDistRightCol();
			delay(100);
		}
	}
	else if( getCurrCol() == 'G' )
	{

		while(row != getCurrRow())
		{
			forward(12);
			downRow();
			switch (getCurrRow())
			{
				case '1': case '2': case '3': case '4':
				fixDistDiffBack();
				fixDistBackCol();
				break;
				
				case '5': case '6': case '7':
				fixDistDiffFront();
				fixDistFrontCol();
				break;
			}
			fixDistLeftCol();
			delay(100);
		}

		backward(3);
		delay(500);
		right(1);
		ccw(90);
		forward(1.5);

		while(col != getCurrCol())
		{

			backward(12);
			decCellIndex();
			adjustOrientation();
			adjustSidePosition();
			adjustFrontBackPosition();
			delay(100);
		}
	}
	else if(getCurrRow() == '1' )
	{
		while(col != getCurrCol())
		{
			backward(12);
			decCellIndex();
			adjustOrientation();
			adjustSidePosition();
			adjustFrontBackPosition();
			delay(100);
		}

		forward(3);
		delay(100);
		left(1);
		cw(90);
		backward(1.5);

		while(row != getCurrRow())
		{
			forward(12);
			downRow();
			switch(getCurrRow())
			{
				case '1': case '2': case '3': case '4':
				fixDistDiffBack();
				fixDistBackCol();
				break;
				
				case '5': case '6': case '7':
				fixDistDiffFront();
				fixDistFrontCol();
				break;
			}
			fixDistRightCol();
			delay(100);
		}
		//ccw(90);
	}
}