/**
 * Justin Dupre
 * CSCI 463 ASsignment 4 Extra Credit
 * Hamming Code Detection and Correction
 * Due 12/4/19
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

/**
 * Checks if the bitToCheck bit is set in the int value x
 * returns true or false
 */
bool isBitSet(int x, int bitToCheck)
{
	return ((x >> (bitToCheck - 1)) & 1);
}

/**
 * Returns 0 or 1 for parity of whole word
 */
int getParity(string num)
{
	int oneCount = 0;
	for (size_t i = 0; i < num.size(); i++)
	{
		if (num[i] == '1')
			oneCount++;
	}

	return (oneCount % 2);
}

int main()
{
	int parityCounter = 0; //parity for a given parity-check set
	int bitPos = 1;		   //current bitPos to track if bits are set
	int errorSum = 0;	  //sum of error bit position
	int currentParity = 0; //currentParity of full word (0 for even ; 1 for odd)
	bool broken = false;   //if an error was detected in the word
	string binaryNum;	  //binary number we get from input line

	//while there are lines left in data file
	while (std::getline(std::cin, binaryNum))
	{
		currentParity = getParity(binaryNum);
		//loop through power of 2's
		for (size_t i = 1; i <= binaryNum.size(); i += i)
		{
			//loop through each bit
			for (size_t j = 1; j <= binaryNum.size(); j++)
			{
				//check if the current bitPos bit is set for the j num
				if (isBitSet(j, bitPos))
				{
					//if it's set and it's a 1, add parityCounter for that parity-check bit
					if (binaryNum[j - 1] == '1')
						parityCounter++;
				}
			}

			//check if the parity does not match with the word parity
			//if it does't match, the word needs correction
			//else we just add the error sum with the check-bit value
			if ((currentParity == 0 && parityCounter % 2 != 0) || (currentParity != 0 && parityCounter % 2 == 0))
				broken = true;
			else
				errorSum += i;

			//reset parity counter for next check-bit
			parityCounter = 0;

			//increase the bit position we are at for next loop
			bitPos++;
		}

		//if we detected an error, flip the bit at the sum of the errors
		if (broken && size_t(errorSum - 1) <= binaryNum.size())
			binaryNum[errorSum - 1] == '0' ? binaryNum[errorSum - 1] = '1' : binaryNum[errorSum - 1] = '0';

		//print out original or corrected binary number
		cout << binaryNum << endl;

		//reset all values for next line
		parityCounter = 0;
		bitPos = 1;
		errorSum = 0;
		broken = false;
	}

	return 0;
}