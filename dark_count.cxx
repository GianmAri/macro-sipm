void dark_cout() {
    ifstream file;
    TFile *fout = new TFile("darkcount.root", "recreate");

    file.open(fname);

    
    double constant_of_conversion = 2.0/4096.0;
    //double deltat = 0.004/16.0; // us
    double resistance = 50; // Ohm
    
    Int_t temp = 0;
    Int_t a[16*1024];
    Int_t dark_cont[100000];
    //Double_t time[16*1024];
    Int_t count = 0;
    Double_t mean = 1.64408e-11; //valore primo picco
    Double_t sigma = 1.52515e-12; //valore primo picco
    Double_t constant_of_conversion = 4096.0/2.0;
    Double_t minimum = (mean + 1.0) * constant_of_conversion;

    Double_t threshold = minimum -  (3.0 * sigma);
    
    TTree *dark_count_tree = new TTree("dark_count_tree", "dark_count_tree");
    dark_count_tree -> Branch("Dark Count", dark_count,"Dark Count[100000]/I");
    
    Int_t j = 0;

    while (file.good()) {
        count = 0;
        for(int i = 0; i < 16 * 1024; i++) {
            file >> temp;
            a[i] = temp;
            //time[i] = deltat * i;     
            }
        
        for (int i = 0; i < 16 * 1024; i++) {
            if (a[i] < threshold && (i+1) != (16 * 1024 + 1)) {
                if(a[i+1] >= threshold) {
                    count++;
                }
            }
        }
        dark_cont[j] = count;
        j++;
           
        
        dark_count_tree -> Fill();
    }


    file.close();
    fout->cd();
    dark_count_tree -> Write();
    fout -> Close();
    
    return;
    
}
