/*########################################################*\
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "G4Timer.hh"

#include "GeRunAction.hh"
#include "GeDetectorConstruction.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "Randomize.hh"
#include "G4HCofThisEvent.hh"

#include "GeEventAction.hh"

GeRunAction::GeRunAction() : G4UserRunAction(), fTimer(0)
{
    fTimer = new G4Timer;
  // automatic (time-based) random seeds for each run
     G4cout << "*******************" << G4endl;
     G4cout << "*** AUTOSEED ON ***" << G4endl;
     G4cout << "*******************" << G4endl;
     //long seeds[1];
     time_t systime = time(NULL);
     //seeds[0] = (long) systime;
     G4Random::showEngineStatus();

     // Create analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetDefaultFileType("root");
    //analysisManager->SetFileName("geiger137.root");

    analysisManager->CreateNtuple("CIGE","CIGE");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->FinishNtuple(0);
    /*
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi");
    analysisManager->CreateNtupleDColumn("u");
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->CreateNtupleDColumn("Parent");
    analysisManager->CreateNtupleDColumn("TrackID");
    analysisManager->FinishNtuple(0);
    */

    analysisManager->CreateNtuple("AIGE","AIGE");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->FinishNtuple(1);
/*
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi");
    analysisManager->CreateNtupleDColumn("u");
    analysisManager->CreateNtupleDColumn("E");
*/ 

    analysisManager->CreateNtuple("GE","GE");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->FinishNtuple(2);
/*
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi");
    analysisManager->CreateNtupleDColumn("u");
    analysisManager->CreateNtupleDColumn("E");
*/

    analysisManager->CreateNtuple("WICG","WICG");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->FinishNtuple(3);
    /*
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi");
    analysisManager->CreateNtupleDColumn("u");
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->CreateNtupleDColumn("l");
    
*/
    analysisManager->CreateNtuple("WICE","WICE");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->FinishNtuple(4);
 /*   
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi");
    analysisManager->CreateNtupleDColumn("u");
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->CreateNtupleDColumn("l");
    */
/*
    analysisManager->CreateNtuple("GasIntoCathodeGamma","GasIntoCathodeGamma");
    analysisManager->CreateNtupleDColumn("x");
    /*
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi");
    analysisManager->CreateNtupleDColumn("u");
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->CreateNtupleDColumn("l");
    
    analysisManager->FinishNtuple(5);

    analysisManager->CreateNtuple("CathodeIntoWorldGamma","CathodeIntoWorldGamma");
    analysisManager->CreateNtupleDColumn("x");
    /*
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi");
    analysisManager->CreateNtupleDColumn("u");
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->CreateNtupleDColumn("l");
    
    analysisManager->FinishNtuple(6);
    /*
    analysisManager->CreateNtuple("GasElectron","GasElectron");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi");
    analysisManager->CreateNtupleDColumn("u");
    analysisManager->CreateNtupleDColumn("E");  
    analysisManager->FinishNtuple(2);

    */
}


GeRunAction::~GeRunAction()
{
  delete fTimer;
}


void GeRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    fTimer->Start();

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile();
}


void GeRunAction::EndOfRunAction(const G4Run* aRun)
{
    fTimer->Stop();
    G4cout << "############################################################################" << G4endl;
    G4cout << "number of event = " << aRun->GetNumberOfEvent()
           << " " << *fTimer << G4endl;

    G4cout << "############################################################################" << G4endl;
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
