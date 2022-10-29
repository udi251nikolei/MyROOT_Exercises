// Analyze_v2.C

#include <iostream>
#include <fstream>

#include <TMath.h>
#include <TString.h>
#include<TComplex.h>

using namespace std;

void analyze_v2_2particle() {

	// Opening the input file
	ifstream file("phi_dist.dat");
	if (!file) {
		throw runtime_error{"File could not be opened."};
	}

// Creating a canvas and generating the histogram we want to plot data from file.
	TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
	TH1D* hPhi = new TH1D("hPhi", "ROOT file read phi distribution; phi; Counts", 100, 0, 2*TMath::Pi());

	Int_t nEvents = 0; // event counter
	string helpString; // help variable
	Int_t eventNo = -1;

// Sum of all seperate calculated <2> counter per even (Sec. 2.2)
	Double_t avg_v2_std_allEvents = 0;
	Double_t avg_v2_Qvector_allEvents = 0;
	
	while(file >> helpString >> eventNo) {
		// cout << "Reading event: " << eventNo << endl;
		nEvents++;

		Int_t nTracks = -1;
		file >> helpString >> nTracks;
		// cout << "Event contains " << nTracks << " tracks" << endl;

		Int_t trackNo;
		string colon_string;
		Double_t phi[nTracks]; 

		for(Int_t nt = 0; nt < nTracks; nt++) {
			file >> trackNo >> colon_string >> phi[nt];
			//cout << "In event " << nEvents << " the phi in trackNo " << trackNo << " is " << phi[nt] << endl;
			hPhi->Fill(phi[nt]);
		}

		// 2-particle standard method (Sec. 2.2)
		Double_t sum_cos2_diff = 0;

		// 2-particle Q vectors (Sec. 2.3)
		Double_t sum_cos2 = 0;
		Double_t sum_sin2 = 0;

		for(Int_t s = 0; s < nTracks; s++) { 

			// Computing Q vector
			sum_cos2 += cos(2*phi[s]);
			sum_sin2 += sin(2*phi[s]);

			for(Int_t t = s+1; t < nTracks; t++) {
				sum_cos2_diff += 2*cos(2*(phi[s]-phi[t]));
			}
		}

		Double_t Double_nTracks = nTracks;

		// Computing <2> per Event
		Double_t avg_v2_perEvent = 1/(Double_nTracks*(Double_nTracks - 1)) * sum_cos2_diff;
		avg_v2_std_allEvents += avg_v2_perEvent; // Adding to total sum over all Events

		// cout << "The calculated <2> for Event " << nEvents << " is " << avg_2_perEvent << endl;
		// cout << "The total sum <2> after event " << nEvents <<  " is " << savg2_allEvents << endl;

		TComplex g = TComplex(sum_cos2, sum_sin2);
		Double_t g2 = g*g; // Ignoring imaginary numbers
		
		Double_t avg_v2_perEvent_Qvector = (g2 - Double_nTracks)/(Double_nTracks*(Double_nTracks - 1));
		avg_v2_Qvector_allEvents += avg_v2_perEvent_Qvector;
		
	}

// The calculated v2 from 2-particle method (Sec. 2.2)
	Double_t v2_std = sqrt(avg_v2_std_allEvents /nEvents);
	cout << "Std: v2 (average over " << nEvents << " events) = " << v2_std << endl;

	Double_t v2_Qvector = sqrt(avg_v2_Qvector_allEvents/nEvents);
	cout << "Q-vectors: v2 (average over " << nEvents << " events) = " << v2_std << endl;

// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetStatX(0.9);
	gStyle->SetStatY(0.5);
	gStyle->SetOptFit(1111);

// Plotting the v2 function
	hPhi->SetMinimum(0);
	hPhi->Draw();
  
// Saving the canvas as a jpg file
  	c1->SaveAs("Analyze_v2.jpg");
}
