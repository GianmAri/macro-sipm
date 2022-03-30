void multifit_darkcount(TString fname, TString tname){
    TFile * file= new TFile(fname);
    TTree* t=(TTree*) file->Get(tname);
    Double_t Minimum;
    t->SetBranchAddress("Minimum",&Minimum);
    TH1F * h=new TH1F("H","",200,-0.3,0.2);
    int neventi=t->GetEntries();
    for(int i=0; i<neventi;i++){
        t->GetEntry(i);
        h->Fill(Minimum);

    }
    //TCanvas *c0=new TCanvas();
    TF1 *g0 = new TF1("g0", "gaus", -0.5, 0.5);

        

    h -> Fit(g0, "R");

 
    h->Draw();
    
    //TCanvas *c2=new TCanvas();
    
    Double_t x[8],y[8],err[8];
    
    Double_t a0=g0->GetParameter("Mean");

    
    Double_t e0=g0->GetParameter(2);

    
    for(int i=0;i<=7;i++){
        x[i]=i+1;
        
    }
    y[0]=a0;

    
    err[0]=e0;

    
    return;
    
}