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
 * Author: Aurel Gruber on 18.09.17.
 */

#ifndef GEOMETRYPROCESSINGPIPELINE_GUIENTRY_H
#define GEOMETRYPROCESSINGPIPELINE_GUIENTRY_H

#include <string>
#include "macros.h"
#include "Geometry.h"
#include <Eigen/Dense>

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    class GUIEntry {
    private:
        std::string mLabel;
        Geometry mGeometry;

        Eigen::VectorXd mPointWeights;
        Eigen::VectorXd mFaceWeights;

    public:
        GUIEntry(std::string label, Geometry &g): mLabel(label), mGeometry(g) {}
        GUIEntry(std::string label, Geometry &g, Eigen::VectorXd weights);

        bool providesPointWeights() const;
        bool providesFaceWeights() const;

        std::string getLabel() const;

        const Eigen::VectorXd& getPointWeights() const;
        const Eigen::VectorXd& getFaceWeights() const;

        const Geometry& getGeometry() const;
    };

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END

#endif //GEOMETRYPROCESSINGPIPELINE_GUIENTRY_H
