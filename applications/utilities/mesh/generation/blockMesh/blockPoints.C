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

Description
    private member of block. Creates vertices for cells filling the block.

\*---------------------------------------------------------------------------*/

#include "error.H"
#include "block.H"

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::block::blockPoints()
{
    // set local variables for mesh specification
    const label ni = blockDef_.n().x();
    const label nj = blockDef_.n().y();
    const label nk = blockDef_.n().z();

    const point p000 = blockDef_.points()[blockDef_.blockShape()[0]];
    const point p100 = blockDef_.points()[blockDef_.blockShape()[1]];
    const point p110 = blockDef_.points()[blockDef_.blockShape()[2]];
    const point p010 = blockDef_.points()[blockDef_.blockShape()[3]];

    const point p001 = blockDef_.points()[blockDef_.blockShape()[4]];
    const point p101 = blockDef_.points()[blockDef_.blockShape()[5]];
    const point p111 = blockDef_.points()[blockDef_.blockShape()[6]];
    const point p011 = blockDef_.points()[blockDef_.blockShape()[7]];

    // list of edge point and weighting factors
    const List<List<point> >& p = blockDef_.blockEdgePoints();
    const scalarListList& w = blockDef_.blockEdgeWeights();

    // generate vertices

    for (label k = 0; k <= nk; k++)
    {
        for (label j = 0; j <= nj; j++)
        {
            for (label i = 0; i <= ni; i++)
            {
                label vertexNo = vtxLabel(i, j, k);

                // points on edges
                vector edgex1 = p000 + (p100 - p000)*w[0][i];
                vector edgex2 = p010 + (p110 - p010)*w[1][i];
                vector edgex3 = p011 + (p111 - p011)*w[2][i];
                vector edgex4 = p001 + (p101 - p001)*w[3][i];

                vector edgey1 = p000 + (p010 - p000)*w[4][j];
                vector edgey2 = p100 + (p110 - p100)*w[5][j];
                vector edgey3 = p101 + (p111 - p101)*w[6][j];
                vector edgey4 = p001 + (p011 - p001)*w[7][j];

                vector edgez1 = p000 + (p001 - p000)*w[8][k];
                vector edgez2 = p100 + (p101 - p100)*w[9][k];
                vector edgez3 = p110 + (p111 - p110)*w[10][k];
                vector edgez4 = p010 + (p011 - p010)*w[11][k];

                // calculate the importance factors for all edges
                // x - direction
                scalar impx1 =
                (
                    (1.0 - w[0][i])*(1.0 - w[4][j])*(1.0 - w[8][k])
                  + w[0][i]*(1.0 - w[5][j])*(1.0 - w[9][k])
                );

                scalar impx2 =
                (
                    (1.0 - w[1][i])*w[4][j]*(1.0 - w[11][k])
                  + w[1][i]*w[5][j]*(1.0 - w[10][k])
                );

                scalar impx3 =
                (
                     (1.0 - w[2][i])*w[7][j]*w[11][k]
                   + w[2][i]*w[6][j]*w[10][k]
                );


                scalar impx4 =
                (
                    (1.0 - w[3][i])*(1.0 - w[7][j])*w[8][k]
                  + w[3][i]*(1.0 - w[6][j])*w[9][k]
                );

                scalar magImpx = impx1 + impx2 + impx3 + impx4;
                impx1 /= magImpx;
                impx2 /= magImpx;
                impx3 /= magImpx;
                impx4 /= magImpx;


                // y - direction
                scalar impy1 =
                (
                    (1.0 - w[4][j])*(1.0 - w[0][i])*(1.0 - w[8][k])
                  + w[4][j]*(1.0 - w[1][i])*(1.0 - w[11][k])
                );

                scalar impy2 =
                (
                    (1.0 - w[5][j])*w[0][i]*(1.0 - w[9][k])
                  + w[5][j]*w[1][i]*(1.0 - w[10][k])
                );

                scalar impy3 =
                (
                    (1.0 - w[6][j])*w[3][i]*w[9][k]
                  + w[6][j]*w[2][i]*w[10][k]
                );

                scalar impy4 =
                (
                    (1.0 - w[7][j])*(1.0 - w[3][i])*w[8][k]
                  + w[7][j]*(1.0 - w[2][i])*w[11][k]
                );

                scalar magImpy = impy1 + impy2 + impy3 + impy4;
                impy1 /= magImpy;
                impy2 /= magImpy;
                impy3 /= magImpy;
                impy4 /= magImpy;


                // z - direction
                scalar impz1 =
                (
                    (1.0 - w[8][k])*(1.0 - w[0][i])*(1.0 - w[4][j])
                  + w[8][k]*(1.0 - w[3][i])*(1.0 - w[7][j])
                );

                scalar impz2 =
                (
                    (1.0 - w[9][k])*w[0][i]*(1.0 - w[5][j])
                  + w[9][k]*w[3][i]*(1.0 - w[6][j])
                );

                scalar impz3 =
                (
                    (1.0 - w[10][k])*w[1][i]*w[5][j]
                  + w[10][k]*w[2][i]*w[6][j]
                );

                scalar impz4 =
                (
                    (1.0 - w[11][k])*(1.0 - w[1][i])*w[4][j]
                  + w[11][k]*(1.0 - w[2][i])*w[7][j]
                );

                scalar magImpz = impz1 + impz2 + impz3 + impz4;
                impz1 /= magImpz;
                impz2 /= magImpz;
                impz3 /= magImpz;
                impz4 /= magImpz;

                // calculate the correction vectors
                vector corx1 = impx1*(p[0][i] - edgex1);
                vector corx2 = impx2*(p[1][i] - edgex2);
                vector corx3 = impx3*(p[2][i] - edgex3);
                vector corx4 = impx4*(p[3][i] - edgex4);

                vector cory1 = impy1*(p[4][j] - edgey1);
                vector cory2 = impy2*(p[5][j] - edgey2);
                vector cory3 = impy3*(p[6][j] - edgey3);
                vector cory4 = impy4*(p[7][j] - edgey4);

                vector corz1 = impz1*(p[8][k] - edgez1);
                vector corz2 = impz2*(p[9][k] - edgez2);
                vector corz3 = impz3*(p[10][k] - edgez3);
                vector corz4 = impz4*(p[11][k] - edgez4);


                // multiply by the importance factor

                // x - direction
                edgex1 *= impx1;
                edgex2 *= impx2;
                edgex3 *= impx3;
                edgex4 *= impx4;

                // y - direction
                edgey1 *= impy1;
                edgey2 *= impy2;
                edgey3 *= impy3;
                edgey4 *= impy4;

                // z - direction
                edgez1 *= impz1;
                edgez2 *= impz2;
                edgez3 *= impz3;
                edgez4 *= impz4;


                // add the contributions
                vertices_[vertexNo] = edgex1 + edgex2 + edgex3 + edgex4;
                vertices_[vertexNo] += edgey1 + edgey2 + edgey3 + edgey4;
                vertices_[vertexNo] += edgez1 + edgez2 + edgez3 + edgez4;

                vertices_[vertexNo] /= 3.0;

                vertices_[vertexNo] += corx1 + corx2 + corx3 + corx4;
                vertices_[vertexNo] += cory1 + cory2 + cory3 + cory4;
                vertices_[vertexNo] += corz1 + corz2 + corz3 + corz4;
            }
        }
    }
}

// ************************************************************************* //
