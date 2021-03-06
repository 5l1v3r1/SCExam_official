#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>

using namespace std;

int main (int argc, char** argv ){

        if (argc!=2 || argv[1]=="-h" || argv[1]=="--help" ) {
                cout << "Argument has to be an existing .root file" << endl;
                return 0;
        }

        char* filename = argv[1];
        TFile f(filename);

        TCanvas* c = new TCanvas("c1", "", 20, 20, 1000, 1000);
        TH1D* h = (TH1D*)f.Get("histograms/Eabs_tot");
        h->Draw("HIST");

        /*TH1D* h = (TH1D*)f.Get("histograms/Egap");
        int bin1 = h->FindFirstBinAbove(h->GetMaximum()/2);
        int bin2 = h->FindLastBinAbove(h->GetMaximum()/2);
        double fwhm = h->GetBinCenter(bin2) - h->GetBinCenter(bin1);
        double mean = h->GetMean();
        double rms = h->GetRMS();
        double res = fwhm/mean;
        double res2 = rms/mean;

        cout << "FWHM for Egap is: " << fwhm << endl;
        cout << "RMS for Egap is: " << rms << endl;
        cout << "Mean for Egap is: " << mean << endl;
        cout << "Energy resolution (with FWHM) is: " << res*100 << "%" << endl;
        cout << "Energy resolution (with RMS) is: " << res2*100 << "%" << endl;*/

        return 0;
}
