//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm18/src/DetectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:G4UImessenger(),fDetector(Det),
 fLayerDir(0),
 fSetLayerName(0),    
 fSetLayerMaterial(0),
 fAddLayer(0),
 fShiftDis(0),
 fUpdateCmd(0)
{ 
  fLayerDir = new G4UIdirectory("/layer/"); 
  fLayerDir->SetGuidance("configure geometry of layers");
    

  fSetLayerName = new G4UIcmdWithAString("/layer/SetName",this);
  fSetLayerName->SetGuidance("set the name of the layer.");
  fSetLayerName->SetParameterName("LayerName",false);
  fSetLayerName->AvailableForStates(G4State_PreInit,G4State_Idle);

  fSetLayerMaterial = new G4UIcmdWithAString("/layer/SetMat",this);
  fSetLayerMaterial->SetGuidance("set the mateiral of the layer.");
  fSetLayerMaterial->SetParameterName("LayerMat",false);
  fSetLayerMaterial->AvailableForStates(G4State_PreInit,G4State_Idle);

  fAddLayer = new G4UIcmdWithADoubleAndUnit("/layer/AddLayer", this);
  fAddLayer -> SetGuidance("add a layer to the geometry with thickness");
  fAddLayer -> SetParameterName("thickness", false);
  fAddLayer -> SetRange("thickness>0.");
  fAddLayer->SetUnitCategory("Length");
  fAddLayer->AvailableForStates(G4State_PreInit,G4State_Idle);

  fShiftDis = new G4UIcmdWithADoubleAndUnit("/layer/shift", this);
  fShiftDis -> SetGuidance("shift placement of layers with a distance");
  fShiftDis -> SetParameterName("dis", false);
  fShiftDis -> SetRange("dis>0.");
  fShiftDis->SetUnitCategory("Length");
  fShiftDis->AvailableForStates(G4State_PreInit,G4State_Idle);
    
  fUpdateCmd = new G4UIcmdWithoutParameter("/layer/update",this);
  fUpdateCmd->SetGuidance("Update calorimeter geometry.");
  fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  fUpdateCmd->SetGuidance("if you changed geometrical value(s).");
  fUpdateCmd->AvailableForStates(G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fUpdateCmd;
  delete fAddLayer;
  delete fSetLayerName;
  delete fSetLayerMaterial;
  delete fShiftDis;
  delete fLayerDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if( command == fAddLayer )
   { fDetector->Addlayer(fAddLayer->GetNewDoubleValue(newValue));}
   
  if( command == fSetLayerMaterial )
   { fDetector->SetLayerMat(newValue);}

  if( command == fSetLayerName )
   { fDetector->SetLayerName(newValue);}

  if( command == fShiftDis )
   { fDetector->ShiftPos(fShiftDis->GetNewDoubleValue(newValue));}
     
  if( command == fUpdateCmd )
   { fDetector->UpdateGeometry(); }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
