// NEH.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <limits>

using namespace std;

vector<vector<int>> Read(string); // funkcja czytajaca
void sort(vector<vector<int>>&); // funkcja sortuj¹ca malej¹co (nierosn¹co)
vector<vector<int>> best_insert(vector<vector<int>> , vector<int>); // funkcja wstawiajaca zadanie w liste
int calculateTime(vector<vector<int>>); // zwraca czas potrzebny do wykonania zadan w podanej permutacji
vector<vector<int>> NEH(vector<vector<int>>); // zwraca vector permutacji na podstawie algorytmu NEH

int main(){
	string nazwa = "3"; //<--- numer partii danych do wybrania od 1 do 10
	vector<vector<int> > processingTimes = Read("przyklady/neh_"+nazwa+"_in.txt"); 

	processingTimes = NEH(processingTimes);
	int cMax = calculateTime(processingTimes);

	// print result
	cout << "cMax=" << cMax << endl;
	fstream plik("przyklady/neh_" + nazwa + "_out.txt");
	int poprawna;
	plik >> poprawna;
	cout << "Poprawna wartosc to: " << poprawna << endl;
	plik.close();
	cin.get();
	return 0;
}

vector<vector<int>> Read(string file_name) {
	fstream plik(file_name);
	vector<vector<int> > processingTimes;
	// read input
	if (plik.good()) { // n - liczba zadañ , m - liczba mszyn
		int n, m; 
		plik >> n >> m;
		for (int i = 0; i < n; i++) {
			processingTimes.push_back(vector<int>());
			for (int j = 0; j < m; j++) {
				int p;
				plik >> p;
				processingTimes[i].push_back(p);
			}
		}
		plik.close();
	}
	else {
		cout << "Error: Can not open the file" << endl;
		cin.get();
		exit(0);
	}
	return processingTimes;
}
void sort(vector<vector<int>>& processingTimes) {
	sort(processingTimes.begin(), processingTimes.end(), [](const vector<int> & a, const vector<int> & b)->bool {
		int sum_a = 0, sum_b = 0;
		for (unsigned i = 0; i < a.size(); i++) {
			sum_a += a[i];
		}
		for (unsigned i = 0; i < b.size(); i++) {
			sum_b += b[i];
		}
		return sum_a < sum_b;
	});
}
vector<vector<int>> best_insert(vector<vector<int>> processingTimes, vector<int> newProcess) {

	unsigned m = processingTimes[0].size(); // ilosc maszyn
	unsigned n = processingTimes.size(); // ilosc zadan
	vector<vector<vector<int>>> permutationList; // wektor mo¿liwych permutacji
	tuple<int, int> bestPermutationTime(-1,numeric_limits<int>::max());	// czasy koncowe kazdej permutacji <0-nr permutacji,1 - czas permutacji>
	int cMax;

	for (unsigned i = 0; i < n+1; i++) {
	vector<vector<int>> PER;
		for (unsigned j = 0; j < n; j++) {
			if (i == j) {
				PER.push_back(newProcess);
			}
			PER.push_back(processingTimes[j]);
		}
		if (i == n) {
			PER.push_back(newProcess);
		}

		permutationList.push_back(PER); // tworzenie vektora z permutacjami dla wszystkich mo¿liwoœci
		cMax = calculateTime(PER); // obliczanie czasu 
		if (cMax < get<1>(bestPermutationTime)) { // ustalanie najlepszej wartosci tablicy
			get<0>(bestPermutationTime) = i;
			get<1>(bestPermutationTime) = cMax;
		}
	}
	// wyswietlanie numeru 
	cout << n << endl;
	/*
	// wyswietlanie wydarzen przychodzacych
	cout << "PRZYCHODZACE" << endl;
	for (unsigned i = 0; i < n; i++) {//wyswietlanie
	for (unsigned j = 0; j < m; j++) {
	cout << " " << processingTimes[i][j];
	}cout << endl;
	}
	// proces dodawany
	cout << "Proces" << endl;
	for (unsigned i = 0; i < m; i++) {
	cout << " " << newProcess[i];
	}cout << endl;
	// permutacje z wydarzen przychodzacych i procesu dodawany
	for (unsigned k = 0; k < permutationList.size(); k++) {
		cout << "PERMUTACJE" << endl;
		for (unsigned i = 0; i < permutationList[0].size(); i++) {//wyswietlanie
			for (unsigned j = 0; j < permutationList[0][0].size(); j++) {
				cout << " " << permutationList[k][i][j];
			}cout << endl;
		}
	}
	//*/
	return permutationList.at(get<0>(bestPermutationTime));
}
int calculateTime(vector<vector<int>> processingTimes ){
	unsigned m = processingTimes[0].size(); // ilosc maszyn
	unsigned n = processingTimes.size(); // ilosc zadan
	int **time = new int*[n]; // dwuwymiarowa tablica czasow time[maszyna][zadanie]
	int cMax;

	for (unsigned i = 0; i < n; i++) {
		time[i] = new int[m];
	}
	time[0][0] = processingTimes[0][0];
	for (unsigned i = 1; i < m; i++) {
		time[0][i] = time[0][i - 1] + processingTimes[0][i];
	}
	for (unsigned i = 1; i < n; i++) {
		time[i][0] = time[i - 1][0] + processingTimes[i][0];
		for (unsigned j = 1; j < m; j++) {
			time[i][j] = max(time[i - 1][j], time[i][j - 1]) + processingTimes[i][j];
		}
	}
	/*
	cout << "WYNIK PERMUTACJI" << endl; // wyswietlanie
	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = 0; j < m; j++) {
			cout << "[i" << i << "][j" << j << "]" << time[i][j];
		}cout << endl;
	}*/
	cMax= time[n - 1][m - 1];
	for (unsigned i = 0; i < n; i++) {
		delete[] time[i];
	}
	delete[] time;
	return cMax;
}
vector<vector<int>> NEH(vector<vector<int>>processingTimes) {
	vector<vector<int> > result_processingTimes;
	sort(processingTimes);
	result_processingTimes.push_back(processingTimes.back());
	processingTimes.pop_back();
	while (!processingTimes.empty()) {
		result_processingTimes = best_insert(result_processingTimes, processingTimes.back());
		processingTimes.pop_back();
	}
	return result_processingTimes;
}