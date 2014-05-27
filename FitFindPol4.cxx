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
void FitFindPol4(){

	// The range of the fit.
	double fitMin = 0.;
	double fitMax = 3.2;
	
	// The range of the X-axis on the printed graph
	double xMin = 0.;
	double xMax = 5.;
	
	// The range of the Y-axis on the printed graph
	double yMin = 0.;
	double yMax = 0.4;
	
	// Initial guesses for the parameters
	double p0 = 0.008;
	double p1 = 0.00269685;
	double p2 = 0.000480676;

	
	// Sets the function of fit to accommodate a half dataset or a full one
	//		true  =  Apply fit for half dataset i.e. x >= 0
	//		false =  Apply fit for full dataset
	bool isHalf = true;
	
	// Determine which parameters to fix
	//		0 = No Parameters Fixed, both vary
	//		1 = Fix the first parameter i.e. p0
	//		2 = Fix the second parameter i.e. p1
	//		3 = Fix both parameters
	//		4 = No parameters fixed, but both have limits
	int fixPar = 0;
	
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
		"200 GeV Pol4;
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
	
	
	// This is the fit function found by Chris Appier. If isHalf is true, then
	//		the function is only for the positive half: 
	//				
	//				p0 * Exp(x/p1)
	//		
	//		Otherwise the function is for both sides:
	//
	//				p0 * ( Exp(x/p1) + Exp(-x/p1) )
	//
	if(isHalf){
		TF1 *total = new TF1("total","([0] + ([1]*(x*x)) + ([2]*(x*x*x*x)))",fitMin,fitMax);
	} else {
		TF1 *total = new TF1("total","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",fitMin,fitMax);
	}
	
	
	// Set the fit line color to red, for some reason (I should probably change this)
	total->SetLineColor(kAzure);
	
	
	if(fixPar == 0){
		total->SetParameter(0,p0);
		total->SetParameter(1,p1);
		total->SetParameter(2,p2);
	} else if(fixPar == 1) {
		total->FixParameter(0,p0);
		total->SetParameter(1,p1);
	} else if(fixPar == 2) {
		total->SetParameter(0,p0);
		total->FixParameter(1,p1);
	} else if(fixPar == 3){
		total->FixParameter(0,p0);
		total->FixParameter(1,p1);
	} else {
		total->SetParameter(0,p0);
		total->SetParLimits(0,p0-0.01869,p0+0.01869);
		total->SetParameter(1,p1);
		total->SetParLimits(1,1,2);
	}
	
/****************************************/
	// Fitting the entire range with the fit function
	grph->Fit(total,"WEM");
	//grph->Fit(total);
/****************************************/


//gaussian.SetParameter(0, gausppar.GetParameter(ipar));
	
	
	
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
	
	cout << "\n\n\tp0:\t" << par[0];
	cout << "\n\n\tp1:\t" << par[1];
	cout << "\n\n\tp2:\t" << par[2];
	
	
	// Create a function for the mean integral
	TF1 *total2 = new TF1("total2","total * x",fitMin,fitMax);
	
	total2->SetParameter(0,par[0]);
	total2->SetParameter(1,par[1]);
	total2->SetParameter(2,par[2]);
	
	// Compute integral for bottom of the expectation value function
	Double_t integral1 = total->Integral(0.,fitMax);
	
	// Compute error of the integral
	Double_t integral1Error = total->IntegralError(0.,fitMax,parErrors,
													covMatrix.GetMatrixArray());
													
	// Compute integral for top of the expectation value function
	Double_t integral2 = total2->Integral(0.,fitMax);
	
	// Compute error of the integral
	Double_t integral2Error = total2->IntegralError(0.,fitMax,parErrors,
													covMatrix.GetMatrixArray());
													
	
	Double_t expY = integral2/integral1;
	Double_t expYerr = integral1Error/integral2Error;
	
	Double_t deltaY = fitMax - expY;
	
	cout << "\n\n\tError of first integral:\t" << integral1Error;
	cout << "\n\tError of second integral:\t" << integral2Error; 
	
	
	cout << "\n\n\t<y>:\t\t" << expY << "\t\t+/-\t" << expYerr;
	cout << "\n\tDelta-y:\t" << deltaY << endl << endl;
	
}