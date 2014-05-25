int PlotAll(){
	
	ifstream inp;
	double x[100], y[100];
	int n = 0;
	
	inp.open("158gevN.txt");
	while(inp >> x[n] >> y[n]) {
		n++;
	}
	
	TCanvas* c = new TCanvas();
	c->SetGrid();
	
	TGraphErrors *gr158 = new TGraph(n,x,y);
	
	//TGraphErrors gr158("./158gevN.txt","%lg %lg");
	
	//gr158->SetTitle(
	//	"Rapidity Density at 62.4 GeV, 158 GeV, and 200 GeV;
	//	y';
	//	dN/dy'");
	gr158->SetMarkerStyle(22);
	gr158->SetMarkerColor(kBlack);
	gr158->GetXaxis()->SetLimits(-5.,0.);
	gr158->DrawClone("AP");
	
	TGraphErrors gr200("./200gevN.txt","%lg %lg");
	gr200.SetMarkerStyle(8);
	gr200.SetMarkerColor(kBlue);
	gr200.DrawClone("PSame");
	
	TGraphErrors gr624("./62.4gevN.txt","%lg %lg");
	gr624.SetMarkerStyle(21);
	gr624.SetMarkerColor(kRed);
	gr624.DrawClone("PSame");
	
	TLegend leg(.1,.7,.3,.9," ");
	leg.SetFillColor(0);
	leg.AddEntry(&gr624, "62.4 GeV");
	leg.AddEntry(&gr158, "158 GeV");
	leg.AddEntry(&gr200, "200 GeV");
	leg.DrawClone("Same");
}
