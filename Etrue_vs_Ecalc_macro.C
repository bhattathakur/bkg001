{
  const char * filedata="E_estandE_true.dat"; //File storing the estimated and true energy and their errors
  const char * rootfile="true_estimated_enregyplot.root"; //root file to save the plot
  const char * filename="slope_intercept.dat"; //file to store slope and intercept of plot
  c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(29);
  graph_expected=new TGraphErrors(filedata,"%lg%lg%lg%lg","");//E-calc,E-true,errorE-Calc,errorE-true
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

  c->GetFrame()->SetFillColor(21);
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  c->Update();

  //Legend
  auto legend=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  //legend->SetHeader("The Legend Title");
  legend->AddEntry(graph_expected->GetFunction("pol1"),"E_{estimated}=P_{0}+P_{1}E_{true}","l");
  legend->AddEntry(graph_expected,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  legend->Draw();
  
//Saving the plot in root file
file=new TFile(rootfile,"RECREATE");
 if(file->IsOpen())cout<<rootfile <<" opened successfully"<<endl;
graph_expected->Write();
 c->Write();
//c->Close();
 ofstream output(filename);
 double m1,c1; //slope , intercept
  if(output.is_open())
   {
     output<<setw(10)<<  graph_expected->GetFunction("pol1")->GetParameter(0)<<setw(10)<<graph_expected->GetFunction("pol1")->GetParameter(1)<<endl;
     cout<<"Successfully stored intercept and slope in the file"<<filename<<endl;
     
     }
  else
    {
	cout<<"Unable to open the file "<< filename<<endl;
	return 0;
    }
} 
