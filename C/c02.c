// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// the Internet, or any other unauthorized source, either modified
// or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an authorized source, such as a text book or
// course notes, that has been clearly noted with a proper citation
// in the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the grading code.
//
// Tanner Spicer
// tanner9


//Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Function Declarations -----------------------------------

/**
   This function should parse integers from a given char array.
   
   Pre: The given char should contain a read line of text.

  Should modify the values in the provided position array

  --Bug where values would randomly be misread?, 
    solution: read values individually
              still rarely screws up
 */
void parsePos(char line[], int position[]);

/**
   This function will parse the direction from a line read from the input file.

   Pre: the line has been given the values of a line of file read

   This function should modify the given direction array
 */
void parseDir(char line[], char direction[]);

/**
   This method will return a distance in seconds depending on the 
   positions of the given source and destination.

   If source and destination coordinates are in the east or south hemisphere,
   their values will be treated as negative, similar to being in
   quadrants 3 and 4 on a cartesian graph.

   Each Coordinante value will be converted to seconds then put in the equation
     |source - destination|_longitude + |source - destination|_latitude 
       = taxiCabDistance

   Pre: All parameters have been initialized with the proper values
   
   Returns: An int to represent the distance in seconds.
 */
int distance(int sourcePos[], char sourceDir[], int destPos[], 
	     char destDir[]);

/**
   Given a distance in seconds, the function should calculate
   the degrees and minutes by dividing by their conversion factor, 
   then mod by that factor.

   Pre: the parameter is a distance in seconds.

   This function should modify the given dms array
 */
void convertDistance(int seconds, int dms[]);

/**
 This method should write to the output file in the specified format in
 the assignment spec.

 params: the out file should already be opened and all other parameters
         should contain the correct values read from the data file.

 returns: 1 if fprintf successfully printed to the out file.
 */
int writeOut(FILE* out, int source[], char sourceDir[], int dest[], 
	     char destDir[], int distance, int dms[]);

/**
   This function should, in steps:
   1) Open the given files
   2) Read strings of length LINE_LENGTH from the file
   3) Parse Information form the strings
   4) Compute the needed distance values
   5) Write to the given output files
   6) Close all Files

   Pre: The given file names should be correct

   Return: 0 if it ran correctly, 
           values 1-3 are failures for not opening files
 */
int main(int argc, char* argv[]);

//Implementations -----------------------------------------


/**
   This function should parse integers from a given char array.
   
   Pre: The given char should contain a read line of text.

  Should modify the values in the provided position array

  --Bug where values would randomly be misread?, 
    solution: read values individually
              still rarely screws up
 */
void parsePos(char line[], int position[]){
  sscanf(line, "%3i", &position[0]);
  sscanf(line, "%*3i %2i", &position[1]);
  sscanf(line, "%*5i %2i", &position[2]);
  sscanf(line, "%*7i %*c %2i", &position[3]);
  sscanf(line, "%*7i %*c %*2i %2i", &position[4]);
  sscanf(line, "%*7i %*c %*4i %2i", &position[5]);
}

/**
   This function will parse the direction from a line read from the input file.

   Pre: the line has been given the values of a line of file read

   This function should modify the given direction array
 */
void parseDir(char line[], char direction[]){

  sscanf(line, "%*7i %c %*6i %c", &direction[0], &direction[1]);

}

/**
   This method will return a distance in seconds depending on the 
   positions of the given source and destination.

   If source and destination coordinates are in the east or south hemisphere,
   their values will be treated as negative, similar to being in
   quadrants 3 and 4 on a cartesian graph.

   Each Coordinante value will be converted to seconds then put in the equation
     |source - destination|_longitude + |source - destination|_latitude 
       = taxiCabDistance

   Pre: All parameters have been initialized with the proper values
   
   Returns: An int to represent the distance in seconds.
 */
int distance(int sourcePos[], char sourceDir[], int destPos[], 
	     char destDir[]){

  int longitude, latitude;

  //Change signs dependent on cardinal direction 
  if(sourceDir[0] == 'E'){
    for (int i = 0; i < 3; i++){
      sourceDir[i] = sourceDir[i]*-1;
    }
  }
  if(sourceDir[1] == 'S'){
    for (int i = 3; i < 6; i++){
      sourceDir[i] = sourceDir[i]*-1;
    }
  }
  if(destDir[0] == 'E'){
    for (int i = 0; i < 3; i++){
      destDir[i] = destDir[i]*-1;
    }
  }
  if(destDir[1] == 'S'){
    for (int i = 3; i < 6; i++){
      destDir[i] = destDir[i]*-1;
    }
  }

  //Convert values to seconds and sum
  longitude = abs((sourcePos[0]*60*60) + (sourcePos[1]*60)+(sourcePos[2])
		    -(destPos[0]*60*60)-(destPos[1]*60)-(destPos[2]));

  latitude = abs((sourcePos[3]*60*60) + (sourcePos[4]*60)+(sourcePos[5])
		    -(destPos[3]*60*60)-(destPos[4]*60)-(destPos[5]));

  return longitude + latitude;
}

