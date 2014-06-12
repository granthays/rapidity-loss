/************************************************************************************
 * Plotting the curve for the positive, negative, and full fit function at 158 GeV
 *
 * Title:		Plot158tri.cxx
 * Author:		Grant Hays
 * Date: 		29 May 2014
 * Description:	This is a ROOT macro to plot data from RHIC for the data at 158 GeV,
 *				as well as the curve of the best fit functions on the positive (red),
 *				negative (blue), and full (violet) data sets.
 ************************************************************************************/
{

	// The range of the fit.
	Double_t fitMin[3] = {-3.6,-2.9,-3.2};
	Double_t fitMax[3] = {3.6,2.9,3.2};
	
	// The range of the X-axis on the printed graph
	Double_t xMin = -4.;
	Double_t xMax = 4.;
	
	// The range of the Y-axis on the printed graph
	Double_t yMin = 0.;
	Double_t yMax = 0.4;
	
	// Initial guesses for the parameters
	Double_t expP0[3] = {0.0066618,0.03682,0.00935};
	Double_t errP0[3] = {0.00016992,1.47023e-009,3.10359e-005};
	
	Double_t expP1[3] = {1.28977,1.12302,1.00247};
	Double_t errP1[3] = {0.0177675,1.16983e-006,0.00676547};
	
	Int_t numOfData[3] = {23,30,11};
	
	

/*********************************************************************************/
	
	// Setting up Canvas and Grid for Graph
	TCanvas* c1 = new TCanvas("c1","c1",1000,700);
	//c->SetGrid();
	
	// This will add an information box to the graph containing
	// the fit function parameters and Chi2/ndf
	gStyle->SetOptFit(0);
	
	// Creating and filling the TGraphErrors
	TGraphErrors *gr158 = new TGraphErrors("./158GeV.dat","%lg %lg %lg");
	gr158->SetName("gr158");
	// Set titles for the graph and it's axes
	gr158->SetTitle(
		";
		y';
		dN/dy'");
	gr158->SetLineColor(kBlack);
	gr158->SetLineWidth(2);
	gr158->SetMarkerStyle(24);
	gr158->SetMarkerSize(2);
	gr158->SetMarkerColor(kGreen+1);
	// Set the range of the X-axis so that it shows everything, but isn't too big
	gr158->GetXaxis()->SetLimits(xMin,xMax);
	gr158->SetMinimum(yMin);
	gr158->SetMaximum(yMax);
	// Draw with options:
	//		A = Axis are drawn around the graph
	//		P = The current marker is plotted at each point
	gr158->Draw("AP");
	
	
	/************************************************************************/
	
	
	
	TF1 *fit158Full = new TF1("fit158Full","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	//TF1 *fit158 = new TF1("fit158","[0]*(TMath::Exp(x/[1]))",-5.,5.);
	fit158Full->SetParameter(0,expP0[1]);
	fit158Full->SetParameter(1,expP1[1]);
	fit158Full->SetLineWidth(3);
	fit158Full->SetLineColor(kViolet);
	

	
//--------------------------------------------------------------------


	//TF1 *fit158 = new TF1("fit158","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	TF1 *fit158N = new TF1("fit158N","[0]*(TMath::Exp(-x/[1]))",5.,-5.);
	fit158N->SetParameter(0,expP0[1]);
	fit158N->SetParameter(1,expP1[1]);
	fit158N->SetLineWidth(3);
	fit158N->SetLineColor(kBlue);
	


//--------------------------------------------------------------------


	
	//TF1 *fit158 = new TF1("fit158","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	TF1 *fit158 = new TF1("fit158","[0]*(TMath::Exp(x/[1]))",-5.,5.);
	fit158->SetParameter(0,expP0[1]);
	fit158->SetParameter(1,expP1[1]);
	fit158->SetLineWidth(3);
	fit158->SetLineColor(kRed);
	
	

	fit158Full->Draw("LSame");

	fit158N->Draw("LSame");

	fit158->Draw("LSame");

	
	
	return c1;
	
}
