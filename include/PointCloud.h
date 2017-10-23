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
 * Author: Aurel Gruber on 21.10.17
 */

#ifndef SCANRECOGNITIONSOFTWARE_POINTCLOUD_H
#define SCANRECOGNITIONSOFTWARE_POINTCLOUD_H

#include <iostream>
#include "macros.h"
#include "Geometry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    /* Class that represents a Pointcloud according to the expectations of nanoflann. Required (for nanoflann) are the
     * functions marked with REQUIRED in the comment.*/
    template <int dimension>
    class PointCloud {

        static_assert(dimension == 2 || dimension == 3, "Only 2 or 3 dimensional pointclouds are currently supported!");

    private:

        Geometry const *geometry;
        std::vector<Geometry::VertexHandle>  m_points;

    public:
        PointCloud(Geometry const *g);

        // REQUIRED Must return the number of data points
        inline size_t kdtree_get_point_count() const { return m_points.size(); }

        // REQUIRED Returns the dim'th component of the idx'th point in the class.
        inline double kdtree_get_pt(const size_t idx, int dim) const
        {
            if (dim >= dimension) {
                std::cerr << "Accessing the " << dim << "th dimension coordinate of a point in a " << dimension <<
                          "dimensional pointcloud is not possible! Returning 0.";
                return 0;
            }

            // if the second dimension is required in the case of a 2D pointcloud, we return the z coordinate
            dim = (dim == 0) ? 0 : (dimension == 2) ? 2 : dim;

            return geometry->point(m_points[idx])[dim];
        }

        // REQUIRED Optional bounding-box computation: return false to default to a standard bbox computation loop.
        //   Return true if the BBOX was already computed by the class and returned in "bb" so it can be avoided to redo it again.
        //   Look at bb.size() to find out the expected dimensionality (e.g. 2 or 3 for point clouds)
        template <class BBOX>
        bool kdtree_get_bbox(BBOX& /* bb */) const { return false; }

        inline Geometry::VertexHandle kdtree_get_vh(const size_t idx) const
        {
            return m_points[idx];
        }
    };

    template<int dimension>
    PointCloud<dimension>::PointCloud(Geometry const *g): geometry(g)
    {
        for (auto iter = g->vertices_begin(); iter != g->vertices_end(); ++iter) {
            m_points.push_back(*iter);
        }
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END

#endif //SCANRECOGNITIONSOFTWARE_POINTCLOUD_H
