#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"


void multifit(TString fname, TString tname){
    TFile * file= new TFile(fname);
    TTree* t=(TTree*) file->Get(tname);
    double Charge;
    t->SetBranchAddress("Charge",&Charge);
    TH1F * h=new TH1F("H","",400,0,0.2e-9);
    int neventi=t->GetEntries();
    for(int i=0; i<neventi;i++){
        t->GetEntry(i);
        h->Fill(Charge);

    }
    h->Draw();
    
}
