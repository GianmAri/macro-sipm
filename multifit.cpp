#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
using namespace std;


void multifit(TString fname, TString tname){
    TFile * file= new TFile(fname);
    TTree* t=(TTree*) file->Get(tname);
    double Charge;
    t->SetBranchAddress("Charge",&Charge);
    TH1F * h=new TH1F("H","",300,0,0.2e-9);
    int neventi=t->GetEntries();
    for(int i=0; i<neventi;i++){
        t->GetEntry(i);
        h->Fill(Charge);

    }
    TCanvas *c0=new TCanvas();
        TF1 *g0 = new TF1("g0", "gaus", (0.005e-9), (0.025e-9));
        TF1 *g1 = new TF1("g1", "gaus", (0.025e-9), (0.040e-9));
        TF1 *g2 = new TF1("g2", "gaus", (0.04e-9), (0.055e-9));
        
        TF1 *g3 = new TF1("g3", "gaus", (0.055e-9), (0.070e-9));
        TF1 *g4 = new TF1("g4", "gaus", (0.073e-9), (0.085e-9));
        TF1 *g5 = new TF1("g5", "gaus", (0.09e-9), (0.100e-9));
        TF1 *g6 = new TF1("g6", "gaus", (0.105e-9), (0.116e-9));
        TF1 *g7 = new TF1("g7", "gaus", (0.12e-9), (0.132e-9));
        

        h -> Fit(g0, "R");
        h -> Fit(g1, "R+");
        h -> Fit(g2, "R+");
        h -> Fit(g3, "R+");
        h -> Fit(g4, "R+");
        h -> Fit(g5, "R+");
        h -> Fit(g6, "R+");
        h -> Fit(g7, "R+");
 
    h->Draw();
    
    TCanvas *c2=new TCanvas();
    
    Double_t x[8],y[8],err[8];
    
    Double_t a0=g0->GetParameter("Mean");
    Double_t a1=g1->GetParameter("Mean");
    Double_t a2=g2->GetParameter("Mean");
    Double_t a3=g3->GetParameter("Mean");
    Double_t a4=g4->GetParameter("Mean");
    Double_t a5=g5->GetParameter("Mean");
    Double_t a6=g6->GetParameter("Mean");
    Double_t a7=g7->GetParameter("Mean");
    
    Double_t e0=g0->GetParameter(2);
    Double_t e1=g1->GetParameter(2);
    Double_t e2=g2->GetParameter(2);
    Double_t e3=g3->GetParameter(2);
    Double_t e4=g4->GetParameter(2);
    Double_t e5=g5->GetParameter(2);
    Double_t e6=g6->GetParameter(2);
    Double_t e7=g7->GetParameter(2);
    
    for(int i=0;i<=7;i++){
        x[i]=i+1;
        
    }
    y[0]=a0;
    y[1]=a1;
    y[2]=a2;
    y[3]=a3;
    y[4]=a4;
    y[5]=a5;
    y[6]=a6;
    y[7]=a7;
    
    err[0]=e0;
    err[1]=e1;
    err[2]=e2;
    err[3]=e3;
    err[4]=e4;
    err[5]=e5;
    err[6]=e6;
    err[7]=e7;
    
    TGraphErrors * g=new TGraphErrors(8,x,y,0,err);
    g->Fit("pol1");
    g->Draw("AP*");
    
   
    
}

