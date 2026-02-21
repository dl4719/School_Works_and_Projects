#ifndef SENECA_DYNACOPY_H
#define SENECA_DYNACOPY_H

#include "Utils.h"
#include <iostream>


using namespace std;
namespace seneca {

	template <typename T>
	T* dynaCopy(const T* srcArray, int arrSize) {
		T* tempArray = new T[arrSize];

		for (int i = 0; i < arrSize; i++) {
			tempArray[i] = srcArray[i];
		}

		return tempArray;
	}
	template <typename T>
	T* dynaCopy(T*& dest, const T* src, int srcSize) {
		if (dest) {
			delete[] dest;
		}

		dest = new T[srcSize];

		for (int i = 0; i < srcSize; i++) {
			dest[i] = src[i];
		}
		return dest;
	}
	template <typename T>
	void prnArray(const T* src, int arrSize) {
		for (int i = 0; i < arrSize; i++) {
			if (i == arrSize - 1) {
				cout << src[i] << '\n';
			}
			else {
				cout << src[i] << ", ";
			}
		}
	}

}

#endif // !SENECA_DYNACOPY_H

