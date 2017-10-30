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
#include <Eigen/Dense>
#include <nanoflann.hpp>

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    /* Class that represents a Pointcloud according to the expectations of nanoflann. Required (for nanoflann) are the
     * functions marked with REQUIRED in the comment.*/
    template <int dimension, typename T>
    class PointCloudMatrixAdaptor {

        static_assert(dimension == 2 || dimension == 3, "Only 2 or 3 dimensional pointclouds are currently supported!");

    private:

        typedef Eigen::Matrix<T, Eigen::Dynamic, dimension> Matrix;
        Matrix const *m_points;

        typedef nanoflann::KDTreeEigenMatrixAdaptor< Matrix >  KDTree;
        std::shared_ptr<KDTree> kdtree;
        bool isKdtreeBuilt = false;

    public:
        PointCloudMatrixAdaptor(Matrix const *points);

        void buildKdTree();
        void rebuildKdTree();

        std::pair<int, T> findNearestPoint(Eigen::Matrix<T, dimension, 1> queryPoint);
    };

    template<int dimension, typename T>
    PointCloudMatrixAdaptor<dimension, T>::PointCloudMatrixAdaptor(Matrix const *points): m_points(points) {
    }

    template<int dimension, typename T>
    void PointCloudMatrixAdaptor<dimension, T>::buildKdTree() {
        kdtree = std::shared_ptr<KDTree>(new KDTree(*m_points));
        kdtree->index->buildIndex();
        isKdtreeBuilt = true;
    }

    template<int dimension, typename T>
    void PointCloudMatrixAdaptor<dimension, T>::rebuildKdTree() {
        kdtree->index->buildIndex();
        isKdtreeBuilt = true;
    }

    template<int dimension, typename T>
    std::pair<int, T> PointCloudMatrixAdaptor<dimension, T>::findNearestPoint(Eigen::Matrix<T, dimension, 1> queryPoint) {

        if (!isKdtreeBuilt) {
            std::cerr << "You have to call .buildKdTree first!" << std::endl;
            return std::make_pair(-1, std::numeric_limits<T>::infinity());
        }

        int num_results = 1;

        std::vector<long>   ret_index(num_results);
        std::vector<T>   out_dist(num_results);

        kdtree->index->knnSearch( &(queryPoint(0)), num_results, &ret_index[0], &out_dist[0]);

        return std::make_pair( ret_index[0], out_dist[0]);
    };

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END

#endif //SCANRECOGNITIONSOFTWARE_POINTCLOUD_H
