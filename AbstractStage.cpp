//
// Created by Aurel Gruber on 15.09.17.
//

#include "include/AbstractStage.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    void AbstractStage::execute(const Geometry &g) {
        mOutputGeometry = g;
        mInputGeometry = g;
        processGeometry();
        createGUIElements();
    }

    std::string AbstractStage::getMessage() {
        return mMessage;
    }

    const std::vector<GUIEntry>& AbstractStage::getGUIEntries() const {
        return mGuiEntries;
    }

    Geometry AbstractStage::output() const {
        return mOutputGeometry;
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END