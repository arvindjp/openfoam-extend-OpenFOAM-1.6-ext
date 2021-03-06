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

#include "NASsurfaceFormatCore.H"
#include "IStringStream.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Do weird things to extract a floating point number
Foam::scalar Foam::fileFormats::NASsurfaceFormatCore::parseNASCoord
(
    const string& s
)
{
    size_t expSign = s.find_last_of("+-");

    if (expSign != string::npos && expSign > 0 && !isspace(s[expSign-1]))
    {
        scalar mantissa = readScalar(IStringStream(s.substr(0, expSign))());
        scalar exponent = readScalar(IStringStream(s.substr(expSign+1))());

        if (s[expSign] == '-')
        {
            exponent = -exponent;
        }
        return mantissa * pow(10, exponent);
    }
    else
    {
        return readScalar(IStringStream(s)());
    }
}


// ************************************************************************* //
