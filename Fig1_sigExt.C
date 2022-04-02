{

 const int nsig=2;
 const char signame[nsig][100] = {"high", "low"};
 double multmin[nsig] = { 0, 60 };
 double multmax[nsig] = {20, 80 };
 double ptmin[nsig] = {1.5, 1.5 };
 double ptmax[nsig] = {2.0, 2.0 };


 TFile* fin = new TFile("./data/Sigout.root","read");
 TH1D* hSig[nsig];
 TF1* fFit[nsig];
 TF1* fFitBkg[nsig];
 TF1* fFitf0[nsig];
 TF1* fFitf2[nsig];
 TF1* fFitRho[nsig];
 for(int i=0;i<nsig;i++){
	hSig[i] = (TH1D*)fin->Get(Form("hist_%s",signame[i]));
	fFit[i] = (TF1*)fin->Get(Form("fit_%s",signame[i]));
	fFitBkg[i] = (TF1*)fin->Get(Form("Bkg_%s",signame[i]));
	fFitf0[i] = (TF1*)fin->Get(Form("f0_%s",signame[i]));
	fFitf2[i] = (TF1*)fin->Get(Form("f2_%s",signame[i]));
	fFitf2[i]->SetLineColor(kGreen+3);
	fFitRho[i] = (TF1*)fin->Get(Form("rho_%s",signame[i]));
 }


 TCanvas* cc = new TCanvas("cc","cc",900,700);
 cc->SetLeftMargin(0.15);
 cc->SetBottomMargin(0.12);
 cc->SetRightMargin(0.03);
 cc->SetTopMargin(0.05);
 gPad->SetTicks(1);

 TLegend* legEvtClass = new TLegend(0.55,0.73,0.9,0.93);
 legEvtClass->SetLineWidth(0.0);
 legEvtClass->SetTextFont(43);
 legEvtClass->SetTextSize(28);
 legEvtClass->SetFillColorAlpha(0,0);

 TLegend* legFitCos = new TLegend(0.7,0.43,0.9,0.73);
 legFitCos->SetLineWidth(0.0);
 legFitCos->SetTextFont(43);
 legFitCos->SetTextSize(28);
 legFitCos->SetFillColorAlpha(0,0);


 for(int i=0;i<nsig;i++){
	hSig[i]->GetYaxis()->SetTitleOffset(1.4);
	hSig[i]->GetYaxis()->SetTitleFont(43);
	hSig[i]->GetYaxis()->SetTitleSize(32);
	hSig[i]->GetYaxis()->SetLabelFont(43);
	hSig[i]->GetYaxis()->SetLabelSize(26);
	hSig[i]->GetXaxis()->SetTitleOffset(1.05);
	hSig[i]->GetXaxis()->SetTitleFont(43);
	hSig[i]->GetXaxis()->SetTitleSize(32);
	hSig[i]->GetXaxis()->SetLabelFont(43);
	hSig[i]->GetXaxis()->SetLabelSize(26);
	hSig[i]->Draw();
	fFit[i]->Draw("same");
	fFitBkg[i]->Draw("same");
	fFitRho[i]->Draw("same");
	fFitf2[i]->Draw("same");
	fFitf0[i]->Draw("same");

	legEvtClass->SetHeader("#scale[1.2]{ALICE Preliminary}","h");
	legEvtClass->AddEntry( (TObject*)0, "p#font[122]{-}Pb, #sqrt{s_{NN}} = 5.02 TeV","h");
	legEvtClass->AddEntry( (TObject*)0, Form("%.0lf#font[122]{-}%.0lf%%, %.1lf < #it{p}_{T} < %.1lf GeV/#it{c}",multmin[i],multmax[i],ptmin[i],ptmax[i]),"h" );
	legEvtClass->AddEntry( (TObject*)0, "f_{0}(980) #rightarrow #pi^{+}#pi^{-}, -0.5<y<0","h");

	legFitCos->AddEntry( hSig[i], "#scale[0.9]{Data}","lp");
	legFitCos->AddEntry( fFit[i], "#scale[0.9]{Sum}","lp");
	legFitCos->AddEntry( fFitf0[i], "#scale[0.9]{f_{0}(980)}","lp");
	legFitCos->AddEntry( fFitRho[i], "#scale[0.9]{#rho^{0}(770)}","lp");
	legFitCos->AddEntry( fFitf2[i], "#scale[0.9]{f_{2}(1270)}","lp");
	legFitCos->AddEntry( fFitBkg[i], "#scale[0.9]{Res. bkg}","lp");

	legEvtClass->Draw();
	legFitCos->Draw();

	cc->SaveAs(Form("figs/Fig1_sigext_%s.pdf",signame[i]));
	cc->SaveAs(Form("figs/Fig1_sigext_%s.eps",signame[i]));

	legEvtClass->Clear();
	legFitCos->Clear();
 }



}

