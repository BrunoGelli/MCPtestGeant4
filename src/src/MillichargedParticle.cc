#include "MillichargedParticle.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"

G4ParticleDefinition* MillichargedParticle::Definition(double charge_fraction)
{
    static G4ParticleDefinition* particle = nullptr;
    if (particle) return particle;

    G4String name = "millicharged";
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4double mass = 105.7 * MeV; // muon-like
    G4double charge = charge_fraction * eplus;
    G4double lifetime = -1.0;

    // particle = new G4ParticleDefinition(
    //     name,       // name
    //     mass,
    //     0.0 * MeV,  // width
    //     charge,
    //     1,          // spin
    //     0, 0,       // parity, C-conjugation
    //     0, 0, 0,    // isospin, isospin3, G-parity
    //     "exotic",   // type
    //     0, 0,       // lepton number, baryon number
    //     9900012,    // PDG encoding
    //     true,       // stable
    //     lifetime,
    //     nullptr,    // decay table
    //     false,      // short lived
    //     "millicharged"  // subtype (MUST NOT BE nullptr)
    // );

    particle = new G4ParticleDefinition(
        "millicharged",    // name
        105.7*MeV,         // mass (muon-like for test)
        0.0*MeV,           // width
        +1.0*eplus,        // charge (use 1.0e for now)
        1,                 // 2*spin
        0,                 // parity
        0,                 // C-conjugation
        0,                 // 2*isospin
        0,                 // 2*isospin3
        0,                 // G-parity
        "lepton",          // type
        0,                 // lepton number
        0,                 // baryon number
        0,                 // PDG encoding
        false,             // stable
        -1,               // lifetime
        nullptr,           // decay table
        false,             // short lived
        "test",           // subType
        0                  // anti_encoding
    );

    return particle;
}
