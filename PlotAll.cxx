/*********************************************************************************
 * 	Plotting data points and curve of fit function for three energy levels
 *
 * Title:		PlotAll.cxx
 * Author:		Grant Hays
 * Date: 		29 May 2014
 * Description:	This is a ROOT macro to plot data from RHIC for three energy
 *				levels, as well as the curve of the best fit functions.
 *********************************************************************************/
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
	TGraphErrors *gr200 = new TGraphErrors("./200GeV.dat","%lg %lg %lg");
	gr200->SetName("gr200");
	// Set titles for the graph and it's axes
	gr200->SetTitle(
		";
		y';
		dN/dy'");
	gr200->SetLineColor(kBlack);
	gr200->SetLineWidth(3);
	gr200->SetMarkerStyle(24);
	gr200->SetMarkerSize(2);
	gr200->SetMarkerColor(kRed);
	// Set the range of the X-axis so that it shows everything, but isn't too big
	gr200->GetXaxis()->SetLimits(xMin,xMax);
	gr200->SetMinimum(yMin);
	gr200->SetMaximum(yMax);
	// Draw with options:
	//		A = Axis are drawn around the graph
	//		P = The current marker is plotted at each point
	gr200->Draw("AP");
	
	
	TGraphErrors *gr158 = new TGraphErrors("./158GeV.dat","%lg %lg %lg");
	gr158->SetName("gr158");
	gr158->SetLineColor(kBlack);
	gr158->SetLineWidth(2);
	gr158->SetMarkerStyle(25);
	gr158->SetMarkerSize(2);
	gr158->SetMarkerColor(kGreen+1);
	gr158->Draw("PSame");
	
	TGraphErrors *gr624 = new TGraphErrors("./624GeV.dat","%lg %lg %lg");
	gr624->SetName("gr624");
	gr624->SetLineColor(kBlack);
	gr624->SetLineWidth(2);
	gr624->SetMarkerStyle(26);
	gr624->SetMarkerSize(2);
	gr624->SetMarkerColor(kBlue);
	gr624->Draw("PSame");
	
	
	/************************************************************************/
	
	
	TF1 *fit200Full = new TF1("fit200Full","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	//TF1 *fit200 = new TF1("fit200","[0]*(TMath::Exp(x/[1]))",-5.,5.);
	fit200Full->SetParameter(0,expP0[0]);
	fit200Full->SetParameter(1,expP1[0]);
	fit200Full->SetLineWidth(2);
	fit200Full->SetLineColor(kViolet);
	
	
	TF1 *fit158Full = new TF1("fit158Full","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	//TF1 *fit158 = new TF1("fit158","[0]*(TMath::Exp(x/[1]))",-5.,5.);
	fit158Full->SetParameter(0,expP0[1]);
	fit158Full->SetParameter(1,expP1[1]);
	fit158Full->SetLineWidth(2);
	fit158Full->SetLineColor(kViolet);
	
	
	TF1 *fit624Full = new TF1("fit624Full","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	//TF1 *fit624 = new TF1("fit624","[0]*(TMath::Exp(x/[1]))",-5.,5.);
	fit624Full->SetParameter(0,expP0[2]);
	fit624Full->SetParameter(1,expP1[2]);
	fit624Full->SetLineWidth(2);
	fit624Full->SetLineColor(kViolet);
	
//--------------------------------------------------------------------

	//TF1 *fit200 = new TF1("fit200","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	TF1 *fit200N = new TF1("fit200N","[0]*(TMath::Exp(-x/[1]))",5.,-5.);
	fit200N->SetParameter(0,expP0[0]);
	fit200N->SetParameter(1,expP1[0]);
	fit200N->SetLineWidth(2);
	fit200N->SetLineColor(kBlue);
	
	
	//TF1 *fit158 = new TF1("fit158","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	TF1 *fit158N = new TF1("fit158N","[0]*(TMath::Exp(-x/[1]))",5.,-5.);
	fit158N->SetParameter(0,expP0[1]);
	fit158N->SetParameter(1,expP1[1]);
	fit158N->SetLineWidth(2);
	fit158N->SetLineColor(kBlue);
	
	
	//TF1 *fit624 = new TF1("fit624","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	TF1 *fit624N = new TF1("fit624N","[0]*(TMath::Exp(-x/[1]))",5.,-5.);
	fit624N->SetParameter(0,expP0[2]);
	fit624N->SetParameter(1,expP1[2]);
	fit624N->SetLineWidth(2);
	fit624N->SetLineColor(kBlue);

//--------------------------------------------------------------------

	//TF1 *fit200 = new TF1("fit200","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	TF1 *fit200 = new TF1("fit200","[0]*(TMath::Exp(x/[1]))",-5.,5.);
	fit200->SetParameter(0,expP0[0]);
	fit200->SetParameter(1,expP1[0]);
	fit200->SetLineWidth(2);
	fit200->SetLineColor(kRed);
	
	
	//TF1 *fit158 = new TF1("fit158","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	TF1 *fit158 = new TF1("fit158","[0]*(TMath::Exp(x/[1]))",-5.,5.);
	fit158->SetParameter(0,expP0[1]);
	fit158->SetParameter(1,expP1[1]);
	fit158->SetLineWidth(2);
	fit158->SetLineColor(kRed);
	
	
	//TF1 *fit624 = new TF1("fit624","[0]*(TMath::Exp(x/[1]) + TMath::Exp(-x/[1]))",-5.,5.);
	TF1 *fit624 = new TF1("fit624","[0]*(TMath::Exp(x/[1]))",-5.,5.);
	fit624->SetParameter(0,expP0[2]);
	fit624->SetParameter(1,expP1[2]);
	fit624->SetLineWidth(2);
	fit624->SetLineColor(kRed);


	
	
	fit200Full->Draw("LSame");
	fit158Full->Draw("LSame");
	fit624Full->Draw("LSame");
	
	fit200N->Draw("LSame");
	fit158N->Draw("LSame");
	fit624N->Draw("LSame");
	
	fit200->Draw("LSame");
	fit158->Draw("LSame");
	fit624->Draw("LSame");
	
	
	
	
	/*
	TPaveText *paveText = new TPaveText(0.1,0.7,0.48,0.9,"NDC");
	paveText->AddText("Test text");
	paveText->Draw();
	*/
	
	TLegend *leg = new TLegend(.7,.75,.89,.89);
	leg->SetFillColor(0);
	leg->AddEntry("gr624","62.4 GeV","lp");
	leg->AddEntry("gr158","158 GeV","lp");
	leg->AddEntry("gr200","200 GeV","lp");
	leg->Draw();
	
	
	return c1;
	
}
