// Analyze_v2.C

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Reading data set within Tree. Get phi value from tree and perform similar calculations seen in Analyze_v2.C in Tutorial15
//
// How to run code:
// $ root
// root [0] .L MyClasses.C
// root [1] .L EG_v2_tree.C
// root [2] rootfuncgenerate(.....) -> This will generate the phi values and put them into Ttree
// root [3] .L Analyze_v2.C
// root [4] analyze_v2_2particle() -> Output will give caluclation results for two methods
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#include <iostream>
#include <fstream>

#include <TMath.h>
#include <TString.h>
#include<TComplex.h>

using namespace std;

void analyze_v2_2particle() {

// Creating a canvas and generating the histogram we want to plot data from file.
	TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
	TH1D* hPhi = new TH1D("hPhi", "ROOT file read phi distribution; phi; Counts", 100, 0, 2*TMath::Pi());

// Sum of all seperate calculated <2> counter per even (Sec. 2.2)
	Double_t avg_v2_std_allEvents = 0;
	Double_t avg_v2_Qvector_allEvents = 0;
	
	//while(file >> helpString >> eventNo) {
		//cout << "Reading event: " << eventNo << endl;
		//nEvents++;

		//Int_t nTracks = -1;
		//file >> helpString >> nTracks;
		//cout << "Event contains " << nTracks << " tracks" << endl;

		//Int_t trackNo;
		//string colon_string;
		//Double_t phi[nTracks]; 

// Open the file and get the tree
  	TFile* file = TFile::Open("phi_dist.root");
  	TTree* tree = (TTree*)file->Get("tree");
  	MyEvent* event = 0;
  	TClonesArray* trackArray = 0;
  	tree->SetBranchAddress("event", &event);
  	tree->SetBranchAddress("track", &trackArray);

  	Int_t nEvents = tree->GetEntries();

	cout << nEvents << endl; // Total size of nEvents -> 1000 events

	for(Int_t n = 0; n < nEvents; n++) {
    	// Read in event n (fills event and trackArray)
    	tree->GetEntry(n);
		cout << "Entry no. " << n << endl; // Prints all Events
		const Int_t nTracks = trackArray->GetEntries();
		cout << "This event has " << nTracks << " tracks" << endl; // For each event, number of Tracks inside that Event is printed

		Double_t phi[nTracks];

		for(Int_t nt = 0; nt < nTracks; nt++) {
			MyTrack* track = (MyTrack*)trackArray->At(nt);
			phi[nt] = track->fPhi; // Get all phi values within that event
			cout << "Phi value for track element " << nt << " is " << phi[nt] << endl;

			hPhi->Fill(phi[nt]);
		}

	}

// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetStatX(0.9);
	gStyle->SetStatY(0.5);
	gStyle->SetOptFit(1111);

// Plotting the v2 function
	hPhi->SetMinimum(0);
	hPhi->Draw();
  
// Saving the canvas as a jpg file
  	//c1->SaveAs("test.jpg");
}
