A simulation of the energy loss of impinging particles through multiple layers

## How to start

Execute the shell script 'launch.sh' with a macro file:
```sh
./launch.sh MARCO.mac
```

### Quick test

- Run `./launch.sh test.mac`

## How to write a macro file

There are three main parts in a macro file:

### 1. Initialization of basic process parameters
```
/control/cout/ignoreThreadsExcept 0
/control/verbose 2
/run/verbose 1

/run/setCut 100 um
/process/em/verbose 0
/process/em/printParameters
/run/initialize
```
This part should not be changed unless absolutely needed.

### 2. Configuration of layers
```
#adding layers here:

/layer/SetName Mn_1
/layer/SetMat G4_Mn
/layer/AddLayer 0.998e-3 mm

/layer/SetName 172Yb_1
/layer/SetMat G4_Mn
/layer/AddLayer 0.4e-3 mm

/layer/SetName Al_1
/layer/SetMat Aluminium
/layer/AddLayer 7e-3 mm

/layer/shift 2 mm

/layer/SetName Mn_2
/layer/SetMat G4_Mn
/layer/AddLayer 0.998e-3 mm

/layer/SetName 172Yb_2
/layer/SetMat G4_Mn
/layer/AddLayer 0.4e-3 mm

/layer/SetName Al_2
/layer/SetMat Aluminium
/layer/AddLayer 7e-3 mm

```
The example above shows 6 layers in total being added with specification of their layer names, materials and thicknesses. These parameters are added by using the three following commands:
* `/layer/SetName` : Set the name of the layer to be added next.
* `/layer/SetMat` : Specify the material of the layer to be added next. The input string must be defined in the class method `DetectorConstruction::DefineMaterials()` inside the file "./src/DetectorConstruction.cc".
* `/layer/AddLayer` : Set the thickness of the layer to be added next and add the layer to the geometry. The input parameter should be a number of type Double followed by a string for the lengh unit (either to be 'm', 'cm', 'mm' or 'um').

Different layers are added back to back with no separation distance. To specify the separation distance between the last added layer and the next one, use the comand:
* `/layer/shift` : The input parameter is of the same format as `/layer/AddLayer`.

### 3. Configuration of impinging particles and events
```
/gun/particle proton
/gun/energy 10 MeV
/run/printProgress 10000
/run/beamOn 100000
```
with commands:
* `/gun/particle`: Specify the type of the impinging particles, e.g. 'proton', 'alpha' or 'gamma'. For more information, please refer to [Using particle names](http://fismed.ciemat.es/GAMOS/GAMOS_doc/GAMOS.5.1.0/x11519.html).
* `/gun/energy`: Specify the energy of the impinging particles with a double type number and a unit.
* `/run/printProgress`: Print the progress for each certain amount of events.
* `/run/beamOn`: Specify the total number of events to be simulated.

## Results
The results are placed in the "./out/" folder. The initial results are stored as ROOT::TTree format in the file './out/output.root'. Then it is automatically converted into a .csv file by "root2csv.cc". The column names in the CSV file correspond to each layer added to the simulation and the values below represent the energy losses in unit of MeV.
