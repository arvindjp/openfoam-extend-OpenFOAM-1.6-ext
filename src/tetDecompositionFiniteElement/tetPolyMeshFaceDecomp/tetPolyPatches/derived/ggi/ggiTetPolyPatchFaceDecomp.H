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

Class
    ggiTetPolyPatchFaceDecomp

Description
    GGI patch.

Author
    Hrvoje Jasak, Wikki Ltd.  All rights reserved.

SourceFiles
    ggiTetPolyPatchFaceDecomp.C

\*---------------------------------------------------------------------------*/

#ifndef ggiTetPolyPatchFaceDecomp_H
#define ggiTetPolyPatchFaceDecomp_H

#include "faceTetPolyPatchFaceDecomp.H"
#include "ggiPolyPatch.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
               Class ggiTetPolyPatchFaceDecomp Declaration
\*---------------------------------------------------------------------------*/

class ggiTetPolyPatchFaceDecomp
:
    public faceTetPolyPatchFaceDecomp
{

public:

    //- Runtime type information
    TypeName(ggiPolyPatch::typeName_());


    // Constructors

        //- Construct from polyPatch
        ggiTetPolyPatchFaceDecomp
        (
            const polyPatch& patch,
            const tetPolyBoundaryMeshFaceDecomp& bm
        )
        :
            faceTetPolyPatchFaceDecomp(patch, bm)
        {}
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
