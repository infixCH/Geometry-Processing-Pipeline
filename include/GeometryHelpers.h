//
// Created by Aurel Gruber on 19.09.17.
//

#ifndef GEOMETRYPROCESSINGPIPELINE_GEOMETRYHELPERS_H
#define GEOMETRYPROCESSINGPIPELINE_GEOMETRYHELPERS_H

#include <Eigen/Dense>
#include <unordered_set>
#include <stack>
#include "macros.h"

#include "Geometry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

namespace GeometryHelpers {

    Eigen::Matrix3d rotationMatrixFromUpVector(const Eigen::Vector3d &up);

    void fitPointsToPlane(const Eigen::Matrix3Xd &points,
                          Eigen::Vector3d &centroid,
                          Eigen::Vector3d &planeBase1,
                          Eigen::Vector3d &planeBase2,
                          Eigen::Vector3d &normal);

    void findLocalMinimas(const Geometry &g,
                          std::unordered_set<Geometry::VertexHandle> &localMinimas);

    void add4PointPlane(Geometry &g,
                        Geometry::Point p1,
                        Geometry::Point p2,
                        Geometry::Point p3,
                        Geometry::Point p4);

    void addGroundPlane(Geometry &g);
}

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END

#endif //GEOMETRYPROCESSINGPIPELINE_GEOMETRYHELPERS_H

