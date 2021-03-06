#include "pch.h"
#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

int proverkazn(char x);

void priority2(unsigned char *i, short int *znn, char znak[], double chisl[]);
void priority1(unsigned char *i, short int *znn, char znak[], double chisl[], short int *proof);
void skobki(unsigned char *i, short int *znn, char znak[], double chisl[], short int *proof);

int proofpriority(char z);
void sdvig(unsigned char *i, short int *znn, char znak[], double chisl[]);
void sdvigznak(unsigned char *i, short int *znn, char znak[]);

int main()
{
	char vvod[255], answer;
	char vse_znaki[][2] = { {'+', '0'}, {'-', '0'}, {'/', '1'}, {'^', '1'}, {'&','1'}, {'#','1'}, {'%','1'} };
	setlocale(LC_ALL, "RUSSIAN");
	do {
		cout << "Введите выражение" << endl << ' ' << endl;
		cin.getline(vvod, 255);
		short int bukv = 0, znn = 0, userbukv, chn = 0, numneiz = 0, proof = 1;
		for (unsigned char i = 0; i < strlen(vvod) - 1; i++) {
			if (vvod[i] == '=') { proof = 0; vvod[0] = '='; break; }
		}
		vvod[strlen(vvod)] = '=';
		for (unsigned char i = 0; vvod[i] != '='; i++) {
			if (vvod[i] == ' ') {
				for (unsigned char k = i; vvod[k] != '='; k++) { vvod[k] = vvod[k + 1]; }
				i--;
			}
		}
		if (vvod[0] == '-') { proof = 0; }
		cout << "Сколько неизвестных переменных в уравнении?" << endl;
		while (!(cin >> userbukv) || (cin.peek() != '\n')) {
			cin.clear(); while (cin.get() != '\n'); cout << "Введите значение корректно" << endl;
		}

		// Сколько всего неизвестных переменных (букв) и сколько введет пользователь
		char perem[150];
		for (unsigned char i = 0; vvod[i] != '='; i++) {
			if (vvod[i] > 96 && vvod[i] < 123) {
				perem[bukv] = vvod[i]; perem[bukv + 1] = '1';
				int xxx = bukv;
				for (unsigned char s = 0; perem[s] != '1'; s++) {
					if (perem[s] == vvod[i] && s != bukv) { xxx--; }
				}
				bukv = xxx + 1;
			}
		}
		if (userbukv != bukv) { proof = 0; }

		//Ввод переменных если они есть, запоминается какая переменная встречается в каком порядке, позже значения подставляются в нужном порядке.
		//Если пользователь вводит букву которой не было или вводит некоректное значение выводится ошибка. 
		double neizm[100], neiz_zn; short int kodel; char neiz = '1';
		for (bukv; bukv != 0 && proof != 0; bukv--) {
			cout << "Какой переменной внести значение?" << endl;
			char neizpr[100]; cin.ignore(); cin.getline(neizpr, 100);
			proof = 0;
			if (strlen(neizpr) > 1 || strlen(neizpr) == 0) { break; }
			neiz = neizpr[0];
			for (unsigned char i = 0; perem[i] != '1'; i++) {
				if (neiz == perem[i]) { perem[i] = '0'; proof = 1; }
			}

			if (proof != 1) { proof = 0; break; }
			cout << "Введите значение переменной" << ' ' << neiz << endl; neiz_zn = 0;
			while (!(cin >> neiz_zn) || (cin.peek() != '\n')) {
				cin.clear(); while (cin.get() != '\n'); cout << "Введите значение переменной '" << neiz << "' корректно" << endl;
			}
			numneiz = 0;
			for (unsigned char i = 0; vvod[i] != '='; i++) {
				kodel = vvod[i]; if (kodel > 96 && kodel < 123) {
					if (vvod[i] == neiz) {
						neizm[numneiz] = neiz_zn;
					} numneiz++;
				}
			}
		}

		numneiz = 0; short int s = 0; char znak[200]; double chisl[150]; chn = 0;
		for (short int i = 0; vvod[i] != '=' && proof != 0; i++) {
			proof = 0; 
			if (vvod[i] == '+' || vvod[i] == '-' || vvod[i] == '/' || vvod[i] == '*' || vvod[i] == '#' || vvod[i] == '^' || vvod[i] == '%' || vvod[i] == '&') {
				znak[znn] = vvod[i]; znn++; proof = proverkazn(vvod[i + 1]); continue;
			}
			if (vvod[i] == '(') {
				s++; znak[znn] = '('; znn++; proof = proverkazn(vvod[i + 1]); continue;
			}
			if (vvod[i] == ')') {
				s--; znak[znn] = ')'; znn++; if ((proof = proverkazn(vvod[i + 1])) == 0) { proof = 1; } continue;
			}
			kodel = vvod[i];
			if (kodel > 96 && kodel < 123) {
				chisl[chn] = neizm[numneiz]; chn++; numneiz++; proof = 1;
				if ((vvod[i + 1] > 96 && vvod[i + 1] < 123) || (vvod[i + 1] > 47 && vvod[i + 1] < 58)) { proof = 0; }
				continue;
			}
			if (47 < vvod[i] && vvod[i] < 58) {
				proof = 1; kodel = vvod[i] - 48; chisl[chn] = kodel; int des = 10;
				if (47 < (kodel = vvod[i + 1]) && (kodel = vvod[i + 1]) < 58) {
					for (unsigned char k = i + 1; (47 < vvod[k]) && (vvod[k] < 58); k++) {
						kodel = vvod[k] - 48; chisl[chn] = chisl[chn] * 10 + kodel; i = k;
					}
				}
				if (vvod[i + 1] == '.') {
					if (vvod[i + 2] < 48 || vvod[i + 2] > 57) { proof = 0; }
					for (unsigned char k = i + 2; (47 < vvod[k] && vvod[k] < 58); k++) {
						kodel = vvod[k] - 48;
						double x = double(kodel) / des;
						chisl[chn] = double(chisl[chn] + x);
						des = des * 10; i = k;
					}
				}
				chn++;
			}
		}
		if (s != 0) {proof = 0;}
		for (unsigned char i = 0; i != znn && proof != 0; i++) {
			if (znak[i] == '(') { skobki(&i, &znn, znak, chisl, &proof); }
		}
		for (unsigned char i = 0; i != znn && proof != 0; i++) {
			priority1(&i, &znn, znak, chisl, &proof);
		}

		for (unsigned char i = 0; i != znn && proof != 0; i++) {
			priority2(&i, &znn, znak, chisl);
		}
		if (proof == 0 || s != 0) { cout << "ERROR" << endl; proof = 0; }
		if (proof != 0) { cout << ' ' << endl << "Ответ = " << chisl[0] << endl; }
		cout << "Хотите решить другой пример?" << endl; cout << "Введите 'y' для повтора" << endl;
		cin >> answer; cout << ' ' << endl; cin.ignore();
	} while (answer == 'y');
	cout << "До свидания" << endl;
	return 0;
}

