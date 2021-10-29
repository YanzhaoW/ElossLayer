#ifndef NtupleManager_h
#define NtupleManager_h 1

#include "globals.hh"
#include <vector>
#include "g4root.hh"
//#include "g4xml.hh"
class DetectorConstruction;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class NtupleManager
{
  public:
    NtupleManager();
    ~NtupleManager();
    void ImportLayers(DetectorConstruction* det);
    void Book();

  private:
    std::vector<G4String> LayerNames;
    G4String fFileName;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif