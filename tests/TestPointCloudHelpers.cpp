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

//
// Created by Aurel Gruber on 21.10.17.
//

#include "../include/Geometry.h"
#include "../include/PointCloudHelpers.h"
#include "../include/PointCloudMatrixAdaptor.h"
#include "../external/GTest/googletest/include/gtest/gtest.h"

TEST(GPPPointCloudTest, simplePointCloud2DTest){

    std::vector<GPP::Geometry::Point> points;

    GPP::Geometry g;

    g.add_vertex(GPP::Geometry::Point(0, 0, 0));
    g.add_vertex(GPP::Geometry::Point(2, 0, 0));
    g.add_vertex(GPP::Geometry::Point(2.5, 0, 0));


    GPP::PointCloudMatrixAdaptor<2> pc(&g);

    GPP::PointCloudHelpers::KDTree<2> kdtree(-1 /*dimension set by typedef*/, pc);
    kdtree.buildIndex();

    std::pair<GPP::Geometry::VertexHandle, double> closest =
            GPP::PointCloudHelpers::findNearestPoint(pc,
                                                     GPP::Geometry::Point(2.4, 0, 0),
                                                     g,
                                                     &kdtree);

    std::cout << closest.first.idx() << std::endl;

    ASSERT_NEAR(closest.second, pow(0.1, 2), 1E-6);
}

TEST(GPPPointCloudTest, simplePointCloud3DTest){

    std::vector<GPP::Geometry::Point> points;

    GPP::Geometry g;

    g.add_vertex(GPP::Geometry::Point(0, 0, 0));
    g.add_vertex(GPP::Geometry::Point(2, 0, 1));
    g.add_vertex(GPP::Geometry::Point(2.5, 0, 0));


    GPP::PointCloudMatrixAdaptor<3> pc(&g);

    GPP::PointCloudHelpers::KDTree<3> kdtree(-1 /*dimension set by typedef*/, pc);
    kdtree.buildIndex();

    std::pair<GPP::Geometry::VertexHandle, double> closest =
            GPP::PointCloudHelpers::findNearestPoint(pc,
                                                     GPP::Geometry::Point(2.4, 0, 1),
                                                     g,
                                                     &kdtree);

    std::cout << closest.first.idx() << std::endl;

    ASSERT_NEAR(closest.second, pow(0.4, 2), 1E-6);
}