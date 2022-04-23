
void poisson_fit(TString fname, TString tname) {
    TFile * file= new TFile(fname);
    TTree* t=(TTree*) file->Get(tname);
    Int_t DarkCount;
    t->SetBranchAddress("DarkCount",&DarkCount);
    TH1I *h = new TH1I("H","",10,0,10);
    int neventi=t->GetEntries();
    for(int i=0; i<neventi;i++){
        t -> GetEntry(i);
        h -> Fill(DarkCount);
    }

    TF1 *p=new TF1("p","[0]*TMath::PoissonI(x,[1])",0,10);
    p->SetParameters(0,1);
    p->SetParameters(5000,1);
    h -> Draw();
    h->Fit(p);

    double p1 = p -> GetParameter(1);
    std::cout << p1/(16*1024*4e-9) << std::endl;

    return;
}

//dark_count_tree->Draw("DarkCount>>h(10,0,10)")

//TF1 *p=new TF1("p","[0]*TMath::PoissonI(x,[1])",0,10)
//p->SetParameters(0,1)
//p->SetParameters(5000,1)
//h->Fit(p)


//1.02158e-01/(16*1024*4e-9) = 1558.8074 (u = 2071 sigma = 8 picco 2)
//4.46249e+00/(16*1024*4e-9) = 68092.194 (u = 2122 sigma = 5 picco 1) 1 milione 55.11V
//3.95261e+00/(16*1024*4e-9) = 59509.27  (u = 2122 sigma = 5 picco 1) 5 mila    55.11V
///(16*1024*4e-9) = 