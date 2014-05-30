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

	// The range of the fit.
	//		200:	0.4 - 3.6
	//		158:	0.0 - 2.9
	//		6.24:	0.0 - 3.2
	double fitMin = 0.4;
	double fitMax = 3.6;
	
	// The range of the X-axis on the printed graph
	double xMin = 0.;
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
	TGraphErrors *grph = new TGraphErrors("./200GeVP.dat","%lg %lg %lg");
	
	// Set titles for the graph and it's axes
	grph->SetTitle(
		"200 GeV (Positive);
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
	TF1 *total = new TF1("total","[0]*(TMath::Exp(x/[1]))",fitMin,fitMax);
	
	
	// Set the fit line color to red, for some reason (I should probably change this)
	total->SetLineColor(kAzure);


	total->SetParameter(0,p0);
	//total->SetParLimits(0,0,p0);
	total->SetParameter(1,p1);
	
/****************************************/
	// Fitting the entire range with the fit function
	TFitResultPtr r = grph->Fit(total, "SEM");
	//grph->Fit(total,"WEM");
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
	
	cout << "\n\n\tp0:\t" << par[0] << "\t\t+/-\t" << r->ParError(0);
	cout << "\n\tp1:\t" << par[1] << "\t\t+/-\t" << r->ParError(1);
	
	//total->SetParameter(0,par[0]);
	//total->SetParameter(1,par[1]);
	
	// Create a function for the mean integral
	TF1 *total2 = new TF1("total2","x*[0]*(TMath::Exp(x/[1]))",fitMin,fitMax);
	
	total2->SetParameter(0,par[0]);
	total2->SetParameter(1,par[1]);
	
	// Compute integral for bottom of the expectation value function
	Double_t integral1 = total->Integral(0.,maxRapidity);
	
	// Compute error of the integral
	Double_t integral1Error = total->IntegralError(0.,maxRapidity,r->GetParams(), 
										r->GetCovarianceMatrix().GetMatrixArray() );
													
	// Compute integral for top of the expectation value function
	Double_t integral2 = total2->Integral(0.,maxRapidity);
	
	// Compute error of the integral
	Double_t integral2Error = total2->IntegralError(0.,maxRapidity,r->GetParams(), 
										r->GetCovarianceMatrix().GetMatrixArray() );
													
	
	Double_t expY = integral2/integral1;
	
	Double_t expYerr = expY*(TMath::Sqrt((TMath::Power((integral2Error/integral2),2)) + 
										(TMath::Power((integral1Error/integral1),2))));
	
	Double_t deltaY = maxRapidity - expY;
	
	//Double_t deltaYerr = deltaY*(TMath::Sqrt((TMath::Power((0.05*maxRapidity),2)) + 
	//									(TMath::Power(expYerr,2))));
	
	
	cout << "\n\n\tFirst integral:\t" << integral1;
	cout << "\n\tSecond integral:\t" << integral2;
	
	cout << "\n\n\tError of first integral:\t" << integral1Error;
	cout << "\n\tError of second integral:\t" << integral2Error; 
	
	
	cout << "\n\n\t<y>:\t\t" << expY << "\t\t+/-\t" << expYerr;
	cout << "\n\tDelta-y:\t" << deltaY << "\t\t+/-\t" << expYerr << endl << endl;
	
}