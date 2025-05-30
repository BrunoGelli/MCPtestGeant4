#include "G4PrimaryGeneratorAction.hh"
#include "G4Constantes.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4SystemOfUnits.hh"



// ============================================================================

G4PrimaryGeneratorAction::G4PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(), 
   particleGun(0)
{   
    // default
    flag_alpha=true;
    G4int n_particle = 1;
    particleGun = new G4ParticleGun(n_particle);
    // G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    // G4ParticleDefinition* particle = particleTable->FindParticle("alpha");   
}

// ============================================================================

G4PrimaryGeneratorAction::~G4PrimaryGeneratorAction() {
    
    delete particleGun;
    
}

// ============================================================================

void G4PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) { 
    
    // for mcp

    G4ParticleDefinition* mcp = G4ParticleTable::GetParticleTable()->FindParticle("e-");

    particleGun->SetParticleDefinition(mcp);
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    particleGun->SetParticleEnergy(1.0 * GeV);
    particleGun->SetParticlePosition(G4ThreeVector(0*cm,0*cm,0*m));

    particleGun->GeneratePrimaryVertex(anEvent);
    
}


// ============================================================================

void G4PrimaryGeneratorAction::SetOptPhotonPolar() {
    
    G4double angle = G4UniformRand() * 360.0*deg;
    SetOptPhotonPolar(angle);
    
}

// ============================================================================

void G4PrimaryGeneratorAction::SetOptPhotonPolar(G4double angle) {
    
    if (particleGun->GetParticleDefinition()->GetParticleName() != "opticalphoton") {
        G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
                "the particleGun is not an opticalphoton" << G4endl;
        return;
    }

    G4ThreeVector normal (1., 0., 0.);
    G4ThreeVector kphoton = particleGun->GetParticleMomentumDirection();
    G4ThreeVector product = normal.cross(kphoton);
    G4double modul2       = product*product;

    G4ThreeVector e_perpend (0., 0., 1.);
    if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
    G4ThreeVector e_paralle    = e_perpend.cross(kphoton);

    G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
    particleGun->SetParticlePolarization(polar);
    
}

// ============================================================================
