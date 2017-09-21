//
// Created by Aurel Gruber on 18.09.17.
//

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
