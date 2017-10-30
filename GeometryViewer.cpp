/**
 * Copyright 2017, infix development gmbh <admin@infix.ch>
 *
 * This file is part of the Geometry Processing Pipeline (GPP) Library.
 *
 * The GPP Library is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The GPP Library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the GPP Library. If not, see <http://www.gnu.org/licenses/>.
 *
 * @license LGPL-3.0+
 *
 * Author: Aurel Gruber on 12.09.17.
 */

#include "include/GeometryViewer.h"
#include <igl/jet.h>

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    GeometryViewer::GeometryViewer() {
        mWindowTitel = "Window";
        mGroupTitel = "Group";

        mViewer.callback_init = [&](igl::viewer::Viewer &v){
            // TODO(d) comment for disposing default window
            v.ngui->window()->dispose();
            v.ngui->addWindow(Eigen::Vector2i(220,10),mWindowTitel);
            v.ngui->addGroup(mGroupTitel);

            addAllButtons(v);

            v.screen->performLayout();

            afterLaunchCallback();

            return false;
        };
    }

    void GeometryViewer::setWindowTitel(std::string windowTitel) {
        mWindowTitel = windowTitel;
    }

    void GeometryViewer::setGroupTitel(std::string groupTitel) {
        mGroupTitel = groupTitel;
    }

    void GeometryViewer::addAllButtons(igl::viewer::Viewer &v) {
        for (int i = 0; i < mLabels.size(); ++i) {
            v.ngui->addButton(mLabels[i], mCallbacks[i]);
        }
    }

    void GeometryViewer::displayObject(Geometry g, Eigen::MatrixXd weights, bool align) {

        Eigen::MatrixXd colors;
        igl::jet(weights, true, colors);

        mViewer.data.clear();
        mViewer.data.set_mesh(g.V(), g.F());

        if (align) mViewer.core.align_camera_center(g.V(), g.F());

        mViewer.data.set_colors(colors);
        mViewer.draw();
    }

    void GeometryViewer::displayObject(Geometry g, bool align) {
        mViewer.data.clear();
        mViewer.data.set_mesh(g.V(), g.F());

        if (align) mViewer.core.align_camera_center(g.V(), g.F());

        mViewer.draw();
    }

    void GeometryViewer::addButton(std::string label, std::function<void()> callback) {
        mLabels.push_back(label);
        mCallbacks.push_back(callback);
    }

    void GeometryViewer::launch(std::function<void()> callback) {
        afterLaunchCallback = callback;
        mViewer.launch();
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END