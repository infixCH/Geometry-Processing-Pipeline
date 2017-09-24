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

#include <iostream>
#include "include/GUIEntry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    GUIEntry::GUIEntry(std::string label, Geometry &g, Eigen::VectorXd weights): mLabel(label), mGeometry(g) {
        if (weights.rows() == g.n_vertices()){
            mPointWeights = weights;
        } else if (weights.rows() == g.n_faces()) {
            mFaceWeights = weights;
        } else {
            std::cerr << "Wrong number of weights! Matches neither the number of Vertices nor the number of Faces!"
                      << std::endl;
        }
    }

    bool GUIEntry::providesPointWeights() const {
        return mPointWeights.rows() > 0;
    }

    bool GUIEntry::providesFaceWeights() const {
        return mFaceWeights.rows() > 0;
    }

    std::string GUIEntry::getLabel() const {
        return mLabel;
    }

    const Eigen::VectorXd& GUIEntry::getPointWeights() const {
        return mPointWeights;
    }

    const Eigen::VectorXd& GUIEntry::getFaceWeights() const {
        return mFaceWeights;
    }

    const Geometry& GUIEntry::getGeometry() const {
        return mGeometry;
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
