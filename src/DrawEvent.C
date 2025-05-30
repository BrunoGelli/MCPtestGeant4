TTree* ntuple = nullptr;
TTree* config = nullptr;
TCanvas* c = nullptr;
Int_t currentEvt = 0;
Int_t maxEvt = 0;

void DrawEvent(Int_t evtID) {
    c->Clear();

    // Draw config once
    Int_t sizeY, sizeZ, pixelY, pixelZ;
    config->SetBranchAddress("sizeY", &sizeY);
    config->SetBranchAddress("sizeZ", &sizeZ);
    config->SetBranchAddress("pixelSizeY", &pixelY);
    config->SetBranchAddress("pixelSizeZ", &pixelZ);
    config->GetEntry(0);

    Int_t nBinsY = sizeY / pixelY;
    Int_t nBinsZ = sizeZ / pixelZ;

    // Filter only this event
    TString cut = Form("evt == %d", evtID);

    // 2D histogram of energy deposition (Z vs Y)
    TH2D* h = new TH2D("h", Form("Event %d: Energy Deposition and True Track;Z [cm];Y [cm]", evtID),
                       nBinsZ, -sizeZ / 2., sizeZ / 2.,
                       nBinsY, -sizeY / 2., sizeY / 2.);

    ntuple->Draw("dy:dz>>h", cut + " && energy > 0", "COLZ");

    // Overlay track: projected to Y-Z plane
    ntuple->Draw("y:z", cut + " && energy == 0", "L SAME");  // true track (assumed 0 energy)
    c->Update();
}

void NextEvent() {
    if (++currentEvt > maxEvt) currentEvt = 0;
    DrawEvent(currentEvt);
}

void PrevEvent() {
    if (--currentEvt < 0) currentEvt = maxEvt;
    DrawEvent(currentEvt);
}

void InteractiveDisplay() {
    TFile* f = new TFile("OutPut.root");
    ntuple = (TTree*)f->Get("ntuple");
    config = (TTree*)f->Get("config");

    c = new TCanvas("c", "Event Display", 800, 600);

    // Find the max event number
    ntuple->SetEstimate(ntuple->GetEntries());
    ntuple->Draw("evt", "", "goff");
    auto* evts = ntuple->GetV1();
    for (Long64_t i = 0; i < ntuple->GetSelectedRows(); ++i)
        if (evts[i] > maxEvt) maxEvt = evts[i];

    DrawEvent(currentEvt);
}
