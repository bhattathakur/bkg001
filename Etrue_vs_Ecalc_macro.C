{
  char * datafile="E_estandE_true.dat";
  char * rootfile="true_estimated_enregyplot.root";
  c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(29);
  graph_expected=new TGraphErrors(datafile,"%lg%lg%lg","");//E-calc,E-true,errorE-Calc,errorE-true
  graph_expected->SetTitle("E_{true} vs  E_{estimated}  Plot;E_{true}(eV);E_{estimated}(eV);");
  graph_expected->GetYaxis()->SetTitleOffset(1.2);
  graph_expected->SetMarkerColor(4);
  graph_expected->SetMarkerStyle(21);
  graph_expected->SetLineColor(9);
  graph_expected->SetLineWidth(2);
  graph_expected->Draw("AP");
  graph_expected->Fit("pol1");
  graph_expected->GetFunction("pol1")->SetLineStyle(2);
  graph_expected->GetFunction("pol1")->SetParName(0,"Intercept(P_{0})");
  graph_expected->GetFunction("pol1")->SetParName(1,"Slope(P_{1})");
  //->Update();
  c->GetFrame()->SetFillColor(21);
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  c->Update();
  //raph_expected->Draw();

  //Legend
  auto legend=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  //legend->SetHeader("The Legend Title");
 
  legend->AddEntry(graph_expected->GetFunction("pol1"),"E_{estimated}=P_{0}+P_{1}E_{true}","l");
  legend->AddEntry(graph_expected,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  // gStyle->SetLegendTextSize(12);
  legend->Draw();
//Saving the plot in root file
file=new TFile(rootfile,"RECREATE");
if(file->IsOpen())cout<<rootfile <<" opened successfully";
graph_expected->Write();
c->Close();
  // c->Modified();
  //Calculating the sigma corresponding to E=1332 keV for Co-60
  /*const int E=1332;
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
  cout<<"FWHM  = "<<FWHM<<endl;*/
}
