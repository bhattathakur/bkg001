{
  //Data file containing final errors and parameters
  char  dataafile[]="/home/Thakur.Bhatta/data9.24/dat/stability/bkg001/DATA/finalEnergyerror.dat";//A,mean,sigma,error in A,error in mean, error in sigma,N
  char pdfresoluton[]="/home/Thakur.Bhatta/data9.24/dat/stability/bkg001/PLOTS/resolutionplot.pdf"; //pdf file to save the plot
  ifstream inputres(dataafile);
  if(inputres.is_open())
    {
	cout<<"successfully opend the file "<<dataafile<<endl;
    }
  else
    {
	cout<<"Unable to open the file "<<dataafile<<endl;
    }
  
  c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(29);
  TGraphErrors *graph_expected=new TGraphErrors(dataafile,"%*lg%lg%lg%*lg%lg%lg%*lg","");//A,mean,sigma,error in A,error in mean, error in sigma,N
  graph_expected->SetTitle("Energy Resolution plot;E/#mu(eV);(#sigma);");
  graph_expected->SetMarkerColor(4);
  graph_expected->SetMarkerStyle(21);
  graph_expected->SetLineColor(9);
  graph_expected->SetLineWidth(2);
  graph_expected->Draw("AP");
  graph_expected->Fit("pol1");
  graph_expected->GetFunction("pol1")->SetLineStyle(2);
  graph_expected->GetFunction("pol1")->SetParName(0,"Intercept(p_{0})");
  graph_expected->GetFunction("pol1")->SetParName(1,"Slope(p_{1})");

  c->GetFrame()->SetFillColor(21);
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  c->Update();

  //Legend
  auto legend=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  legend->AddEntry(graph_expected->GetFunction("pol1"),"#sigma=p_{0}+p_{1}E","l");
  legend->AddEntry(graph_expected,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  legend->Draw();
  c->SaveAs(pdfresoluton);//Using as the pdf file for the plot

  const int E=1332;
  cout<<fixed<<setprecision(8);
  const double slope=graph_expected->GetFunction("pol1")->GetParameter(1);
  cout<<"slope = "<<slope<<endl;
  const double intercept=graph_expected->GetFunction("pol1")->GetParameter(0);
  cout<<"intercept = "<<intercept<<endl;
  double sigma=slope*E+intercept;
  double FWHM=2.355*sigma;
  cout<<fixed<<setprecision(3);
  cout<<"Corresponding to E = 1332 keV for (Co-60)): "<<endl;
  cout<<"sigma = "<<sigma<<endl;
  cout<<"FWHM  = "<<FWHM<<endl;
}
