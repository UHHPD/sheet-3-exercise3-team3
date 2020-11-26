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

double prob_normaliser(std::vector<int> daten) {
    double l = 1;
    for (int k = 0 ; k < daten.size() ; k++) {
      int n_k = daten[k];
      l *= poisson(n_k, n_k);
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
    foutlog.close();

    // d)
    ofstream foutdlog("deltanll.txt");
    double lower_mu, upper_mu; // init confidence intervall variables
    bool found_lower_mu = 0, found_upper_mu = 0; // set flags

    double lower_mu2, upper_mu2;
    bool found_lower_mu2 = 0, found_upper_mu2 = 0;

    double double_log_l_min = -2 * log(prob(daten, 3.11538));
    for (double mu = 1 ; mu < 5 ; mu += step_size) {
      foutdlog  << mu << " " << -2 * log(prob(daten, mu)) - double_log_l_min << endl;
      double llratio = -2 * log(abs(prob(daten, mu)/ prob(daten, 3.11538)));

      if (llratio < 4 && found_lower_mu2 == 0) {
        lower_mu2 = mu;
        found_lower_mu2 = 1;
      }

      if (llratio < 1 && found_lower_mu == 0) {
        lower_mu = mu;
        found_lower_mu = 1;
      }
      if (llratio > 1 && found_lower_mu == 1 && found_upper_mu == 0) {
        upper_mu = mu - step_size;
        found_upper_mu = 1;
      }

      if (llratio > 4 && found_lower_mu2 == 1 && found_upper_mu2 == 0) {
        upper_mu2 = mu - step_size;
        found_upper_mu2 = 1;
      }

    }
    foutdlog.close();
    cout << lower_mu << " < mu < " << upper_mu << " for 68 %" << endl;
    cout << "Uncertainty of sample mean: 1.65365/sqrt(234)" << endl;
    cout << lower_mu2 << " < mu < " << upper_mu2 << " for 95 %" << endl;
    cout << "Uncertainty of sample mean: 1.65365/sqrt(234) = 0.1083" << endl;
    cout << "Uncertainty of mean: " << (upper_mu - lower_mu)/2 << endl;

    // e)
    double lambda = prob(daten, 3.11538)/prob_normaliser(daten);
    cout << "Lambda: " << lambda << ", -2ln(Lambda): " << -2*log(lambda) << endl;
    cout << (-2*log(lambda)-233) / (sqrt(2*233)) << endl;

}

// set terminal svg size 400,300 enhanced fname "arial", 10 butt solid
// set output "likelihood.svg"
// plot "likelihood.txt" using 1:2 smooth freq with boxes
//
// set terminal svg size 400,300 enhanced fname "arial", 10 butt solid
// set output "nll.svg"
// plot "nll.txt" using 1:2 smooth freq with lines

// set terminal svg size 400,300 enhanced fname "arial", 10 butt solid
// set output "deltanll.svg"
// plot "deltanll.txt" using 1:2 smooth freq with lines

// plot [2:4][0:10e-195] "likelihood.txt" using 1:2 smooth freq with line