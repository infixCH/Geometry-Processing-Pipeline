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

#ifndef GEOMETRYPROCESSINGPIPELINE_STAGE_H
#define GEOMETRYPROCESSINGPIPELINE_STAGE_H

#include "macros.h"
#include <string>
#include <functional>
#include <vector>
#include "Geometry.h"
#include "GUIEntry.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

class AbstractStage {

protected:
    std::string mMessage;

    Geometry mOutputGeometry;
    Geometry mInputGeometry;
    std::vector<GUIEntry> mGuiEntries;

    virtual void processGeometry() = 0;
    virtual void createGUIElements() = 0;

public:
    AbstractStage(std::string message): mMessage(message) {}

    virtual void execute(const Geometry &g);

    std::string getMessage();
    const std::vector<GUIEntry>& getGUIEntries() const;
    Geometry output() const;

    void clearStage();
};

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END

#endif //GEOMETRYPROCESSINGPIPELINE_STAGE_H
