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
