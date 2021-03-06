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

#ifndef GEOMETRYPROCESSINGPIPELINE_PROCESSVISUALIZER_H
#define GEOMETRYPROCESSINGPIPELINE_PROCESSVISUALIZER_H

#include "macros.h"
#include "GeometryProcessor.h"
#include "GeometryViewer.h"
#include "GUIEntry.h"
#include "Geometry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    class ProcessVisualizer {
    private:
        GeometryViewer mViewer;
        GeometryProcessor mProcessor;

        nanogui::Button* loadButton;
        nanogui::Label* loadGroup;

        std::function<void(Geometry& output, const std::vector<Geometry> &otherOutputs)> mSavingFunction;
    public:
        ProcessVisualizer(GeometryProcessor &p,
                          std::string windowTitel,
                          std::string guiGroupTitel);

        ProcessVisualizer(GeometryProcessor &p,
                          std::string windowTitel,
                          std::string guiGroupTitel,
                          std::function<void(Geometry& output, const std::vector<Geometry> &otherOutputs)> savingFunction);

        void addEntries(const std::vector<GUIEntry> &entries);
        void addButton(int entryNumber, const GUIEntry &entry);
        void launch(float scale);
    };

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
#endif //GEOMETRYPROCESSINGPIPELINE_PROCESSVISUALIZER_H
