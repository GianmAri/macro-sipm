#include <vector>
//#include "TMath.h"

//Resistenza in ingresso: 50 Ohm
// T1 = 1.668 us -> 422
// T2 = 2.056 us -> 514

Double_t mediabaseline(TString fname){
    ifstream file;
    //TFile *fout = new TFile("output.root", "recreate");
    
    file.open(fname);
    
    double constant_of_conversion = 2.0/4096.0;
    double deltat = 0.004; // us
    double resistance = 50; // Ohm
    
    Double_t a[1024];   // events
    Int_t temp = 0;
    Double_t time[1024];
    //Double_t integral[1024];
    Double_t sum = 0.0;
    Double_t baseline = 0.0;
    //Double_t rettangolone = 0.0; // integrale superficie picco
    //Double_t Charge = 0.0;
    Double_t mediabaseline=0.0;
    
    
    while(file.good()) {
        //Charge = 0;
        
        for (int i = 0; i<1024; i++) {
            file >> temp;
            a[i] = temp * constant_of_conversion - 1.0; // mv
            time[i] = deltat * i; // us
        }
        sum = 0.0;
        for (int i = 0; i<200; i++) {
            sum = sum + a[i];
        }
        baseline=sum/200.0;
        mediabaseline= mediabaseline+ baseline/5000;
    }
    file.close();
    
    return mediabaseline;
    
}
void sipm_analysis(TString fname) {
    ifstream file;
    TFile *fout = new TFile("output.root", "recreate");
    
    file.open(fname);
    
    Double_t MB=mediabaseline(fname);

    
    double constant_of_conversion = 2.0/4096.0;
    double deltat = 0.004; // us
    double resistance = 50; // Ohm


    Double_t a[1024];   // events
    Int_t temp = 0;
    Double_t time[1024];
    Double_t integral[1024];
    Double_t sum = 0.0;
    Double_t baseline = 0.0;
    Double_t rettangolone = 0.0; // integrale superficie picco
    Double_t Charge = 0.0;



    
    fout->cd();
    TTree *sipm_tree = new TTree("sipm_tree","sipm_tree");
    sipm_tree -> Branch("Data", a,"Data[1024]/D");
    sipm_tree -> Branch("Time", time, "Time[1024]/D");
    sipm_tree -> Branch("Charge", &Charge, "Charge/D");

    
    while(file.good()) {
        Charge = 0;
        
        for (int i = 0; i<1024; i++) {
            file >> temp;
            a[i] = temp * constant_of_conversion - 1.0; // mv
            time[i] = deltat * i; // us
        }
      
    


        // 92 è la differenza tra 514 e 422
        rettangolone = 0.0;
        rettangolone = ((MB * (deltat * 92) / resistance)) * 0.000001; // mA * t = mC       TMath::Power(10,-6

        Double_t integrale = 0.0;
        for (int i = 422 ; i < 514 ; i++  ) {
            integrale = a[i] * deltat/resistance * 0.000001 + integrale; // mC       TMath::Power(10,-6)
        }

        Charge = rettangolone - integrale; // mC   

        sipm_tree -> Fill();
    }
    
    
    




    file.close();

    sipm_tree -> Write();
    fout -> Close();
    
    return;    
}
