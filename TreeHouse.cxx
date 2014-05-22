// Reads a simple data file 
#include <TFile.h> 
#include <TTree.h> 
#include <string> 
#include <iostream> 
using namespace std; 
void TreeHouse() { 
	// Location of the directory for input and output files 
	string dirName = "D:/Users/Grant/Documents/GitHub/rapidity-loss/" ; 
	
	// Name of the input and output files 
	string inFileName = dirName + "158GeVP.txt" ; 
	string outFileName = dirName + "Tree158GeVP.root" ; 
	
	// Create a tree to store the data 
	TTree *tree = new TTree("tree158GeVP","158 GeV (Positive)"); 

	// Open the output file to write to 
	TFile *fout = new TFile(outFileName.c_str(),"RECREATE"); 
	fout->cd(); 
	
	// Read in the data from the text file 
	int nentries = tree->ReadFile(inFileName.c_str(), 
		"y/D:dy/D:edy/D"); 
		cout << "Read " << nentries << " entries from the input file " << 
		inFileName << endl; 
	// Write the ROOT tree to output file 
	tree->Write(); 
	fout->Close(); 
	// Cleanup 
	delete tree; 
	delete fout; 
} 
