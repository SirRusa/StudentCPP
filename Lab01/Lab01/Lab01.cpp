#include "pch.h"
#include <iostream>
#include <locale>
#include <cmath>

using namespace std;

char vvod[400], neiz; int xv,k, i, des, s, kodel, bukv = 0, userbukv; int numneiz = 0, proof = 1;
char znak[200]; double chisl[200], neiz_zn, x; int znn = 0, chn = 0;
void proverkazn(); void skobki(int i); void pr1(int i); void pr2(int i);
int main()
{
	char answer = 'y';
	setlocale(LC_ALL, "RUSSIAN");
	do {
		cout << "Введите выражение" << endl << ' ' << endl;
		for (i = 0; vvod[i-1] != '='; i++) {
			cin >> (vvod[i]);
			if (vvod[i] == '\n' ) vvod[i] = '=';
		}
		bukv = 0; znn = 0, chn = 0; numneiz = 0, proof = 1;
		cout << "Сколько неизвестных переменных в уравнении?" << endl;
		while (!(cin >> userbukv) || (cin.peek() != '\n')) { cin.clear(); while (cin.get() != '\n'); cout << "Введите значение корректно" << endl; }
		// Сколько всего неизвестных переменных (букв) и сколько введет пользователь
		for (i = 0; vvod[i] != '='; i++) {
			kodel = vvod[i];
			if (kodel > 96 && kodel < 123) {
				bukv = bukv + 1;
			}
		}
		if (userbukv != bukv) { cout << "ERROR" << endl; proof = 0; }
		//Ввод переменных если они есть, запоминается какая переменная встречается в каком порядке, позже значиния подставляются в нужном порядке.
		//Если пользователь вводит букву которой не было или вводит некоректное значение выводится ошибка. 
		double neizm[100];
		for (bukv; bukv != 0 && proof != 0; bukv--) {
			cout << "Какой переменной внести значение?" << endl;
			cin >> neiz; proof = 0;
			for (i = 0; vvod[i] != '='; i++) { if (vvod[i] == neiz) { proof = 1; } } if (proof != 1) { cout << "ERROR" << endl;  proof = 0; continue; }
			cout << "Введите значение переменной" << ' ' << neiz << endl; neiz_zn = 0;
			while (!(cin >> neiz_zn) || (cin.peek() != '\n')) { cin.clear(); while (cin.get() != '\n'); cout << "Введите значение переменной -" << neiz << "- корректно" << endl; }  numneiz = 0;
			for (i = 0; vvod[i] != '='; i++) {
				kodel = vvod[i]; if (kodel > 96 && kodel < 123) { if (vvod[i] == neiz) { neizm[numneiz] = neiz_zn; } numneiz = numneiz + 1; }
			}
		}
		numneiz = 0; s = 0;
		//Массив знаков и чисел для обратной польской записи
		//char znak[100]; double chisl[100]; int znn, chn; znn = 0; chn = 0;
		for (i = 0; vvod[i] != '=' && proof != 0; i++) {
			kodel = vvod[i]; proof = 0;
			if (vvod[i] == '(') { s = s + 1; znak[znn] = '('; proverkazn(); }
			if (vvod[i] == ')') { s = s - 1; znak[znn] = ')'; proof = 1; znn++; 
				if (s < 0) { proof = 0; cout << "ERROR" << endl; } }
			if (vvod[i] == '*') { proverkazn(); }
			if (vvod[i] == '/') { proverkazn(); }
			if (vvod[i] == '^') { proverkazn(); }
			if (vvod[i] == '#') { proverkazn(); }
			if (vvod[i] == '&') { proverkazn(); }
			if (vvod[i] == '%') { proverkazn(); }
			if (vvod[i] == '+') { proverkazn(); }
			if (vvod[i] == '-') { proverkazn(); }
			if (kodel > 96 && kodel < 123) { chisl[chn] = neizm[numneiz]; chn++; numneiz++; proof = 1; 
			if ((vvod[i + 1] > 96 && vvod[i+1] < 123) || (vvod[i+1] > 47 && vvod[i+1] < 58 )) { cout << "ERROR" << endl; proof = 0; continue; } }
			if (47 < kodel && kodel < 58) {
				kodel = kodel - 48; chisl[chn] = kodel; des = 10; proof = 1;
				if (47 < (kodel = vvod[i + 1]) && (kodel = vvod[i + 1]) < 58) {
					for (k = i + 1; (47 < vvod[k]) && (vvod[k] < 58); k++) { 
						kodel = vvod[k] - 48; chisl[chn] = chisl[chn] * 10 + kodel; i = k; } 
				}
				if (vvod[i + 1] == '.') { i++; for (k = i + 1; (47 < vvod[k] && vvod[k] < 58); k++) { kodel = vvod[k] - 48; x = double(kodel) / des; chisl[chn] = double(chisl[chn] + x); des = des * 10; i = k; } }
				chn++;
			}
			if (proof == 0) { cout << "ERROR" << endl; }
		}
		if (s > 0 && proof != 0) { cout << "ERROR" << endl; proof = 0; }
		for (k = 0; k != znn && proof != 0; k++) { if (znak[k] == '(') { skobki(k); } }
		for (k = 0; k != znn && proof != 0; k++) { xv = k; pr1(k); k = xv; }
		for (k = 0; k != znn && proof != 0; k++) { xv = k; pr2(k); k = xv; }
		if (proof != 0) { cout << ' ' << endl << "Ответ = " << chisl[0] << endl; }
		cout << "Хотите решить другой пример?" << endl; cout << "Введите 'y' для повтора" << endl;
		cin >> answer; cout << ' ' << endl;
	} while (answer == 'y');
		cout << "До свидания" << endl;
		return 0;
}

