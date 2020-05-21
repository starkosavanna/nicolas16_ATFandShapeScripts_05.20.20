{
  TCanvas *c1 = new TCanvas ("c1","c1",800,600);   //instantiate the canvas.
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 1.0, 1.0);  //instantiate the first pad.
  gStyle->SetOptStat(0);   //don't print weird stats box that usually appears at upper right.
  pad1->SetBottomMargin(0.1); 
  pad1->Draw(); 
  pad1->cd();

  TFile *f1 = new TFile("~/Documents/UC_gradstudents/nicolas/nicolas_lowdpTandOS_05.18.20/qcd_nicolas16_lowdpTandOS_051920.root");  //grab the qcd file for OS and low dpT.
  f1->cd("NRecoBJet");  //go into the NRecoBJet folder.
  TH1D *ditaurecotau1tau2deltaptmass_crb_plot = Tau1Pt;  //grab the histo. for tau pT.
  Double_t nbins_ditaurecotau1tau2deltaptmasscrbplot = ditaurecotau1tau2deltaptmass_crb_plot->GetNbinsX();  //get the number of bins for the histo. for tau pT.
  Double_t xmin_ditaurecotau1tau2deltaptmasscrbplot = ditaurecotau1tau2deltaptmass_crb_plot->GetXaxis()->GetXmin();  //get the minimum for the x-axis for the histo. for tau pT.
  Double_t xmax_ditaurecotau1tau2deltaptmasscrbplot = ditaurecotau1tau2deltaptmass_crb_plot->GetXaxis()->GetXmax();  //get the maximum for the x-axis for the histo. for tau pT.

  ///---making clone of guy above---///
  TH1F *ditaurecotau1tau2deltaptmass_crb_plot_copy = new TH1F("ditaurecotau1tau2deltaptmass_crb_plot_copy","ditaurecotau1tau2deltaptmass_crb_plot_copy", nbins_ditaurecotau1tau2deltaptmasscrbplot,xmin_ditaurecotau1tau2deltaptmasscrbplot,xmax_ditaurecotau1tau2deltaptmasscrbplot);
  for(Int_t i=1;i<=nbins_ditaurecotau1tau2deltaptmasscrbplot;i++){
    ditaurecotau1tau2deltaptmass_crb_plot_copy->SetBinContent(i,ditaurecotau1tau2deltaptmass_crb_plot->GetBinContent(i)*ditaurecotau1tau2deltaptmass_crb_plot->GetBinWidth(i));
  }
  ditaurecotau1tau2deltaptmass_crb_plot_copy->Sumw2();  //properly handle the errors.
  
  TFile *f2 = new TFile("~/Documents/UC_gradstudents/nicolas/nicolas_lowdpTandLS_05.18.20/qcd_nicolas16_lowdpTandLS_051920.root");  //grab the qcd file for LS and low dpT.
  f2->cd("NRecoBJet");  //go into the NRecoBJet folder.
  TH1D *ditaurecotau1tau2deltaptmass_crd_plot = Tau1Pt;  //grab the histo. for tau pT.
  Double_t nbins_ditaurecotau1tau2deltaptmasscrdplot = ditaurecotau1tau2deltaptmass_crd_plot->GetNbinsX();  //get the number of bins for the histo. for tau pT.
  Double_t xmin_ditaurecotau1tau2deltaptmasscrdplot = ditaurecotau1tau2deltaptmass_crd_plot->GetXaxis()->GetXmin();  //get the minimum for the x-axis for the histo. for tau pT.
  Double_t xmax_ditaurecotau1tau2deltaptmasscrdplot = ditaurecotau1tau2deltaptmass_crd_plot->GetXaxis()->GetXmax();  //get the maximum for the x-axis for the histo. for tau pT.

  ///---making clone of guy above---///
  TH1F *ditaurecotau1tau2deltaptmass_crd_plot_copy = new TH1F("ditaurecotau1tau2deltaptmass_crd_plot_copy","ditaurecotau1tau2deltaptmass_crd_plot_copy", nbins_ditaurecotau1tau2deltaptmasscrdplot,xmin_ditaurecotau1tau2deltaptmasscrdplot,xmax_ditaurecotau1tau2deltaptmasscrdplot);
  for(Int_t i=0;i<=nbins_ditaurecotau1tau2deltaptmasscrdplot;i++){
    ditaurecotau1tau2deltaptmass_crd_plot_copy->SetBinContent(i,ditaurecotau1tau2deltaptmass_crd_plot->GetBinContent(i)*ditaurecotau1tau2deltaptmass_crd_plot->GetBinWidth(i));
  }
  ditaurecotau1tau2deltaptmass_crd_plot_copy->Sumw2();  //properly handle the errors.

  Double_t xbins_taupt[8] = {70, 80, 90, 100, 110, 120, 140, 160};  //chosen binning for the pT tau plot.
  Double_t xbins_met[9] = {30, 40, 50, 60, 70, 80, 90, 100, 120};  //chosen binning if using MET.
  Double_t xbins_mass[7] = {150, 200, 250, 300, 350, 475, 600};  //chosen binning for the mass plots.

  //Rebins the first one.
  ditaurecotau1tau2deltaptmass_crb_plot_copy->Rebin(7,"ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned",xbins_taupt);

  //Rebins the second one.
  ditaurecotau1tau2deltaptmass_crd_plot_copy->Rebin(7,"ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned",xbins_taupt);

  //Finally, this takes the first copied histogram, "ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned", and divides it by the second copied histogram, "ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned".
  TH1F ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot = (*ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned / *ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned);

  //---style parameters---///
  ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.SetMarkerColor(4);
  ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.SetMarkerStyle(7);
  ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.SetMarkerSize(2);


  //ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.GetXaxis()->SetTitle("m_{reco}(#tau_{1}, #tau_{2}, #Deltap_{T}(#tau_{1},#tau_{2})) [GeV]");
  //ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.GetXaxis()->SetTitle("m_{reco}(#tau_{1}, #tau_{2}, E^{miss}_{T}) [GeV]");
  //ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.GetXaxis()->SetTitle("E^{miss}_{T} [GeV]");
  ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.GetXaxis()->SetTitle("p_{T}(#tau) [GeV]");
  ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.GetYaxis()->SetTitle("R_{OS/LS} = N^{QCD}_{OS_CR_B}/N^{QCD}_{LS_CR_D}");
  ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.SetTitle(" ");
  ATF_R_of_OS_CR_B_dividedby_LS_CR_D_plot.Draw("hist e p");
  
  c1->Update();
}
