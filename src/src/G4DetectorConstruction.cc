    #include "G4DetectorConstruction.hh"
    #include "G4Constantes.hh"

    #include "G4Material.hh"
    #include "G4Element.hh"
    #include "G4NistManager.hh"

    #include "G4Box.hh"
    #include "G4Orb.hh"
    #include "G4Tubs.hh"
    #include "G4Sphere.hh"
    #include "G4Trd.hh"

    #include "G4LogicalVolume.hh"
    #include "G4ThreeVector.hh"
    #include "G4PVPlacement.hh"
    #include "G4AutoDelete.hh"
    #include "G4LogicalBorderSurface.hh"
    #include "G4LogicalSkinSurface.hh"
    #include "G4OpticalSurface.hh"

    #include "G4SubtractionSolid.hh"
    #include "G4VSolid.hh"
    #include "G4UnionSolid.hh"
    #include "G4VPVParameterisation.hh"
    #include "G4PVParameterised.hh"


    #include "G4VisAttributes.hh"
    #include "G4Colour.hh"

    #include "G4PhysicalConstants.hh"
    #include "G4SystemOfUnits.hh"
    #include "globals.hh"

    #include "G4Navigator.hh"
    #include "G4VPhysicalVolume.hh"
    #include "G4TransportationManager.hh"

    #include <fstream>
    using namespace std;

    #include "G4NeutronHPManager.hh"
    #include <G4HadronicProcessStore.hh>
    
    //================================================================================

    G4DetectorConstruction::G4DetectorConstruction (G4double RIndex, DetectorConfig& GeoConf)
    : G4VUserDetectorConstruction(), fCheckOverlaps(true), Refr_Index(RIndex),  fConfig(GeoConf) {

        G4NeutronHPManager::GetInstance()->SetVerboseLevel(0);
        G4HadronicProcessStore::Instance()->SetVerbose(0);
        // World
        world_x = 5 * m * 0.5;
        world_y = 5 * m * 0.5;
        world_z = 20 * m * 0.5;

        // VLAr_x =  50 * cm * 0.5;
        // VLAr_y =  50 * cm * 0.5;
        // VLAr_z = 100 * cm * 0.5;
        
        VLAr_x =  10 * m * 0.5;
        VLAr_y =  10 * m * 0.5;
        VLAr_z =  150 * m * 0.5;

        Pixel_x =  1 * cm * 0.5;
        Pixel_y =  1 * cm * 0.5;
        Pixel_z =  1 * cm * 0.5;

    }

    //================================================================================

    G4DetectorConstruction::~G4DetectorConstruction (){;}



    //================================================================================

    G4VPhysicalVolume* G4DetectorConstruction::Construct () {

        // Define materials 
        DefineMaterials();
        
        // Define volumes
        return DefineVolumes();
        
    }

    //================================================================================

    void G4DetectorConstruction::DefineMaterials() {
        
        G4NistManager* nistManager = G4NistManager::Instance();

        nistManager->FindOrBuildMaterial("G4_lAr");
        nistManager->FindOrBuildMaterial("G4_Galactic");
        nistManager->FindOrBuildMaterial("G4_URANIUM_MONOCARBIDE");

        // G4cout << *(G4Material::GetMaterialTable()) << G4endl;
        
    }

    //================================================================================

    G4VPhysicalVolume* G4DetectorConstruction::DefineVolumes() {
        // Get materials
       
        G4Material* Vacuo       = G4Material::GetMaterial("G4_Galactic");       
        G4Material* LAr         = G4Material::GetMaterial("G4_lAr");
        G4Material* HighSP      = G4Material::GetMaterial("G4_URANIUM_MONOCARBIDE");

    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Construction %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    //====================== World ===========-===========

        G4Box*              WorldS          = new G4Box (MUNDO_NOME, world_x, world_y, world_z);

        G4LogicalVolume*    WorldLV         = new G4LogicalVolume (WorldS, LAr, MUNDO_NOME);

        G4VPhysicalVolume*  WorldPV         = new G4PVPlacement (0, G4ThreeVector (), WorldLV, MUNDO_NOME, 0, true, 0, fCheckOverlaps);

    //======================= Parametric volumes =======================


    // // Slice volume (same dimensions for all copies)
    // auto sliceSolid = new G4Box("VLAr", VLAr_x, VLAr_y, VLAr_z);
    // auto sliceLogic = new G4LogicalVolume(sliceSolid, LAr, "VLAr");

    // new G4PVPlacement(0, G4ThreeVector (0,0,0), sliceLogic, "VLAr", WorldLV, false, 0);


        return WorldPV;


        
    }