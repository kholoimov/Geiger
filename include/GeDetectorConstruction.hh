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

   private:
      void DefineMaterials();

      G4Box *worldSol;
      G4Tubs *detTubeSol, *gasSol, *anodeTubeSol;
      G4LogicalVolume *worldLog, *gasLog, *anodeTubeLog, *detTubeLog;
      G4VPhysicalVolume *worldPhys, *detTubePhys, *gasPhys, *anodeTubePhys;

      G4double detWallThick;

      G4Material *world_mat, *gas_mat, *tube_mat;

      G4GenericMessenger *fMessenger;

};

#endif