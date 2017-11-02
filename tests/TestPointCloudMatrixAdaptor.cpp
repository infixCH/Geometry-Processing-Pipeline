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

    Eigen::MatrixX2f points(3,2);

    points << 0, 0,
            2, 0,
            2.5, 0;


    GPP::PointCloudMatrixAdaptor<2, float> pc(&points);

    pc.buildKdTree();

    std::pair<int, float> closest = pc.findNearestPoint(Eigen::Vector2f(2.4, 0));

    std::cout << closest.first << std::endl;

    ASSERT_NEAR(closest.second, pow(0.1, 2), 1E-6);
}

TEST(GPPPointCloudTest, simplePointCloud3DTest){

    Eigen::MatrixX3f points(3,3);

    points << 0, 0, 0,
            2, 0, 1,
            2.5, 0, 0;


    GPP::PointCloudMatrixAdaptor<3, float> pc(&points);

    pc.buildKdTree();

    std::pair<int, float> closest =
            pc.findNearestPoint(Eigen::Vector3f(2.4, 0, 1));

    std::cout << closest.first << std::endl;

    ASSERT_NEAR(closest.second, pow(0.4, 2), 1E-6);
}