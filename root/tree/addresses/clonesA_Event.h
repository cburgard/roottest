#include "TTree.h"
#include "Riostream.h"

class TUsrHit:public TObject {
 public:
   TUsrHit(Int_t ev=0);
   virtual ~TUsrHit() {}

 protected:
   Int_t    fEventNumber;       // internal event number
   Int_t    fModuleNumber;      // module serial number
   Int_t    fChannel;           // module channel
   long long fChannelTime; 		// time stamp generated by dgf clock bus (48 bits unsigned!)
//   UShort_t fEventTime[3];      // time stamp generated by dgf clock bus (48 bits unsigned!)

   ClassDef(TUsrHit, 1)         // [Analyze] Hit
};

//______________________________________________________

class TUsrHitBuffer:public TObject {
 public:
   // TUsrHitBuffer(){};
   TUsrHitBuffer(Int_t maxent = 10);
   virtual ~TUsrHitBuffer() {
      cerr << "~~~~~~dtor TUsrHitBuffer " << this << endl;
      delete fHits;
   }
   

   TUsrHit *AddHit(Int_t ev);
   Int_t GetBufSize() { return fHits->GetSize();}
   Int_t GetNofHits() { return fNofHits; }
   Int_t GetNofEntries() { return fNofEntries; } 
   TClonesArray *GetCA() { return (fHits);}
   void Clear(Option_t *opt="");

 protected:

   Int_t fNofEntries;           // max number of entries
   Int_t fNofHits;              // current number of hits
   TClonesArray *fHits;         // array containing hit data

   ClassDef(TUsrHitBuffer, 1)   // [Analyze] Hit buffer
};

//______________________________________________________

class TMrbSubevent_Caen:public TObject {

 public:
   TMrbSubevent_Caen() { cerr << "ctor TMrbSubevent_Caen: " << this << endl;}
   virtual ~TMrbSubevent_Caen() {}
   void Clear(Option_t *opt="") {fHitBuffer.Clear();};

   Int_t           GetTimeStamp() {return fTimeStamp;}
   TUsrHitBuffer * GetHitBuffer() {return &fHitBuffer;};
 protected:

   Int_t fTimeStamp;            // time stamp, same as fUniqueID
   TUsrHitBuffer fHitBuffer;    // hit buffer to store subevent data

   ClassDef(TMrbSubevent_Caen, 1)	// [Analyze] Base class for subevents: CAEN data stored in hit buffer
};

class TMrbSubevent_Nice {
 public:
   TMrbSubevent_Nice() { cerr << "ctor TMrbSubevent_Nice: " << this << endl;}
   virtual ~TMrbSubevent_Nice() {}
   void Clear(Option_t *opt="") {};
   
   Int_t GetNiceTrig() { return fNiceTrig; }

 protected:
   Int_t fNiceTrig;

};

//______________________________________________________

class TUsrSevtData1 : public TMrbSubevent_Caen, public TMrbSubevent_Nice {
 public:
   TUsrSevtData1() { cerr << "ctor TUsrSevtData1 " << this << endl; SetEvent(0);}

   virtual ~TUsrSevtData1() {}
   void Clear(Option_t *opt="") {TMrbSubevent_Caen::Clear(opt); TMrbSubevent_Nice::Clear(opt);}

   void  SetEvent(Int_t ev);
   Int_t GetPileup() {return fPileup; };
   
 protected:
   TString fSevtName;           // subevent name
   Int_t fMer;                  // data2.mer
   Int_t fPileup;               // data2.mpileup

   ClassDef(TUsrSevtData1, 1)   // [Analyze] Store CAEN data in hit buffer
};
//______________________________________________________

class TUsrSevtData2:public TMrbSubevent_Caen {
 public:
   TUsrSevtData2() {SetEvent(0);}

   virtual ~TUsrSevtData2() {}
   void  SetEvent(Int_t ev);
   Int_t GetPileup() {return fPileup; };
   
 protected:
   TString fSevtName;           // subevent name
   Int_t fMer;                  // data2.mer
   Int_t fPileup;               // data2.mpileup

   ClassDef(TUsrSevtData2, 1)   // [Analyze] Store CAEN data in hit buffer
};
