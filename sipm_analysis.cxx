#include <vector>

void sipm_analysis(TString fname) {
    ifstream file;
    TFile *fout = new TFile("output.root", "recreate");

    Int_t num;
    //ifstream in(fname);
    ifstream is (fname);
    std::istream_iterator<double> start(is), end;
    std::vector <double> aa(start, end);
    //for(int i=0; i<aa.size(); i++) {
    //    std::cout << aa[i] << endl;
    //}
    


    //std::string unused;
    //while (std::getline(in, unused)) {
    //    ++num;
    //}
    //std::cout << num/1024 << endl;


    file.open(fname);

    double constant_of_conversion = 2.0/4096.0;


    Double_t a[num];   // events
    Double_t b[num];   // 
    double time[1024];

    

    TTree *sipm_tree = new TTree("sipm_tree","sipm_tree");
    TBranch *Acquisizioni = sipm_tree->Branch("aa", &aa);  //TBranch *Acquisizioni = sipm_tree->Branch("b",b,"b[num]/D");
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

    
    //TCanvas *c =  new TCanvas ("c");
    //TGraph *gra = new TGraph(1024,time,b);
    //c -> cd();
    //gra -> Draw;
    fout->cd();
    sipm_tree -> Write();
    
    return;    
}