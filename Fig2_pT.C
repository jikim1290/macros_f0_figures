int GetSerialColors(int colorbins = 1){
    const int NRGBs = 5;
    double stops[NRGBs] = {0.00, 0.34, 0.61, 0.84, 1.00};
    double red[NRGBs] = {0.00, 0.00, 0.87, 0.9 * 1.00, 0.51};
    double green[NRGBs] = {0.00, 0.81, 0.9 * 1.00, 0.20, 0.00};
    double blue[NRGBs] = {0.51, 0.9 * 1.00, 0.12, 0.00, 0.00};
    int FIf = TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue,
                                                 colorbins);
    return FIf;
}


void Fig2_pT(){
 gStyle->SetTextFont(42);

 TFile* fin = new TFile("./data/TotalYieldOut.root","read");

 const int nmult = 5;

 const char multname[nmult][100] = {
	"0#font[122]{-}20%",
	"20#font[122]{-}40%",
	"40#font[122]{-}60%",
	"60#font[122]{-}100%",
	"NSD"
 };
 TH1D* hPt_Stat[nmult];
 TH1D* hPt_Syst[nmult];
 TH1D* hPt_Uncorr_Syst[nmult];

 TH1D* hPt_R_Stat[nmult];
 TH1D* hPt_R_Syst[nmult];


 int RainbowColor[nmult];
 int sysColorPallet = GetSerialColors(nmult);
 for(int i=0;i<nmult-1;i++){
        RainbowColor[i] = sysColorPallet + nmult - i - 1;
 }
 RainbowColor[nmult-1] = 1;
 int MarkerStyle[nmult] = {
	21, 22, 23, 29 ,20 };

 for(int i=0;i<nmult;i++){
	hPt_Stat[i] = (TH1D*)fin->Get(Form("hYStat_%d",i));
	hPt_Syst[i] = (TH1D*)fin->Get(Form("hYSyst_%d",i));
	hPt_Uncorr_Syst[i] = (TH1D*)fin->Get(Form("hYSystUn_%d",i));

	hPt_R_Stat[i] = (TH1D*)fin->Get(Form("hYRStat_%d",i));
	hPt_R_Syst[i] = (TH1D*)fin->Get(Form("hYRSyst_%d",i));

	hPt_Stat[i]->SetTitle("");
	hPt_Stat[i]->GetYaxis()->SetTitleSize(32);
	hPt_Stat[i]->GetYaxis()->SetTitleFont(43);
	hPt_Stat[i]->GetYaxis()->SetLabelSize(26);
	hPt_Stat[i]->GetYaxis()->SetLabelFont(43);
	hPt_Stat[i]->GetYaxis()->SetTitleOffset(1.6);
	hPt_Stat[i]->GetYaxis()->SetTitle("1/#it{N}_{evt} d^{2}#it{N}/(dyd#it{p}_{T}) [(GeV/#it{c}^{-1})]");

	hPt_Stat[i]->GetXaxis()->SetTitleSize(32);
	hPt_Stat[i]->GetXaxis()->SetTitleFont(43);
	hPt_Stat[i]->GetXaxis()->SetLabelSize(26);
	hPt_Stat[i]->GetXaxis()->SetLabelFont(43);
	hPt_Stat[i]->GetXaxis()->SetTitleOffset(1.3);
	hPt_Stat[i]->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");

	hPt_R_Stat[i]->GetXaxis()->SetLabelSize(0.05*0.88/0.35);
	hPt_R_Stat[i]->GetXaxis()->SetTitleSize(0.05*0.88/0.35);
	hPt_R_Stat[i]->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
	hPt_R_Stat[i]->GetXaxis()->SetTitleOffset(0.9*1.12);	

	hPt_R_Stat[i]->GetYaxis()->CenterTitle();

	hPt_R_Stat[i]->GetYaxis()->SetNdivisions(505);
	hPt_R_Stat[i]->GetYaxis()->SetTitleOffset(0.6);
	hPt_Stat[i]->GetXaxis()->SetRangeUser(0,9);
	hPt_R_Stat[i]->GetXaxis()->SetRangeUser(0,9);

	hPt_Stat[i]->SetLineColor( RainbowColor[i] );
	hPt_Syst[i]->SetLineColor( RainbowColor[i] );
	hPt_Uncorr_Syst[i]->SetLineColor( RainbowColor[i] );
	hPt_R_Stat[i]->SetLineColor( RainbowColor[i] );
	hPt_R_Syst[i]->SetLineColor( RainbowColor[i] );

	hPt_Stat[i]->SetMarkerColor( RainbowColor[i] );
	hPt_Syst[i]->SetMarkerColor( RainbowColor[i] );
	hPt_Uncorr_Syst[i]->SetMarkerColor( RainbowColor[i] );
	hPt_R_Stat[i]->SetMarkerColor( RainbowColor[i] );
	hPt_R_Syst[i]->SetMarkerColor( RainbowColor[i] );

	hPt_Stat[i]->SetMarkerStyle( MarkerStyle[i] );
	hPt_Syst[i]->SetMarkerStyle( MarkerStyle[i] );
	hPt_Uncorr_Syst[i]->SetMarkerStyle( MarkerStyle[i] );
	hPt_R_Stat[i]->SetMarkerStyle( MarkerStyle[i] );
	hPt_R_Syst[i]->SetMarkerStyle( MarkerStyle[i] );
 }
 TH1D* hPt_Stat_inc = (TH1D*)hPt_Stat[4]->Clone();
 TH1D* hPt_Syst_inc = (TH1D*)hPt_Syst[4]->Clone();


 TLegend* leg_inc = new TLegend(0.35, 0.7, 0.945, 0.940);
 leg_inc->SetFillStyle(0);
 leg_inc->SetMargin(0.15);
 leg_inc->SetTextSize(23);
 leg_inc->SetTextFont(43);
 leg_inc->SetLineWidth(0.0);

 leg_inc->AddEntry( (TObject*)0, "#scale[1.2]{ALICE Preliminary}", "");
 //leg_inc->AddEntry( hPt_Stat_inc, "ALICE, p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV", "p");
 leg_inc->AddEntry( hPt_Stat_inc, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV", "p");
 leg_inc->AddEntry( (TObject*)0, "-0.5<y<0, NSD", "");
 leg_inc->AddEntry( (TObject*)0, "f_{0}(980)#rightarrow#pi^{+}#pi^{-}", "");
 leg_inc->AddEntry( (TObject*)0, "Uncertainties: stat.(bars), syst.(boxes)", "");

 TCanvas* c = new TCanvas("c","c",700,800);
 c->SetTopMargin(0.03);
 c->SetRightMargin(0.03);
 c->SetLeftMargin(0.15);
 c->SetBottomMargin(0.12);
 c->SetLogy();
 c->SetTicks(1);

 //hPt_Stat_inc->GetYaxis()->SetTitleSize( 0.8*0.06 );
 //hPt_Stat_inc->GetXaxis()->SetTitleSize( 0.8*0.06 );
 //hPt_Stat_inc->GetYaxis()->SetLabelSize( 0.8*0.05 );
 //hPt_Stat_inc->GetXaxis()->SetLabelSize( 0.8*0.05 );
 //hPt_Stat_inc->GetXaxis()->SetTitleOffset( 1.15 );
 hPt_Stat_inc->Draw("ex0");
 hPt_Syst_inc->Draw("same,e2");

 leg_inc->Draw();
 c->SaveAs("figs/Fig2_pt_inc.pdf");
 c->SaveAs("figs/Fig2_pt_inc.eps");

 //return;

 TPad* pad1 = new TPad("p1","p1",0.0, 0.35, 1, 1);
 TPad* pad2 = new TPad("p2","p2",0.0, 0.0,  1, 0.35);

 pad1->SetLogy();
 pad1->SetTopMargin( 0.03*1.0/0.65 );
 pad1->SetRightMargin(0.03);
 pad1->SetBottomMargin(0.0);
 pad1->SetLeftMargin(0.15);

 pad2->SetLogy();
 pad2->SetTopMargin(0.0);
 pad2->SetRightMargin(0.03);
 pad2->SetLeftMargin(0.15);
 pad2->SetBottomMargin( 0.12*1.0/0.35);

 pad1->SetTicks(1); pad2->SetTicks(1);

 c->cd(); pad1->Draw();
 c->cd(); pad2->Draw();

 pad1->cd();
 for(int i=0;i<nmult;i++){
	hPt_Stat[i]->Scale( pow( 2, nmult-i-1 ) );
	hPt_Syst[i]->Scale( pow( 2, nmult-i-1 ) );
 }
 hPt_Stat[4]->Scale(0.25);
 hPt_Syst[4]->Scale(0.25);

 //hPt_Stat[0]->GetYaxis()->SetTitleSize( 1*0.06 );
 //hPt_Stat[0]->GetXaxis()->SetTitleSize( 1*0.06 );
 //hPt_Stat[0]->GetYaxis()->SetLabelSize( 1*0.05 );
 //hPt_Stat[0]->GetXaxis()->SetLabelSize( 1*0.05 );
 //hPt_Stat[0]->GetYaxis()->SetTitleOffset( 1.15 );
 hPt_Stat[0]->SetMinimum(2e-5);
 hPt_Stat[0]->Draw("ex0");


 for(int i=0;i<nmult;i++){	
	hPt_Stat[i]->Draw("same,ex0");
	hPt_Syst[i]->Draw("same,e2");
 }

 pad2->cd(); 

 hPt_R_Stat[0]->SetMinimum(2e-1);
 hPt_R_Stat[0]->GetYaxis()->SetTitleSize( 32 );
 hPt_R_Stat[0]->GetXaxis()->SetTitleSize( 32 );
 hPt_R_Stat[0]->GetYaxis()->SetTitleFont( 43 );
 hPt_R_Stat[0]->GetXaxis()->SetTitleFont( 43 );
 hPt_R_Stat[0]->GetYaxis()->SetLabelSize( 26 );
 hPt_R_Stat[0]->GetXaxis()->SetLabelSize( 26 );
 hPt_R_Stat[0]->GetYaxis()->SetLabelFont( 43 );
 hPt_R_Stat[0]->GetXaxis()->SetLabelFont( 43 );
 hPt_R_Stat[0]->GetYaxis()->SetTitleOffset( 1.5 );
 hPt_R_Stat[0]->GetXaxis()->SetTitleOffset( 3.5 );
 hPt_R_Stat[0]->Draw("ex0");


 for(int i=0;i<nmult-1;i++){
	hPt_R_Stat[i]->Draw("same,ex0");
	hPt_R_Syst[i]->Draw("same,e2");
 }


 TLegend* leg_mult = new TLegend(0.332, 0.73, 0.945, 0.930);
 leg_mult->SetFillStyle(0);
 leg_mult->SetTextSize(23);
 leg_mult->SetTextFont(43);
 leg_mult->SetLineWidth(0.0);

 leg_mult->AddEntry( (TObject*)0, "#scale[1.2]{ALICE Preliminary}", "");
 //leg_mult->AddEntry( (TObject*)0, "ALICE, p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV", "");
 leg_mult->AddEntry( (TObject*)0, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV", "");
 leg_mult->AddEntry( (TObject*)0, "-0.5<y<0, f_{0}(980)#rightarrow#pi^{+}#pi^{-}", "");


 TLegend* leg_v0a = new TLegend(0.174,0.022,0.602,0.275);
 leg_v0a->SetFillStyle(0);
 leg_v0a->SetNColumns(2);
 leg_v0a->SetLineWidth(0.0);
 leg_v0a->SetHeader("V0A multiplicity (Pb side)");
 leg_v0a->SetTextSize(20);
 leg_v0a->SetTextFont(43);
 for(int i=0;i<nmult-1;i++){
	leg_v0a->AddEntry( hPt_R_Stat[i], Form("%s (#times2^{%d})",multname[i],nmult-i-1), "pl");
	if( i==0 ) leg_v0a->AddEntry( (TObject*)0, "", "");
 }
 leg_v0a->AddEntry( hPt_R_Stat[4], Form("%s (#times2^{%d})",multname[4],-2), "pl");

// leg_mult->AddEntry( (TObject*)0, "Uncertainties: stat.(bars), syst.(boxes)", "");

 pad1->cd();
 leg_mult->Draw();
 leg_v0a->Draw();

 c->SaveAs("figs/Fig2_pt_all.pdf");
 c->SaveAs("figs/Fig2_pt_all.eps");
}
