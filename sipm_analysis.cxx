#include <vector>

void sipm_analysis(TString fname) {
    ifstream file;
    TFile *fout = new TFile("output.root", "recreate");

    // Contatore numero di eventi
    Int_t num;
    ifstream is(fname);
    std::istream_iterator<double> start(is), end;
    

    file.open(fname);

    
    double constant_of_conversion = 2.0/4096.0; 


    Double_t a[num];   // events
    Double_t b[num];   // 
    double time[1024];

    

    TTree *sipm_tree = new TTree("sipm_tree","sipm_tree");
    std::vector <double> aa(start, end);
    std::vector <double> bb;
    for(int i=0; i<aa.size(); i++) {
        bb.push_back(aa[i] * constant_of_conversion - 1.0);
    }
    sipm_tree -> Branch("bb", &bb);

    //TBranch *Acquisizioni = sipm_tree->Branch("aa", &aa);  //TBranch *Acquisizioni = sipm_tree->Branch("b",b,"b[num]/D");
    sipm_tree -> Fill();



    for (int i=0; i<1024;i++) {
        time[i] = i*0.004; // us
    }
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
