/*********************************************************************************
 * Plotting data points and curve of polynomial fit function for three energy levels
 *
 * Title:		PlotAllPoly4.cxx
 * Author:		Grant Hays
 * Date: 		29 May 2014
 * Description:	This is a ROOT macro to plot data from RHIC for three energy
 *				levels, as well as the curve of the best fourth degree fit 
  *				functions.
 *********************************************************************************/
{

	// The range of the fit.
	Double_t fitMin[3] = {0.4,0.,0.};
	Double_t fitMax[3] = {3.6,2.9,3.2};
	
	// The range of the X-axis on the printed graph
	Double_t xMin = 0.;
	Double_t xMax = 4.;
	
	// The range of the Y-axis on the printed graph
	Double_t yMin = 0.;
	Double_t yMax = 0.4;
	
	// Initial guesses for the parameters
	Double_t polyP0[3] = {0.00969221,0.03682,0.0192085};
	Double_t errP0[3] = {0.000279788,0.00147079,0.000713582};
	
	Double_t polyP1[3] = {0.00340975,0.073939,0.00315261};
	Double_t errP1[3] = {0.000321774,0.00681557,0.00122971};
	
	Double_t polyP2[3] = {0.000356624,-0.0040087,0.00178204};
	Double_t errP2[3] = {3.68146e-005,0.00105205,0.000160708};
	

/*********************************************************************************/
	
	// Setting up Canvas and Grid for Graph
	TCanvas* c1 = new TCanvas("c1","c1",1000,800);
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
	gr200->SetLineWidth(2);
	gr200->SetMarkerStyle(24);
	gr200->SetMarkerSize(2);
	gr200->SetMarkerColor(kRed+1);
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
	gr624->SetMarkerColor(kBlue+1);
	gr624->Draw("PSame");
	
	
	/************************************************************************/
	
	
	TF1 *fit200 = new TF1("fit200","([0] + ([1]*(x*x)) + ([2]*(x*x*x*x)))",0.,5.);
	fit200->SetParameter(0,polyP0[0]);
	fit200->SetParameter(1,polyP1[0]);
	fit200->SetParameter(2,polyP2[0]);
	fit200->SetLineWidth(2);
	fit200->SetLineColor(kBlack);
	
	
	TF1 *fit158 = new TF1("fit158","([0] + ([1]*(x*x)) + ([2]*(x*x*x*x)))",0.,5.);
	fit158->SetParameter(0,polyP0[1]);
	fit158->SetParameter(1,polyP1[1]);
	fit158->SetParameter(2,polyP2[1]);
	fit158->SetLineWidth(2);
	fit158->SetLineColor(kBlack);
	
	
	TF1 *fit624 = new TF1("fit624","([0] + ([1]*(x*x)) + ([2]*(x*x*x*x)))",0.,5.);
	fit624->SetParameter(0,polyP0[2]);
	fit624->SetParameter(1,polyP1[2]);
	fit624->SetParameter(2,polyP2[2]);
	fit624->SetLineWidth(2);
	fit624->SetLineColor(kBlack);
	
	
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
