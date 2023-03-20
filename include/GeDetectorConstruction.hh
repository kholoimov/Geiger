/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

//#pragma once

#ifndef GeDetectorConstruction_h
#define GeDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "tls.hh"
#include "G4GenericMessenger.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"

// These two classes are called within the construct function
class G4VPhysicalVolume;
class G4LogicalVolume;


class GeDetectorConstruction : public G4VUserDetectorConstruction
{
   public:
      GeDetectorConstruction();
      virtual ~GeDetectorConstruction();

   public:
      virtual G4VPhysicalVolume* Construct();
      void SetWallThick(G4double WallThick);
      void SetStopPosition (G4double Position);

   private:
      void DefineMaterials();

      G4Box *worldSol, *stopSol;
      G4Tubs *detTubeSol, *gasSol, *anodeTubeSol, *blockSol, *frameSol;
      G4LogicalVolume *worldLog, *gasLog, *anodeTubeLog, *detTubeLog, *blockLog, *frameLog, *stopLog;
      G4VPhysicalVolume *worldPhys, *detTubePhys, *gasPhys, *anodeTubePhys, *blockPhys1, *blockPhys2, *framePhys, *stopPhys;

      G4double detWallThick, stopPosition;

      G4Material *world_mat, *gas_mat, *tube_mat, *frame_mat;

      G4GenericMessenger *fMessenger;

};

#endif
