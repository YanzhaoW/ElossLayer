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
/// \file electromagnetic/TestEm18/include/DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <vector>

class G4LogicalVolume;
class G4Material;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
   ~DetectorConstruction();

  public:
  
  virtual G4VPhysicalVolume* Construct();
     

  void UpdateGeometry();
     
  public:
  
     const
     G4VPhysicalVolume* GetWorld()      {return worldPV;};           
                    
     G4double           GetSize();      
     G4Material*        GetMaterial();
     void Addlayer(G4String name, G4String pMaterial, G4double thickness);
     void Addlayer(G4double thickness);
     void ShiftPos(G4double dis) {fPos += dis;};
     std::vector<G4String> GetLayerNames() {return LayerNames;};
      void SetLayerName(G4String name) {fLayerName = name;};
      void SetLayerMat(G4String mat) {fLayerMat = mat;};
  private:
  
     G4VPhysicalVolume* worldPV;
     G4LogicalVolume*   worldLV;
     G4int layer_count = 0;
     DetectorMessenger* fDetectorMessenger;
     G4String fLayerName, fLayerMat;
     
     G4bool fCheckOverlaps=true;
     std::vector<G4String> LayerNames;

  private:
    
     void               DefineMaterials();
     G4VPhysicalVolume* ConstructVolumes();     
     G4double fPos = 0.0*mm;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif

