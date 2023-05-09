/*########################################################*\
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "G4GenericMessenger.hh"
#include "GeDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

using namespace std;

GeDetectorConstruction::GeDetectorConstruction() : G4VUserDetectorConstruction()
{ 
   fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construiction");
 //  auto& setWallThickCmd = fMessenger->DeclareMethod("setWallThick", &GeDetectorConstruction:: SetWallThick, "Set Detector Wall Thick");
 // setWallThickCmd.SetUnit("mm");

 //  auto& setPosCmd = fMessenger->DeclareMethod("setPosition", &GeDetectorConstruction:: SetStopPosition, "Should be + 0.5 cm from source");
 //  setPosCmd.SetUnit("mm");
   detWallThick = 0.1 * mm;
   stopPosition = 55 * mm;
   G4cout << detWallThick << G4endl;
   DefineMaterials();

}

GeDetectorConstruction::~GeDetectorConstruction()
{
   delete fMessenger;
}

void GeDetectorConstruction::DefineMaterials()
{
   G4NistManager *nist = G4NistManager::Instance();

   world_mat = nist->FindOrBuildMaterial("G4_AIR");
   gas_mat = nist->FindOrBuildMaterial("G4_Ar");
   tube_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
   frame_mat = nist->FindOrBuildMaterial("G4_Al");
}

G4VPhysicalVolume *GeDetectorConstruction::Construct()
{
   G4double worldSize = 40 * cm;
   G4double detLength = 150. * mm;
   G4double detInnerRad = 10 * mm;
   // detWallThick = 0.0625 * mm; // 50 mg/cm^2 from the web
   G4double anodeDia = 0.75 * mm;
   G4double blockThick = 21 * mm;
   G4double frameRad = 20 * mm; 
   G4double frameThick = 1 * mm;
   G4double frameLenght = 200 * mm;

   worldSol = new G4Box("World", worldSize, worldSize, worldSize);
   worldLog = new G4LogicalVolume(worldSol, world_mat, "World");
   worldPhys = new G4PVPlacement(0,
                                                    G4ThreeVector(),
                                                    worldLog,
                                                    "World",
                                                    0,
                                                    false,
                                                    0);

   stopSol = new G4Box("Stop", worldSize, detWallThick, worldSize);
   stopLog = new G4LogicalVolume(stopSol, world_mat, "Stop");
 //  stopPhys = new G4PVPlacement(0, G4ThreeVector(0, 5.5*cm, 0), stopLog, "Stop", worldLog, false,0);

   detTubeSol = new G4Tubs("geigerTube", detInnerRad, detInnerRad + detWallThick,
                                   detLength / 2., 0, 360 * deg);
   detTubeLog = new G4LogicalVolume(detTubeSol, tube_mat, "geigerTube");
   detTubePhys = new G4PVPlacement(0,
                                                      G4ThreeVector(),
                                                      detTubeLog,
                                                      "geigerTube",
                                                      worldLog,
                                                      false,
                                                      0);

   gasSol = new G4Tubs("gas", 0., detInnerRad, detLength / 2., 0, 360 * deg);
   gasLog = new G4LogicalVolume(gasSol, gas_mat, "gas");
   gasPhys = new G4PVPlacement(0,
                                                  G4ThreeVector(),
                                                  gasLog,
                                                  "gas",
                                                  worldLog,
                                                  false,
                                                  0);

   anodeTubeSol = new G4Tubs("anodeTube", 0 * mm, anodeDia / 2., detLength / 2., 0, 360 * deg);
   anodeTubeLog = new G4LogicalVolume(anodeTubeSol, tube_mat, "anodeTube");
   anodeTubePhys = new G4PVPlacement(0,
                                                        G4ThreeVector(),
                                                        anodeTubeLog,
                                                        "anodeTube",
                                                        gasLog,
                                                        false,
                                                        0);

   blockSol  = new G4Tubs("block", 0 * mm, detInnerRad + detWallThick, blockThick/2,0, 360* deg);
   blockLog = new G4LogicalVolume(blockSol, tube_mat, "block");
   G4double dy = detLength/2 + blockThick / 2;
   blockPhys1 = new G4PVPlacement(0, G4ThreeVector(0,0,dy), blockLog, "block",worldLog, false,0);
   blockPhys2 = new G4PVPlacement(0, G4ThreeVector(0,0,-dy), blockLog, "block",worldLog, false,0);
   
   frameSol = new G4Tubs("frameTube", frameRad, frameRad + frameThick, frameLenght, 0, 360* deg);
   frameLog = new G4LogicalVolume(frameSol, frame_mat,"frameTube");
   //framePhys = new G4PVPlacement(0,G4ThreeVector(), frameLog, "frameTube", worldLog, false,0);

   return worldPhys;
}

void GeDetectorConstruction::SetWallThick(G4double newValue)
{
   G4cout << newValue << G4endl;
   detWallThick = newValue * mm;
   G4cout << detWallThick << G4endl;

}

void GeDetectorConstruction::SetStopPosition(G4double Position)
{
   stopPosition = Position * mm;
}
