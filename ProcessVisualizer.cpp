//
// Created by Aurel Gruber on 12.09.17.
//

#include "include/ProcessVisualizer.h"


GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    ProcessVisualizer::ProcessVisualizer(GeometryProcessor &p,
                                         std::string windowTitel,
                                         std::string guiGroupTitel) : mProcessor(p){
        mViewer.setWindowTitel(windowTitel);
        mViewer.setGroupTitel(guiGroupTitel);

        for (auto stageIter = p.mStages.begin(); stageIter != p.mStages.end(); ++stageIter){
            std::shared_ptr<Stage> s = *stageIter;

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
                mViewer.displayObject(g, weights);
            } else {
                mViewer.displayObject(g);
            }
        });
    }

    void ProcessVisualizer::launch() {
        mViewer.launch();
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END