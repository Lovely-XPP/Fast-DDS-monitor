// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// This file is part of eProsima Fast DDS Monitor.
//
// eProsima Fast DDS Monitor is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// eProsima Fast DDS Monitor is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with eProsima Fast DDS Monitor. If not, see <https://www.gnu.org/licenses/>.

#include <fastdds_monitor/backend/backend_utils.h>
#include <fastdds_monitor/model/physical/ProcessModelItem.h>

namespace models {

QVariant ProcessModelItem::data(
        int role) const
{
    switch (role)
    {
        case idRole:
            return this->entity_id();
        case nameRole:
            return this->name();
        case kindRole:
            return this->kind();
        case pidRole:
            return this->pid();
        case aliveRole:
            return this->alive();
        case clickedRole:
            return this->clicked();
        default:
            return QVariant();
    }
}

QString ProcessModelItem::pid() const
{
    return utils::to_QString(backend::get_info_value(info_, "pid"));
}

QHash<int, QByteArray> ProcessModelItem::roleNames() const
{
    QHash<int, QByteArray>  roles = ListItem::roleNames();

    roles[pidRole] = "processPID";

    return roles;
}

} // namespace models
