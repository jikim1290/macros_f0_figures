TH1D* Rebinning(TH1D* href, TH1D* htar){
 TH1D* hout = (TH1D*)href->Clone();
 hout->Reset();
 double cntl;
 double unc;

 for(int j=2;j<href->GetNbinsX();j++){
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


void Fig6_DR_pt_kstar(){

 TFile* fin_pPb5TeV_phiRef = new TFile("./data/HEPData-ins1418181-v1-root.root","read");

 const int nmult = 5;
 const double multmin[nmult] = {
	 0, 20, 40, 60, 80 };
 const double multmax[nmult] = {
	20, 40, 60, 80, 100 };

 const double dNeta[nmult] = {
        35.417500, 23.12, 15.89, 9.63, 4.13 };

 double RealIncMultSysUpErr[nmult]={
        0.5, 0.5, 0.4, 0.2, 0.1};
 double RealIncMultSysDownErr[nmult]={
        0.5, 0.5, 0.4, 0.2, 0.1};

 double RealIncMultSysErr[nmult];
 for(int i=0;i<nmult;i++){ RealIncMultSysErr[i] = ( RealIncMultSysUpErr[i]+RealIncMultSysDownErr[i] )/2.0; }


 TH1F* hPionCentral[nmult];
 TH1F* hPionStat[nmult];
 TH1F* hPionSyst[nmult];

 TDirectoryFile* dir;
 for(int i=0;i<5;i++){
	dir = (TDirectoryFile*)fin_pPb5TeV_phiRef->GetDirectory(Form("Table %d",3+i));
	hPionCentral[i] = (TH1F*)dir->Get(Form("Hist1D_y%d",1));
	hPionStat[i] = (TH1F*)dir->Get(Form("Hist1D_y%d_e1",1));
	hPionSyst[i] = (TH1F*)dir->Get(Form("Hist1D_y%d_e2",1));
 }
 dir = (TDirectoryFile*)fin_pPb5TeV_phiRef->GetDirectory(Form("Table %d",2));
 TH1F* hPionCentralMB = (TH1F*)dir->Get(Form("Hist1D_y%d",1));
 TH1F* hPionStatMB = (TH1F*)dir->Get(Form("Hist1D_y%d_e1",1));
 TH1F* hPionSystMB = (TH1F*)dir->Get(Form("Hist1D_y%d_e2",1));

 TH1D* hPionPtStat[nmult];
 TH1D* hPionPtSyst[nmult];
 for(int i=0;i<nmult;i++){
	hPionPtStat[i] = (TH1D*)hPionCentral[i]->Clone();
	hPionPtSyst[i] = (TH1D*)hPionCentral[i]->Clone();

	for(int j=0;j<hPionPtStat[i]->GetNbinsX();j++){
		hPionPtStat[i]->SetBinError( j+1, hPionStat[i]->GetBinContent(j+1) );
		hPionPtSyst[i]->SetBinError( j+1, hPionSyst[i]->GetBinContent(j+1) );
	}
 }

 TH1D* hPionPtStatMB;
 TH1D* hPionPtSystMB;
 hPionPtStatMB = (TH1D*)hPionCentralMB->Clone();
 hPionPtSystMB = (TH1D*)hPionCentralMB->Clone();
 for(int j=0;j<hPionCentralMB->GetNbinsX();j++){
	hPionPtStatMB->SetBinError( j+1, hPionStatMB->GetBinContent(j+1) );
	hPionPtSystMB->SetBinError( j+1, hPionSystMB->GetBinContent(j+1) );
 }


 const int nmult_thiswork = 5;

 double multmin_this[nmult_thiswork] = {0,  20, 40,  60,   0};
 double multmax_this[nmult_thiswork] = {20, 40, 60, 100, 100};

 const int index_merge_min[nmult_thiswork] = {
	0, 1, 2, 3, 0 };
 const int index_merge_max[nmult_thiswork] = {
	1, 2, 3, 4, 5 };

 TH1D* hPionPtStat_MultRebinned[nmult_thiswork];
 TH1D* hPionPtSyst_MultRebinned[nmult_thiswork];


 for(int i=0;i<nmult_thiswork-2;i++){
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
 hPionPtStat_MultRebinned[3] = (TH1D*)hPionPtStatMB->Clone();
 hPionPtSyst_MultRebinned[3] = (TH1D*)hPionPtSystMB->Clone();
 for(int i=0;i<hPionPtStat_MultRebinned[3]->GetNbinsX();i++){
	hPionPtStat_MultRebinned[3]->SetBinContent( i+1, ( hPionPtStat[3]->GetBinContent(i+1) + hPionPtStat[4]->GetBinContent(i+1) )/2.0 );
	hPionPtStat_MultRebinned[3]->SetBinError( i+1, sqrt( pow( hPionPtStat[3]->GetBinError(i+1)/2.0,2 ) + pow( hPionPtStat[4]->GetBinError(i+1)/2.0,2) ) );	

	hPionPtSyst_MultRebinned[3]->SetBinContent( i+1, ( hPionPtSyst[3]->GetBinContent(i+1) + hPionPtSyst[4]->GetBinContent(i+1) )/2.0 );
        hPionPtSyst_MultRebinned[3]->SetBinError( i+1, sqrt( pow( hPionPtSyst[3]->GetBinError(i+1)/2.0,2 ) + pow( hPionPtSyst[4]->GetBinError(i+1)/2.0,2) ) );

 }

 hPionPtStat_MultRebinned[4] = (TH1D*)hPionPtStatMB->Clone();
 hPionPtSyst_MultRebinned[4] = (TH1D*)hPionPtSystMB->Clone();
 hPionPtSyst_MultRebinned[4]->SetFillStyle(0);



 TFile* fin_pPb5TeV_f0 = new TFile("./data/TotalYieldOut.root","read");
 TH1D* hF0PtStat[nmult_thiswork];
 TH1D* hF0PtSyst[nmult_thiswork];
 for(int i=0;i<nmult_thiswork;i++){
	hF0PtStat[i] = (TH1D*)fin_pPb5TeV_f0->Get(Form("hYStat_%d",i));
	hF0PtSyst[i] = (TH1D*)fin_pPb5TeV_f0->Get(Form("hYSystUn_%d",i));	

	hF0PtSyst[i]->SetLineWidth(1);
	hF0PtSyst[i]->SetFillStyle(0);
	hF0PtSyst[i]->SetLineColor(i+1);
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

 hPionPtStat_MultRebinned[0]->Draw("same");
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

 }
 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetTitle("2f_{0}/(K^{*0} + #bar{K^{*0})}");
 hF0_pion_ratio_pT_syst[0]->SetMaximum(2);

 hF0_pion_ratio_pT_syst[0]->SetTitle("");
 hF0_pion_ratio_pT_syst[0]->GetXaxis()->SetTitleOffset(0.85);
 hF0_pion_ratio_pT_syst[0]->GetXaxis()->SetTitleSize(0.06);
 hF0_pion_ratio_pT_syst[0]->GetXaxis()->SetLabelSize(0.05);

 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetTitleSize(28);
 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetTitleFont(43);
 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetTitleOffset(0.8);
 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetLabelSize(0.24);
 hF0_pion_ratio_pT_syst[0]->GetYaxis()->SetLabelFont(43);

 TCanvas* c = new TCanvas("c","c",800,600);
 gPad->SetLeftMargin(0.13);
 gPad->SetBottomMargin(0.13);
 gStyle->SetOptStat(0);

 TLegend* leg = new TLegend(0.149,0.61,0.689,0.92);
 leg->SetLineWidth(0.0); leg->SetFillStyle(0);
 leg->SetTextSize(24);
 leg->SetTextFont(43);

 leg->AddEntry( (TObject*)0, "#scale[1.2]{ALICE Preliminary}", "");
 leg->AddEntry( (TObject*)0, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV, -0.5<y<0", "");
 leg->AddEntry( hF0_pion_ratio_pT_stat[0], "0#font[122]{-}20%", "p");
 leg->AddEntry( hF0_pion_ratio_pT_stat[3], "60#font[122]{-}100%", "p");

// leg->AddEntry( (TObject*)0, "Uncertainties: stat.(bars), syst.(boxes)", "");

 hF0_pion_ratio_pT_stat[0]->SetMarkerSize(2);
 hF0_pion_ratio_pT_stat[3]->SetMarkerSize(2);


 hF0_pion_ratio_pT_syst[0]->SetMaximum(1.3); 
 hF0_pion_ratio_pT_syst[0]->SetMinimum(0.15);
 hF0_pion_ratio_pT_syst[0]->Draw("e2");
 hF0_pion_ratio_pT_syst[3]->Draw("same,e2");
 hF0_pion_ratio_pT_stat[0]->Draw("same");
 hF0_pion_ratio_pT_stat[3]->Draw("same");

 leg->Draw();

// c->SaveAs("f0_kstar_ratio_pt.pdf");

 TFile* fin_pion_ratio = new TFile("./data/fout_kstar_ratio_pT.root","read");
 TH1D* hRatioStat[nmult_thiswork];
 TH1D* hRatioSyst[nmult_thiswork];
 for(int i=0;i<nmult_thiswork;i++){
	hRatioStat[i] = (TH1D*)fin_pion_ratio->Get(Form("kstarRatio_total_stat_%d",i));
	hRatioSyst[i] = (TH1D*)fin_pion_ratio->Get(Form("kstarRatio_total_syst_%d",i));
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

 hRatioSyst[0]->GetYaxis()->SetTitleSize(28);
 hRatioSyst[0]->GetYaxis()->SetTitleFont(43);
 hRatioSyst[0]->GetYaxis()->SetTitleOffset(1.3);
 hRatioSyst[0]->GetYaxis()->SetLabelSize(24);
 hRatioSyst[0]->GetYaxis()->SetLabelFont(43);


 pad1->cd();
 hRatioSyst[0]->SetMarkerSize(2);
 hRatioStat[3]->SetMarkerSize(2);
 hRatioSyst[0]->Draw("e2");
 hRatioSyst[3]->Draw("same,e2");
 hRatioStat[0]->Draw("same");
 hRatioStat[3]->Draw("same");
 leg->Draw();


 TLegend* legu = new TLegend(0.002,0.5,0.647,0.6);
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

 cRatio->SaveAs("figs/Fig6_DR_pt_kstar.pdf");
 cRatio->SaveAs("figs/Fig6_DR_pt_kstar.eps");


/*
 TFile* fout_piondr = new TFile("kstar_double_ratio_out.root","recreate");
 hDoubleRatioStat->SetName("hDoubleRatioKstarStat");
 hDoubleRatioSyst->SetName("hDoubleRatioKstarSyst");
 hDoubleRatioStat->Write();
 hDoubleRatioSyst->Write();
*/
}
