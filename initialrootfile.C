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
