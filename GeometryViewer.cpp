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

        mViewer.callback_init = [&](igl::viewer::Viewer &v){
            // initial window is already set in nanogui code -> must be disposed
            v.ngui->window()->dispose();
            mWindow = v.ngui->addWindow(Eigen::Vector2i(0,0),mWindowTitel);

            afterLaunchCallback();

            return false;
        };
    }

    void GeometryViewer::setWindowTitel(std::string windowTitel) {
        mWindowTitel = windowTitel;
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

    nanogui::Label* GeometryViewer::addGroup(std::string groupName) {
        groups.push_back(mViewer.ngui->addGroup(groupName));
        (*groups.rbegin())->setId(std::to_string(idCounter++));
        return *groups.rbegin();
    }

    nanogui::Button* GeometryViewer::addButton(std::string label, std::function<void()> callback) {
        nanogui::Button* button = mViewer.ngui->addButton(label, callback);
        button->setId(std::to_string(idCounter++));
        return button;
    }

    void GeometryViewer::clearGUI() {
        mViewer.ngui->window()->dispose();
        mWindow = mViewer.ngui->addWindow(Eigen::Vector2i(0,0),mWindowTitel);
    }

    void GeometryViewer::launch(std::function<void()> callback) {
        afterLaunchCallback = callback;
        mViewer.launch();
    }

    void GeometryViewer::updateGui(){
        mViewer.screen->performLayout();
    }

    void GeometryViewer::quit(){
        glfwSetWindowShouldClose(mViewer.window, 1);
    }


GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END