//
// Created by Aurel Gruber on 19.09.17.
//

#include "include/GeometryHelpers.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    namespace GeometryHelpers {

        Eigen::Matrix3d rotationMatrixFromUpVector(const Eigen::Vector3d &up) {

                Eigen::Vector3d xProjected = up;
                xProjected(0) = 0;
                xProjected.normalize();
                double sign = xProjected(2) > 0 ? -1 : 1;

                double angleX = sign * acos(xProjected(1));

                Eigen::Matrix3d rotX;

                rotX << 1, 0, 0,
                        0, cos(angleX), -sin(angleX),
                        0, sin(angleX), cos(angleX);

                Eigen::Vector3d upX = rotX * up;

                Eigen::Vector3d zProjected = upX;
                zProjected(2) = 0;
                zProjected.normalize();
                sign = zProjected(0) > 0 ? 1 : -1;

                double angleZ = sign * acos(zProjected(1));

                Eigen::Matrix3d rotZ;

                rotZ << cos(angleZ), -sin(angleZ), 0,
                        sin(angleZ), cos(angleZ), 0,
                        0, 0, 1;

                Eigen::Vector3d upZ = rotZ * rotX * up;

                return rotZ * rotX;
        }

        void fitPointsToPlane(const Eigen::Matrix3Xd &points,
                              Eigen::Vector3d &centroid,
                              Eigen::Vector3d &planeBase1,
                              Eigen::Vector3d &planeBase2,
                              Eigen::Vector3d &normal) {

            //fit plane to points and find plane normal
            centroid = points.rowwise().mean();
            const Eigen::Matrix3Xd centeredPoints = points.colwise() - centroid;
            const Eigen::JacobiSVD<Eigen::Matrix3Xd> svd = centeredPoints.jacobiSvd(Eigen::ComputeFullU);

            Eigen::Matrix3d U = svd.matrixU();

            planeBase1 = U.col(0);
            planeBase2 = U.col(1);
            normal = U.col(2);

            // ensure upward normal
            if (normal(1) < 0) {
                normal = -normal;
            }
        }


        void findLocalMinimas(const Geometry &g,
                              std::unordered_set<Geometry::VertexHandle> &localMinimas) {

            for (auto vIter = g.vertices_begin(); vIter != g.vertices_end(); ++vIter){

                Geometry::Point p = g.point(vIter);
                bool isLocalMinimum = true;

                for (auto vvIter = g.cvv_begin(vIter); vvIter; ++vvIter) {
                    Geometry::Point np = g.point(vvIter);

                    if (np[1] < p[1]) {
                        isLocalMinimum = false;
                        break;
                    }
                }

                if (isLocalMinimum) {
                    localMinimas.insert(*vIter);
                }
            }
        };

        void add4PointPlane(Geometry &g,
                            Geometry::Point p1,
                            Geometry::Point p2,
                            Geometry::Point p3,
                            Geometry::Point p4){

            Geometry::VertexHandle v1 = g.add_vertex(p1);
            Geometry::VertexHandle v2 = g.add_vertex(p2);
            Geometry::VertexHandle v3 = g.add_vertex(p3);
            Geometry::VertexHandle v4 = g.add_vertex(p4);

            g.add_face(v1, v2, v3);
            g.add_face(v3, v4, v1);
        };


        void addGroundPlane(Geometry &g) {
            Geometry::Point p1(-10, 0, -10);
            Geometry::Point p2(-10, 0, 10);
            Geometry::Point p3(10, 0, 10);
            Geometry::Point p4(10, 0, -10);

            add4PointPlane(g, p1, p2, p3, p4);
        }

    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END