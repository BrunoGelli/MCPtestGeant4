void EventDisplay() {
    // Open file and get trees
    TFile *f = new TFile("OutPut.root");
    if (!f || f->IsZombie()) {
        std::cerr << "Failed to open OutPut.root" << std::endl;
        return;
    }

    // Get data tree and config tree
    TTree *t = (TTree*)f->Get("ntuple");
    TTree *config = (TTree*)f->Get("config");
    if (!t || !config) {
        std::cerr << "Missing ntuple or config tree!" << std::endl;
        return;
    }

    // Read detector configuration
    int sizeY, sizeZ;
    double pixelSizeY, pixelSizeZ;
    config->SetBranchAddress("sizeY", &sizeY);
    config->SetBranchAddress("sizeZ", &sizeZ);
    config->SetBranchAddress("pixelSizeY", &pixelSizeY);
    config->SetBranchAddress("pixelSizeZ", &pixelSizeZ);
    config->GetEntry(0); // read the only entry

    // Compute histogram bounds and binning
    double yMin = -sizeY / 2.0;
    double yMax =  sizeY / 2.0;
    double zMin = -sizeZ / 2.0;
    double zMax =  sizeZ / 2.0;
    int yBins = sizeY / pixelSizeY;
    int zBins = sizeZ / pixelSizeZ;

    double offset = 35;
    
    // Create canvas with 2x2 pads
    TCanvas *c = new TCanvas("c", "Event Display per Module", 1000, 1000);
    c->Divide(2, 2);

    // lets go over each module

    // Starting with module 0
    c->cd(1);
    // Create unique histogram name per module
    TString hname_0 = "Module 0";
    TString htitle_0 = "Module 0;Z [cm];Y [cm];Edep [MeV]";
    TH2D *h_0 = new TH2D(hname_0, htitle_0, zBins, zMin - offset, zMax - offset, yBins, yMin, yMax);
    // Fill histogram for this module only
    TString drawCmd_0 = "dy:dz>>" + hname_0;
    t->Draw(drawCmd_0, "energy*(module == 0 && evt == 10)", "COLZ");
    // gPad->SetLogz();


    // Starting with module 2
    c->cd(2);
    // Create unique histogram name per module
    TString hname_2 = "Module 2";
    TString htitle_2 = "Module 2;Z [cm];Y [cm];Edep [MeV]";
    TH2D *h_2 = new TH2D(hname_2, htitle_2, zBins, zMin + offset, zMax + offset, yBins, yMin, yMax);
    // Fill histogram for this module only
    TString drawCmd_2 = "dy:dz>>" + hname_2;
    t->Draw(drawCmd_2, "energy*(module == 2 && evt == 10)", "COLZ");
    // gPad->SetLogz();

    // Starting with module 1
    c->cd(3);
    // Create unique histogram name per module
    TString hname_1 = "Module 1";
    TString htitle_1 = "Module 1;Z [cm];Y [cm];Edep [MeV]";
    TH2D *h_1 = new TH2D(hname_1, htitle_1, zBins, zMin - offset, zMax - offset, yBins, yMin, yMax);
    // Fill histogram for this module only
    TString drawCmd_1 = "dy:dz>>" + hname_1;
    t->Draw(drawCmd_1, "energy*(module == 1)", "COLZ");
    gPad->SetLogz();


    // Starting with module 3
    c->cd(4);
    // Create unique histogram name per module
    TString hname_3 = "Module 3";
    TString htitle_3 = "Module 3;Z [cm];Y [cm];Edep [MeV]";
    TH2D *h_3 = new TH2D(hname_3, htitle_3, zBins, zMin + offset, zMax + offset, yBins, yMin, yMax);
    // Fill histogram for this module only
    TString drawCmd_3 = "dy:dz>>" + hname_3;
    t->Draw(drawCmd_3, "energy*(module == 3)", "COLZ");
    gPad->SetLogz();










    c->Update();

}