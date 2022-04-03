TH1D* Rebinning(TH1D* href, TH1D* htar){
 TH1D* hout = (TH1D*)href->Clone();
 hout->Reset();
 double cntl;
 double unc;

 for(int j=1;j<href->GetNbinsX();j++){
	cntl = 0.0;
	unc = 0.0;
	for(int k=0;k<htar->GetNbinsX();k++){
		if( href->GetXaxis()->GetBinLowEdge( j+1 ) > htar->GetXaxis()->GetBinUpEdge( k+1 ) ) continue;
		if( href->GetXaxis()->GetBinUpEdge( j+1 ) < htar->GetXaxis()->GetBinLowEdge( k+1 ) ) continue;
		if( href->GetXaxis()->GetBinLowEdge( j+1 ) >= htar->GetXaxis()->GetBinLowEdge( k+1 ) &&
		    href->GetXaxis()->GetBinLowEdge( j+1 ) <= htar->GetXaxis()->GetBinUpEdge( k+1 ) ){
			cntl += htar->GetBinContent(k+1) * ( htar->GetXaxis()->GetBinUpEdge( k+1 ) - href->GetXaxis()->GetBinLowEdge( j+1 ) );
			unc += pow( htar->GetBinError(k+1) * ( htar->GetXaxis()->GetBinUpEdge( k+1 ) - href->GetXaxis()->GetBinLowEdge( j+1 ) ),2 );
		} else if(
		    href->GetXaxis()->GetBinUpEdge( j+1 ) >= htar->GetXaxis()->GetBinLowEdge( k+1 ) &&
		    href->GetXaxis()->GetBinUpEdge( j+1 ) <= htar->GetXaxis()->GetBinUpEdge( k+1 ) ){
			cntl += htar->GetBinContent(k+1) * ( href->GetXaxis()->GetBinUpEdge( j+1 ) - htar->GetXaxis()->GetBinLowEdge( k+1 ) );
			unc += pow( htar->GetBinError(k+1) * ( href->GetXaxis()->GetBinUpEdge( j+1 ) - htar->GetXaxis()->GetBinLowEdge( k+1 ) ),2 );
		} else{
			cntl += htar->GetBinContent(k+1) * htar->GetXaxis()->GetBinWidth(k+1);
			unc += pow( htar->GetBinError(k+1) * htar->GetXaxis()->GetBinWidth(k+1),2 );
		}
	}
	hout->SetBinContent( j+1, cntl / hout->GetXaxis()->GetBinWidth(j+1) );
	hout->SetBinError( j+1, sqrt( unc / hout->GetXaxis()->GetBinWidth(j+1) ) );
 }
 return hout;
}



