//Include statements
#include <iostream>
#include <string>
#include <time.h>

//Namespace declaration
using namespace std;

//Constant def
#define CHAR_SIZE 8

//Keygenerator function
//Generates 6 keys
void getKeys(int keys[])
{
	cout << "Generating keys..." << endl;

	for (int i = 0; i < 6; i++) //Create 6 random keys
	{
		keys[i] = rand() % 8888 + 1111; //Get a 4 digit key between 1111 and 9999
		cout << "\tKey " << i + 1 << ": " << keys[i] << endl;
	}

	cout << "Keys successfully generated." << endl << endl;
}

//
void getEachPlace(int &k, int arr[], bool fixIfZero)
{
	int num = k; //Number to act as modification reference
	int t = 0, h = 0, tE = 0; //three counters for the thousands/hundreds/tens place of each digit

	while (num >= 1000) //While there is still something in the thousands place
	{
		t++; //Add the thousands place to the thousands counter
		num -= 1000; //Take away 1000 that has been accounted for
	}

	arr[0] = t; //Set the first digit to the thousands counter

			  //Get the second digit from the 100s place
	if (num < 100 && fixIfZero) //If something doesn't exist in the hundreds place
	{
		cout << "First key generated does not have a number in the hundreds place. Randomizing key..." << endl;
		arr[1] = rand() % 9 + 1; //Get random number between 1 and 9
		k += arr[1] * 100; //Add new number into the key
		cout << "\tKey set to " << arr[1] << ". Master key updated to " << k << "." << endl;
	}
	else //If the hundreds place has an existing number
	{
		while (num >= 100) //While there is still something in the hundreds place
		{
			h++; //Add the hundreds place to the hundreds counter
			num -= 100; //Take away the 100 that has been accounted for
		}

		arr[1] = h; //Set the second digit to the hundreds counter
	}

	//Get the third digit from the 10s place
	if (num < 10 && fixIfZero) //If something doesn't exist in the tens place
	{
		cout << "First key generated does not have a number in the tens place. Randomizing key..." << endl;
		arr[2] = rand() % 9 + 1; //Get random number between 1 and 9
		k += arr[2] * 10; //Add new number into the key
		cout << "\tKey set to " << arr[2] << ". Master key updated to " << k << "." << endl;
	}
	else //If the tens place has an existing number
	{
		while (num >= 10) //While there is still something in the hundreds place
		{
			tE++; //Add the tens place to the hundreds counter
			num -= 10; //Take away the 10 that has been accounted for
		}

		arr[2] = tE; //Set the second digit to the tens counter
	}

	//Get the last digit from the 1s place
	if (num < 1 && fixIfZero) //If something doesn't exist in the ones place
	{
		cout << "First key generated does not have a number in the ones place. Randomizing key..." << endl;
		arr[3] = rand() % 9 + 1; //Get random number between 1 and 9
		k += arr[3]; //Add new number into the key
		cout << "\tKey set to " << arr[3] << ". Master key updated to " << k << "." << endl;
	}
	else //If the ones place has an existing number
	{
		arr[3] = num; //Set the second digit to the ones counter
	}
}

//Digit determinate
//Gets the 4 digits to consider in each of the 4 keys for shifting
void getDigit(int &k, int d[]) //Passed in by reference in case any of the 4 digits is == 0, in which case that will need to be fixed
{
	getEachPlace(k, d, true); //Get each place, and fix the key if any digit is 0

	cout << "Master key (" << k << ") digits are: ";

	for (int i = 0; i < 4; i++)
	{
		cout << d[i] << ", ";
	}

	cout << "respectively." << endl << endl;
	cout << "Modulating all numbers by 4..." << endl;

	for (int i = 0; i < 4; i++)
	{
		d[i] %= 4; //Get the modulus of each number by 4
	}

	cout << "\tMaster key (" << k << ") will select digits:" << endl << "\t\t";

	for (int i = 0; i < 4; i++)
	{
		cout << d[i] << ", ";
	}

	cout << endl << "\tin keys 3, 4, 5, and 6 respectively." << endl << endl;
}

//Right shift determinate
//Gets whether or not the program should shift right or left
void getRightShift(int k, bool rS[])
{
	int rA[4]; //Returning array to get digits back from

	getEachPlace(k, rA, false);

	if (rA[0] % 2 == 1) //If the thousands place counter is odd
		rS[0] = true; //Set right shift on key 1 to true

	if (rA[1] % 2 == 1) //If the hundreds place counter is odd
		rS[1] = true; //Set right shift on key 2 to true
	
	if (rA[2] % 2 == 1) //If the tens place counter is odd
		rS[2] = true; //Set right shift on key 3 to true

	if (rA[3] % 2 == 1) //If the ones place counter is odd
		rS[3] = true; //Set right shift on key 4 to true

	cout << "Based on Key 2 (" << k << "):" << endl;

	for (int i = 0; i < 4; i++)
	{
		if (rS[i])
			cout << "\tKey " << i + 3 << " will shift right." << endl;
		else
			cout << "\tKey " << i + 3 << " will shift left." << endl;
	}

	cout << endl;
}

//Power calculator
//Gets number to a power
int power(int num, int pow)
{
	int get;

	if (pow < 1)
		return 1;
	else if (pow == 1)
		return num;
	else
		get = power(num, pow - 1);

	return num * get;
}

