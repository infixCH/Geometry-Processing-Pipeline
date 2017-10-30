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
 * Author: Aurel Gruber on 19.09.17.
 */

#include <set>
#include <queue>
#include <OpenMesh/Tools/Decimater/ModIndependentSetsT.hh>
#include "include/GeometryHelpers.h"
#include "OpenMesh/Tools/Decimater/DecimaterT.hh"
#include "OpenMesh/Tools/Decimater/ModQuadricT.hh"

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

        std::unordered_set<Geometry::VertexHandle> growIsland(
                const Geometry &g,
                const std::unordered_set<Geometry::VertexHandle> &island, int levels)
        {
            std::vector<Geometry::VertexHandle> vertexHandlesToVisit;
            std::vector<Geometry::VertexHandle> newVertexHandlesToVisit;

            std::unordered_set<Geometry::VertexHandle> nextRim;

            for (auto &i: island) {
                vertexHandlesToVisit.push_back(i);
            }

            int nLoops = 0;
            while (nLoops < levels)
            {
                for (auto &v: vertexHandlesToVisit) {
                    for (auto vv_iter = g.cvv_begin(v); vv_iter; ++vv_iter) {
                        if (island.find(*vv_iter) != island.end() ||
                            nextRim.find(*vv_iter) != nextRim.end()) {
                            continue;
                        }

                        newVertexHandlesToVisit.push_back(*vv_iter);
                        nextRim.insert(*vv_iter);
                    }
                }

                vertexHandlesToVisit = newVertexHandlesToVisit;

                ++nLoops;
            }

            return nextRim;
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
            Geometry::Point p1(-100, 0, -100);
            Geometry::Point p2(-100, 0, 100);
            Geometry::Point p3(100, 0, 100);
            Geometry::Point p4(100, 0, -100);

            add4PointPlane(g, p1, p2, p3, p4);
        }

        std::vector<Geometry::VertexHandle> addSphere(Geometry &g, Geometry::Point center, double radius, unsigned int nSegments) {
            std::vector<Geometry::VertexHandle> addedVertices;

            // define helper function for adding verteices
            auto adjustToTargetCoordinates = [&](Geometry::Point &p){
                return p + center;
            };

            // define number of segments
            int nLatitudeSegments = nSegments;
            int nLongitudeSegments = nSegments*2;

            // add top vertex
            Geometry::Point top(0, radius, 0);
            Geometry::VertexHandle top_vh = g.add_vertex(adjustToTargetCoordinates(top));
            addedVertices.push_back(top_vh);

            std::vector<Geometry::VertexHandle> previousCircle(nLongitudeSegments, top_vh);
            std::vector<Geometry::VertexHandle> currentCircle;

            // add all intermediate vertices
            for (int latitude = 1; latitude < nLatitudeSegments; ++latitude) {

                double angle1 = (M_PI / nLatitudeSegments) * latitude;
                double height = cos(angle1)*radius;

                // initial vertex of new level
                Geometry::Point p(0, height, sin(angle1)*radius);
                Geometry::VertexHandle first_vh = g.add_vertex(adjustToTargetCoordinates(p));
                addedVertices.push_back(first_vh);

                currentCircle.push_back(first_vh);

                // add all intermediate vertices on circle
                for (int longitude = 1; longitude < nLongitudeSegments; ++longitude) {

                    double angle2 = (2*M_PI / (nLongitudeSegments)) * longitude;
                    double x = sin(angle1)*sin(angle2)*radius;
                    double z = sin(angle1)*cos(angle2)*radius;

                    Geometry::Point p(x, height, z);

                    Geometry::VertexHandle current_vh = g.add_vertex(adjustToTargetCoordinates(p));
                    addedVertices.push_back(current_vh);


                    g.add_face(previousCircle[longitude-1], *currentCircle.rbegin(), current_vh);
                    if (latitude > 1) {
                        g.add_face(previousCircle[longitude - 1], current_vh,
                                   previousCircle[longitude % (nLongitudeSegments)]);
                    }

                    currentCircle.push_back(current_vh);
                }

                // close circle
                g.add_face(*previousCircle.rbegin(), *currentCircle.rbegin(), *currentCircle.begin());
                if (latitude > 1) {
                    g.add_face(*previousCircle.rbegin(), *currentCircle.begin(), *previousCircle.begin());
                }

                previousCircle = currentCircle;
                currentCircle.clear();
            }

            Geometry::Point bottom(0, -radius, 0);
            Geometry::VertexHandle bottom_vh = g.add_vertex(adjustToTargetCoordinates(bottom));
            addedVertices.push_back(bottom_vh);

            // close sphere
            for (int longitude = 1; longitude <= nLongitudeSegments; ++longitude) {
                g.add_face(previousCircle[longitude-1], bottom_vh, previousCircle[longitude % (nLongitudeSegments)]);
            }

            return addedVertices;
        }

        std::vector<Geometry::VertexHandle>  AddCoordinateAxis(Geometry &g, double size) {
            std::vector<Geometry::VertexHandle> addedVertices;

            double halfThickness = size / 200;

            // create Y
            Geometry::VertexHandle vh1 = g.add_vertex(Geometry::Point(-halfThickness,0,-halfThickness));
            Geometry::VertexHandle vh2 = g.add_vertex(Geometry::Point(halfThickness,0,-halfThickness));
            Geometry::VertexHandle vh3 = g.add_vertex(Geometry::Point(-halfThickness,0,halfThickness));
            Geometry::VertexHandle vh4 = g.add_vertex(Geometry::Point(halfThickness,0,halfThickness));

            g.add_face(vh1, vh2, vh3);
            g.add_face(vh3, vh2, vh4);

            Geometry::VertexHandle vh5 = g.add_vertex(Geometry::Point(-halfThickness,size,-halfThickness));
            Geometry::VertexHandle vh6 = g.add_vertex(Geometry::Point(halfThickness,size,-halfThickness));
            Geometry::VertexHandle vh7 = g.add_vertex(Geometry::Point(-halfThickness,size,halfThickness));
            Geometry::VertexHandle vh8 = g.add_vertex(Geometry::Point(halfThickness,size,halfThickness));

            Geometry::VertexHandle vh9 = g.add_vertex(Geometry::Point(0,size + halfThickness * 6,0));

            g.add_face(vh9, vh6, vh5);
            g.add_face(vh9, vh8, vh6);
            g.add_face(vh9, vh7, vh8);
            g.add_face(vh9, vh5, vh7);

            g.add_face(vh5, vh2, vh1);
            g.add_face(vh5, vh6, vh2);

            g.add_face(vh6, vh8, vh2);
            g.add_face(vh2, vh8, vh4);

            g.add_face(vh8, vh7, vh4);
            g.add_face(vh4, vh7, vh3);

            g.add_face(vh7, vh5, vh3);
            g.add_face(vh3, vh5, vh1);

            // create X
            vh1 = g.add_vertex(Geometry::Point(0, -halfThickness,-halfThickness));
            vh2 = g.add_vertex(Geometry::Point(0, halfThickness,-halfThickness));
            vh3 = g.add_vertex(Geometry::Point(0, -halfThickness,halfThickness));
            vh4 = g.add_vertex(Geometry::Point(0, halfThickness,halfThickness));

            g.add_face(vh3, vh2, vh1);
            g.add_face(vh4, vh2, vh3);

            vh5 = g.add_vertex(Geometry::Point(size, -halfThickness,-halfThickness));
            vh6 = g.add_vertex(Geometry::Point(size, halfThickness,-halfThickness));
            vh7 = g.add_vertex(Geometry::Point(size, -halfThickness,halfThickness));
            vh8 = g.add_vertex(Geometry::Point(size, halfThickness,halfThickness));


            g.add_face(vh5, vh6, vh7);
            g.add_face(vh6, vh8, vh7);

            g.add_face(vh1, vh2, vh5);
            g.add_face(vh2, vh6, vh5);

            g.add_face(vh2, vh8, vh6);
            g.add_face(vh4, vh8, vh2);

            g.add_face(vh4, vh7, vh8);
            g.add_face(vh3, vh7, vh4);

            g.add_face(vh3, vh5, vh7);
            g.add_face(vh1, vh5, vh3);

            // create X
            vh1 = g.add_vertex(Geometry::Point(-halfThickness,-halfThickness, 0));
            vh2 = g.add_vertex(Geometry::Point(halfThickness,-halfThickness, 0));
            vh3 = g.add_vertex(Geometry::Point(-halfThickness,halfThickness, 0));
            vh4 = g.add_vertex(Geometry::Point(halfThickness,halfThickness, 0));

            g.add_face(vh3, vh2, vh1);
            g.add_face(vh4, vh2, vh3);

            vh5 = g.add_vertex(Geometry::Point(-halfThickness,-halfThickness, size));
            vh6 = g.add_vertex(Geometry::Point(halfThickness,-halfThickness, size));
            vh7 = g.add_vertex(Geometry::Point(-halfThickness,halfThickness, size));
            vh8 = g.add_vertex(Geometry::Point(halfThickness,halfThickness, size));


            g.add_face(vh5, vh6, vh7);
            g.add_face(vh6, vh8, vh7);

            g.add_face(vh1, vh2, vh5);
            g.add_face(vh2, vh6, vh5);

            g.add_face(vh2, vh8, vh6);
            g.add_face(vh4, vh8, vh2);

            g.add_face(vh4, vh7, vh8);
            g.add_face(vh3, vh7, vh4);

            g.add_face(vh3, vh5, vh7);
            g.add_face(vh1, vh5, vh3);

            return addedVertices;
        }

        Geometry decimateGeometry(Geometry g, double ratio) {
            typedef OpenMesh::Decimater::DecimaterT<Geometry> Decimator;
            typedef OpenMesh::Decimater::ModQuadricT<Geometry>::Handle QuadModule;

            Decimator decimater(g);
            QuadModule quadModule;

            decimater.add(quadModule);

            decimater.initialize();
            decimater.decimate(static_cast<int>((1.0 - ratio) * g.n_vertices()));

            g.garbage_collection();
            return g;
        }
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END