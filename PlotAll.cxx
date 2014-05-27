int PlotAll(){
	
	// The range of the fit.
	double fitMin = 0.4;
	double fitMax = 3.6;
	
	// The range of the X-axis on the printed graph
	double xMin = 0.;
	double xMax = 5.;
	
	// The range of the Y-axis on the printed graph
	double yMin = 0.;
	double yMax = 0.4;
	
	// Initial guesses for the parameters
	double p0 = 0.0093;
	double p1 = 1.45;
	

/*********************************************************************************/
	
	// Setting up Canvas and Grid for Graph
	TCanvas* c = new TCanvas();
	c->SetGrid();
	
	// This will add an information box to the graph containing
	// the fit function parameters and Chi2/ndf
	gStyle->SetOptFit();
	
	// Creating and filling the TGraphErrors
	TGraphErrors *gr200 = new TGraphErrors("./200GeVP.dat","%lg %lg %lg");
	
	// Set titles for the graph and it's axes
	gr200->SetTitle(
		"200 GeV (Positive);
		y';
		dN/dy'");
	// Set plot marker style to filled squares
	gr200->SetMarkerStyle(21);
	// Set plot marker color to red
	gr200->SetMarkerColor(kRed);
	// Set the range of the X-axis so that it shows everything, but isn't too big
	gr200->GetXaxis()->SetLimits(xMin,xMax);
	gr200->SetMinimum(yMin);
	gr200->SetMaximum(yMax);
	// Draw with options:
	//		A = Axis are drawn around the graph
	//		P = The current marker is plotted at each point
	gr200->DrawClone("AP");
	
	
	
	TGraphErrors *gr158 = new TGraphErrors("./158GeVP.dat","%lg %lg %lg");
	gr158->SetMarkerStyle(22);
	gr158->DrawClone("PSame");
	
	TGraphErrors *gr624 = new TGraphErrors("./624GeVP.dat","%lg %lg %lg");
	gr624->SetMarkerStyle(22);
	gr624->DrawClone("PSame");
	/*
	TLegend *leg = new TLegend(.1,.7,.3,.9," ");
	leg->SetFillColor(0);
	leg->AddEntry(&gr624, "62.4 GeV");
	leg->AddEntry(&gr158, "158 GeV");
	leg->AddEntry(&gr200, "200 GeV");
	leg->DrawClone("Same");
	*/
}
