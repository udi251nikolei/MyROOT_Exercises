#include <iostream>
#include <fstream>
using namespace std;

#include <TH1.h>
#include <TRandom.h>

void v2_distribution(Int_t nEvents, Double_t V2, Double_t sigmaV2) {

	TH1D* hist = new TH1D("hist", "Histogram; X; Counts", 100, 0, 1);

	// Generating a random value for v2
	TRandom* random = new TRandom(0);

	for(Int_t n = 0; n < nEvents; n++) {
		double v2 = random->Gaus(V2, sigmaV2);
		cout<< "v2 = " << v2 << endl;

		hist->Fill(v2); 
  	}

	TCanvas* c1 = new TCanvas();
  	hist->Draw();
}
