void dark_cout() {
    ifstream file;
    TFile *fout = new TFile("darkcount.root", "recreate");

    file.open(fname);

    
    double constant_of_conversion = 2.0/4096.0;
    double deltat = 0.004; // us
    double resistance = 50; // Ohm
    
    Int_t temp = 0;
    Double_t time[16*1024];
    Int_t count = 0;
    Double_t mean = 1.64408e-11;
    Double_t sigma = 1.52515e-12;
    Double_t constant_of_conversion = 4096.0/2.0;
    Double_t minimum = (mean + 1.0) * constant_of_conversion;

    Double_t threshold = minimum -  (3.0 * sigma);


    for(int i = 0; i < 16 * 1024; i++) {
        file >> temp;
        
    }



}