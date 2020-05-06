/*******************************************************************************************
*Author: Y Nguyen
*Self study: COSC 2430 Data structure using C++
*Date: 01/10/2019
*Program: This is a simple program that can add or subtract two ingeter number
*No matter about the numbers of digits of the given numbers
*Practicing in using class, pointer, dynamic array and overloading operator. 
*******************************************************************************************/

#include<iostream>
#include<string>

using namespace std;
class largeIntegers {

	friend ostream& operator<<(ostream& osObject, const largeIntegers& num) {
		if (num.isPositive()) {
			for (int i = num.len - 1;i >= 0;i--) {
				osObject << num.numPtr[i];
			}
				return osObject;
		}
		else {
			osObject << num.sign;
			for (int i = num.len - 1;i >= 0;i--) {
				osObject << num.numPtr[i];
			}//end for
			return osObject;
		}
	}
	friend istream& operator>>(istream& ipObject, largeIntegers& num) {
		string numStr;
		ipObject >> numStr;
		num.reversedArrayInt(numStr);
		return ipObject;
	}
private:
	string number;
	int *numPtr;
	int len; // numOfDigits
	char sign;
	//static const int MAX_NUM_OF_DIGITS = 100;

	int charToInt(char c) {
		return c - 48;		//(static_cast<int>(c) - 48);
	}
	char intToChar(int n) {
		return (n + 48);
	}
	int length() {
		return len;
	}
	//check if a given character is digit or nondigit
	bool isDigit(char ch) {
		if (ch >= '0'&&ch <= '9')
			return true;
		else
			return false;
	}
	/*PRIVATE CONSTRUCTOR
	 *@para: int
	 *This constructor create an empty int array with a given length*/
	largeIntegers(int length) {
		if (length < MAX_NUM_OF_DIGITS)
			numPtr = new int[length];
	}

	/**
	* Checking and Converting the string number to an integer array but in reversed order
	* @para: numStr
	**/
	void reversedArrayInt(string& numStr) {
		//check sign if it exists;
		if (numStr[0] == '-' || numStr[0] == '+') {
			sign = numStr[0];
			number = numStr.erase(0, 1);//delete the sign from numStr
		}//end if
		else {
			sign = '+';
			number = numStr;
		}//end else

		len = number.size();
		numPtr = new int[len];
		int j = 0;
		for (int i = len - 1;i >= 0;i--) {
			if (isDigit(number[i])) {
				numPtr[j] = charToInt(number[i]); 	//numPtr[j] = static_cast<int>(number[i] - 48);
				j++;
			}//end if
			else {
				numStr.clear();//numStr.erase()
				cout << "Invalid number" << endl;
			}
		}//end for

	}//end of reversedArrayInt


	/**
	ADD function will received add the current number to
	a given number of largeIntegers type
	*@para: otherNumber
	*@return: largeIntegers
	**/

	largeIntegers addTwoPositive(largeIntegers &otherNumber) {
		largeIntegers *large;
		largeIntegers *small;

		if (len <= otherNumber.len) {
			large = &otherNumber;
			small = this;
		}
		else {
			large = this;
			small = &otherNumber;
		}
		//Create a largeIntegers object z to store the result. 
		largeIntegers z(large->len + 1);//int maxSize=x.size()+small.size();
		int size = 0;// to store the length of z
		int sum = 0;// use sum to add 2 number and carry
		// process the adding two number form digits 1st to nth
		for (int i = 0;i < small->len;i++) {
			sum = sum + large->numPtr[i] + small->numPtr[i];// sum= carry +digit1 + digit2
			z.numPtr[i] = sum % 10;
			sum = sum / 10;// carry
			size++;

		}//end for
		 //process the number from nth to mth
		while (sum != 0 || size < large->len) {
			if (size < large->len) {
				for (int j = small->len;j < large->len;j++) {
					sum = sum + large->numPtr[j];
					z.numPtr[j] = sum % 10;
					sum = sum / 10;
					size++;
				}//end for
			}//end if
			 //if len of z =large.len but sum=1, z[m+1]=1 
			else {
				z.numPtr[size] = sum; // z.a[len] index 10, which is the number at (len+1)th
				sum = 0;
			}//end if
		}//end while

		z.len = size;
		return z;
	}//end of addTwoPositive function

	largeIntegers absOfsub(largeIntegers &otherNumber) {
		largeIntegers z(len);
		int size = 0;
		int sub=0;
		for (int i = 0;i < otherNumber.len;i++) {
			sub= numPtr[i] - otherNumber.numPtr[i]+sub;
			if (sub >= 0) {
				z.numPtr[i] = sub;
				sub = 0;
					size++;
			}
			else {
				z.numPtr[i] = 10 + sub;
				sub = -1;//carry -1
				size++;
			}
		}
		for (int i = otherNumber.len;i < len;i++) {
			z.numPtr[i] = sub + numPtr[i];
			sub = 0;
			size++;
		}
		for (int i = size - 1;i >= 0;i--) {
			if (z.numPtr[i] == 0)// trace the leading 0s
				size--;
			else
				break;
		}
		z.len = size;
		return z;
}//end sub*/
	
	void destroyPtr() {
		delete [] numPtr;
		numPtr = nullptr;
		int len = 0;
		number = "";
	}

