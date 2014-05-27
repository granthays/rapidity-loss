//Create and Draw a TMultiGraph
//Author:: Rene Brun
{
	
	// The range of the fit.
	Float_t fitMin[] = {0.4,0.0,0.0};
	Float_t fitMax[] = {3.6,2.9,3.2};
	
	// The range of the X-axis on the printed graph
	Float_t xMin = 0.;
	Float_t xMax = 5.;
	
	// The range of the Y-axis on the printed graph
	Float_t yMin = 0.;
	Float_t yMax = 0.4;
	
	// Initial guesses for the parameters
	Float_t p0[] = {0.0093,0.04,0.00935};
	Float_t p1[] = {1.45,1.13,1.};
	
	gStyle->SetOptFit();
	TCanvas *c1 = new TCanvas();
	c1->SetGrid();
	
	// draw a frame to define the range
	TMultiGraph *mg = new TMultiGraph();

	
/**********************************************************************
 *
 *		First Graph 200 GeV
 *
 * 		 Initial p0 = 0.0093
 * 		 Initial p1 = 1.45
 *
**********************************************************************/
	// Creating and filling the TGraphErrors
	TGraphErrors *grph200 = new TGraphErrors("./200GeVP.dat","%lg %lg %lg");
	
	// Set plot marker style to filled squares
	grph200->SetMarkerStyle(21);
	// Set plot marker color to red
	grph200->SetMarkerColor(kCyan+1);
	
	// This is the fit function found by Chris Appier.
	TF1 *fit200 = new TF1("fit200","[0]*(TMath::Exp(x/[1]))",fitMin[0],fitMax[0]);
	
	// Set the fit line color to red, for some reason (I should probably change this)
	fit200->SetLineColor(kRed+1);
	
	fit200->SetParameter(0,p0[0]);
	fit200->SetParameter(1,p1[0]);
	
	// Fitting the entire range with the fit function
	grph200->Fit(fit200,"W");
	
	// Add the first graph to the multigraph
	mg->Add(grph200);
	
	
	
	
	
/**********************************************************************
 *
 *		First Graph 158 GeV
 *
 * 		 Initial p0 = 0.04
 * 		 Initial p1 = 1.13
 *
**********************************************************************/
	// Creating and filling the TGraphErrors
	TGraphErrors *grph158 = new TGraphErrors("./158GeVP.dat","%lg %lg %lg");

	// Set plot marker style to filled squares
	grph158->SetMarkerStyle(21);
	// Set plot marker color to red
	grph158->SetMarkerColor(kGreen+1);
	
	// This is the fit function found by Chris Appier.
	TF1 *fit158 = new TF1("fit158","[1]*(TMath::Exp(x/[1]))",fitMin[1],fitMax[1]);
	
	// Set the fit line color to red, for some reason (I should probably change this)
	fit158->SetLineColor(kMagenta+1);
	
	fit158->SetParameter(0,p0[1]);
	fit158->SetParameter(1,p1[1]);
	
	// Fitting the entire range with the fit function
	grph158->Fit(fit158,"W");

	// Add second graph to multigraph
	mg->Add(grph158);
	
	
	
/**********************************************************************
 *
 *		First Graph 62.4 GeV
 *
 * 		 Initial p0 = 0.0093
 * 		 Initial p1 = 1.00
 *
**********************************************************************/
	// Creating and filling the TGraphErrors
	TGraphErrors *grph624 = new TGraphErrors("./624GeVP.dat","%lg %lg %lg");

	// Set plot marker style to filled squares
	grph624->SetMarkerStyle(21);
	// Set plot marker color to red
	grph624->SetMarkerColor(kYellow+1);
	
	// This is the fit function found by Chris Appier.
	TF1 *fit624 = new TF1("fit624","[2]*(TMath::Exp(x/[2]))",fitMin[2],fitMax[2]);
	
	// Set the fit line color to red, for some reason (I should probably change this)
	fit624->SetLineColor(kBlue+1);
	
	fit624->SetParameter(0,p0[2]);
	fit624->SetParameter(1,p1[2]);
	
	// Fitting the entire range with the fit function
	grph624->Fit(fit624,"W");

	// Add second graph to multigraph
	mg->Add(grph624);
	
	// Draw the damn thing.
	mg->Draw("AP");
	mg->GetXaxis()->SetTitle("y");
	mg->GetYaxis()->SetTitle("dN/dy");
	
	// Set the range of the X-axis so that it shows everything, but isn't too big
	gPad->Modified();
	mg->GetXaxis()->SetLimits(xMin,xMax);
	mg->SetMinimum(yMin);
	mg->SetMaximum(yMax);

	
	
	//force drawing of canvas to generate the fit TPaveStats
	c1->Update();
	TPaveStats *stats1 = (TPaveStats*)grph200->GetListOfFunctions()->FindObject("stats");
	TPaveStats *stats2 = (TPaveStats*)grph158->GetListOfFunctions()->FindObject("stats");
	TPaveStats *stats3 = (TPaveStats*)grph624->GetListOfFunctions()->FindObject("stats");
	stats1->SetTextColor(kCyan+1); 
	stats2->SetTextColor(kMagenta+1); 
	stats3->SetTextColor(kCyan+1);
	stats1->SetX1NDC(0.12); stats1->SetX2NDC(0.32); stats1->SetY1NDC(0.75);
	stats2->SetX1NDC(0.42); stats2->SetX2NDC(0.62); stats2->SetY1NDC(0.75);
	stats3->SetX1NDC(0.72); stats3->SetX2NDC(0.92); stats3->SetY1NDC(0.75);
	c1->Modified();
	return c1;
}