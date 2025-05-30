#ifndef MILLICHARGEDPARTICLE_HH
#define MILLICHARGEDPARTICLE_HH

#include "G4ParticleDefinition.hh"

class MillichargedParticle {
public:
    static G4ParticleDefinition* Definition(double charge_fraction = 0.001);
};

#endif
