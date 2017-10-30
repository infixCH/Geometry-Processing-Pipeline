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
        std::function<void()> afterLaunchCallback;

    public:
        GeometryViewer();

        void setWindowTitel(std::string windowTitel);
        void setGroupTitel(std::string groupTitel);
        void addButton(std::string label, std::function<void()> callback);

        void displayObject(Geometry g, Eigen::MatrixXd weights, bool align = false);
        void displayObject(Geometry g, bool align = false);

        void launch(std::function<void()> callback = [](){});
    };

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
#endif //GEOMETRYPROCESSINGPIPELINE_SCANVIEWER_H
