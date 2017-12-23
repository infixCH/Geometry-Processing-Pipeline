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
 * Author: Aurel Gruber on 12.09.17.
 */

#ifndef GEOMETRYPROCESSINGPIPELINE_SCANPROCESSOR_H
#define GEOMETRYPROCESSINGPIPELINE_SCANPROCESSOR_H

#include "macros.h"
#include <Eigen/Dense>
#include <vector>
#include "Geometry.h"
#include "AbstractStage.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    class ProcessVisualizer; // forward declaration

/**
 * Takes a Geometryned Geometry and several processing stages and computes the new geometry.
 */
    class GeometryProcessor {
        friend class ProcessVisualizer;

    private:
        typedef std::function<void(double, std::string)> ProgressCallback;

        Geometry mInputGeometry;
        std::vector<std::shared_ptr<AbstractStage>> mStages;
        ProgressCallback mCallback;

    public:
        GeometryProcessor(std::function<void(double, std::string)> callback);

        void addStage(std::shared_ptr<AbstractStage> s);
        void clearStages();
        void processGeometry(GPP::Geometry &g);

        void getResultingGeometry(Geometry &g) const;
        void getAdditionalResultingGeometries(std::vector<Geometry> &otherOutputs) const;

    };

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
#endif //GEOMETRYPROCESSINGPIPELINE_SCANPROCESSOR_H
