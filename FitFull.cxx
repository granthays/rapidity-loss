/*********************************************************************************
 * 			Fitting Data and Finding Expectation Value with ROOT (Both Sides)
 *
 * Title:		FitFull.cxx
 * Author:		Grant Hays
 * Date: 		29 May 2014
 * Description:	This is a ROOT macro to plot data from RHIC and finding the best 
 *				fit for the data using an exponential fit function. The total
 *				rapidity loss (delta-y) for the y'-beam is also found.
 *********************************************************************************/
void FitFull(){

	// The range of the fit.
	//		200:	0.4 - 3.6
	//		158:	0.0 - 2.9
	//		6.24:	0.0 - 3.2
	double fitMin = -0.4;
	double fitMax = 0.4;
	
	// The range of the X-axis on the printed graph
	double xMin = -5.;
	double xMax = 5.;
	
	// The range of the Y-axis on the printed graph
	double yMin = 0.;
	double yMax = 0.4;
	
	// Initial guesses for the parameters
	//		200:	0.0093 and 1.45
	//		158:	0.04 (or 0.07364/2) and 1.13
	//		62.4:	0.00935 and 1.0
	double p0 = 0.0093;
	double p1 = 1.45;
	
	
	// 200:		5.4
	// 158:		3.0
	// 62.4:	4.2
	double maxRapidity = 5.4;
	
	
/*********************************************************************************/
	
	// Setting up Canvas and Grid for Graph
	TCanvas* c = new TCanvas();
	c->SetGrid();
	
	// This will add an information box to the graph containing
	// the fit function parameters and Chi2/ndf
	gStyle->SetOptFit();
	
	// Creating and filling the TGraphErrors
	TGraphErrors *grph = new TGraphErrors("./158GeV.dat","%lg %lg %lg");
	
	// Set titles for the graph and it's axes
	grph->SetTitle(
		"158 GeV;
		y';
		dN/dy'");
	// Set plot marker style to filled squares
	grph->SetMarkerStyle(21);
	// Set plot marker color to red
	grph->SetMarkerColor(kRed);
	// Set the range of the X-axis so that it shows everything, but isn't too big
	grph->GetXaxis()->SetLimits(xMin,xMax);
	grph->SetMinimum(yMin);
	grph->SetMaximum(yMax);
	// Draw with options:
	//		A = Axis are drawn around the graph
	//		P = The current marker is plotted at each point
	grph->Draw("AP");
	
	
	// This is the fit function found by Chris Appier
	TF1 *total = new TF1("total","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",fitMin,fitMax);
	
	
	// Set the fit line color to red, for some reason (I should probably change this)
	total->SetLineColor(kAzure);


	total->SetParameter(0,p0);
	total->SetParLimits(0,p0-0.01869,p0);
	total->SetParameter(1,p1);
	total->SetParLimits(1,1,2);
	
/****************************************/
	// Fitting the entire range with the fit function
	TFitResultPtr r = grph->Fit(total, "SWEMB");
	//grph->Fit(total,"WLEMB");
	//grph->Fit(total);
/****************************************/

	
	// Retrieve and print the number of parameters in the function
	int numParam = total->GetNpar();
	cout << "\n\nNumber of Parameters:\t" << numParam << endl << endl;
	
	
	// Retrieve and print the Covariance Matrix of the fit function
	TMatrixD covMatrix(numParam,numParam);
	gMinuit->mnemat(covMatrix.GetMatrixArray(),numParam);
	covMatrix.Print();
	
	// Retrieve an array of the parameter values
	Double_t par[2];
	total->GetParameters(par);
	
	// Retrieve an array of the errors for each parameter of the fit function
	Double_t *parErrors = total->GetParErrors();
	
	cout << "\n\n\tp0:\t" << par[0];
	cout << "\n\n\tp1:\t" << par[1];
	
	
}