/*********************************************************************************
 * 	Fitting Data w/ 4th Deg. Polynomial and Finding Expectation Value with ROOT
 *
 * Title:		FitFindPol4.cxx
 * Author:		Grant Hays
 * Date: 		29 May 2014
 * Description:	This is a ROOT macro to plot data from RHIC and finding the best 
 *				fit for the data using a fourth degree polynomial. The total
 *				rapidity loss (delta-y) for the y'-beam is also found.
 *********************************************************************************/
void FitFindPol4(){

	// The range of the fit.
	//		200:	0.4 - 3.6
	//		158:	0.0 - 2.9
	//		6.24:	0.0 - 3.2
	double fitMin = 0.;
	double fitMax = 2.9;
		// The range of the X-axis on the printed graph
	double xMin = 0.;
	double xMax = 5.;
	
	// The range of the Y-axis on the printed graph
	double yMin = 0.;
	double yMax = 0.4;
	
	// Initial guesses for the parameters
	//		200:	0.008		0.00269685		 0.000480676
	//		158:	0.03682		0.073939		-0.00400871
	//		62.4:	0.00935		0.0055318		 0.0016652
	double p0 = 0.03682;
	double p1 = 0.073939;
	double p2 = -0.00400871;

	// 200:		5.4
	// 158:		3.0
	// 62.4:	4.2
	double maxRapidity = 3.;


/*********************************************************************************/
	
	// Setting up Canvas and Grid for Graph
	TCanvas* c = new TCanvas();
	c->SetGrid();
	
	// This will add an information box to the graph containing
	// the fit function parameters and Chi2/ndf
	gStyle->SetOptFit();
	
	// Creating and filling the TGraphErrors
	TGraphErrors *grph = new TGraphErrors("./158GeVP.dat","%lg %lg %lg");
	
	// Set titles for the graph and it's axes
	grph->SetTitle(
		"158 GeV Pol4;
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
	TF1 *total = new TF1("total","([0] + ([1]*(x*x)) + ([2]*(x*x*x*x)))",fitMin,fitMax);

	
	// Set the fit line color to red, for some reason (I should probably change this)
	total->SetLineColor(kAzure);
	
	
	total->SetParameter(0,p0);
	total->SetParLimits(0,0.,p0);
	total->SetParameter(1,p1);
	total->SetParameter(2,p2);
	
/****************************************/
	// Fitting the entire range with the fit function
	TFitResultPtr r = grph->Fit(total, "SWEM");
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
	Double_t par[3];
	total->GetParameters(par);
	
	// Retrieve an array of the errors for each parameter of the fit function
	Double_t *parErrors = total->GetParErrors();
	
	cout << "\n\n\tp0:\t" << par[0] << "\t+/-\t" << r->ParError(0);
	cout << "\n\n\tp1:\t" << par[1] << "\t+/-\t" << r->ParError(1);
	cout << "\n\n\tp2:\t" << par[2] << "\t+/-\t" << r->ParError(2);
	
	
	// Create a function for the mean integral
	TF1 *total2 = new TF1("total2","x*([0] + ([1]*(x*x)) + ([2]*(x*x*x*x)))",fitMin,fitMax);
	//TF1 *total2 = new TF1("total2","x*total",fitMin,fitMax);
	
	total2->SetParameter(0,par[0]);
	total2->SetParameter(1,par[1]);
	total2->SetParameter(2,par[2]);
	
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