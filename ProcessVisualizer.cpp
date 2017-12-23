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
#include "include/GeometryHelpers.h"
#include <nanogui/messagedialog.h>

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    ProcessVisualizer::ProcessVisualizer(GeometryProcessor &p,
                                         std::string windowTitel,
                                         std::string guiGroupTitel) : mProcessor(p){
        // default saving function only saves output
        mSavingFunction = [&](Geometry &g, const std::vector<Geometry> &otherOutputs) {
            std::string path = nanogui::file_dialog({{"obj", "Wavefront OBJ"}}, true);
            if (path == "") return;

            bool success;
            g.saveGeometry(path, success);

            if (!success) return;
        };

        mViewer.setWindowTitel(windowTitel);
    }

    ProcessVisualizer::ProcessVisualizer(GeometryProcessor &p,
                                         std::string windowTitel,
                                         std::string guiGroupTitel,
                                         std::function<void(Geometry& output, const std::vector<Geometry> &otherOutputs)> savingFunction) : mProcessor(p), mSavingFunction(savingFunction){
        mViewer.setWindowTitel(windowTitel);
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
                mViewer.displayObject(g, weights);
            } else {
                mViewer.displayObject(g);
            }
        });
    }

    void ProcessVisualizer::launch(float scale) {
        auto afterLaunchCallback = [&]() {

            loadGroup = mViewer.addGroup("Load Object");
            loadButton = mViewer.addButton("Load Object from .obj file", [&]() {
                //std::string path = nanogui::file_dialog({{"obj", "Wavefront OBJ"}}, false);
                std::string path = igl::file_dialog_open();

                if (path == "") return;

                bool success;
                Geometry g(path, success);

                if (!success) return;

                mViewer.clearGUI();

                // recursive reference to the callback
                loadGroup = mViewer.addGroup("Load Object");
                loadButton = mViewer.addButton("Load Object from .obj file", loadButton->callback());

                // reset processor
                mProcessor.clearStages();

                mProcessor.processGeometry(g);

                mViewer.addGroup("Processing Steps");

                for (auto stageIter = mProcessor.mStages.begin(); stageIter != mProcessor.mStages.end(); ++stageIter) {
                    int stageNumber = stageIter - mProcessor.mStages.begin();
                    mViewer.addGroup("   " + std::to_string(stageNumber) + ": " + (*stageIter)->getMessage());

                    std::shared_ptr<AbstractStage> s = *stageIter;
                    const std::vector<GUIEntry> &entries = s->getGUIEntries();
                    addEntries(entries);
                }

                mViewer.addGroup("Save Geometry");

                mViewer.addButton("Save processed Objects to .obj file", [&]() {
                    Geometry g;
                    mProcessor.getResultingGeometry(g);
                    mSavingFunction(g, mProcessor.mStages.back()->otherOutputs());
                });

                mViewer.addButton("Exit", [&]() {
                    mViewer.quit();
                });

                mViewer.updateGui();
            });

            mViewer.updateGui();

            Geometry g;
            GeometryHelpers::AddCoordinateAxis(g, scale);
            mViewer.displayObject(g, true);
        };

        mViewer.launch(afterLaunchCallback);
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END