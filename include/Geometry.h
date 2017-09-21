//
// Created by Aurel Gruber on 13.09.17.
//

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
