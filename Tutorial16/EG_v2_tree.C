// EG_v2_tree.C

#include <iostream>
#include <fstream>
using namespace std;

#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TString.h>
#include <TString.h>
#include <TRandom.h>

#include "MyClasses.C"

void rootfuncgenerate(Int_t nEvents, Double_t sigmaTracks, Double_t sigmaV2) {

// Generating a random value for v2
  TRandom* random = new TRandom(0);
  Double_t v2 = random->Rndm();
  cout<< "v2 = " << v2 << endl;

// Creating a canvas and generating the the histogram and v2 function we want.
	TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
	TH1D* hPhi = new TH1D("hPhi", "ROOT func generated phi distribution; phi; Counts", 100, 0, 2*TMath::Pi());
	TF1* v2Func = new TF1("v2Func", "1 + 2*[0]*cos(2*x)", 0, 2*TMath::Pi());
		v2Func->SetParameter(0, v2);

// Create the outfile and data structure before the loop
	TFile* file = new TFile("phi_dist.root", "RECREATE");
	TTree* tree = new TTree("tree", "Output tree");
	MyEvent* event = new MyEvent();
	tree->Branch("event", &event);
	TClonesArray* trackArray = new TClonesArray("MyTrack", 1000);
	tree->Branch("track", "TClonesArray", &trackArray);
	Int_t nT = 0;

	// Generating nTracks of random phi angles and filling the array for each loop
	for (Int_t e = 0; e < nEvents; e++) {
		// Generating randoms number for nTracks for each events
		Int_t nTracks = random->Rndm()*100;
		Double_t phi[nTracks];

		// In the generate loop: for each event set nTracks and fV2
		event->nTracks = nTracks;
		event->fV2 = v2;

  		for (Int_t t = 0; t < nTracks; t++) {
			phi[t] = v2Func->GetRandom();

			// In the track loop: for each track
			MyTrack* track = new((*trackArray)[nT]) MyTrack();
  			nT++;
  			track->fPhi = phi[t];

    		hPhi->Fill(phi[t]); 
		}

		tree->Fill();
  		trackArray->Clear(); // reset the array but do not delete memory
  	}

	// After all the generation is done, write and close.
  	file->Write();
  	file->Close();
  
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
