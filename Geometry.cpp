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
 * Author: Aurel Gruber on 13.09.17.
 */

#include "include/Geometry.h"
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    Geometry::Geometry(Eigen::MatrixXd &V, Eigen::MatrixXi &F) {
        init(V, F);
    }

    Geometry::Geometry(std::string &pathToObj, bool &status) {
        Eigen::MatrixXd V;
        Eigen::MatrixXi F;
        status = igl::readOBJ(pathToObj, V, F);

        if (status) {
            init(V, F);
        } else {
            std::cerr << ".Obj file with scan could not be found!" << std::endl;
        }
    }

    void Geometry::init(Eigen::MatrixXd &V, Eigen::MatrixXi &F) {

        for (int i = 0; i < V.rows(); ++i) {
            Point p(V(i, 0), V(i,1), V(i,2));
            add_vertex(p);
        }

        for (int i = 0; i < F.rows(); ++i) {
            VertexHandle vh1 = vertex_handle(F(i, 0));
            VertexHandle vh2 = vertex_handle(F(i, 1));
            VertexHandle vh3 = vertex_handle(F(i, 2));

            add_face(vh1, vh2, vh3);
        }
    }

    Eigen::MatrixXd Geometry::V() const {
        Eigen::MatrixXd V(n_vertices(), 3);

        for (auto vIter = vertices_begin(); vIter!=vertices_end(); ++vIter) {
            Point p = point(vIter);
            int id = vIter->idx();

            V(id, 0) = p[0];
            V(id, 1) = p[1];
            V(id, 2) = p[2];
        }

        return V;
    }

    Eigen::MatrixXi Geometry::F() const {
        Eigen::MatrixXi F(n_faces(), 3);

        for (auto fIter = faces_begin(); fIter!=faces_end(); ++fIter) {
            int id = fIter->idx();

            int i = 0;
            for (auto vIter = cfv_begin(fIter); vIter; ++vIter) {
                F(id, i++) = vIter->idx();
            }
        }

        return F;
    }

    void Geometry::setV(Eigen::MatrixXd V) {

        if (V.rows() != n_vertices()){
            std::cerr << "Wrong number of vertices!" << std::endl;
            return;
        }

        for (int i = 0; i < V.rows(); ++i) {
            Point p(V(i,0), V(i,1), V(i,2));
            set_point(vertex_handle(i), p);
        }
    }

    void Geometry::setF(Eigen::MatrixXi F) {
        for (auto fIter = faces_begin(); fIter != faces_end(); ++fIter) {
            delete_face(fIter);
        }

        for (int i = 0; i < F.rows(); ++i) {
            VertexHandle vh1 = vertex_handle(F(i, 0));
            VertexHandle vh2 = vertex_handle(F(i, 1));
            VertexHandle vh3 = vertex_handle(F(i, 2));

            add_face(vh1, vh2, vh3);
        }
    }

    void Geometry::saveGeometry(std::string &pathToObj, bool &status) {

        status = igl::writeOBJ(pathToObj, V(), F());

        if (!status) {
            std::cerr << "File could not be written!" << std::endl;
        }
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
