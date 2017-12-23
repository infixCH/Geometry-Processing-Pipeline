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

#include "include/AbstractStage.h"

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_START

    void AbstractStage::execute(const Geometry &g) {
        mOutputGeometry = g;
        mInputGeometry = g;
        processGeometry();
        createGUIElements();
    }

    std::string AbstractStage::getMessage() {
        return mMessage;
    }

    const std::vector<GUIEntry>& AbstractStage::getGUIEntries() const {
        return mGuiEntries;
    }

    Geometry AbstractStage::output() const {
        return mOutputGeometry;
    }

    const std::vector<Geometry>& AbstractStage::otherOutputs() const {
        return mOtherOutputs;
    }

    void AbstractStage::clearStage() {
        mGuiEntries.clear();
        mOtherOutputs.clear();
        mInputGeometry = mOutputGeometry = Geometry();
    }

GEOMETRY_PROCESSING_PIPELINE_NAMESPACE_END