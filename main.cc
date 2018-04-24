 /*
 * Source code for Program 6
 *
 * Based on the example code from Dr. Perkins
 *
 * File:    main.cc
 * Author:  Kenneth Palmer
 * Email:   Kenneth.Palmer@UTDallas.edu
 * Section: CS 3377.502
 *
 */

#include <iostream>
#include <cstdint>
#include <fstream>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 30
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;
class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{
  ifstream binary_reader("cs3377.bin",ios::in|ios::binary);
  BinaryFileHeader *bin_head = new BinaryFileHeader();
  binary_reader.read((char *)bin_head, sizeof(BinaryFileHeader));
  cout << bin_head->magicNumber << endl;
  cout << bin_head->versionNumber << endl;
  cout << bin_head->numRecords << endl;
  
  char magic[maxRecordStringLength];
  sprintf(magic, "Magic: 0x%X",bin_head->magicNumber);
  char version[maxRecordStringLength];
  sprintf(version, "Version: %u",bin_head->versionNumber);
  char records[maxRecordStringLength];
  sprintf(records, "NumRecords: %lu",bin_head->numRecords);

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"", "a", "b", "c"};
  int		boxWidths[MATRIX_WIDTH+1] = {maxRecordStringLength,maxRecordStringLength,maxRecordStringLength,maxRecordStringLength};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 1, 1, magic);
  setCDKMatrixCell(myMatrix, 1, 2, version);
  setCDKMatrixCell(myMatrix, 1, 3, records);
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
}
