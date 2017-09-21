//
// Created by Aurel Gruber on 12.09.17.
//

#ifndef GEOMETRYPROCESSINGPIPELINE_CLAPARSER_H
#define GEOMETRYPROCESSINGPIPELINE_CLAPARSER_H

#include "macros.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    namespace CLAParsing {

        enum Options {
            INVALID = 1,
            VIEWER = 2,
            HIDDEN = 3,
        };

        int parse(int argc, char *argv[]);

        void printCLAUsage(std::string executable);

    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
#endif //GEOMETRYPROCESSINGPIPELINE_CLAPARSER_H
