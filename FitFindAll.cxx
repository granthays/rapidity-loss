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
	double fitMin[3] = {0.4,0.0,0.0};
	double fitMax[3] = {3.6,2.9,3.2};
	
	// The range of the X-axis on the printed graph
	double xMin = 0.;
	double xMax = 5.;
	
	// The range of the Y-axis on the printed graph
	double yMin = 0.;
	double yMax = 0.4;
	
	// Initial guesses for the parameters
	double p0[3] = {0.0093,0.04,0.00935};
	double p1[3] = {1.45,1.13,1.};
	
	
	
	
	// Sets the data set to be fit
	//		200 = 200 GeV
	//		158 = 158 GeV
	//		624 = 62.4 GeV
	int dataSet = 200;
	
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
	
	
	TCanvas* c = new TCanvas();
	c->SetGrid();
	gStyle->SetOptFit();
	
	TGraphErrors *grph = new TGraphErrors("./200GeVP.dat","%lg %lg %lg");
	
	grph->SetTitle(
		"200 GeV (Positive);
		y';
		dN/dy'");
	grph->SetMarkerStyle(21);
	grph->SetMarkerColor(kRed);
	grph->GetXaxis()->SetLimits(xMin,xMax);
	grph->SetMinimum(yMin);
	grph->SetMaximum(yMax);
	grph->Draw("AP");
	
	TF1 *total = new TF1("total","[0]*(TMath::Exp(x/[1]))",fitMin,fitMax);
	total->SetLineColor(kAzure);
	
	
	total->SetParameter(0,p0);
	total->SetParameter(1,p1);
		
	grph->Fit(total,"WVEM");
	
	
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
	TF1 *total2 = new TF1("total2","total * x",fitMin,fitMax);
	
	// Compute integral for bottom of the expectation value function
	Double_t integral1 = total->Integral(fitMin,fitMax);
	// Compute error of the integral
	Double_t integral1Error = total->IntegralError(fitMin,fitMax,parErrors,covMatrix.
													GetMatrixArray());
	// Compute integral for top of the expectation value function
	Double_t integral2 = total2->Integral(fitMin,fitMax);
	// Compute error of the integral
	Double_t integral2Error = total2->IntegralError(fitMin,fitMax,parErrors,covMatrix.
												GetMatrixArray());
	
	cout << "\n\n\tError of first integral:\t" << integral1Error;
	cout << "\n\tError of second integral:\t" << integral2Error; 
	
	// Print integrals and the expectation value
	//cout << "\n\n\tIntegral y * dN/dy:\t" << integral2 << endl << endl;
	//cout << "\n\tIntegral dN/dy:\t\t" << integral1 << endl << endl;
	cout << "\n\n\t<y>:\t" << integral2/integral1 << "+/- " << integral1Error << endl << endl;
	
}