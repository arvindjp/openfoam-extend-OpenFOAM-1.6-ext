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

#include "dsmcParcel.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(dsmcParcel, 0);
    defineParticleTypeNameAndDebug(dsmcParcel, 0);
    defineParcelTypeNameAndDebug(dsmcParcel, 0);
};


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::dsmcParcel::dsmcParcel
(
    DsmcCloud<dsmcParcel>& owner,
    const vector& position,
    const vector& U,
    const scalar Ei,
    const label celli,
    const label typeId
)
:
    DsmcParcel<dsmcParcel>
    (
        owner,
        position,
        U,
        Ei,
        celli,
        typeId
    )
{}


Foam::dsmcParcel::dsmcParcel
(
    const Cloud<dsmcParcel>& cloud,
    Istream& is,
    bool readFields
)
:
    DsmcParcel<dsmcParcel>(cloud, is, readFields)
{}


// * * * * * * * * * * * * * * * *  Destructors  * * * * * * * * * * * * * * //

Foam::dsmcParcel::~dsmcParcel()
{}


// ************************************************************************* //