	//Function isLarger compare the digit part of the two largeIntegers number;
	bool isLarger(const largeIntegers& otherNumber)const {
		if (len > otherNumber.len)
			return true;
		else if (len == otherNumber.len) {
			bool isLarger = false;
			for (int i = len - 1;i >= 0;i--) {
				if (numPtr[i] > otherNumber.numPtr[i]) {
					isLarger = true;
					break;
				}//end if
				else if (numPtr[i] == otherNumber.numPtr[i])
					continue;
				else {
					isLarger = false;
					break;
				}//end else

			}//end for
			return isLarger;
		}
		else
			return false;
	}
	bool isEqual(const largeIntegers & otherNumber)const {
		if (len == otherNumber.len) {
			for (int i = len - 1;i >= 0;i--) {
				if (numPtr[i] != otherNumber.numPtr[i])
					return false;
			}
			return true;
		}
		else
			return false;
	}//end isEqual
	
	
public:
	bool isPositive()const {
		if (sign == '+')
			return true;
		else
			return false;
	}
	bool isNegative()const {
		if (isPositive())
			return false;
		else
			return true;
	}
	
	bool operator >(const largeIntegers& otherNumber)const {
		if (isPositive() && otherNumber.isPositive()) {
			if (isLarger(otherNumber))
				return true;
			else
				return false;
		}//end if
		else if (isNegative() && otherNumber.isPositive())
			return false;
		else if (isPositive() && otherNumber.isNegative())
			return true;
		else {
			if (isLarger(otherNumber))
				return false;
			else
				return true;
		}//end else
	}//end operator >


	bool operator >=(const largeIntegers& otherNumber)const {
		if (*this > otherNumber || *this == otherNumber)
			return true;
		else
			return false;
}// end overloading operator >=

	bool operator ==(const largeIntegers& otherNumber)const {
		if (sign == otherNumber.sign && isEqual(otherNumber))
			return true;
		else
			return false;
	}

	bool operator <(const largeIntegers& otherNumber)const {
		if (*this >= otherNumber)
			return false;
		else
			return true;
	}
	bool operator<=(const largeIntegers& otherNumber)const {
		if (!(*this>otherNumber))
			return true;
		else
			return false;
	}
	bool operator!=(const largeIntegers& otherNumber)const {
		if (*this == otherNumber)
			return false;
		else
			return true;
	}

	void assignNumber(string numStr) {

		reversedArrayInt(numStr);
	}

	//Defalt constructor;
	largeIntegers() {
		//*numPtr ;// is it necessary to assign Null to pointer in this case?
		len = 0;
	}

	//Constructor receive a string as a prameter
	largeIntegers(string numStr)
	{
		reversedArrayInt(numStr);
	}

	//overloading operator +
	largeIntegers operator+(largeIntegers &otherNumber) {
		//add(otherNumber).print();
		largeIntegers result;
		if (isPositive() && otherNumber.isPositive()) {
			result = addTwoPositive(otherNumber);
			result.sign = '+';
		}
		else if (isNegative() && otherNumber.isNegative()) {
			result = addTwoPositive(otherNumber);
			result.sign = '-';
		}
		else if (isNegative() && otherNumber.isPositive()) {
			if (isLarger(otherNumber)) {// if abs of right >left
				result = absOfsub(otherNumber);
				result.sign = '-';
			}
			else {
				result = otherNumber.absOfsub(*this);
				result.sign = '+';
			}
		}
		else {
			if (isLarger(otherNumber)) {// if abs of right >left
				result = absOfsub(otherNumber);
				result.sign = '+';
			}
			else {
				result = otherNumber.absOfsub(*this);
				result.sign = '-';
			}
		}
		return result;
	}

	//overloading operator +
	largeIntegers operator-(largeIntegers &otherNumber) {
		//add(otherNumber).print();
		largeIntegers result;
		if (isPositive() && otherNumber.isPositive()) {
			if (isLarger(otherNumber)) {
				result=absOfsub(otherNumber);
				result.sign = '+';
			}
			else {
				otherNumber.absOfsub(*this);
				result.sign = '-';
			}
		}
		else if (isNegative() && otherNumber.isNegative()) {
			if (*this >= otherNumber) {
				result = otherNumber.absOfsub(*this);
				result.sign = '+';
			}
			else {
				result = absOfsub(otherNumber);
				result.sign = '-';
			}
		}//end else if
		else if (isPositive()&&otherNumber.isNegative()) {
			result = addTwoPositive(otherNumber);
			result.sign = '+';
		}
		else {
			result = addTwoPositive(otherNumber);
			result.sign = '-';
		}
		return result;
	}

	//Function Print
	void print() {
		if(isPositive())
		for (int i = len - 1;i >= 0;i--) {
			cout <<numPtr[i];
		}
		else {
			cout << sign;
			for (int i = len - 1;i >= 0;i--) {
				cout << numPtr[i];
			}
		}
	}//end print()

	//copy constructor
	largeIntegers(const largeIntegers& otherNumber) {
	len = otherNumber.len;
	sign = otherNumber.sign;
	numPtr = new int[len];
		for (int i = 0; i < len ;i++) {
			numPtr[i] = otherNumber.numPtr[i];
		}//end for
	}//end copy constructor
	 //Destructor;
	/* ~largeIntegers() {
	 delete numPtr;
	 numPtr = nullptr;
	 }*/
};

int main() {
	largeIntegers num1;
	largeIntegers num2;
	cin >> num1;
	cin >> num2;
	cout << "num1: " << num1 << endl;
	cout << "num2: " << num2 << endl;

	cout << "num1 + num2 = " << num1 + num2 << endl;

	cout << "num1 - num2 = " << num1 - num2 << endl;

	cout << "num1 == num2: " << (num1 == num2) << endl;
	cout << "num1 != num2: " << (num1 != num2) << endl;
	cout << "num1 > num2: " << (num1 > num2) << endl;
	cout << "num1 >= num2: " << (num1 >= num2) << endl;
	cout << "num1 < num2: " << (num1 < num2) << endl;
	cout << "num1 <= num2: " << (num1 <= num2) << endl;

	system("PAUSE");
	return 0;
}