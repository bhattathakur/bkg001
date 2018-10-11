{
  //Defining the array to read the paramertes
const  int peakNo=23;
  double firstParameter[peakNo]={};
  double secondParameter[peakNo]={};
  double thirdParameter[peakNo]={};
  double firstLimit[peakNo]={};
  double secondLimit[peakNo]={};
  //double firstParameter[peakNo],secondParameter[peakNo],thirdParameter[peakNo],firstLimit[peakNo],secondLimit[peakNo];
  ifstream datafile("initialestimates.dat"); //File containing the estimated fit parameters
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

  //Creating the canvas and rootfile to store different histograms 
  TCanvas *c = new TCanvas("c","Histogram",500,700);
  //  char * root_file="initial.root";
  TFile *file=new TFile("allhistograms.root","RECREATE"); //Root file to store the histograms

  TF1 * f[peakNo];
  TH1F * h[peakNo]; //Array of histograms
  //Reading the histogram from rootfile
  //  char * filename="initial.root";
  TFile *MyFile = new TFile("initial.root","READ");
  if(MyFile->IsOpen())cout<<" file opened successfully\n";
  TH1F *his = (TH1F*)MyFile->Get("histo");
  
  for(int i=0;i<peakNo;i++)
    {
      f[i]=new TF1(Form("f%d",i),"[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
      f[i]->SetParNames("A","#mu","#sigma","a1","b1");
      f[i]->SetParameters(firstParameter[i],secondParameter[i],thirdParameter[i],0,0);
	cout<<endl;
	cout<<"########################  Peak "<<(i+1)<<"  #########################     "<<endl;
	cout<<endl;
      c->cd(i+1);
	h[i]=(TH1F*)his->Clone(Form("h%d",i+1));
	//	h[i]=(TH1F*)MyFile->Get("histo");
      h[i]->GetXaxis()->SetTitle("Energy(keV)");
      h[i]->GetXaxis()->CenterTitle();
      h[i]->GetYaxis()->SetTitle("Counts/Channel");
      h[i]->GetYaxis()->CenterTitle();
      h[i]->Fit(f[i],"rem+","",firstLimit[i],secondLimit[i]);
   	h[i]->Sumw2();
	gStyle->SetOptStat(1000000001);
      gStyle->SetOptFit(1111);
	h[i]->Draw();
	  // histo->Draw();
	file->cd();
	h[i]->Write();
    }

  ///////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%555/////////////////////////////////////
 //Storing the Gaussian mean and Number of Counts in Peak based on fit parametes%%%%%%%%%%%%%%%555555///
  
 ofstream myfile("initialEnergyerror");
 const double binWidth=his->GetBinWidth(1);
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
