#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"


void multifit(TString fname, TString tname){
    TFile * file = new TFile(fname);
    TTree* t = (TTree*) file -> Get(tname);
    
    double Charge;
    t -> SetBranchAddress("Charge",&Charge);
    
    TH1F * h = new TH1F("H","",400,0,0.4e-9);
    int neventi = t -> GetEntries();
    
    for(int i = 0; i < neventi; i++){
        t -> GetEntry(i);
        h -> Fill(Charge);
    }
    
    
    TF1 *g0 = new TF1("g0", "gaus", (0.04e-9), (0.06e-9));
    TF1 *g1 = new TF1("g1", "gaus", (0.06e-9), (0.08e-9));
    TF1 *g2 = new TF1("g2", "gaus", (0.08e-9), (0.1e-9));
    TF1 *g3 = new TF1("g3", "gaus", (0.1e-9), (0.12e-9));
    TF1 *g4 = new TF1("g4", "gaus", (0.12e-9), (0.14e-9));
    TF1 *g5 = new TF1("g5", "gaus", (0.14e-9), (0.16e-9));
    TF1 *g6 = new TF1("g6", "gaus", (0.16e-9), (0.18e-9));
    TF1 *g7 = new TF1("g7", "gaus", (0.18e-9), (0.2e-9));
    TF1 *g8 = new TF1("g8", "gaus", (0.2e-9), (0.22e-9));
    TF1 *g9 = new TF1("g9", "gaus", (0.24e-9), (0.26e-9));

    h -> Fit(g0, "R");
    h -> Fit(g1, "R+");
    h -> Fit(g2, "R+");
    h -> Fit(g3, "R+");
    h -> Fit(g4, "R+");
    h -> Fit(g5, "R+");
    h -> Fit(g6, "R+");
    h -> Fit(g7, "R+");
    h -> Fit(g8, "R+");
    h -> Fit(g9, "R+");

    
    h -> Draw();
    
}
