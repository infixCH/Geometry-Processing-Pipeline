//
// Created by Aurel Gruber on 18.09.17.
//

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
