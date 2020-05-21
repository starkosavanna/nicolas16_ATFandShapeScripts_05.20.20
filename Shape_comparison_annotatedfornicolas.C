{
  ///---instantiating the canvas and the pad---///
  TCanvas *c1 = new TCanvas ("c1","c1",800,800);   //This line instantiates the canvas.
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.375, 1.0, 1.0);  //This line instantiates the first pad.
  gStyle->SetOptStat(0);   //This line allows you to remove the weird stats box that usually appears at upper right.
  pad1->SetBottomMargin(0.1);   //This line controls how much space is at the bottom below the pad. 
  pad1->SetGridx();   //This line is why the background of the pad has vertical dotted-ish lines. 
  pad1->Draw();   //This line draws the first pad. 
  pad1->cd();   //Just like when you cd into a folder, this line allows you to "cd" into the first pad to do work there. 

  ///---getting the mass distribution and making the copy from CR B (OS)---///
  TFile *f1 = new TFile("~/Documents/UC_gradstudents/nicolas/nicolas_lowdpTandOS_05.18.20/qcd_nicolas16_lowdpTandOS_051920.root");   ///This line grabs the file.
  f1->cd("NDiTauCombinations");   ///I went into this folder because your statistics were better - more on this later.
  TH1D *ditaurecotau1tau2deltaptmass_crb_plot = DiTauReconstructableMassDeltaPt;   ///This line grabs the mass plot.
  Double_t nbins_ditaurecotau1tau2deltaptmasscrbplot = ditaurecotau1tau2deltaptmass_crb_plot->GetNbinsX();   ///This line gets the bin number along x.
  Double_t xmin_ditaurecotau1tau2deltaptmasscrbplot = ditaurecotau1tau2deltaptmass_crb_plot->GetXaxis()->GetXmin();   ///This line gets the minimum on the x-axis.
  Double_t xmax_ditaurecotau1tau2deltaptmasscrbplot = ditaurecotau1tau2deltaptmass_crb_plot->GetXaxis()->GetXmax();   ///This line gets the maximum on the x-axis.

  TH1F *ditaurecotau1tau2deltaptmass_crb_plot_copy = new TH1F("ditaurecotau1tau2deltaptmass_crb_plot_copy","ditaurecotau1tau2deltaptmass_crb_plot_copy", nbins_ditaurecotau1tau2deltaptmasscrbplot,xmin_ditaurecotau1tau2deltaptmasscrbplot,xmax_ditaurecotau1tau2deltaptmasscrbplot);
  for(Int_t i=1;i<=nbins_ditaurecotau1tau2deltaptmasscrbplot;i++){
    ditaurecotau1tau2deltaptmass_crb_plot_copy->SetBinContent(i,ditaurecotau1tau2deltaptmass_crb_plot->GetBinContent(i)*ditaurecotau1tau2deltaptmass_crb_plot->GetBinWidth(i));
  }   ///This filling line makes the copy for you to manipulate subsequently.

  ditaurecotau1tau2deltaptmass_crb_plot_copy->Sumw2();
  
  ///---getting the mass distribution and making the copy from CR D (LS)---///
  TFile *f2 = new TFile("~/Documents/UC_gradstudents/nicolas/nicolas_lowdpTandLS_05.18.20/qcd_nicolas16_lowdpTandLS_051920.root");   ///This line grabs the second file.
  f2->cd("NDiTauCombinations");   ///I went into this folder because your statistics were better - more on this later.
  TH1D *ditaurecotau1tau2deltaptmass_crd_plot = DiTauReconstructableMassDeltaPt;   ///This line grabs the mass plot.
  Double_t nbins_ditaurecotau1tau2deltaptmasscrdplot = ditaurecotau1tau2deltaptmass_crd_plot->GetNbinsX();   ///This line gets the bin number along x for this second distribution.
  Double_t xmin_ditaurecotau1tau2deltaptmasscrdplot = ditaurecotau1tau2deltaptmass_crd_plot->GetXaxis()->GetXmin();   ///This line gets the minimum along the x-axis for this second distribution.
  Double_t xmax_ditaurecotau1tau2deltaptmasscrdplot = ditaurecotau1tau2deltaptmass_crd_plot->GetXaxis()->GetXmax();   ///This line gets the maximum along the x-axis for this second distribution.

  TH1F *ditaurecotau1tau2deltaptmass_crd_plot_copy = new TH1F("ditaurecotau1tau2deltaptmass_crd_plot_copy","ditaurecotau1tau2deltaptmass_crd_plot_copy", nbins_ditaurecotau1tau2deltaptmasscrdplot,xmin_ditaurecotau1tau2deltaptmasscrdplot,xmax_ditaurecotau1tau2deltaptmasscrdplot);
  for(Int_t i=1;i<=nbins_ditaurecotau1tau2deltaptmasscrdplot;i++){
    ditaurecotau1tau2deltaptmass_crd_plot_copy->SetBinContent(i,ditaurecotau1tau2deltaptmass_crd_plot->GetBinContent(i)*ditaurecotau1tau2deltaptmass_crd_plot->GetBinWidth(i));
  }   ///This filling line makes the copy for you to manipulate subsequently of the second distribution.

  ditaurecotau1tau2deltaptmass_crd_plot_copy->Sumw2();
  
  Double_t xbins_mass[6] = {150, 200, 250, 300, 350, 500}; ///This line defines the bin edges.  We started at 150 since you had little-to-no statistics before this.

  ///---handling binning---///
  /// Rebins the first distribution from CR B.  Sumw2 is to appropriately handle errors.
  ditaurecotau1tau2deltaptmass_crb_plot_copy->Rebin(5,"ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned",xbins_mass);

  /// Rebins the second distribution from CR D.  Sumw2 is to appropriately handle errors.
  ditaurecotau1tau2deltaptmass_crd_plot_copy->Rebin(5,"ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned",xbins_mass);

  Double_t yield_from_b = ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned->Integral();
  ///---normalizing both histograms to unity---///
  Double_t scale_crd = (1 / (ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->Integral())) * yield_from_b;
  Double_t scale_crb = 1 / yield_from_b;
  
  ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->Scale(scale_crd);
  Double_t scale_crd2 = (1 / (ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->Integral()));
  ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->Scale(scale_crd2);
  ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned->Scale(scale_crb);

  ///---style parameters---///
  ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->GetXaxis()->SetTitle("");
  ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->GetYaxis()->SetTitle("a.u.");
  ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->GetYaxis()->SetTitleSize(0.04);
  ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->SetTitle("");
  ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->Draw("ep");  ///when you put "c" in the argument of this, that says you want a curve drawn between the points.  "e" is for error bars.  "p" is for points.
  ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->SetLineColor(8);
  
  ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned->Draw("ep same");
  Double_t ymin = 0.000001;
  Double_t ymax = ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->GetMaximum() * 2;
  ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned->SetLineColor(9);
  ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->GetYaxis()->SetRangeUser(ymin,ymax);

  //legend
  Double_t xl1=0.62, yl1=0.12, xl2=0.89, yl2=0.29;
  TLegend *leg = new TLegend(xl1,yl1,xl2,yl2);
  leg->AddEntry(ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned,"m(#tau_{1}, #tau_{2}, #Deltap_{T}): emulated (shape from Region D (LS))","f");
  //leg->AddEntry(ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned,"m(#tau_{1}, #tau_{2}, E^{miss}_{T}): emulated (shape from Region D (LS))","f");
  leg->AddEntry(ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned,"m(#tau_{1}, #tau_{2}, #Deltap_{T}): raw (Region B (OS))","f");
  //leg->AddEntry(ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned,"m(#tau_{1}, #tau_{2}, E^{miss}_{T}): raw (Region B (OS))","f");
  leg->Draw();
  pad1->SetLogy();
  
  //defining the second pad
  c1->cd();
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.35);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx();
  pad2->Draw();
  pad2->cd();
  
  //defining the ratio plot
  TH1F *rat = (TH1F*)ditaurecotau1tau2deltaptmass_crd_plot_copy_rebinned->Clone("rat");
  rat->SetStats(0);  //parameter for the error bars
  rat->Divide(ditaurecotau1tau2deltaptmass_crb_plot_copy_rebinned);
  rat->SetLineColor(1);
  rat->SetMinimum(0.0);
  rat->SetMaximum(5.2);

  //x-axis
  rat->GetXaxis()->SetTitle("m(#tau_{1}, #tau_{2}, #Deltap_{T}) [GeV]");
  //rat->GetXaxis()->SetTitle("m(#tau_{1}, #tau_{2}, E^{miss}_{T}) [GeV]");
  rat->GetXaxis()->SetTitleSize(0.085);
  rat->GetXaxis()->SetTitleOffset(1.1);
  rat->GetXaxis()->SetLabelFont(43);
  rat->GetXaxis()->SetLabelSize(20);
  rat->GetXaxis()->SetLabelOffset(0.02);

  rat->SetTitle(" ");

  //y-axis
  rat->GetYaxis()->SetTitle("(Emulated / Raw)");
  rat->GetYaxis()->SetTitleSize(26);
  rat->GetYaxis()->SetTitleOffset(1.5);
  rat->GetYaxis()->SetTitleFont(43);
  rat->GetYaxis()->SetLabelFont(43);
  rat->GetYaxis()->SetLabelSize(20);

  rat->SetMarkerStyle(7);
  rat->SetMarkerColor(7);
  rat->Draw("p");

  const Int_t n = 15000;
  Double_t x[n], y[n];
  for (Int_t i=0;i<n;i++) {
    x[i] = i*0.1;
    y[i] = 1;
  }
  TGraph *gr = new TGraph(n,x,y);
  gr->SetLineColor(1);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(4);
  gr->Draw("same");

  c1->Update();
}
