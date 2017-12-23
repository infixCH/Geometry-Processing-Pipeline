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
 * Author: Aurel Gruber on 25.11.17
 */

//
// Created by Aurel Gruber on 25.11.17.
//



#include "../include/Geometry.h"
#include "../include/GeometryHelpers.h"
#include "../include/BooleanOperation.h"
#include "../external/GTest/googletest/include/gtest/gtest.h"

#include <igl/volume.h>

TEST(GPPBooleanOperationTest, simpleBooleanOperationTest){

    GPP::Geometry sphere1;
    GPP::GeometryHelpers::addSphere(sphere1, GPP::Geometry::Point(0, 0, 0), 0.5, 8);
    std::cout << sphere1.n_vertices() << std::endl;

    GPP::Geometry sphere2;
    GPP::GeometryHelpers::addSphere(sphere2, GPP::Geometry::Point(0.3, 0, 0), 0.5, 8);

    GPP::Geometry g3 = GPP::BooleanOperation::difference(sphere1, sphere2);

    Eigen::VectorXd volumes1;
    igl::volume(sphere1.V(), sphere1.F(), volumes1);

    Eigen::VectorXd volumes2;
    igl::volume(g3.V(), g3.F(), volumes2);

    ASSERT_GT(volumes1.sum(), volumes2.sum());
}