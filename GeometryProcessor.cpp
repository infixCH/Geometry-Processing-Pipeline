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

#include "include/GeometryProcessor.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    // TODO(d) look into automatic formatting with clang-format
    GeometryProcessor::GeometryProcessor(std::function<void(double, std::string)> callback): mCallback(callback){
    }

    void GeometryProcessor::addStage(std::shared_ptr<AbstractStage> s) {
        mStages.push_back(s);
    }

    void GeometryProcessor::clearStages() {
        for (auto &stage: mStages) {
            stage->clearStage();
        }
    }

    void GeometryProcessor::processGeometry(Geometry &g){
        mInputGeometry = g;
        Geometry previousGeometry = mInputGeometry;

        for (auto stageIter = mStages.begin(); stageIter != mStages.end(); ++stageIter) {
            std::shared_ptr<AbstractStage> s = *stageIter;

            long stageNumber = stageIter - mStages.begin();
            float progress = static_cast<float>(stageNumber)/mStages.size();

            mCallback(progress, s->getMessage());
            s->execute(previousGeometry);

            previousGeometry = s->output();
        }

        mCallback(1.0f, "Processing finished!");
    }

    void GeometryProcessor::getResultingGeometry(Geometry &g) const {
        g = mStages.back()->output();
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END