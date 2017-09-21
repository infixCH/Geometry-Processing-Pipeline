//
// Created by Aurel Gruber on 12.09.17.
//

#ifndef GEOMETRYPROCESSINGPIPELINE_SCANVIEWER_H
#define GEOMETRYPROCESSINGPIPELINE_SCANVIEWER_H

#include "macros.h"
#include <igl/viewer/Viewer.h>
#include <Eigen/Dense>
#include "Geometry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    class GeometryViewer {

    private:
        igl::viewer::Viewer mViewer;
        // TODO(d) merge mLabels and mCallbacks to vector of pairs
        // TODO(d) maybe possible to add as generic GUI objects
        // TODO(d) might be possible to construct viewer with GUI elements already
        std::vector<std::string> mLabels;
        std::vector<std::function<void()>> mCallbacks;
        std::string mWindowTitel;
        std::string mGroupTitel;


        void addAllButtons(igl::viewer::Viewer &v);

    public:
        GeometryViewer();

        void setWindowTitel(std::string windowTitel);
        void setGroupTitel(std::string groupTitel);
        void addButton(std::string label, std::function<void()> callback);

        void displayObject(Geometry g, Eigen::MatrixXd weights);
        void displayObject(Geometry g);

        void launch();
    };

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
#endif //GEOMETRYPROCESSINGPIPELINE_SCANVIEWER_H
