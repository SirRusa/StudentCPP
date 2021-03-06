#include "pch.h"
#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

int main()
{
	bool proof = 1;
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите константы" << endl;
	double chisl[100]; short int chn = 0;
	for (; proof != 0; ) {
		char vvod[255];
		cin.getline(vvod, 255);
		if (vvod[0] == 'e' && vvod[1] == 'n' && vvod[2] == 'd' && strlen(vvod) == 3) { break; }
		for (short int i = 0; i < strlen(vvod); i++) { if (vvod[i] == '.') { vvod[i] = ','; } }
		for (short int x = 1, i = 0; i < strlen(vvod); i++) {
			if (vvod[i] == ',') { x--; } 
			if (x < 0) { proof = 0; break; }
		}
		for (short int i = 0; i < strlen(vvod); i++) {
			if ((vvod[i] < 48 || vvod[i]>57) && vvod[i] != ',') { proof = 0; break; }
		}
		chisl[chn] = atof(vvod); chn++;
	}
	if (proof != 0) { cout << "Введите знаки" << endl; }
	char znak[100]; short int znn = 0; chn--;
	for (; (znn < chn) && proof != 0; znn++) {
		char vvod[100];
		cin.getline(vvod, 100);
		if (strlen(vvod) > 1) { proof = 0; break; }
		znak[znn] = vvod[0];
	}
	for (short int i = 0; i != znn && proof != 0; i++) {
		switch (znak[i]) {
		case '+': {
			chisl[i + 1] = chisl[i] + chisl[i + 1]; break;
			}
		case '-': {
			chisl[i + 1] = chisl[i] - chisl[i + 1]; break;
			}
		case '/': {
			if (chisl[i + 1] == 0) { proof = 0; break; }
			chisl[i + 1] = chisl[i] / chisl[i + 1]; break;
			}
		case '*': {
			chisl[i + 1] = chisl[i] * chisl[i + 1]; break;
			}
		default: {
			proof = 0; break;
			}
		}
	}
	if (proof != 0) { cout << "Ответ: " << chisl[chn] << endl; }
	if (proof == 0) { cout << "ERROR" << endl; }
	return 0;
}