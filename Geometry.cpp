//
// Created by Aurel Gruber on 13.09.17.
//

#include "include/Geometry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    Geometry::Geometry(Eigen::MatrixXd V, Eigen::MatrixXi F) {

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

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
