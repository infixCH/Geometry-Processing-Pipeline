# Geometry Processing Pipeline Library
> The GPP Library allows the efficient implementation of pipelines to process geometry and to allow the visualization of intermediate results.

## Release History

* 0.0.1
    * Work in progress

## Initialization of subrepositories

The GPP Library is dependent on the two open source libraries 
[libigl](https://github.com/libigl/libigl) and 
[OpenMesh](https://www.graphics.rwth-aachen.de:9000/OpenMesh/OpenMesh). After cloning you can initialize these submodules with  

```git submodule update --init --recursive```


## Meta

Aurel Gruber, infix development gmbh – aurel.gruber@infix.ch

Distributed under the LGPL license. See ``COPYING`` and ``COPYING.LESSER`` for more information.

[https://github.com/orgs/infixCH](https://github.com/orgs/infixCH)

## Usage example

In a CMake project you can integrate the GPP Library like so:

```
...
add_subdirectory(external/GPP)
include_directories(${GPP_INCLUDE_DIRS})

...

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} GeometryProcessingPipeline)
```

You can then implement your own processing stages by extending from the AbstractStage by 
implementing the two functions processGeometry and createGUIElements:

``` 
#ifndef YOURPROGRAM_INITIALXYROTATION_H
#define YOURPROGRAM_INITIALXYROTATION_H
 
#include "AbstractStage.h"
 
SCAN_RECOGNITION_NAMESPACE_START

    class YourProcessingStage1: public GPP::AbstractStage {
    
    ...
    
    public:
        YourProcessingStage1(std::string message): AbstractStage(message) {}

        virtual void processGeometry();
        virtual void createGUIElements();
    };
 
SCAN_RECOGNITION_NAMESPACE_END
 
#endif //SCANRECOGNITIONSOFTWARE_INITIALXYROTATION_H

```

``` 
#include "GeometryHelpers.h"

SCAN_RECOGNITION_NAMESPACE_START

    void InitialXYRotation::processGeometry() {
        
        // at this point mInputGeometry and mOutputGeometry are identical -> the output of the last stage
        // modify it with the OpenMesh provided interface:
        
        for (auto vIter = mOutputGeometry.vertices_begin(); vIter != mOutputGeometry.vertices_end(); ++vIter ){
            if (mOutputGeometry.is_boundary(vIter)) {
                // do some processing
            }
            
            //do some more processing
        }
        // do some other things
 
        // or extract the Vertex and Face matrices to interface with libigl or other frameworks
    
        Eigen::Matrix3Xd V = mInputGeometry.V();
        Eigen::Matrix3Xd F = mInputGeometry.F();
 
        // modify the matrices in libigl - style
 
        mOutputGeometry.setV(V.transpose());
        mOutputGeometry.setF(F.transpose());
    }
 
  
    void InitialXYRotation::createGUIElements() {
        GPP::Geometry newGeometry = mOutputGeometry;

        mGuiEntries.push_back(GPP::GUIEntry("Processing Step 1 result 1", newGeometry));

        Eigen::VectorXd weights = Eigen::VectorXd::Zero(newGeometry2.n_vertices());
        
        // fill in weight for each vertex or face

        mGuiEntries.push_back(GPP::GUIEntry("Highlighted vertices", newGeometry2, weights));
    }

```

You then instantiate your stages and add them to the GeometryProcessor:

``` 
#include <Eigen/Dense>
 
#include <igl/readOBJ.h>
#include <igl/writeOBJ.h>
 
#include "Geometry.h"
#include "GeometryProcessor.h"
#include "ProcessVisualizer.h"
 
#include "Stages/YourProcessingStage1.h"
#include "Stages/YourProcessingStage2.h"
#include "Stages/YourProcessingStage3.h"
 
// ...
 
GPP::Geometry mInputGeometry;
GPP::Geometry mOutputGeometry;
 
auto callback = [](double progress, std::string message){
    std::cout << progress * 100 << "% " << message << std::endl;
};
 
Eigen::MatrixXd V;
Eigen::MatrixXi F;
bool status = igl::readOBJ(sourcePath, V, F);
 
if (status) {
    mInputGeometry = GPP::Geometry(V, F);
}
 
GPP::GeometryProcessor p(mInputGeometry, callback);
 
p.addStage(std::shared_ptr<GPP::AbstractStage>(new ScanRecognition::OriginalScan("Loading Original Scan...")));
p.addStage(std::shared_ptr<GPP::AbstractStage>(new ScanRecognition::InitialXYRotation("Finding Initial XY-Rotation...")));
p.addStage(std::shared_ptr<GPP::AbstractStage>(new ScanRecognition::RefinedXYRotation("Refining Initial XY-Rotation...")));
 
p.processStages();
 
GPP::ProcessVisualizer v(p, "Scan Recognition Software", "Intermediate Steps");
v.launch();
```

With `v.launch()`the libigl viewer launches and you can use the different buttons to display the 
results of the intermediate stages as captured by your createGUIElements callbacks.
 
Have fun!