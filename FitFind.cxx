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
void FitFind(){

	double grphMin = 0.;
	double grphMax = 3.2;
	double p0 = 0.00935;
	double p1 = 2.;
	
	// Setting up Canvas and Grid for Graph
	TCanvas* c = new TCanvas();
	c->SetGrid();
	
	// This will add an information box to the graph containing
	// the fit function parameters and Chi2/ndf
	gStyle->SetOptFit();
	
	// Creating and filling the TGraphErrors
	TGraphErrors *grph = new TGraphErrors("./62.4GeVP.txt","%lg %lg %lg");
	
	// Set titles for the graph and it's axes
	grph->SetTitle(
		"62.4 GeV (Positive);
		y';
		dN/dy'");
	// Set plot marker style to filled squares
	grph->SetMarkerStyle(21);
	// Set plot marker color to red
	grph->SetMarkerColor(kRed);
	// Set the range of the X-axis so that it shows everything, but isn't too big
	grph->GetXaxis()->SetLimits(0.,4.);
	grph->SetMinimum(0.);
	grph->SetMaximum(0.4);
	// Draw with options:
	//		A = Axis are drawn around the graph
	//		P = The current marker is plotted at each point
	grph->Draw("AP");
	
	// This is the fit function for the whole range of data. Gaussian + Landau
	//TF1 *total = new TF1("total","[0]*(TMath::Exp(x/[1]))",grphMin,grphMax);
	TF1 *total = new TF1("total","[0]*(TMath::Exp(x/[1]))",grphMin,grphMax);
	
	// Set the fit line color to red, for some reason (I should probably change this)
	total->SetLineColor(kAzure);
	
	// Using the retrieved parameter info to set the parameters for the full fit function
	total->FixParameter(0,p0);
	total->FixParameter(1,p1);
	
	// Fitting the entire range with the fit amalgamation
	grph->Fit(total);
	
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
	TF1 *total2 = new TF1("total2","total * x",grphMin,grphMax);
	
	// Compute integral for bottom of the expectation value function
	Double_t integral1 = total->Integral(grphMin,grphMax);
	// Compute error of the integral
	Double_t integral1Error = total->IntegralError(grphMin,grphMax,parErrors,covMatrix.GetMatrixArray());
	// Compute integral for top of the expectation value function
	Double_t integral2 = total2->Integral(grphMin,grphMax);
	
	// Print integrals and the expectation value
	//cout << "\n\n\tIntegral y * dN/dy:\t" << integral2 << endl << endl;
	//cout << "\n\tIntegral dN/dy:\t\t" << integral1 << endl << endl;
	cout << "\n\n\t<y>:\t" << integral2/integral1 << "+/- " << integral1Error << endl << endl;
	
}