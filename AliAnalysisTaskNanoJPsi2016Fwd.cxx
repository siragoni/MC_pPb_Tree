/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

// c++ headers
#include <iostream>
#include <fstream>

// root headers
#include <TMath.h>
#include "TH1I.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH1D.h"
#include "TH2D.h"
#include <TFile.h>
#include <TF2.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TTree.h>
#include <TGraph2D.h>
#include <TStopwatch.h>
#include <TMatrixDSym.h>
#include <TFitResult.h>
#include <TLatex.h>
#include "TClonesArray.h"
#include "TDatabasePDG.h"
#include "TLorentzVector.h"
#include "TParticle.h"
#include "TObjString.h"
#include "TList.h"
#include "TChain.h"


// aliroot headers
#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"
#include "AliAODEvent.h"
#include "AliAODInputHandler.h"
#include "AliMuonTrackCuts.h"
#include "AliMCEvent.h"
#include <AliMCParticle.h>

// my headers
#include "AliAnalysisTaskNanoJPsi2016Fwd.h"



class AliAnalysisTaskNanoJPsi2016Fwd;    // your analysis class

using namespace std;            // std namespace: so you can do things like 'cout'

ClassImp(AliAnalysisTaskNanoJPsi2016Fwd) // classimp: necessary for root


AliAnalysisTaskNanoJPsi2016Fwd::AliAnalysisTaskNanoJPsi2016Fwd() : AliAnalysisTaskSE(),
  gMuonMass(0.105658), fPeriod(0), fIsMC(0),
  fAOD(0), fOutputList(0),fCounterH(0),
  fMuonTrackCounterH(0),
  fTriggerCounterFwdH(0),
  fGoodTrkFwdH(0),
  fMuonTrackCuts(0x0), fAnaTree(0), fAnaTreeMC(0),
  fRunNum(0), fL0inputs(0), fTracklets(0), fAnaType(-1),
  fGoodPosTrk(0), fGoodNegTrk(0),
  fZNAfired(0), fZNCfired(), fZNCEnergy(0), fZNAEnergy(0), fZPCEnergy(0), fZPAEnergy(0),
  fV0ADecision(-10), fV0CDecision(-10), fV0ATime(0), fV0CTime(0), fADADecision(-10), fADCDecision(-10), fADATime(0), fADCTime(0),
  fIR1Map(0), fIR2Map(0), fTrkTrkPt(0), fTrkTrkPhi(0), fTrkTrkY(0), fTrkTrkM(0), fTrkPt1(0), fTrkPt2(0),
  fTrkEta1(0), fTrkEta2(0), fTrkPhi1(0), fTrkPhi2(0), fTrkQ1(0), fTrkQ2(0), fTrkRabs1(0), fTrkRabs2(0),
  fMCTrkTrkPt(0), fMCTrkTrkPhi(0), fMCTrkTrkY(0), fMCTrkTrkM(0), fMCTrkPt1(0), fMCTrkPt2(0),
  fMCTrkEta1(0), fMCTrkEta2(0), fMCTrkPhi1(0), fMCTrkPhi2(0), fMCTrkQ1(0), fMCTrkQ2(0),
  fV0Hits{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  fV0TotalNCells(0)
{
    // default constructor, don't allocate memory here!
    // this is used by root for IO purposes, it needs to remain empty
}

//_____________________________________________________________________________
AliAnalysisTaskNanoJPsi2016Fwd::AliAnalysisTaskNanoJPsi2016Fwd(const char* name) : AliAnalysisTaskSE(name),
 gMuonMass(0.105658),fPeriod(0), fIsMC(0),
 fAOD(0), fOutputList(0),fCounterH(0),
  fMuonTrackCounterH(0),
  fTriggerCounterFwdH(0),
  fGoodTrkFwdH(0),
  fMuonTrackCuts(0x0), fAnaTree(0), fAnaTreeMC(0),
  fRunNum(0), fL0inputs(0), fTracklets(0), fAnaType(-1),
  fGoodPosTrk(0), fGoodNegTrk(0),
  fZNAfired(0), fZNCfired(), fZNCEnergy(0), fZNAEnergy(0), fZPCEnergy(0), fZPAEnergy(0),
  fV0ADecision(-10), fV0CDecision(-10), fV0ATime(0), fV0CTime(0),fADADecision(-10), fADCDecision(-10), fADATime(0), fADCTime(0),
  fIR1Map(0), fIR2Map(0), fTrkTrkPt(0), fTrkTrkPhi(0), fTrkTrkY(0), fTrkTrkM(0), fTrkPt1(0), fTrkPt2(0),
  fTrkEta1(0), fTrkEta2(0), fTrkPhi1(0), fTrkPhi2(0), fTrkQ1(0), fTrkQ2(0), fTrkRabs1(0), fTrkRabs2(0),
  fMCTrkTrkPt(0), fMCTrkTrkPhi(0), fMCTrkTrkY(0), fMCTrkTrkM(0), fMCTrkPt1(0), fMCTrkPt2(0),
  fMCTrkEta1(0), fMCTrkEta2(0), fMCTrkPhi1(0), fMCTrkPhi2(0), fMCTrkQ1(0), fMCTrkQ2(0),
  fV0Hits{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  fV0TotalNCells(0)
{
    // constructor
    DefineInput(0, TChain::Class());
    DefineOutput(1, TTree::Class());
    DefineOutput(2, TList::Class());
    DefineOutput(3, TTree::Class());
}
//_____________________________________________________________________________
AliAnalysisTaskNanoJPsi2016Fwd::~AliAnalysisTaskNanoJPsi2016Fwd()
{
    // destructor
    // liberate all allocated memory
    if(fOutputList) {delete fOutputList;}
    if(fMuonTrackCuts) {delete fMuonTrackCuts;}
    if(fAnaTree) {delete fAnaTree;}
    if(fCounterH) {delete fCounterH;}
    if(fMuonTrackCounterH) {delete fMuonTrackCounterH;}
    if(fTriggerCounterFwdH) {delete fTriggerCounterFwdH;}
    if(fGoodTrkFwdH) {delete fGoodTrkFwdH;}

}
//_____________________________________________________________________________
void AliAnalysisTaskNanoJPsi2016Fwd::UserCreateOutputObjects()
{
    // create output objects
    //
    // this function is called ONCE at the start of your analysis (RUNTIME)

  ////////////////////////////////////////
  //muon track cuts
  ////////////////////////////////////////
  fMuonTrackCuts = new AliMuonTrackCuts("StdMuonCuts", "StdMuonCuts");

  fMuonTrackCuts->SetFilterMask(AliMuonTrackCuts::kMuEta | AliMuonTrackCuts::kMuThetaAbs
				| AliMuonTrackCuts::kMuPdca
        | AliMuonTrackCuts::kMuMatchLpt
      );
  /*
  fMuonTrackCuts->SetFilterMask(AliMuonTrackCuts::kMuEta | AliMuonTrackCuts::kMuThetaAbs
				| AliMuonTrackCuts::kMuMatchLpt);
  */
  fMuonTrackCuts->SetAllowDefaultParams(kTRUE);
  fMuonTrackCuts->Print("mask");
  fMuonTrackCuts->SetIsMC();

  ////////////////////////////////////////
  //output tree
  ////////////////////////////////////////
  fAnaTree = new TTree("fOutputTree", "fOutputTree");
  fAnaTree ->Branch("fRunNum", &fRunNum, "fRunNum/I");
  fAnaTree ->Branch("fL0inputs", &fL0inputs, "fL0inputs/i");
  // fAnaTree ->Branch("fAnaType", &fAnaType, "fAnaType/I");
  // fAnaTree ->Branch("fGoodPosTrk", &fGoodPosTrk, "fGoodPosTrk/I");
  // fAnaTree ->Branch("fGoodNegTrk", &fGoodNegTrk, "fGoodNegTrk/I");
  fAnaTree ->Branch("fTrkTrkPt", &fTrkTrkPt, "fTrkTrkPt/D");
  // fAnaTree ->Branch("fTrkTrkPhi", &fTrkTrkPhi, "fTrkTrkPhi/D");
  fAnaTree ->Branch("fTrkTrkY", &fTrkTrkY, "fTrkTrkY/D");
  fAnaTree ->Branch("fTrkTrkM", &fTrkTrkM, "fTrkTrkM/D");




  fAnaTree ->Branch("fV0ADecision",   &fV0ADecision,   "fV0ADecision/I");
  fAnaTree ->Branch("fV0CDecision",   &fV0CDecision,   "fV0CDecision/I");
  fAnaTree ->Branch("fADADecision",   &fADADecision,   "fADADecision/I");
  fAnaTree ->Branch("fADCDecision",   &fADCDecision,   "fADCDecision/I");
  fAnaTree ->Branch("fV0TotalNCells", &fV0TotalNCells, "fV0TotalNCells/I");



  // fAnaTree ->Branch("fTrkPt1", &fTrkPt1, "fTrkPt1/D");
  // fAnaTree ->Branch("fTrkPt2", &fTrkPt2, "fTrkPt2/D");
  fAnaTree ->Branch("fTrkEta1", &fTrkEta1, "fTrkEta1/D");
  fAnaTree ->Branch("fTrkEta2", &fTrkEta2, "fTrkEta2/D");
  // fAnaTree ->Branch("fTrkPhi1", &fTrkPhi1, "fTrkPhi1/D");
  // fAnaTree ->Branch("fTrkPhi2", &fTrkPhi2, "fTrkPhi2/D");
  // fAnaTree ->Branch("fTrkQ1", &fTrkQ1, "fTrkQ1/D");
  // fAnaTree ->Branch("fTrkQ2", &fTrkQ2, "fTrkQ2/D");
  // fAnaTree ->Branch("fTrkRabs1", &fTrkRabs1, "fTrkRabs1/D");
  // fAnaTree ->Branch("fTrkRabs2", &fTrkRabs2, "fTrkRabs2/D");
  // not needed in MC
  /*
  fAnaTree ->Branch("fTracklets", &fTracklets, "fTracklets/I");
  fAnaTree ->Branch("fZNAfired", &fZNAfired, "fZNAfired/O");
  fAnaTree ->Branch("fZNCfired", &fZNCfired, "fZNCfired/O");
  fAnaTree ->Branch("fZNCEnergy", &fZNCEnergy, "fZNCEnergy/D");
  fAnaTree ->Branch("fZNAEnergy", &fZNAEnergy, "fZNAEnergy/D");
  fAnaTree ->Branch("fZPCEnergy", &fZPCEnergy, "fZPCEnergy/D");
  fAnaTree ->Branch("fZPAEnergy", &fZPAEnergy, "fZPAEnergy/D");
  fAnaTree ->Branch("fZNATDC", &fZNATDC[0], "fZNATDC[4]/D");
  fAnaTree ->Branch("fZNCTDC", &fZNCTDC[0], "fZNCTDC[4]/D");
  fAnaTree ->Branch("fZPATDC", &fZPATDC[0], "fZPATDC[4]/D");
  fAnaTree ->Branch("fZPCTDC", &fZPCTDC[0], "fZPCTDC[4]/D");
  fAnaTree ->Branch("fV0ADecision", &fV0ADecision, "fV0ADecision/I");
  fAnaTree ->Branch("fV0CDecision", &fV0CDecision, "fV0CDecision/I");
  fAnaTree ->Branch("fV0ATime", &fV0ATime, "fV0ATime/D");
  fAnaTree ->Branch("fV0CTime", &fV0CTime, "fV0CTime/D");
  fAnaTree ->Branch("fV0AMultiplicity", &fV0AMultiplicity[0], "fV0AMultiplicity[32]/F");
  fAnaTree ->Branch("fV0CMultiplicity", &fV0CMultiplicity[0], "fV0CMultiplicity[32]/F");
  fAnaTree ->Branch("fADADecision", &fADADecision, "fADADecision/I");
  fAnaTree ->Branch("fADCDecision", &fADCDecision, "fADCDecision/I");
  fAnaTree ->Branch("fADATime", &fADATime, "fADATime/D");
  fAnaTree ->Branch("fADCTime", &fADCTime, "fADCTime/D");
  fAnaTree ->Branch("fADAMultiplicity", &fADAMultiplicity[0], "fADAMultiplicity[8]/F");
  fAnaTree ->Branch("fADCMultiplicity", &fADCMultiplicity[0], "fADCMultiplicity[8]/F");
  fAnaTree ->Branch("fIR1Map", &fIR1Map);
  fAnaTree ->Branch("fIR2Map", &fIR2Map);
  */
   // post data
  PostData(1, fAnaTree);

  ////////////////////////////////////////
  //output histograms
  ////////////////////////////////////////

  fOutputList = new TList();          // this is a list which will contain all  histograms
  fOutputList->SetOwner(kTRUE);       // memory stuff: the list is owner of all objects it contains and will delete them
  //  counter for events passing each cut
  fCounterH = new TH1F("fCounterH", "fCounterH", 25, -0.5, 24.5);
  fOutputList->Add(fCounterH);
  //  counter for tracks passing each cut
  fMuonTrackCounterH = new TH1F("fMuonTrackCounterH", "fMuonTrackCounterH", 10, -0.5, 9.5);
  fOutputList->Add(fMuonTrackCounterH);
   //  counter for triggers per run
  Int_t FirstRun = 1;
  Int_t LastRun = -1;
  if (fPeriod == 0 ) {FirstRun=265589;LastRun=266318;}// 16r
  else if (fPeriod == 1) {FirstRun=266405;LastRun=267131;}// 16s
  Int_t nRuns = LastRun-FirstRun+1;
  fTriggerCounterFwdH = new TH1F("fTriggerCounterFwdH", "fTriggerCounterFwdH", nRuns, FirstRun-0.5, LastRun+0.5);
  fOutputList->Add(fTriggerCounterFwdH);
  // number of good tracks in event
  fGoodTrkFwdH = new TH2F("fGoodTrkFwdH", "fGoodTrkFwdH", 10,-0.5,9.5,10,-0.5,9.5);
  fOutputList->Add(fGoodTrkFwdH);

  // post data
  PostData(2, fOutputList);

  ////////////////////////////////////////
  //MC tree at generator level
  ////////////////////////////////////////

  fAnaTreeMC = new TTree("fOutputTreeMC", "fOutputTreeMC");
  // // fAnaTreeMC ->Branch("fRunNum", &fRunNum, "fRunNum/I");
  fAnaTreeMC ->Branch("fMCTrkTrkPt", &fMCTrkTrkPt, "fMCTrkTrkPt/D");
  // // fAnaTreeMC ->Branch("fMCTrkTrkPhi", &fMCTrkTrkPhi, "fMCTrkTrkPhi/D");
  fAnaTreeMC ->Branch("fMCTrkTrkY", &fMCTrkTrkY, "fMCTrkTrkY/D");
  fAnaTreeMC ->Branch("fMCTrkTrkM", &fMCTrkTrkM, "fMCTrkTrkM/D");
  // // fAnaTreeMC ->Branch("fMCTrkPt1", &fMCTrkPt1, "fMCTrkPt1/D");
  // // fAnaTreeMC ->Branch("fMCTrkPt2", &fMCTrkPt2, "fMCTrkPt2/D");
  // // fAnaTreeMC ->Branch("fMCTrkEta1", &fMCTrkEta1, "fMCTrkEta1/D");
  // // fAnaTreeMC ->Branch("fMCTrkEta2", &fMCTrkEta2, "fMCTrkEta2/D");
  // // fAnaTreeMC ->Branch("fMCTrkPhi1", &fMCTrkPhi1, "fMCTrkPhi1/D");
  // // fAnaTreeMC ->Branch("fMCTrkPhi2", &fMCTrkPhi2, "fMCTrkPhi2/D");
  // // fAnaTreeMC ->Branch("fMCTrkQ1", &fMCTrkQ1, "fMCTrkQ1/I");
  // // fAnaTreeMC ->Branch("fMCTrkQ2", &fMCTrkQ2, "fMCTrkQ2/I");

  // post data
  PostData(3, fAnaTreeMC);

}
//_____________________________________________________________________________
void AliAnalysisTaskNanoJPsi2016Fwd::NotifyRun()
{
  /// Set run number for cuts
 fMuonTrackCuts->SetRun(fInputHandler);
}

//_____________________________________________________________________________
void AliAnalysisTaskNanoJPsi2016Fwd::SetPeriod(Int_t period)
{
  // period = 0 => 2016 s, = 1 => 2016 r
  fPeriod = period;
}

//_____________________________________________________________________________
void AliAnalysisTaskNanoJPsi2016Fwd::SetMC(Bool_t flag)
{
  // set if MC file
  fIsMC = flag;
}
//_____________________________________________________________________________
void AliAnalysisTaskNanoJPsi2016Fwd::TrkTrkKine(AliAODTrack *Track1, AliAODTrack *Track2, Double_t TrkMass)
{
  // --  positive track
  TLorentzVector PosLV;
  PosLV.SetPtEtaPhiM(Track1->Pt(), Track1->Eta(), Track1->Phi(), TrkMass);
  // --  negative track
  TLorentzVector NegLV;
  NegLV.SetPtEtaPhiM(Track2->Pt(), Track2->Eta(), Track2->Phi(), TrkMass);

  // vector of Trk+Trk
  TLorentzVector TrkTrk = NegLV+PosLV;

  // set tree variables
  fTrkTrkPt = TrkTrk.Pt();
  fTrkTrkPhi = TrkTrk.Phi();
  fTrkTrkY = TrkTrk.Rapidity();
  fTrkTrkM = TrkTrk.M();
  fTrkPt1 = Track1->Pt();
  fTrkPt2 = Track2->Pt();
  fTrkEta1 = Track1->Eta();
  fTrkEta2 = Track2->Eta();
  fTrkPhi1 = Track1->Phi();
  fTrkPhi2 = Track2->Phi();
  fTrkQ1 = Track1->Charge();
  fTrkQ2 = Track2->Charge();
  fTrkRabs1 = Track1->GetRAtAbsorberEnd();
  fTrkRabs2 = Track2->GetRAtAbsorberEnd();


}

//_____________________________________________________________________________

void AliAnalysisTaskNanoJPsi2016Fwd::CheckTrigger(Bool_t *isTriggered)
// checks if event is triggered according to period and analysis type
{
  // Initialise: 0 = fwd, 1 = cent, 2 = semi-fwd
  isTriggered[0] = isTriggered[1] = isTriggered[2] = kFALSE;

  // read trigger info
  TString trigger = fAOD->GetFiredTriggerClasses();

  // forward analysis
  // in 2016 r : CMUP14-B-NOPF-MUFAST = 0MSL *0VBA *0UBA
  // in 2016 s : CMUP23-B-NOPF-MUFAST = 0MUL *0UBC *0UGC *0VBA *0VGA *0SH2 *0VC5
  // central analysis
  // in 2016 r CCUP20-B-NOPF-CENTNOTRD = !VBA & !VGA & !VBC & !UBA & !UGC & !SH2 & STG & OMU
  // in 2016 s CCUP22-B-SPD2-CENTNOTRD = !VBA & !VGA & !VBC & !UBC & !UGC & !SH2 & STG & OMU
  // semi-forward analysis
  // in 2016 r CMUP15-B-NOPF-ALLNOTRD = *0VBA *0UBA *0VC5 0SMB *0SH2 0MSL
  // in 2016 s CMUP22-B-NOPF-ALLNOTRD = *0UBC *0UGC *0VBA *0VGA *0SH2 *0VC5 0MSL 0SMB
  if (fPeriod == 0) {
    if (trigger.Contains("CMUP14-B-NOPF-MUFAST")) isTriggered[0] = kTRUE;
    if (trigger.Contains("CCUP20-B-NOPF-CENTNOTRD")) isTriggered[1] = kTRUE;
    if (trigger.Contains("CMUP15-B-NOPF-ALLNOTRD")) isTriggered[2] = kTRUE;
  } else if (fPeriod == 1) {
    if (trigger.Contains("CMUP23-B-NOPF-MUFAST")) isTriggered[0] = kTRUE;
    if (trigger.Contains("CCUP22-B-SPD2-CENTNOTRD")) isTriggered[1] = kTRUE;
    if (trigger.Contains("CMUP22-B-NOPF-ALLNOTRD")) isTriggered[2] = kTRUE;
  }
}



//_____________________________________________________________________________

Bool_t AliAnalysisTaskNanoJPsi2016Fwd::GoodMUONTrack(Int_t iTrack)
// selects good MUON tracks
{
  fMuonTrackCounterH->Fill(0);
  AliAODTrack* track = static_cast<AliAODTrack*>(fAOD->GetTrack(iTrack));
  if(!track) return kFALSE;
  fMuonTrackCounterH->Fill(1);
  if(!track->IsMuonTrack())  return kFALSE;
  fMuonTrackCounterH->Fill(2);
  if(!fMuonTrackCuts->IsSelected(track))  return kFALSE;
  fMuonTrackCounterH->Fill(3);
  if(track->GetRAtAbsorberEnd()>89.5)  return kFALSE;
  fMuonTrackCounterH->Fill(4);
  if(track->GetRAtAbsorberEnd()<17.5)  return kFALSE;
  fMuonTrackCounterH->Fill(5);
  return kTRUE;
}

//_____________________________________________________________________________
void AliAnalysisTaskNanoJPsi2016Fwd::GetMCInfo()
{
  // get MC
  AliMCEvent *mc_data = dynamic_cast<AliMCEvent*>(MCEvent());
  if (!mc_data) {
    cout << "No MC data found" << endl;
    return;
  }

  // get MC particles
  fMCTrkQ1 = fMCTrkQ2 = 0;
  Int_t n_mcp = mc_data->GetNumberOfTracks();
  for(Int_t i_mcp = 0; i_mcp < n_mcp; i_mcp++) {
    AliMCParticle *mcp = static_cast<AliMCParticle*>(mc_data->GetTrack(i_mcp));
    if(!mcp) continue;
    // assuming that j/psi was not stored, so muons have no mother
    if (mcp->GetMother() == -1) {
      if (mcp->PdgCode() == 13) {
	fMCTrkPt1 = mcp->Pt();
	fMCTrkEta1 = mcp->Eta();
	fMCTrkPhi1 = mcp->Phi();
	fMCTrkQ1++;
      }
      if (mcp->PdgCode() == -13) {
	fMCTrkPt2 = mcp->Pt();
	fMCTrkEta2 = mcp->Eta();
	fMCTrkPhi2 = mcp->Phi();
	fMCTrkQ2++;
      }
    }
  }
  if (fMCTrkQ1==1 && fMCTrkQ2==1) {
    TLorentzVector PosLV;
    PosLV.SetPtEtaPhiM(fMCTrkPt1, fMCTrkEta1, fMCTrkPhi1, gMuonMass);
    TLorentzVector NegLV;
    NegLV.SetPtEtaPhiM(fMCTrkPt2, fMCTrkEta2, fMCTrkPhi2, gMuonMass);
    TLorentzVector TrkTrk = NegLV+PosLV;
    fMCTrkTrkPt = TrkTrk.Pt();
    fMCTrkTrkPhi = TrkTrk.Phi();
    fMCTrkTrkY = TrkTrk.Rapidity();
    fMCTrkTrkM = TrkTrk.M();
  } else {
    fMCTrkTrkPt = -1;
    fMCTrkTrkPhi = -999;
    fMCTrkTrkY = -999;
    fMCTrkTrkM = -1;
  }

  // fill the tree and post it
  fAnaTreeMC->Fill();
  PostData(3, fAnaTreeMC);
}

//_____________________________________________________________________________
void AliAnalysisTaskNanoJPsi2016Fwd::UserExec(Option_t *)
{

  fTrkTrkPt = -999.;
  fTrkTrkPhi = -999.;
  fTrkTrkY = -999.;
  fTrkTrkM = -999.;
  fTrkPt1 = -999.;
  fTrkPt2 = -999.;
  fTrkEta1 = -999.;
  fTrkEta2 = -999.;
  fTrkPhi1 = -999.;
  fTrkPhi2 = -999.;
  fMCTrkTrkPt = -999.;
  fMCTrkTrkPhi = -999.;
  fMCTrkTrkY = -999.;
  fMCTrkTrkM = -999.;
  fMCTrkPt1 = -999.;
  fMCTrkPt2 = -999.;
  fMCTrkEta1 = -999.;
  fMCTrkEta2 = -999.;
  fMCTrkPhi1 = -999.;
  fMCTrkPhi2 = -999.;
  fTrkQ1 = -999.;
  fTrkQ2 = -999.;
  fTrkRabs1 = -999.;
  fTrkRabs2 = -999.;

  ////////////////////////////////////////////
  // general info of the event
  ////////////////////////////////////////////
  Int_t iSelectionCounter = 0; // no selection applied yet
  fCounterH->Fill(iSelectionCounter); // entering UserExec
  iSelectionCounter++;

  // get AOD event
  fAOD = dynamic_cast<AliAODEvent*>(InputEvent());
  if(!fAOD) {
    PostData(1, fAnaTree);
    PostData(2, fOutputList);
    return;
  }
  fCounterH->Fill(iSelectionCounter); // AOD event found
  iSelectionCounter++;

  // get the run number
  fRunNum = fAOD ->GetRunNumber();

  // is the right trigger?
  Bool_t isTriggered[3];
  isTriggered[0]=isTriggered[1]=isTriggered[2]=kFALSE;
  if (fIsMC) {
    isTriggered[0] = kTRUE;
    GetMCInfo();
  } else {
    CheckTrigger(isTriggered);
  }
  if (!isTriggered[0]) {
    PostData(1, fAnaTree);
    PostData(2, fOutputList);
    fAnaTree->Fill();
    return;
  }
  fCounterH->Fill(iSelectionCounter); // right trigger found
  iSelectionCounter++;
  // trigger inputs
  fL0inputs = fAOD->GetHeader()->GetL0TriggerInputs();

  if (isTriggered[0]) fTriggerCounterFwdH->Fill(fRunNum);

  ////////////////////////////////////////////
  //  find events with two good tracks
  ////////////////////////////////////////////

  //are there tracks at all?
  Int_t nTracks(fAOD->GetNumberOfTracks());
  if(nTracks<1) {
    PostData(1, fAnaTree);
    PostData(2, fOutputList);
    fAnaTree->Fill();
    return;
  }
  fCounterH->Fill(iSelectionCounter); // At least one track
  iSelectionCounter++;

  // loop over tracks and select good muons
  Int_t nGoodPosTrk = 0;
  Int_t nGoodNegTrk = 0;
  Int_t *idxPosTrk = new Int_t[nTracks];
  Int_t *idxNegTrk = new Int_t[nTracks];
  Int_t nGoodMUON = 0;

  for(Int_t iTrack(0); iTrack < nTracks; iTrack++) {
    // initialise
    Bool_t isGoodMUON = kFALSE;

    // check if it is muon, if not check if it is central
    isGoodMUON = GoodMUONTrack(iTrack);

    // if valid track
    if (isGoodMUON) {
      nGoodMUON++; // update counter
      AliAODTrack* track = static_cast<AliAODTrack*>(fAOD->GetTrack(iTrack));
      // set charge, increase counter and store indices
      if (track->Charge() > 0) {
	idxPosTrk[nGoodPosTrk] = iTrack;
	nGoodPosTrk++;
      } else  if (track->Charge() < 0) {
	idxNegTrk[nGoodNegTrk] = iTrack;
	nGoodNegTrk++;
      }
    }
  }

  // fill in number of good tracks
  fGoodPosTrk = nGoodPosTrk;
  fGoodNegTrk = nGoodNegTrk;
  if (isTriggered[0]) fGoodTrkFwdH->Fill(nGoodPosTrk,nGoodNegTrk);

  ////////////////////////////////////////////
  // two track analysis
  ////////////////////////////////////////////

  // set type of analysis
  fAnaType = -1;
  if (isTriggered[0] && (nGoodMUON == 2)) fAnaType = 0;

  // check valid analysis type
  if ( fAnaType == -1 ) {
    PostData(1, fAnaTree);
    PostData(2, fOutputList);
    fAnaTree->Fill();
    delete [] idxNegTrk;
    delete [] idxPosTrk;
    return;
  }
  fCounterH->Fill(iSelectionCounter); // valid analysis
  iSelectionCounter++;

  // compute trk+trk kinematics
  AliAODTrack *Track1 = NULL;
  AliAODTrack *Track2 = NULL;
  if (nGoodPosTrk == 1 && nGoodNegTrk == 1) { // exactly one positive and one negative track
    fCounterH->Fill(iSelectionCounter);
    iSelectionCounter++;
    Track1 = static_cast<AliAODTrack*>(fAOD->GetTrack(idxPosTrk[0]));
    Track2 = static_cast<AliAODTrack*>(fAOD->GetTrack(idxNegTrk[0]));
  } else if (nGoodPosTrk == 2 && nGoodNegTrk == 0) { //two positive  tracks
    Track1 = static_cast<AliAODTrack*>(fAOD->GetTrack(idxPosTrk[0]));
    Track2 = static_cast<AliAODTrack*>(fAOD->GetTrack(idxPosTrk[1]));
  } else if (nGoodPosTrk == 0 && nGoodNegTrk == 2) { //two positive  tracks
    Track1 = static_cast<AliAODTrack*>(fAOD->GetTrack(idxNegTrk[0]));
    Track2 = static_cast<AliAODTrack*>(fAOD->GetTrack(idxNegTrk[1]));
  }
  TrkTrkKine(Track1,Track2,gMuonMass);

  // clean up
  delete [] idxNegTrk;
  delete [] idxPosTrk;












  // V0
  AliVVZERO *dataVZERO = dynamic_cast<AliVVZERO*>(fAOD->GetVZEROData());
  if(!dataVZERO) {
    PostData(1, fAnaTree);
    PostData(2, fOutputList);
    fAnaTree->Fill();
    return;
  }
  fV0ADecision = dataVZERO->GetV0ADecision();
  fV0CDecision = dataVZERO->GetV0CDecision();
  // check AD
  AliVAD *dataAD = dynamic_cast<AliVAD*>(fAOD->GetADData());
  if(!dataAD){
    PostData(1, fAnaTree);
    PostData(2, fOutputList);
    fAnaTree->Fill();
    return;
  }
  fADADecision = dataAD->GetADADecision();
  fADCDecision = dataAD->GetADCDecision();






  fV0TotalNCells = 0;
  for(Int_t iV0Hits = 0; iV0Hits < 64; iV0Hits++) {
        fV0Hits[iV0Hits] = dataVZERO->GetBBFlag(iV0Hits);
        if(fV0Hits[iV0Hits] == kTRUE) {
              fV0TotalNCells += 1;
        }
  }













  /*
  ////////////////////////////////////////////
  // info to determine exclusivity
  ////////////////////////////////////////////

  //  SPD
  fTracklets = fAOD->GetTracklets()->GetNumberOfTracklets();

  //  ZDC
  AliAODZDC *dataZDC = dynamic_cast<AliAODZDC*>(fAOD->GetZDCData());
  if(!dataZDC) {
    PostData(1, fAnaTree);
    PostData(2, fOutputList);
    return;
  }
  fCounterH->Fill(iSelectionCounter); // ZDC info is present
  iSelectionCounter++;
  fZNAfired = dataZDC->IsZNAfired();
  fZNCfired = dataZDC->IsZNCfired();
  fZNAEnergy = dataZDC->GetZNATowerEnergy()[0];
  fZNCEnergy = dataZDC->GetZNCTowerEnergy()[0];
  fZPAEnergy = dataZDC->GetZPATowerEnergy()[0];
  fZPCEnergy = dataZDC->GetZPCTowerEnergy()[0];
  for (Int_t i=0;i<4;i++) fZNATDC[i] = dataZDC->GetZNATDCm(i);
  for (Int_t i=0;i<4;i++) fZNCTDC[i] = dataZDC->GetZNCTDCm(i);
  for (Int_t i=0;i<4;i++) fZPATDC[i] = dataZDC->GetZPATDCm(i);
  for (Int_t i=0;i<4;i++) fZPCTDC[i] = dataZDC->GetZPCTDCm(i);

  // V0
  AliVVZERO *dataVZERO = dynamic_cast<AliVVZERO*>(fAOD->GetVZEROData());
  if(!dataVZERO) {
    PostData(1, fAnaTree);
    PostData(2, fOutputList);
    return;
  }
  fCounterH->Fill(iSelectionCounter); //  V0 info
  iSelectionCounter++;
  fV0ADecision = dataVZERO->GetV0ADecision();
  fV0CDecision = dataVZERO->GetV0CDecision();
  fV0ATime = dataVZERO->GetV0ATime();
  fV0CTime = dataVZERO->GetV0CTime();
  for(Int_t i=0;i<32;i++) {
    fV0AMultiplicity[i] = dataVZERO->GetMultiplicityV0A(i);
    fV0CMultiplicity[i] = dataVZERO->GetMultiplicityV0C(i);
  }

  //virtual Bool_t   GetPFBBFlag(Int_t channel, Int_t clock) const { return fIsBB[channel][clock]; }
  //virtual Bool_t   GetPFBGFlag(Int_t channel, Int_t clock) const { return fIsBG[channel][clock]; }
  //Bool_t   fIsBB[64][21];  ///< 'Beam-Beam' flag for all channels and 21 clocks
  //Bool_t   fIsBG[64][21];  ///< 'Beam-Gas' flag for all channels and 21 clocks


  // check AD
  AliVAD *dataAD = dynamic_cast<AliVAD*>(fAOD->GetADData());
  if(!dataAD){
    PostData(1, fAnaTree);
    PostData(2, fOutputList);
    return;
  }
  fCounterH->Fill(iSelectionCounter); //  AD info
  iSelectionCounter++;
  fADADecision = dataAD->GetADADecision();
  fADCDecision = dataAD->GetADCDecision();
  fADATime = dataAD->GetADATime();
  fADCTime = dataAD->GetADCTime();
  for(Int_t i=0;i<8;i++) {
    fADAMultiplicity[i] = dataAD->GetMultiplicityADA(i);
    fADCMultiplicity[i] = dataAD->GetMultiplicityADC(i);
  }

  //virtual Bool_t   GetPFBBFlag(Int_t channel, Int_t clock) const { return fIsBB[channel][clock]; }
  //  virtual Bool_t   GetPFBGFlag(Int_t channel, Int_t clock) const { return fIsBG[channel][clock]; }
  //Bool_t   fIsBB[16][21];  ///< BB flag for all channels and 21 clocks
  //Bool_t   fIsBG[16][21];  ///< BG flag for all channels and 21 clocks


  //Past-future protection maps
  fIR1Map = fAOD->GetHeader()->GetIRInt1InteractionMap();
  fIR2Map = fAOD->GetHeader()->GetIRInt2InteractionMap();
   */
  // fill the tree
  fAnaTree->Fill();

  // post the data
  PostData(1, fAnaTree);
  PostData(2, fOutputList);

}
//_____________________________________________________________________________
void AliAnalysisTaskNanoJPsi2016Fwd::Terminate(Option_t *)
{
    cout << endl;
    // terminate
    // called at the END of the analysis (when all events are processed)
}
//_____________________________________________________________________________
