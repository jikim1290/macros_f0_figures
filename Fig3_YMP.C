{
 gStyle->SetTextFont(42);

 TFile* fpPb5 = new TFile("./data//TotalYieldOut.root","read");
 TGraphErrors* gf0y_pPb5_stat = (TGraphErrors*)fpPb5->Get("gF0HadronStat");
 TGraphErrors* gf0y_pPb5_syst = (TGraphErrors*)fpPb5->Get("gF0HadronSys");
 TGraphErrors* gf0y_pPb5_UnCorrsyst = (TGraphErrors*)fpPb5->Get("gF0HadronUnCorrSys");
 
 TGraphErrors* gf0y_pPb5_mb_stat = new TGraphErrors();
 TGraphErrors* gf0y_pPb5_mb_syst = new TGraphErrors();
 
 gf0y_pPb5_mb_stat->SetPoint( 0, gf0y_pPb5_stat->GetX()[4], gf0y_pPb5_stat->GetY()[4] );
 gf0y_pPb5_mb_stat->SetPointError( 0, gf0y_pPb5_stat->GetErrorX(4), gf0y_pPb5_stat->GetErrorY(4) );

 gf0y_pPb5_mb_syst->SetPoint( 0, gf0y_pPb5_syst->GetX()[4], gf0y_pPb5_syst->GetY()[4] );
 gf0y_pPb5_mb_syst->SetPointError( 0, gf0y_pPb5_syst->GetErrorX(4), gf0y_pPb5_syst->GetErrorY(4) );

 gf0y_pPb5_syst->SetPoint(4,-1,-1);
 gf0y_pPb5_stat->SetPoint(4,-1,-1);

 TGraphErrors* gf0mp_pPb5_stat = (TGraphErrors*)fpPb5->Get("gMeanpTOverHadronStatUpdated");
 TGraphErrors* gf0mp_pPb5_syst = (TGraphErrors*)fpPb5->Get("gMeanpTOverHadronSysUpdated");
 TGraphErrors* gf0mp_pPb5_UnCorrsyst = (TGraphErrors*)fpPb5->Get("gMeanpTOverHadronSysUpdated");

 TGraphErrors* gf0mp_pPb5_mb_stat = new TGraphErrors();
 TGraphErrors* gf0mp_pPb5_mb_syst = new TGraphErrors();

 gf0mp_pPb5_mb_stat->SetPoint( 0, gf0mp_pPb5_stat->GetX()[4], gf0mp_pPb5_stat->GetY()[4] );
 gf0mp_pPb5_mb_stat->SetPointError( 0, gf0mp_pPb5_stat->GetErrorX(4), gf0mp_pPb5_stat->GetErrorY(4) );
 
 gf0mp_pPb5_mb_syst->SetPoint( 0, gf0mp_pPb5_syst->GetX()[4], gf0mp_pPb5_syst->GetY()[4] );
 gf0mp_pPb5_mb_syst->SetPointError( 0, gf0mp_pPb5_syst->GetErrorX(4), gf0mp_pPb5_syst->GetErrorY(4) );

 gf0mp_pPb5_syst->SetPoint(4,-1,-1);
 gf0mp_pPb5_stat->SetPoint(4,-1,-1);

 gf0y_pPb5_stat->SetMinimum(0.0);
 gf0y_pPb5_stat->SetMaximum(0.25);

 gf0y_pPb5_stat->GetXaxis()->SetRangeUser(0,40);
 gf0y_pPb5_syst->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#eta_{|#eta|<0.5}#GT");
 gf0y_pPb5_syst->GetYaxis()->SetTitle("d#it{N}_{f_{0}(980)}/dy");
 gf0y_pPb5_syst->SetTitle("");
 gf0y_pPb5_syst->GetXaxis()->SetTitleSize(0.06);
 gf0y_pPb5_syst->GetYaxis()->SetTitleSize(0.06);
 gf0y_pPb5_syst->GetXaxis()->SetLabelSize(0.06);
 gf0y_pPb5_syst->GetYaxis()->SetLabelSize(0.06);
 gf0y_pPb5_syst->GetYaxis()->SetTitleOffset(1.15);
 gf0y_pPb5_syst->GetXaxis()->SetTitleOffset(1.15);


 gf0mp_pPb5_stat->GetXaxis()->SetRangeUser(0,40);
 gf0mp_pPb5_syst->GetXaxis()->SetTitle("#LTd#it{N}_{ch}/d#eta_{|#eta|<0.5}#GT");
 gf0mp_pPb5_syst->GetYaxis()->SetTitle("#LT#it{p}_{T}#GT (GeV/#it{c})");
 gf0mp_pPb5_syst->SetTitle("");
 gf0mp_pPb5_syst->GetXaxis()->SetTitleSize(0.06);
 gf0mp_pPb5_syst->GetYaxis()->SetTitleSize(0.06);
 gf0mp_pPb5_syst->GetXaxis()->SetLabelSize(0.06);
 gf0mp_pPb5_syst->GetYaxis()->SetLabelSize(0.06);
 gf0mp_pPb5_syst->GetYaxis()->SetTitleOffset(1.15);
 gf0mp_pPb5_syst->GetXaxis()->SetTitleOffset(1.15);

 gf0y_pPb5_stat->SetLineColor(2);
 gf0y_pPb5_stat->SetMarkerColor(2);
 gf0y_pPb5_stat->SetMarkerStyle(22);
 gf0y_pPb5_stat->SetMarkerSize(1.5);

 gf0y_pPb5_syst->SetLineColor(2);
 gf0y_pPb5_syst->SetMarkerColor(2);
 gf0y_pPb5_syst->SetMarkerStyle(22);

 gf0y_pPb5_UnCorrsyst->SetFillStyle(3001);
 gf0y_pPb5_UnCorrsyst->SetFillColor(2);

 gf0mp_pPb5_stat->SetLineColor(2);
 gf0mp_pPb5_stat->SetMarkerColor(2);
 gf0mp_pPb5_stat->SetMarkerStyle(22);
 gf0mp_pPb5_stat->SetMarkerSize(1.5);

 gf0mp_pPb5_syst->SetLineColor(2);
 gf0mp_pPb5_syst->SetMarkerColor(2);
 gf0mp_pPb5_syst->SetMarkerStyle(22);
 gf0mp_pPb5_syst->SetFillStyle(0);

 gf0mp_pPb5_UnCorrsyst->SetFillStyle(3001);
 gf0mp_pPb5_UnCorrsyst->SetFillColor(2);


 gf0y_pPb5_mb_stat->SetMarkerStyle(22);
 gf0y_pPb5_mb_stat->SetMarkerColor(1);
 gf0y_pPb5_mb_stat->SetMarkerSize(1.5);

 gf0y_pPb5_mb_syst->SetMarkerStyle(22);
 gf0y_pPb5_mb_syst->SetMarkerColor(1);
 gf0y_pPb5_mb_syst->SetLineColor(1);
 gf0y_pPb5_mb_syst->SetFillStyle(0);


 gf0mp_pPb5_mb_stat->SetMarkerStyle(22);
 gf0mp_pPb5_mb_stat->SetMarkerColor(1);
 gf0mp_pPb5_mb_stat->SetMarkerSize(1.5);

 gf0mp_pPb5_mb_syst->SetMarkerStyle(22);
 gf0mp_pPb5_mb_syst->SetMarkerColor(1);
 gf0mp_pPb5_mb_syst->SetLineColor(1);
 gf0mp_pPb5_mb_syst->SetFillStyle(0);

 double pp5TeV_inc_mult = 4.3;
 double pp5TeV_inc_mult_staterr = 0.0;
 double pp5TeV_inc_mult_systerr = 0.32;

 double pp5TeV_inc_f0_yield = 0.0385;
 double pp5TeV_inc_f0_yield_staterr = 0.00001;
 double pp5TeV_inc_f0_yield_systerr = 0.0047;

 double pp5TeV_inc_f0_meanpt = 0.9627;
 double pp5TeV_inc_f0_meanpt_staterr = 0.0014;
 double pp5TeV_inc_f0_meanpt_systerr = 0.0357;


 TGraphErrors* gf0y_pp5_stat = new TGraphErrors(1, &pp5TeV_inc_mult, &pp5TeV_inc_f0_yield, &pp5TeV_inc_mult_staterr, &pp5TeV_inc_f0_yield_staterr );
 TGraphErrors* gf0y_pp5_syst = new TGraphErrors(1, &pp5TeV_inc_mult, &pp5TeV_inc_f0_yield, &pp5TeV_inc_mult_systerr, &pp5TeV_inc_f0_yield_systerr );

 TGraphErrors* gf0mp_pp5_stat = new TGraphErrors(1, &pp5TeV_inc_mult, &pp5TeV_inc_f0_meanpt, &pp5TeV_inc_mult_staterr, &pp5TeV_inc_f0_meanpt_staterr );
 TGraphErrors* gf0mp_pp5_syst = new TGraphErrors(1, &pp5TeV_inc_mult, &pp5TeV_inc_f0_meanpt, &pp5TeV_inc_mult_systerr, &pp5TeV_inc_f0_meanpt_systerr );


 gf0y_pp5_stat->SetLineColor(6);
 gf0y_pp5_stat->SetMarkerColor(6);
 gf0y_pp5_stat->SetMarkerStyle(21);
 gf0y_pp5_stat->SetMarkerSize(1.5);

 gf0y_pp5_syst->SetLineColor(6);
 gf0y_pp5_syst->SetMarkerColor(6);
 gf0y_pp5_syst->SetMarkerStyle(21);
 gf0y_pp5_syst->SetFillStyle(0);


 gf0mp_pp5_stat->SetLineColor(6);
 gf0mp_pp5_stat->SetMarkerColor(6);
 gf0mp_pp5_stat->SetMarkerStyle(21);

 gf0mp_pp5_syst->SetLineColor(6);
 gf0mp_pp5_syst->SetMarkerColor(6);
 gf0mp_pp5_syst->SetMarkerStyle(21);
 gf0mp_pp5_syst->SetFillStyle(0);
 gf0mp_pp5_stat->SetMarkerSize(1.5);

 TCanvas* c = new TCanvas("c","c",900,650);
 c->SetLeftMargin(0.15);
 c->SetBottomMargin(0.17);
 c->SetTicks(1);

 gf0y_pPb5_syst->GetXaxis()->SetRangeUser(0,40);
 gf0y_pPb5_syst->GetYaxis()->SetRangeUser(0,0.3);
 gf0y_pPb5_syst->Draw("Ae2");
 gf0y_pPb5_stat->Draw("P");
// gf0y_pPb5_UnCorrsyst->Draw("p2");


// gf0y_pp13_stat->Draw("P");
// gf0y_pp13_syst->Draw("e2");

// gf0y_pPb8_stat->Draw("P");
// gf0y_pPb8_syst->Draw("e2");

 gf0y_pp5_stat->Draw("P");
 gf0y_pp5_syst->Draw("e2");

 gf0y_pPb5_mb_stat->Draw("P");
 gf0y_pPb5_mb_syst->Draw("e2");

 TLegend* leg = new TLegend(0.168,0.593,0.744,0.88);
 leg->SetFillColorAlpha(0,0);
 leg->SetLineWidth(0.0);
 leg->AddEntry( (TObject*)0, "#scale[1.3]{ALICE Preliminary}","");
 leg->AddEntry( (TObject*)0, "f_{0}(980)#rightarrow#pi^{+}#pi^{-}", "");
 leg->AddEntry( gf0y_pp5_stat, "pp, #sqrt{#it{s}} = 5.02 TeV, INEL","lp");
 leg->AddEntry( gf0y_pPb5_stat, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV","lp");
 leg->AddEntry( gf0y_pPb5_mb_stat, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV, NSD","lp");

 leg->Draw();
 c->SaveAs("figs/Fig3_yield.pdf");
// leg->Clear();


 TCanvas* c1 = new TCanvas("c1","c1",900,650);
 c1->SetLeftMargin(0.15);
 c1->SetBottomMargin(0.15);
 c1->SetTicks(1);

 gf0mp_pPb5_syst->GetXaxis()->SetRangeUser(0,40);
 gf0mp_pPb5_syst->SetMaximum(1.4);
 gf0mp_pPb5_syst->SetMinimum(0.7);

 gf0mp_pPb5_syst->Draw("Ae2");
 gf0mp_pPb5_stat->Draw("P");

 gf0mp_pPb5_mb_stat->Draw("P");
 gf0mp_pPb5_mb_syst->Draw("e2");



// gf0mp_pPb5_UnCorrsyst->Draw("p2");

// gf0mp_pp13_stat->Draw("P");
// gf0mp_pp13_syst->Draw("e2");
 gf0mp_pp5_stat->Draw("P");
 gf0mp_pp5_syst->Draw("e2");
// gf0mp_pPb8_stat->Draw("P");
// gf0mp_pPb8_syst->Draw("e2");

 TLegend* leg1 = new TLegend(0.304,0.233,0.864,0.486);
 leg1->SetFillColorAlpha(0,0);
 leg1->SetLineWidth(0.0);
 leg1->AddEntry( (TObject*)0, "#scale[1.3]{ALICE Preliminary}","");
// leg1->AddEntry( gf0mp_pp13_stat, "pp, #sqrt{s} = 13 TeV, INEL>0","lp");
 leg1->AddEntry( (TObject*)0, "f_{0}(980)#rightarrow#pi^{+}#pi^{-}", "");
 leg1->AddEntry( gf0mp_pp5_stat, "pp, #sqrt{#it{s}} = 5.02 TeV, INEL","lp");
 leg1->AddEntry( gf0mp_pPb5_stat, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV","lp");
 leg1->AddEntry( gf0mp_pPb5_mb_stat, "p#font[122]{-}Pb, #sqrt{#it{s}_{NN}} = 5.02 TeV, NSD","lp");

// leg1->AddEntry( gf0mp_pPb8_stat, "p-Pb, #sqrt{s_{NN}} = 8.16 TeV, NSD","lp");

 leg1->Draw();

 c1->SaveAs("figs/Fig3_MP.pdf");

}
