/*
 * IMT2019524 - Srijan Kumar Nallamothu
 * 
 * String Library
 * 
// returns the length of the string passed to it                   - int strlen_asm(char *str);
// returns the dest str after copying and returns dest str         - char * strcpy_asm(char * destStr, char * srcStr);
// copies n chars from src to dest and returns dest str            - char * strncpy_asm(char * destStr, char * srcStr, int num);
// Returns the first ASCII diff of two strs                        - int strcmp_asm(char * str1, char * str2);
// Returns the first ASCII diff of two strs, only max num compared - int strncmp_asm(char * str1, char * str2, int num);
// It appends str2 to the dest str and returns dest str()          - char * strcat_asm(char *destStr, char * str2); 

 * Assignment 2: Template program for String library implementation
 * It also has the sample implementation of strlen_asm()
 This needs to be built with the board package of MBedOS 
 (Arduino MbedOS RP2040 boards --> Raspberry Pi Pico

*/

//timestamp module of Raspberry Pi Pico
// Ref: https://raspberrypi.github.io/pico-sdk-doxygen/group__timestamp.html


absolute_time_t startTime;
absolute_time_t endTime;

void takeTwoInputStrings(char ** ppStr1, char **ppStr2, int * pNum);
static char * inStr1;
static char * inStr2;
static int inNum;
static char * destStr;  // used for both inStr1 and inStr2

void myPrint(char* fnName, int result);
int retValFromASM_fn = 0;

extern "C" {
  int strlen_asm0(char *str);
  int strlen_asm1(char *str);
  char * strcpy_asm(char * destStr, char * srcStr);
  char * strncpy_asm(char * destStr, char * srcStr, int num);
  int strcmp_asm(char * str1, char * str2);
  int strncmp_asm(char * str1, char * str2, int num);
  char * strcat_asm(char * destStr, char * str2);
}

// the setup function runs once when you press reset or power the board

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever


void loop() {
  
  char * inStr1 = 0;
  char * inStr2 = 0;
  int lenStr1 = 0;
  int lenStr2 = 0;
  int64_t diffTime_us = 0;
  
  Serial.println("Wait for the user to give some input.");      
  while (Serial.available() == 0) { }
  Serial.readString(); //flush this input from the buffer
  
  takeTwoInputStringsAndNum(&inStr1, &inStr2, &inNum);

  Serial.println("Call strlen_asm0(inStr1)");
  startTime = get_absolute_time();
  lenStr1 = strlen_asm0(inStr1);
  endTime = get_absolute_time();
  diffTime_us  = absolute_time_diff_us(startTime, endTime);
  Serial.print("Print inStr1: ");
  Serial.println(inStr1); 
  Serial.print("inStr1 length: ");
  Serial.println(lenStr1);  
  Serial.print("Time taken for strlen_asm0() in microsecs: ");
  Serial.println(diffTime_us);
  Serial.println(strlen(inStr1));

  
  Serial.println("Call strlen_asm1(inStr1)");
  startTime = get_absolute_time();
  lenStr1 = strlen_asm1(inStr1);
  endTime = get_absolute_time();
  diffTime_us  = absolute_time_diff_us(startTime, endTime);
  Serial.print("inStr1 length: ");
  Serial.println(lenStr1);  
  Serial.print("Time taken for strlen_asm1() in microsecs: ");
  Serial.println(diffTime_us);
  
  Serial.println("**************");
  Serial.println("Call strlen(inStr1)");
  startTime = get_absolute_time();
  lenStr1 = strlen(inStr1);
  endTime = get_absolute_time();
  diffTime_us  = absolute_time_diff_us(startTime, endTime); 
  Serial.print("inStr1 length: ");
  Serial.println(lenStr1);  
  Serial.print("Time taken for strlen() in microsecs: ");
  Serial.println(diffTime_us);

  Serial.println("**************");
  Serial.println("Call strlen_asm1(inStr2)");  
  lenStr2 = strlen_asm0(inStr2);
  Serial.print("Print inStr2: ");
  Serial.println(inStr2); 
  Serial.print("inStr2 length: ");
  Serial.println(lenStr2);
  Serial.println("**************");

  Serial.println("Call strcpy_asm(destStr,inStr1)");
  destStr = (char*)malloc(strlen(inStr1)+1);
  startTime = get_absolute_time();
  destStr = strcpy_asm(destStr,inStr1);
  endTime = get_absolute_time();
  diffTime_us  = absolute_time_diff_us(startTime, endTime);
  Serial.print(" inStr1 :");
  Serial.println(inStr1); 
  Serial.print(" destStr : ");
  Serial.println(destStr);  
  Serial.print("Time taken for strcpy_asm() in microsecs: ");
  Serial.println(diffTime_us);
  free(destStr);
  
  Serial.println("Call strcpy_asm(destStr,inStr2)");
  destStr = (char*)malloc(strlen(inStr2)+1);
  startTime = get_absolute_time();
  destStr = strcpy_asm(destStr,inStr2);
  endTime = get_absolute_time();
  diffTime_us  = absolute_time_diff_us(startTime, endTime);
  Serial.print(" inStr2 : ");
  Serial.println(inStr2); 
  Serial.print(" destStrstr  ");
  Serial.println(destStr);  
  Serial.print("Time taken for strcpy_asm() in microsecs: ");
  Serial.println(diffTime_us);
  free(destStr);
  
  Serial.println("**************");
  Serial.println("Call strncpy_asm(destStr,inStr1,inNum)");
  destStr = (char*)malloc(inNum+1);
  startTime = get_absolute_time();
  destStr = strncpy_asm(destStr,inStr1,inNum);
  endTime = get_absolute_time();
  diffTime_us  = absolute_time_diff_us(startTime, endTime);
  Serial.print(" inStr2 : ");
  Serial.println(inStr1); 
  Serial.print(" destStr : ");
  Serial.println(destStr);  
  Serial.print("Time taken for strcpy_asm() in microsecs: ");
  Serial.println(diffTime_us);
  free(destStr);
  
  Serial.println("**************");
  Serial.println("Call strcmp_asm(inStr1,inStr2)");
  startTime = get_absolute_time();
  int result = strcmp_asm(inStr1,inStr2);
  endTime = get_absolute_time();
  diffTime_us  = absolute_time_diff_us(startTime, endTime);
  Serial.print(" strcmp(inStr1,inStr2): ");
  Serial.println(result);  
  Serial.print("Time taken for strcpy_asm() in microsecs: ");
  Serial.println(diffTime_us);
  
  Serial.println("**************");
  Serial.println("Call strncmp_asm(inStr1,inStr2,inNum)");
  startTime = get_absolute_time();
  int result_strncmp = strncmp_asm(inStr1,inStr2,inNum);
  endTime = get_absolute_time();
  diffTime_us  = absolute_time_diff_us(startTime, endTime);
  Serial.print(" strncmp(inStr1,inStr2,inNum): ");
  Serial.println(result_strncmp);  
  Serial.print("Time taken for strncpy_asm() in microsecs: ");
  Serial.println(diffTime_us);
  
  Serial.println("**************");
  Serial.println("Call strcat_asm(destStr,inStr2)");
  destStr = (char *)malloc(strlen_asm1(inStr1)+strlen_asm1(inStr2)+1);
  destStr = strcpy_asm(destStr,inStr1);
  startTime = get_absolute_time();
  destStr = strcat_asm(destStr,inStr2);
  endTime = get_absolute_time();
  diffTime_us  = absolute_time_diff_us(startTime, endTime);
  Serial.print(" strcat(destStr,inStr2): ");
  Serial.println(destStr);  
  Serial.print("Time taken for strcat_asm() in microsecs: ");
  Serial.println(diffTime_us);
  free(destStr);
  
  
  free(inStr1); // Remember to free both the buffers allocated through malloc()
  free(inStr2);
  
} // end of loop()

