// Read data (CERN staff) from an ascii file and create a root file with a Tree.
// see also a variant in staff.C
// Author: Rene Brun
   
TFile *TreeHouse(Int_t get=0, Int_t print=1) {

	Double_t = y;
	Double_t = dy;
	Double_t = edy;
   Int_t           Category;
   UInt_t          Flag;
   Int_t           Age;
   Int_t           Service;
   Int_t           Children;
   Int_t           Grade;
   Int_t           Step;
   Int_t           Hrweek;
   Int_t           Cost;
   Char_t          Division[4];
   Char_t          Nation[3];

   //The input file cern.dat is a copy of the CERN staff data base
   //from 1988
   TString filename = "TreeHouse.root";
   TString dir = gSystem->UnixPathName(gInterpreter->GetCurrentMacroName());
   dir.ReplaceAll("TreeHouse.cxx","");
   dir.ReplaceAll("/./","/");
   FILE *fp = fopen(Form("%158GeVP.txt",dir.Data()),"r");

   TFile *hfile = 0;
   if (get) {
      // if the argument get =1 return the file "TreeHouse.root"
      // if the file does not exist, it is created
      if (!gSystem->AccessPathName(dir+"TreeHouse.root",kFileExists)) {
         hfile = TFile::Open(dir+"TreeHouse.root"); //in $ROOTSYS/tutorials/tree
         if (hfile) return hfile;
      }
      //otherwise try $PWD/TreeHouse.root
      if (!gSystem->AccessPathName("TreeHouse.root",kFileExists)) {
         hfile = TFile::Open("TreeHouse.root"); //in current dir
         if (hfile) return hfile;
      }
   }
   //no TreeHouse.root file found. Must generate it !
   //generate TreeHouse.root in $ROOTSYS/tutorials/tree if we have write access
   if (!gSystem->AccessPathName(dir,kWritePermission)) {
      filename = dir+"TreeHouse.root";
   } else if (!gSystem->AccessPathName(".",kWritePermission)) {
      //otherwise generate TreeHouse.root in the current directory
   } else {
      printf("you must run the script in a directory with write access\n");
      return 0;
   }
   hfile = TFile::Open(filename,"RECREATE");
   TTree *tree = new TTree("T","158 GeV (Positive)");
   tree->Branch("y",&y,"y/D");
   tree->Branch("dy",&dy,"dy/D");
   tree->Branch("edy",&edy,"edy/D");

   char line[80];
   while (fgets(line,80,fp)) {
      sscanf(&line[0],"%d %d %d",&y,&dy,&edy);
      tree->Fill();
   }
   if (print) tree->Print();
   tree->Write();

   fclose(fp);
   delete hfile;
   if (get) {
      //we come here when the script is executed outside $ROOTSYS/tutorials/tree
      hfile = TFile::Open(filename);
      return hfile;
   }
   return 0;
}