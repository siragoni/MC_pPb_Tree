//
// to run:
//   alienv enter version
//   alien-token-init
//   source /tmp/gclient_env_501
//   aliroot runNanoJPsi2016AnalysisFwd.C\(period\)


// include the header of your analysis task here!
#include "AliAnalysisTaskNanoJPsi2016Fwd.h"

void runAnalysis(Int_t period)
// period = 0 => 2016 r,
//        = 1 => 2016 s
{
  // set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
  // Bool_t local = kTRUE;
  Bool_t local = kFALSE;
  // if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
  // Bool_t gridTest = kTRUE;
  Bool_t gridTest = kFALSE;

    // since we will compile a class, tell root where to look for headers
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->ProcessLine(".include $ROOTSYS/include");
    gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
#else
    gROOT->ProcessLine(".include $ROOTSYS/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
#endif

    // create the analysis manager
    AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskNanoJPsi2016Fwd");
    AliAODInputHandler *aodH = new AliAODInputHandler();
    mgr->SetInputEventHandler(aodH);

    // compile the class and load the add task macro
    // here we have to differentiate between using the just-in-time compiler
    // from root6, or the interpreter of root5
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->LoadMacro("AliAnalysisTaskNanoJPsi2016Fwd.cxx++g");
    char txt_cmd[120];
    sprintf(txt_cmd,"AddNanoJPsi2016Fwd.C(%d)",period);
    AliAnalysisTaskNanoJPsi2016Fwd *task = reinterpret_cast<AliAnalysisTaskNanoJPsi2016Fwd*>(gInterpreter->ExecuteMacro(txt_cmd));
#else
    gROOT->LoadMacro("AliAnalysisTaskNanoJPsi2016Fwd.cxx++g");
    gROOT->LoadMacro("AddNanoJPsi2016Fwd.C");
    AliAnalysisTaskNanoJPsi2016Fwd *task = AddNanoJPsi2016Fwd(period);
#endif

    if(!mgr->InitAnalysis()) return;
    // mgr->SetDebugLevel(2);
    // mgr->PrintStatus();
    // mgr->SetUseProgressBar(1, 25);
    char tmpstr[120];
    if(local) {
        // if you want to run locally, we need to define some input
        TChain* chain = new TChain("aodTree");
        // add a few files to the chain (change this so that your local files are added)
	chain->Add("/Users/jgcn/Work/ALICE_Data/pPb2016/MCtest/AliAOD.root");
        // start the analysis locally, reading the events from the tchain
        mgr->StartAnalysis("local", chain);
    } else {
      // if we want to run on grid, we create and configure the plugin
        AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
        // also specify the include (header) paths on grid
        alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
        // make sure your source files get copied to grid
        alienHandler->SetAdditionalLibs("AliAnalysisTaskNanoJPsi2016Fwd.cxx AliAnalysisTaskNanoJPsi2016Fwd.h");
        alienHandler->SetAnalysisSource("AliAnalysisTaskNanoJPsi2016Fwd.cxx");
        // select the aliphysics version. all other packages
        // are LOADED AUTOMATICALLY!
        alienHandler->SetAliPhysicsVersion("vAN-20200526_ROOT6-1");
        // set the Alien API version
        alienHandler->SetAPIVersion("V1.1x");
        // select the input data
  // alienHandler->SetGridDataDir("/alice/sim/2017/LHC17e4_2/kIncohJpsiToMu");
	// alienHandler->SetGridDataDir("/alice/sim/2017/LHC17e4/kIncohJpsiToMu");
  alienHandler->SetGridDataDir("/alice/sim/2017/LHC17e4_2/kTwoGammaToMuLow");
  // alienHandler->SetGridDataDir("/alice/sim/2017/LHC17e4/kTwoGammaToMuLow");
  // alienHandler->SetGridDataDir("/alice/sim/2017/LHC17e4/kCohJpsiToMu");
	alienHandler->SetDataPattern("AOD/*/AliAOD.root");
	if (period == 0) {
	  // MC has no prefix, data has prefix 000
	  // alienHandler->SetRunPrefix("000");
	  // runnumber
  alienHandler->AddRunNumber(265589);
  alienHandler->AddRunNumber(265594);
  alienHandler->AddRunNumber(265596);
  alienHandler->AddRunNumber(265607);
  alienHandler->AddRunNumber(265669);
  alienHandler->AddRunNumber(265691);
  alienHandler->AddRunNumber(265694);
  alienHandler->AddRunNumber(265697);
  alienHandler->AddRunNumber(265698);
  alienHandler->AddRunNumber(265700);
  alienHandler->AddRunNumber(265701);
  alienHandler->AddRunNumber(265709);
  alienHandler->AddRunNumber(265713);
  alienHandler->AddRunNumber(265714);
  alienHandler->AddRunNumber(265740);
  alienHandler->AddRunNumber(265741);
  alienHandler->AddRunNumber(265742);
  alienHandler->AddRunNumber(265744);
  alienHandler->AddRunNumber(265746);
  alienHandler->AddRunNumber(265754);
  alienHandler->AddRunNumber(265756);
  alienHandler->AddRunNumber(265785);
  alienHandler->AddRunNumber(265787);
  alienHandler->AddRunNumber(265788);
  alienHandler->AddRunNumber(265789);
  alienHandler->AddRunNumber(265792);
  alienHandler->AddRunNumber(265795);
  alienHandler->AddRunNumber(265797);
  alienHandler->AddRunNumber(265840);
  alienHandler->AddRunNumber(266022);
  alienHandler->AddRunNumber(266023);
  alienHandler->AddRunNumber(266025);
  alienHandler->AddRunNumber(266034);
  alienHandler->AddRunNumber(266074);
  alienHandler->AddRunNumber(266076);
  alienHandler->AddRunNumber(266081);
  alienHandler->AddRunNumber(266084);
  alienHandler->AddRunNumber(266085);
  alienHandler->AddRunNumber(266086);
  alienHandler->AddRunNumber(266117);
  alienHandler->AddRunNumber(266187);
  alienHandler->AddRunNumber(266189);
  alienHandler->AddRunNumber(266190);
  alienHandler->AddRunNumber(266193);
  alienHandler->AddRunNumber(266196);
  alienHandler->AddRunNumber(266197);
  alienHandler->AddRunNumber(266208);
  alienHandler->AddRunNumber(266234);
  alienHandler->AddRunNumber(266235);
  alienHandler->AddRunNumber(266296);
  alienHandler->AddRunNumber(266299);
  alienHandler->AddRunNumber(266300);
  alienHandler->AddRunNumber(266304);
  alienHandler->AddRunNumber(266305);
  alienHandler->AddRunNumber(266312);
  alienHandler->AddRunNumber(266316);
  alienHandler->AddRunNumber(266318);
	  // working dir
	  alienHandler->SetGridWorkingDir("LHC16r_Gamma_low4");
	  alienHandler->SetExecutable("LHC16r_Task.sh");
	  alienHandler->SetJDLName("LHC16r_Task.jdl");
	}  else if (period == 1) {
	  // MC has no prefix, data has prefix 000
	  //  alienHandler->SetRunPrefix("000");
	  // runnumber
 alienHandler->AddRunNumber(266439);
  alienHandler->AddRunNumber(266441);
  alienHandler->AddRunNumber(266472);
  alienHandler->AddRunNumber(266479);
  alienHandler->AddRunNumber(266480);
  alienHandler->AddRunNumber(266487);
  alienHandler->AddRunNumber(266514);
  alienHandler->AddRunNumber(266516);
  alienHandler->AddRunNumber(266518);
  alienHandler->AddRunNumber(266520);
  alienHandler->AddRunNumber(266522);
  alienHandler->AddRunNumber(266523);
  alienHandler->AddRunNumber(266525);
  alienHandler->AddRunNumber(266533);
  alienHandler->AddRunNumber(266534);
  alienHandler->AddRunNumber(266539);
  alienHandler->AddRunNumber(266543);
  alienHandler->AddRunNumber(266549);
  alienHandler->AddRunNumber(266584);
  alienHandler->AddRunNumber(266587);
  alienHandler->AddRunNumber(266588);
  alienHandler->AddRunNumber(266591);
  alienHandler->AddRunNumber(266593);
  alienHandler->AddRunNumber(266595);
  alienHandler->AddRunNumber(266613);
  alienHandler->AddRunNumber(266614);
  alienHandler->AddRunNumber(266618);
  alienHandler->AddRunNumber(266621);
  alienHandler->AddRunNumber(266630);
  alienHandler->AddRunNumber(266657);
  alienHandler->AddRunNumber(266658);
  alienHandler->AddRunNumber(266659);
  alienHandler->AddRunNumber(266665);
  alienHandler->AddRunNumber(266668);
  alienHandler->AddRunNumber(266669);
  alienHandler->AddRunNumber(266674);
  alienHandler->AddRunNumber(266676);
  alienHandler->AddRunNumber(266702);
  alienHandler->AddRunNumber(266703);
  alienHandler->AddRunNumber(266706);
  alienHandler->AddRunNumber(266708);
  alienHandler->AddRunNumber(266775);
  alienHandler->AddRunNumber(266776);
  alienHandler->AddRunNumber(266800);
  alienHandler->AddRunNumber(266805);
  alienHandler->AddRunNumber(266807);
  alienHandler->AddRunNumber(266857);
  alienHandler->AddRunNumber(266878);
  alienHandler->AddRunNumber(266880);
  alienHandler->AddRunNumber(266882);
  alienHandler->AddRunNumber(266883);
  alienHandler->AddRunNumber(266885);
  alienHandler->AddRunNumber(266886);
  alienHandler->AddRunNumber(266912);
  alienHandler->AddRunNumber(266915);
  alienHandler->AddRunNumber(266940);
  alienHandler->AddRunNumber(266942);
  alienHandler->AddRunNumber(266943);
  alienHandler->AddRunNumber(266944);
  alienHandler->AddRunNumber(266988);
  alienHandler->AddRunNumber(266993);
  alienHandler->AddRunNumber(266994);
  alienHandler->AddRunNumber(266997);
  alienHandler->AddRunNumber(266998);
  alienHandler->AddRunNumber(267020);
  alienHandler->AddRunNumber(267022);
  alienHandler->AddRunNumber(267062);
  alienHandler->AddRunNumber(267063);
  alienHandler->AddRunNumber(267067);
  alienHandler->AddRunNumber(267070);
  alienHandler->AddRunNumber(267072);
  alienHandler->AddRunNumber(267077);
  alienHandler->AddRunNumber(267109);
  alienHandler->AddRunNumber(267110);
  alienHandler->AddRunNumber(267130);
  alienHandler->AddRunNumber(267131);
	  // working dir
	  alienHandler->SetGridWorkingDir("LHC16s_Incoh_new");
	  alienHandler->SetExecutable("LHC16s_Task.sh");
	  alienHandler->SetJDLName("LHC16s_Task.jdl");
	}  else {
	  cout << " not a valid option ... bye!" << endl;
	  return;
	}

        // number of files per subjob
        alienHandler->SetSplitMaxInputFileNumber(20);
        // specify how many seconds your job may take
        alienHandler->SetTTL(10000);
        alienHandler->SetOutputToRunNo(kTRUE);
        alienHandler->SetKeepLogs(kTRUE);
        // merging: run with "kTRUE" and "full" for normal run
        // to merge on grid run jobs in SetRunMode("terminate")
        // to collect final results set SetMergeViaJDL(kFALSE)
        alienHandler->SetMaxMergeStages(2);
        // alienHandler->SetMergeViaJDL(kFALSE);
        alienHandler->SetMergeViaJDL(kTRUE);
        // define the output folders
        alienHandler->SetGridOutputDir("MyOutputDir");
        // connect the alien plugin to the manager
        mgr->SetGridHandler(alienHandler);

        if(gridTest) {
            // speficy on how many files you want to run
            alienHandler->SetNtestFiles(1);
            // and launch the analysis
            alienHandler->SetRunMode("test");
            mgr->StartAnalysis("grid");
        } else {
	  // else launch the full grid analysis
	  alienHandler->SetRunMode("full");
	  // alienHandler->SetRunMode("terminate");
	  mgr->StartAnalysis("grid");
        }
    }
}

/*
running in lxplus:
Welcome my dear ALICE user! To use ALICE software from CVMFS:
 * List all packages         --> alienv q
 * List AliPhysics packages  --> alienv q | grep -i aliphysics
 * Enable a specific package --> alienv enter VO_ALICE@AliPhysics::vAN-20190114_ROOT6-1
 * Enable multiple packages  --> alienv enter VO_ALICE@AliPhysics::vAN-20190114_ROOT6-1,VO_ALICE@fastjet::v3.2.1_1.024-alice3-7
 */

/*
cd AliceWork/pass1_UD/
alienv enter VO_ALICE@AliPhysics::vAN-20191015_ROOT6-1
alien-token-init
source /tmp/gclient_env_3582
aliroot runNanoJPsi2016Analysis.C\(period\)
 */
