// EG_v2.C

#include <iostream>
#include <fstream>
using namespace std;

#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TString.h>

void rootfuncgenerate(Int_t nEvents, Int_t nTracks, Double_t v2) {

// Creating a canvas and generating the the histogram and v2 function we want.
	TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
	TH1D* hPhi = new TH1D("hPhi", "ROOT func generated phi distribution; phi; Counts", 100, 0, 2*TMath::Pi());
	TF1* v2Func = new TF1("v2Func", "1 + 2*[0]*cos(2*x)", 0, 2*TMath::Pi());
		v2Func->SetParameter(0, v2);

// Creating an array to store phi angle values
	Double_t phi[nTracks];

	// open output file
	ofstream file("phi_dist.dat");

	// Generating nTracks of random phi angles and filling the array for each loop
	for (Int_t e = 0; e < nEvents; e++) {
		file << "Event " << e << endl;
		file << "nTracks " << nTracks << endl;
  		for (Int_t t = 0; t < nTracks; t++) {
			phi[t] = v2Func->GetRandom();
    		hPhi->Fill(phi[t]); 
			file << t << " : " << phi[t] << endl;
		}
  	}

	// closing file "phi_dist.dat"
	file.close();
	cout << "File phi_dist.dat created." << endl;
  
// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetStatX(0.9);
	gStyle->SetStatY(0.5);
	gStyle->SetOptFit(1111);

// Plotting the v2 function
	hPhi->SetMinimum(0);
	hPhi->Draw();
  
// Generating a fitting function to the hPhi histogram
  	TF1* fitFunc = new TF1("fitFunc", "[1]*(2*[0]*cos(2*(x)) + 1)", 0, 2*TMath::Pi());
  	fitFunc->SetParameter(0, v2);
	fitFunc->SetParameter(1, 10);
  	fitFunc->SetLineColor(kRed);
  	hPhi->Fit(fitFunc);
  
// Saving the canvas as a jpg file
  	c1->SaveAs("v2_rootfunc.jpg");
}