/**
   Given a distance in seconds, the function should calculate
   the degrees and minutes by dividing by their conversion factor, 
   then mod by that factor.

   Pre: the parameter is a distance in seconds.

   This function should modify the given dms array
 */
void convertDistance(int seconds, int dms[]){
  //Find days, then minutes, then the remaing seconds
  //by dividing by the conversion factor then modding the
  //remaining seconds by that conversion factor.
  dms[0] = seconds / 3600;
  seconds = seconds % 3600;
  dms[1] = seconds / 60;
  seconds = seconds % 60;
  dms[2] = seconds;
}

/**
 This method should write to the output file in the specified format in
 the assignment spec.

 params: the out file should already be opened and all other parameters
         should contain the correct values read from the data file.

 returns: 1 if fprintf successfully printed to the out file.
 */
int writeOut(FILE* out, int source[], char sourceDir[], int dest[], 
	     char destDir[], int distance, int dms[]){
  if(fprintf(out, "(%03id %02im %02is %c, %02id %02im %02is %c)\t"
	     "(%03id %02im %02is %c, %02id %02im %02is %c)\t" 
	     "%i\t %id %02im %02is\n", 
	     source[0], source[1], source[2], sourceDir[0], 
	     source[3], source[4], source[5], sourceDir[1],
	     dest[0], dest[1], dest[2], destDir[0],
	     dest[3], dest[4], dest[5], destDir[1],
	     distance, 
	     dms[0], dms[1], dms[2])){
    return 0;
  } else {
    return 1;
  }
}

/**
   This function should, in steps:
   1) Open the given files
   2) Read strings of length LINE_LENGTH from the file
   3) Parse Information form the strings
   4) Compute the needed distance values
   5) Write to the given output files
   6) Close all Files

   Pre: The given file names should be correct

   Return: 0 if it ran correctly
 */
int main(int argc, char* argv[]) {

  //The length of text that should be read at every fgets() call.
  int LINE_LENGTH = 18;

  //Exit early if the worng amount of inputs were given.
  if(argc < 3) {
    printf("%s <testFile> <outputFile> \n", argv[0]);
    return 1;
  }

  char* testData = argv[1];
  char* resultsFile = argv[2];

  //Attempt to open input file, return 2 if unreadable
  FILE* tests = fopen(testData, "r");
  if ( tests == NULL ){
    printf("Could not read from %s \n", testData);
    return 2;
  }
  
  //Attempt to write to output file, return 3 if unwriteable
  FILE* results = fopen(resultsFile, "w");
  if ( results == NULL ){
    printf("Could not write to %s \n", resultsFile);
    fclose(tests);
    return 3;
  }


  //Write header on output file
  fprintf(results, "First coordinate                Second coordinate               seconds  DMS\n");
  fprintf(results, "------------------------------------------------------------------------------------------\n");
  

  char line[LINE_LENGTH]; //Holds the current input line
  int lineCount = 2;//Should start on line 2 after skipping header

  fgets(line, LINE_LENGTH, tests);//Skip the header number

  while(fgets(line, LINE_LENGTH, tests)){

    //Get the position and direction of the source form the line
    int sourcePos[6] = {0};
    parsePos(line, sourcePos);
    char sourceDir[2] = {'a'};
    parseDir(line, sourceDir);

    //Get the next information for the destination
    int destPos[6] = {0};
    char destDir[2] = {'a'};
    if (fgets(line, LINE_LENGTH, tests)){
      parsePos(line, destPos);
      parseDir(line, destDir);
    }
    else{
      printf("read error line 150 source, line %i file", lineCount);
    }

    //Compute distance
    int dist = distance(sourcePos, sourceDir, destPos, destDir);

    //Convert Distance to d,m,s format
    int distanceDms[3] = {0};
    convertDistance(dist, distanceDms);

    //Write to output
    writeOut(results, sourcePos, sourceDir, destPos, destDir, 
	     dist, distanceDms);
    
    lineCount++;
  }
  


  //Close all files, return 0 for success.
  fclose(tests);
  fclose(results);
  return 0;
}
