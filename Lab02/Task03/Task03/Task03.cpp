#include "pch.h"
#include <iostream>
#include <locale>
#include <cmath>

using namespace std;
bool proverkazn(char x);

int main()
{	
	setlocale(LC_ALL, "RUSSIAN");
	cout << "Введите выражение" << endl << ' ' << endl;
	char *vvod = new char [255];
	cin.getline(vvod, 255);
	for (short int i = 0; i != strlen(vvod); i++) {
		if (vvod[i] == ' ') {
			for (short int k = i; k < strlen(vvod); k++) { vvod[k] = vvod[k + 1]; }
			i--;
		}
	}
	
	double *chisl = new double[2]; char znak = '0'; bool proof = 1, minus = 0, znn = 0; short int chn = 0;
	
	for (short int i = 0; i < strlen(vvod) && proof != 0; i++) {
		proof = 0;
		if (vvod[i] == '+' || vvod[i] == '/' || vvod[i] == '*') {
			if (znn == 1 || i == 0) { proof = 0; break; }
			znak = vvod[i]; znn = 1; proof = proverkazn(vvod[i + 1]); continue; 
		}
		if (vvod[i] == '-') {
			minus = 1; proof = proverkazn(vvod[i + 1]);
			if (i > 0 && znak == '0') { znak = '-'; znn = 1; minus = 0; } continue;
		}
		if (47 < vvod[i] && vvod[i] < 58) {
			int kodel;
			if (chn == 2) { proof = 0; break; }
			proof = 1; kodel = vvod[i] - 48; chisl[chn] = kodel; int des = 10;
			if ((47 < vvod[i + 1]) && (vvod[i + 1] < 58)) {
				for (short int k = i + 1; (47 < vvod[k]) && (vvod[k] < 58); k++) {
					kodel = vvod[k] - 48; chisl[chn] = chisl[chn] * 10 + kodel; i = k;
				}
			}
			for (; vvod[i + 1] == '.';) {
				if (vvod[i + 2] < 48 || vvod[i + 2] > 57) { proof = 0; break; }
				for (short int k = i + 2; (47 < vvod[k] && vvod[k] < 58); k++) {
					kodel = vvod[k] - 48;
					double x = double(kodel) / des;
					chisl[chn] = double(chisl[chn] + x);
					des = des * 10; i = k;
				}
			}
			if (minus == 1) { chisl[chn] *= -1; minus = 0;}
			chn++;
		}
	}
	if (chn == 1) { proof = 0; }
	delete[] vvod;
	for (; znn != 0; znn = 0) {
		switch (znak) {
			case '*': {
				chisl[1] = double(chisl[1] * chisl[0]);
				break;
			}
			case '/': {
			if (chisl[1] == 0) { proof = 0; chisl[1] = 1; chisl[0] = 1; }
			chisl[1] = double(chisl[0]) / double(chisl[1]);
			break;
			}
			case '+': { chisl[1] = double(chisl[1] + chisl[0]); break; }
			case '-': { chisl[1] = double(chisl[0] - chisl[1]); break; }
		}
	}

	if (proof != 0) { cout << "Результат: " << chisl[1] << endl; }
	if (proof == 0) { cout << "ERROR" << endl; }

	return 0;
}

bool proverkazn(char x) {
	bool proof = 1;
	if ((x < 48 || x > 57) && (x != '-') && (x < 97 || x>122)) {
		proof = 0;
	}
	return proof;
}