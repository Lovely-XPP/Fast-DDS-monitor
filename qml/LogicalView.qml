// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import QtQuick 2.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQml.Models 2.12

Rectangle {
    id: logicalView

    ListView {
        id: domainList
        model: domainModel
        clip: true
        leftMargin: 5
        bottomMargin: 5
        width: parent.width
        height: parent.height
        delegate: domainListDelegate

        ScrollBar.vertical: ScrollBar { }
    }

    Component {
        id: domainListDelegate

        Item {
            id: domainItem
            width: domainList.width - domainList.leftMargin
            height: domainListColumn.childrenRect.height

            property var item_id: id

            Column {
                id: domainListColumn

                RowLayout {
                    spacing: 8

                    IconSVG {
                        source: "/resources/images/domain.svg"
                        scalingFactor: 1.5
                        Layout.bottomMargin: 5

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if(topicList.height === topicList.collapseHeightFlag) {
                                    topicList.height = 0;
                                }
                                else {
                                    topicList.height = topicList.collapseHeightFlag;
                                }
                            }
                        }
                    }
                    Label {
                        text: name
                        Layout.bottomMargin: 5

                        DifferClickMouseArea {
                            anchors.fill: parent
                            onSingleClick: {
                                if(topicList.height === topicList.collapseHeightFlag) {
                                    topicList.height = 0;
                                }
                                else {
                                    topicList.height = topicList.collapseHeightFlag;
                                }
                            }
                            onDoubleClick: {
                                controller.domain_click(id)
                            }
                        }
                    }
                }
                ListView {
                    id: topicList
                    model: domainModel.subModelFromEntityId(id)
                    property int collapseHeightFlag: childrenRect.height
                    leftMargin: 25
                    width: domainList.width - domainList.leftMargin
                    height: 0
                    contentHeight: contentItem.childrenRect.height
                    clip: true
                    delegate: topicListDelegate
                }

                Component {
                    id: topicListDelegate

                    Item {
                        height: topicListColumn.childrenRect.height

                        ListView.onAdd: {
                            if(topicList.height != 0) {
                                topicList.height = topicList.collapseHeightFlag;
                            }
                        }

                        Column {
                            id: topicListColumn

                            RowLayout {
                                spacing: 8

                                IconSVG {
                                    source: "/resources/images/topic.svg"
                                    scalingFactor: 1.5
                                    Layout.bottomMargin: 5
                                }
                                Label {
                                    text: name
                                    Layout.bottomMargin: 5

                                    MouseArea {
                                        anchors.fill: parent
                                        onDoubleClicked: {
                                            controller.topic_click(id)
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}