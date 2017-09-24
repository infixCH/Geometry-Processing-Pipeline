//
// Created by Aurel Gruber on 15.09.17.
//

#ifndef GEOMETRYPROCESSINGPIPELINE_STAGE_H
#define GEOMETRYPROCESSINGPIPELINE_STAGE_H

#include "macros.h"
#include <string>
#include <functional>
#include <vector>
#include "Geometry.h"
#include "GUIEntry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

class AbstractStage {

protected:
    std::string mMessage;

    Geometry mOutputGeometry;
    Geometry mInputGeometry;
    std::vector<GUIEntry> mGuiEntries;

    virtual void processGeometry() = 0;
    virtual void createGUIElements() = 0;

public:
    AbstractStage(std::string message): mMessage(message) {}

    virtual void execute(const Geometry &g);

    std::string getMessage();
    const std::vector<GUIEntry>& getGUIEntries() const;
    Geometry output() const;
};

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END

#endif //GEOMETRYPROCESSINGPIPELINE_STAGE_H
