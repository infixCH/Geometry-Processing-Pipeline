//
// Created by Aurel Gruber on 12.09.17.
//

#include "include/GeometryViewer.h"
#include <igl/jet.h>

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    GeometryViewer::GeometryViewer(std::string &windowTitel, std::string &groupTitel) {
        mViewer.callback_init = [&](igl::viewer::Viewer v){
            // TODO(d) comment for disposing default window
            v.ngui->window()->dispose();
            v.ngui->addWindow(Eigen::Vector2i(220,10),windowTitel);
            v.ngui->addGroup(groupTitel);

            addAllButtons(v);

            v.screen->performLayout();

            return false;
        };
    }

    void GeometryViewer::addAllButtons(igl::viewer::Viewer &v) {
        for (int i = 0; i < mLabels.size(); ++i) {
            v.ngui->addButton(mLabels[i], mCallbacks[i]);
        }
    }

    void GeometryViewer::displayObject(Geometry g, Eigen::MatrixXd weights) {

        Eigen::MatrixXd colors;
        igl::jet(weights, true, colors);

        mViewer.data.clear();
        mViewer.data.set_mesh(g.V(), g.F());
        mViewer.core.align_camera_center(g.V(), g.F());
        mViewer.data.set_colors(colors);
        mViewer.draw();
    }

    void GeometryViewer::displayObject(Geometry g) {
        mViewer.data.clear();
        mViewer.data.set_mesh(g.V(), g.F());
        mViewer.draw();
    }

    void GeometryViewer::addButton(std::string label, std::function<void()> callback) {
        mLabels.push_back(label);
        mCallbacks.push_back(callback);
    }

    void GeometryViewer::launch() {
        mViewer.launch();
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END