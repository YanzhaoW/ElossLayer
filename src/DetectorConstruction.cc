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
/// \file electromagnetic/TestEm18/src/DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),worldPV(0), worldLV(0), 
 fDetectorMessenger(0),fLayerName(""), fLayerMat("")
{
  DefineMaterials();
  fDetectorMessenger = new DetectorMessenger(this);
}


DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}


void DetectorConstruction::DefineMaterials()
{
  // define materials
  G4NistManager* nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Mn");

  G4double z,a,density;
  new G4Material("Galactic", 1, 1.01 * g / mole, CLHEP::universe_mean_density, kStateGas, 2.73 * kelvin, 3.e-18 * pascal);
  new G4Material("Aluminium"  , z=13., a= 26.98*g/mole, density= 2.700*g/cm3);
  new G4Material("Yb-170", z=70., a=170.0 * g/mole, density = 170.0/173.045*6.9*g/cm3);
  new G4Material("Yb-172", z=70., a=172.0 * g/mole, density = 172.0/173.045*6.9*g/cm3);
                 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{

  // World
  const G4double worldSizeXYZ = 5. * m / 2;
  auto worldS = new G4Box("World", worldSizeXYZ, worldSizeXYZ, worldSizeXYZ);
  worldLV = new G4LogicalVolume(worldS, G4Material::GetMaterial("Galactic"), "World");
  worldLV->SetVisAttributes(G4VisAttributes::Invisible);

  // Addlayer("Mn","G4_Mn", 0.998e-3*mm);
  // Addlayer("Yb-172","Yb-172", 0.4e-3*mm);
  // Addlayer("Al","Aluminium", 7e-3*mm);

 G4cout <<"++++++++++++++++++----------------------" << G4endl;
  worldPV = new G4PVPlacement(nullptr, G4ThreeVector(), worldLV, "World", nullptr, false, 0, fCheckOverlaps);
  return worldPV;
}

void DetectorConstruction::Addlayer(G4String name, G4String pMaterial, G4double thickness){
  fLayerName = name;
  fLayerMat = pMaterial;
  Addlayer(thickness);
}

void DetectorConstruction::Addlayer(G4double thickness){
  G4cout << "thickness: "<<thickness <<G4endl;
  G4cout << "material: "<<fLayerMat <<G4endl;
  auto layerS = new G4Box("layer", 2*cm, 2*cm, thickness/2);
  auto layerLV = new G4LogicalVolume(layerS, G4Material::GetMaterial(fLayerMat), "layer");
  layerLV->SetVisAttributes(G4VisAttributes(true));
  layer_count++;
  fPos += thickness/2;
  new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, fPos),
                  layerLV, fLayerName, worldLV, false, 0, fCheckOverlaps);
  fPos += thickness/2;
  LayerNames.push_back(fLayerName); 
  UpdateGeometry();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetSize(){
  return 5.0*m/2;
}      

G4Material* DetectorConstruction::GetMaterial(){
  return G4Material::GetMaterial("Galactic");
}