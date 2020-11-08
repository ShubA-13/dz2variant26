#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
int main(int argc, const char* argv[]) {
	if (argc != 3) {
		cerr << "Error: Use three parameters\n";
		return 5;
	}
	const string mode(argv[1]); // Режим работы
	const string file_name(argv[2]); // Имя файла
	ofstream file; //предназначен для вывода и записи файлов
	ifstream file_2; //предназначен для ввода и чтения файлов
	if (mode == "encryption") {
		// Режим шифрование
		string txt;
		int password;
		cout << "write text length == 2 char, it will be encripted: ";
		getline(cin, txt);
		if (txt.length() != 2) cout << "worng length";
		cout << endl << "write password: ";
		cin >> password;
		srand(password);
		int t = 0;
		for (int i = 0; i < static_cast<int>(txt.length()); i++) {
			int n = static_cast<int>(txt[i]);
			if (i == 0) n *= (int)pow(2, 8);
			t += n;
		}
		t = t ^ rand();
		int last = t % 2;
		int prelast = (t % (int)pow(2, 2)) / 2;
		int last_2 = (t % (int)pow(2, 3)) / (int)pow(2,2);
		int last_3 = (t % (int)pow(2, 4)) / (int)pow(2, 3);
		int last_4 = (t % (int)pow(2, 5)) / (int)pow(2, 4);
		t = t >> 5;
		t = last_4 * pow(2, 15)+ last_3*pow(2,14) + last_2*pow(2,13) + prelast*pow(2,12) + last * pow(2, 11) + t;


		file.open(file_name, ios::binary);
		file << t;
		file.close();
	}
	else if (mode == "decryption") {
		// Режим расшифрования
		int password_2;
		cout << endl << "write password: ";
		cin >> password_2;
		srand(password_2);

		file_2.open(file_name, ios::binary);
		int t;
		file_2 >> t;

		int first_t = t / (int)pow(2, 15);
		int second_t = (t / (int)pow(2, 14)) % 2;
		int third_t = (t / (int)pow(2, 13)) % 2;
		int fourth_t = (t / (int)pow(2, 12)) % 2;
		int fivth_t = (t / (int)pow(2, 11)) % 2;
		t = t << 5;
		t = t + first_t * (int)pow(2, 4) + second_t * (int)pow(2, 3) + third_t * (int)pow(2, 2) + fourth_t * 2 + fivth_t;


		t = t ^ rand();
		char n1 = t / (int)pow(2, 8);
		char n2 = t % (int)pow(2, 8);
		cout << n1 << n2;
	}
	return 0;
}