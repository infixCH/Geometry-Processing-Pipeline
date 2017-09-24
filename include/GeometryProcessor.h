//
// Created by Aurel Gruber on 12.09.17.
//

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
        GeometryProcessor(Geometry inputGeometry, std::function<void(double, std::string)> callback);

        void addStage(std::shared_ptr<AbstractStage> s);
        void processStages();

        void getResultingGeometry(Geometry &g) const;
    };

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
#endif //GEOMETRYPROCESSINGPIPELINE_SCANPROCESSOR_H
