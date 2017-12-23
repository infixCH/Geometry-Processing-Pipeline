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
 * Author: Aurel Gruber on 20.11.17
 */

#include <iostream>
#include "include/BooleanOperation.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    namespace BooleanOperation {

        void convertOpenMeshToCork(const Geometry &g, CorkTriMesh &cm) {

            cm.n_vertices = g.n_vertices();
            cm.n_triangles = g.n_faces();
            cm.vertices = (float *) malloc(sizeof(float) * cm.n_vertices * 3);
            cm.triangles = (uint *) malloc(sizeof(uint) * cm.n_triangles * 3);

            // transfer vertices of geometry1
            int i = 0;
            for (auto iter = g.vertices_begin(); iter != g.vertices_end(); ++iter ) {
                Geometry::Point p = g.point(iter);
                cm.vertices[i++] = p[0];
                cm.vertices[i++] = p[1];
                cm.vertices[i++] = p[2];
            }

            // transfer triangles of geometry1
            i = 0;
            for (auto iter = g.faces_begin(); iter != g.faces_end(); ++iter ) {
                for (auto fv_iter = g.cfv_ccwbegin(iter); fv_iter != g.cfv_ccwend(iter); ++fv_iter) {
                    cm.triangles[i++] = fv_iter->idx();
                }
            }
        }

        Geometry convertCorkTriMeshToOpenMesh(const CorkTriMesh &cm) {
            Geometry g;
            for (int i = 0; i < cm.n_vertices; ++i) {
                g.add_vertex(Geometry::Point(cm.vertices[i*3],
                                             cm.vertices[i*3+1],
                                             cm.vertices[i*3+2]));
            }

            for (int i = 0; i < cm.n_triangles; ++i) {
                Geometry::VertexHandle vhs[3];

                for (int j = 0; j < 3; ++j) {
                    vhs[j] = g.vertex_handle(cm.triangles[i*3 + j]);
                }

                g.add_face(vhs[0], vhs[1], vhs[2]);
            }

            return g;
        }

        Geometry difference(const Geometry &g1, const Geometry &g2){
            CorkTriMesh cm1, cm2, cm3;

            convertOpenMeshToCork(g1, cm1);

            convertOpenMeshToCork(g2, cm2);

            std::cout << "isSolid: " << isSolid(cm1) << std::endl;
            std::cout << "isSolid: " << isSolid(cm2) << std::endl;

            computeDifference(cm1, cm2, &cm3);

            Geometry g3 = convertCorkTriMeshToOpenMesh(cm3);

            std::cout << "g3: " << g3.n_vertices() << " " << g3.n_faces() << std::endl;

            freeCorkTriMesh(&cm1);
            freeCorkTriMesh(&cm2);
            freeCorkTriMesh(&cm3);

            return g3;
        }

    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END