#include <iostream>
#include <fstream>
using namespace std;

#include <TF1.h>
#include <TH1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TString.h>
#include <TRandom.h>

#include "MyClasses.C"

int main() {
	MyEvent* event = new MyEvent();
	event->fV2 = 621;
	event->nTracks = 42;
	event->print();
}