void takeTwoInputStringsAndNum(char ** ppStr1, char **ppStr2, int * pNum){
  String str1;
  String str2;
  String numStr;  
  char * charStr1 = 0;
  int lenStr1 = 0;
  char * charStr2 = 0;

  int lenStr2 = 0;
  
  Serial.println("Wait for the user to give some input again.");      
  while (Serial.available() == 0) {}
  Serial.readString(); //flush this input from the buffer

  Serial.println("---------------------");    
  Serial.println("Enter the str1: ");
  while (Serial.available() == 0) {}                
  str1 = Serial.readString(); //Reading the Input string from the Serial port.

  Serial.println("Enter the str2: ");
  while (Serial.available() == 0) {}                
  str2 = Serial.readString(); //Reading the Input string from the Serial port. 

  Serial.println("Enter the numStr: ");
  while (Serial.available() == 0) {}                
  numStr = Serial.readString(); //Reading the num as string from the Serial port. 

  Serial.println("**************");  
  Serial.print("str1 entered:" + str1);
  Serial.print("str2 entered:" + str2);
  Serial.print("numStr entered:" + numStr);

  Serial.println("**************");
  Serial.print("str1 length: ");
  Serial.println(str1.length());
  lenStr1 = (int) str1.length();
  charStr1 = (char *) calloc(lenStr1, 1); // size of element is 1 char
  str1.toCharArray(charStr1, lenStr1);
  charStr1[lenStr1 - 1] = 0; // terminate it with NULL by overwriting CR
  Serial.print("Print the str1 with CR:");
  Serial.println(charStr1);

  Serial.println("**************");
  Serial.print("str2 length: ");
  Serial.println(str2.length());
  lenStr2 = (int) str2.length();
  charStr2 = (char *) calloc(lenStr2, 1); // element size is 1 char
  str2.toCharArray(charStr2, lenStr2);
  charStr2[lenStr2 - 1] = 0; // terminate it with NULL by overwriting CR
  Serial.print("Print the str2 with CR:");
  Serial.println(charStr2);

  Serial.println("**************");
  Serial.print("numStr length: ");
  Serial.println(numStr.length());
  *pNum = numStr.toInt();
  Serial.print("Print the num entered:");
  Serial.println(*pNum);
  Serial.println("**************");
  *ppStr1 = charStr1;
  *ppStr2 = charStr2;
  
} // takeTwoInputStrings(char ** ppStr1, char **ppStr2)

void myPrint(char* fnName, int printVal){
  Serial.print("The value returned from the assembly fn ");
  Serial.print(fnName);
  Serial.print(" : "); Serial.println(printVal);
  
  Serial.print("The value returned from the assembly fn ");
  Serial.print(fnName);
  Serial.print(" in Hex: 0x"); Serial.println(printVal, HEX);  
} // myPrint(char*, int)
