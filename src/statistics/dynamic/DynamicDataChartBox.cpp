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

#include <QDebug>
#include <iostream>
#include <mutex>

#include <fastdds_monitor/statistics/dynamic/DynamicDataChartBox.h>
#include <fastdds_monitor/utils.h>

QtCharts::QVXYModelMapper* DynamicDataChartBox::add_series(
        QString statistic_kind,
        models::EntityId source_id,
        models::EntityId target_id /* = ID_INVALID */)
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    quint64 new_id;

    auto new_mapper = DataChartBox::add_series(new DataModel(), new_id);

    if (new_mapper)
    {
        current_update_parameters_.series_ids.push_back(new_id);
        current_update_parameters_.source_ids.push_back(source_id);
        current_update_parameters_.target_ids.push_back(target_id);
        current_update_parameters_.statistics_kinds.push_back(statistic_kind);
    }

    return new_mapper;
}

void DynamicDataChartBox::delete_series_by_order_index(
        quint64 series_order_index)
{
    DataChartBox::delete_series_by_order_index(series_order_index);

    current_update_parameters_.series_ids.erase(
        current_update_parameters_.series_ids.begin() + series_order_index);
    current_update_parameters_.source_ids.erase(
        current_update_parameters_.source_ids.begin() + series_order_index);
    current_update_parameters_.target_ids.erase(
        current_update_parameters_.target_ids.begin() + series_order_index);
    current_update_parameters_.statistics_kinds.erase(
        current_update_parameters_.statistics_kinds.begin() + series_order_index);
}

void DynamicDataChartBox::update(
        std::map<quint64, QVector<QPointF>>& new_data,
        quint64 time_to)
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    // Update internal timer so next call to get data use it as from
    time_to_ = time_to;

    DataChartBox::update(new_data);
}

UpdateParameters DynamicDataChartBox::get_update_parameters()
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);
    current_update_parameters_.time_from = time_to_;
    return current_update_parameters_;
}

void DynamicDataChartBox::clear_charts()
{
    const std::lock_guard<std::recursive_mutex> lock(mutex_);

    DataChartBox::clear_charts();

    current_update_parameters_.series_ids.clear();
    current_update_parameters_.source_ids.clear();
    current_update_parameters_.target_ids.clear();
    current_update_parameters_.statistics_kinds.clear();
}