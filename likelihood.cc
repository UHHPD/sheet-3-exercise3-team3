#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


// define function to compute prob given a poisson distribution
double poisson(double mu, int k) {
    return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

double prob(std::vector<int> daten, double mu) {
    double l = 1;
    for (int k = 0 ; k < daten.size() ; k++) {
      l *= poisson(mu, daten[k]);
    }
    return l;
}

int main() {
    using namespace std;


    ifstream fin("datensumme.txt");
    int n_i;
    vector<int> daten;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        daten.push_back(n_i);
    }
    // a)
    cout << prob(daten, 3.11538) << endl;
    fin.close();

    // b)
    ofstream fout("likelihood.txt");
    double step_size = 0.01;
    for (double mu = 0 ; mu < 6 ; mu += step_size) {
      fout << mu << " " << prob(daten, mu) << endl;
    }
    fout.close();

    // c)
    ofstream foutlog("nll.txt");
    for (double mu = 0 ; mu < 6 ; mu += step_size) {
      foutlog  << mu << " " << -2 * log(prob(daten, mu)) << endl;
    }
    fout.close();
}

// set terminal svg size 400,300 enhanced fname "arial", 10 butt solid
// set output "likelihood.svg"
// plot "likelihood.txt" using 1:2 smooth freq with boxes
//
// set output "nll.svg"
// plot "nll.txt" using 1:2 smooth freq with lines

// plot [2:4][0:10e-195] "likelihood.txt" using 1:2 smooth freq with line