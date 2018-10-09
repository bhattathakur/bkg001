//Energy calibration function....:      0.15448454 keV +     0.38903224 keV/chn
{
  double b1=0.15448454;
  double m1=0.38903224;
  double Emin=0;
  const int numberOfChannels=16384;
  double Emax=numberOfChannels;
  double correctedEmin=Emin*m1-b1;
  double correctedEmax=Emax*m1-b1;
  cout<<"correctedEmin = "<<correctedEmin<<endl;
  cout<<"correctedEmax = "<<correctedEmax<<endl;
  
  TCanvas *c = new TCanvas("c","Histogram",500,700);
  char * root_file="initial.root";
  TFile *file=new TFile(root_file,"RECREATE"); //Root file to store the histograms
  TH1F *histo=new TH1F("histo","#font[22]{Calibrated Energy Spectrum}",numberOfChannels,correctedEmin,correctedEmax);
  // string inputfile="bkg_001.dat";
  
   ifstream input("bkg_001.dat");
   if(input.is_open())
	 {
	   Float_t x,y; //for storing the data in histogram
	   Int_t nlines=0; //for counting the number of lines
	   while(1)
		 {
		   input>>x>>y; //Reading the data file into two columns
		   if(!input.good())break;
		   histo->SetBinContent(x,y); //SetBinContent(bin,content)
		   nlines++;
		 }
	   input.close();
	 }
   else
	 {
	   cout<<"Unable to open the data file to create energy spectrum"<<endl;
	   return 0;
	 }
  printf("found %d lines\n",nlines);
  histo->GetXaxis()->SetTitle("Energy(keV)");
  histo->GetYaxis()->SetTitle("Counts/Channel");
  gStyle->SetOptStat(1000000001);//shows only name of the histogram
  histo->Draw();
  histo->Write();
  cout<<"stored histogram in the root file: "<<root_file<<endl;
  //  file->Close();
}
  /*
  double firstParameter[peakNo]={0};
  double secondParameter[peakNo]={0};
  double thirdParameter[peakNo]={0};
  double firstLimit[peakNo]={0};
  double secondLimit[peakNo]={0};
  
  ifstream datafile("gussedParameterfinal.dat"); //File containing the estimated fit parameters
  if(datafile.is_open())
	{
	  cout<<" File reading for estimated parameters done successfully"<<endl;
	  int peakCount=0;
	  while(peakCount<=peakNo)
		{
		  datafile>>firstParameter[peakCount]>>secondParameter[peakCount]>>thirdParameter[peakCount]>>firstLimit[peakCount]>>secondLimit[peakCount];
		  peakCount++;
		}
	}
  else
	{
	  cout<<"Error in reading the file  for estimated paramters"<<endl;
	  return 0;
	}
  TF1 * f[peakNo];
  TH1F * h[peakNo]; //Array of histograms
  for(int i=0;i<peakNo;i++)
    {
      f[i]=new TF1(Form("f%d",i),"[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
      f[i]->SetParNames("A","#mu","#sigma","a1","b1");
      f[i]->SetParameters(firstParameter[i],secondParameter[i],thirdParameter[i],0,0);
	  cout<<endl;
	  cout<<"########################  Peak "<<(i+1)<<"  #########################     "<<endl;
	  cout<<endl;
      c->cd(i+1);
	  h[i]=(TH1F*)histo->Clone(Form("h%d",i+1));
      h[i]->GetXaxis()->SetTitle("Energy(keV)");
      h[i]->GetXaxis()->CenterTitle();
      h[i]->GetYaxis()->SetTitle("Counts/Channel");
      h[i]->GetYaxis()->CenterTitle();
      h[i]->Fit(f[i],"rem+","",firstLimit[i],secondLimit[i]);
   	  h[i]->Sumw2();
      gStyle->SetOptFit(1111);
	  h[i]->Draw();
	  // histo->Draw();
	  file->cd();
	  h[i]->Write();
    }

  ///////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%555/////////////////////////////////////
 //Storing the Gaussian mean and Number of Counts in Peak based on fit parametes%%%%%%%%%%%%%%%555555///
  
 ofstream myfile("finalerrordata.dat");
 const double binWidth=histo->GetBinWidth(1);
 if(myfile.is_open())
 {
   cout<<"Creating the file with A,eA,u,eu,6,e6,N"<<endl;
  myfile<<fixed<<setprecision(2);
     for(int i=0;i<peakNo;i++)
       {
         myfile<< f[i]->GetParameter(0)<<'\t'<<f[i]->GetParameter(1)<<'\t'<<f[i]->GetParameter(2)<<'\t'<<f[i]->GetParError(0)
			   <<'\t'<<f[i]->GetParError(1)<<'\t'<<f[i]->GetParError(2)<<'\t'<<f[i]->GetParameter(0)/binWidth<<endl;
       }
     cout<<"successfully stored gaussian mean and Number of events in \"finalerror.dat\""<<endl;
 }
 else cout<<"unable to open the file \"finalerror.dat\" " <<endl;
 //file->Close(); 
 //}
 //gROOT->ProcessLine(".x plotTabulatedvsCalculated.C");
}
