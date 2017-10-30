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

#ifndef GEOMETRYPROCESSINGPIPELINE_GEOMETRYHELPERS_H
#define GEOMETRYPROCESSINGPIPELINE_GEOMETRYHELPERS_H

#include <Eigen/Dense>
#include <unordered_set>
#include <stack>
#include "macros.h"

#include <iostream>
#include "Geometry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

namespace GeometryHelpers {

    Eigen::Matrix3d rotationMatrixFromUpVector(const Eigen::Vector3d &up);

    void fitPointsToPlane(const Eigen::Matrix3Xd &points,
                          Eigen::Vector3d &centroid,
                          Eigen::Vector3d &planeBase1,
                          Eigen::Vector3d &planeBase2,
                          Eigen::Vector3d &normal);

    std::unordered_set<Geometry::VertexHandle> growIsland(
            const Geometry &g,
            const std::unordered_set<Geometry::VertexHandle> &island, int levels);

    void findLocalMinimas(const Geometry &g,
                          std::unordered_set<Geometry::VertexHandle> &localMinimas);

    void add4PointPlane(Geometry &g,
                        Geometry::Point p1,
                        Geometry::Point p2,
                        Geometry::Point p3,
                        Geometry::Point p4);

    void addGroundPlane(Geometry &g);

    std::vector<Geometry::VertexHandle>  addSphere(Geometry &g, Geometry::Point center, double radius, unsigned int nSegments);

    std::vector<Geometry::VertexHandle>  AddCoordinateAxis(Geometry &g, double size);

    Geometry decimateGeometry(Geometry g, double ratio);

}

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END

#endif //GEOMETRYPROCESSINGPIPELINE_GEOMETRYHELPERS_H

