//
// Created by Aurel Gruber on 15.09.17.
//

#include "include/AbstractStage.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    void Stage::execute(const Geometry &g) {
        mOutputGeometry = g;
        mInputGeometry = g;
        processGeometry();
        createGUIElements();
    }

    std::string Stage::getMessage() {
        return mMessage;
    }

    const std::vector<GUIEntry>& Stage::getGUIEntries() const {
        return mGuiEntries;
    }

    Geometry Stage::output() const {
        return mOutputGeometry;
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END