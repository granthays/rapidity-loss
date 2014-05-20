/*****************************************************************************************
 * 			Finding Best Fit Parameters of Rapidity Loss Function
 *
 * Title:		FitFind.cxx
 * Author:		Grant Hays
 * Date: 		20 May. 2014
 * Description:	This is a ROOT macro to find the best-fit parameters of the 
 *				rapidity loss function estimated by Chris A. Minimization
 *				techniques will be used from MINUIT, MINUIT2, MINOS, or MINGRAD.
 *
 * Modified from: 
 *	 http://superk.physics.sunysb.edu/~mcgrew/phy310/lectures/phy310-lecture-11-2007.pdf
 *****************************************************************************************/
 
// The function to be minimized. Remember C++ rules about function order:
//		Put it before minimizerExample
double fitFcn(double A, double exDiv) {
	return(A*(TMath::Exp(x/exDiv)));
}

void minuitFunction(int& nDim, double* gout, double& result, double par[], intflg) {
	result = myFunction(par[0], par[1]);
}

 void FitParMin()
{
	TFitter* minimizer = new TFitter(2);
	
	// MAKE IT QUIET!!
	{
		double p1 = -1;
		minimizer->ExecuteCommand("SET PRINTOUT",&p1,1);
	}
	
	// Tell the minimizer about the function to be minimized
	minimizer->SetFCN(minuitFunction);
	
	// Define the parameters
	//		arg1 - parameter number
	//		arg2 - parameter name
	//		arg3 - first guess at parameter value
	//		arg4 - estimated distance to minimum
	//		arg5 - ignore for now
	//		arg6 - ignore for now
	minimizer->SetParameter(0,"A",0.07364/2,1,0,0);
	minimizer->SetParameter(1,"exDiv",1.13,1,0,0);
	
	// Run the SIMPLEX minimizer to get close to the minimum
	minimizer->ExecuteCommand("SIMPLEX",0,0);
	
	// Run the MIGRAD minimizer, an extended Powell's method, to improve the fit
	minimizer->ExecuteCommand("MIGRAD",0,0);
	
	// Get the best fit values
	double bestA = minimizer->GetParameter(0);
	double bestExDiv = minimizer->GetParameter(1);
	
	// Get the function value at the best fit
	double minimum = myFunc(bestA, bestExDiv);
	
	// Do a scan of the function with one variable fixed and the other being minimized at
	//	each step to find delta chi2 = 1
	// 		-Pick step so you need about 500 steps to find uncertainty value.
	// 		-Repeat for other parameters
	double errA;
	for(errA = 0; errA < 10; errA += 0.001) {
		minimizer->SetParameter(0,"A",0.07364/2,1,0,0);
		minimizer->SetParameter(1,"exDiv",1.13,1,0,0);
		minimizer->ExecuteCommand("MIGRAD",0,0);
		double t = fitFcn(minimizer->GetParameter(0),
						  minimizer->GetParameter(1));
		if(t - minimum > 1.0) break;
	}
}