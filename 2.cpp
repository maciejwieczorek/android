#include <iostream>
#include <list>
#include <cmath>
#include <limits>

using namespace std;

struct Wezel {
	int a;
	int b;
	double w;
};


bool bellmana_forda(list<Wezel*>graf, int x, int m, double konto, double *d) {

	Wezel *pom;
	bool sprawdz = true;

	double *kosztDojscia = new double[x];
	double *kosztDojsciaPoprzednikow = new double[x];

	for (int i = 0; i < x; i++) {
		kosztDojscia[i] = numeric_limits<double>::max();
		kosztDojsciaPoprzednikow[i] = NULL;
		d[i] = -1;
	}

	kosztDojscia[m] = 0;
	d[m] = konto;

	for (int i = 0; i < x - 1; i++) {
		sprawdz = true;
		for (list<Wezel*>::iterator iter = graf.begin(); iter != graf.end(); iter++) {
			pom = *iter;
			if (kosztDojscia[pom->a] > kosztDojscia[pom->b] + pom->w) {
				kosztDojscia[pom->a] = kosztDojscia[pom->b] + pom->w;
				kosztDojsciaPoprzednikow[pom->a] = pom->b;
				sprawdz = false;
			}

			if (kosztDojscia[pom->b] > kosztDojscia[pom->a] + pom->w) {
				kosztDojscia[pom->b] = kosztDojscia[pom->a] + pom->w;
				kosztDojsciaPoprzednikow[pom->b] = pom->a;
				sprawdz = false;
			}
			if (d[pom->b] < d[pom->a] * (1 - pom->w)) {
				d[pom->b] = d[pom->a] * (1 - pom->w);
			}
		}
	}

	for (list<Wezel*>::iterator iter = graf.begin(); iter != graf.end(); iter++) {
		pom = *iter;
		if (kosztDojscia[pom->b] > kosztDojscia[pom->a] + pom->w) {
			return false;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);

	int a, b;
	double i, j;
	int n, m;
	int x;
	bool *statusGieldy;
	Wezel *pom, *pom_2;

	cin >> x;

	statusGieldy = new bool[x];
	list<Wezel*> graf;
	list<Wezel*> grafPowrot;

	for (int i = 0; i < x; i++) {
		bool pom;
		cin >> pom;
		statusGieldy[i] = pom;
	}

	cin >> n;

	for (int k = 0; k < n; k++) {
		cin >> a >> b >> i >> j;
		//i = 1 - i;
		//j = 1 - j;

		pom = new Wezel;
		pom_2 = new Wezel;

		pom->a = a;
		pom->b = b;
		pom->w = i;

		graf.push_back(pom);

		pom_2->a = a;
		pom_2->b = b;
		pom_2->w = j;

		grafPowrot.push_back(pom_2);

	}

	cin >> m;

	double max = 0;
	double *d = new double[x];
	double *d2 = new double[x];


	if (!bellmana_forda(graf, x, m, 100000, d)) {
		cout << "MATEUSZU NIE KOMBINUJ!";
	}
	else {

		if (!bellmana_forda(grafPowrot, x, m, 1, d2)) {
			cout << "MATEUSZU NIE KOMBINUJ!";
		}
		else {
			for (int i = 0; i < x; i++) {
				d[i] = d[i] * 1.20;
				d[i] = d[i] * d2[i];
			}

			for (int i = 0; i < x; i++)
				if (statusGieldy[i] == 1 && max < d[i])
					max = d[i];

			cout << (int)max << endl;
		}
	}


	//system("pause");

	return 0;
}