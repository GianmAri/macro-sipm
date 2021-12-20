#include <vector>

//Resistenza in ingresso: 50 Ohm


void sipm_analysis(TString fname) {
    ifstream file;
    TFile *fout = new TFile("output.root", "recreate");

    // Contatore numero di eventi
    Int_t num;
    ifstream is(fname);
    std::istream_iterator<double> start(is), end;
    

    file.open(fname);

    
    double constant_of_conversion = 2.0/4096.0; 


    Double_t a[1024];   // events
    Double_t b[1024];   // 
    Int_t temp;
    double time[1024];

    

    TTree *sipm_tree = new TTree("sipm_tree","sipm_tree");
    sipm_tree -> Branch("Data", a,"Data[1024]/D");
    sipm_tree -> Branch("Time", time, "Time[1024]/D");
    while(file.good()) {
        for (int i = 0; i<1024; i++) {
            file >> temp;
            a[i] = temp * constant_of_conversion; // mv
            time[i] = 0.004 * i; // us
        }
        sipm_tree -> Fill();
    }

    /*

    std::vector <double> aa(start, end);
    std::vector <double> bb;
    for(int i=0; i<aa.size(); i++) {
        bb.push_back(aa[i] * constant_of_conversion - 1.0);
    }
    sipm_tree -> Branch("bb", &bb);

    */

    //TBranch *Acquisizioni = sipm_tree->Branch("aa", &aa);  //TBranch *Acquisizioni = sipm_tree->Branch("b",b,"b[num]/D");




    //for (int i=0; i<events; i++) {
        //for(int j=0; j<num; j++) {
        //    file >> a[j];  //[i]; // Scala da convertire
        //    b[j] = a[j] * constant_of_conversion; // mV
            
        //}

    
    //sipm_tree -> ResetBranchAddresses(); //INVESTIGARE
    //}

    file.close();

    fout->cd();
    sipm_tree -> Write();
    fout -> Close();
    
    return;    
}


///////////////////////////////////////////////////////



// Utilizzato per contare
/*
    std::string unused;
    while (std::getline(in, unused)) {
        ++num;
    }
    std::cout << num/1024 << endl;
*/
