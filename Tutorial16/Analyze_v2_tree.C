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

// Sum of all seperate calculated <2> counter per even (Sec. 2.2)
	Double_t avg_v2_std_allEvents = 0;
	Double_t avg_v2_Qvector_allEvents = 0;

// Open the file and get the tree
  	TFile* file = TFile::Open("phi_dist.root");
  	TTree* tree = (TTree*)file->Get("tree");
  	MyEvent* event = 0;
  	TClonesArray* trackArray = 0;
  	tree->SetBranchAddress("event", &event);
  	tree->SetBranchAddress("track", &trackArray);

  	Int_t nEvents = tree->GetEntries();

	cout << "Analyzing " << nEvents << " events..." << endl;

	for(Int_t n = 0; n < nEvents; n++) {
    	// Read in event n (fills event and trackArray)
    	tree->GetEntry(n);
		//cout << "Entry no. " << n << endl; // Prints all Events

		const Int_t nTracks = trackArray->GetEntries();
		//cout << "This event has " << nTracks << " tracks" << endl; // For each event, number of Tracks inside that Event is printed

		Double_t phi[nTracks];

		for(Int_t nt = 0; nt < nTracks; nt++) {
			MyTrack* track = (MyTrack*)trackArray->At(nt);
			phi[nt] = track->fPhi; // Get all phi values within that event
			//cout << "Phi value for track element " << nt << " is " << phi[nt] << endl;

			//hPhi->Fill(phi[nt]);
		}

	// Starting calculations for on event at a time
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

		// Computing std <2> per Event
		Double_t avg_v2_perEvent = 1/(Double_nTracks*(Double_nTracks - 1)) * sum_cos2_diff;
		avg_v2_std_allEvents += avg_v2_perEvent; // Adding to total sum over all Events

		// cout << "The calculated <2> for Event " << nEvents << " is " << avg_2_perEvent << endl;
		// cout << "The total sum <2> after event " << nEvents <<  " is " << savg2_allEvents << endl;

		// Computing Qvector <2> per Event
		TComplex Q = TComplex(sum_cos2, sum_sin2);
		Double_t Q2 = Q*Q; // Ignoring imaginary numbers
		
		Double_t avg_v2_perEvent_Qvector = (Q2 - Double_nTracks)/(Double_nTracks*(Double_nTracks - 1));
		avg_v2_Qvector_allEvents += avg_v2_perEvent_Qvector;

	}

	// The calculated v2 from 2-particle method (Sec. 2.2)
	Double_t v2_std = sqrt(avg_v2_std_allEvents /nEvents);
	cout << "Std: v2 (average over " << nEvents << " events) = " << v2_std << endl;

	// The calculated v2 from 2-particle method using the Q-vector (Sec. 2.3)
	Double_t v2_Qvector = sqrt(avg_v2_Qvector_allEvents/nEvents);
	cout << "Q-vectors: v2 (average over " << nEvents << " events) = " << v2_std << endl;

}

