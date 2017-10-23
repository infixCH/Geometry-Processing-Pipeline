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
 * Author: Aurel Gruber on 22.10.17
 */

#ifndef SCANRECOGNITIONSOFTWARE_POINTCLOUDHELPERS_H
#define SCANRECOGNITIONSOFTWARE_POINTCLOUDHELPERS_H

#include "../include/macros.h"
#include "../include/PointCloud.h"
#include "../include/Geometry.h"
#include "../external/nanoflann/include/nanoflann.hpp"
#include <Eigen/Dense>

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    namespace PointCloudHelpers {

        template <int dimension>
        using KDTree =
        nanoflann::KDTreeSingleIndexAdaptor<
                nanoflann::L2_Simple_Adaptor<double, PointCloud<dimension> > ,
                PointCloud<dimension>,
                dimension /* dim */>;

        template <int dimension>
        std::pair<Geometry::VertexHandle, double> findNearestPoint(PointCloud<dimension> &pc,
                                                                   Geometry::Point queryPoint,
                                                                   Geometry const &g,
                                                                   KDTree<dimension> const *kdtree)
        {
            int num_results = 1;

            double p_coords[dimension];
            if (dimension == 2) {
                p_coords[0] = queryPoint[0];
                p_coords[1] = queryPoint[2];
            } else {
                p_coords[0] = queryPoint[0];
                p_coords[1] = queryPoint[1];
                p_coords[2] = queryPoint[2];
            }

            std::vector<size_t >   ret_index(num_results);
            std::vector<double>   out_dist_sqr(num_results);

            kdtree->knnSearch(p_coords, num_results, &ret_index[0], &out_dist_sqr[0]);

            return std::make_pair( pc.kdtree_get_vh(ret_index[0]), out_dist_sqr[0]);
        };

    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END

#endif //SCANRECOGNITIONSOFTWARE_POINTCLOUDHELPERS_H