int proverkazn(char x) {
	short int proof = 1;
	if ((x < 48 || x > 57) && (x != '(') && (x < 97 || x>122)) {
		proof = 0;
	}
	return proof;
}

void priority1(unsigned char *i, short int *znn, char znak[], double chisl[], short int *proof) {
	*proof = proofpriority(znak[*i]);
	if (*proof == 2) {
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

int proofpriority(char z) {
	short int proof = 1;
	if (z == '/' || z == '*' || z == '#' || z == '^' || z == '%' || z == '&') { proof = 2; }
	return proof;
}

void priority2(unsigned char *i, short int *znn, char znak[], double chisl[]) {
	switch (znak[*i]) {
	case '+': { chisl[*i + 1] = double(chisl[*i] + chisl[*i + 1]); break; }
	case '-': { chisl[*i + 1] = double(chisl[*i] - chisl[*i + 1]); break; }
	}
	sdvig(&*i, &*znn, znak, chisl);
}

void skobki(unsigned char *i, short int *znn, char znak[], double chisl[], short int *proof) {
	sdvigznak(&*i, &*znn, znak);
	for (unsigned char k = *i; znak[k] != ')'; k++) {
		if (znak[k] == '(') { skobki(&k, &*znn, znak, chisl, &*proof); k--; }
	}
	for (unsigned char k = *i; znak[k] != ')'; k++) { priority1(&k, &*znn, znak, chisl, &*proof); }
	for (unsigned char k = *i; znak[k] != ')'; k++) { priority2(&k, &*znn, znak, chisl); }
	sdvigznak(&*i, &*znn, znak);
}

void sdvig(unsigned char *i, short int *znn, char znak[], double chisl[]) {
	for (unsigned char k = *i; k != *znn; k++) {
		znak[k] = znak[k + 1]; chisl[k] = chisl[k + 1];
	}
	*znn = *znn - 1; *i = *i - 1;
}

void sdvigznak(unsigned char *i, short int *znn, char znak[]) {
	for (unsigned char k = *i; k != *znn; k++) {
		znak[k] = znak[k + 1];
	}
	*znn = *znn - 1;
}