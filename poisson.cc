#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

int main() {
    using namespace std;

    vector<int> zaehler(11);

    ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i] += 1;
    }
    for (int i = 0 ; i < zaehler.size() ; i++) {
      cout << i << ": " << zaehler[i] << endl;
    }

    int total_n = 0;
    ofstream fout("hist.txt");
    for (int i = 0 ; i < zaehler.size() ; i++) {
      total_n += zaehler[i];
      fout << i << " " << zaehler[i] << endl;
    }

    ofstream foutpoi("histpoi.txt");
    for (int i = 0 ; i < zaehler.size() ; i++) {
      double eofpoi = total_n * poisson(3.11538, i);
      foutpoi << i << " " << zaehler[i] << " " << eofpoi << endl;
    }

    fin.close();
    fout.close();
    foutpoi.close();
}
// set terminal svg size 400,300 enhanced fname "arial", 10 butt solid
// set output "out.svg"
// plot "hist.txt" using 1:2 smooth freq with boxes
//
// plot "./histpoi.txt" using 1:2, "./histpoi.txt" using 1:3 smooth freq with boxes