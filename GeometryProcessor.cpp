//
// Created by Aurel Gruber on 12.09.17.
//

#include "include/GeometryProcessor.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    // TODO(d) look into automatic formatting with clang-format
    GeometryProcessor::GeometryProcessor(Geometry inputGeometry, std::function<void(double, std::string)> callback):
            mInputGeometry(inputGeometry), mCallback(callback) {}

    void GeometryProcessor::addStage(std::shared_ptr<AbstractStage> s) {
        mStages.push_back(s);
    }

    void GeometryProcessor::processStages() {
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