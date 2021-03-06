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

Typedef
    Foam::complexField

Description
    Specialisation of Field\<T\> for complex.

Typedef
    Foam::complexVectorField

Description
    Specialisation of Field\<T\> for complexVector.

SourceFiles
    complexFields.C

\*---------------------------------------------------------------------------*/

#ifndef complexFields_H
#define complexFields_H

#include "complex.H"
#include "complexVector.H"
#include "primitiveFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

typedef Field<complex> complexField;

complexField ComplexField(const UList<scalar>&, const UList<scalar>&);
complexField ReComplexField(const UList<scalar>&);
complexField ImComplexField(const UList<scalar>&);
scalarField Re(const UList<complex>&);
scalarField Im(const UList<complex>&);
scalarField ReImSum(const UList<complex>&);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

typedef Field<complexVector> complexVectorField;

complexVectorField ComplexField(const UList<vector>&, const UList<vector>&);
complexVectorField ReComplexField(const UList<vector>&);
complexVectorField ImComplexField(const UList<vector>&);
vectorField Re(const UList<complexVector>&);
vectorField Im(const UList<complexVector>&);
vectorField ReImSum(const UList<complexVector>&);

complexVectorField operator^
(
    const UList<vector>&,
    const UList<complexVector>&
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