void Fig5_DR_pt_pion(){
 TFile* fin_pPb5TeV_pionRef = new TFile("./data/HEPData-ins1415274-v1-root.root","read");

 const int nmult = 7;
 const double multmin[nmult] = {
	0, 5,  10, 20, 40, 60, 80 };
 const double multmax[nmult] = {
	5, 10, 20, 40, 60, 80, 100 };

 const double dNeta[nmult] = {
        44.96, 36.05, 30.33, 23.12, 15.89, 9.63, 4.13 };

 double RealIncMultSysUpErr[nmult]={
        1.0, 0.8, 0.7, 0.5, 0.4, 0.2, 0.1};
 double RealIncMultSysDownErr[nmult]={
        1.0, 0.8, 0.7, 0.5, 0.4, 0.2, 0.1};

 double RealIncMultSysErr[nmult];
 for(int i=0;i<nmult;i++){ RealIncMultSysErr[i] = ( RealIncMultSysUpErr[i]+RealIncMultSysDownErr[i] )/2.0; }


 TH1F* hPionCentral[nmult];
 TH1F* hPionStat[nmult];
 TH1F* hPionSyst[nmult];

 TDirectoryFile* dir;
 dir = (TDirectoryFile*)fin_pPb5TeV_pionRef->GetDirectory("Table 1");

 for(int i=0;i<7;i++){
	hPionCentral[i] = (TH1F*)dir->Get(Form("Hist1D_y%d",i+1));
	hPionStat[i] = (TH1F*)dir->Get(Form("Hist1D_y%d_e1",i+1));
	hPionSyst[i] = (TH1F*)dir->Get(Form("Hist1D_y%d_e3",i+1));
 }
/*
 dir = (TDirectoryFile*)fin_pPb5TeV_pionRef->GetDirectory("Table 2");
 for(int i=0;i<3;i++){
	hPionCentral[i+4] = (TH1F*)dir->Get(Form("Hist1D_y%d",i+1));
        hPionStat[i+4] = (TH1F*)dir->Get(Form("Hist1D_y%d_e1",i+1));
        hPionSyst[i+4] = (TH1F*)dir->Get(Form("Hist1D_y%d_e2",i+1));
 }
*/
 TH1D* hPionPtStat[nmult];
 TH1D* hPionPtSyst[nmult];
 for(int i=0;i<nmult;i++){
	for(int j=0;j<hPionCentral[i]->GetNbinsX();j++){
		hPionCentral[i]->SetBinContent( j+1, hPionCentral[i]->GetBinContent(j+1) * 2.0 * TMath::Pi() * hPionCentral[i]->GetBinCenter(j+1) );
		hPionStat[i]->SetBinContent( j+1, hPionStat[i]->GetBinContent(j+1) * 2.0 * TMath::Pi() * hPionCentral[i]->GetBinCenter(j+1) );
		hPionSyst[i]->SetBinContent( j+1, hPionSyst[i]->GetBinContent(j+1) * 2.0 * TMath::Pi() * hPionCentral[i]->GetBinCenter(j+1) );
	}

	hPionPtStat[i] = (TH1D*)hPionCentral[i]->Clone();
	hPionPtSyst[i] = (TH1D*)hPionCentral[i]->Clone();

	for(int j=0;j<hPionPtStat[i]->GetNbinsX();j++){
		hPionPtStat[i]->SetBinError( j+1, hPionStat[i]->GetBinContent(j+1) );
		hPionPtSyst[i]->SetBinError( j+1, hPionSyst[i]->GetBinContent(j+1) );
	}
 }


 const int nmult_thiswork = 5;

 double multmin_this[nmult_thiswork] = {0,  20, 40,  60,   0};
 double multmax_this[nmult_thiswork] = {20, 40, 60, 100, 100};

 const int index_merge_min[nmult_thiswork] = {
	0, 3, 4, 5, 0 };
 const int index_merge_max[nmult_thiswork] = {
	3, 4, 5, 7, 7 };

 TH1D* hPionPtStat_MultRebinned[nmult_thiswork];
 TH1D* hPionPtSyst_MultRebinned[nmult_thiswork];

 for(int i=0;i<nmult_thiswork;i++){
	for(int j=index_merge_min[i];j<index_merge_max[i];j++){
		if( j==index_merge_min[i] ){
			hPionPtStat_MultRebinned[i] = (TH1D*)hPionPtStat[j]->Clone();
			hPionPtSyst_MultRebinned[i] = (TH1D*)hPionPtSyst[j]->Clone();
		}
		if( j==index_merge_min[i] ){
			hPionPtStat_MultRebinned[i]->Scale( multmax[j]-multmin[j] );
			hPionPtSyst_MultRebinned[i]->Scale( multmax[j]-multmin[j] );
		}

		if( j>index_merge_min[i] ){
			hPionPtStat_MultRebinned[i]->Add( hPionPtStat[j], multmax[j]-multmin[j] );
			hPionPtSyst_MultRebinned[i]->Add( hPionPtSyst[j], multmax[j]-multmin[j] );
		}
	}
	hPionPtStat_MultRebinned[i]->Scale( 1.0/(multmax_this[i]-multmin_this[i]) );
	hPionPtSyst_MultRebinned[i]->Scale( 1.0/(multmax_this[i]-multmin_this[i]) );

	hPionPtSyst_MultRebinned[i]->SetFillStyle(0);
 }

 TFile* fin_pPb5TeV_f0 = new TFile("./data/TotalYieldOut.root","read");
 TH1D* hF0PtStat[nmult_thiswork];
 TH1D* hF0PtSyst[nmult_thiswork];
 for(int i=0;i<nmult_thiswork;i++){
	hF0PtStat[i] = (TH1D*)fin_pPb5TeV_f0->Get(Form("hYStat_%d",i));
	hF0PtSyst[i] = (TH1D*)fin_pPb5TeV_f0->Get(Form("hYSystUn_%d",i));
 

 }

 TH1D* hPionPtStat_FullRebinned[nmult_thiswork];
 TH1D* hPionPtSyst_FullRebinned[nmult_thiswork];


 for(int i=0;i<nmult_thiswork;i++){
	hPionPtStat_FullRebinned[i] = (TH1D*)Rebinning( hF0PtStat[i], hPionPtStat_MultRebinned[i] );
	hPionPtStat_FullRebinned[i]->GetYaxis()->UnZoom();
	hPionPtStat_FullRebinned[i]->SetMarkerColor(1);
	hPionPtStat_FullRebinned[i]->SetMarkerStyle(22);

	hPionPtSyst_FullRebinned[i] = (TH1D*)Rebinning( hF0PtSyst[i], hPionPtSyst_MultRebinned[i] );

 }



 hPionPtStat_MultRebinned[0]->Draw("");
 hPionPtStat_FullRebinned[0]->Draw("same");


 TH1D* hF0_pion_ratio_pT_stat[nmult_thiswork];
 TH1D* hF0_pion_ratio_pT_syst[nmult_thiswork];

 for(int i=0;i<nmult_thiswork;i++){
	hF0_pion_ratio_pT_stat[i] = (TH1D*)hF0PtStat[i]->Clone();
	hF0_pion_ratio_pT_stat[i]->Divide( hPionPtStat_FullRebinned[i] );
	hF0_pion_ratio_pT_stat[i]->GetYaxis()->UnZoom();
	hF0_pion_ratio_pT_stat[i]->SetMarkerStyle(20+i);
	hF0_pion_ratio_pT_stat[i]->SetMarkerColor(i+1);
	hF0_pion_ratio_pT_stat[i]->SetLineColor(i+1);
	

	hF0_pion_ratio_pT_syst[i] = (TH1D*)hF0PtSyst[i]->Clone();
        hF0_pion_ratio_pT_syst[i]->Divide( hPionPtSyst_FullRebinned[i] );
        hF0_pion_ratio_pT_syst[i]->GetYaxis()->UnZoom();
        hF0_pion_ratio_pT_syst[i]->SetMarkerStyle(20+i);
        hF0_pion_ratio_pT_syst[i]->SetMarkerColor(i+1);
        hF0_pion_ratio_pT_syst[i]->SetLineColor(i+1);
	hF0_pion_ratio_pT_syst[i]->SetFillStyle(0);

	for(int p=0;p<hF0_pion_ratio_pT_stat[i]->GetNbinsX();p++){
		hF0_pion_ratio_pT_stat[i]->SetBinContent( p+1, hF0_pion_ratio_pT_stat[i]->GetBinContent(p+1)*2.0 );
		hF0_pion_ratio_pT_stat[i]->SetBinError( p+1, hF0_pion_ratio_pT_stat[i]->GetBinError(p+1)*2.0 );

		hF0_pion_ratio_pT_syst[i]->SetBinContent( p+1, hF0_pion_ratio_pT_syst[i]->GetBinContent(p+1)*2.0 );
		hF0_pion_ratio_pT_syst[i]->SetBinError( p+1, hF0_pion_ratio_pT_syst[i]->GetBinError(p+1)*2.0 );
	}
 }
 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetTitle("f0/pi");
// hF0_pion_ratio_pT_syst[0]->SetMaximum(0.015);
 hF0_pion_ratio_pT_syst[0]->Draw("e2");
 hF0_pion_ratio_pT_syst[3]->Draw("same,e2");

 hF0_pion_ratio_pT_stat[0]->Draw("same");
 hF0_pion_ratio_pT_stat[3]->Draw("same");


 TH1D* hF0_pion_ratio_pT_stat_ratio = (TH1D*)hF0_pion_ratio_pT_stat[0]->Clone();
 hF0_pion_ratio_pT_stat_ratio->Divide( hF0_pion_ratio_pT_stat[3] );
 hF0_pion_ratio_pT_stat_ratio->Draw();




 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetTitle("2f_{0}/(#pi^{+}+#pi^{-})");
// hF0_pion_ratio_pT_syst[0]->SetMaximum(0.2);

 hF0_pion_ratio_pT_syst[0]->SetTitle("");
 hF0_pion_ratio_pT_syst[0]->GetXaxis()->SetTitleOffset(0.85);
 hF0_pion_ratio_pT_syst[0]->GetXaxis()->SetTitleSize(0.06);
 hF0_pion_ratio_pT_syst[0]->GetXaxis()->SetLabelSize(0.05);

 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetTitleSize(0.07);
 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetTitleOffset(0.8);
 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetLabelSize(0.05);

 TCanvas* c = new TCanvas("c","c",800,600);
 gPad->SetLeftMargin(0.13);
 gPad->SetBottomMargin(0.13);
 gStyle->SetOptStat(0);

 TLegend* leg = new TLegend(0.14, 0.610, 0.650, 0.92);
 leg->SetLineWidth(0.0); leg->SetFillStyle(0);
 leg->SetTextSize(24);
 leg->SetTextFont(43);

 leg->AddEntry( (TObject*)0, "#scale[1.2]{ALICE Preliminary}", "");
 leg->AddEntry( (TObject*)0, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV, -0.5<y<0", "");
 leg->AddEntry( hF0_pion_ratio_pT_stat[0], "0#font[122]{-}20%", "p");
 leg->AddEntry( hF0_pion_ratio_pT_stat[3], "60#font[122]{-}100%", "p");
 //leg->AddEntry( (TObject*)0, "Uncertainties: stat.(bars), syst.(boxes)", "");

 hF0_pion_ratio_pT_stat[0]->SetMarkerSize(2);
 hF0_pion_ratio_pT_stat[3]->SetMarkerSize(2);

 hF0_pion_ratio_pT_syst[0]->Draw("e2");
 hF0_pion_ratio_pT_syst[3]->Draw("same,e2");
 hF0_pion_ratio_pT_stat[0]->Draw("same");
 hF0_pion_ratio_pT_stat[3]->Draw("same");

 leg->Draw();

// c->SaveAs("f0_pion_ratio_pt.pdf");


 TFile* fin_pion_ratio = new TFile("./data/fout_pion_ratio_pT.root","read");
 TH1D* hRatioStat[nmult_thiswork];
 TH1D* hRatioSyst[nmult_thiswork];
 for(int i=0;i<nmult_thiswork;i++){
        hRatioStat[i] = (TH1D*)fin_pion_ratio->Get(Form("pionRatio_total_stat_%d",i));
        hRatioSyst[i] = (TH1D*)fin_pion_ratio->Get(Form("pionRatio_total_syst_%d",i));

	hRatioStat[i]->Scale(2.0);
	hRatioSyst[i]->Scale(2.0);
 }


 TH1D* hDoubleRatioStat = (TH1D*)hF0_pion_ratio_pT_stat[0]->Clone();
 hDoubleRatioStat->Divide( hF0_pion_ratio_pT_stat[3] );

 TH1D* hDoubleRatioSyst = (TH1D*)hF0_pion_ratio_pT_syst[0]->Clone();
 hDoubleRatioSyst->Divide( hF0_pion_ratio_pT_syst[3] );


 TCanvas* cRatio = new TCanvas("cRatio","cRatio",800,700);
 TPad* pad1 = new TPad("p1","p1",0.0,0.35,1.0,1.0);
 TPad* pad2 = new TPad("p2","p2",0.0,0.0,1.0,0.35);
 pad1->SetLeftMargin(0.13);
 pad1->SetBottomMargin(0.0);
 pad1->SetTopMargin(0.03);
 pad1->SetRightMargin(0.03);
 pad2->SetTopMargin(0.0);
 pad2->SetLeftMargin(0.13);
 pad2->SetBottomMargin(0.3);
 pad2->SetRightMargin(0.03);
 pad1->SetTicks();
 pad2->SetTicks();

 cRatio->cd(); pad1->Draw();
 cRatio->cd(); pad2->Draw();

 pad1->cd();
 hRatioSyst[0]->SetMarkerSize(2);
 hRatioStat[3]->SetMarkerSize(2);
 hRatioSyst[0]->GetYaxis()->SetTitleSize(28);
 hRatioSyst[0]->GetYaxis()->SetTitleFont(43);
 hRatioSyst[0]->GetYaxis()->SetTitleOffset(1.3);
 hRatioSyst[0]->GetYaxis()->SetLabelSize(24);
 hRatioSyst[0]->GetYaxis()->SetLabelFont(43);
 hRatioSyst[0]->GetYaxis()->SetTitle("2f_{0}/(#pi^{+}+#pi^{-})");
 hRatioSyst[0]->SetMinimum(0.005);
 hRatioSyst[0]->GetYaxis()->SetNdivisions(505);
 hRatioSyst[0]->Draw("e2");
 hRatioSyst[3]->Draw("same,e2");
 hRatioStat[0]->Draw("same");
 hRatioStat[3]->Draw("same");
 leg->Draw();

 TLegend* legu = new TLegend(0.356,0.006,0.917,0.131);
 legu->SetLineWidth(0.0); legu->SetFillStyle(0);
 legu->SetTextSize(20);
 legu->SetTextFont(43);
 legu->AddEntry( (TObject*)0, "Uncertainties: stat.(bars), syst.(boxes)", "");
 legu->Draw();


 pad2->cd();
 hDoubleRatioStat->SetMaximum(1.6);
 hDoubleRatioStat->SetMinimum(0.4);
 hDoubleRatioStat->SetTitle("");
 hDoubleRatioStat->GetXaxis()->SetTitleSize(28);
 hDoubleRatioStat->GetXaxis()->SetTitleFont(43);
 hDoubleRatioStat->GetXaxis()->SetLabelSize(24);
 hDoubleRatioStat->GetXaxis()->SetLabelFont(43);
 hDoubleRatioStat->GetXaxis()->SetTitleOffset(3.0);
 hDoubleRatioStat->GetYaxis()->SetTitle("#frac{(0#font[122]{-}20%)}{(60#font[122]{-}100%)}");
 hDoubleRatioStat->GetYaxis()->CenterTitle();
 hDoubleRatioStat->GetYaxis()->SetTitleSize(28);
 hDoubleRatioStat->GetYaxis()->SetTitleFont(43);
 hDoubleRatioStat->GetYaxis()->SetTitleOffset(1.3);
 hDoubleRatioStat->GetYaxis()->SetNdivisions(505);
 hDoubleRatioStat->GetYaxis()->SetLabelSize(24);
 hDoubleRatioStat->GetYaxis()->SetLabelFont(43);
 hDoubleRatioStat->Draw();
 hDoubleRatioSyst->Draw("same,e2");

 TLine* lui = new TLine(0,1,8,1);
 lui->SetLineStyle(4);
 lui->SetLineWidth(3);
 lui->Draw();

 cRatio->SaveAs("figs/Fig5_DR_pt_pion.pdf");
 cRatio->SaveAs("figs/Fig5_DR_pt_pion.eps");

/*
 TFile* fout_piondr = new TFile("pion_double_ratio_out.root","recreate");
 hDoubleRatioStat->SetName("hDoubleRatioPionStat");
 hDoubleRatioSyst->SetName("hDoubleRatioPionSyst");
 hDoubleRatioStat->Write();
 hDoubleRatioSyst->Write();
*/



}
