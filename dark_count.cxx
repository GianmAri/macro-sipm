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
    Int_t dark_count[100000];
    //Double_t time[16*1024];
    Int_t count = 0;
    Double_t mean = 1.64408e-11; //valore primo picco
    Double_t sigma = 1.52515e-12; //valore primo picco
    Double_t constant_of_conversion = 4096.0/2.0;
    Double_t minimum = (mean + 1.0) * constant_of_conversion;

    Double_t threshold = minimum -  (3.0 * sigma);
    
    TTree *dark_count_tree = new TTree("dark_count_tree", "dark_count_tree");
    dark_count_tree -> Branch("DarkCount", dark_count,"DarkCount[100000]/I");
    
    Int_t j = 0;

    while (file.good()) {
        //std::cout << "PROVA1" << std::endl;
        count = 0;
        for(int i = 0; i < 16 * 1024; i++) {
            file >> temp;
            a[i] = temp;
            //std::cout << "PROVA2" << "      " << i << std::endl;
            //time[i] = deltat * i;     
        }
        
        for (int i = 0; i < 16 * 1024; i++) {
            //std::cout << "PROVA3" << "      " << i << std::endl;
            if (a[i] < threshold && (i+1) < 16 * 1024) {
                if(a[i+1] >= threshold) {
                    count++;
                }
            }
        }

        //std::cout << "PROVA4" << std::endl;
        dark_count[j] = count;
        j++;
        //h1 -> Fill(count);
        //std::cout << "PROVA5" << std::endl;

        std::cout << double(j) / 1000.0 << "% \r"; 

        //std::cout << "PROVA6" << std::endl;
           
        
        dark_count_tree -> Fill();
        //std::cout << "PROVA7" << std::endl;
    }


    file.close();
    fout->cd();
    dark_count_tree -> Write();
    fout -> Close();

    //c1 -> cd();
    //h1 -> Draw();
    
    return;
    
}