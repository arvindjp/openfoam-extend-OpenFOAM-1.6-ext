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

#include "complex.H"
#include "IOstreams.H"

#include <sstream>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const Foam::complex::typeName = "complex";
const Foam::complex Foam::complex::zero(0, 0);
const Foam::complex Foam::complex::one(1, 1);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::complex::complex(Istream& is)
{
    is >> *this;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

Foam::word Foam::name(const complex& c)
{
    std::ostringstream buf;
    buf << '(' << c.Re() << ',' << c.Im() << ')';
    return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

Foam::Istream& Foam::operator>>(Istream& is, complex& c)
{
    // Read beginning of complex
    is.readBegin("complex");

    is  >> c.re >> c.im;

    // Read end of complex
    is.readEnd("complex");

    // Check state of Istream
    is.check("operator>>(Istream&, complex&)");

    return is;
}


Foam::Ostream& Foam::operator<<(Ostream& os, const complex& c)
{
    os  << token::BEGIN_LIST
        << c.re << token::SPACE << c.im
        << token::END_LIST;

    return os;
}


// ************************************************************************* //
