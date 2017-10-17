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

#include "include/ProcessVisualizer.h"


GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    ProcessVisualizer::ProcessVisualizer(GeometryProcessor &p,
                                         std::string windowTitel,
                                         std::string guiGroupTitel) : mProcessor(p){
        mViewer.setWindowTitel(windowTitel);
        mViewer.setGroupTitel(guiGroupTitel);

        for (auto stageIter = p.mStages.begin(); stageIter != p.mStages.end(); ++stageIter){
            std::shared_ptr<AbstractStage> s = *stageIter;

            const std::vector<GUIEntry> &entries = s->getGUIEntries();
            addEntries(entries);
        }
    }

    void ProcessVisualizer::addEntries(const std::vector<GUIEntry> &entries) {
        int entryNumber = 1;

        for (auto entryIter = entries.begin(); entryIter != entries.end(); ++entryIter) {
            addButton(entryNumber++, *entryIter);
        }
    }

    void ProcessVisualizer::addButton(int entryNumber, const GUIEntry &entry) {

        std::string label = std::to_string(entryNumber++) + ". " + entry.getLabel();
        Geometry g = entry.getGeometry();

        Eigen::VectorXd weights;

        if (entry.providesPointWeights()) {
            weights = entry.getPointWeights();
        } else if (entry.providesFaceWeights()) {
            weights = entry.getFaceWeights();
        }

        mViewer.addButton(label, [&, g, weights](){
            if (weights.rows() > 0) {
                mViewer.displayObject(g, weights, true);
            } else {
                mViewer.displayObject(g, true);
            }
        });
    }

    void ProcessVisualizer::launch() {
        mViewer.launch();
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END