void proverkazn() { znak[znn] = vvod[i];  proof = 1; znn++; 
if ((vvod[i + 1] < 48 || vvod[i + 1] > 57) && (vvod[i + 1] != '(') && (vvod[i + 1] < 97 || vvod[i + 1]>122) ) { 
	proof = 0; 
	} 
}

void skobki (int i) {
	for (s = i; s != znn; s++) { znak[s] = znak[s + 1]; } znn--;
	for (s = i; znak[s] != ')'; s++) { if (znak[s] == '(') { xv = s; skobki(xv); s = xv-1; } }
	for (s = i; znak[s] != ')' && proof != 0; s++) { xv = s; pr1(xv); s = xv; }
	for (s = i; znak[s] != ')' && proof != 0; s++) { xv = s; pr2(xv); s = xv; }
	for (s = i; s != znn; s++) { znak[s] = znak[s + 1]; } znn--; k--;
}

void pr1 (int i) { for (i = xv; i == xv; i++){
	if (znak[i] == '&') {
		if (chisl[i] == 0 || chisl[i + 1] == 0) { cout << "ERROR" << endl; proof = 0; continue; } 
		chisl[i + 1] = double(log(chisl[i]) / log(chisl[i + 1])); }
	if (znak[i] == '#') { 
		if (chisl[i + 1] < 0) { cout << "ERROR" << endl; proof = 0; continue; } 
		chisl[i + 1] = pow(double(chisl[i + 1]), (double(1) / chisl[i])); }
	if (znak[i] == '^') { chisl[i + 1] = pow(double(chisl[i]), double(chisl[i + 1])); }
	if (znak[i] == '%') { 
		if (chisl[i + 1] == 0) { cout << "ERROR" << endl; proof = 0; continue; } 
		chisl[i + 1] = fmod(chisl[i], chisl[i + 1]); }
	if (znak[i] == '*') { chisl[i + 1] = double(chisl[i] * chisl[i + 1]); }
	if (znak[i] == '/') { if (chisl[i + 1] == 0) { cout << "ERROR" << endl; proof = 0; continue; } chisl[i + 1] = double(chisl[i]) / double(chisl[i + 1]); }
	if (znak[i] == '/' || znak[i] == '*' || znak[i] == '#' || znak[i] == '%' || znak[i] == '&' || znak[i] == '^') {
		for (s = i; s != znn; s++) { znak[s] = znak[s + 1]; chisl[s] = chisl[s + 1]; } xv--; znn--;
		}
	}
}

void pr2(int i) {
	if (znak[i] == '+') { chisl[i + 1] = double(chisl[i] + chisl[i + 1]); }
	if (znak[i] == '-') { chisl[i + 1] = double(chisl[i] - chisl[i + 1]); }
	for (s = i; s != znn; s++) { znak[s] = znak[s + 1]; chisl[s] = chisl[s + 1]; } xv--; znn--;
}