#include "pch.h"
#include <iostream>
#include <cmath>
#include <locale>

#define AndProof && proof != 0

using namespace std;

void sdvig(unsigned char *i, unsigned char *znn, char znak[], double chisl[]) {
	for (unsigned char k = *i; k != *znn; k++) {
		znak[k] = znak[k + 1]; chisl[k] = chisl[k + 1];
	}
	*znn = *znn - 1; *i = *i - 1;
}

void sdvigznak(unsigned char *i, unsigned char *znn, char znak[]) {
	for (unsigned char k = *i; k != *znn; k++) {
		znak[k] = znak[k + 1];
	}
	*znn = *znn - 1;
}

void priority1(unsigned char *i, unsigned char *znn, char znak[], double chisl[], bool *proof) {
	if (znak[*i] == '/' || znak[*i] == '*' || znak[*i] == '#' || znak[*i] == '^' || znak[*i] == '%' || znak[*i] == '&') {
		switch (znak[*i]) {
			case '&': {
				if (chisl[*i] == 0 || chisl[*i + 1] == 0) { *proof = 0; chisl[*i] = 1; chisl[*i + 1] = 1; }
				chisl[*i + 1] = double(log(chisl[*i]) / log(chisl[*i + 1]));
				break;
			}
			case '#': {
				if (chisl[*i + 1] < 0) { *proof = 0; chisl[*i] = 1; chisl[*i + 1] = 1; }
				chisl[*i + 1] = pow(double(chisl[*i + 1]), (double(1) / chisl[*i]));
				break;
			}
			case '^': {
				chisl[*i + 1] = pow(double(chisl[*i]), double(chisl[*i + 1]));
				break;
			}
			case '%': {
				if (chisl[*i + 1] == 0) { *proof = 0; chisl[*i] = 1; chisl[*i + 1] = 1; }
				chisl[*i + 1] = fmod(chisl[*i], chisl[*i + 1]);
				break;
			}
			case '*': {
				chisl[*i + 1] = double(chisl[*i] * chisl[*i + 1]);
				break;
			}
			case '/': {
				if (chisl[*i + 1] == 0) { *proof = 0; chisl[*i] = 1; chisl[*i + 1] = 1; }
				chisl[*i + 1] = double(chisl[*i]) / double(chisl[*i + 1]);
				break;
			}
		}
		sdvig(&*i, &*znn, znak, chisl);
	}
}

void priority2(unsigned char *i, unsigned char *znn, char znak[], double chisl[]) {
	switch (znak[*i]) {
	case '+': { chisl[*i + 1] = double(chisl[*i] + chisl[*i + 1]); break; }
	case '-': { chisl[*i + 1] = double(chisl[*i] - chisl[*i + 1]); break; }
	}
	sdvig(&*i, &*znn, znak, chisl);
}

void skobki(unsigned char *i, unsigned char *znn, char znak[], double chisl[], bool *proof) {
	sdvigznak(&*i, &*znn, znak);
	for (unsigned char k = *i; znak[k] != ')'; k++) {
		if (znak[k] == '(') { skobki(&k, &*znn, znak, chisl, &*proof); k--; }
	}
	for (unsigned char k = *i; znak[k] != ')'; k++) { priority1(&k, &*znn, znak, chisl, &*proof); }
	for (unsigned char k = *i; znak[k] != ')'; k++) { priority2(&k, &*znn, znak, chisl); }
	sdvigznak(&*i, &*znn, znak);
}

int main()
{
	setlocale(0, "Russian");
	cout << "Введите выражение" << endl;
	char *vvod = new char[255];
	cin.getline(vvod, 255);
	bool proof = 1;
	if (strlen(vvod) == 0) { proof = 0; }

	for (unsigned char i = 0; i < strlen(vvod) AndProof; i++) { 
		if (vvod[i] == ' ') {
			for (unsigned char k = i; k < strlen(vvod); k++) {
				vvod[k] = vvod[k + 1];
			}
			i--;
		}
	}
	
	char *znak = new char[130]; double *chisl = new double[130]; unsigned char znn = 0, chn = 0, sk = 0;
	
	if (vvod[0] == '-') { chisl[0] = 0; chn++; vvod[0] = '0'; znak[0] = '-'; znn++; }

	for (unsigned char i = 0; i < strlen(vvod) AndProof; i++) {
		proof = 0;
		if (vvod[i] == '-') {
			proof = 1;
			if (vvod[i - 1] < 48 || vvod[i - 1]>57) { chisl[chn] = -1; chn++; znak[znn] = '*'; znn++; continue; }
			znak[znn] = '-'; znn++; continue;
		}
		if (vvod[i] == '+' || vvod[i] == '*' || vvod[i] == '/' || vvod[i] == '%' || vvod[i] == '#' || vvod[i] == '^') {
			proof = 1; znak[znn] = vvod[i]; znn++;
			if (vvod[i + 1] < 48 || vvod[i + 1] >57) { proof = 0; }
		}
		if (vvod[i] == '(') {
			proof = 1; sk++; znak[znn] = vvod[i]; znn++; continue;
		}
		if (vvod[i] == ')') { 
			proof = 1; sk--; znak[znn] = vvod[i]; znn++; if (sk < 0) { proof = 0; }
			if (vvod[i + 1] == '(') { znak[znn] == '*'; znn++;} continue;
		}
		if (proof == 1 && (vvod[i + 1] < 48 || vvod[i + 1] > 57) && vvod[i+1] != '-') { proof = 0; continue; }
		if (47 < vvod[i] && vvod[i] < 58 ) { 
			proof = 1; chisl[chn] = vvod[i] - 48;
			for (unsigned char k = i + 1; 47 < vvod[k] && vvod[k] < 58; k++) {
				chisl[chn] = chisl[chn] * 10 + vvod[k] - 48; i = k;
			}
			if (vvod[i + 1] == '.' || vvod[i + 1] == ',') {
				int des = 10;
				if (vvod[i + 2] < 48 || vvod[i + 2] >57) { proof = 0; continue; }
				for (unsigned char k = i + 2; 47 < vvod[k] && vvod[k] < 58; k++) {
					double x = double(vvod[k] - 48) / des;
					chisl[chn] = double(chisl[chn] + x);
					des = des * 10; i = k;
				}
			}
			chn++;
		}
	}
	if (sk != 0) { proof = 0;}

	for (unsigned char i = 0; i != znn AndProof; i++) {
		if (znak[i] == '(') { skobki(&i, &znn, znak, chisl, &proof); }
	}
	for (unsigned char i = 0; i != znn AndProof; i++) {
		priority1(&i, &znn, znak, chisl, &proof);
	}

	for (unsigned char i = 0; i != znn AndProof; i++) {
		priority2(&i, &znn, znak, chisl);
	}
	if (proof == 0) { cout << "ERROR" << endl; proof = 0; }
	if (proof != 0) { cout << ' ' << endl << "Ответ = " << chisl[0] << endl; }

	return 0;
}

//&& vvod[i - 1] == '('