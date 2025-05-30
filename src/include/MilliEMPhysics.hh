#ifndef MILLI_EM_PHYSICS_HH
#define MILLI_EM_PHYSICS_HH

#include "G4VPhysicsConstructor.hh"

class MilliEMPhysics : public G4VPhysicsConstructor {
public:
    MilliEMPhysics();
    virtual ~MilliEMPhysics() = default;

    virtual void ConstructParticle() override;
    virtual void ConstructProcess() override;
};

#endif