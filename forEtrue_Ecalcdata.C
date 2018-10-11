{
  //Data File contaiing estimated energy and true energy
  char input1[]="initialEnergyerror.dat"; //estimated 
  char input2[]="tabulated_energy.dat"; //true
  char output[]="E_estandE_true.dat";
  ifstream file1(input1);
  ifstream file2(input2);
  if(file1.is_open())
    {
	cout<<input1<< " successfully opened"<<endl;
    }
  else
    {
	cout<<"failed to open"<< file1<<endl;
	return 0;
    }
  if(file2.is_open())
    {
	cout<<input2<< " successfully opened"<<endl;
    }
  else
    {
	cout<<"failed to open"<< file2<<endl;
	return 0;
    }
  double amplitude,mean,sigma,errorAmp,errorMean,errorSigma,N;  //input1
  double trueE,errorE; //input2
  //Open file to store the required data:
  ofstream file3(output);
  if(file3.is_open())
    {
	while(1)
	  {
	    file1>>amplitude>>mean>>sigma>>errorAmp>>errorMean>>errorSigma>>N;
	    file2>>trueE>>errorE;
	    if(!file1.good()|| !file2.good())break;
	    // cout<<setw(10)<<mean<<setw(10)<<trueE<<setw(10)<<errorMean<<setw(10)<<errorE<<endl;
	    file3<<setw(10)<<mean<<setw(10)<<trueE<<setw(10)<<errorMean<<setw(10)<<errorE<<endl;
	  }
	cout<<"successfully stored the E-Calc,E-true and erros in the file "<<output<<endl;
    }
  else
    {
	cout<<"Unable to open file "<<output<<endl;
	return 0;
    }
}
