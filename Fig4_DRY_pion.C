
TGraphErrors* GetDR( TGraphErrors* g1, TGraphErrors* g2, int np=4 ){
 TGraphErrors* gr = new TGraphErrors();
 for(int i=0;i<np;i++){
	gr->SetPoint( i, pow( g1->GetX()[i], 1.0/3.0 ),
		( g1->GetY()[i]/g2->GetY()[i] ) / ( g1->GetY()[np-1]/g2->GetY()[np-1] )  );
	gr->SetPointError( i, (1.0/3.0) * pow( g1->GetX()[i], -2.0/3.0 ) * g1->GetErrorX(i),
		( g1->GetY()[i]/g2->GetY()[i] ) / ( g1->GetY()[np-1]/g2->GetY()[np-1] ) * sqrt(
		pow( g1->GetErrorY(i)   /g1->GetY()[i],2 ) +
		pow( g1->GetErrorY(np-1)/g1->GetY()[np-1],2 ) +
		pow( g2->GetErrorY(i)   /g2->GetY()[i],2 ) +
		pow( g2->GetErrorY(np-1)/g2->GetY()[np-1],2 ) ) );
 }

 return gr;
}



void Fig4_DRY_pion(){
 TFile* fkstar_total = new TFile("./data/CompareKSTAR_out.root","read");
 TFile* fpion_total = new TFile("./data/ComparePion_out.root","read");
 TFile* fphi_total = new TFile("./data/ComparePhi_out.root","read");

 TGraphErrors* gF0Stat = (TGraphErrors*)fphi_total->Get("gF0HadronStat");
 TGraphErrors* gF0Syst = (TGraphErrors*)fphi_total->Get("gF0HadronUnCorrSys");

 TGraphErrors* gKstarStat = (TGraphErrors*)fkstar_total->Get("gKSTARHadronStat");
 TGraphErrors* gKstarSyst = (TGraphErrors*)fkstar_total->Get("gKSTARHadronSys");

 TGraphErrors* gPhiStat = (TGraphErrors*)fphi_total->Get("gPhiHadronStat");
 TGraphErrors* gPhiSyst = (TGraphErrors*)fphi_total->Get("gPhiHadronSys");

 TGraphErrors* gPionStat = (TGraphErrors*)fpion_total->Get("gPIONHadronStat");
 TGraphErrors* gPionSyst = (TGraphErrors*)fpion_total->Get("gPIONHadronSys");

 TGraphErrors* gDR_F0_stat = (TGraphErrors*)GetDR( gF0Stat, gPionStat );
 TGraphErrors* gDR_F0_syst = (TGraphErrors*)GetDR( gF0Syst, gPionSyst );

 TGraphErrors* gDR_Kstar_stat = (TGraphErrors*)GetDR( gKstarStat, gPionStat );
 TGraphErrors* gDR_Kstar_syst = (TGraphErrors*)GetDR( gKstarSyst, gPionSyst );
 
 TGraphErrors* gDR_Phi_stat = (TGraphErrors*)GetDR( gPhiStat, gPionStat );
 TGraphErrors* gDR_Phi_syst = (TGraphErrors*)GetDR( gPhiSyst, gPionSyst );


 TCanvas* c = new TCanvas("c","c",700,600);
 gPad->SetLeftMargin(0.14);
 gPad->SetBottomMargin(0.14);

 gPad->SetRightMargin(0.03);
 gPad->SetTopMargin(0.03);

 gPad->SetTicks();


 gDR_Phi_stat->SetMaximum(1.5);
 gDR_Phi_stat->SetMinimum(0.5);

 gDR_Phi_stat->GetYaxis()->SetTitle(" (h/#pi)/(h/#pi)_{LM}");
 gDR_Phi_stat->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#eta#GT^{1/3}_{|#eta|<0.5}");
 gDR_Phi_stat->GetYaxis()->SetTitleSize(0.06);
 gDR_Phi_stat->GetXaxis()->SetTitleSize(0.06);
 gDR_Phi_stat->GetYaxis()->SetLabelSize(0.05);
 gDR_Phi_stat->GetXaxis()->SetLabelSize(0.05);
 gDR_Phi_stat->GetYaxis()->SetTitleOffset(0.9);
 gDR_Phi_stat->GetXaxis()->SetTitleOffset(0.9);
 gDR_Phi_stat->GetXaxis()->SetNdivisions(505);
 gDR_Phi_stat->GetYaxis()->SetNdivisions(505);


 gDR_Phi_stat->SetMarkerStyle(21);
 gDR_Phi_stat->SetMarkerColor(kBlue-3);
 gDR_Phi_stat->SetMarkerSize(1.5);
 gDR_Phi_stat->SetLineColor(kBlue-3);
 gDR_Phi_syst->SetLineColor(kBlue-3);

 gDR_Kstar_stat->SetMarkerStyle(22);
 gDR_Kstar_stat->SetMarkerColor(1);
 gDR_Kstar_stat->SetMarkerSize(1.5);
 gDR_Kstar_stat->SetLineColor(1);
 gDR_Kstar_syst->SetLineColor(1);

 gDR_F0_stat->SetMarkerStyle(20);
 gDR_F0_stat->SetMarkerColor(kRed-4);
 gDR_F0_stat->SetMarkerSize(1.5);
 gDR_F0_stat->SetLineColor(kRed-4);
 gDR_F0_syst->SetLineColor(kRed-4);

 gDR_Phi_stat->Draw("AP"); 
 gDR_Kstar_stat->Draw("P");
 gDR_F0_stat->Draw("P");


 gDR_Phi_syst->SetFillStyle(0);
 gDR_Kstar_syst->SetFillStyle(0);
 gDR_F0_syst->SetFillStyle(0);

 gDR_Phi_syst->Draw("e2");
 gDR_Kstar_syst->Draw("e2");
 gDR_F0_syst->Draw("e2");

 TLegend* leg = new TLegend(0.161,0.728,0.703,0.939);
 leg->SetFillColorAlpha(0,0);
 leg->SetLineWidth(0.0);
 
 leg->AddEntry( (TObject*)0, "ALICE, p#font[122]{-}Pb #sqrt{#it{s}_{NN}} = 5.02 TeV", "");
 leg->AddEntry( gDR_Phi_stat, "#phi (EPJC 76 (2016) 245)", "pl");
 leg->AddEntry( gDR_Kstar_stat, "K^{*0} (EPJC 76 (2016) 245)", "pl");
 leg->AddEntry( gDR_F0_stat, "f_{0}, Preliminary", "pl");
 leg->Draw();

 TLegend* legu = new TLegend(0.027,0.168,0.727,0.259);
 legu->SetFillColorAlpha(0,0);
 legu->SetLineWidth(0.0);
 legu->AddEntry( (TObject*)0, "Uncertainties: stat.(bars), syst.(boxes)", "");
 legu->Draw();

 c->SaveAs("figs/Fig4_dr_pion.pdf");


/* RHO
 TGraphErrors* gRhoStat = new TGraphErrors();
 TGraphErrors* gRhoSyst = new TGraphErrors();

 double YRho_cntl[4] = {
	1.565, 1.068, 0.823, 0.404 };
 double YRho_stat[4] = {
	0.014, 0.009, 0.007, 0.005 };
 double YRho_syst[4] = {
	0.171, 0.119, 0.095, 0.050 };

 for(int i=0;i<4;i++){
	gRhoStat->SetPoint(i, gPionStat->GetX()[i], YRho_cntl[i] );
	gRhoStat->SetPointError(i, gPionStat->GetErrorX(i), YRho_stat[i] );

        gRhoSyst->SetPoint(i, gPionSyst->GetX()[i], YRho_cntl[i] );
        gRhoSyst->SetPointError(i, gPionSyst->GetErrorX(i), YRho_syst[i] );
 }

 TGraphErrors* gDR_Rho_stat = (TGraphErrors*)GetDR( gRhoStat, gPionStat );
 TGraphErrors* gDR_Rho_syst = (TGraphErrors*)GetDR( gRhoSyst, gPionSyst );


 gDR_Rho_stat->SetMarkerStyle(23);
 gDR_Rho_stat->SetMarkerColor(kSpring-7);
 gDR_Rho_stat->SetMarkerSize(1.5);
 gDR_Rho_stat->SetLineColor(kSpring-7);
 gDR_Rho_syst->SetLineColor(kSpring-7);
 gDR_Rho_syst->SetFillStyle(0);
 
 gDR_Rho_stat->Draw("P");
 gDR_Rho_syst->Draw("e2");

 leg->AddEntry( gDR_Rho_stat, "#rho, Preliminary", "pl");
 leg->Draw();

 c->SaveAs("yield_dr_pion_addrho.pdf");
*/





/* EPOS
 TFile* fepos_urqmd_on = new TFile("EPOS3_UrQMDOn.root","read");
 TH1D* hevents = (TH1D*)fepos_urqmd_on->Get("hNevents");

 TH1D* hEtaCent[4];
 TH1D* hYPhiCent[4];
 TH1D* hYKstarCent[4];
 TH1D* hYPionCent[4];

 double dndeta[4];
 double dndetaerr[4];

 double dndy_Phi_cntl[4]={0};
 double dndy_Kstar_cntl[4]={0};
 double dndy_Pion_cntl[4]={0};

 double dndy_Phi_unc[4]={0};
 double dndy_Kstar_unc[4]={0};
 double dndy_Pion_unc[4]={0};

 double SRatio_Phi_cntl[4];
 double SRatio_Kstar_cntl[4];

 double SRatio_Phi_unc[4];
 double SRatio_Kstar_unc[4];

 double DRatio_Phi_cntl[4];
 double DRatio_Kstar_cntl[4];

 double DRatio_Phi_unc[4];
 double DRatio_Kstar_unc[4];

 for(int i=0;i<4;i++){
	hYPhiCent[i] = (TH1D*)fepos_urqmd_on->Get(Form("hYPhiCent%d",i));
	hYKstarCent[i] = (TH1D*)fepos_urqmd_on->Get(Form("hYKStarCent%d",i));
	hYPionCent[i] = (TH1D*)fepos_urqmd_on->Get(Form("hYPionCent%d",i));

	hYPhiCent[i]->Scale( 1.0,"width");
	hYKstarCent[i]->Scale( 1.0,"width");
	hYPionCent[i]->Scale( 1.0,"width");

	hEtaCent[i] = (TH1D*)fepos_urqmd_on->Get(Form("hEtaCent%d",i));
	if( i!= 3 ) hEtaCent[i]->Scale( 1.0/(hevents->GetBinContent(1)*0.2), "width" );
	else{ hEtaCent[i]->Scale( 1.0/(hevents->GetBinContent(1)*0.4), "width"); }

	dndeta[i] = 0.0;
	dndetaerr[i] = 0.0;
	for(int j=0;j<hEtaCent[i]->GetNbinsX();j++){
		if( fabs( hEtaCent[i]->GetBinCenter(j+1) ) > 0.5 ) continue;
		dndeta[i] += hEtaCent[i]->GetBinContent(j+1)*hEtaCent[i]->GetBinWidth(j+1);
		dndetaerr[i] += pow( hEtaCent[i]->GetBinError(j+1)*hEtaCent[i]->GetBinWidth(j+1),2 );
	}
	dndetaerr[i] = sqrt( dndetaerr[i] );

	dndy_Phi_cntl[i] = hYPhiCent[i]->IntegralAndError(
		hYPhiCent[i]->GetXaxis()->FindBin(-0.465), hYPhiCent[i]->GetXaxis()->FindBin(0.035),
		dndy_Phi_unc[i] );
	
        dndy_Kstar_cntl[i] = hYKstarCent[i]->IntegralAndError(
                hYKstarCent[i]->GetXaxis()->FindBin(-0.465), hYKstarCent[i]->GetXaxis()->FindBin(0.035),
                dndy_Kstar_unc[i] );

        dndy_Pion_cntl[i] = hYPionCent[i]->IntegralAndError(
                hYPionCent[i]->GetXaxis()->FindBin(-0.465), hYPionCent[i]->GetXaxis()->FindBin(0.035),
                dndy_Pion_unc[i] );


	SRatio_Phi_cntl[i] = dndy_Phi_cntl[i] / dndy_Pion_cntl[i];
	SRatio_Kstar_cntl[i] = dndy_Kstar_cntl[i] / dndy_Pion_cntl[i];
	
	SRatio_Phi_unc[i] = SRatio_Phi_cntl[i]*sqrt( pow( dndy_Phi_unc[i]/dndy_Phi_cntl[i],2 ) + pow( dndy_Pion_unc[i]/dndy_Pion_cntl[i],2 ) );
	SRatio_Kstar_unc[i] = SRatio_Kstar_cntl[i]*sqrt( pow( dndy_Kstar_unc[i]/dndy_Kstar_cntl[i],2 ) + pow( dndy_Pion_unc[i]/dndy_Pion_cntl[i],2 ) );
 }

 for(int i=0;i<4;i++){
	DRatio_Phi_cntl[i] = SRatio_Phi_cntl[i] / SRatio_Phi_cntl[3];
	DRatio_Kstar_cntl[i] = SRatio_Kstar_cntl[i] / SRatio_Kstar_cntl[3];

	DRatio_Phi_unc[i] = DRatio_Phi_cntl[i]*sqrt( pow( SRatio_Phi_unc[i]/SRatio_Phi_cntl[i],2) + pow( SRatio_Phi_unc[3]/SRatio_Phi_cntl[3],2) );
	DRatio_Kstar_unc[i] = DRatio_Kstar_cntl[i]*sqrt( pow( SRatio_Kstar_unc[i]/SRatio_Kstar_cntl[i],2) + pow( SRatio_Kstar_unc[3]/SRatio_Kstar_cntl[3],2 ) );
 }


 TGraphErrors* gDR_Phi_epos3_urqmd_on = new TGraphErrors();
 TGraphErrors* gDR_Kstar_epos3_urqmd_on = new TGraphErrors();

 for(int i=0;i<4;i++){
	gDR_Phi_epos3_urqmd_on->SetPoint( i, pow(dndeta[i],1.0/3.0) , DRatio_Phi_cntl[i] );
	gDR_Phi_epos3_urqmd_on->SetPoint( i, pow(dndeta[i],1.0/3.0) , DRatio_Phi_unc[i] );
	gDR_Kstar_epos3_urqmd_on->SetPoint( i, pow(dndeta[i],1.0/3.0), DRatio_Kstar_cntl[i] );
 }
 gDR_Phi_epos3_urqmd_on->SetFillStyle(1);
 gDR_Kstar_epos3_urqmd_on->SetFillStyle(1);
 gDR_Phi_epos3_urqmd_on->SetFillColor(1);
 gDR_Kstar_epos3_urqmd_on->SetFillColor(2);


 gDR_Phi_epos3_urqmd_on->Draw("e3");
 gDR_Kstar_epos3_urqmd_on->Draw("e3");








 TFile* fepos_urqmd_off = new TFile("EPOS3_UrQMDOff.root","read");
 hevents = (TH1D*)fepos_urqmd_off->Get("hNevents");

 for(int i=0;i<4;i++){
        hYPhiCent[i] = (TH1D*)fepos_urqmd_off->Get(Form("hYPhiCent%d",i));
        hYKstarCent[i] = (TH1D*)fepos_urqmd_off->Get(Form("hYKStarCent%d",i));
        hYPionCent[i] = (TH1D*)fepos_urqmd_off->Get(Form("hYPionCent%d",i));

        hYPhiCent[i]->Scale( 1.0,"width");
        hYKstarCent[i]->Scale( 1.0,"width");
        hYPionCent[i]->Scale( 1.0,"width");

        hEtaCent[i] = (TH1D*)fepos_urqmd_off->Get(Form("hEtaCent%d",i));
        if( i!= 3 ) hEtaCent[i]->Scale( 1.0/(hevents->GetBinContent(1)*0.2), "width" );
        else{ hEtaCent[i]->Scale( 1.0/(hevents->GetBinContent(1)*0.4), "width"); }

        dndeta[i] = 0.0;
	dndetaerr[i] = 0.0;
        for(int j=0;j<hEtaCent[i]->GetNbinsX();j++){
                if( fabs( hEtaCent[i]->GetBinCenter(j+1) ) > 0.5 ) continue;
                dndeta[i] += hEtaCent[i]->GetBinContent(j+1)*hEtaCent[i]->GetBinWidth(j+1);
		dndetaerr[i] += pow( hEtaCent[i]->GetBinError(j+1)*hEtaCent[i]->GetBinWidth(j+1),2 );
        }
	dndetaerr[i] = sqrt( dndetaerr[i] );

        dndy_Phi_cntl[i] = hYPhiCent[i]->IntegralAndError(
                hYPhiCent[i]->GetXaxis()->FindBin(-0.465), hYPhiCent[i]->GetXaxis()->FindBin(0.035),
                dndy_Phi_unc[i] );

        dndy_Kstar_cntl[i] = hYKstarCent[i]->IntegralAndError(
                hYKstarCent[i]->GetXaxis()->FindBin(-0.465), hYKstarCent[i]->GetXaxis()->FindBin(0.035),
                dndy_Kstar_unc[i] );

        dndy_Pion_cntl[i] = hYPionCent[i]->IntegralAndError(
                hYPionCent[i]->GetXaxis()->FindBin(-0.465), hYPionCent[i]->GetXaxis()->FindBin(0.035),
                dndy_Pion_unc[i] );


        SRatio_Phi_cntl[i] = dndy_Phi_cntl[i] / dndy_Pion_cntl[i];
        SRatio_Kstar_cntl[i] = dndy_Kstar_cntl[i] / dndy_Pion_cntl[i];

        SRatio_Phi_unc[i] = SRatio_Phi_cntl[i]*sqrt( pow( dndy_Phi_unc[i]/dndy_Phi_cntl[i],2 ) + pow( dndy_Pion_unc[i]/dndy_Pion_cntl[i],2 ) );
        SRatio_Kstar_unc[i] = SRatio_Kstar_cntl[i]*sqrt( pow( dndy_Kstar_unc[i]/dndy_Kstar_cntl[i],2 ) + pow( dndy_Pion_unc[i]/dndy_Pion_cntl[i],2 ) );
        cout << dndeta[i] << endl;
 }

 for(int i=0;i<4;i++){
        DRatio_Phi_cntl[i] = SRatio_Phi_cntl[i] / SRatio_Phi_cntl[3];
        DRatio_Kstar_cntl[i] = SRatio_Kstar_cntl[i] / SRatio_Kstar_cntl[3];

        DRatio_Phi_unc[i] = DRatio_Phi_cntl[i]*sqrt( pow( SRatio_Phi_unc[i]/SRatio_Phi_cntl[i],2) + pow( SRatio_Phi_unc[3]/SRatio_Phi_cntl[3],2) );
        DRatio_Kstar_unc[i] = DRatio_Kstar_cntl[i]*sqrt( pow( SRatio_Kstar_unc[i]/SRatio_Kstar_cntl[i],2) + pow( SRatio_Kstar_unc[3]/SRatio_Kstar_cntl[3],2 ) );

        cout << DRatio_Kstar_cntl[i] << ", " << DRatio_Phi_unc[i] << endl;
 }


 TGraphErrors* gDR_Phi_epos3_urqmd_off = new TGraphErrors();
 TGraphErrors* gDR_Kstar_epos3_urqmd_off = new TGraphErrors();

 for(int i=0;i<4;i++){
        gDR_Phi_epos3_urqmd_off->SetPoint( i, pow(dndeta[i],1.0/3.0) , DRatio_Phi_cntl[i] );
        gDR_Kstar_epos3_urqmd_off->SetPoint( i, pow(dndeta[i],1.0/3.0), DRatio_Kstar_cntl[i] );
	gDR_Phi_epos3_urqmd_off->SetPointError( i, 
 }
 gDR_Phi_epos3_urqmd_off->SetFillStyle(1);
 gDR_Kstar_epos3_urqmd_off->SetFillStyle(1);
 gDR_Phi_epos3_urqmd_off->SetFillColor(3);
 gDR_Kstar_epos3_urqmd_off->SetFillColor(4);


 gDR_Phi_epos3_urqmd_off->Draw("e3");
// gDR_Kstar_epos3_urqmd_off->Draw("e3");


*/
}
