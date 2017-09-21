//
// Created by Aurel Gruber on 12.09.17.
//

#include <iostream>
#include "include/CLAParser.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    namespace CLAParsing {

        int parse(int argc, char *argv[]) {

            switch (argc) {
                case 3:
                    return Options::VIEWER;
                case 4:
                    if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--hidden") {
                        return Options::HIDDEN;
                    }
                    // no break here!
                default:
                    printCLAUsage(argv[0]);
                    return Options::INVALID;
            }
        }

        void printCLAUsage(std::string executable) {
            std::cout << "Usage: \n"
                      << executable << " <option(s)> PATH_TO_RAW_SCAN DESTINATION_OF_PROCESSED_SCAN\n"
                      << "Options: \n"
                      << "\t-h, --hidden\t\tDoes NOT launch the viewer to show intermediate steps."
                      << std::endl;
        }
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END
