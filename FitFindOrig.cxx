/*********************************************************************************
 * 			Fitting Data and Finding Expectation Value with ROOT
 *
 * Title:		FitFind.cxx
 * Author:		Grant Hays
 * Date: 		28 Mar. 2014
 * Description:	This is a ROOT macro to plot data from RHIC and finding the best 
 *				fit for the data using a combination of Gaussian and Landau. The 
 *				expectation value for the y'-beam is also found.
 *********************************************************************************/
void FitFindOrig(){
	
	// Setting up Canvas and Grid for Graph
	TCanvas* c = new TCanvas();
	c->SetGrid();
	
	// This will add an information box to the graph containing
	// the fit function parameters and Chi2/ndf
	gStyle->SetOptFit();
	
	// Creating and filling the TGraphErrors
	TGraphErrors *gr158 = new TGraphErrors("./158gevN.txt","%lg %lg %lg");
	
	// Set titles for the graph and it's axes
	gr158->SetTitle(
		"158 GeV;
		y';
		dN/dy'");
	// Set plot marker style to filled squares
	gr158->SetMarkerStyle(21);
	// Set plot marker color to red
	gr158->SetMarkerColor(kRed);
	// Set the range of the X-axis so that it shows everything, but isn't too big
	gr158->GetXaxis()->SetLimits(-3.,0.1);
	// Draw with options:
	//		A = Axis are drawn around the graph
	//		P = The current marker is plotted at each point
	gr158->Draw("AP");
	
	// An array to save parameter values to
	Double_t par[6];
	
	// The fit function of the first range is Gaussian. The range is comprised of 
	// 	the lowest 4 points that spike at the top-left
	TF1 *f1 = new TF1("f1", "gaus",-2.9,-2.6);
	
	// The fit function of the bulk of the data is Landau. This is the range from -2.5
	// 	to 0.0
	TF1 *f2 = new TF1("f2", "landau",-2.5,0.);
	
	// This is the fit function for the whole range of data. Gaussian + Landau
	TF1 *total = new TF1("total","gaus(0)+landau(3)",-2.9,0.);
	
	// Set the fit line color to red, for some reason (I should probably change this)
	total->SetLineColor(2);
	
	// Fitting the Gaussian portion
	gr158->Fit(f1,"0R");
	// Fitting the Landau portion
	gr158->Fit(f2,"0R+");
	
	// Retrieve the parameter values of the found fit functions
	f1->GetParameters(&par[0]);
	f2->GetParameters(&par[3]);
	
	// Using the retrieved parameter info to set the parameters for the full fit function
	total->SetParameters(par);
	
	// Fitting the entire range with the fit amalgamation
	gr158->Fit(total);
	
	// Retrieve and print the number of parameters in the function
	int numParam = total->GetNpar();
	cout << "\n\nNumber of Parameters:\t" << numParam << endl << endl;
	
	// Retrieve and print the Covariance Matrix of the fit function
	TMatrixD covMatrix(numParam,numParam);
	gMinuit->mnemat(covMatrix.GetMatrixArray(),numParam);
	covMatrix.Print();
	
	// Retrieve an array of the errors for each parameter of the fit function
	Double_t *parErrors = total->GetParErrors();
	
	// Create a function for the mean integral
	TF1 *total2 = new TF1("total2","total * x",-2.9,0.);
	
	// Compute integral for bottom of the expectation value function
	Double_t integral1 = total->Integral(-2.9,0.);
	// Compute error of the integral
	Double_t integral1Error = total->IntegralError(-2.9,0.,parErrors,covMatrix.GetMatrixArray());
	// Compute integral for top of the expectation value function
	Double_t integral2 = total2->Integral(-2.9,0.);
	
	// Print integrals and the expectation value
	//cout << "\n\n\tIntegral y * dN/dy:\t" << integral2 << endl << endl;
	//cout << "\n\tIntegral dN/dy:\t\t" << integral1 << endl << endl;
	cout << "\n\n\t<y>:\t" << integral2/integral1 << "+/- " << integral1Error << endl << endl;
	
}