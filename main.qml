import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick3D

import instancetable
import controller

Window {
    id: window
    title: "ANN Visualization"
    width: 800
    height: 600
    visible: true

    View3D {
        id: view
        anchors.fill: parent

        //! [environment]
        environment: SceneEnvironment {
            clearColor: "black"
            backgroundMode: SceneEnvironment.Color
        }
        //! [environment]

        //! [camera]
        Node {
            PerspectiveCamera {
                id: cameraPerspectiveOne
                clipFar: 100000
                //z: 600
                z: 850
                y: 10
            }

            PropertyAnimation on eulerRotation.y {
                loops: Animation.Infinite
                duration: 15000
                to: -360
                from: 0
            }
        }
        //! [camera]

        //! [light]
        DirectionalLight {
            ambientColor: Qt.rgba(0.4, 0.4, 0.4, 1)
            color: Qt.rgba(0.7, 0.7, 0.7, 1)
            brightness: 1.0
            eulerRotation.x: -25
        }

        DirectionalLight {
            color: Qt.rgba(0.7, 0.7, 0.7, 1)
            brightness: 1.0
            eulerRotation.x: -90
            shadowMapFar: 2000
            shadowMapQuality: Light.ShadowMapQualityMedium
            castsShadow: true
            shadowFilter: 25.0
            shadowFactor: 1.0
        }

        //! [light]

        //! [objects]
        Model {
            id: nnCube
            source: "#Cube"
            scale: Qt.vector3d(1, 1, 1)
            materials: [ DefaultMaterial {
                    //diffuseColor: "purple"
                }
            ]
            instancing: InstanceTable {}
        }

        Model {
            id: field
            source: "#Cube"
            scale: Qt.vector3d(50, 0.1, 50)
            position: Qt.vector3d(0, -300, 0)
            materials: CustomMaterial {
                fragmentShader: "blend.frag"
            }

        }

        //! [objects]

        //! [features]
        Controller {
            id: nnController
            instanceTable: nnCube.instancing
            neuralNetworkSize: [
                Qt.size(28, 28),
                Qt.size(28, 28),
                Qt.size(28, 28),
                Qt.size(28, 28),
                Qt.size(10, 1)
            ]
            layerScale: [
                Qt.vector3d(5, 5, 5),
                Qt.vector3d(5, 5, 5),
                Qt.vector3d(5, 5, 5),
                Qt.vector3d(5, 5, 5),
                Qt.vector3d(5, 5, 5)
            ]
        }

        Timer {
            interval: 1000
            running: true
            repeat: true
            triggeredOnStart: true
            onTriggered: {
                nnController.nextInstance();
            }
        }
        //! [features]
    }
}
