//Ling Pei Li

#include <iostream>
using namespace std;

int get_choice();
void unsigned_to_int();
void signed_to_int();
void print_base_n(int quotient, int dest);
void conv_base_n(int, char *, int, int);
void conv_float();
void conv_binary(int, char*);

int main()
{
  int choice;

  do{
    choice = get_choice();
    
    switch(choice)
    {
      case 1: unsigned_to_int();
        break;
      case 2: signed_to_int();
        break;
      case 3: conv_float();
        break;
      case 0: cout << "Bye" << endl;
        break;
      default: ;
    }//switch()
  } while(choice != 0);  

  return 0;
} //main()

int get_choice()
{
  int choice;
  cout << "Menu\n";
  cout << "0. Done." << endl;
  cout << "1. Convert unsigned integer." << endl;
  cout << "2. Convert signed integer." << endl;
  cout << "3. Convert float." << endl;
  cout << "Your choice: ";
  cin >> choice;
  return choice;
}//get_choice()

void unsigned_to_int()
{
  int source, dest;
  int output = 0;
  int i = 0;
  char num[80];
  cout << "Number: ";
  cin >> num;
  cout << "Source base: ";
  cin >> source;
  cout << "Destination base: ";
  cin >> dest;
  
  //convert from source base to decimal
  for(; num[i+1] != '\0'; i++)
  {
    if(num[i] <= '9')
      output = (output + (num[i] - '0')) * source;
    else
      output = (output + (num[i] - 'A' + 10)) * source;
  }//for
  
  if(num[i] <= '9') 
    output+= (num[i] - '0');
  else
    output+= (num[i] - 'A' + 10);
  //convert from source base to decimal
  
  if(dest == 10)
    cout << output;
  else
    print_base_n(output, dest);

  cout << endl<<endl;
  
}//unsigned_to_int()

void signed_to_int()
{
  int num = 0, carry = 1;
  char mag[8] ={'0','0','0','0','0','0','0','0'};
  char comp[8] = {'0','0','0','0','0','0','0','0'};
  cout << "Signed number: " ;
  cin >> num;
  cout << "Signed magnitude: ";
		
  if(num < 0)
  {
    conv_base_n(-num, mag, 7, 16);
    conv_base_n(-num, comp, 7, 16); 
    mag[0] = mag[0] - '0' + 8;

    if(mag[0] > 9)
      mag[0] = mag[0] - 10 + 'A';
    else
      mag[0] += '0'; 
  } //if num is negative
  else
  {
    conv_base_n(num, mag, 7, 16);
    conv_base_n(num, comp, 7, 16);
  }

  for(int i = 0 ; i < 8; i++)
    cout << mag[i];

  cout << endl;
  
  cout << "Two's complement: ";
  
  if(num < 0)
  { 
    for(int i = 0; i < 8; i++)
    {
      if(comp[i] <= '9')
      {
        comp[i] -= '0';
        comp[i] = 15 - comp[i];
      
        if(comp[i] > 9)
          comp[i] = comp[i] - 10 + 'A';
        else
          comp[i] += '0';
      } //if comp[i] < 9
      else
        comp[i] = 'F' - comp[i] + '0';
    }//for

    //adding 1 to reversed  
    for(int i = 7; i >= 0 && carry; i--)
    {
      if(comp[i] == 'F')
        comp[i] = '0';
      else if(comp[i] == '9')
      {
        comp[i] = 'A';
        carry = 0;
      } //if comp[i] is 9
      else
      {
        comp[i]++;
        carry = 0;
      } //comp[i] is 0 through 8
    }//for 
  } //if num is negative

  for( int j = 0; j < 8; j++)
    cout << comp[j];

  cout << endl << endl;
}//signed_to_int()

void conv_float()
{
    int exp, mantissa, neg_sign;
    char mant_char[23];
		float floatValue;

    for(int i = 0; i < 23; i++)
      mant_char[i] = '0';

	  cout << "Float: ";
		cin >> floatValue;
     
    if(floatValue == 0)
    {
      cout << "0.0 E0" << endl << endl;
      return;
    }
    
	  unsigned temp = *((unsigned*)&floatValue);
		neg_sign = temp>>31;
    exp = (temp<<1>>24) - 127;
    mantissa = temp<<9>>9;

    if(neg_sign)
      cout << '-';
    
    cout << "1.";
   // print_base_n(mantissa, 2);
    conv_base_n(mantissa, mant_char, 22, 2);
    for(int i = 0; i < 23; i++)        
    cout<<mant_char[i];

    cout << " E";
    print_base_n(exp, 2);
    cout << endl<<endl;
} //conv_float()

void print_base_n(int quotient, int dest)
{
  int digit = quotient % dest;
  quotient /= dest;
  
  if(quotient != 0)
    print_base_n(quotient, dest);
  
  if(digit < 10)
    cout << digit;
  else
  {
    char temp = digit - 10 + 'A';
    cout << temp;
  } //digit > 10
} //print_base_n()

void conv_base_n(int quotient, char *mag,  int index, int dest)
{
  int digit = quotient % dest;
  quotient /= dest;
  
  if(quotient != 0)
    conv_base_n(quotient, mag, index-1, dest);
  
  if(digit < 10)
    mag[index] = digit + '0';
  else
  {
    char temp = digit - 10 + 'A';
    mag[index] = temp;
  } //digit > 10
} //conv_base_n()
