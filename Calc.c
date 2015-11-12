#include "stdio.h"
#include "string.h"
//#include "serial.h"
//#include "serial.c"
//#include "keypad.c"
//#include "keypad.h"

//need to collect from keyboard and output to LCD

//to be put in header
int power (int base, int exp);
int converter (char *number);
int Calc (str);

int Calc (char* str) {
 
//char str[128]; //can remove as its input
char *ptr; 
//strcpy (str, "10D7"); // input string to test
int w = strlen(str);
double divtotal = 0;
int total, result, result1 = 0;
int i;
for (i = 0; i < w; i++){
        
    if (str[i] == 'A'){ //Add
        strtok_r (str, "A", &ptr);
        result = converter(str);
        result1 = converter(ptr);
        total = result + result1;
        return total;}
    else if (str[i] == 'B'){ //Subtract
        strtok_r (str, "B", &ptr);
        result = converter(str);
        result1 = converter(ptr);
        total = result - result1;
        return total;}
    else if (str[i] == '*'){ //Times
        strtok_r (str, "*", &ptr);
        result = converter(str);
        result1 = converter(ptr);
        total = result * result1;
        return total;} 
    else if (str[i] == 'D'){ //Divide
        strtok_r (str, "D", &ptr);
        result = converter(str);
        result1 = converter(ptr);
        if (result1 == 0){
            return -1;}
        else{       
            divtotal = (double)result / result1;
            return divtotal;}}
    else{continue;}
}

return 0;
}


int power(int base, int exp) {
    if (exp == 0)
        return 1;
    else if (exp % 2)
        return base * power(base, exp - 1);
    else {
        int temp = power(base, exp / 2);
        return temp * temp;
    }
}


int converter (char *number){
    int result = 0;
    int count = (strlen(number)-1);
    int x;
    for (x = 0; x < strlen(number); x++){       
    int y = number[x] -48; // turns ascii to number
    result += y * power(10, count);         
    count--;}
    return result;
}
