/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*---------------------------------------------------------------------------*/

#include "infinitelyFastChemistry.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace combustionModels
{
    defineTypeNameAndDebug(infinitelyFastChemistry, 0);
    addToRunTimeSelectionTable
    (
        combustionModel,
        infinitelyFastChemistry,
        dictionary
    );
};
};


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::combustionModels::infinitelyFastChemistry::infinitelyFastChemistry
(
    const dictionary& combustionProperties,
    const hsCombustionThermo& thermo,
    const compressible::turbulenceModel& turbulence,
    const surfaceScalarField& phi,
    const volScalarField& rho
)
:
    combustionModel(combustionProperties, thermo, turbulence, phi, rho),
    C_(readScalar(combustionModelCoeffs_.lookup("C")))
{}


// * * * * * * * * * * * * * * * * Destructors * * * * * * * * * * * * * * * //

Foam::combustionModels::infinitelyFastChemistry::~infinitelyFastChemistry()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void Foam::combustionModels::infinitelyFastChemistry::correct()
{}


Foam::tmp<Foam::volScalarField>
Foam::combustionModels::infinitelyFastChemistry::wFuelNorm() const
{
    return rho_/(mesh_.time().deltaT()*C_);
}


bool Foam::combustionModels::infinitelyFastChemistry::read
(
    const dictionary& combustionProperties
)
{
    combustionModel::read(combustionProperties);
    combustionModelCoeffs_.lookup("C") >> C_ ;

    return true;
}


// ************************************************************************* //
