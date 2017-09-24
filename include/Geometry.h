/**
 * Copyright 2017, infix development gmbh <admin@infix.ch>
 *
 * This file is part of the Geometry Processing Pipeline (GPP) Library.
 *
 * The GPP Library is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The GPP Library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the GPP Library. If not, see <http://www.gnu.org/licenses/>.
 *
 * @license LGPL-3.0+
 *
 * Author: Aurel Gruber on 12.09.17.
 */

#ifndef GEOMETRYPROCESSINGPIPELINE_GEOMETRY_H
#define GEOMETRYPROCESSINGPIPELINE_GEOMETRY_H

#include "macros.h"
#include <Eigen/Dense>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    struct GeometryMeshTraits : public OpenMesh::DefaultTraits {
    };

    class Geometry: public OpenMesh::TriMesh_ArrayKernelT<GeometryMeshTraits> {
    public:
        Geometry() {}

        Geometry(Eigen::MatrixXd V, Eigen::MatrixXi F);

        Eigen::MatrixXd V() const;
        Eigen::MatrixXi F() const;

        void setV(Eigen::MatrixXd V);
        void setF(Eigen::MatrixXi F);
    };

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
#endif //GEOMETRYPROCESSINGPIPELINE_GEOMETRY_H