//Right shifter
//Shifts the int value to the right
int shiftRight(int c, int times)
{
	int bits[7]; //Bit storage
	int shifted[7]; //Shifted bits
	int pos = 0; //Position to shift to
	int finalNum = 0; //Final number storage
	int count = 0; //Counter

	for (int i = 6; i >= 0; i--) //Get bit digits
	{
		if (c % 2 == 1) //If the number is odd
			bits[i] = 1; //Add a bit to the back
		else
			bits[i] = 0; //Skip this bit

		c /= 2; //Divide number by 2
	}

	for (int i = 0; i < 7; i++) //Shift bit digits
	{
		pos = (i + times) % 7; //Get position to shift to
		shifted[pos] = bits[i]; //Move shifted bit to new position
	}

	for (int i = 6; i >= 0; i--) //Get number
	{
		if (shifted[i] == 1) //If a bit exists
			finalNum += power(2, count); //Get a number for this position

		count++;
	}

	return finalNum; //Return the final number
}

//LEft shifter
//Shifts the int value to the left
int shiftLeft(int c, int times)
{
	int bits[7]; //Bit storage
	int shifted[7]; //Shifted bits
	int pos = 0; //Position to shift to
	int finalNum = 0; //Final number storage
	int count = 0; //Counter

	for (int i = 6; i >= 0; i--) //Get bit digits
	{
		if (c % 2 == 1) //If the number is odd
			bits[i] = 1; //Add a bit to the back
		else
			bits[i] = 0; //Skip this bit

		c /= 2; //Divide number by 2
	}

	for (int i = 0; i < 7; i++) //Shift bit digits
	{
		pos = (i - times) % 7; //Get position to shift to

		if (pos < 0) //If number is negative
			pos += 7; //Add 7 to offset the difference

		shifted[pos] = bits[i]; //Move shifted bit to new position
	}

	for (int i = 6; i >= 0; i--) //Get number
	{
		if (shifted[i] == 1) //If a bit exists
			finalNum += power(2, count); //Get a number for this position

		count++; //Increase counter
	}

	return finalNum; //Return the final number
}

//Encrypter function
//Encrypts a given string
void enc(string t, string &cip, int k[], int d[], bool rS[])
{
	int digit3[4]; //digits in key 3
	int digit4[4]; //digits in key 4
	int digit5[4]; //digits in key 5
	int digit6[4]; //digits in key 6
	int times[4]; //Times to shift in each direction
	int currentChar; //Current character's ASCII value
	int newASCII; //New ASCII value to use=

	//Get digits
	getEachPlace(k[2], digit3, false); //Get digits for key 3
	getEachPlace(k[3], digit4, false); //Get digits for key 4
	getEachPlace(k[4], digit5, false); //Get digits for key 5
	getEachPlace(k[5], digit6, false); //Get digits for key 6

	//Get shift times
	times[0] = digit3[d[0]]; //Get shift times for key 3
	times[1] = digit4[d[1]]; //Get shift times for key 4
	times[2] = digit5[d[2]]; //Get shift times for key 5
	times[3] = digit6[d[3]]; //Get shift times for key 6

	for (int i = 0; i < t.length(); i++) //Encrypt the string
	{
		currentChar = (int)t[i]; //Get the current character's ASCII value

		if (rS[i]) //If right shift
			newASCII = shiftRight(currentChar, times[i % 4]); //Shift character's ASCII value right
		else
			newASCII = shiftLeft(currentChar, times[i % 4]); //Shift character's ASCII value left

		cip += newASCII; //Add new character to the ciphertext string
	}
}

//Decrypter function
//Decrypts a given string
void dec(string enc, string &pla, int k[], int d[], bool rS[])
{
	int digit3[4]; //digits in key 3
	int digit4[4]; //digits in key 4
	int digit5[4]; //digits in key 5
	int digit6[4]; //digits in key 6
	int times[4]; //Times to shift in each direction
	char cAntiNeg; //Char used to prevent negative ASCII values
	int currentChar; //Current character's ASCII value
	int newASCII; //New ASCII value to use=

				  //Get digits
	getEachPlace(k[2], digit3, false); //Get digits for key 3
	getEachPlace(k[3], digit4, false); //Get digits for key 4
	getEachPlace(k[4], digit5, false); //Get digits for key 5
	getEachPlace(k[5], digit6, false); //Get digits for key 6

									   //Get shift times
	times[0] = digit3[d[0]]; //Get shift times for key 3
	times[1] = digit4[d[1]]; //Get shift times for key 4
	times[2] = digit5[d[2]]; //Get shift times for key 5
	times[3] = digit6[d[3]]; //Get shift times for key 6

	for (int i = 0; i < enc.length(); i++) //Encrypt the string
	{
		cAntiNeg = enc[i]; //Get the current character's ASCII value
		currentChar = (int)cAntiNeg;

		if (rS[i]) //If right shift
			newASCII = shiftLeft(currentChar, times[i % 4]); //Shift character's ASCII value right
		else
			newASCII = shiftRight(currentChar, times[i % 4]); //Shift character's ASCII value left

		pla += newASCII; //Add new character to the ciphertext string
	}
}

//Main driver
int main()
{
	string text = "This string of text is to be encrypted and decrypted."; //String to encrypt
	string encText = ""; //Encrypted text
	string decText = ""; //Decrypted text

	int keys[6]; //Keys
	int digit[4]; //Digit to consider for each of the 4 keys
	bool rightShift[4] = { false, false, false, false }; //Bool that tells the program to shift keys right or not

	srand(time(NULL)); //Number randomizer seed

	getKeys(keys); //Generate keys
	getDigit(keys[0], digit); //Get the considered digits
	getRightShift(keys[1], rightShift); //Get the right shift flag

	cout << "Original text: " << text << endl;

	//Encrypt
	enc(text, encText, keys, digit, rightShift);

	cout << "Encrypted text: " << encText << endl;

	//Decrypt
	dec(encText, decText, keys, digit, rightShift);

	cout << "Decrypted text: " << decText << endl << endl;

	//Close program
	system("pause");
	return 0;
}