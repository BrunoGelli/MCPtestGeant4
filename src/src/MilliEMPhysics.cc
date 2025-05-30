#include "MilliEMPhysics.hh"
#include "MillichargedParticle.hh"  // custom particle header

#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"
#include "G4eIonisation.hh"
#include "G4eMultipleScattering.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

MilliEMPhysics::MilliEMPhysics() : G4VPhysicsConstructor("MilliEMPhysics") {}

void MilliEMPhysics::ConstructParticle() {
    MillichargedParticle::Definition(1.0);  // set desired epsilon
}

void MilliEMPhysics::ConstructProcess() {
    G4ParticleDefinition* milli = G4ParticleTable::GetParticleTable()->FindParticle("millicharged");
    if (!milli) return;

    G4ProcessManager* pmanager = milli->GetProcessManager();

    // Multiple scattering
    auto msc = new G4eMultipleScattering();
    pmanager->AddProcess(msc, -1, 1, 1);

    // Ionization
    auto ion = new G4eIonisation();
    ion->SetStepFunction(0.2, 0.01*cm);  // you can tune this
    pmanager->AddProcess(ion, -1, 2, 2);
}