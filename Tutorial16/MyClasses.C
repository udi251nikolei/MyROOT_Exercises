// MyClasses.C

#include <TObject.h>
#include <iostream>

using namespace std;

#ifndef MyClasses_C
#define MyClasses_C

// MyEvent Class header and Implementation
class MyEvent : public TObject {
	public:
  		Int_t nTracks;
  		Double_t fV2;
  		
		MyEvent();
		
		//void print();

		ClassDef(MyEvent, 1); // Help class, 1=version
};

// MyTrack Class header and implementation
class MyTrack : public TObject {
	public:
		Double_t fPhi;

		MyTrack();
		
		//void print();
		
		ClassDef(MyTrack,1);
};

#endif // MyClasses_C

ClassImp(MyEvent) // No semi-colon!

MyEvent::MyEvent():
	TObject(),
	nTracks(),
	fV2() { // default constructor
	}

//void MyEvent::print() {cout << "Input value for fV2 is " << fV2 << endl;}

ClassImp(MyTrack)

MyTrack::MyTrack():
	TObject(),
	fPhi() {}

//void MyTrack::print() {cout << "Input value for fPhi is " << fPhi << endl;}
 
