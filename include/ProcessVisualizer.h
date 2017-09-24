//
// Created by Aurel Gruber on 12.09.17.
//

#ifndef GEOMETRYPROCESSINGPIPELINE_PROCESSVISUALIZER_H
#define GEOMETRYPROCESSINGPIPELINE_PROCESSVISUALIZER_H

#include "macros.h"
#include "GeometryProcessor.h"
#include "GeometryViewer.h"
#include "GUIEntry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    class ProcessVisualizer {
    private:
        GeometryViewer mViewer;
        GeometryProcessor &mProcessor;

    public:
        ProcessVisualizer(GeometryProcessor &p,
                          std::string windowTitel,
                          std::string guiGroupTitel);

        void addEntries(const std::vector<GUIEntry> &entries);
        void addButton(int entryNumber, const GUIEntry &entry);
        void launch();
    };

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
#endif //GEOMETRYPROCESSINGPIPELINE_PROCESSVISUALIZER_H
