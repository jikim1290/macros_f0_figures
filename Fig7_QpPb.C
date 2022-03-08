{
 TFile* fpPb5_stat = new TFile("./data/TotalYieldOut_ZNA.root","read");
 TFile* fpPb5_syst = new TFile("./data/TotalSyst_ZNA.root","read");
 TFile* fRpPb_ch = new TFile("./data/HEPData-ins1335350-v1-root.root","read");

 const int nmult_pPb5 = 4;

 double multmin[nmult_pPb5] = {0, 20, 40, 60 };
 double multmax[nmult_pPb5] = {20,40, 60, 80 };

 TH1D* h_pt_pPb5_stat[nmult_pPb5];
 TH1D* h_pt_pPb5_syst[nmult_pPb5];
 TH1D* h_pt_pPb5_syst_uncorr[nmult_pPb5];

 TF1* f_pt_pPb5_fit[nmult_pPb5];

 double syst_corr_unc_pPb5[nmult_pPb5];

 for(int i=0;i<nmult_pPb5;i++){
	h_pt_pPb5_stat[i] = (TH1D*)fpPb5_stat->Get(Form("hYStat_%d",i));
	h_pt_pPb5_syst[i] = (TH1D*)fpPb5_syst->Get(Form("hSyst_%d",i))->Clone(0);
	h_pt_pPb5_syst_uncorr[i] = (TH1D*)fpPb5_syst->Get(Form("hSystUnCorr_%d",i))->Clone(0);

	f_pt_pPb5_fit[i] = (TF1*)fpPb5_stat->Get(Form("fun_%d",i));

	syst_corr_unc_pPb5[i] = sqrt( pow( h_pt_pPb5_syst[i]->GetBinContent(1),2 )  - pow( h_pt_pPb5_syst_uncorr[i]->GetBinContent(1),2 ) );

	for(int j=0;j<h_pt_pPb5_syst_uncorr[i]->GetNbinsX();j++){
		h_pt_pPb5_syst[i]->SetBinError( j+1, h_pt_pPb5_stat[i]->GetBinContent(j+1)*h_pt_pPb5_syst[i]->GetBinContent(j+1) );
		h_pt_pPb5_syst[i]->SetBinContent( j+1, h_pt_pPb5_stat[i]->GetBinContent(j+1) );

		h_pt_pPb5_syst_uncorr[i]->SetBinError( j+1, h_pt_pPb5_stat[i]->GetBinContent(j+1)*h_pt_pPb5_syst_uncorr[i]->GetBinContent(j+1) );
		h_pt_pPb5_syst_uncorr[i]->SetBinContent( j+1, h_pt_pPb5_stat[i]->GetBinContent(j+1) );
	}

	if( h_pt_pPb5_stat[i]->GetFunction("f1") ) h_pt_pPb5_stat[i]->GetFunction("f1")->Delete();
	if( h_pt_pPb5_syst[i]->GetFunction("f1") ) h_pt_pPb5_syst[i]->GetFunction("f1")->Delete();
	if( h_pt_pPb5_syst_uncorr[i]->GetFunction("f1") ) h_pt_pPb5_syst_uncorr[i]->GetFunction("f1")->Delete();
 }
 TFile* fpp5 = new TFile("./data/prel_finalWsys.root","read");
 TFile* fpp5_v1 = new TFile("./data/f0_pp_5TeV_merged.root","read");

 TH1D* h_pt_pp5_trackcut = (TH1D*)fpp5->Get("trackcuts");
 TH1D* h_pt_pp5_function = (TH1D*)fpp5->Get("function");

 const double syst_corr_unc_pp5 = sqrt( pow( h_pt_pp5_trackcut->GetBinContent(1),2 ) + pow( h_pt_pp5_function->GetBinContent(1),2 ) );

 TH1D* h_pt_pp5_stat = (TH1D*)fpp5_v1->Get("href_merged_stat");
 TH1D* h_pt_pp5_syst = (TH1D*)fpp5->Get("sum2")->Clone(0);
 TH1D* h_pt_pp5_syst_uncorr = (TH1D*)fpp5->Get("sum2");

 for(int i=0;i<h_pt_pp5_syst_uncorr->GetNbinsX();i++){
	h_pt_pp5_syst_uncorr->SetBinContent( i+1,
		sqrt( pow( h_pt_pp5_syst_uncorr->GetBinContent(i+1),2 ) - pow( syst_corr_unc_pp5,2 ) ) );

	h_pt_pp5_syst_uncorr->SetBinError( i+1, h_pt_pp5_stat->GetBinContent(i+1)*h_pt_pp5_syst_uncorr->GetBinContent(i+1) );
	h_pt_pp5_syst_uncorr->SetBinContent( i+1, h_pt_pp5_stat->GetBinContent(i+1) );


	h_pt_pp5_syst->SetBinError( i+1, h_pt_pp5_stat->GetBinContent(i+1)*h_pt_pp5_syst->GetBinContent(i+1) );
	h_pt_pp5_syst->SetBinContent( i+1, h_pt_pp5_stat->GetBinContent(i+1) );

 }

// TH1D* h_pt_pp5_syst = (TH1D*)fpp5_v1->Get("href_merged_syst");
// TH1D* h_pt_pp5_syst_uncorr = (TH1D*)fpp5_v1->Get("href_merged_syst");


// TH1D* h_pt_pp5_stat_rebin = (TH1D*)h_pt_pp5_stat->Rebin( h_pt_pPb5_stat[0]->GetNbinsX(), "Rebined_pp5_stat", pT );
// TH1D* h_pt_pp5_syst_rebin = (TH1D*)h_pt_pp5_stat->Rebin( h_pt_pPb5_stat[0]->GetNbinsX(), "Rebined_pp5_syst", pT );
// TH1D* h_pt_pp5_syst_uncorr_rebin = (TH1D*)h_pt_pp5_syst_uncorr->Rebin( h_pt_pPb5_stat[0]->GetNbinsX(), "Rebined_pp5_syst_uncorr", pT );

 TH1D* h_pt_pp5_stat_rebin = (TH1D*)h_pt_pp5_stat->Clone();
 TH1D* h_pt_pp5_syst_rebin = (TH1D*)h_pt_pp5_syst->Clone();
 TH1D* h_pt_pp5_syst_uncorr_rebin = (TH1D*)h_pt_pp5_syst_uncorr->Clone();
/*
//**
 h_pt_pp5_stat_rebin->SetBinContent( 1, ( h_pt_pp5_stat->GetBinContent(2) + h_pt_pp5_stat->GetBinContent(3) )/2.0 );
 h_pt_pp5_stat_rebin->SetBinError( 1, sqrt( pow( h_pt_pp5_stat->GetBinError(2),2 ) + pow( h_pt_pp5_stat->GetBinError(3),2 ) ) );

 h_pt_pp5_stat_rebin->SetBinContent( 2, ( h_pt_pp5_stat->GetBinContent(4) + h_pt_pp5_stat->GetBinContent(5) )/2.0 );
 h_pt_pp5_stat_rebin->SetBinError( 2, sqrt( pow( h_pt_pp5_stat->GetBinError(4),2 ) + pow( h_pt_pp5_stat->GetBinError(5),2 ) ) );

 h_pt_pp5_stat_rebin->SetBinContent( 3, ( h_pt_pp5_stat->GetBinContent(6) + h_pt_pp5_stat->GetBinContent(7) )/2.0 );
 h_pt_pp5_stat_rebin->SetBinError( 3, sqrt( pow( h_pt_pp5_stat->GetBinError(6),2 ) + pow( h_pt_pp5_stat->GetBinError(7),2 ) ) );

 h_pt_pp5_stat_rebin->SetBinContent( 4, ( h_pt_pp5_stat->GetBinContent(8) + h_pt_pp5_stat->GetBinContent(9) )/2.0 );
 h_pt_pp5_stat_rebin->SetBinError( 4, sqrt( pow( h_pt_pp5_stat->GetBinError(8),2 ) + pow( h_pt_pp5_stat->GetBinError(9),2 ) ) );

 h_pt_pp5_stat_rebin->SetBinContent( 5, h_pt_pp5_stat->GetBinContent(10) );
 h_pt_pp5_stat_rebin->SetBinError( 5, h_pt_pp5_stat->GetBinError(10) );

 h_pt_pp5_stat_rebin->SetBinContent( 6, h_pt_pp5_stat->GetBinContent(11) );
 h_pt_pp5_stat_rebin->SetBinError( 6, h_pt_pp5_stat->GetBinError(11) );

 h_pt_pp5_stat_rebin->SetBinContent( 7, ( h_pt_pp5_stat->GetBinContent(12) + h_pt_pp5_stat->GetBinContent(13) )/2.0 );
 h_pt_pp5_stat_rebin->SetBinError( 7, sqrt( pow( h_pt_pp5_stat->GetBinError(12),2 ) + pow( h_pt_pp5_stat->GetBinError(13),2 ) ) );
//**
*/

/*
//**
 h_pt_pp5_syst_rebin->SetBinContent( 1, ( h_pt_pp5_syst->GetBinContent(2) + h_pt_pp5_syst->GetBinContent(3) )/2.0 );
 h_pt_pp5_syst_rebin->SetBinError( 1, sqrt( pow( h_pt_pp5_syst->GetBinError(2),2 ) + pow( h_pt_pp5_syst->GetBinError(3),2 ) ) );

 h_pt_pp5_syst_rebin->SetBinContent( 2, ( h_pt_pp5_syst->GetBinContent(4) + h_pt_pp5_syst->GetBinContent(5) )/2.0 );
 h_pt_pp5_syst_rebin->SetBinError( 2, sqrt( pow( h_pt_pp5_syst->GetBinError(4),2 ) + pow( h_pt_pp5_syst->GetBinError(5),2 ) ) );

 h_pt_pp5_syst_rebin->SetBinContent( 3, ( h_pt_pp5_syst->GetBinContent(6) + h_pt_pp5_syst->GetBinContent(7) )/2.0 );
 h_pt_pp5_syst_rebin->SetBinError( 3, sqrt( pow( h_pt_pp5_syst->GetBinError(6),2 ) + pow( h_pt_pp5_syst->GetBinError(7),2 ) ) );

 h_pt_pp5_syst_rebin->SetBinContent( 4, ( h_pt_pp5_syst->GetBinContent(8) + h_pt_pp5_syst->GetBinContent(9) )/2.0 );
 h_pt_pp5_syst_rebin->SetBinError( 4, sqrt( pow( h_pt_pp5_syst->GetBinError(8),2 ) + pow( h_pt_pp5_syst->GetBinError(9),2 ) ) );

 h_pt_pp5_syst_rebin->SetBinContent( 5, h_pt_pp5_syst->GetBinContent(10) );
 h_pt_pp5_syst_rebin->SetBinError( 5, h_pt_pp5_syst->GetBinError(10) );

 h_pt_pp5_syst_rebin->SetBinContent( 6, h_pt_pp5_syst->GetBinContent(11) );
 h_pt_pp5_syst_rebin->SetBinError( 6, h_pt_pp5_syst->GetBinError(11) );

 h_pt_pp5_syst_rebin->SetBinContent( 7, ( h_pt_pp5_syst->GetBinContent(12) + h_pt_pp5_syst->GetBinContent(13) )/2.0 );
 h_pt_pp5_syst_rebin->SetBinError( 7, sqrt( pow( h_pt_pp5_syst->GetBinError(12),2 ) + pow( h_pt_pp5_syst->GetBinError(13),2 ) ) );
//**


//**
 h_pt_pp5_syst_uncorr_rebin->SetBinContent( 1, ( h_pt_pp5_syst_uncorr->GetBinContent(2) + h_pt_pp5_syst_uncorr->GetBinContent(3) )/2.0 );
 h_pt_pp5_syst_uncorr_rebin->SetBinError( 1, sqrt( pow( h_pt_pp5_syst_uncorr->GetBinError(2),2 ) + pow( h_pt_pp5_syst_uncorr->GetBinError(3),2 ) ) );

 h_pt_pp5_syst_uncorr_rebin->SetBinContent( 2, ( h_pt_pp5_syst_uncorr->GetBinContent(4) + h_pt_pp5_syst_uncorr->GetBinContent(5) )/2.0 );
 h_pt_pp5_syst_uncorr_rebin->SetBinError( 2, sqrt( pow( h_pt_pp5_syst_uncorr->GetBinError(4),2 ) + pow( h_pt_pp5_syst_uncorr->GetBinError(5),2 ) ) );

 h_pt_pp5_syst_uncorr_rebin->SetBinContent( 3, ( h_pt_pp5_syst_uncorr->GetBinContent(6) + h_pt_pp5_syst_uncorr->GetBinContent(7) )/2.0 );
 h_pt_pp5_syst_uncorr_rebin->SetBinError( 3, sqrt( pow( h_pt_pp5_syst_uncorr->GetBinError(6),2 ) + pow( h_pt_pp5_syst_uncorr->GetBinError(7),2 ) ) );

 h_pt_pp5_syst_uncorr_rebin->SetBinContent( 4, ( h_pt_pp5_syst_uncorr->GetBinContent(8) + h_pt_pp5_syst_uncorr->GetBinContent(9) )/2.0 );
 h_pt_pp5_syst_uncorr_rebin->SetBinError( 4, sqrt( pow( h_pt_pp5_syst_uncorr->GetBinError(8),2 ) + pow( h_pt_pp5_syst_uncorr->GetBinError(9),2 ) ) );

 h_pt_pp5_syst_uncorr_rebin->SetBinContent( 5, h_pt_pp5_syst_uncorr->GetBinContent(10) );
 h_pt_pp5_syst_uncorr_rebin->SetBinError( 5, h_pt_pp5_syst_uncorr->GetBinError(10) );

 h_pt_pp5_syst_uncorr_rebin->SetBinContent( 6, h_pt_pp5_syst_uncorr->GetBinContent(11) );
 h_pt_pp5_syst_uncorr_rebin->SetBinError( 6, h_pt_pp5_syst_uncorr->GetBinError(11) );

 h_pt_pp5_syst_uncorr_rebin->SetBinContent( 7, ( h_pt_pp5_syst_uncorr->GetBinContent(12) + h_pt_pp5_syst_uncorr->GetBinContent(13) )/2.0 );
 h_pt_pp5_syst_uncorr_rebin->SetBinError( 7, sqrt( pow( h_pt_pp5_syst_uncorr->GetBinError(12),2 ) + pow( h_pt_pp5_syst_uncorr->GetBinError(13),2 ) ) );
//**
*/


 double ncoll[nmult_pPb5] = {
//	13.6, 9.99, 6.53, 3.04 };
//	12.1, 9.6, 6.74, 4.0 };
	11.8, 9.32, 6.54, 3.89 };
 double ncoll_unc[nmult_pPb5] = {
	0.033, 0.024, 0.051, 0.071 };
 for(int i=0;i<nmult_pPb5;i++){
	ncoll_unc[i] *= ncoll[i];
 }

 double scale_unc_perc[nmult_pPb5];
 for(int i=0;i<nmult_pPb5;i++){
	scale_unc_perc[i] = ncoll_unc[i]/ncoll[i];
 }

 double total_corr_perc[nmult_pPb5];
 double corr_perc[nmult_pPb5];

 for(int i=0;i<nmult_pPb5;i++){
	total_corr_perc[i] = sqrt(
	pow( syst_corr_unc_pPb5[i],2 ) +
	pow( syst_corr_unc_pp5,2 ) + 
	pow( scale_unc_perc[i],2 ) );

	corr_perc[i] = sqrt(
	pow( syst_corr_unc_pPb5[i],2 ) +
	pow( syst_corr_unc_pp5,2 ) );
 }

 int RainbowColor[nmult_pPb5]=
       {632, 801, 402, 419 };
 TH1D* hR_pPb5_stat[nmult_pPb5];
 TH1D* hR_pPb5_syst_unc[nmult_pPb5]; 
 for(int i=0;i<nmult_pPb5;i++){
	hR_pPb5_stat[i] = (TH1D*)h_pt_pPb5_stat[i]->Clone(0);
	hR_pPb5_syst_unc[i] = (TH1D*)h_pt_pPb5_syst_uncorr[i]->Clone(0);

//	if( hR_pPb5_stat[i]->GetFunction("f1") ) hR_pPb5_stat[i]->GetFunction("f1")->Delete(); 
//	if( hR_pPb5_syst_unc[i]->GetFunction("f1") ) hR_pPb5_syst_unc[i]->GetFunction("f1")->Delete(); 


	hR_pPb5_stat[i]->Divide( h_pt_pp5_stat_rebin );
	hR_pPb5_stat[i]->Scale( 1.0/ncoll[i] );

	hR_pPb5_syst_unc[i]->Divide( h_pt_pp5_syst_uncorr_rebin );
	hR_pPb5_syst_unc[i]->Scale( 1.0/ncoll[i] );

	hR_pPb5_stat[i]->SetMarkerStyle(20);
	hR_pPb5_stat[i]->SetMarkerColor(RainbowColor[i]);
	hR_pPb5_stat[i]->SetMarkerColor(RainbowColor[i]);

	hR_pPb5_stat[i]->SetMaximum(2.0);
	hR_pPb5_stat[i]->SetMinimum(0.0);

	hR_pPb5_syst_unc[i]->SetFillStyle(0);
	hR_pPb5_syst_unc[i]->SetLineColor(RainbowColor[i]);
	hR_pPb5_syst_unc[i]->SetMarkerColor(RainbowColor[i]);

	hR_pPb5_stat[i]->SetLineColor(RainbowColor[i]); 

	hR_pPb5_stat[i]->GetYaxis()->SetTitle("Q_{pPb}");
	hR_pPb5_stat[i]->SetTitle("");
 }


 const int nmult_RpPb_ch = 7;
 double multmin_RpPb_ch[nmult_RpPb_ch] = {
	0,  5, 10, 20, 40, 60, 80 };
 double multmax_RpPb_ch[nmult_RpPb_ch] = {
	5, 10, 20, 40, 60, 80, 100 };


 TH1F* hRpPb_ch_cntr[nmult_RpPb_ch];
 TH1F* hRpPb_ch_stat[nmult_RpPb_ch];
 TH1F* hRpPb_ch_syst[nmult_RpPb_ch];
 TH1F* hRpPb_ch_scle[nmult_RpPb_ch];
 TH1F* hRpPb_ch_corr[nmult_RpPb_ch];

 TDirectoryFile* dir;
 dir = (TDirectoryFile*)fRpPb_ch->GetDirectory("Table 9");

 for(int i=0;i<nmult_RpPb_ch;i++){
	hRpPb_ch_cntr[i] = (TH1F*)dir->Get(Form("Hist1D_y%d",i+1));
	hRpPb_ch_stat[i] = (TH1F*)dir->Get(Form("Hist1D_y%d_e1",i+1));
	hRpPb_ch_syst[i] = (TH1F*)dir->Get(Form("Hist1D_y%d_e2",i+1));
	hRpPb_ch_scle[i] = (TH1F*)dir->Get(Form("Hist1D_y%d_e3",i+1));
	hRpPb_ch_corr[i] = (TH1F*)dir->Get(Form("Hist1D_y%d_e4",i+1));

	hRpPb_ch_cntr[i]->Scale( multmax_RpPb_ch[i] - multmin_RpPb_ch[i] );
	hRpPb_ch_stat[i]->Scale( multmax_RpPb_ch[i] - multmin_RpPb_ch[i] );
	hRpPb_ch_syst[i]->Scale( multmax_RpPb_ch[i] - multmin_RpPb_ch[i] );
	hRpPb_ch_scle[i]->Scale( multmax_RpPb_ch[i] - multmin_RpPb_ch[i] );
	hRpPb_ch_corr[i]->Scale( multmax_RpPb_ch[i] - multmin_RpPb_ch[i] );
 }

 TH1F* hRpPb_ch_cntr_rebin[nmult_pPb5];
 TH1F* hRpPb_ch_stat_rebin[nmult_pPb5];
 TH1F* hRpPb_ch_syst_rebin[nmult_pPb5];
 TH1F* hRpPb_ch_scle_rebin[nmult_pPb5];
 TH1F* hRpPb_ch_corr_rebin[nmult_pPb5];

 for(int i=0;i<nmult_RpPb_ch;i++){
	if( i < 2.5 ){
		if( i == 0 ){
			hRpPb_ch_cntr_rebin[0] = (TH1F*)hRpPb_ch_cntr[i]->Clone();
			hRpPb_ch_stat_rebin[0] = (TH1F*)hRpPb_ch_stat[i]->Clone();
			hRpPb_ch_syst_rebin[0] = (TH1F*)hRpPb_ch_syst[i]->Clone();
			hRpPb_ch_scle_rebin[0] = (TH1F*)hRpPb_ch_scle[i]->Clone();
			hRpPb_ch_corr_rebin[0] = (TH1F*)hRpPb_ch_corr[i]->Clone();		
		}
		else{
			hRpPb_ch_cntr_rebin[0]->Add( (TH1F*)hRpPb_ch_cntr[i], 1.0 );
			for(int j=0;j<hRpPb_ch_cntr_rebin[0]->GetNbinsX();j++){
				hRpPb_ch_stat_rebin[0]->SetBinContent( j+1,
					sqrt( pow( hRpPb_ch_stat_rebin[0]->GetBinContent(j+1),2 ) +
					pow( hRpPb_ch_stat[i]->GetBinContent(j+1),2 ) ) );

				hRpPb_ch_syst_rebin[0]->SetBinContent( j+1,
					sqrt( pow( hRpPb_ch_syst_rebin[0]->GetBinContent(j+1),2 ) +
					pow( hRpPb_ch_syst[i]->GetBinContent(j+1),2 ) ) );

				hRpPb_ch_scle_rebin[0]->SetBinContent( j+1,
					sqrt( pow( hRpPb_ch_scle_rebin[0]->GetBinContent(j+1),2 ) +
					pow( hRpPb_ch_scle[i]->GetBinContent(j+1),2 ) ) );

				hRpPb_ch_corr_rebin[0]->SetBinContent( j+1,
					sqrt( pow( hRpPb_ch_corr_rebin[0]->GetBinContent(j+1),2 ) +
					pow( hRpPb_ch_corr[i]->GetBinContent(j+1),2 ) ) );
			}
		}
	}
	else if( i == 3 ){
		hRpPb_ch_cntr_rebin[1] = (TH1F*)hRpPb_ch_cntr[i]->Clone();
		hRpPb_ch_stat_rebin[1] = (TH1F*)hRpPb_ch_stat[i]->Clone();
		hRpPb_ch_syst_rebin[1] = (TH1F*)hRpPb_ch_syst[i]->Clone();
		hRpPb_ch_scle_rebin[1] = (TH1F*)hRpPb_ch_scle[i]->Clone();
		hRpPb_ch_corr_rebin[1] = (TH1F*)hRpPb_ch_corr[i]->Clone();
	}
	else if( i == 4 ){
                hRpPb_ch_cntr_rebin[2] = (TH1F*)hRpPb_ch_cntr[i]->Clone();
                hRpPb_ch_stat_rebin[2] = (TH1F*)hRpPb_ch_stat[i]->Clone();
                hRpPb_ch_syst_rebin[2] = (TH1F*)hRpPb_ch_syst[i]->Clone();
                hRpPb_ch_scle_rebin[2] = (TH1F*)hRpPb_ch_scle[i]->Clone();
                hRpPb_ch_corr_rebin[2] = (TH1F*)hRpPb_ch_corr[i]->Clone();
	}
	else if( i == 5 ){
               	hRpPb_ch_cntr_rebin[3] = (TH1F*)hRpPb_ch_cntr[i]->Clone();
               	hRpPb_ch_stat_rebin[3] = (TH1F*)hRpPb_ch_stat[i]->Clone();
               	hRpPb_ch_syst_rebin[3] = (TH1F*)hRpPb_ch_syst[i]->Clone();
               	hRpPb_ch_scle_rebin[3] = (TH1F*)hRpPb_ch_scle[i]->Clone();
               	hRpPb_ch_corr_rebin[3] = (TH1F*)hRpPb_ch_corr[i]->Clone();
	}
 }

 TCanvas* ctest = new TCanvas("ctest","ctest");
 gStyle->SetOptStat(0);
 for(int i=0;i<nmult_pPb5;i++){
	hRpPb_ch_cntr_rebin[i]->Scale( 1.0 / ( multmax[i] - multmin[i] ) ); 
	hRpPb_ch_stat_rebin[i]->Scale( 1.0 / ( multmax[i] - multmin[i] ) );
	hRpPb_ch_syst_rebin[i]->Scale( 1.0 / ( multmax[i] - multmin[i] ) );
	hRpPb_ch_scle_rebin[i]->Scale( 1.0 / ( multmax[i] - multmin[i] ) );
	hRpPb_ch_corr_rebin[i]->Scale( 1.0 / ( multmax[i] - multmin[i] ) );

	for(int j=0;j<hRpPb_ch_cntr_rebin[i]->GetNbinsX();j++){
		hRpPb_ch_stat_rebin[i]->SetBinError( j+1, hRpPb_ch_stat_rebin[i]->GetBinContent(j+1) );
		hRpPb_ch_syst_rebin[i]->SetBinError( j+1, hRpPb_ch_syst_rebin[i]->GetBinContent(j+1) );

		hRpPb_ch_stat_rebin[i]->SetBinContent( j+1, hRpPb_ch_cntr_rebin[i]->GetBinContent(j+1) );
		hRpPb_ch_syst_rebin[i]->SetBinContent( j+1, hRpPb_ch_cntr_rebin[i]->GetBinContent(j+1) );
	}

	hRpPb_ch_syst_rebin[i]->SetFillStyle(0);

	hRpPb_ch_syst_rebin[i]->SetLineColor( RainbowColor[i] );
	hRpPb_ch_stat_rebin[i]->SetLineColor( RainbowColor[i] );

        hRpPb_ch_syst_rebin[i]->SetMarkerColor( RainbowColor[i] );
        hRpPb_ch_stat_rebin[i]->SetMarkerColor( RainbowColor[i] );

	if( i==0 ) hRpPb_ch_syst_rebin[i]->Draw("e2");
	hRpPb_ch_syst_rebin[i]->Draw("e2, same");
	hRpPb_ch_stat_rebin[i]->Draw("same");
	hRpPb_ch_stat_rebin[i]->Draw("same");


	corr_perc[i] = sqrt( pow( corr_perc[i],2 ) + pow( hRpPb_ch_corr_rebin[i]->GetBinContent(1),2 ) );
 }




 TCanvas* c = new TCanvas("c","c",800,600);

 TLegend* leg = new TLegend(0.2,0.55,0.5,0.89);
 leg->SetLineWidth(0);
 leg->SetNColumns(2);
 leg->SetHeader("ZNA Multiplicity for pPb");
 leg->SetFillColorAlpha(0,0);

 for(int i=0;i<nmult_pPb5;i++){
	if(i==0) hR_pPb5_stat[i]->Draw();
	hR_pPb5_stat[i]->Draw("same");
	hR_pPb5_syst_unc[i]->Draw("same,e2");
	leg->AddEntry( hR_pPb5_stat[i], Form("%.0lf#font[122]{-}%.0lf%%",multmin[i],multmax[i]),"LP");
 }

 TLine* l_unity = new TLine( 0.3, 1.0, 9.0, 1.0 );
 l_unity->Draw();
 TBox* corr[nmult_pPb5];
 TBox* ScaleUnc[nmult_pPb5];
 for(int i=0;i<nmult_pPb5;i++){
//	corr[i] = new TBox(0.5+0.2*i, 1.0-total_corr_perc[i], 0.7+0.2*i, 1.0+total_corr_perc[i]);
//	corr[i] = new TBox(0.3, 1.0-total_corr_perc[i], 0.7, 1.0+total_corr_perc[i]);
//	corr[i] = new TBox(0.3, 1.0-corr_perc[i], 0.7, 1.0+corr_perc[i]);
	ScaleUnc[i] = new TBox(0.3, 1.0-scale_unc_perc[i], 0.7, 1.0+scale_unc_perc[i]);
//	corr[i]->SetFillColor(RainbowColor[i]);
	ScaleUnc[i]->SetFillColor(RainbowColor[i]);
	ScaleUnc[i]->SetLineColor(RainbowColor[i]);
	ScaleUnc[i]->SetFillStyle(0);

//	corr[i]->Draw();
 }
 TLatex* latex = new TLatex();
 latex->SetTextSize(0.04);
 latex->DrawLatex(4.5,1.8,"ALICE Preliminary");
 latex->DrawLatex(4.5,1.7,"INEL for pp, mult. class for p#font[122]{-}Pb");
 latex->DrawLatex(4.5,1.6,"pp@5.02 TeV, this work");
 latex->DrawLatex(4.5,1.5,"pPb@5.02 TeV, this work");


 leg->Draw();

// c->SaveAs("RpPb_5TeV.pdf");

 TLegend* leg_for_pPb5 = new TLegend(0.0475,0.576,0.992,0.865);
 leg_for_pPb5->SetNColumns(3);
 leg_for_pPb5->SetLineWidth(0.0);
 leg_for_pPb5->SetFillColorAlpha(0,0); 
for(int i=0;i<nmult_pPb5;i++){
	leg_for_pPb5->AddEntry( hR_pPb5_stat[i], Form("%.0lf#font[122]{-}%.0lf%%",multmin[i],multmax[i]),"p");
 }


 TLegend* leg_for_unc = new TLegend(0.3555, 0.8955, 0.9380, 0.9841);
 leg_for_unc->SetFillColorAlpha(0,0);
 leg_for_unc->SetNColumns(2);
 leg_for_unc->SetLineWidth(0.0);
 TBox* unc_corr_example = new TBox(0,0,1,1);
 unc_corr_example->SetFillColor(1);
 TBox* unc_scale_example = new TBox(0,0,1,1);
 unc_scale_example->SetFillStyle(0);

// leg_for_unc->AddEntry( unc_corr_example,"Correlated Unc.","f");
 leg_for_unc->AddEntry( unc_scale_example,"Scaling Unc.","f");



 TCanvas* cc_v1 = new TCanvas("cc_v1","cc_v1",1000,600);
 cc_v1->SetBottomMargin(0.14);
 cc_v1->SetLeftMargin(0.14);
 cc_v1->Divide(2,2,0,.0);
 for(int i=0;i<nmult_pPb5;i++){
	cc_v1->cd(i+1);
	gPad->SetTicks();
	hR_pPb5_stat[i]->GetXaxis()->SetTitle(" #font[12]{p}_{#font[22]{T}} (GeV/#font[12]{c})");
	hR_pPb5_stat[i]->GetYaxis()->SetNdivisions(505);
	if( i==0 || i==2 ){
		hR_pPb5_stat[i]->GetYaxis()->SetTitleSize(0.1);
		hR_pPb5_stat[i]->GetYaxis()->SetTitleOffset(0.6);
		hR_pPb5_stat[i]->GetYaxis()->SetLabelSize(0.07);
		hR_pPb5_stat[i]->GetYaxis()->SetNdivisions(505);
		hR_pPb5_stat[i]->GetYaxis()->CenterTitle();
	}
	else{
		hR_pPb5_stat[i]->GetYaxis()->SetTitleSize(0.0);
		hR_pPb5_stat[i]->GetYaxis()->SetLabelSize(0.0);
	}

	if( i==2 || i==3 ){
		hR_pPb5_stat[i]->GetXaxis()->SetTitleSize(0.07);
		hR_pPb5_stat[i]->GetXaxis()->SetTitleOffset(0.9);
		hR_pPb5_stat[i]->GetXaxis()->SetLabelSize(0.07);
		hR_pPb5_stat[i]->GetXaxis()->CenterTitle();
	}
	else{
		hR_pPb5_stat[i]->GetXaxis()->SetTitleSize(0.0);
		hR_pPb5_stat[i]->GetXaxis()->SetLabelSize(0.0);
	}
	hR_pPb5_stat[i]->SetMaximum(2.1);
	hR_pPb5_stat[i]->SetMinimum(0.1);
	hR_pPb5_stat[i]->GetXaxis()->SetRangeUser(0,8.1);
	hR_pPb5_stat[i]->GetXaxis()->SetNdivisions(508);
	hR_pPb5_stat[i]->GetXaxis()->LabelsOption("d");
	hR_pPb5_stat[i]->Draw();
	hR_pPb5_syst_unc[i]->Draw("same,e2");
	l_unity->Draw();
//	corr[i]->Draw();
	ScaleUnc[i]->Draw();

	if( i==0 ){
		latex->SetTextSize(0.09);
		latex->DrawLatex(1.0,1.7,"ALICE Preliminary");
		latex->DrawLatex(1.0,1.4,"p#font[122]{-}Pb #sqrt{#it{s}_{NN}} = 5.02 TeV, -0.5<y<0");
	}
	else if( i==1 ){
		gPad->SetLeftMargin(0.012);
		latex->SetTextSize(0.07);
		latex->DrawLatex(1.0,1.8,"ZNA Multiplicity");
		leg_for_pPb5->Draw();	
	}
	else if( i== 2 ){
		leg_for_unc->Draw();
	}
	else if( i==3 ){
		gPad->SetLeftMargin(0.012);
	}
 }

// cc_v1->SaveAs("RpPb_cos.pdf");

 TLegend* legdata = new TLegend(0.189,0.696,0.741,0.838);
 legdata->SetNColumns(2);
 legdata->SetLineWidth(0.0);
 legdata->SetFillColorAlpha(0,0);
 legdata->AddEntry( hR_pPb5_stat[0], "f_{0}(980)", "p");
 legdata->AddEntry( hRpPb_ch_stat_rebin[0], "Charged Hadron","p");

 for(int i=0;i<nmult_pPb5;i++){
	cc_v1->cd(i+1);

	hRpPb_ch_stat_rebin[i]->SetMarkerStyle(24);
	hRpPb_ch_stat_rebin[i]->Draw("same");
	hRpPb_ch_syst_rebin[i]->Draw("same,e2");

	if( i == 2 ){
		legdata->Draw();
	}
	else if( i == 3 ){
		latex->DrawLatex(0.5,1.5,"Uncertainties: stat.(bars), syst.(boxes)");
		latex->DrawLatex(0.5,1.7,"Q_{pPb}^{ch}, PRC 91 064905 (2015)");
	}
 }

 cc_v1->SaveAs("figs/Fig7_QpPb.pdf");
/*

 TH1D* hQpPb_ratio_stat[nmult_pPb5];
 TH1D* hQpPb_ratio_syst[nmult_pPb5];

 for(int i=0;i<nmult_pPb5;i++){
	hQpPb_ratio_stat[i] = (TH1D*)hR_pPb5_stat[i]->Clone();
	hQpPb_ratio_stat[i]->Divide( hRpPb_ch_stat_rebin[i] );

	hQpPb_ratio_syst[i] = (TH1D*)hR_pPb5_syst_unc[i]->Clone();
	hQpPb_ratio_syst[i]->Divide( hRpPb_ch_syst_rebin[i] );

	cc_v1->cd(i+1);
	hQpPb_ratio_stat[i]->GetYaxis()->SetTitle(" Q_{pPb}^{f0(980)} / Q_{pPb}^{ch}");
	
	hQpPb_ratio_stat[i]->Draw();
	hQpPb_ratio_syst[i]->Draw("same,e2");

        if( i==0 ){
                latex->SetTextSize(0.09);
                latex->DrawLatex(1.0,1.7,"ALICE Work in progress");
        }
        else if( i==1 ){
                latex->SetTextSize(0.07);
                latex->DrawLatex(1.0,1.8,"ZNA Multiplicity");
                leg_for_pPb5->Draw();
        }
        else if( i== 2 ){
//                leg_for_unc->Draw();
        }

 }
 
 cc_v1->SaveAs("RpPb_cos_addch_ZNA_ratio.pdf");

// TFile* fout_QpPb = new TFile("QpPb_out.root","recreate");

*/
}
