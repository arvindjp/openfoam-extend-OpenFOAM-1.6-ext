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

#include "DsmcParcel.H"
#include "IOstreams.H"
#include "IOField.H"
#include "Cloud.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template <class ParcelType>
Foam::DsmcParcel<ParcelType>::DsmcParcel
(
    const Cloud<ParcelType>& cloud,
    Istream& is,
    bool readFields
)
:
    Particle<ParcelType>(cloud, is, readFields),
    U_(vector::zero),
    Ei_(0.0),
    typeId_(-1)
{
    if (readFields)
    {
        if (is.format() == IOstream::ASCII)
        {
            is >> U_;
            Ei_ = readScalar(is);
            typeId_ = readLabel(is);
        }
        else
        {
            is.read
            (
                reinterpret_cast<char*>(&U_),
                sizeof(U_)
              + sizeof(Ei_)
              + sizeof(typeId_)
            );
        }
    }

    // Check state of Istream
    is.check
    (
        "DsmcParcel<ParcelType>::DsmcParcel"
        "(const Cloud<ParcelType>&, Istream&, bool)"
    );
}


template<class ParcelType>
void Foam::DsmcParcel<ParcelType>::readFields(Cloud<ParcelType>& c)
{
    if (!c.size())
    {
        return;
    }

    Particle<ParcelType>::readFields(c);

    IOField<vector> U(c.fieldIOobject("U", IOobject::MUST_READ));
    c.checkFieldIOobject(c, U);

    IOField<scalar> Ei(c.fieldIOobject("Ei", IOobject::MUST_READ));
    c.checkFieldIOobject(c, Ei);

    IOField<label> typeId(c.fieldIOobject("typeId", IOobject::MUST_READ));
    c.checkFieldIOobject(c, typeId);

    label i = 0;
    forAllIter(typename Cloud<ParcelType>, c, iter)
    {
        ParcelType& p = iter();

        p.U_ = U[i];
        p.Ei_ = Ei[i];
        p.typeId_ = typeId[i];
        i++;
    }
}


template<class ParcelType>
void Foam::DsmcParcel<ParcelType>::writeFields(const Cloud<ParcelType>& c)
{
    Particle<ParcelType>::writeFields(c);

    label np =  c.size();

    IOField<vector> U(c.fieldIOobject("U", IOobject::NO_READ), np);
    IOField<scalar> Ei(c.fieldIOobject("Ei", IOobject::NO_READ), np);
    IOField<label> typeId(c.fieldIOobject("typeId", IOobject::NO_READ), np);

    label i = 0;
    forAllConstIter(typename Cloud<ParcelType>, c, iter)
    {
        const DsmcParcel<ParcelType>& p = iter();

        U[i] = p.U();
        Ei[i] = p.Ei();
        typeId[i] = p.typeId();
        i++;
    }

    U.write();
    Ei.write();
    typeId.write();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class ParcelType>
Foam::Ostream& Foam::operator<<
(
    Ostream& os,
    const DsmcParcel<ParcelType>& p
)
{
    if (os.format() == IOstream::ASCII)
    {
        os  << static_cast<const Particle<ParcelType>& >(p)
            << token::SPACE << p.U()
            << token::SPACE << p.Ei()
            << token::SPACE << p.typeId();
    }
    else
    {
        os  << static_cast<const Particle<ParcelType>& >(p);
        os.write
        (
            reinterpret_cast<const char*>(&p.U_),
            sizeof(p.U())
          + sizeof(p.Ei())
          + sizeof(p.typeId())
        );
    }

    // Check state of Ostream
    os.check
    (
        "Ostream& operator<<(Ostream&, const DsmcParcel<ParcelType>&)"
    );

    return os;
}


// ************************************************************************* //
