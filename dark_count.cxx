void dark_count(TString fname) {
    ifstream file;
    TFile *fout = new TFile("darkcount.root", "recreate");

    file.open(fname);

    
    //double deltat = 0.004/16.0; // us
    double resistance = 50; // Ohm


    //TH1I *h1 = new TH1I("h1", "h1", 6, -1, 5);
    //TCanvas *c1 = new TCanvas("c1","c1");
    
    Int_t temp = 0;
    Int_t a[16 * 1024];
    Int_t dark_count=0;
    //Double_t time[16*1024];
    Int_t count = 0;
    Double_t mean = 2071; //valore primo picco
    Double_t sigma = 8; //valore primo picco
    //Double_t Minimum = (mean + 1.0) * constant_of_conversion;

    Double_t threshold = mean + (3.0 * sigma);
    
    TTree *dark_count_tree = new TTree("dark_count_tree", "dark_count_tree");
    dark_count_tree -> Branch("DarkCount", &dark_count,"DarkCount/I");
    //dark_count_tree -> Branch("Signal", a,"Signal[16384]/I");
    
    Int_t j = 0;

    while (file.good()) {
        count = 0;
        for(int i = 0; i < 16 * 1024; i++) {
            file >> temp;
            a[i] = temp;
            //std::cout << a[i] << std::endl;
        }
        
        for (int i = 0; i < 16 * 1024; i++) {
            if (a[i] < threshold && (i+1) < 16 * 1024) {
                if(a[i+1] >= threshold) {
                    count++;
                }
            }
        }

        dark_count = count;
        //std::cout << dark_count << std::endl;
        j++;


        std::cout << double(j) / 1000.0 << "% \r"; 
           
        
        dark_count_tree -> Fill();
    }


    file.close();
    fout->cd();
    dark_count_tree -> Write();
    fout -> Close();

    //c1 -> cd();
    //h1 -> Draw();
    
    return;
    
}