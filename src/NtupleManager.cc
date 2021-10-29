#include "NtupleManager.hh"
#include "G4UnitsTable.hh"
#include "RunAction.hh"
#include <vector>

NtupleManager::NtupleManager() : fFileName("output"){
}


NtupleManager::~NtupleManager()
{
  delete G4AnalysisManager::Instance();
}

void NtupleManager::ImportLayers(DetectorConstruction* det){
   LayerNames = det->GetLayerNames();
}

void NtupleManager::Book(){
   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   analysisManager->SetFileName(fFileName);
   analysisManager->SetVerboseLevel(1);
   
   analysisManager->CreateNtuple("Edep", "Energy depositions across multiple layers");
   G4cout << "number of layers: " << LayerNames.size()<< G4endl;
   for(const auto & Layer : LayerNames){
       G4cout <<"layer: " <<Layer << G4endl;
       analysisManager->CreateNtupleDColumn(Layer);
   }
   analysisManager->FinishNtuple();
}
