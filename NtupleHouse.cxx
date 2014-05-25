void NtupleHouse() {
//   example of macro to create can ntuple reading data from an ascii file.
//   This macro is a variant of basic.C
//Author: Rene Brun   

   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("NtupleHouse.cxx","");
   dir.ReplaceAll("/./","/");
   
   TFile *f = new TFile("Ntuple158P.root","RECREATE");
   TH1F *h1 = new TH1F("h1","x distribution",100,-4,4);
   TTree *T = new TTree("ntuple","data from ascii file");
   Long64_t nlines = T->ReadFile(Form("%s158GeVP.dat",dir.Data()),"y:dy:edy");
   printf(" found %lld points\n",nlines);
   T->Draw("y","z>2");
   T->Write();
}