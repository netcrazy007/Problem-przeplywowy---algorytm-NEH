// NEH.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <fstream>
#include <algorithm>
#include <cmath>


using namespace std;
vector<vector<int>> Read(string); // funkcja czytajaca
void sort(vector<vector<int>>&); // funkcja sortuj¹ca rosn¹co (niemalej¹co)
void best_insert(vector<vector<int>>&, vector<int>); // funkcja wstawiajaca zadanie w liste
int main()
{
	string nazwa = "przyklady/neh_1_"; //<--- numer partii danych
	
	vector<vector<int> > processingTimes = Read(nazwa + "in.txt"); 
	vector<vector<int> > result_processingTimes;
	sort(processingTimes);
	//for (int i = 0; i < processingTimes.size(); i++) {
		//for (int j = 0; j < processingTimes[i].size(); j++) {
			//result_processingTimes
		//}
	//}
	//processingTimes.
	vector<int> v;
	v.push_back(0);
	v.push_back(0);
	v.push_back(0);

	best_insert(processingTimes,v);
	/*for (int i = 0; i < processingTimes.size(); i++){
		for (int j = 0; j < processingTimes[i].size(); j++){
			cout << processingTimes[i][j] << " ";
		}
		cout << endl;
	}*/
	// process
	int cMax = -1;

	// ...

	// print result
	cout << cMax << endl;
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
		return sum_a > sum_b;
	});
}
void best_insert(vector<vector<int>>& processingTimes, vector<int> newProcess) {
	unsigned m = processingTimes[0].size();
	unsigned n = processingTimes.size();
	int **time = new int*[m]; // tablica czasow time[maszyna][zadanie]
	list<int> finishTime;
	vector<vector<vector<int>>> permutationList;

	cout << "PRZYCHODZACE" << endl;
	for (unsigned i = 0; i < n; i++) {//wyswietlanie
		for (unsigned j = 0; j < m; j++) {
			cout << " " << processingTimes[i][j];
		}cout << endl;
	}

	cout << "Proces" << endl;
	for (unsigned i = 0; i < m; i++) {
		cout << " " << newProcess[i];
	}cout << endl;
	
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
		permutationList.push_back(PER);
	}

	for (unsigned k = 0; k < permutationList.size(); k++) {
		cout << "PERMUTACJE" << endl;
		for (unsigned i = 0; i < permutationList[0].size(); i++) {//wyswietlanie
			for (unsigned j = 0; j < permutationList[0][0].size(); j++) {
				cout << " " << permutationList[k][i][j];
			}cout << endl;
		}
	}
	
		
	for (unsigned i = 0; i < n+1; i++) {
		time[i] = new int[m];
		for (unsigned j = 0; j < m; j++)
			time[i][j] = 0;
	}
	
	for (unsigned i = 0; i < m; i++) {
		time[0][i] = time[0][i]+ permutationList[0][0][i];
	}
	for (unsigned i = 1; i < n; i++) {
		time[i][0] = time[i - 1][0] + permutationList[0][i][0];
		for (unsigned j = 1; j < m; j++) {
			time[i][j] = max(time[i - 1][j],time[i][j-1]) + permutationList[0][i][j];
		}
	}
	//finishTime.push_back(time[n - 1][n - 1]);
	cout << "WYNIKI" << endl;
	for (unsigned i = 0; i < n+1; i++) {//wyswietlanie
		for (unsigned j = 0; j < m; j++) {
			cout << "[i" << i << "][j" << j << "]" << time[i][j];
		}cout << endl;
	}
	//for (unsigned i = 0; i < n+1; i++) {
	//	delete[] time[i];	
	//}
	//delete[] time;
}