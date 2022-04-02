//#include "TMath.h"

//Resistenza in ingresso: 50 Ohm
// T1 = 1.668 us -> 422
// T2 = 2.056 us -> 514


void sipm_analysis(TString fname) {
    ifstream file;
    TFile *fout = new TFile("output.root", "recreate");
    
    //TCanvas *c1 = new TCanvas("c1","c1");
    //TH1D *h1 = new TH1D ("h1", "h1", 25, -1, 1);

    file.open(fname);

    
    double constant_of_conversion = 2.0/4096.0;
    double deltat = 0.004; // us
    double resistance = 50; // Ohm


    Double_t a[1024];   // events
    Int_t b[1024]; // unconverted events

    Int_t Minimum = 0;
    Int_t temp = 0;
    Double_t time[1024];
    Double_t integral[1024];
    Double_t sum = 0.0;
    Double_t baseline = 0.0;
    Double_t rettangolone = 0.0; // integrale superficie picco
    Double_t integrale = 0.0;
    Double_t Charge = 0.0;




    

    TTree *sipm_tree = new TTree("sipm_tree","sipm_tree");
    sipm_tree -> Branch("Data", a,"Data[1024]/D");
    sipm_tree -> Branch("UnconvertedData", b, "UnconvertedData[1024]/I");
    sipm_tree -> Branch("Time", time, "Time[1024]/D");
    sipm_tree -> Branch("Charge", &Charge, "Charge/D");
    sipm_tree -> Branch("Minimum", &Minimum, "Minimum/I");



    while(file.good()) {
        Minimum = 0;
        Charge = 0;

        for (int i = 0; i<1024; i++) {
            file >> temp;
            b[i] = temp;
            a[i] = temp * constant_of_conversion - 1.0; // V
            time[i] = deltat * i; // us
        }  

        sum = 0.0;
        
        for (int i = 0; i<150; i++) {
            sum = sum + a[i];
        
        }
        baseline = sum/150.0;

        // 92 è la differenza tra 514 e 422
        rettangolone = 0.0;
        rettangolone = ((baseline * (deltat * 92) / resistance)) * 0.000001; // A * t = C       TMath::Power(10,-6

        integrale = 0.0;
        Minimum = b[422];
        for (int i = 422 ; i < 514 ; i++  ) {
            integrale = a[i] * deltat/resistance * 0.000001 + integrale; // C       TMath::Power(10,-6)
            if(b[i] < Minimum) {
                Minimum = b[i];
            }
        }

        Charge = rettangolone - integrale; // C   

        std::cout << Minimum << std::endl;

        sipm_tree -> Fill();
    }




    file.close();

    //c1 -> cd();
    //h1 -> Draw();

    fout->cd();
    sipm_tree -> Write();
    fout -> Close();
    
    return;    
}
