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
    Foam::fileFormats::WRLsurfaceFormatCore

Description
    Internal class used by the WRLsurfaceFormat

SourceFiles
    WRLsurfaceFormatCore.C

\*---------------------------------------------------------------------------*/

#ifndef WRLsurfaceFormatCore_H
#define WRLsurfaceFormatCore_H

#include "Ostream.H"
#include "OFstream.H"
#include "MeshedSurface.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace fileFormats
{

/*---------------------------------------------------------------------------*\
                    Class WRLsurfaceFormatCore Declaration
\*---------------------------------------------------------------------------*/

class WRLsurfaceFormatCore
{
protected:
    // Protected Member Functions

    //- Write file header
    static void writeHeader
    (
        Ostream&,
        const pointField&,
        const label nFaces,
        const UList<surfZone>&
    );


    //- Write appearance node
    static void writeAppearance(Ostream&);

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fileFormats
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
